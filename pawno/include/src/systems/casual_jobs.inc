/*
	Project: GodFather
	Author: MisterMagik, steeZ
	File name: casual_jobs.inc
	Date: 12.03.2026
	Modified: 12.03.2026
	Desc: Casual jobs system.

	Prace dorywcze
*/

new TrashJobObjects[MAX_TRASH_JOB_OBJECTS];
new BushJobObjects[MAX_BUSH_JOB_OBJECTS];

new TrashJobActualObjects = MAX_TRASH_JOB_OBJECTS;
new BushJobActualObjects = MAX_BUSH_JOB_OBJECTS;

new bool:TrashJobObjectsIsCreated[MAX_TRASH_JOB_OBJECTS];
new bool:BushJobObjectsIsCreated[MAX_BUSH_JOB_OBJECTS];

new bool:TrashJobObjectsInit = false;
new bool:BushJobObjectsInit = false;

new pFoundJobObject[MAX_PLAYERS] = {INVALID_OBJECT_ID, ...};
new bool:pSetAction[MAX_PLAYERS];

new TrashJobZone;
new BushJobZone;

new TrashJobPrizes[] = { 5, 10, 15, 20, 25 };
new BushJobPrizes[] = { 30, 35, 40, 45, 50, 55 };

new Float:TrashJobObjectsPos[][] = {
	{1891.17126, -1164.25146, 23.08340, 0.00000, 0.00000, 0.72820},
	{1990.63049, -1224.16919, 19.24251, 0.00000, 0.00000, 0.00000},
	{1990.32983, -1242.32788, 19.37830, 0.00000, 0.00000, 0.00000},
	{2020.75403, -1221.69177, 20.80310, 0.00000, 0.00000, 0.00000},
	{2044.42749, -1224.29675, 22.15020, 0.00000, 0.00000, 0.51010},
	{2046.50708, -1243.37415, 22.38920, 0.00000, 0.00000, 0.30910},
	{2051.52271, -1202.67639, 22.71576, 0.00000, 0.00000, 0.30910},
	{2052.38281, -1176.04480, 22.69580, 0.00000, 0.00000, 0.30910},
	{2041.34167, -1168.56934, 21.90720, 0.00000, 0.00000, 0.30910},
	{2030.66223, -1158.44653, 21.53190, 0.00000, 0.00000, 0.30910},
	{2031.54321, -1176.34399, 21.43190, 0.00000, 0.00000, 0.30910},
	{2028.02014, -1188.09351, 20.93670, 0.00000, 0.00000, 0.30910},
	{2035.87732, -1198.42529, 21.66573, 0.00000, 0.00000, 0.30910},
	{1982.78491, -1150.86169, 20.16030, 0.00000, 0.00000, 0.30910},
	{1985.46826, -1165.90369, 19.65590, 0.00000, 0.00000, 0.30910},
	{1995.39417, -1166.29956, 19.77880, 0.00000, 0.00000, 0.30910},
	{1956.17297, -1165.16992, 19.70750, 0.00000, 0.00000, 0.30910},
	{1956.51685, -1149.72119, 20.67910, 0.00000, 0.00000, 0.30910},
	{1919.24451, -1188.95996, 20.26370, 0.00000, 0.00000, 0.30910},
	{1921.23340, -1227.97937, 17.65620, 0.00000, 0.00000, 0.30910},
	{1958.74634, -1231.00745, 18.92890, 0.00000, 0.00000, 0.72820},
	{1962.63916, -1246.68738, 19.05150, 0.00000, 0.00000, 0.72820},
	{1876.54102, -1190.78210, 21.60050, 0.00000, 0.00000, 0.72820},
	{1884.97327, -1183.28418, 22.28050, 0.00000, 0.00000, 0.72820}
};

new Float:BushJobObjectsPos[][] = {
	{1252.92834, -1962.66809, 53.19856},
	{1267.64185, -2075.46362, 58.20520},
	{1273.55493, -2084.85376, 57.77419},
	{1157.73499, -2020.10242, 68.93955},
	{1233.25623, -1989.22803, 59.20900},
	{1266.24573, -1982.45911, 54.99367},
	{1250.41895, -1995.54407, 58.39690},
	{1151.57886, -2000.21057, 68.93584},
	{1201.10693, -2026.21558, 69.14055},
	{1150.81274, -2026.11548, 68.93955},
	{1200.71289, -2047.48279, 68.93955},
	{1153.67102, -2045.18701, 68.93955},
	{1159.51208, -2060.68237, 68.93955},
	{1151.11023, -2075.52539, 68.93955},
	{1194.47864, -2059.89087, 68.93955},
	{1196.57361, -2074.16992, 68.93955},
	{1191.39172, -2014.87268, 68.93584},
	{1198.58350, -1998.35754, 68.93584},
	{1163.24463, -1998.74048, 68.93584},
	{1190.10510, -2000.73389, 68.93584}
};

