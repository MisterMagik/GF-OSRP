/*
	Project: GodFather
	Author: MisterMagik, steeZ
	File name: vehicle.inc
	Date: 12.03.2026
	Modified: 12.03.2026
	Desc: Vehicle system.
	
	Wszystko z pojazdami.
*/

stock InitVehicleData() {
	printf("[POJAZD] Zaczynam ladowac pojazdy...");

	new id;
	new colorStr[16], posStr[32], windowStr[16], componentStr[82];

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT `ID`, `OwnerID`, `OwnerType`, `BizID`, `AccessID`, `RentID`, `ModelID`, `EngineType`, `Color`, `Pos`, `Fuel`, `Locked`, `Engine`, `EngineHp`, `Spawned`, `LightsOn`, `Window`, `Accessories`, `Panels`, `Doors`, `Lights`, `Tires`, `Vw`, `Int`, `Paintjob`, `Nitro`, `Components`, `Repair`, `Mileage`, `Block`, `Plate`, `Desc` FROM `Vehicles`");
	mysql_query(queryStr);

	mysql_store_result();

	if(mysql_result_stored()) {
		while(mysql_fetch_row(queryStr, "|")) {
			id++;

			sscanf(queryStr, "p<|>iiiis[32]iiis[8]s[64]fiifiis[16]iiiiiiiifs[82]ffis[32]s[128]",
				VehicleInfo[id][vID],
				VehicleInfo[id][vOwnerID],
				VehicleInfo[id][vOwnerType],
				VehicleInfo[id][vBizID],
				VehicleInfo[id][vAccessID],
				VehicleInfo[id][vRentID],
				VehicleInfo[id][vModelID],
				VehicleInfo[id][vEngineType],
				colorStr,
				posStr,
				VehicleInfo[id][vFuel],
				VehicleInfo[id][vLocked],
				VehicleInfo[id][vEngine],
				VehicleInfo[id][vEngineHp],
				VehicleInfo[id][vSpawned],
				VehicleInfo[id][vLightsOn],
				windowStr,
				VehicleInfo[id][vAccessories],
				VehicleInfo[id][vPanels],
				VehicleInfo[id][vDoors],
				VehicleInfo[id][vLights],
				VehicleInfo[id][vTires],
				VehicleInfo[id][vVw],
				VehicleInfo[id][vInt],
				VehicleInfo[id][vPaintjob],
				VehicleInfo[id][vNitro],
				componentStr,
				VehicleInfo[id][vRepair],
				VehicleInfo[id][vMileage],
				VehicleInfo[id][vBlock],
				VehicleInfo[id][vPlate],
				VehicleInfo[id][vDesc]
			);

			VehicleInfo[id][vDriverID] = INVALID_PLAYER_ID;
			VehicleInfo[id][v3DDesc] = Text3D:INVALID_STREAMER_ID;

			sscanf(colorStr, "p<,>ii", VehicleInfo[id][vColor][0], VehicleInfo[id][vColor][1]);
			sscanf(posStr, "p<,>ffff", VehicleInfo[id][vPos][0], VehicleInfo[id][vPos][1], VehicleInfo[id][vPos][2], VehicleInfo[id][vPos][3]);
			sscanf(windowStr, "p<,>iiii", VehicleInfo[id][vWindow][0], VehicleInfo[id][vWindow][1], VehicleInfo[id][vWindow][2], VehicleInfo[id][vWindow][3]);

			sscanf(componentStr, "p<,>iiiiiiiiiiiiii",
				VehicleInfo[id][vComponents][0],
				VehicleInfo[id][vComponents][1],
				VehicleInfo[id][vComponents][2],
				VehicleInfo[id][vComponents][3],
				VehicleInfo[id][vComponents][4],
				VehicleInfo[id][vComponents][5],
				VehicleInfo[id][vComponents][6],
				VehicleInfo[id][vComponents][7],
				VehicleInfo[id][vComponents][8],
				VehicleInfo[id][vComponents][9],
				VehicleInfo[id][vComponents][10],
				VehicleInfo[id][vComponents][11],
				VehicleInfo[id][vComponents][12],
				VehicleInfo[id][vComponents][13]
			);

			Iter_Add(VehItter, id);

			if(VehicleInfo[id][vSpawned]) {
				SpawnVehicle(id);
			}

			printf("[POJAZD] ID: %d, OwnerID: %d, OwnerType: %d, BizID: %d, AccessID: %s, RentID: %d, ModelID: %d, EngineType: %d, colorStr: %s, posStr: %s, Fuel: %0.1f, Lock: %d, Engine: %d, EngineHp: %0.1f, Spawned: %d, LightsOn: %d, Window: %s, Accessories: %d, Panels: %d, Doors: %d, Lights: %d, Tires: %d, Vw: %d, Int: %d, Paintjob: %d, Nitro: %0.1f, Components: %s, Repair: %0.1f, Mileage: %0.1f, Block: %d, Plate: %s, Desc: %s\n",
				VehicleInfo[id][vID],
				VehicleInfo[id][vOwnerID],
				VehicleInfo[id][vOwnerType],
				VehicleInfo[id][vBizID],
				VehicleInfo[id][vAccessID],
				VehicleInfo[id][vRentID],
				VehicleInfo[id][vModelID],
				VehicleInfo[id][vEngineType],
				colorStr,
				posStr,
				VehicleInfo[id][vFuel],
				VehicleInfo[id][vLocked],
				VehicleInfo[id][vEngine],
				VehicleInfo[id][vEngineHp],
				VehicleInfo[id][vSpawned],
				VehicleInfo[id][vLightsOn],
				windowStr,
				VehicleInfo[id][vAccessories],
				VehicleInfo[id][vPanels],
				VehicleInfo[id][vDoors],
				VehicleInfo[id][vLights],
				VehicleInfo[id][vTires],
				VehicleInfo[id][vVw],
				VehicleInfo[id][vInt],
				VehicleInfo[id][vPaintjob],
				VehicleInfo[id][vNitro],
				componentStr,
				VehicleInfo[id][vRepair],
				VehicleInfo[id][vMileage],
				VehicleInfo[id][vBlock],
				VehicleInfo[id][vDesc],
				VehicleInfo[id][vPlate]
				
			);
		}
	}

	printf("[POJAZD] Wczytano %d pojazdow.", id);

	mysql_free_result();
	return 1;
}

