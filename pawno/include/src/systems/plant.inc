/*
	Project: GodFather
	File name: systems/trees.inc
	Desc: System sadzenia i podlewania drzew.

	Jak to dziala:
	- kazde drzewo ma 3 znaczniki czasu zapisane w bazie (Grown, WateredUntil, LastUpdate),
	- podlanie drzewa daje "okno wzrostu" (TREE_WATER_AMOUNT sekund),
	- drzewo rosnie tylko wtedy, gdy jest podlane, ale NIE potrzebuje do tego gracza online,
	- postep jest liczony z czasu rzeczywistego, wiec po restarcie serwera i po powrocie
	  gracza wszystko zostaje "dogonione" automatycznie.

	Komendy: /drzewo [posadz | podlej | lista | zetnij tak]
*/

// ---------------------------------------------------------------------------
// Ustawienia
// ---------------------------------------------------------------------------
#define MAX_TREES				300			// globalny limit drzew na serwerze
#define TREE_LIMIT_DEFAULT		5			// limit drzew na postac
#define TREE_LIMIT_VIP			10			// limit dla graczy z pDonateRank > 0
#define TREE_PLANT_COST			0			// koszt posadzenia (0 = za darmo)
#define TREE_MIN_DISTANCE		3.0			// minimalna odleglosc miedzy drzewami
#define TREE_USE_DISTANCE		3.0			// z jakiej odleglosci mozna podlewac / scinac

#define TREE_GROW_TIME			(5 * 86400)	// ile sekund PODLANEGO wzrostu do dojrzalosci (5 dni)
#define TREE_WATER_AMOUNT		(12 * 3600)	// ile sekund wzrostu daje jedno podlanie (12h)
										// podlac mozna, gdy zostalo <= TREE_WATER_AMOUNT wody,
										// wiec maksymalny zapas to 2 x TREE_WATER_AMOUNT (24h)

#define TREE_STAGES				4
#define DIALOG_TREES			200			// sprawdz, czy to ID jest u Ciebie wolne

// Modele obiektow dla kolejnych etapow (sadzonka -> dojrzale).
// UWAGA: to sa przykladowe ID - sprawdz je w edytorze i podmien na wlasne.
new const TreeModels[TREE_STAGES] = {861, 617, 616, 615};

new const TreeStageNames[TREE_STAGES][] = {
	"Sadzonka",
	"Mlode drzewko",
	"Drzewo",
	"Dojrzale drzewo"
};

// ---------------------------------------------------------------------------
// Dane
// ---------------------------------------------------------------------------
enum eTree {
	tUsed,
	tSQL,
	tOwner,				// Characters.ID (PlayerInfo[playerid][pID])
	Float:tX,
	Float:tY,
	Float:tZ,
	Float:tRot,
	tGrown,				// zebrane sekundy wzrostu
	tWateredUntil,		// do kiedy (unix) drzewo ma wode
	tLastUpdate,		// kiedy ostatnio policzono wzrost (unix)
	tStage,
	tObject
};

new TreeData[MAX_TREES][eTree];

// ---------------------------------------------------------------------------
// Funkcje pomocnicze
// ---------------------------------------------------------------------------
stock Tree_GetLimit(playerid) {
	return (PlayerInfo[playerid][pDonateRank] > 0) ? TREE_LIMIT_VIP : TREE_LIMIT_DEFAULT;
}

stock Tree_FormatTime(seconds, dest[], size = sizeof(dest)) {
	if(seconds <= 0) {
		format(dest, size, "brak");
	} else if(seconds >= 86400) {
		format(dest, size, "%dd %dh", seconds / 86400, (seconds % 86400) / 3600);
	} else {
		format(dest, size, "%dh %dm", seconds / 3600, (seconds % 3600) / 60);
	}
}

stock Tree_CalcStage(idx) {
	new grown = TreeData[idx][tGrown];

	if(grown >= TREE_GROW_TIME) return 3;

	new percent = grown * 100 / TREE_GROW_TIME;

	if(percent < 25) return 0;
	if(percent < 60) return 1;
	return 2;
}

