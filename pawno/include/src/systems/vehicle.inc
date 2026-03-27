/*
	Project: GodFather
	Author: MisterMagik, steeZ
	File name: timers.inc
	Date: 12.03.2026
	Modified: 12.03.2026
	Desc: Vehicle system.
*/

stock InitVehicleData() {
	printf("[POJAZD] Zaczynam ladowac pojazdy...");

	new id = 1;
	new colorStr[8], posStr[32], windowStr[8], componentStr[82];

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "SELECT `OwnerID`, `OwnerType`, `BizID`, `AccessID`, `RentID`, `ModelID`, `EngineType`, `Color`, `Pos`, `Fuel`, `Lock`, `Engine`, `EngineHp`, `Spawned`, `LightsOn`, `Window`, `Accessories`, `Panels`, `Doors`, `Lights`, `Tires`, `Vw`, `Int`, `Paintjob`, `Nitro`, `Components`, `Repair`, `Mileage`, `Block`, `Desc`, `Plate` FROM `Vehicles`");
	mysql_query(queryStr);

	mysql_store_result();

	if(mysql_result_stored()) {
		while(mysql_fetch_row(queryStr, "|")) {
			sscanf(queryStr, "p<|>iiis[32]iiis[8]s[32]fiifiis[8]iiiiiiiiis[82]ffis[128]s[32]",
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
				VehicleInfo[id][vLock],
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

			if(VehicleInfo[id][vSpawned]) {
				SpawnVehicle(id);
			}

			Iter_Add(VehItter, id);

			printf("[POJAZD] OwnerID: %d, OwnerType: %d, BizID: %d, AccessID: %s, RentID: %d, ModelID: %d, EngineType: %d, colorStr: %s, posStr: %s, Fuel: %0.1f, Lock: %d, Engine: %d, EngineHp: %0.1f, Spawned: %d, LightsOn: %d, Window: %s, Accessories: %d, Panels: %d, Doors: %d, Lights: %d, Tires: %d, Vw: %d, Int: %d, Paintjob: %d, Nitro: %d, Components: %s, Repair: %0.1f, Mileage: %0.1f, Block: %d, Desc: %s, Plate: %s",
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
				VehicleInfo[id][vLock],
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

			id++;
		}
	}

	printf("[POJAZD] Wczytano %d pojazdow.", id);

	mysql_free_result();
	return 1;
}

stock AddVehicle(ownerid, ownertype, modelid, enginetype, color1, color2, salon, Float:PosX, Float:PosY, Float:PosZ, Float:PosA) {
	new id = INVALID_VEHICLE_ID;

	mysql_query("SELECT COUNT(`ID`) FROM `Vehicles`");
	mysql_store_result();

	if(mysql_result_stored()) {
		id = mysql_fetch_int();
		mysql_free_result();
	}

	if(id == INVALID_VEHICLE_ID) {
		return 1;
	}

	if(id + 1 == MAX_VEHICLES) {
		printf("[POJAZD] Nie mozna juz stworzyc kolejnego pojazdu.");
		printf("[POJAZD] Przekroczono max liczbe dozwolonych pojazdow (%d).", MAX_VEHICLES);
		return 1;
	}

	new colorStr[8], posStr[32];

	VehicleInfo[id][vID] = id + 1;
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
	VehicleInfo[id][vLock] = false;
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
	VehicleInfo[id][vNitro] = 0;
	VehicleInfo[id][vRepair] = 0.0;
	VehicleInfo[id][vMileage] = 0.0;
	VehicleInfo[id][vBlock] = false;
	format(VehicleInfo[id][vPlate], 32, " ");
	format(VehicleInfo[id][vDesc], 128, " ");

	if(salon) {
		VehicleInfo[id][vSpawned] = true;

		SpawnVehicle(id);
	}

	for(new i = 0; i < 4; i++) {
		VehicleInfo[id][vWindow] = -1;
	}

	for(new i = 0; i < 14; i++) {
		VehicleInfo[id][vComponents] = -1;
	}

	format(colorStr, sizeof(colorStr), "%d,%d", VehicleInfo[id][vColor][0], VehicleInfo[id][vColor][1]);
	format(posStr, sizeof(posStr), "%f,%f,%f,%f", VehicleInfo[id][vPos][0], VehicleInfo[id][vPos][1], VehicleInfo[id][vPos][2], VehicleInfo[id][vPos][3]);

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "INSERT INTO `Vehicles` (`ID`, `OwnerID`, `OwnerType`, `ModelID`, `EngineType`, `Color`, `Pos`, `Fuel`, `EngineHp`, `Spawned`) VALUES ('%d', '%d', '%d', '%d', '%d', '%s', '%s', '%f', '%f', '%d')",
		VehicleInfo[id][vID],
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

	printf("[POJAZD] Dodano nowy pojazd o ID: %d", id + 1);
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

	VehicleInfo[vehicleid][vID] = OSRP_INVALID_ID;
	VehicleInfo[vehicleid][vOwnerID] = VEHICLE_OWNER_NONE;
	VehicleInfo[vehicleid][vOwnerType] = VEHICLE_OWNER_TYPE_NONE;
	VehicleInfo[vehicleid][vBizID] = 0;
	VehicleInfo[vehicleid][vAccessID] = "Brak";
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
	VehicleInfo[vehicleid][vLock] = false;
	VehicleInfo[vehicleid][vEngine] = false;
	VehicleInfo[vehicleid][vEngineHp] = 0.0;
	VehicleInfo[vehicleid][vLightsOn] = false;
	VehicleInfo[vehicleid][vAccessories] = 0;
	VehicleInfo[vehicleid][vPanels] = 0;
	VehicleInfo[vehicleid][vDoors] = 0;
	VehicleInfo[vehicleid][vLights] = 0;
	VehicleInfo[vehicleid][vTires] = 0;
	VehicleInfo[vehicleid][vVw] = 0;
	VehicleInfo[vehicleid][vInt] = 0;
	VehicleInfo[vehicleid][vPaintjob] = -1;
	VehicleInfo[vehicleid][vNitro] = 0;
	VehicleInfo[vehicleid][vRepair] = 0.0;
	VehicleInfo[vehicleid][vMileage] = 0.0;
	VehicleInfo[vehicleid][vBlock] = false;
	VehicleInfo[vehicleid][vPlate] = " ";
	VehicleInfo[vehicleid][vDesc] = " ";

	if(VehicleInfo[vehicleid][vDriverID] != INVALID_PLAYER_ID) {
		VehicleInfo[vehicleid][vSpawned] = false;

		DestroyVehicle(vehicleid);
		DestroyDynamic3DTextLabel(VehicleInfo[vehicleid][v3DDesc]);
	}

	for(new i = 0; i < 4; i++) {
		VehicleInfo[vehicleid][vWindow] = -1;
	}

	for(new i = 0; i < 14; i++) {
		VehicleInfo[vehicleid][vComponents] = -1;
	}

	Iter_Remove(VehItter, vehicleid);

	printf("[POJAZD] Usunieto pojazd o ID: %d", vehicleid + 1);
	return 1;
}

stock SaveVehicleData(vehicleid, option) {
	if(vehicleid == INVALID_VEHICLE_ID) {
		return 1;
	}

	queryStr[0] = EOS;
	format(queryStr, sizeof(queryStr), "UPDATE `Vehicles` SET ");

	if(option & VEHICLE_SAVE_POS) {
		new posStr[32];

		GetVehiclePos(vehicleid, VehicleInfo[vehicleid][vPos][0], VehicleInfo[vehicleid][vPos][1], VehicleInfo[vehicleid][vPos][2]);
		GetVehicleZAngle(vehicleid, VehicleInfo[vehicleid][vPos][3]);

		format(posStr, sizeof(posStr), "%f,%f,%f,%f", VehicleInfo[vehicleid][vPos][0], VehicleInfo[vehicleid][vPos][1], VehicleInfo[vehicleid][vPos][2], VehicleInfo[vehicleid][vPos][3]);
		format(queryStr, sizeof(queryStr), "%s`Pos` = '%s'", queryStr, posStr);
	}

	if(option & VEHICLE_SAVE_ENGINE) {
		GetVehicleHealth(vehicleid, VehicleInfo[vehicleid][vEngineHp]);

		format(queryStr, sizeof(queryStr), "%s`EngineType` = '%d', `Engine` = '%d', `EngineHp` = '%f'", queryStr, VehicleInfo[vehicleid][vEngineType], VehicleInfo[vehicleid][vEngine], VehicleInfo[vehicleid][vEngineHp]);
	}

	format(queryStr, sizeof(queryStr), "%s WHERE `ID` = '%d'", queryStr, VehicleInfo[vehicleid][vID]);
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

	new SAMPID = INVALID_VEHICLE_ID;

	SAMPID = CreateVehicle(VehicleInfo[vehicleid][vModelID], VehicleInfo[vehicleid][vPos][0], VehicleInfo[vehicleid][vPos][1], VehicleInfo[vehicleid][vPos][2], VehicleInfo[vehicleid][vPos][3], VehicleInfo[vehicleid][vColor][0], VehicleInfo[vehicleid][vColor][1], -1);
	VehicleInfo[vehicleid][v3DDesc] = CreateDynamic3DTextLabel(VehicleInfo[vehicleid][vDesc], COLOR_WHITE, 0.0, 0.0, 0.1, 20.0, INVALID_PLAYER_ID, SAMPID, 0, 0, 0, -1, 20.0, -1, 0);

	if(IsABicycle(VehicleInfo[vehicleid][vModelID])) {
		SetVehicleParamsEx(SAMPID, 1, 0, 0, 0, 0, 0, 0);
	} else {
		new engine, lights, alarm, doors, bonnet, boot, objective;

		GetVehicleParamsEx(SAMPID, engine, lights, alarm, doors, bonnet, boot, objective);
		SetVehicleParamsEx(SAMPID, VehicleInfo[vehicleid][vEngine], VehicleInfo[vehicleid][vLightsOn], alarm, doors, bonnet, boot, objective);
	}

	SetVehicleVirtualWorld(SAMPID, VehicleInfo[vehicleid][vVw]);
	LinkVehicleToInterior(SAMPID, VehicleInfo[vehicleid][vInt]);

	UpdateVehicleDamageStatus(SAMPID, VehicleInfo[vehicleid][vPanels], VehicleInfo[vehicleid][vDoors], VehicleInfo[vehicleid][vLights], VehicleInfo[vehicleid][vTires]);

	if(VehicleInfo[vehicleid][vNitro]) {
		AddVehicleComponent(SAMPID, 1010);
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

	DestroyVehicle(vehicleid);
	VehicleInfo[vehicleid][vSpawned] = false;

	SaveVehicleData(vehicleid, VEHICLE_SAVE_SPAWN);
	return 1;
}

Callback VehicleLightsOn(vehicleid) {
	if(VehicleInfo[vehicleid][vDriverID] == INVALID_PLAYER_ID) {
		return 1;
	}

	if(VehicleInfo[vehicleid][vLightsOn]) {
		return 1;
	}

	new engine, lights, alarm, doors, bonnet, boot, objective;

	VehicleInfo[vehicleid][vLightsOn] = true;

	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
	SetVehicleParamsEx(vehicleid, engine, VehicleInfo[vehicleid][vLightsOn], alarm, doors, bonnet, boot, objective);
	return 1;
}

Callback VehicleLightsOff(vehicleid) {
	if(VehicleInfo[vehicleid][vDriverID] == INVALID_PLAYER_ID) {
		return 1;
	}

	if(!VehicleInfo[vehicleid][vLightsOn]) {
		return 1;
	}

	new engine, lights, alarm, doors, bonnet, boot, objective;

	VehicleInfo[vehicleid][vLightsOn] = false;

	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
	SetVehicleParamsEx(vehicleid, engine, VehicleInfo[vehicleid][vLightsOn], alarm, doors, bonnet, boot, objective);
	return 1;
}

Callback VehicleEngineStarting(vehicleid) {
	if(vehicleid == INVALID_VEHICLE_ID) {
		return 1;
	}

	if(VehicleInfo[vehicleid][vDriverID] == INVALID_PLAYER_ID) {
		return 1;
	}

	new driverid = VehicleInfo[vehicleid][vDriverID];

	if(!VehAnim[driverid]) {
		ApplyAnimation(driverid, "PED", "CAR_tune_radio", 4.1, 0, 0, 0, 0, 0);

		VehAnim[driverid] = true;
	}

	if(!VehicleInfo[vehicleid][vEngine]) {
		SendClientMessage(driverid, COLOR_YELLOW, "Próbujesz odpaliæ silnik...");
		SetTimerEx("VehicleEngineOn", 2500, false, "i", vehicleid);
	} else {
		new engine, lights, alarm, doors, bonnet, boot, objective;

		VehicleInfo[vehicleid][vEngine] = false;

		GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
		SetVehicleParamsEx(vehicleid, VehicleInfo[vehicleid][vEngine], lights, alarm, doors, bonnet, boot, objective);

		SendClientMessage(driverid, COLOR_YELLOW, "Wy³¹czy³eœ silnik.");
		PlayerPlaySound(driverid, 1084, 0.0, 0.0, 0.0);
	}
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

	if(VehicleInfo[vehicleid][vFuel] <= 0.0) {
		return 1;
	}

	if(VehicleInfo[vehicleid][vEngineHp] <= 300.0) {
		return SendClientMessage(driverid, COLOR_YELLOW, "Ten pojazd jest zepsuty, nie mo¿na go uruchomiæ. Aby go naprawiæ musisz wezwaæ mechanika.");
	} else if((VehicleInfo[vehicleid][vEngineHp] > 500.0) || (VehicleInfo[vehicleid][vEngineHp] <= 300.0 && (rand == 1 || rand == 3))) {
		new engine, lights, alarm, doors, bonnet, boot, objective;

		VehicleInfo[vehicleid][vEngine] = true;

		GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
		SetVehicleParamsEx(vehicleid, VehicleInfo[vehicleid][vEngine], lights, alarm, doors, bonnet, boot, objective);

		SendClientMessage(driverid, COLOR_YELLOW, "Odpali³eœ silnik.");
	}
	return 1;
}

stock IsVehicleOwner(playerid, vehicleid) {
	
}

stock GetVehicleSpeed(vehicleid) {
	new Float:Pos[4];

	GetVehicleVelocity(vehicleid, Pos[0], Pos[1], Pos[2]);

	Pos[3] = floatsqroot(floatpower(floatabs(Pos[0]), 2.0) + floatpower(floatabs(Pos[1]), 2.0) + floatpower(floatabs(Pos[2]), 2.0)) * 180.0;
	return floatround(Pos[3]);
}

stock CountVehicleMileage(vehicleid) {
	new Float:dist;

	if(GetVehicleSpeed(vehicleid)) {
		dist = GetVehicleSpeed(vehicleid) * 1000 / 3600 / 1;
		dist = dist / 350.0;
	}

	VehicleInfo[vehicleid][vMileage] += dist;
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
	new name[64];
	
	if(VehicleInfo[vehicleid][vOwnerType] == VEHICLE_OWNER_TYPE_PLAYER) {
		if(VehicleInfo[vehicleid][vOwnerID] != VEHICLE_OWNER_NONE && VehicleInfo[vehicleid][vOwnerID] != VEHICLE_OWNER_SERVER) {
			foreach(new i : Player) {
				if(PlayerInfo[i][pID] == VehicleInfo[vehicleid][vOwnerID]) {
					format(name, sizeof(name), "%s", PlayerInfo[i][pName]);
					break;
				}
			}
		}
	}
	return name;
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