stock AddVehicle(ownerid, ownertype, modelid, enginetype, color1, color2, salon, Float:PosX, Float:PosY, Float:PosZ, Float:PosA) {
	new id = GetVehicleFreeIndex();

	if(id == INVALID_VEHICLE_ID) {
		return 1;
	}

	if(id == MAX_VEHICLES) {
		printf("[POJAZD] Nie mozna juz stworzyc kolejnego pojazdu.");
		printf("[POJAZD] Przekroczono limit dozwolonych pojazdow w grze (%d).", MAX_VEHICLES);
		return 1;
	}

	new colorStr[16], posStr[64];

	VehicleInfo[id][vID] = id;
	VehicleInfo[id][vOwnerID] = ownerid;
	VehicleInfo[id][vOwnerType] = ownertype;
	VehicleInfo[id][vBizID] = 0;
	format(VehicleInfo[id][vAccessID], 32, "Brak");
	VehicleInfo[id][vRentID] = 0;
	VehicleInfo[id][vModelID] = modelid;
	VehicleInfo[id][vEngineType] = enginetype;
	VehicleInfo[id][vColor][0] = color1;
	VehicleInfo[id][vColor][1] = color2;
	VehicleInfo[id][vPos][0] = PosX;
	VehicleInfo[id][vPos][1] = PosY;
	VehicleInfo[id][vPos][2] = PosZ;
	VehicleInfo[id][vPos][3] = PosA;
	VehicleInfo[id][vFuel] = 60.0;
	VehicleInfo[id][vLocked] = false;
	VehicleInfo[id][vEngine] = false;
	VehicleInfo[id][vEngineHp] = 2000.0;
	VehicleInfo[id][vLightsOn] = false;
	VehicleInfo[id][vAccessories] = 0;
	VehicleInfo[id][vPanels] = 0;
	VehicleInfo[id][vDoors] = 0;
	VehicleInfo[id][vLights] = 0;
	VehicleInfo[id][vTires] = 0;
	VehicleInfo[id][vVw] = 0;
	VehicleInfo[id][vInt] = 0;
	VehicleInfo[id][vPaintjob] = -1;
	VehicleInfo[id][vNitro] = -1.0;
	VehicleInfo[id][vRepair] = 0.0;
	VehicleInfo[id][vMileage] = 0.0;
	VehicleInfo[id][vBlock] = false;
	VehicleInfo[id][vDriverID] = INVALID_PLAYER_ID;
	VehicleInfo[id][v3DDesc] = Text3D:INVALID_STREAMER_ID;
	format(VehicleInfo[id][vPlate], 32, "Brak");
	format(VehicleInfo[id][vDesc], 128, "Brak");

	if(salon) {
		VehicleInfo[id][vSpawned] = true;

		SpawnVehicle(id);
	}

	for(new i = 0; i < 4; i++) {
		VehicleInfo[id][vWindow][i] = -1;
	}

	for(new i = 0; i < 14; i++) {
		VehicleInfo[id][vComponents][i] = -1;
	}

	format(colorStr, sizeof(colorStr), "%d,%d", VehicleInfo[id][vColor][0], VehicleInfo[id][vColor][1]);
	format(posStr, sizeof(posStr), "%f,%f,%f,%f", VehicleInfo[id][vPos][0], VehicleInfo[id][vPos][1], VehicleInfo[id][vPos][2], VehicleInfo[id][vPos][3]);

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "INSERT INTO `Vehicles` (`OwnerID`, `OwnerType`, `ModelID`, `EngineType`, `Color`, `Pos`, `Fuel`, `EngineHp`, `Spawned`) VALUES ('%d', '%d', '%d', '%d', '%s', '%s', '%f', '%f', '%d')",
		VehicleInfo[id][vOwnerID],
		VehicleInfo[id][vOwnerType],
		VehicleInfo[id][vModelID],
		VehicleInfo[id][vEngineType],
		colorStr,
		posStr,
		VehicleInfo[id][vFuel],
		VehicleInfo[id][vEngineHp],
		VehicleInfo[id][vSpawned]
	);
	mysql_query(queryStr);

	Iter_Add(VehItter, id);

	printf("[POJAZD] Dodano nowy pojazd o ID: %d", id);
	return 1;
}

