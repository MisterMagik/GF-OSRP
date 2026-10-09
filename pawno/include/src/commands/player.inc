/*
	Project: GodFather
	Author: MisterMagik, steeZ
	File name: commands/player.inc
	Date: 12.03.2026
	Modified: 12.03.2026
	Desc: Player commands.
*/

CMD:pojazdy(playerid, params[]) {
	new VehCount;
	new title[64];

	mainStr[0] = EOS;
	strcat(mainStr, "{FFFFFF}Pojazd\t\t{FFFFFF}Przebieg\t{FFFFFF}Tablica\t{FFFFFF}Opis");

	foreach(new i : VehItter) {
		if(VehicleInfo[i][vOwnerType] == VEHICLE_OWNER_TYPE_PLAYER) {
			if(VehicleInfo[i][vOwnerID] == PlayerInfo[playerid][pID]) {
				if(VehicleInfo[i][vSpawned]) {
					format(mainStr, sizeof(mainStr), "%s\n{FFC801}%s {FFFFFF}(id: %d)\t%d KM\t%s\t%s", mainStr, VehicleNames[VehicleInfo[i][vModelID] - 400], i, FloatToInt(VehicleInfo[i][vMileage]), VehicleInfo[i][vPlate], VehicleInfo[i][vDesc]);
					VehCount++;
				}
			}
		}
	}

	if(!VehCount) {
		return SendClientMessage(playerid, COLOR_GRAD1, "Nie posiadasz ¿adnych pojazdów.");
	}

	format(title, sizeof(title), "{FFC801}Twoje pojazdy (Limit %d/%d):", VehCount, MAX_PLAYER_VEHS);
	osrp_ShowPlayerDialog(playerid, DIALOG_SHOW_PLAYER_VEHICLES, DIALOG_STYLE_TABLIST_HEADERS, title, mainStr, "Wybierz", "Anuluj");
	return 1;
}

CMD:admin(playerid, params[]) {
	new msg[64];

	if(sscanf(params, "s[64]", msg)) {
		SendClientMessage(playerid, COLOR_GRAD2, "Wpisz: (/ad)min [tekst]");
		return 1;
	}

	mainStr[0] = EOS;

	if(PlayerInfo[playerid][pAdmin] == 1) {
		format(mainStr, sizeof(mainStr), "*%d Moderator %s: %s", PlayerInfo[playerid][pAdmin], accName[playerid], msg);
	} else {
		format(mainStr, sizeof(mainStr), "*%d Admin %s: %s", PlayerInfo[playerid][pAdmin], accName[playerid], msg);
	}

	if(PlayerInfo[playerid][pAdmin] >= 1) {
		SendAdminMessage(COLOR_GREEN, mainStr);
	}

	printf("Admin %s: %s", PlayerInfo[playerid][pName], msg);
	return 1;
}

alias:admin("ad")

CMD:gotocar(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] >= 3) {
		new testcar;

		if(sscanf(params, "i", testcar)) {
			return SendClientMessage(playerid, COLOR_GRAD1, "Wpisz: /gotocar [id pojazdu]");
		}

		if(!VehicleInfo[testcar][vSpawned]) {
			return SendClientMessage(playerid, COLOR_GRAD1, "Podany pojazd nie istnieje.");
		}

		new Float:cwx2,Float:cwy2,Float:cwz2;

		GetVehiclePos(testcar, cwx2, cwy2, cwz2);

		if(GetPlayerState(playerid) == 2) {
			new tmpcar = GetPlayerVehicleID(playerid);

			SetVehiclePos(tmpcar, cwx2, cwy2, cwz2);
			TelePos[playerid][0] = 0.0;TelePos[playerid][1] = 0.0;
		} else {
			SetPlayerPos(playerid, cwx2, cwy2, cwz2);
		}

		SendClientMessage(playerid, COLOR_GRAD1, "Zosta³eœ przeteleportowany.");
		SetPlayerInterior(playerid,0);
	} else {
		SendClientMessage(playerid, COLOR_GRAD1, "Nie jesteœ upowa¿niony do u¿ycia tej komendy.");
	}
	return 1;
}