stock Tree_FindFreeSlot() {
	for(new i = 0; i < MAX_TREES; i++) {
		if(!TreeData[i][tUsed]) return i;
	}
	return -1;
}

stock Tree_CountOwned(owner) {
	new count;

	for(new i = 0; i < MAX_TREES; i++) {
		if(TreeData[i][tUsed] && TreeData[i][tOwner] == owner) count++;
	}
	return count;
}

// Najblizsze drzewo w zasiegu maxDist (-1 jesli brak). ownerOnly = tylko drzewa gracza.
stock Tree_GetNearest(playerid, Float:maxDist, bool:ownerOnly = false) {
	new nearest = -1, Float:best = maxDist, Float:dist;

	for(new i = 0; i < MAX_TREES; i++) {
		if(!TreeData[i][tUsed]) continue;
		if(ownerOnly && TreeData[i][tOwner] != PlayerInfo[playerid][pID]) continue;

		dist = GetPlayerDistanceFromPoint(playerid, TreeData[i][tX], TreeData[i][tY], TreeData[i][tZ]);

		if(dist <= best) {
			best = dist;
			nearest = i;
		}
	}
	return nearest;
}

stock Tree_FindOwnerOnline(owner) {
	for(new i = 0; i < MAX_PLAYERS; i++) {
		if(IsPlayerConnected(i) && gPlayerLogged[i] && PlayerInfo[i][pID] == owner) return i;
	}
	return INVALID_PLAYER_ID;
}

// ---------------------------------------------------------------------------
// Wzrost, obiekty, baza
// ---------------------------------------------------------------------------

// Nalicza wzrost od ostatniej aktualizacji (dziala tez dla czasu, gdy gracz byl offline).
stock Tree_Sync(idx, now = 0) {
	if(!now) now = gettime();

	if(TreeData[idx][tGrown] < TREE_GROW_TIME) {
		new till = min(now, TreeData[idx][tWateredUntil]);

		if(till > TreeData[idx][tLastUpdate]) {
			TreeData[idx][tGrown] += till - TreeData[idx][tLastUpdate];

			if(TreeData[idx][tGrown] > TREE_GROW_TIME) {
				TreeData[idx][tGrown] = TREE_GROW_TIME;
			}
		}
	}

	TreeData[idx][tLastUpdate] = now;
}

stock Tree_UpdateObject(idx) {
	if(TreeData[idx][tObject]) {
		DestroyDynamicObject(TreeData[idx][tObject]);
	}

	TreeData[idx][tObject] = CreateDynamicObject(TreeModels[TreeData[idx][tStage]],
		TreeData[idx][tX], TreeData[idx][tY], TreeData[idx][tZ],
		0.0, 0.0, TreeData[idx][tRot], 0, 0);
}

stock Tree_Save(idx) {
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "UPDATE `Plants` SET `Grown` = '%d', `WateredUntil` = '%d', `LastUpdate` = '%d' WHERE `ID` = '%d' LIMIT 1",
		TreeData[idx][tGrown], TreeData[idx][tWateredUntil], TreeData[idx][tLastUpdate], TreeData[idx][tSQL]);
	mysql_query(queryStr);
}

stock Tree_Remove(idx) {
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "DELETE FROM `Plants` WHERE `ID` = '%d' LIMIT 1", TreeData[idx][tSQL]);
	mysql_query(queryStr);

	if(TreeData[idx][tObject]) DestroyDynamicObject(TreeData[idx][tObject]);

	TreeData[idx][tUsed] = 0;
	TreeData[idx][tObject] = 0;
}