stock RemoveVehicle(vehicleid) {
	if(vehicleid == INVALID_VEHICLE_ID) {
		return 1;
	}

	if(!Iter_Count(VehItter)) {
		return 1;
	}

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "DELETE FROM `Vehicles` WHERE `ID` = '%d'", VehicleInfo[vehicleid][vID]);
	mysql_query(queryStr);

	if(VehicleInfo[vehicleid][vSpawned]) {
		ClearVehiclePlayers(vehicleid);
		DestroyDynamic3DTextLabel(VehicleInfo[vehicleid][v3DDesc]);
		DestroyVehicle(vehicleid);
	}

	VehicleInfo[vehicleid][vID] = 0;
	VehicleInfo[vehicleid][vOwnerID] = VEHICLE_OWNER_NONE;
	VehicleInfo[vehicleid][vOwnerType] = VEHICLE_OWNER_TYPE_NONE;
	VehicleInfo[vehicleid][vBizID] = 0;
	format(VehicleInfo[vehicleid][vAccessID], 32, "Brak");
	VehicleInfo[vehicleid][vRentID] = 0;
	VehicleInfo[vehicleid][vModelID] = 0;
	VehicleInfo[vehicleid][vEngineType] = -1;
	VehicleInfo[vehicleid][vColor][0] = 0;
	VehicleInfo[vehicleid][vColor][1] = 0;
	VehicleInfo[vehicleid][vPos][0] = 0.0;
	VehicleInfo[vehicleid][vPos][1] = 0.0;
	VehicleInfo[vehicleid][vPos][2] = 0.0;
	VehicleInfo[vehicleid][vPos][3] = 0.0;
	VehicleInfo[vehicleid][vFuel] = 0.0;
	VehicleInfo[vehicleid][vLocked] = false;
	VehicleInfo[vehicleid][vEngine] = false;
	VehicleInfo[vehicleid][vEngineHp] = 0.0;
	VehicleInfo[vehicleid][vSpawned] = false;
	VehicleInfo[vehicleid][vLightsOn] = false;
	VehicleInfo[vehicleid][vAccessories] = 0;
	VehicleInfo[vehicleid][vPanels] = 0;
	VehicleInfo[vehicleid][vDoors] = 0;
	VehicleInfo[vehicleid][vLights] = 0;
	VehicleInfo[vehicleid][vTires] = 0;
	VehicleInfo[vehicleid][vVw] = 0;
	VehicleInfo[vehicleid][vInt] = 0;
	VehicleInfo[vehicleid][vPaintjob] = -1;
	VehicleInfo[vehicleid][vNitro] = -1.0;
	VehicleInfo[vehicleid][vRepair] = 0.0;
	VehicleInfo[vehicleid][vMileage] = 0.0;
	VehicleInfo[vehicleid][vBlock] = false;
	VehicleInfo[vehicleid][vDriverID] = INVALID_PLAYER_ID;
	format(VehicleInfo[vehicleid][vPlate], 32, "Brak");
	format(VehicleInfo[vehicleid][vDesc], 128, "Brak");

	for(new i = 0; i < 4; i++) {
		VehicleInfo[vehicleid][vWindow][i] = -1;
	}

	for(new i = 0; i < 14; i++) {
		VehicleInfo[vehicleid][vComponents][i] = -1;
	}

	Iter_Remove(VehItter, vehicleid);

	printf("[POJAZD] Usunieto pojazd o ID: %d", vehicleid);
	return 1;
}