CMD:name(playerid, params[]) {
	GetPlayerName(playerid, PlayerInfo[playerid][pName], 24);
	SetPlayerName(playerid, accName[playerid]);
	return 1;
}

CMD:relog(playerid, params[]) {
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) {
		return 1;
	}

	SendClientMessage(playerid, COLOR_GREY, "Zostaniesz wylogowany z tej postaci za 10 sekund.");

	SavePlayerData(playerid);
	SetTimerEx("RelogCharacter", 10000, false, "i", playerid);
	return 1;
}

CMD:pasy(playerid, params[]) {
	
	return 1;
}

CMD:zegarek(playerid, params[]) {
	new mtext[20];
	new year, month,day;

	getdate(year, month, day);

	if(month == 1) { mtext = "Stycznia"; }
	else if(month == 2) { mtext = "Lutego"; }
	else if(month == 3) { mtext = "Marca"; }
	else if(month == 4) { mtext = "Kwietnia"; }
	else if(month == 5) { mtext = "Maja"; }
	else if(month == 6) { mtext = "Czerwca"; }
	else if(month == 7) { mtext = "Lipca"; }
	else if(month == 8) { mtext = "Sierpnia"; }
	else if(month == 9) { mtext = "Wrzesnia"; }
	else if(month == 10) { mtext = "Pazdziernika"; }
	else if(month == 11) { mtext = "Listopada"; }
	else if(month == 12) { mtext = "Grudnia"; }

	new hour, minuite, second;

	gettime(hour,minuite,second);

	FixHour(hour);
	hour = shifthour;
	mainStr[0] = EOS;

	if(minuite < 10) {
		format(mainStr, sizeof(mainStr), "~y~%d %s~n~~g~|~w~%d:0%d~g~|", day, mtext, hour, minuite);
	} else {
		format(mainStr, sizeof(mainStr), "~y~%d %s~n~~g~|~w~%d:%d~g~|", day, mtext, hour, minuite);
	}

	ApplyAnimation(playerid, "PLAYIDLES", "TIME", 4.1, 0, 0, 0, 0, 0);
	GameTextForPlayer(playerid, mainStr, 5000, 1);

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "* %s patrzy na swój zegarek.", PlayerInfo[playerid][pName]);
	ProxDetector(30.0, playerid, mainStr, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
	return 1;
}

alias:zegarek("czas")

CMD:stats(playerid, params[]) {
	if(!gPlayerLogged[playerid]) {
		return SendClientMessage(playerid, COLOR_GRAD1, "Nie jesteœ zalogowany.");
	}

	ShowStats(playerid,playerid);
	return 1;
}

CMD:b(playerid, params[]) {
	if(!gPlayerLogged[playerid]) {
		return SendClientMessage(playerid, COLOR_GRAD1, "Nie jesteœ zalogowany.");
	}

	new result[64];

	if(sscanf(params, "s[64]", result)) {
		return SendClientMessage(playerid, COLOR_GRAD2, "Wpisz: /b [czat ooc]");
	}

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "%s pisze OOC: (( %s ))", PlayerInfo[playerid][pName], result);
	ProxDetector(20.0, playerid, mainStr,COLOR_FADE1,COLOR_FADE2,COLOR_FADE3,COLOR_FADE4,COLOR_FADE5);
	printf("%s", mainStr);
	return 1;
}