stock Tree_Create(owner, Float:x, Float:y, Float:z, Float:rot) {
	new idx = Tree_FindFreeSlot();

	if(idx == -1) return -1;

	new now = gettime();

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "INSERT INTO `Plants` (`OwnerID`, `PosX`, `PosY`, `PosZ`, `RotZ`, `Grown`, `WateredUntil`, `LastUpdate`, `Planted`) VALUES ('%d', '%.4f', '%.4f', '%.4f', '%.1f', '0', '%d', '%d', '%d')",
		owner, x, y, z, rot, now + TREE_WATER_AMOUNT, now, now);
	mysql_query(queryStr);

	TreeData[idx][tUsed] = 1;
	TreeData[idx][tSQL] = mysql_insert_id();
	TreeData[idx][tOwner] = owner;
	TreeData[idx][tX] = x;
	TreeData[idx][tY] = y;
	TreeData[idx][tZ] = z;
	TreeData[idx][tRot] = rot;
	TreeData[idx][tGrown] = 0;
	TreeData[idx][tWateredUntil] = now + TREE_WATER_AMOUNT; // posadzone drzewo jest od razu podlane
	TreeData[idx][tLastUpdate] = now;
	TreeData[idx][tStage] = 0;
	TreeData[idx][tObject] = 0;

	Tree_UpdateObject(idx);
	return idx;
}

// Wywolaj w OnGameModeInit() po ConnectingMySQL().
stock Tree_Load() {
	new row[160], loaded, now = gettime();

	for(new i = 0; i < MAX_TREES; i++) TreeData[i][tUsed] = 0;

	mysql_query("SELECT `ID`, `OwnerID`, `PosX`, `PosY`, `PosZ`, `RotZ`, `Grown`, `WateredUntil`, `LastUpdate` FROM `Plants`");
	mysql_store_result();

	if(mysql_result_stored()) {
		while(mysql_fetch_row(row, "|")) {
			if(loaded >= MAX_TREES) break;

			new id, owner, grown, until, last, Float:x, Float:y, Float:z, Float:rot;

			sscanf(row, "p<|>iiffffiii", id, owner, x, y, z, rot, grown, until, last);

			TreeData[loaded][tUsed] = 1;
			TreeData[loaded][tSQL] = id;
			TreeData[loaded][tOwner] = owner;
			TreeData[loaded][tX] = x;
			TreeData[loaded][tY] = y;
			TreeData[loaded][tZ] = z;
			TreeData[loaded][tRot] = rot;
			TreeData[loaded][tGrown] = grown;
			TreeData[loaded][tWateredUntil] = until;
			TreeData[loaded][tLastUpdate] = last;
			TreeData[loaded][tObject] = 0;

			// UWAGA: w tej petli nie wolno wywolywac zadnych mysql_query() - nowe zapytanie
			// zastepuje wynik, po ktorym iterujemy, i wczytaloby sie tylko pierwsze drzewo.
			loaded++;
		}
	}

	mysql_free_result();

	// dogonienie wzrostu z czasu, gdy serwer / gracz byl offline (dopiero po zwolnieniu wyniku)
	for(new i = 0; i < loaded; i++) {
		Tree_Sync(i, now);
		TreeData[i][tStage] = Tree_CalcStage(i);
		Tree_Save(i);
		Tree_UpdateObject(i);
	}

	printf("[TREES] Wczytano %d drzew.", loaded);
}

// Co minute sprawdza, czy ktores drzewo nie wskoczylo na kolejny etap.
task TreeGrowth[60000]() {
	new now = gettime(), stage, owner, str[128];

	for(new i = 0; i < MAX_TREES; i++) {
		if(!TreeData[i][tUsed]) continue;

		Tree_Sync(i, now);
		stage = Tree_CalcStage(i);

		if(stage != TreeData[i][tStage]) {
			TreeData[i][tStage] = stage;
			Tree_UpdateObject(i);
			Tree_Save(i);

			owner = Tree_FindOwnerOnline(TreeData[i][tOwner]);

			if(owner != INVALID_PLAYER_ID) {
				format(str, sizeof(str), "Drzewa: Twoje drzewo (ID: %d) urosl i jest teraz: %s.", TreeData[i][tSQL], TreeStageNames[stage]);
				SendClientMessage(owner, COLOR_GREEN, str);
			}
		}
	}
}