stock SaveVehicleData(vehicleid, option) {
	if(vehicleid == INVALID_VEHICLE_ID) {
		return 1;
	}

	new QueryTmp[128], Fields;

	queryStr[0] = EOS;
	strcat(queryStr, "UPDATE `Vehicles` SET ");

	if(option & VEHICLE_SAVE_POS) {
		if(!VehicleInfo[vehicleid][vSpawned]) {
			return 1;
		}

		new posStr[64];

		GetVehiclePos(vehicleid, VehicleInfo[vehicleid][vPos][0], VehicleInfo[vehicleid][vPos][1], VehicleInfo[vehicleid][vPos][2]);
		GetVehicleZAngle(vehicleid, VehicleInfo[vehicleid][vPos][3]);

		format(posStr, sizeof(posStr), "%f,%f,%f,%f", VehicleInfo[vehicleid][vPos][0], VehicleInfo[vehicleid][vPos][1], VehicleInfo[vehicleid][vPos][2], VehicleInfo[vehicleid][vPos][3]);
		format(QueryTmp, sizeof(QueryTmp), "`Pos` = '%s'", posStr);

		if(Fields++) {
			strcat(queryStr, ", ");
		}

		strcat(queryStr, QueryTmp);
	}

	if(option & VEHICLE_SAVE_ENGINE) {
		if(!VehicleInfo[vehicleid][vSpawned]) {
			return 1;
		}

		GetVehicleHealth(vehicleid, VehicleInfo[vehicleid][vEngineHp]);
		format(QueryTmp, sizeof(QueryTmp), "`EngineType` = '%d', `Engine` = '%d', `EngineHp` = '%f'", VehicleInfo[vehicleid][vEngineType], VehicleInfo[vehicleid][vEngine], VehicleInfo[vehicleid][vEngineHp]);

		if(Fields++) {
			strcat(queryStr, ", ");
		}

		strcat(queryStr, QueryTmp);
	}

	if(option & VEHICLE_SAVE_LOCKED) {
		format(QueryTmp, sizeof(QueryTmp), "`Locked` = '%d'", VehicleInfo[vehicleid][vLocked]);

		if(Fields++) {
			strcat(queryStr, ", ");
		}

		strcat(queryStr, QueryTmp);
	}

	if(option & VEHICLE_SAVE_MILEAGE) {
		format(QueryTmp, sizeof(QueryTmp), "`Fuel` = '%f', `Mileage` = '%f'", VehicleInfo[vehicleid][vFuel], VehicleInfo[vehicleid][vMileage]);

		if(Fields++) {
			strcat(queryStr, ", ");
		}

		strcat(queryStr, QueryTmp);
	}

	if(option & VEHICLE_SAVE_VISUAL) {
		if(!VehicleInfo[vehicleid][vSpawned]) {
			return 1;
		}

		format(QueryTmp, sizeof(QueryTmp), "`Panels` = '%d', `Doors` = '%d', `Lights` = '%d', `Tires` = '%d'", VehicleInfo[vehicleid][vPanels], VehicleInfo[vehicleid][vDoors], VehicleInfo[vehicleid][vLights], VehicleInfo[vehicleid][vTires]);

		if(Fields++) {
			strcat(queryStr, ", ");
		}

		strcat(queryStr, QueryTmp);
	}

	if(!Fields) {
		return 1;
	}

	format(QueryTmp, sizeof(QueryTmp), " WHERE `ID` = '%d'", VehicleInfo[vehicleid][vID]);
	strcat(queryStr, QueryTmp);
	mysql_query(queryStr);
	return 1;
}