CMD:krzyk(playerid, params[]) {
	if(!gPlayerLogged[playerid]) {
		return SendClientMessage(playerid, COLOR_GREY, "Nie jesteœ zalogowany.");
	}

	new result[64];

	if(sscanf(params, "s[64]", result)) {
		return SendClientMessage(playerid, COLOR_GRAD2, "Wpisz: (/s)krzyk [wiadomoœæ]");
	}

	format(mainStr, sizeof(mainStr), "%s krzyczy: %s!", PlayerInfo[playerid][pName], result);
	ProxDetector(30.0, playerid, mainStr,COLOR_WHITE,COLOR_WHITE,COLOR_WHITE,COLOR_FADE1,COLOR_FADE2);
	printf("%s", mainStr);
	return 1;
}

alias:krzyk("s")

CMD:me(playerid, params[]) {
	if(!gPlayerLogged[playerid]) {
		return SendClientMessage(playerid, COLOR_GRAD1, "Nie jesteœ zalogowany.");
	}

	new result[64];

	if(sscanf(params, "s[64]", result)) {
		return SendClientMessage(playerid, COLOR_GRAD2, "Wpisz: /me [akcja]");
	}

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "* %s %s", PlayerInfo[playerid][pName], result);
	ProxDetector(30.0, playerid, mainStr, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);

	printf("%s", mainStr);
	return 1;
}

alias:me("ja")

CMD:do(playerid, params[]) {
	if(!gPlayerLogged[playerid]) {
		return SendClientMessage(playerid, COLOR_GRAD1, "Nie jesteœ zalogowany.");
	}

	new result[64];

	if(sscanf(params, "s[64]", result)) {
		return SendClientMessage(playerid, COLOR_GRAD2, "Wpisz: /do [akcja]");
	}

	mainStr[0] = EOS;
	format(mainStr, sizeof(mainStr), "* %s (( %s ))", result, PlayerInfo[playerid][pName]);
	ProxDetector(30.0, playerid, mainStr, COLOR_LIGHTBLUE,COLOR_LIGHTBLUE,COLOR_LIGHTBLUE,COLOR_LIGHTBLUE,COLOR_LIGHTBLUE);

	printf("%s", mainStr);
	return 1;
}

CMD:megafon(playerid, params[]) {
	new tmpcar = GetPlayerVehicleID(playerid);
	new result[64];

	if(sscanf(params, "s[64]", result)) {
		return SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: (/m)egaphone [megaphone chat]");
	}

	if(gTeam[playerid] == 2 || IsACop(playerid)) {
		if(!IsACopCar(tmpcar)) {
			return SendClientMessage(playerid, COLOR_GRAD2, "   You are not in a Police Vehicle !");
		}

		if(PlayerInfo[playerid][pMember] == 1||PlayerInfo[playerid][pLeader] == 1) {
			format(mainStr, sizeof(mainStr), "[Oficer %s:o< %s]", PlayerInfo[playerid][pName], result);
			ProxDetector(60.0, playerid, mainStr,COLOR_YELLOW,COLOR_YELLOW,COLOR_YELLOW,COLOR_YELLOW,COLOR_YELLOW);
		} else if(PlayerInfo[playerid][pMember] == 2||PlayerInfo[playerid][pLeader] == 2) {
			format(mainStr, sizeof(mainStr), "[Agent %s:o< %s]", PlayerInfo[playerid][pName], result);
			ProxDetector(60.0, playerid, mainStr,COLOR_YELLOW,COLOR_YELLOW,COLOR_YELLOW,COLOR_YELLOW,COLOR_YELLOW);
		} else if(PlayerInfo[playerid][pMember] == 3||PlayerInfo[playerid][pLeader] == 3) {
			format(mainStr, sizeof(mainStr), "[Soldier %s:o< %s]", PlayerInfo[playerid][pName], result);
			ProxDetector(60.0, playerid, mainStr,COLOR_YELLOW,COLOR_YELLOW,COLOR_YELLOW,COLOR_YELLOW,COLOR_YELLOW);
		}
		printf("%s", mainStr);
	} else {
		SendClientMessage(playerid, COLOR_GRAD2, "   You are not part of a Team !");
	}
	return 1;
}

alias:megaphone("m")