stock CreateTrashJobObjects() {
	if(TrashJobObjectsInit) {
		if(TrashJobActualObjects == MAX_TRASH_JOB_OBJECTS) {
			return 1;
		}

		for(new i = 0; i < MAX_TRASH_JOB_OBJECTS; i++) {
			if(!TrashJobObjectsIsCreated[i]) {
				new bool:found = false;
				new id;

				while(!found) {
					new rand = random(MAX_TRASH_JOB_OBJECTS);

					if(!IsValidDynamicObject(TrashJobObjects[rand]) && !TrashJobObjectsIsCreated[rand]) {
						found = true;
						id = rand;
					}
				}

				CreateTrashJobObject(i, id);
			}
		}
		return 1;
	}

	DestroyTrashJobObjects();

	for(new i = 0; i < MAX_TRASH_JOB_OBJECTS; i++) {
		TrashJobObjectsIsCreated[i] = true;
		TrashJobObjects[i] = CreateDynamicObject(2674,
												 TrashJobObjectsPos[i][0],
												 TrashJobObjectsPos[i][1],
												 TrashJobObjectsPos[i][2],
												 TrashJobObjectsPos[i][3],
												 TrashJobObjectsPos[i][4],
												 TrashJobObjectsPos[i][5],
												 0, -1, -1, 300.0
												 );
	}

	TrashJobZone = CreateDynamicRectangle(2057.5337, -1251.2866, 1876.1093, -1144.9321, -1, -1, -1);
	CreateDynamicMapIcon(1969.7532, -1198.8317, 25.6496, 56, 0, 0, -1, -1, 9999.0);

	TrashJobObjectsInit = true;
	return 1;
}

stock CreateBushJobObjects() {
	if(BushJobObjectsInit) {
		if(BushJobActualObjects == MAX_BUSH_JOB_OBJECTS) {
			return 1;
		}

		for(new i = 0; i < MAX_BUSH_JOB_OBJECTS; i++) {
			if(!BushJobObjectsIsCreated[i]) {
				new bool:found = false;
				new id;

				while(!found) {
					new rand = random(MAX_BUSH_JOB_OBJECTS);

					if(!IsValidDynamicObject(BushJobObjects[rand]) && !BushJobObjectsIsCreated[rand]) {
						found = true;
						id = rand;
					}
				}

				CreateBushJobObject(i, id);
			}
		}
		return 1;
	}

	DestroyBushJobObjects();

	for(new i = 0; i < MAX_BUSH_JOB_OBJECTS; i++) {
		BushJobObjectsIsCreated[i] = true;
		BushJobObjects[i] = CreateDynamicObject(811,
												 BushJobObjectsPos[i][0],
												 BushJobObjectsPos[i][1],
												 BushJobObjectsPos[i][2],
												 0.00000, 0.00000, 0.00000,
												 0, -1, -1, 300.0
												 );
	}

	BushJobZone = CreateDynamicRectangle(1212.7601, -1992.0531, 1136.3495, -2081.7129, -1, -1, -1);
	CreateDynamicMapIcon(1253.9507, -2030.7537, 59.5928, 56, 0, 0, -1, -1, 9999.0);

	BushJobObjectsInit = true;
	return 1;
}

stock CreateTrashJobObject(trashid, posid) {
	if(IsValidDynamicObject(TrashJobObjects[trashid])) {
		return 1;
	}

	TrashJobObjects[trashid] = CreateDynamicObject(2674,
											 TrashJobObjectsPos[posid][0],
											 TrashJobObjectsPos[posid][1],
											 TrashJobObjectsPos[posid][2],
											 TrashJobObjectsPos[posid][3],
											 TrashJobObjectsPos[posid][4],
											 TrashJobObjectsPos[posid][5],
											 0, -1, -1, 300.0
											 );
	TrashJobObjectsIsCreated[trashid] = true;
	return 1;
}

stock CreateBushJobObject(bushid, posid) {
	if(IsValidDynamicObject(BushJobObjects[bushid])) {
		return 1;
	}

	BushJobObjects[bushid] = CreateDynamicObject(811,
											 BushJobObjectsPos[posid][0],
											 BushJobObjectsPos[posid][1],
											 BushJobObjectsPos[posid][2],
											 0.00000, 0.00000, 0.00000,
											 0, -1, -1, 300.0
											 );
	BushJobObjectsIsCreated[bushid] = true;
	return 1;
}

stock DestroyTrashJobObjects() {
	for(new i = 0; i < MAX_TRASH_JOB_OBJECTS; i++) {
		DestroyTrashJobObject(i);
	}
}