stock SpawnVehicle(vehicleid) {
	if(vehicleid == INVALID_VEHICLE_ID) {
		return 1;
	}

	if(!VehicleInfo[vehicleid][vSpawned]) {
		return 1;
	}

	CreateVehicle(VehicleInfo[vehicleid][vModelID], VehicleInfo[vehicleid][vPos][0], VehicleInfo[vehicleid][vPos][1], VehicleInfo[vehicleid][vPos][2], VehicleInfo[vehicleid][vPos][3], VehicleInfo[vehicleid][vColor][0], VehicleInfo[vehicleid][vColor][1], -1);

	if(!strcmp(VehicleInfo[vehicleid][vDesc], "Brak", true)) {
		format(VehicleInfo[vehicleid][vDesc], 128, " ");
	} else {
		VehicleInfo[vehicleid][v3DDesc] = CreateDynamic3DTextLabel(VehicleInfo[vehicleid][vDesc], COLOR_WHITE, 0.0, 0.0, 0.1, 20.0, INVALID_PLAYER_ID, vehicleid, 0, 0, 0, -1, 20.0, -1, 0);
	}

	VehicleInfo[vehicleid][v3DDesc] = CreateDynamic3DTextLabel(VehicleInfo[vehicleid][vDesc], COLOR_WHITE, 0.0, 0.0, 0.1, 20.0, INVALID_PLAYER_ID, vehicleid, 0, 0, 0, -1, 20.0, -1, 0);
	if(strcmp(VehicleInfo[vehicleid][vPlate], "Brak") == 0) {
 		// SetVehicleNumberPlate(vehicleid, "");
	} 
	SetVehicleNumberPlate(vehicleid, VehicleInfo[vehicleid][vPlate]);
	if(IsABicycle(VehicleInfo[vehicleid][vModelID])) {
		SetVehicleParamsEx(vehicleid, 1, 0, 0, 0, 0, 0, 0);
	} else {
		new Engine, Lights, Alarm, Doors, Bonnet, Boot, Objective;

		GetVehicleParamsEx(vehicleid, Engine, Lights, Alarm, Doors, Bonnet, Boot, Objective);
		SetVehicleParamsEx(vehicleid, VehicleInfo[vehicleid][vEngine], VehicleInfo[vehicleid][vLightsOn], Alarm, VehicleInfo[vehicleid][vLocked], Bonnet, Boot, Objective);
	}

	SetVehicleVirtualWorld(vehicleid, VehicleInfo[vehicleid][vVw]);
	LinkVehicleToInterior(vehicleid, VehicleInfo[vehicleid][vInt]);

	UpdateVehicleDamageStatus(vehicleid, VehicleInfo[vehicleid][vPanels], VehicleInfo[vehicleid][vDoors], VehicleInfo[vehicleid][vLights], VehicleInfo[vehicleid][vTires]);

	if(VehicleInfo[vehicleid][vNitro] != -1.0) {
		AddVehicleComponent(vehicleid, 1010);
	}
	return 1;
}