CMD:zamek(playerid, params[]) {
	if(GetClosestVehicle(playerid) != INVALID_VEHICLE_ID) {
		new vehicleid = GetClosestVehicle(playerid);

		if(!IsVehicleOwner(playerid, vehicleid)) {
			return SendClientMessage(playerid, COLOR_GRAD1, "Nie masz klucza do tego pojazdu.");
		}

		if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
			ApplyAnimation(playerid, "INT_HOUSE", "wash_up", 4.1, 0, 0, 0, 0, 0);
		}

		if(VehicleInfo[vehicleid][vLocked]) {
			VehicleInfo[vehicleid][vLocked] = false;
			GameTextForPlayer(playerid, "~n~~n~~n~~w~Pojazd ~g~otwarty", 3000, 3);

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "* %s przekrêca kluczyk i otwiera pojazd.", PlayerInfo[playerid][pName]);
			ProxDetector(30.0, playerid, mainStr, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
		} else {
			VehicleInfo[vehicleid][vLocked] = true;
			GameTextForPlayer(playerid, "~n~~n~~n~~w~Pojazd ~r~zamkniety", 3000, 3);

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "* %s przekrêca kluczyk i zamyka pojazd.", PlayerInfo[playerid][pName]);
			ProxDetector(30.0, playerid, mainStr, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
		}

		SaveVehicleData(vehicleid, VEHICLE_SAVE_LOCKED);

		foreach(new i : Player) {
			SetVehicleParamsForPlayer(vehicleid, i, 0, VehicleInfo[vehicleid][vLocked]);
		}
	} else {
		SendClientMessage(playerid, COLOR_GRAD1, "Nie ma w pobli¿u ¿adnego pojazdu.");
	}
	return 1;
}

CMD:dodajpojazd(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] < 1) {
		return SendClientMessage(playerid, COLOR_GRAD1, "Nie jesteœ upowa¿niony do u¿ycia tej komendy.");
	}

	new str[5000];

	strcat(str, "{FFFFFF}Model pojazdu\t{FFFFFF}ID pojazdu\n");

	for(new i = 0; i < sizeof(VehicleNames); i++) {
		format(str, sizeof(str), "%s\n{FFFFFF}%s\t%d", str, VehicleNames[i], i + 400);
	}

	osrp_ShowPlayerDialog(playerid, DIALOG_ADMIN_VEHICLE, DIALOG_STYLE_TABLIST_HEADERS, "Wybierz model pojazdu:", str, "Dalej", "Anuluj");
	return 1;
}

CMD:usunpojazd(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] < 1) {
		return SendClientMessage(playerid, COLOR_GRAD1, "Nie jesteœ upowa¿niony do u¿ycia tej komendy.");
	}

	new vehicleid;

	if(sscanf(params, "i", vehicleid)) {
		return SendClientMessage(playerid, COLOR_GRAD1, "Wpisz: /usunpojazd [ID pojazdu]");
	}

	if(!VehicleInfo[vehicleid][vSpawned]) {
		return SendClientMessage(playerid, COLOR_GRAD1, "Podany pojazd nie istnieje.");
	}

	RemoveVehicle(vehicleid);
	return 1;
}

CMD:dajtablice(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] < 1) {
		return SendClientMessage(playerid, COLOR_GRAD1, "Nie jesteœ upowa¿niony do u¿ycia tej komendy.");
	}

	new vehicleid;

	if(sscanf(params, "i", vehicleid)) {
		return SendClientMessage(playerid, COLOR_GRAD1, "Wpisz: /dajtablice [ID pojazdu]");
	}

	if(!VehicleInfo[vehicleid][vSpawned]) {
		return SendClientMessage(playerid, COLOR_GRAD1, "Podany pojazd nie istnieje.");
	}

	format(VehicleInfo[vehicleid][vPlate], 32, "%s", GenerateNewNumberPlate());
	RespawnVehicle(vehicleid);
	return 1;
}