stock DestroyBushJobObjects() {
	for(new i = 0; i < MAX_BUSH_JOB_OBJECTS; i++) {
		DestroyBushJobObject(i);
	}
}

stock DestroyTrashJobObject(trashid) {
	DestroyDynamicObject(TrashJobObjects[trashid]);
	TrashJobObjectsIsCreated[trashid] = false;

	if(TrashJobObjectsInit) {
		TrashJobActualObjects--;
	}
}

stock DestroyBushJobObject(bushid) {
	DestroyDynamicObject(BushJobObjects[bushid]);
	BushJobObjectsIsCreated[bushid] = false;

	if(BushJobObjectsInit) {
		BushJobActualObjects--;
	}
}

stock TrashJobPickUpObject(playerid) {
	if(pTrashZone[playerid]) {
		if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
			new Float:oX, Float:oY, Float:oZ;

			if(pFoundJobObject[playerid] == INVALID_OBJECT_ID) {
				for(new i = 0; i < MAX_TRASH_JOB_OBJECTS; i++) {
					GetDynamicObjectPos(TrashJobObjects[i], oX, oY, oZ);

					if(PlayerToPoint(1.0, playerid, oX, oY, oZ)) {
						if(IsValidDynamicObject(TrashJobObjects[i]) && TrashJobObjectsIsCreated[i]) {
							if(IsPlayerFacingObject(playerid, TrashJobObjects[i])) {
								pFoundJobObject[playerid] = i;
								break;
							}
						}
					}
				}
			} else {
				if(!pSetAction[playerid]) {
					osrp_TogglePlayerControllable(playerid, 0);

					ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 0, 0, 0, 0, 0, 0);
					pSetAction[playerid] = true;

					SetTimerEx("StopJobAction", 3000, false, "i", playerid);
					DestroyTrashJobObject(pFoundJobObject[playerid]);

					new prize = TrashJobPrizes[random(sizeof(TrashJobPrizes))];

					ConsumingMoney[playerid] = 1;
					GivePlayerMoney(playerid, prize);

					mainStr[0] = EOS;
					format(mainStr, sizeof(mainStr), "~n~~w~Otrzymujesz: ~g~$%d", prize);
					GameTextForPlayer(playerid, mainStr, 3000, 3);
				}
			}
		}
	}
}

stock BushJobPickUpObject(playerid) {
	if(pBushZone[playerid]) {
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
			new vehicleid = GetPlayerVehicleID(playerid);

			if(GetVehicleModel(vehicleid) == 572) {
				if(VehicleInfo[vehicleid][vOwnerID] == VEHICLE_OWNER_SERVER && VehicleInfo[vehicleid][vOwnerType] == VEHICLE_OWNER_TYPE_SERVER) {
					new Float:oX, Float:oY, Float:oZ;

					if(pFoundJobObject[playerid] == INVALID_OBJECT_ID) {
						for(new i = 0; i < MAX_BUSH_JOB_OBJECTS; i++) {
							GetDynamicObjectPos(BushJobObjects[i], oX, oY, oZ);

							if(PlayerToPoint(1.5, playerid, oX, oY, oZ)) {
								if(IsValidDynamicObject(BushJobObjects[i]) && BushJobObjectsIsCreated[i]) {
									pFoundJobObject[playerid] = i;
									break;
								}
							}
						}
					} else {
						if(!pSetAction[playerid]) {
							osrp_TogglePlayerControllable(playerid, 0);
							pSetAction[playerid] = true;

							if(GetVehicleSpeed(vehicleid) > 0) {
								SetVehicleVelocity(vehicleid, 0.0, 0.0, 0.0);
							}

							SetTimerEx("StopJobAction", 4000, false, "i", playerid);
							DestroyBushJobObject(pFoundJobObject[playerid]);

							GameTextForPlayer(playerid, "~n~~g~Koszenie trawy~n~czekaj...", 2000, 3);
						}
					}
				}
			}
		}
	}
}

Callback StopJobAction(playerid) {
	if(pTrashZone[playerid]) {
		if(pSetAction[playerid]) {
			osrp_TogglePlayerControllable(playerid, 1);

			pSetAction[playerid] = false;
			pFoundJobObject[playerid] = INVALID_OBJECT_ID;
		}
	}

	if(pBushZone[playerid]) {
		if(pSetAction[playerid]) {
			osrp_TogglePlayerControllable(playerid, 1);

			pSetAction[playerid] = false;
			pFoundJobObject[playerid] = INVALID_OBJECT_ID;

			new prize = BushJobPrizes[random(sizeof(BushJobPrizes))];

			ConsumingMoney[playerid] = 1;
			GivePlayerMoney(playerid, prize);
		}
	}
}