stock UnSpawnVehicle(vehicleid) {
	if(vehicleid == INVALID_VEHICLE_ID) {
		return 1;
	}

	if(VehicleInfo[vehicleid][vSpawned]) {
		return 1;
	}

	SaveVehicleData(vehicleid, VEHICLE_SAVE_POS | VEHICLE_SAVE_ENGINE | VEHICLE_SAVE_MILEAGE);

	DestroyVehicle(vehicleid);
	DestroyDynamic3DTextLabel(VehicleInfo[vehicleid][v3DDesc]);

	VehicleInfo[vehicleid][vSpawned] = false;
	VehicleInfo[vehicleid][vDriverID] = INVALID_PLAYER_ID;
	return 1;
}

Callback VehicleLightsOn(vehicleid) {
	if(VehicleInfo[vehicleid][vDriverID] == INVALID_PLAYER_ID) {
		return 1;
	}

	if(VehicleInfo[vehicleid][vLightsOn]) {
		return 1;
	}

	new Engine, Lights, Alarm, Doors, Bonnet, Boot, Objective;

	VehicleInfo[vehicleid][vLightsOn] = true;

	GetVehicleParamsEx(vehicleid, Engine, Lights, Alarm, Doors, Bonnet, Boot, Objective);
	SetVehicleParamsEx(vehicleid, Engine, VehicleInfo[vehicleid][vLightsOn], Alarm, Doors, Bonnet, Boot, Objective);
	return 1;
}

Callback VehicleLightsOff(vehicleid) {
	if(VehicleInfo[vehicleid][vDriverID] == INVALID_PLAYER_ID) {
		return 1;
	}

	if(!VehicleInfo[vehicleid][vLightsOn]) {
		return 1;
	}

	new Engine, Lights, Alarm, Doors, Bonnet, Boot, Objective;

	VehicleInfo[vehicleid][vLightsOn] = false;

	GetVehicleParamsEx(vehicleid, Engine, Lights, Alarm, Doors, Bonnet, Boot, Objective);
	SetVehicleParamsEx(vehicleid, Engine, VehicleInfo[vehicleid][vLightsOn], Alarm, Doors, Bonnet, Boot, Objective);
	return 1;
}

Callback VehicleEngineStarting(vehicleid) {
	if(vehicleid == INVALID_VEHICLE_ID) {
		return 1;
	}

	new driverid = VehicleInfo[vehicleid][vDriverID];

	if(driverid == INVALID_PLAYER_ID) {
		return 1;
	}

	if(!IsVehicleOwner(driverid, vehicleid)) {
		return SendClientMessage(driverid, COLOR_GRAD1, "Nie masz klucza do tego pojazdu.");
	}

	if(VehAnim[driverid]) {
		return 1;
	}

	if(IsABike(vehicleid)) {
		ApplyAnimation(driverid, "CARRY", "crry_prtial", 4.0, 0, 0, 0, 0, 0, 0);
	} else {
		ApplyAnimation(driverid, "PED", "CAR_tune_radio", 4.1, 0, 0, 0, 0, 0);
	}

	PlayerPlaySound(driverid, 1084, 0.0, 0.0, 0.0);

	if(VehicleInfo[vehicleid][vEngine]) {
		new Engine, Lights, Alarm, Doors, Bonnet, Boot, Objective;

		VehicleInfo[vehicleid][vEngine] = false;

		GetVehicleParamsEx(vehicleid, Engine, Lights, Alarm, Doors, Bonnet, Boot, Objective);
		SetVehicleParamsEx(vehicleid, VehicleInfo[vehicleid][vEngine], Lights, Alarm, Doors, Bonnet, Boot, Objective);
		return SendClientMessage(driverid, COLOR_YELLOW, "Wy  czy e  silnik.");
	}

	if(VehicleInfo[vehicleid][vEngineHp] <= 300.0) {
		return SendClientMessage(driverid, COLOR_YELLOW, "Ten pojazd jest zepsuty, nie mo na go uruchomi . Aby go naprawi  musisz wezwa  mechanika.");
	}

	if(VehicleInfo[vehicleid][vFuel] <= 0.0) {
		return SendClientMessage(driverid, COLOR_YELLOW, "Nie mo esz odpali  silnika, poniewa  nie ma paliwa w tym poje dzie.");
	}

	VehAnim[driverid] = true;

	SendClientMessage(driverid, COLOR_YELLOW, "Pr bujesz odpali  silnik...");
	SetTimerEx("VehicleEngineOn", 2500, false, "i", vehicleid);
	return 1;
}