// ---------------------------------------------------------------------------
// Komendy
// ---------------------------------------------------------------------------
CMD:drzewo(playerid, params[]) {
	new option[16], str[144];

	if(!gPlayerLogged[playerid]) return 1;

	if(sscanf(params, "s[16]", option)) {
		SendClientMessage(playerid, COLOR_GRAD1, "Uzycie: /drzewo [posadz | podlej | lista | zetnij tak]");
		return 1;
	}

	// ---- /drzewo posadz ----
	if(!strcmp(option, "posadz", true)) {
		new Float:x, Float:y, Float:z, Float:a, owner = PlayerInfo[playerid][pID];

		if(IsPlayerInAnyVehicle(playerid) || GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) {
			SendClientMessage(playerid, COLOR_GREY, "Drzewa: Musisz stac na nogach, aby posadzic drzewo.");
			return 1;
		}

		if(GetPlayerInterior(playerid) != 0 || GetPlayerVirtualWorld(playerid) != 0) {
			SendClientMessage(playerid, COLOR_GREY, "Drzewa: Drzewa mozna sadzic tylko na zewnatrz.");
			return 1;
		}

		new limit = Tree_GetLimit(playerid);

		if(Tree_CountOwned(owner) >= limit) {
			format(str, sizeof(str), "Drzewa: Osiagnales limit posadzonych drzew (%d).", limit);
			SendClientMessage(playerid, COLOR_GREY, str);
			return 1;
		}

		#if TREE_PLANT_COST > 0
		if(GetPlayerMoney(playerid) < TREE_PLANT_COST) {
			format(str, sizeof(str), "Drzewa: Sadzonka kosztuje $%d.", TREE_PLANT_COST);
			SendClientMessage(playerid, COLOR_GREY, str);
			return 1;
		}
		#endif

		GetPlayerPos(playerid, x, y, z);
		GetPlayerFacingAngle(playerid, a);

		for(new i = 0; i < MAX_TREES; i++) {
			if(!TreeData[i][tUsed]) continue;

			if(GetPlayerDistanceFromPoint(playerid, TreeData[i][tX], TreeData[i][tY], TreeData[i][tZ]) < TREE_MIN_DISTANCE) {
				SendClientMessage(playerid, COLOR_GREY, "Drzewa: W poblizu rosnie juz inne drzewo.");
				return 1;
			}
		}

		if(Tree_Create(owner, x, y, z - 1.0, a) == -1) {
			SendClientMessage(playerid, COLOR_GREY, "Drzewa: Na serwerze nie ma juz miejsca na nowe drzewa.");
			return 1;
		}

		#if TREE_PLANT_COST > 0
		GivePlayerMoney(playerid, -TREE_PLANT_COST);
		#endif

		ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 0, 0, 0, 0, 0, 1);

		format(str, sizeof(str), "Drzewa: Posadziles drzewo (%d/%d). Pamietaj o regularnym podlewaniu - /drzewo podlej.", Tree_CountOwned(owner), limit);
		SendClientMessage(playerid, COLOR_GREEN, str);
		return 1;
	}

	// ---- /drzewo podlej ----
	if(!strcmp(option, "podlej", true)) {
		new idx = Tree_GetNearest(playerid, TREE_USE_DISTANCE, true), now = gettime(), remain;

		if(idx == -1) {
			SendClientMessage(playerid, COLOR_GREY, "Drzewa: Nie stoisz w poblizu zadnego ze swoich drzew.");
			return 1;
		}

		if(TreeData[idx][tGrown] >= TREE_GROW_TIME) {
			SendClientMessage(playerid, COLOR_GREY, "Drzewa: To drzewo jest juz dojrzale i nie wymaga podlewania.");
			return 1;
		}

		Tree_Sync(idx, now);

		remain = TreeData[idx][tWateredUntil] - now;
		if(remain < 0) remain = 0;

		if(remain > TREE_WATER_AMOUNT) {
			new timeStr[16];
			Tree_FormatTime(remain - TREE_WATER_AMOUNT, timeStr);

			format(str, sizeof(str), "Drzewa: Drzewo jest dobrze podlane. Mozesz podlac je ponownie za okolo %s.", timeStr);
			SendClientMessage(playerid, COLOR_GREY, str);
			return 1;
		}

		TreeData[idx][tWateredUntil] = now + remain + TREE_WATER_AMOUNT;
		Tree_Save(idx);

		ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 0, 0, 0, 0, 0, 1);

		new timeStr[16];
		Tree_FormatTime(TreeData[idx][tWateredUntil] - now, timeStr);

		format(str, sizeof(str), "Drzewa: Podlales drzewo (ID: %d). Bedzie rosnac jeszcze przez %s - takze gdy bedziesz offline.", TreeData[idx][tSQL], timeStr);
		SendClientMessage(playerid, COLOR_GREEN, str);
		return 1;
	}

	// ---- /drzewo lista ----
	if(!strcmp(option, "lista", true)) {
		new list[1024], line[128], now = gettime(), count, waterStr[16], progress[16], Float:dist;

		strcat(list, "ID\tEtap\tPostep\tWoda\tOdleglosc\n");

		for(new i = 0; i < MAX_TREES; i++) {
			if(!TreeData[i][tUsed] || TreeData[i][tOwner] != PlayerInfo[playerid][pID]) continue;

			Tree_Sync(i, now);

			if(TreeData[i][tGrown] >= TREE_GROW_TIME) {
				format(progress, sizeof(progress), "100%%");
				format(waterStr, sizeof(waterStr), "-");
			} else {
				format(progress, sizeof(progress), "%d%%", TreeData[i][tGrown] * 100 / TREE_GROW_TIME);
				Tree_FormatTime(TreeData[i][tWateredUntil] - now, waterStr);
			}

			dist = GetPlayerDistanceFromPoint(playerid, TreeData[i][tX], TreeData[i][tY], TreeData[i][tZ]);

			format(line, sizeof(line), "%d\t%s\t%s\t%s\t%.0fm\n", TreeData[i][tSQL], TreeStageNames[TreeData[i][tStage]], progress, waterStr, dist);
			strcat(list, line);
			count++;
		}

		if(!count) {
			SendClientMessage(playerid, COLOR_GREY, "Drzewa: Nie masz zadnych posadzonych drzew.");
			return 1;
		}

		format(line, sizeof(line), "Twoje drzewa (%d/%d)", count, Tree_GetLimit(playerid));
		osrp_ShowPlayerDialog(playerid, DIALOG_TREES, DIALOG_STYLE_TABLIST_HEADERS, line, list, "Zamknij", "");
		return 1;
	}

	// ---- /drzewo zetnij tak ----
	if(!strcmp(option, "zetnij", true)) {
		new confirm[8];

		if(sscanf(params, "{s[16]}s[8]", confirm) || strcmp(confirm, "tak", true)) {
			SendClientMessage(playerid, COLOR_GRAD1, "Uzycie: /drzewo zetnij tak (zetnie najblizsze Twoje drzewo - nie mozna tego cofnac!)");
			return 1;
		}

		new idx = Tree_GetNearest(playerid, TREE_USE_DISTANCE, true);

		if(idx == -1) {
			SendClientMessage(playerid, COLOR_GREY, "Drzewa: Nie stoisz w poblizu zadnego ze swoich drzew.");
			return 1;
		}

		Tree_Remove(idx);
		SendClientMessage(playerid, COLOR_YELLOW, "Drzewa: Zetnales drzewo. Zwolnilo sie jedno miejsce w Twoim limicie.");
		return 1;
	}

	SendClientMessage(playerid, COLOR_GRAD1, "Uzycie: /drzewo [posadz | podlej | lista | zetnij tak]");
	return 1;
}
