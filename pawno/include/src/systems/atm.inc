/*
	Project: Old School Role Play
	Author: MisterMagik, steeZ
	File name: atm.inc
	Date: 29.03.2026
	Modified: 29.03.2026
	Desc: ATM system.
*/

stock InitATMData() {
	printf("[ATM] Zaczynam ladowac bankomaty...");
	new id = 1;
	new posStr[24];
	queryStr[0] = EOS;

	format(queryStr, sizeof(queryStr), "SELECT `ID`, `AName`, `APos`, `AisWorking`, `AobjectID` FROM `Atms`");
	mysql_query(queryStr);

	mysql_store_result();

	if(mysql_result_stored()) {
		while(mysql_fetch_row(queryStr, "|")) {
			sscanf(queryStr, "p<|>is[24]s[8]ii",
				AtmInfo[id][aID],
				AtmInfo[id][aName],
				posStr,
				AtmInfo[id][aIsWorking],
				AtmInfo[id][aObjectID]
				
			);

			sscanf(posStr, "p<,>ffff", AtmInfo[id][aPos][0], AtmInfo[id][aPos][1], AtmInfo[id][aPos][2], AtmInfo[id][aPos][3]);

			Itter_Add(AtmItter, id);
	
			printf("[ATM] ID: %d, aName: %s[24], aPos: %s[24], aIsWorking: %d, aObjectID: %d", 
					AtmInfo[id][aID],
					AtmInfo[id][aName],
					posStr,
					AtmInfo[id][aIsWorking],
					AtmInfo[id][aObjectID]
					);
			id++;
		}
	printf("[ATM] wczytano %d bankomatow", id);
	mysql_free_result();
	return 1;
}

stock AddAtm(name[24], modelid, Float:PosX, Float:PosY, Float:PosZ, Float:PosA, bool: isWorking) {
	new id = -1;

	mysql_query("SELECT COUNT(`ID`) FROM `Atms`");
	mysql_store_result();

	if(mysql_result_stored()) {
		id = mysql_fetch_int();
		mysql_free_result();
	}

	if(id == -1) {
		return 1;
	}

	if(id + 1 == MAX_ATMS) {
		printf("[ATM] Nie mozna juz stworzyc kolejnego bankomatu.");
		printf("[ATM] Przekroczono max liczbe dozwolonych bankomatow (%d).", MAX_ATMS);
		return 1;
	}

	new posStr[32];
	
	AtmInfo[id][aID] = id+1;
	format(AtmInfo[id][aName], 24, name);
	AtmInfo[id][aPos][0] = PosX;
	AtmInfo[id][aPos][1] = PosY;
	AtmInfo[id][aPos][2] = PosZ;
	AtmInfo[id][aPos][3] = PosA;
	AtmInfo[id][aIsWorking] = isWorking;
	AtmInfo[id][aObjectID] = modelid;
	
	format(posStr, sizeof(posStr), "%f,%f,%f,%f", VehicleInfo[id][vPos][0], VehicleInfo[id][vPos][1], VehicleInfo[id][vPos][2], VehicleInfo[id][vPos][3]);
	
	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "INSERT INTO `Atms` (`ID`, `AName`, `APos`, `AisWorking`, `AobjectID`) VALUES
	('%d', '%s[24]', '%s[32], '%d', '%d');",
	AtmInfo[a][aID],
	AtmInfo[id][aName],
	posStr,
	AtmInfo[id][aIsWorking],
	AtmInfo[id][aObjectID]
);
	mysql_query(queryStr);

	Iter_Add(AtmItter, id);

	printf("[ATM] Dodano nowy bankomat o ID: %d", id + 1);
	return 1;
}

stock RemoveAtm(atmid) {
	if(atmid == -1) {
		return 1;
	}

	if(!Iter_Count(AtmItter)) {
		return 1;
	}

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "DELETE FROM `Atms` WHERE `ID` = '%d'", AtmInfo[atmid][aID]);
	mysql_query(queryStr);

	AtmInfo[atmid][aID] = -1;
	AtmInfo[atmid][aName] = "Brak";
	AtmInfo[atmid][aPos][0] = 0.0;
	AtmInfo[atmid][aPos][1] = 0.0;
	AtmInfo[atmid][aPos][2] = 0.0;
	AtmInfo[atmid][aPos][3] = 0.0;
	AtmInfo[atmid][aIsWorking] = false;
	AtmInfo[atmid][aIsWorking] = -1;
	

	Iter_Remove(AtmItter, atmid);

	printf("[ATM] Usunieto bankomat o ID: %d", atmid + 1);
	return 1;
}