Callback VehicleEngineOn(vehicleid) {
	if(vehicleid == INVALID_VEHICLE_ID) {
		return 1;
	}

	if(VehicleInfo[vehicleid][vDriverID] == INVALID_PLAYER_ID) {
		return 1;
	}

	new driverid = VehicleInfo[vehicleid][vDriverID];
	new rand = random(5);

	VehAnim[driverid] = false;

	if((VehicleInfo[vehicleid][vEngineHp] > 300.0 && VehicleInfo[vehicleid][vEngineHp] < 600.0) && (rand == 0 || rand == 2 || rand == 4)) {
		SendClientMessage(driverid, COLOR_YELLOW, "Nie uda o si  odpali  silnika.");
	} else if((VehicleInfo[vehicleid][vEngineHp] > 600.0) || (VehicleInfo[vehicleid][vEngineHp] < 600.0 && (rand == 1 || rand == 3))) {
		new engine, lights, alarm, doors, bonnet, boot, objective;

		VehicleInfo[vehicleid][vEngine] = true;

		GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
		SetVehicleParamsEx(vehicleid, VehicleInfo[vehicleid][vEngine], lights, alarm, doors, bonnet, boot, objective);

		SendClientMessage(driverid, COLOR_YELLOW, "Odpali e  silnik.");
	}
	return 1;
}

stock ClearVehiclePlayers(vehicleid) {
	foreach(new i : Player) {
		if(GetPlayerVehicleID(i) == vehicleid) {
			if(GetPlayerVehicleSeat(i) != -1) {
				RemovePlayerFromVehicle(i);

				TextDrawShowForPlayer(i, VehicleStats[i][0]);
				TextDrawShowForPlayer(i, VehicleStats[i][1]);
			}
		}
	}

	VehicleInfo[vehicleid][vDriverID] = INVALID_PLAYER_ID;
	return 1;
}

stock IsVehicleOwner(playerid, vehicleid) {
	if(VehicleInfo[vehicleid][vOwnerType] == VEHICLE_OWNER_TYPE_SERVER) {
		if(VehicleInfo[vehicleid][vOwnerID] == VEHICLE_OWNER_SERVER) {
			return 1;
		}
	} else if(VehicleInfo[vehicleid][vOwnerType] == VEHICLE_OWNER_TYPE_PLAYER) {
		if(VehicleInfo[vehicleid][vOwnerID] == PlayerInfo[playerid][pID]) {
			return 1;
		}
	}
	return 0;
}

stock GetVehicleSpeed(vehicleid) {
	new Float:Pos[4];

	GetVehicleVelocity(vehicleid, Pos[0], Pos[1], Pos[2]);

	Pos[3] = floatsqroot(floatpower(floatabs(Pos[0]), 2.0) + floatpower(floatabs(Pos[1]), 2.0) + floatpower(floatabs(Pos[2]), 2.0)) * 180.0;
	return floatround(Pos[3]);
}

stock CountVehicleMileage(vehicleid) {
	new Speed = GetVehicleSpeed(vehicleid);

	if(Speed) {
		VehicleInfo[vehicleid][vMileage] += float(Speed) * 1000.0 / 3600.0 / 350.0;
	}
	return 1;
}

stock GetVehicleModelIDFromName(const name[]) {
	for(new i = 0; i < sizeof(VehicleNames); i++) {
		if(strfind(name, VehicleNames[i], true) != -1) {
			return i + 400;
		}
	}
	return -1;
}

stock GetClosestVehicle(playerid) {
	new vehicleid = INVALID_VEHICLE_ID;
	new Float:distance = 5.0;
	new Float:X[2], Float:Y[2], Float:Z[2];

	GetPlayerPos(playerid, X[0], Y[0], Z[0]);

	foreach(new i : VehItter) {
		if(!IsVehicleStreamedIn(i, playerid)) {
			continue;
		}

		GetVehiclePos(i, X[1], Y[1], Z[1]);

		if(distance > Distance(X[0], Y[0], Z[0], X[1], Y[1], Z[1])) {
			distance = Distance(X[0], Y[0], Z[0], X[1], Y[1], Z[1]);
			vehicleid = i;
		}
	}
	return vehicleid;
}

stock GetVehicleOwnerName(vehicleid) {
	new Name[32];

	if(VehicleInfo[vehicleid][vOwnerType] == VEHICLE_OWNER_TYPE_PLAYER) {
		if(VehicleInfo[vehicleid][vOwnerID] != VEHICLE_OWNER_NONE && VehicleInfo[vehicleid][vOwnerID] != VEHICLE_OWNER_SERVER) {
			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "SELECT `Name` FROM `Characters` WHERE `ID` = '%d' LIMIT 1", VehicleInfo[vehicleid][vOwnerID]);
			mysql_query(queryStr);

			mysql_store_result();

			if(mysql_result_stored()) {
				mysql_fetch_string(Name);
				mysql_free_result();
			}
		}
	}
	return Name;
}

stock GetVehicleEngineTypeName(vehicleid) {
	new Name[32];

	switch(VehicleInfo[vehicleid][vEngineType]) {
		case -1: {
			Name = "Brak";
		}
		case 0: {
			Name = "Benzyna";
		}
		case 1: {
			Name = "Olej napedowy";
		}
		case 2: {
			Name = "Bateria";
		}
		case 3: {
			Name = "Paliwo lotnicze";
		}
	}
	return Name;
}

stock GetVehicleFreeIndex() {
	for(new i = 1; i < MAX_VEHICLES; i++) {
		if(!Iter_Contains(VehItter, i)) {
			return i;
		}
	}
	return INVALID_VEHICLE_ID;
}

stock IsVehicleInUse(vehicleid) {
	foreach(new i : Player) {
		if(IsPlayerInVehicle(i, vehicleid)) {
			return 1;
		}
	}
	return 0;
}

stock IsABicycle(carid) {
	if(carid == 481 || carid == 509 || carid == 510) {
		return 1;
	}
	return 0;
}

stock IsABike(carid) {
	if(carid == 481 || carid == 509 || carid == 510) {
		return 1;
	}
	return 0;
}

stock GenerateNewNumberPlate()
{
	new plate[32], platewithoutformatcolor[9], number[6];
	new one, two, three, four, five, six;
	new bool: found = false;
	format(plate, sizeof(plate), "{000000}");
	format(platewithoutformatcolor, 9, "LS ");
	while(!found) {

		
		one = random(10);
		two = random(10);
		three = random(10);
		four = random(10);
		five = random(10);
		six = random(10);
		
		format(number, sizeof(number), "%i%i%i%i%i%i", one, two, three, four, five, six);
		strcat(platewithoutformatcolor, number);

		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "SELECT `ID` FROM `Vehicles` WHERE `Plate` = '%s';", platewithoutformatcolor);
		mysql_query(queryStr);
		mysql_store_result();
		if(mysql_num_rows() == 0) {
			printf("[PLATE] generated %s is unique", platewithoutformatcolor);
			found = true;
		}
		else {	
			printf("[PLATE] generated %s is not unique", platewithoutformatcolor);
		}

		mysql_free_result();
	
	}
	
	strcat(plate, platewithoutformatcolor);
	strcat(plate, "{000000}");
	
	return platewithoutformatcolor;
	
}

stock RespawnVehicle(vehicleid) {
	VehicleInfo[vehicleid][vSpawned] = false;
	UnSpawnVehicle(vehicleid);
	VehicleInfo[vehicleid][vSpawned] = true;
	SpawnVehicle(vehicleid);
	return 1;
}
