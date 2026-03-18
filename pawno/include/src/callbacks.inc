/*
	Project: GodFather
	Author: MisterMagik, steeZ
	File name: callbacks.inc
	Date: 12.03.2026
	Modified: 12.03.2026
	Desc: Server player/vehicle callbacks.
*/

sampCallback OnGameModeInit() {
	new callSecs = gettime();

	EnableStuntBonusForAll(0);
	DisableInteriorEnterExits();
	AllowInteriorWeapons(1);
	EnableVehicleFriendlyFire();
	ManualVehicleEngineAndLights();
	ShowPlayerMarkers(PLAYER_MARKERS_MODE_OFF);
	AddPlayerClassEx(0, 0, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0);
	AllowAdminTeleport(1);
	SetGameModeText("OSRP v1.0");

	ConnectingMySQL();

    new string[MAX_PLAYER_NAME];
    new string1[MAX_PLAYER_NAME];

	for(new c=0;c<CAR_AMOUNT;c++) {
		Gas[c] = GasMax;
	}

	/*LoadProperty();
	LoadBizz();
	LoadSBizz();
	LoadBoxer();
	LoadStuff();
	LoadFamilies();
	LoadCK();
	LoadTurfs();
	LoadPapers();*/
	TextDrawsInit();

	News[hTaken1] = 0; News[hTaken2] = 0; News[hTaken3] = 0; News[hTaken4] = 0; News[hTaken5] = 0;
	format(string, sizeof(string), "Nothing");
	strmid(News[hAdd1], string, 0, strlen(string), 255);
	strmid(News[hAdd2], string, 0, strlen(string), 255);
	strmid(News[hAdd3], string, 0, strlen(string), 255);
	strmid(News[hAdd4], string, 0, strlen(string), 255);
	strmid(News[hAdd5], string, 0, strlen(string), 255);
	format(string1, sizeof(string1), "No-one");
	strmid(News[hContact1], string1, 0, strlen(string1), 255);
	strmid(News[hContact2], string1, 0, strlen(string1), 255);
	strmid(News[hContact3], string1, 0, strlen(string1), 255);
	strmid(News[hContact4], string1, 0, strlen(string1), 255);
	strmid(News[hContact5], string1, 0, strlen(string1), 255);
	PlayerHaul[78][pCapasity] = 100;
	PlayerHaul[79][pCapasity] = 100;
	PlayerHaul[80][pCapasity] = 50;
	PlayerHaul[81][pCapasity] = 50;

	format(objstore, sizeof(objstore), "MOLE: I got nothing, check back with me later.");
	format(cbjstore, sizeof(cbjstore), "HQ: There is nothing in your Vicinity, Out.");
	format(motd, sizeof(motd), "Welcome to the Role Play - The Godfather Server.");
	gettime(ghour, gminute, gsecond);
	FixHour(ghour);
	ghour = shifthour;

	if(!realtime)
	{
		SetWorldTime(wtime);
	}

	// CreatedCars check
	for(new i = 0; i < sizeof(CreatedCars); i++)
	{
	    CreatedCars[i] = 0;
	}

	// Zones
	for(new i = 0; i < sizeof(TurfInfo); i++)
	{
	    Turfs[i] = GangZoneCreate(TurfInfo[i][zMinX],TurfInfo[i][zMinY],TurfInfo[i][zMaxX],TurfInfo[i][zMaxY]);
	}

	// Player Class's
	for(new i = 0; i <= sizeof(Peds)-1; i++)
	{
		AddPlayerClass(Peds[i][0],1958.3783,1343.1572,1100.3746,269.1425,-1,-1,-1,-1,-1,-1);
	}

	// Car Spawns
	for(new h = 0; h < sizeof(HouseInfo); h++)
	{
		AddStaticVehicleEx(HouseInfo[h][hVec], HouseCarSpawns[h][0], HouseCarSpawns[h][1], HouseCarSpawns[h][2], HouseCarSpawns[h][3], HouseInfo[h][hVcol1], HouseInfo[h][hVcol2], 60000);
		gCarLock[h+1] = 1;
	}//34
	for(new h = 0; h < sizeof(HouseInfo); h++)
	{
		if(HouseInfo[h][hOwned] == 0)
		{
			AddStaticPickup(1273, 2, HouseInfo[h][hEntrancex], HouseInfo[h][hEntrancey], HouseInfo[h][hEntrancez]);
			pickups++;
		}
		if(HouseInfo[h][hOwned] == 1)
		{
			AddStaticPickup(1239, 2, HouseInfo[h][hEntrancex], HouseInfo[h][hEntrancey], HouseInfo[h][hEntrancez]);
			pickups++;
		}
	}
	for(new h = 0; h < sizeof(BizzInfo); h++)
	{
		if(BizzInfo[h][bOwned] == 0)
		{
			AddStaticPickup(1272, 2, BizzInfo[h][bEntranceX], BizzInfo[h][bEntranceY], BizzInfo[h][bEntranceZ]);
			pickups++;
		}
		if(BizzInfo[h][bOwned] == 1)
		{
			AddStaticPickup(1239, 2, BizzInfo[h][bEntranceX], BizzInfo[h][bEntranceY], BizzInfo[h][bEntranceZ]);
			pickups++;
		}
	}
	for(new h = 0; h < sizeof(SBizzInfo); h++)
	{
		if(SBizzInfo[h][sbOwned] == 0)
		{
			AddStaticPickup(1272, 2, SBizzInfo[h][sbEntranceX], SBizzInfo[h][sbEntranceY], SBizzInfo[h][sbEntranceZ]);
			pickups++;
		}
		if(SBizzInfo[h][sbOwned] == 1)
		{
			AddStaticPickup(1239, 2, SBizzInfo[h][sbEntranceX], SBizzInfo[h][sbEntranceY], SBizzInfo[h][sbEntranceZ]);
			pickups++;
		}
	}
	AddStaticPickup(1239, 2, 1173.2563,-1323.3102,15.3943); //Hospital 1 near Ammu
	AddStaticPickup(1239, 2, 2029.5945,-1404.6426,17.2512); //Hospital 2 near speedway
	AddStaticPickup(1239, 2, 253.9280,69.6094,1003.6406); //Clear icon in Police Station
	AddStaticPickup(1239, 2, -2162.2554,-2385.9541,30.6250); //City Hall
	AddStaticPickup(1239, 2, 359.5408,206.7693,1008.3828); //Detective Registration
	AddStaticPickup(1239, 2, 347.7374,193.7241,1014.1875); //Lawyer Registration
	AddStaticPickup(1239, 2, 1215.1304,-11.8431,1000.9219); //Whore Registration
	AddStaticPickup(1239, 2, 2166.3772,-1675.3829,15.0859); //DrugDealer Registration
	AddStaticPickup(1239, 2, 1109.3318,-1796.3042,16.5938); //CarJacker Registration
	AddStaticPickup(1239, 2, -2050.8962,460.0262,35.1719); //NewsReporter Registration & /paper
	AddStaticPickup(1239, 2, -2040.9436,456.2395,35.1719); //PaperBoy Registration
	AddStaticPickup(1239, 2, -1932.3859,276.2117,41.0391); //CarMechanic Registration
	AddStaticPickup(1239, 2, 2226.1716,-1718.1792,13.5165); //BodyGuard Registration
	AddStaticPickup(1239, 2, 1366.4325,-1275.2096,13.5469); //ArmsDealer Registration
	AddStaticPickup(1239, 2, 531.7930,-1292.4044,17.2422); //CarDealer Registration
	AddStaticPickup(1239, 2, 766.0804,14.5133,1000.7004); //Boxer Registration
	AddStaticPickup(1239, 2, 1154.2208,-1770.8203,16.5992); //BusDriver Registration
	AddStaticPickup(1239, 2, -77.7288,-1136.3896,1.0781); //Trucker Registration
	AddStaticPickup(1239, 2, 323.0342,1118.5804,1083.8828); //Getting Drugs for DrugDealers
	AddStaticPickup(1239, 2, 1381.0413,-1088.8511,27.3906); //Bill Board (old Job Department)
	AddStaticPickup(1239, 2, 597.1277,-1248.6479,18.2734); //Materials Package building
	AddStaticPickup(1239, 2, -2119.5469,-178.5679,35.3203); //Factory
	AddStaticPickup(1239, 2, 1073.0619,-344.5148,73.9922); //Hitman Agency entrance
	AddStaticPickup(371, 2, 1544.2,-1353.4,329.4); //LS towertop
	AddStaticPickup(371, 2, 1536.0, -1360.0, 1150.0); //LS towertop
	AddStaticPickup(1242, 2, 1527.5,-12.1,1002.0); //binco armor
	AddStaticPickup(1240, 2, 279.3000,1853.5619,8.7649); //area51 health
	pickups=pickups+29;
	printf("Pickups Max = 100, Current Pickups = %d",pickups);
	new randa = random(sizeof(RandCars));
	randa = random(sizeof(RandCars));carselect[0] = RandCars[randa][0];
	randa = random(sizeof(RandCars));carselect[1] = RandCars[randa][0];
	randa = random(sizeof(RandCars));carselect[2] = RandCars[randa][0];
	randa = random(sizeof(RandCars));carselect[3] = RandCars[randa][0];
	randa = random(sizeof(RandCars));carselect[4] = RandCars[randa][0];
	randa = random(sizeof(RandCars));carselect[5] = RandCars[randa][0];
	randa = random(sizeof(RandCars));carselect[6] = RandCars[randa][0];
	randa = random(sizeof(RandCars));carselect[7] = RandCars[randa][0];
	randa = random(sizeof(RandCars));carselect[8] = RandCars[randa][0];
	randa = random(sizeof(RandCars));carselect[9] = RandCars[randa][0];
	randa = random(sizeof(RandCars));carselect[10] = RandCars[randa][0];
	randa = random(sizeof(RandCars));carselect[11] = RandCars[randa][0];
	randa = random(sizeof(RandCars));carselect[12] = RandCars[randa][0];
	randa = random(sizeof(RandCars));carselect[13] = RandCars[randa][0];
	randa = random(sizeof(RandLCars));carselect[14] = RandLCars[randa][0];

	if (realtime)
	{
		new tmphour;
		new tmpminute;
		new tmpsecond;
		gettime(tmphour, tmpminute, tmpsecond);
		FixHour(tmphour);
		tmphour = shifthour;
		SetWorldTime(tmphour);
	}

	synctimer = SetTimer("SyncUp", 60000, 1);
	unjailtimer = SetTimer("SetPlayerUnjail", 1000, 1);
	othtimer = SetTimer("OtherTimer", 1000, 1);
	cartimer = SetTimer("CarCheck", 30000, 1);
	pickuptimer = SetTimer("CustomPickups", 1000, 1);
	spectatetimer = SetTimer("Spectator", 2000, 1);
	idletimer = SetTimer("IdleKick", idletime, 1);
	productiontimer = SetTimer("Production", 300000, 1); //5 mins (300000)
	accountstimer = SetTimer("SaveAccounts", 1800000, 1); //30 mins every account saved
	checkgastimer = SetTimer("CheckGas", RunOutTime, 1);
    stoppedvehtimer = SetTimer("StoppedVehicle", RunOutTime, 1);
	for(new i = 0; i < 165; i++)
	{
		AddCar(i);
	}
	CarInit();

	printf("[CALLBACK] OnGameModeInit (%0.1d sec)", gettime() - callSecs);
	return 1;
}

sampCallback OnGameModeExit()
{
	return 1;
}

sampCallback OnPlayerRequestClass(playerid, classid) {
	new callSecs = gettime();

	SetSpawnInfo(playerid, 0, 0, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0);
	osrp_TogglePlayerSpectating(playerid, 1);

	if(!loadedIntro[playerid]) {
		SetTimerEx("LoadIntro", 3000, false, "i", playerid);
	}
	return 1;
}

sampCallback OnPlayerConnect(playerid)
{
	GetPlayerName(playerid, oocName[playerid], sizeof(oocName));
	mysql_real_escape_string(oocName[playerid], escapedName[playerid]);

	TextDrawShowForPlayer(playerid, SplashScreen);
	PlayerPlaySound(playerid, 1187, 0.0, 0.0, 0.0);

	if(Security != 0)
	{
	    SendClientMessage(playerid, COLOR_YELLOW, "Host has broken one of the Agreement rules, action has been taken.");
	    Kick(playerid);
	    return 1;
	}
	gActivePlayers[playerid]++;
	numplayers++;
	SelectChar[playerid] = 0; HidePM[playerid] = 0; PhoneOnline[playerid] = 0;
	SelectCharID[playerid] = 0; SelectCharPlace[playerid] = 0; ChosenSkin[playerid] = 0;
	GettingJob[playerid] = 0; GuardOffer[playerid] = 999; GuardPrice[playerid] = 0;
    ApprovedLawyer[playerid] = 0; CallLawyer[playerid] = 0; WantLawyer[playerid] = 0;
	KickPlayer[playerid] = 0; CurrentMoney[playerid] = 0; UsedFind[playerid] = 0;
	CP[playerid] = 0; Robbed[playerid] = 0; SpawnChange[playerid] = 1;
	CarOffer[playerid] = 999; CarPrice[playerid] = 0; CarID[playerid] = 0; CarCalls[playerid] = 0;
	RobbedTime[playerid] = 0; MoneyMessage[playerid] = 0; Condom[playerid] = 0;
	STDPlayer[playerid] = 0; SexOffer[playerid] = 999; SexPrice[playerid] = 0;
	RepairOffer[playerid] = 999; RepairPrice[playerid] = 0; RepairCar[playerid] = 0;
	TalkingLive[playerid] = 255; LiveOffer[playerid] = 999; TakingLesson[playerid] = 0;
	RefillOffer[playerid] = 999; RefillPrice[playerid] = 0; MapIconsShown[playerid] = 0;
	DrugOffer[playerid] = 999; PlayerCuffed[playerid] = 0; PlayerCuffedTime[playerid] = 0;
	DrugPrice[playerid] = 0; RegistrationStep[playerid] = 0; OnCK[playerid] = 999; GettingCK[playerid] = 999;
	DrugGram[playerid] = 0; ConnectedToPC[playerid] = 0; OrderReady[playerid] = 0;
	JailPrice[playerid] = 0; MedicTime[playerid] = 0; NeedMedicTime[playerid] = 0; MedicBill[playerid] = 0; GotHit[playerid] = 0;
	WantedPoints[playerid] = 0; GoChase[playerid] = 999; GetChased[playerid] = 999; PlacedNews[playerid] = 0;
	OnDuty[playerid] = 0; WantedLevel[playerid] = 0; TestFishes[playerid] = 0;
	BoxWaitTime[playerid] = 0; SchoolSpawn[playerid] = 0; ChangePos2[playerid][1] = 0;
	SafeTime[playerid] = 60; TransportDuty[playerid] = 0; PlayerTied[playerid] = 0;
	BusCallTime[playerid] = 0; TaxiCallTime[playerid] = 0; MedicCallTime[playerid] = 0; MechanicCallTime[playerid] = 0;
	FindTimePoints[playerid] = 0; FindTime[playerid] = 0; JobDuty[playerid] = 0;
	Mobile[playerid] = 255; Music[playerid] = 0; BoxOffer[playerid] = 999; PlayerBoxing[playerid] = 0;
	Spectate[playerid] = 255; PlayerDrunk[playerid] = 0; PlayerDrunkTime[playerid] = 0;
	Unspec[playerid][sLocal] = 255; FishCount[playerid] = 0;
	WritingPaper[playerid] = 0; WritingPaperNumber[playerid] = 999; WritingLine[playerid] = 0; BringingPaper[playerid] = 0; GotPaper[playerid] = 0;
	PaperOffer[playerid] = 999; ConsumingMoney[playerid] = 0;
    gLastCar[playerid] = 0; FirstSpawn[playerid] = 0;
	gOoc[playerid] = 0; gNews[playerid] = 0; BigEar[playerid] = 0; gDice[playerid] = 0; gFam[playerid] = 0;
	gSpeedo[playerid] = 0; gGas[playerid] = 0;
	gPlayerLogged[playerid] = 0; gPlayerLogTries[playerid] = 0; gPlayerAccount[playerid] = 0;
	gPlayerSpawned[playerid] = 0; PlayerKarting[playerid] = 0; PlayerInKart[playerid] = 0;
	PlayerTazeTime[playerid] = 0; PlayerStoned[playerid] = 0;
	StartTime[playerid] = 0; TicketOffer[playerid] = 999; TicketMoney[playerid] = 0;
	MatsHolding[playerid] = 0; TutTime[playerid] = 0;
	gPlayerMission[playerid] = 0; TaxiAccepted[playerid] = 999; BusAccepted[playerid] = 999;
	PlayerInfo[playerid][pCash] = dollah; NoFuel[playerid] = 0;
	HireCar[playerid] = 299; PlayersChannel[playerid] = 999;
	TransportValue[playerid] = 0; TransportMoney[playerid] = 0; TransportTime[playerid] = 0; TransportCost[playerid] = 0; TransportDriver[playerid] = 999;
	Locator[playerid] = 0; PlayerOnMission[playerid] = 0; MissionCheckpoint[playerid] = 0;
	WatchingTV[playerid] = 0; PlayerPaintballing[playerid] = 0; PlayerPaintballKills[playerid] = 0;
	Fishes[playerid][pLastFish] = 0; Fishes[playerid][pFishID] = 0;
	ProposeOffer[playerid] = 999; MarryWitness[playerid] = 999; MarryWitnessOffer[playerid] = 999; MarriageCeremoney[playerid] = 0; ProposedTo[playerid] = 999; GotProposedBy[playerid] = 999; DivorceOffer[playerid] = 999;
	GivePlayerMoney(playerid,PlayerInfo[playerid][pCash]);
	PlayerInfo[playerid][pLevel] = 0;
	PlayerInfo[playerid][pAdmin] = 0;
	PlayerInfo[playerid][pDonateRank] = 0;
	PlayerInfo[playerid][gPupgrade] = 0;
	PlayerInfo[playerid][pConnectTime] = 0;
	PlayerInfo[playerid][pReg] = 0;
	PlayerInfo[playerid][pSex] = 0;
	PlayerInfo[playerid][pAge] = 0;
	PlayerInfo[playerid][pOrigin] = 0;
	PlayerInfo[playerid][pExp] = 0;
	PlayerInfo[playerid][pAccount] = 0;
	PlayerInfo[playerid][pCrimes] = 0;
	PlayerInfo[playerid][pDeaths] = 0;
	PlayerInfo[playerid][pArrested] = 0;
	PlayerInfo[playerid][pWantedDeaths] = 0;
	PlayerInfo[playerid][pPhoneBook] = 0;
	PlayerInfo[playerid][pLottoNr] = 0;
	PlayerInfo[playerid][pFishes] = 0;
	PlayerInfo[playerid][pBiggestFish] = 0;
	PlayerInfo[playerid][pJob] = 0;
	PlayerInfo[playerid][pPayCheck] = 0;
	PlayerInfo[playerid][pHeadValue] = 0;
	PlayerInfo[playerid][pJailed] = 0;
	PlayerInfo[playerid][pJailTime] = 0;
	PlayerInfo[playerid][pMats] = 0;
	PlayerInfo[playerid][pDrugs] = 0;
	PlayerInfo[playerid][pLeader] = 0;
	PlayerInfo[playerid][pMember] = 0;
	PlayerInfo[playerid][pFMember] = 255;
	PlayerInfo[playerid][pRank] = 0;
	PlayerInfo[playerid][pChar] = 0;
	PlayerInfo[playerid][pContractTime] = 0;
	PlayerInfo[playerid][pDetSkill] = 0;
	PlayerInfo[playerid][pSexSkill] = 0;
	PlayerInfo[playerid][pBoxSkill] = 0;
	PlayerInfo[playerid][pLawSkill] = 0;
	PlayerInfo[playerid][pMechSkill] = 0;
	PlayerInfo[playerid][pJackSkill] = 0;
	PlayerInfo[playerid][pCarSkill] = 0;
	PlayerInfo[playerid][pNewsSkill] = 0;
	PlayerInfo[playerid][pDrugsSkill] = 0;
	PlayerInfo[playerid][pCookSkill] = 0;
	PlayerInfo[playerid][pFishSkill] = 0;
	PlayerInfo[playerid][pSHealth] = 0.0;
	PlayerInfo[playerid][pHealth] = 50.0;
	PlayerInfo[playerid][pPos_x] = 2246.6;
	PlayerInfo[playerid][pPos_y] = -1161.9;
	PlayerInfo[playerid][pPos_z] = 1029.7;
	PlayerInfo[playerid][pInt] = 15;
	PlayerInfo[playerid][pLocal] = 255;
	PlayerInfo[playerid][pTeam] = 3;
	PlayerInfo[playerid][pModel] = 264;
	new randphone = 1000 + random(8999);//minimum 1000  max 9999 //giving one at the start
	PlayerInfo[playerid][pPnumber] = randphone;
	PlayerInfo[playerid][pPhousekey] = 255;
	PlayerInfo[playerid][pPbiskey] = 255;
	PlayerInfo[playerid][pCarLic] = 0;
	PlayerInfo[playerid][pFlyLic] = 0;
	PlayerInfo[playerid][pBoatLic] = 0;
	PlayerInfo[playerid][pFishLic] = 0;
	PlayerInfo[playerid][pGunLic] = 0;
	PlayerInfo[playerid][pGun1] = 0;
	PlayerInfo[playerid][pGun2] = 0;
	PlayerInfo[playerid][pGun3] = 0;
	PlayerInfo[playerid][pGun4] = 0;
	PlayerInfo[playerid][pAmmo1] = 0;
	PlayerInfo[playerid][pAmmo2] = 0;
	PlayerInfo[playerid][pAmmo3] = 0;
	PlayerInfo[playerid][pAmmo4] = 0;
	PlayerInfo[playerid][pCarTime] = 0;
	PlayerInfo[playerid][pPayDay] = 0;
	PlayerInfo[playerid][pPayDayHad] = 0;
	PlayerInfo[playerid][pCDPlayer] = 0;
	PlayerInfo[playerid][pWins] = 0;
	PlayerInfo[playerid][pLoses] = 0;
	PlayerInfo[playerid][pAlcoholPerk] = 0;
	PlayerInfo[playerid][pDrugPerk] = 0;
	PlayerInfo[playerid][pMiserPerk] = 0;
	PlayerInfo[playerid][pPainPerk] = 0;
	PlayerInfo[playerid][pTraderPerk] = 0;
	PlayerInfo[playerid][pTut] = 0;
	PlayerInfo[playerid][pMissionNr] = 0;
	PlayerInfo[playerid][pWarns] = 0;
	PlayerInfo[playerid][pFuel] = 0;
	PlayerInfo[playerid][pAdjustable] = 0;
	ClearCrime(playerid);
	ClearFishes(playerid);
	ClearCooking(playerid);
	ClearGroceries(playerid);
	ClearMarriage(playerid);
	SetPlayerColor(playerid,COLOR_GRAD2);
	return 1;
}

sampCallback OnPlayerDisconnect(playerid)
{
	gActivePlayers[playerid]--;
	numplayers--;
	PlayerInfo[playerid][pAdjustable] = 1;
	OnPlayerUpdate(playerid);
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
	    if(IsPlayerConnected(i))
	    {
	        if(TaxiAccepted[i] < 999)
	        {
		        if(TaxiAccepted[i] == playerid)
		        {
		            TaxiAccepted[i] = 999;
		            GameTextForPlayer(i, "~w~Taxi Caller~n~~r~Left the game", 5000, 1);
		            TaxiCallTime[i] = 0;
		            DisablePlayerCheckpoint(i);
		        }
	        }
	        else if(BusAccepted[i] < 999)
	        {
		        if(BusAccepted[i] == playerid)
		        {
		            BusAccepted[i] = 999;
		            GameTextForPlayer(i, "~w~Bus Caller~n~~r~Left the game", 5000, 1);
		            BusCallTime[i] = 0;
		            DisablePlayerCheckpoint(i);
		        }
	        }
	    }
	}
	if(GettingCK[playerid] < 999)
	{
	    if(IsPlayerConnected(GettingCK[playerid]))
	    {
	        SendClientMessage(GettingCK[playerid], COLOR_YELLOW, "Your Character Kill has left the server, try again later.");
	        OnCK[GettingCK[playerid]] = 999;
	    }
	}
	if(TransportCost[playerid] > 0 && TransportDriver[playerid] < 999)
	{
	    if(IsPlayerConnected(TransportDriver[playerid]))
		{
		    new string[64];
		    TransportMoney[TransportDriver[playerid]] += TransportCost[playerid];
		    TransportTime[TransportDriver[playerid]] = 0;
		    TransportCost[TransportDriver[playerid]] = 0;
		    format(string, sizeof(string), "~w~Passenger left~n~~g~Earned $%d",TransportCost[playerid]);
		    GameTextForPlayer(TransportDriver[playerid], string, 5000, 1);
		}
	}
	if(GotHit[playerid] > 0)
	{
	    if(GetChased[playerid] < 999)
	    {
	        if(IsPlayerConnected(GetChased[playerid]))
	        {
	        	SendClientMessage(GetChased[playerid], COLOR_YELLOW, "Your Hit has left the server.");
	            GoChase[GetChased[playerid]] = 999;
			}
	    }
	}
	if(PlayerPaintballing[playerid] != 0)
	{
	    PaintballPlayers --;
	}
	if(PlayerKarting[playerid] > 0 && PlayerInKart[playerid] > 0)
	{
	    KartingPlayers --;
	}
	if(HireCar[playerid] != 299)
	{
		gLastDriver[HireCar[playerid]] = 300;
		gCarLock[HireCar[playerid]] = 0;
		UnLockCar(HireCar[playerid]);
	}
	if (gLastCar[playerid] > 0)
	{
		gLastDriver[gLastCar[playerid]] = 300;
		if(PlayerInfo[playerid][pPhousekey] != gLastCar[playerid]-1)
		{
			gCarLock[gLastCar[playerid]] = 0;
			UnLockCar(gLastCar[playerid]);
		}
	}
	if(PlayerBoxing[playerid] > 0)
	{
	    if(Boxer1 == playerid)
	    {
	        if(IsPlayerConnected(Boxer2))
	        {
	        	PlayerBoxing[Boxer2] = 0;
	        	SetPlayerPos(Boxer2, 765.8433,3.2924,1000.7186);
	        	SetPlayerInterior(Boxer2, 5);
	        	GameTextForPlayer(Boxer2, "~r~Match interupted", 5000, 1);
			}
	    }
	    else if(Boxer2 == playerid)
	    {
	        if(IsPlayerConnected(Boxer1))
	        {
	        	PlayerBoxing[Boxer1] = 0;
	        	SetPlayerPos(Boxer1, 765.8433,3.2924,1000.7186);
	        	SetPlayerInterior(Boxer1, 5);
	        	GameTextForPlayer(Boxer1, "~r~Match interupted", 5000, 1);
			}
	    }
	    InRing = 0;
     	RoundStarted = 0;
		Boxer1 = 255;
		Boxer2 = 255;
		TBoxer = 255;
	}
    if(TransportDuty[playerid] == 1)
	{
		TaxiDrivers -= 1;
	}
    else if(TransportDuty[playerid] == 2)
	{
		BusDrivers -= 1;
	}
	if(PlayerInfo[playerid][pJob] == 11)
	{
	    if(JobDuty[playerid] == 1) { Medics -= 1; }
	}
	else if(PlayerInfo[playerid][pJob] == 7)
	{
	    if(JobDuty[playerid] == 1) { Mechanics -= 1; }
	}
	return 1;
}

sampCallback OnPlayerSpawn(playerid)
{
	InitLockDoors(playerid);
	STDPlayer[playerid] = 0;
	gTeam[playerid] = PlayerInfo[playerid][pTeam]; //Set the Team
	if (gTeam[playerid] == 4) //medic / criminal reset team
	{
		gTeam[playerid] = 3;
	}
	if(gPlayerLogged[playerid] == 0)
	{
    	SendClientMessage(playerid, COLOR_LIGHTRED, "** This server requires a Login BEFORE spawn (Kicked) **");
        KickPlayer[playerid] = 1;
 	}
	if(gTeam[playerid] == 11 && PlayerInfo[playerid][pLeader] < 1)
	{
	    MedicBill[playerid] = 0;
	    new rand = random(sizeof(CIV));
		SendClientMessage(playerid, COLOR_LIGHTRED, "You are not an Approved Leader, you are now a Civilian !");
		PlayerInfo[playerid][pTeam] = 3;
		gTeam[playerid] = 3;
		SetSpawnInfo(playerid, gTeam[playerid], CIV[rand],0.0,0.0,0.0,0,0,0,0,0,0,0);
		PlayerInfo[playerid][pModel] = CIV[rand];
		SpawnPlayer(playerid);
	}
	if(gTeam[playerid] == 5)
	{
	    if(PlayerInfo[playerid][pMember] < 1)
	    {
	        MedicBill[playerid] = 0;
	        new rand = random(sizeof(CIV));
			SendClientMessage(playerid, COLOR_LIGHTRED, "You are not a Family Member, you are now a Civilian !");
			PlayerInfo[playerid][pTeam] = 3;
			gTeam[playerid] = 3;
            SetSpawnInfo(playerid, gTeam[playerid], CIV[rand],0.0,0.0,0.0,0,0,0,0,0,0,0);
			PlayerInfo[playerid][pModel] = CIV[rand];
			SpawnPlayer(playerid);
		}
	}
	if(gTeam[playerid] == 10)
	{
	    if(PlayerInfo[playerid][pMember] != 8)
	    {
	        MedicBill[playerid] = 0;
	        new rand = random(sizeof(CIV));
			SendClientMessage(playerid, COLOR_LIGHTRED, "You are not a Member of this Agency, you are now a Civilian !");
			PlayerInfo[playerid][pTeam] = 3;
			gTeam[playerid] = 3;
            SetSpawnInfo(playerid, gTeam[playerid], CIV[rand],0.0,0.0,0.0,0,0,0,0,0,0,0);
			PlayerInfo[playerid][pModel] = CIV[rand];
			SpawnPlayer(playerid);
		}
	}
	if(gTeam[playerid] == 2 && PlayerInfo[playerid][pMember] > 3)
	{
	    MedicBill[playerid] = 0;
		new rand = random(sizeof(CIV));
		SendClientMessage(playerid, COLOR_LIGHTRED, "You haven't applied for being an Officer / FBI / National Guard, you are now a Civilian !");
		PlayerInfo[playerid][pTeam] = 3;
		gTeam[playerid] = 3;
		SetSpawnInfo(playerid, gTeam[playerid], CIV[rand],0.0,0.0,0.0,0,0,0,0,0,0,0);
		PlayerInfo[playerid][pModel] = CIV[rand];
		SpawnPlayer(playerid);
	}
	if(gTeam[playerid] == 3)
	{
	    if(PlayerInfo[playerid][pMember] > 0 || PlayerInfo[playerid][pLeader] > 0)
	    {
			SendClientMessage(playerid, COLOR_LIGHTRED, "You are part of a Family/Force, you've been forced to the right Class + Char !");
			MedicBill[playerid] = 0;
			new model = PlayerInfo[playerid][pChar];
			if(PlayerInfo[playerid][pMember] == 1) { SetSpawnInfo(playerid, 2, model,0.0,0.0,0.0,0,0,0,0,0,0,0); PlayerInfo[playerid][pTeam] = 2; gTeam[playerid] = 2; PlayerInfo[playerid][pModel] = model; }
			else if(PlayerInfo[playerid][pMember] == 2) { SetSpawnInfo(playerid, 2, model,0.0,0.0,0.0,0,0,0,0,0,0,0); PlayerInfo[playerid][pTeam] = 2; gTeam[playerid] = 2; PlayerInfo[playerid][pModel] = model; }
			else if(PlayerInfo[playerid][pMember] == 3) { SetSpawnInfo(playerid, 2, model,0.0,0.0,0.0,0,0,0,0,0,0,0); PlayerInfo[playerid][pTeam] = 2; gTeam[playerid] = 2; PlayerInfo[playerid][pModel] = model; }
			else if(PlayerInfo[playerid][pMember] == 4) { SetSpawnInfo(playerid, 1, model,0.0,0.0,0.0,0,0,0,0,0,0,0); PlayerInfo[playerid][pTeam] = 1; gTeam[playerid] = 1; PlayerInfo[playerid][pModel] = model; }
			else if(PlayerInfo[playerid][pMember] == 5) { SetSpawnInfo(playerid, 5, model,0.0,0.0,0.0,0,0,0,0,0,0,0); PlayerInfo[playerid][pTeam] = 5; gTeam[playerid] = 5; PlayerInfo[playerid][pModel] = model; }
			else if(PlayerInfo[playerid][pMember] == 6) { SetSpawnInfo(playerid, 5, model,0.0,0.0,0.0,0,0,0,0,0,0,0); PlayerInfo[playerid][pTeam] = 5; gTeam[playerid] = 5; PlayerInfo[playerid][pModel] = model; }
			else if(PlayerInfo[playerid][pMember] == 8) { SetSpawnInfo(playerid, 10, model,0.0,0.0,0.0,0,0,0,0,0,0,0); PlayerInfo[playerid][pTeam] = 10; gTeam[playerid] = 10; PlayerInfo[playerid][pModel] = model; }
			else if(PlayerInfo[playerid][pMember] == 9) { SetSpawnInfo(playerid, 12, model,0.0,0.0,0.0,0,0,0,0,0,0,0); PlayerInfo[playerid][pTeam] = 12; gTeam[playerid] = 12; PlayerInfo[playerid][pModel] = model; }
			else if(PlayerInfo[playerid][pMember] == 10) { SetSpawnInfo(playerid, 12, model,0.0,0.0,0.0,0,0,0,0,0,0,0); PlayerInfo[playerid][pTeam] = 12; gTeam[playerid] = 12; PlayerInfo[playerid][pModel] = model; }
			else if(PlayerInfo[playerid][pMember] == 11) { SetSpawnInfo(playerid, 12, model,0.0,0.0,0.0,0,0,0,0,0,0,0); PlayerInfo[playerid][pTeam] = 12; gTeam[playerid] = 12; PlayerInfo[playerid][pModel] = model; }
			else if(PlayerInfo[playerid][pLeader] == 1) { SetSpawnInfo(playerid, 11, model,0.0,0.0,0.0,0,0,0,0,0,0,0); PlayerInfo[playerid][pTeam] = 11; gTeam[playerid] = 11; PlayerInfo[playerid][pModel] = model; }
			else if(PlayerInfo[playerid][pLeader] == 2) { SetSpawnInfo(playerid, 11, model,0.0,0.0,0.0,0,0,0,0,0,0,0); PlayerInfo[playerid][pTeam] = 11; gTeam[playerid] = 11; PlayerInfo[playerid][pModel] = model; }
			else if(PlayerInfo[playerid][pLeader] == 3) { SetSpawnInfo(playerid, 11, model,0.0,0.0,0.0,0,0,0,0,0,0,0); PlayerInfo[playerid][pTeam] = 11; gTeam[playerid] = 11; PlayerInfo[playerid][pModel] = model; }
			else if(PlayerInfo[playerid][pLeader] == 4) { SetSpawnInfo(playerid, 11, model,0.0,0.0,0.0,0,0,0,0,0,0,0); PlayerInfo[playerid][pTeam] = 11; gTeam[playerid] = 11; PlayerInfo[playerid][pModel] = model; }
			else if(PlayerInfo[playerid][pLeader] == 5) { SetSpawnInfo(playerid, 11, model,0.0,0.0,0.0,0,0,0,0,0,0,0); PlayerInfo[playerid][pTeam] = 11; gTeam[playerid] = 11; PlayerInfo[playerid][pModel] = model; }
			else if(PlayerInfo[playerid][pLeader] == 6) { SetSpawnInfo(playerid, 11, model,0.0,0.0,0.0,0,0,0,0,0,0,0); PlayerInfo[playerid][pTeam] = 11; gTeam[playerid] = 11; PlayerInfo[playerid][pModel] = model; }
			else if(PlayerInfo[playerid][pLeader] == 7) { SetSpawnInfo(playerid, 11, model,0.0,0.0,0.0,0,0,0,0,0,0,0); PlayerInfo[playerid][pTeam] = 11; gTeam[playerid] = 11; PlayerInfo[playerid][pModel] = model; }
			else if(PlayerInfo[playerid][pLeader] == 8) { SetSpawnInfo(playerid, 11, model,0.0,0.0,0.0,0,0,0,0,0,0,0); PlayerInfo[playerid][pTeam] = 11; gTeam[playerid] = 11; PlayerInfo[playerid][pModel] = model; }
			else if(PlayerInfo[playerid][pLeader] == 9) { SetSpawnInfo(playerid, 11, model,0.0,0.0,0.0,0,0,0,0,0,0,0); PlayerInfo[playerid][pTeam] = 11; gTeam[playerid] = 11; PlayerInfo[playerid][pModel] = model; }
			else if(PlayerInfo[playerid][pLeader] == 10) { SetSpawnInfo(playerid, 11, model,0.0,0.0,0.0,0,0,0,0,0,0,0); PlayerInfo[playerid][pTeam] = 11; gTeam[playerid] = 11; PlayerInfo[playerid][pModel] = model; }
			else if(PlayerInfo[playerid][pLeader] == 11) { SetSpawnInfo(playerid, 11, model,0.0,0.0,0.0,0,0,0,0,0,0,0); PlayerInfo[playerid][pTeam] = 11; gTeam[playerid] = 11; PlayerInfo[playerid][pModel] = model; }
			//SetSpawnInfo(playerid, team, model,0.0,0.0,0.0,0,0,0,0,0,0,0);
			SpawnPlayer(playerid);
		}
	}
	if(PlayerInfo[playerid][pChar] > 0) { SetPlayerSkin(playerid, PlayerInfo[playerid][pChar]); }
	else { SetPlayerSkin(playerid, PlayerInfo[playerid][pModel]); }
	SetPlayerWeapons(playerid);
	SetPlayerSpawn(playerid);
	SetPlayerToTeamColor(playerid);
	PlayerFixRadio(playerid);
	for(new i = 0; i < sizeof(Turfs); i++)
	{
	    GangZoneShowForPlayer(playerid, i, TurfInfo[i][zColor]);
	}
	if(MapIconsShown[playerid] != 1)
	{
	    MapIconsShown[playerid] = 1;
	    for(new i = 0; i < sizeof(BizzInfo); i++)
		{
			SetPlayerMapIcon(playerid,i + 1,BizzInfo[i][bEntranceX],BizzInfo[i][bEntranceY],BizzInfo[i][bEntranceZ],36,COLOR_LIGHTRED);
		}
		for(new i = 0; i < sizeof(SBizzInfo); i++)
		{
		    SetPlayerMapIcon(playerid,i + 20,SBizzInfo[i][sbEntranceX],SBizzInfo[i][sbEntranceY],SBizzInfo[i][sbEntranceZ],36,COLOR_LIGHTRED);
		}
	}
	return 1;
}

sampCallback OnPlayerDeath(playerid, killerid, reason)
{
	new name[MAX_PLAYER_NAME];
	new string[256];
	//new dmessage[128];
	//new deathreason[20];
	new playercash;
	new victimteam;
	new Float:px,Float:py,Float:pz;
	new killerteam;

	victimteam = gTeam[playerid];
	killerteam = gTeam[killerid];
	gPlayerSpawned[playerid] = 0;
	GetPlayerName(playerid, name, sizeof(name));
	PlayerInfo[playerid][pLocal] = 255;
	GetPlayerPos(playerid, px, py, pz);
	if(killerid != 255)
	{
		if(GetPlayerState(killerid) == 2)
		{
			SendClientMessage(killerid, COLOR_YELLOW, "DriveBy Kill, dont abuse it, On foot gets you $$$!");
			return 1;
		}
	}
	if(reason == 38)
	{
		new kstring[128];
		new kickname[MAX_PLAYER_NAME];
		if(IsPlayerConnected(killerid))
		{
			GetPlayerName(killerid, kickname, sizeof(kickname));
			format(string, 256, "AdmWarning: [%d]%s just killed a player with minigun, be sure he's not fake-killing.",killerid,kickname);
			ABroadCast(COLOR_YELLOW,string,1);
			printf("%s", kstring);
		}
	}
	if (gPlayerCheckpointStatus[playerid] > 4 && gPlayerCheckpointStatus[playerid] < 11)
	{
		DisablePlayerCheckpoint(playerid);
		gPlayerCheckpointStatus[playerid] = CHECKPOINT_NONE;
	}
	new caller = Mobile[playerid];
	if(caller != 255)
	{
		if(caller < 255)
		{
			SendClientMessage(caller,  COLOR_GRAD2, "   The line just went dead....");
			CellTime[caller] = 0;
			CellTime[playerid] = 0;
			Mobile[caller] = 255;
		}
		Mobile[playerid] = 255;
		CellTime[playerid] = 0;
	}
	ClearCrime(playerid);
	if(PlayerPaintballing[playerid] != 0)
	{
	    PlayerPaintballKills[killerid] ++;
	    if(PlayerPaintballKills[killerid] > PaintballWinnerKills)
	    {
	        new killer[MAX_PLAYER_NAME];
	        PaintballWinner = killerid;
	        PaintballWinnerKills = PlayerPaintballKills[killerid];
	        GetPlayerName(killerid, killer, sizeof(killer));
	        for(new i = 0; i < MAX_PLAYERS; i++)
	        {
	            if(IsPlayerConnected(i))
	            {
	                if(PlayerPaintballing[i] != 0)
	                {
	                    format(string, sizeof(string), "* %s is in the lead with %d Kills.",killer,PaintballWinnerKills);
						SendClientMessage(i, COLOR_WHITE, string);
	                }
	            }
	        }
	    }
	    return 1;
	}
	if(GettingCK[playerid] < 999 || OnCK[playerid] < 999)
	{
	    if(IsPlayerConnected(killerid))
	    {
	        if(GettingCK[killerid] < 999 || OnCK[playerid] < 999)
	        {
	            new killer[MAX_PLAYER_NAME];
	            new dier[MAX_PLAYER_NAME];
	            GetPlayerName(playerid, dier, sizeof(dier));
				GetPlayerName(killerid, killer, sizeof(killer));
	            format(string, sizeof(string), "* %s has performed a Character Kill on you, you aren't able to play with this Character anymore.",killer);
	            SendClientMessage(playerid, COLOR_LIGHTRED, string);
	            format(string, sizeof(string), "** %s has Character Killed %s **",killer,dier);
	            CKLog(string);
	            PlayerInfo[playerid][pCK] = 1;
	            if(GettingCK[playerid] < 999) { GettingCK[playerid] = 999; }
	            else if(OnCK[playerid] < 999) { OnCK[playerid] = 999; }
	            if(GettingCK[killerid] < 999) { GettingCK[killerid] = 999; }
	            else if(OnCK[killerid] < 999) { OnCK[killerid] = 999; }
	            KickPlayer[playerid] = 1;
	        }
	    }
	}
	if(PlayerInfo[playerid][pHeadValue] > 0)
	{
	    if(IsPlayerConnected(killerid))
	    {
		    if(gTeam[killerid] == 10 || PlayerInfo[killerid][pLeader] == 8)
		    {
		        if(GoChase[killerid] == playerid)
		        {
		            ConsumingMoney[killerid] = 1;
					new killer[MAX_PLAYER_NAME];
					GetPlayerName(killerid, killer, sizeof(killer));
					GivePlayerMoney(killerid, PlayerInfo[playerid][pHeadValue]);
					format(string,128,"<< Hitman %s has fulfilled the contract on %s and collected $%d >>",killer,name,PlayerInfo[playerid][pHeadValue]);
					SendFamilyMessage(8, COLOR_YELLOW, string);
					PlayerInfo[playerid][pHeadValue] = 0;
					GotHit[playerid] = 0;
					GetChased[playerid] = 999;
					GoChase[killerid] = 999;
				}
			}
		}
	}
	if(victimteam >= 4)
	{
	    if(IsPlayerConnected(killerid))
	    {
			//new killer[MAX_PLAYER_NAME];
			//GetPlayerName(killerid, killer, sizeof(killer));
			new slice = 100; //$100
			playercash = GetPlayerMoney(playerid);
			if(gTeam[killerid] != 2) { WantedPoints[killerid] += 2; } //+ 2 wanted points
			if(SafeTime[playerid] <= 0)
			{
				if(gTeam[killerid] != gTeam[playerid])
				{
					if(GetPlayerState(killerid) == 1)
					{
						PlayerInfo[killerid][pKills] = PlayerInfo[killerid][pKills] + 2;
					}
					else
					{
						PlayerInfo[killerid][pKills]++;
					}
					PlayerInfo[playerid][pKills]--;
				}
			}
			/*if (strlen(deathreason) > 0)// patch
			{
				if (((gTeam[killerid]) == 1) || ((gTeam[killerid]) == 3 && civnokill) || gTeam[killerid] == gTeam[playerid])//med kill criminal
				{
					format(string, sizeof(string), ".: %s murdered %s. (%s) :.", killer, name, deathreason);
				}
				else
				{
					format(string, sizeof(string), ".: %s murdered %s. (%s) for $%d :.", killer, name, deathreason, slice);
				}

			}
			else
			{
				if (((gTeam[killerid]) == 1) || ((gTeam[killerid]) == 3 && civnokill || gTeam[killerid] == gTeam[playerid]))
				{
					format(string, sizeof(string), ".: %s murdered %s :.", killer, name);
				}
				else
				{
					format(string, sizeof(string), ".: %s murdered %s for $%d :.", killer, name, slice);
				}
			}*/
			if (((gTeam[killerid]) == 1) || ((gTeam[killerid]) == 3 && civnokill) || (gTeam[killerid] == gTeam[playerid] && gTeam[playerid] != 4))
			{
				slice = 0;
			}
			if (((gTeam[killerid]) != 4) && ((gTeam[killerid]) == gTeam[playerid]))//no team kill
			{
				slice = 0;
			}
			if (playercash > 0)
			{
				GivePlayerMoney(playerid, -slice);
			}
			else
			{
				slice = slice+500;
			}
			GivePlayerMoney(killerid, slice);
			//GameTextForPlayer(playerid, dmessage, 5000, 2);
			PlayerPlaySound(killerid, 1083, 0.0, 0.0, 0.0);
			if (((gTeam[killerid]) == 3) && reason != 49)
			{
				SetPlayerCriminal(killerid,255, "First Degree Murder");
			}
			else if (((gTeam[killerid]) == 3) && reason == 49)
			{
				SetPlayerCriminal(killerid,255, "Hit And Run");
			}
		}
	}
	else if (victimteam == 2)
	{
	    if(IsPlayerConnected(killerid))
	    {
			//new killer[MAX_PLAYER_NAME];
			//GetPlayerName(killerid, killer, sizeof(killer));
			// Cop kill
			PlayerInfo[playerid][pKills]--;
			if (gTeam[killerid] == 2)//cops kill cop
			{
				//format(string,128,".: Officer %s murdered Officer %s (%s) and was sued for $%d :.",killer,name,deathreason,suecost);
				PlayerPlaySound(killerid, 1084, 0.0, 0.0, 0.0);
				GivePlayerMoney(killerid, -suecost);
				GivePlayerMoney(playerid, suecost+100);//+100pays hospital bill
			}
			else
			{
				//format(string,128,".: %s murdered Officer %s (%s) :.",killer,name,deathreason);
		    }
			if (gTeam[killerid] >= 3)
			{
			    WantedPoints[killerid] += 2; //+ 2 wanted points
				if(reason != 49)
				{
					SetPlayerCriminal(killerid,255, "First Degree Murder");
				}
				else if (reason == 49)
				{
					SetPlayerCriminal(killerid,255, "Hit And Run");
				}
			}
			if(gTeam[killerid] >= 5 && SafeTime[playerid] <= 0)
			{
				if(GetPlayerState(killerid) == 1)
				{
					PlayerInfo[killerid][pKills] = PlayerInfo[killerid][pKills]+2;
				}
				else
				{
					PlayerInfo[killerid][pKills]++;
				}
				WantedPoints[killerid]+=2;
			}
			//BroadCast(COLOR_RED, string);
		}
	}
	else if (victimteam == 3)
	{
	    if(IsPlayerConnected(killerid))
	    {
			//new killer[MAX_PLAYER_NAME];
			//GetPlayerName(killerid, killer, sizeof(killer));
			// Civ kill
			if ((gTeam[killerid]) == 2)//cops kill civ
			{
			    if(WantedLevel[playerid] < 1)
			    {
					//format(string,128,".: Officer %s murdered %s (%s) and was sued for $%d :.",killer,name,deathreason,suecost);
					PlayerPlaySound(killerid, 1084, 0.0, 0.0, 0.0);
					GivePlayerMoney(killerid, -suecost);
					GivePlayerMoney(playerid, suecost+100);//+100pays hospital bill
				}
			}
			else
			{
				//format(string,128,".: %s murdered %s (%s) :.",killer,name,deathreason);
				WantedPoints[killerid] += 2;
		    }
			if (((gTeam[killerid]) >= 3 || (gTeam[killerid]) == 1) && reason != 49)
			{
				SetPlayerCriminal(killerid,255, "First Degree Murder");
			}
			else if (((gTeam[killerid]) >= 3 || (gTeam[killerid]) == 1) && reason == 49)
			{
				SetPlayerCriminal(killerid,255, "Hit And Run");
			}
		    //BroadCast(COLOR_RED, string);
		}
	}
	else if (victimteam == 1)
	{
	    if(IsPlayerConnected(killerid))
	    {
			//new killer[MAX_PLAYER_NAME];
			//GetPlayerName(killerid, killer, sizeof(killer));
			// Civ kill
			if ((gTeam[killerid]) == 2)//cops kill civ
			{
				//format(string,128,".: Officer %s murdered Paramedic %s (%s) and was sued for $%d :.",killer,name,deathreason,suecost);
				PlayerPlaySound(killerid, 1084, 0.0, 0.0, 0.0);
				GivePlayerMoney(killerid, -suecost);
				GivePlayerMoney(playerid, suecost+100);//+100pays hospital bill
			}
			else if ((gTeam[killerid]) == 1)//med kill civ
			{
				//format(string,128,".: Paramedic %s murdered %s (%s) and was sued for $%d :.",killer,name,deathreason,suecost);
				PlayerPlaySound(killerid, 1084, 0.0, 0.0, 0.0);
				GivePlayerMoney(killerid, -suecost);
				GivePlayerMoney(playerid, suecost+100);//+100pays hospital bill
			}
			else
			{
				//format(string,128,".: %s murdered %s (%s) :.",killer,name,deathreason);
		    }
			if (((gTeam[killerid]) == 4) && reason != 49)
			{
				SetPlayerCriminal(killerid,255, "First Degree Murder");
			}
			else if (((gTeam[killerid]) == 3) && reason == 49)
			{
				SetPlayerCriminal(killerid,255, "Hit And Run");
			}
		    //BroadCast(COLOR_RED, string);
		}
	}
	if (victimteam >= 3 && WantedPoints[playerid] > 0 && killerteam == 2)
	{
	    SetPlayerFree(playerid,killerid, "Got Killed");
	}
	killerid = INVALID_PLAYER_ID;
	SetPlayerColor(playerid,COLOR_GRAD2);
	return 1;
}

sampCallback OnVehicleSpawn(vehicleid)
{
	return 1;
}

sampCallback OnVehicleDeath(vehicleid, killerid)
{
	return 1;
}

sampCallback OnPlayerText(playerid, text[])
{
	new giver[MAX_PLAYER_NAME];
	new sendername[MAX_PLAYER_NAME];
	new giveplayer[MAX_PLAYER_NAME];
	new tmp[256];
	new string[256];
	new giveplayerid;
	if(PlayerInfo[playerid][pMuted] == 1)
	{
		SendClientMessage(playerid, TEAM_CYAN_COLOR, "You cannot speak, you have been silenced");
		return 0;
	}
	if(SelectChar[playerid] == 255)
	{
	    new idx;
	    tmp = strtok(text, idx);
	    if ((strcmp("next", tmp, true, strlen(tmp)) == 0) && (strlen(tmp) == strlen("next")))
		{
		    switch (SelectCharID[playerid])
			{
				case 1: //Police Force
				{
				    if(SelectCharPlace[playerid] == 1) { SetPlayerSkin(playerid, JoinPed[0][0]); SelectCharPlace[playerid] = 2; ChosenSkin[playerid] = JoinPed[0][0]; }
				    else if(SelectCharPlace[playerid] == 2) { SetPlayerSkin(playerid, JoinPed[1][0]); SelectCharPlace[playerid] = 3; ChosenSkin[playerid] = JoinPed[1][0]; }
				    else if(SelectCharPlace[playerid] == 3) { SetPlayerSkin(playerid, JoinPed[2][0]); SelectCharPlace[playerid] = 4; ChosenSkin[playerid] = JoinPed[2][0]; }
				    else if(SelectCharPlace[playerid] == 4) { SetPlayerSkin(playerid, JoinPed[3][0]); SelectCharPlace[playerid] = 5; ChosenSkin[playerid] = JoinPed[3][0]; }
				    else if(SelectCharPlace[playerid] == 5) { SetPlayerSkin(playerid, JoinPed[4][0]); SelectCharPlace[playerid] = 6; ChosenSkin[playerid] = JoinPed[4][0]; }
				    else if(SelectCharPlace[playerid] == 6) { SetPlayerSkin(playerid, JoinPed[5][0]); SelectCharPlace[playerid] = 7; ChosenSkin[playerid] = JoinPed[5][0]; }
				    else if(SelectCharPlace[playerid] == 7) { SetPlayerSkin(playerid, JoinPed[6][0]); SelectCharPlace[playerid] = 8; ChosenSkin[playerid] = JoinPed[6][0]; }
				    else if(SelectCharPlace[playerid] == 8) { SetPlayerSkin(playerid, JoinPed[7][0]); SelectCharPlace[playerid] = 9; ChosenSkin[playerid] = JoinPed[7][0]; }
				    else if(SelectCharPlace[playerid] == 9) { SetPlayerSkin(playerid, JoinPed[8][0]); SelectCharPlace[playerid] = 10; ChosenSkin[playerid] = JoinPed[8][0]; }
				    else if(SelectCharPlace[playerid] == 10) { SetPlayerSkin(playerid, JoinPed[9][0]); SelectCharPlace[playerid] = 11; ChosenSkin[playerid] = JoinPed[9][0]; }
				    else if(SelectCharPlace[playerid] == 11) { SetPlayerSkin(playerid, JoinPed[10][0]); SelectCharPlace[playerid] = 1; ChosenSkin[playerid] = JoinPed[10][0]; }
				}
				case 2: //FBI/ATF
				{
				    if(SelectCharPlace[playerid] == 1) { SetPlayerSkin(playerid, JoinPed[11][0]); SelectCharPlace[playerid] = 2; ChosenSkin[playerid] = JoinPed[11][0]; }
				    else if(SelectCharPlace[playerid] == 2) { SetPlayerSkin(playerid, JoinPed[12][0]); SelectCharPlace[playerid] = 3; ChosenSkin[playerid] = JoinPed[12][0]; }
				    else if(SelectCharPlace[playerid] == 3) { SetPlayerSkin(playerid, JoinPed[13][0]); SelectCharPlace[playerid] = 1; ChosenSkin[playerid] = JoinPed[13][0]; }
    			}
				case 3: //National Guard
				{
				    if(SelectCharPlace[playerid] == 1) { SetPlayerSkin(playerid, JoinPed[14][0]); SelectCharPlace[playerid] = 2; ChosenSkin[playerid] = JoinPed[14][0]; }
				    else if(SelectCharPlace[playerid] == 2) { SetPlayerSkin(playerid, JoinPed[15][0]); SelectCharPlace[playerid] = 1; ChosenSkin[playerid] = JoinPed[15][0]; }
				}
				case 4: //Fire&Ambulance
				{
				    if(SelectCharPlace[playerid] == 1) { SetPlayerSkin(playerid, JoinPed[16][0]); SelectCharPlace[playerid] = 2; ChosenSkin[playerid] = JoinPed[16][0]; }
				    else if(SelectCharPlace[playerid] == 2) { SetPlayerSkin(playerid, JoinPed[17][0]); SelectCharPlace[playerid] = 3; ChosenSkin[playerid] = JoinPed[17][0]; }
				    else if(SelectCharPlace[playerid] == 3) { SetPlayerSkin(playerid, JoinPed[18][0]); SelectCharPlace[playerid] = 4; ChosenSkin[playerid] = JoinPed[18][0]; }
				    else if(SelectCharPlace[playerid] == 4) { SetPlayerSkin(playerid, JoinPed[19][0]); SelectCharPlace[playerid] = 5; ChosenSkin[playerid] = JoinPed[19][0]; }
				    else if(SelectCharPlace[playerid] == 5) { SetPlayerSkin(playerid, JoinPed[20][0]); SelectCharPlace[playerid] = 6; ChosenSkin[playerid] = JoinPed[20][0]; }
				    else if(SelectCharPlace[playerid] == 6) { SetPlayerSkin(playerid, JoinPed[21][0]); SelectCharPlace[playerid] = 7; ChosenSkin[playerid] = JoinPed[21][0]; }
				    else if(SelectCharPlace[playerid] == 7) { SetPlayerSkin(playerid, JoinPed[22][0]); SelectCharPlace[playerid] = 1; ChosenSkin[playerid] = JoinPed[22][0]; }
				}
				case 5: //La Cosa Nostra
				{
				    if(SelectCharPlace[playerid] == 1) { SetPlayerSkin(playerid, JoinPed[23][0]); SelectCharPlace[playerid] = 2; ChosenSkin[playerid] = JoinPed[23][0]; }
				    else if(SelectCharPlace[playerid] == 2) { SetPlayerSkin(playerid, JoinPed[24][0]); SelectCharPlace[playerid] = 3; ChosenSkin[playerid] = JoinPed[24][0]; }
				    else if(SelectCharPlace[playerid] == 3) { SetPlayerSkin(playerid, JoinPed[25][0]); SelectCharPlace[playerid] = 4; ChosenSkin[playerid] = JoinPed[25][0]; }
				    else if(SelectCharPlace[playerid] == 4) { SetPlayerSkin(playerid, JoinPed[26][0]); SelectCharPlace[playerid] = 5; ChosenSkin[playerid] = JoinPed[26][0]; }
				    else if(SelectCharPlace[playerid] == 5) { SetPlayerSkin(playerid, JoinPed[27][0]); SelectCharPlace[playerid] = 6; ChosenSkin[playerid] = JoinPed[27][0]; }
				    else if(SelectCharPlace[playerid] == 6) { SetPlayerSkin(playerid, JoinPed[28][0]); SelectCharPlace[playerid] = 7; ChosenSkin[playerid] = JoinPed[28][0]; }
				    else if(SelectCharPlace[playerid] == 7) { SetPlayerSkin(playerid, JoinPed[29][0]); SelectCharPlace[playerid] = 8; ChosenSkin[playerid] = JoinPed[29][0]; }
				    else if(SelectCharPlace[playerid] == 8) { SetPlayerSkin(playerid, JoinPed[30][0]); SelectCharPlace[playerid] = 1; ChosenSkin[playerid] = JoinPed[30][0]; }
				}
				case 6: //Yakuza
				{
				    if(SelectCharPlace[playerid] == 1) { SetPlayerSkin(playerid, JoinPed[31][0]); SelectCharPlace[playerid] = 2; ChosenSkin[playerid] = JoinPed[31][0]; }
				    else if(SelectCharPlace[playerid] == 2) { SetPlayerSkin(playerid, JoinPed[32][0]); SelectCharPlace[playerid] = 3; ChosenSkin[playerid] = JoinPed[32][0]; }
				    else if(SelectCharPlace[playerid] == 3) { SetPlayerSkin(playerid, JoinPed[33][0]); SelectCharPlace[playerid] = 4; ChosenSkin[playerid] = JoinPed[33][0]; }
				    else if(SelectCharPlace[playerid] == 4) { SetPlayerSkin(playerid, JoinPed[34][0]); SelectCharPlace[playerid] = 5; ChosenSkin[playerid] = JoinPed[34][0]; }
				    else if(SelectCharPlace[playerid] == 5) { SetPlayerSkin(playerid, JoinPed[35][0]); SelectCharPlace[playerid] = 6; ChosenSkin[playerid] = JoinPed[35][0]; }
				    else if(SelectCharPlace[playerid] == 6) { SetPlayerSkin(playerid, JoinPed[36][0]); SelectCharPlace[playerid] = 7; ChosenSkin[playerid] = JoinPed[36][0]; }
				    else if(SelectCharPlace[playerid] == 7) { SetPlayerSkin(playerid, JoinPed[37][0]); SelectCharPlace[playerid] = 1; ChosenSkin[playerid] = JoinPed[37][0]; }
				}
				case 8: //Hitman Agency
				{
				    if(SelectCharPlace[playerid] == 1) { SetPlayerSkin(playerid, JoinPed[38][0]); SelectCharPlace[playerid] = 2; ChosenSkin[playerid] = JoinPed[38][0]; }
				    else if(SelectCharPlace[playerid] == 2) { SetPlayerSkin(playerid, JoinPed[39][0]); SelectCharPlace[playerid] = 3; ChosenSkin[playerid] = JoinPed[39][0]; }
				    else if(SelectCharPlace[playerid] == 3) { SetPlayerSkin(playerid, JoinPed[40][0]); SelectCharPlace[playerid] = 4; ChosenSkin[playerid] = JoinPed[40][0]; }
				    else if(SelectCharPlace[playerid] == 4) { SetPlayerSkin(playerid, JoinPed[41][0]); SelectCharPlace[playerid] = 5; ChosenSkin[playerid] = JoinPed[41][0]; }
				    else if(SelectCharPlace[playerid] == 5) { SetPlayerSkin(playerid, JoinPed[42][0]); SelectCharPlace[playerid] = 1; ChosenSkin[playerid] = JoinPed[42][0]; }
				}
				case 9: //News Reporters
				{
				    if(SelectCharPlace[playerid] == 1) { SetPlayerSkin(playerid, JoinPed[43][0]); SelectCharPlace[playerid] = 2; ChosenSkin[playerid] = JoinPed[43][0]; }
				    else if(SelectCharPlace[playerid] == 2) { SetPlayerSkin(playerid, JoinPed[44][0]); SelectCharPlace[playerid] = 3; ChosenSkin[playerid] = JoinPed[44][0]; }
				    else if(SelectCharPlace[playerid] == 3) { SetPlayerSkin(playerid, JoinPed[45][0]); SelectCharPlace[playerid] = 1; ChosenSkin[playerid] = JoinPed[45][0]; }
				}
				case 10: //Taxi Cab Company
				{
				    if(SelectCharPlace[playerid] == 1) { SetPlayerSkin(playerid, JoinPed[46][0]); SelectCharPlace[playerid] = 2; ChosenSkin[playerid] = JoinPed[46][0]; }
				    else if(SelectCharPlace[playerid] == 2) { SetPlayerSkin(playerid, JoinPed[47][0]); SelectCharPlace[playerid] = 1; ChosenSkin[playerid] = JoinPed[47][0]; }
				}
				case 11: //Driving/Flying School
				{
				    if(SelectCharPlace[playerid] == 1) { SetPlayerSkin(playerid, JoinPed[48][0]); SelectCharPlace[playerid] = 2; ChosenSkin[playerid] = JoinPed[48][0]; }
				    else if(SelectCharPlace[playerid] == 2) { SetPlayerSkin(playerid, JoinPed[49][0]); SelectCharPlace[playerid] = 3; ChosenSkin[playerid] = JoinPed[49][0]; }
				    else if(SelectCharPlace[playerid] == 3) { SetPlayerSkin(playerid, JoinPed[50][0]); SelectCharPlace[playerid] = 4; ChosenSkin[playerid] = JoinPed[50][0]; }
				    else if(SelectCharPlace[playerid] == 4) { SetPlayerSkin(playerid, JoinPed[51][0]); SelectCharPlace[playerid] = 1; ChosenSkin[playerid] = JoinPed[51][0]; }
				}
			}
		    return 0;
		}
		else if ((strcmp("done", tmp, true, strlen(tmp)) == 0) && (strlen(tmp) == strlen("done")))
		{
		    if(ChangePos2[playerid][1] == 1)
		    {
		        SetPlayerInterior(playerid, ChangePos2[playerid][0]);
		        SetPlayerPos(playerid, ChangePos[playerid][0],ChangePos[playerid][1],ChangePos[playerid][2]);
		        ChangePos2[playerid][1] = 0;
		        return 0;
		    }
		    PlayerInfo[playerid][pModel] = ChosenSkin[playerid];
		    PlayerInfo[playerid][pChar] = ChosenSkin[playerid];
		    SetSpawnInfo(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pModel],0.0,0.0,0.0,0,0,0,0,0,0,0);
		    gTeam[playerid] = PlayerInfo[playerid][pTeam];
			SetPlayerToTeamColor(playerid);
			MedicBill[playerid] = 0;
			SpawnPlayer(playerid);
		    SelectCharPlace[playerid] = 0;
		    SelectCharID[playerid] = 0;
		    SelectChar[playerid] = 0;
		    return 0;
		}
		else
		{
		    SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Use 'next', or 'done'.");
		    return 0;
		}
	}
	if(RegistrationStep[playerid] > 0)
	{
	    if(RegistrationStep[playerid] == 1)
	    {
	        new idx;
	    	tmp = strtok(text, idx);
		    if((strcmp("male", tmp, true, strlen(tmp)) == 0) && (strlen(tmp) == strlen("male")))
			{
			    PlayerInfo[playerid][pSex] = 1;
			    SendClientMessage(playerid, COLOR_YELLOW2, "Ok, so you are a Male.");
			    SendClientMessage(playerid, COLOR_LIGHTRED, "What is your birthdate? (Use dd/mm/yyyy)");
			    RegistrationStep[playerid] = 2;
			    return 0;
			}
			else if((strcmp("female", tmp, true, strlen(tmp)) == 0) && (strlen(tmp) == strlen("female")))
			{
			    PlayerInfo[playerid][pSex] = 2;
			    SendClientMessage(playerid, COLOR_YELLOW2, "Ok, so you are a Female.");
			    SendClientMessage(playerid, COLOR_LIGHTRED, "What is your birthdate? (Use dd/mm/yyyy)");
			    RegistrationStep[playerid] = 2;
			    return 0;
			}
			else
			{
			    SendClientMessage(playerid, COLOR_LIGHTRED, "Are you a Male or Female? (Type in what you are).");
			}
			return 0;
		}
		else if(RegistrationStep[playerid] == 2)
	    {
	        new year, month,day;
			getdate(year, month, day);
	        new DateInfo[3][20];
			split(text, DateInfo, '/');
			if(year - strval(DateInfo[2]) > 100 || strval(DateInfo[2]) < 1 || strval(DateInfo[2]) >= year)
			{
			    SendClientMessage(playerid, COLOR_LIGHTRED, "What is your Birthdate? (Use dd/mm/yyyy)");
			    return 0;
			}
			new check = year - strval(DateInfo[2]);
			if(check == year)
			{
			    SendClientMessage(playerid, COLOR_LIGHTRED, "What is your Birthdate? (Use dd/mm/yyyy)");
			    return 0;
			}
			if(strval(DateInfo[1]) > month)
			{
			    check -= 1;
			}
			else if(strval(DateInfo[1]) == month && strval(DateInfo[0]) > day)
			{
			    check -= 1;
			}
			PlayerInfo[playerid][pAge] = check;
			format(string, sizeof(string), "Ok, so you are %d year old.",PlayerInfo[playerid][pAge]);
			SendClientMessage(playerid, COLOR_YELLOW2, string);
			RegistrationStep[playerid] = 3;
			SendClientMessage(playerid, COLOR_LIGHTRED, "What is your Origin? (Type in: USA, Europe or Asia)");
			return 0;
	    }
	    else if(RegistrationStep[playerid] == 3)
	    {
	        new idx;
	    	tmp = strtok(text, idx);
		    if((strcmp("usa", tmp, true, strlen(tmp)) == 0) && (strlen(tmp) == strlen("usa")))
			{
			    PlayerInfo[playerid][pOrigin] = 1;
			    SendClientMessage(playerid, COLOR_YELLOW2, "Ok, so you are from the USA.");
			    SendClientMessage(playerid, COLOR_LIGHTRED, "Thank you for filling in all the information, now you will proceed to the Tutorial.");
				RegistrationStep[playerid] = 0;
			    TutTime[playerid] = 1;
			    return 0;
			}
			else if((strcmp("europe", tmp, true, strlen(tmp)) == 0) && (strlen(tmp) == strlen("europe")))
			{
			    PlayerInfo[playerid][pOrigin] = 2;
			    SendClientMessage(playerid, COLOR_YELLOW2, "Ok, so you are from Europe.");
			    SendClientMessage(playerid, COLOR_LIGHTRED, "Thank you for filling in all the information, now you will proceed to the Tutorial.");
				RegistrationStep[playerid] = 0;
			    TutTime[playerid] = 1;
			    return 0;
			}
			else if((strcmp("asia", tmp, true, strlen(tmp)) == 0) && (strlen(tmp) == strlen("asia")))
			{
			    PlayerInfo[playerid][pOrigin] = 3;
			    SendClientMessage(playerid, COLOR_YELLOW2, "Ok, so you are from Asia.");
			    SendClientMessage(playerid, COLOR_LIGHTRED, "Thank you for filling in all the information, now you will proceed to the Tutorial.");
				RegistrationStep[playerid] = 0;
			    TutTime[playerid] = 1;
			    return 0;
			}
			else
			{
			    SendClientMessage(playerid, COLOR_LIGHTRED, "What is your Origin? (Type in: USA, Europe or Asia)");
			}
			return 0;
	    }
		return 0;
	}
	if(MarriageCeremoney[playerid] > 0)
	{
	    new idx;
	    tmp = strtok(text, idx);
	    if ((strcmp("yes", tmp, true, strlen(tmp)) == 0) && (strlen(tmp) == strlen("yes")))
		{
		    if(GotProposedBy[playerid] < 999)
		    {
			    if(IsPlayerConnected(GotProposedBy[playerid]))
				{
					GetPlayerName(playerid, sendername, sizeof(sendername));
					GetPlayerName(GotProposedBy[playerid], giveplayer, sizeof(giveplayer));
				    format(string, sizeof(string), "Priest: %s do you take %s as your lovely Wife? (type 'yes', anything else will reject the Marriage).", giveplayer,sendername);
					SendClientMessage(GotProposedBy[playerid], COLOR_WHITE, string);
					MarriageCeremoney[GotProposedBy[playerid]] = 1;
					MarriageCeremoney[playerid] = 0;
					GotProposedBy[playerid] = 999;
				    return 1;
			    }
			    else
			    {
			        MarriageCeremoney[playerid] = 0;
			        GotProposedBy[playerid] = 999;
			        return 0;
			    }
			}
			else if(ProposedTo[playerid] < 999)
			{
			    if(IsPlayerConnected(ProposedTo[playerid]))
				{
					GetPlayerName(playerid, sendername, sizeof(sendername));
					GetPlayerName(ProposedTo[playerid], giveplayer, sizeof(giveplayer));
					if(PlayerInfo[playerid][pSex] == 1 && PlayerInfo[ProposedTo[playerid]][pSex] == 2)
					{
						format(string, sizeof(string), "Priest: %s and %s i pronounce you now...Husband & Wife, you may kiss the Bride.", sendername, giveplayer);
						SendClientMessage(playerid, COLOR_WHITE, string);
				   		format(string, sizeof(string), "Priest: %s and %s i pronounce you now...Husband & Wife, you may kiss the Groom.", giveplayer, sendername);
						SendClientMessage(ProposedTo[playerid], COLOR_WHITE, string);
						format(string, sizeof(string), "Marriage News: We have a new lovely couple, %s & %s have been married.", sendername, giveplayer);
						OOCNews(COLOR_WHITE, string);
					}
					else if(PlayerInfo[playerid][pSex] == 1 && PlayerInfo[ProposedTo[playerid]][pSex] == 1)
					{
					    format(string, sizeof(string), "Priest: %s and %s i pronounce you now...Husband & Husband, you may kiss the Bride.", sendername, giveplayer);
						SendClientMessage(playerid, COLOR_WHITE, string);
				   		format(string, sizeof(string), "Priest: %s and %s i pronounce you now...Husband & Husband, you may kiss the Groom.", giveplayer, sendername);
						SendClientMessage(ProposedTo[playerid], COLOR_WHITE, string);
						format(string, sizeof(string), "Marriage News: We have a new Gay couple, %s & %s have been married.", sendername, giveplayer);
						OOCNews(COLOR_WHITE, string);
					}
					else if(PlayerInfo[playerid][pSex] == 2 && PlayerInfo[ProposedTo[playerid]][pSex] == 2)
					{
					    format(string, sizeof(string), "Priest: %s and %s i pronounce you now...Wife & Wife, you may kiss the Bride.", sendername, giveplayer);
						SendClientMessage(playerid, COLOR_WHITE, string);
				   		format(string, sizeof(string), "Priest: %s and %s i pronounce you now...Wife & Wife, you may kiss the Groom.", giveplayer, sendername);
						SendClientMessage(ProposedTo[playerid], COLOR_WHITE, string);
						format(string, sizeof(string), "Marriage News: We have a new Lesbian couple, %s & %s have been married.", sendername, giveplayer);
						OOCNews(COLOR_WHITE, string);
					}
					//MarriageCeremoney[ProposedTo[playerid]] = 1;
					MarriageCeremoney[ProposedTo[playerid]] = 0;
					MarriageCeremoney[playerid] = 0;
					format(string, sizeof(string), "%s", sendername);
					strmid(PlayerInfo[ProposedTo[playerid]][pMarriedTo], string, 0, strlen(string), 255);
					format(string, sizeof(string), "%s", giveplayer);
					strmid(PlayerInfo[playerid][pMarriedTo], string, 0, strlen(string), 255);
					GivePlayerMoney(playerid, - 100000);
					PlayerInfo[playerid][pMarried] = 1;
					PlayerInfo[ProposedTo[playerid]][pMarried] = 1;
					PlayerInfo[ProposedTo[playerid]][pPhousekey] = PlayerInfo[playerid][pPhousekey];
					PlayerInfo[ProposedTo[playerid]][pPbiskey] = PlayerInfo[playerid][pPbiskey];
					ProposedTo[playerid] = 999;
					MarriageCeremoney[playerid] = 0;
				    return 1;
			    }
			    else
			    {
			        MarriageCeremoney[playerid] = 0;
			        ProposedTo[playerid] = 999;
			        return 0;
			    }
			}
		}
		else
		{
		    if(GotProposedBy[playerid] < 999)
		    {
				if(IsPlayerConnected(GotProposedBy[playerid]))
				{
					GetPlayerName(playerid, sendername, sizeof(sendername));
					GetPlayerName(GotProposedBy[playerid], giveplayer, sizeof(giveplayer));
					format(string, sizeof(string), "* You didn't want to Marry %s, no 'yes' was said.",giveplayer);
				    SendClientMessage(playerid, COLOR_YELLOW, string);
				    format(string, sizeof(string), "* %s did't want to Marry you, no 'yes' was said.",sendername);
				    SendClientMessage(GotProposedBy[playerid], COLOR_YELLOW, string);
				    return 0;
			    }
			    else
			    {
			        MarriageCeremoney[playerid] = 0;
			        GotProposedBy[playerid] = 999;
			        return 0;
			    }
		    }
		    else if(ProposedTo[playerid] < 999)
			{
			    if(IsPlayerConnected(ProposedTo[playerid]))
				{
					GetPlayerName(playerid, sendername, sizeof(sendername));
					GetPlayerName(ProposedTo[playerid], giveplayer, sizeof(giveplayer));
					format(string, sizeof(string), "* You didn't want to Marry %s, no 'yes' was said.",giveplayer);
				    SendClientMessage(playerid, COLOR_YELLOW, string);
				    format(string, sizeof(string), "* %s did't want to Marry you, no 'yes' was said.",sendername);
				    SendClientMessage(ProposedTo[playerid], COLOR_YELLOW, string);
				    return 0;
			    }
			    else
			    {
			        MarriageCeremoney[playerid] = 0;
			        ProposedTo[playerid] = 999;
			        return 0;
			    }
			}
		}
	    return 0;
	}
	if(WritingPaper[playerid] > 0)
	{
	    new line;
        new nstring[256];
        new idx;
        new length = strlen(text);
		while ((idx < length) && (text[idx] <= ' '))
		{
			idx++;
		}
		new offset = idx;
		new result[64];
		while ((idx < length) && ((idx - offset) < (sizeof(result) - 1)))
		{
			result[idx - offset] = text[idx];
			idx++;
		}
		result[idx - offset] = EOS;
		if(!strlen(result))
		{
		    if(WritingLine[playerid] == 1) { SendClientMessage(playerid, COLOR_GRAD2, "* Please type in the Title of your Newspaper."); }
		    else { SendClientMessage(playerid, COLOR_LIGHTRED, "* Please type in a Text Line of your Newspaper."); }
			return 0;
		}
		format(nstring, sizeof(nstring), "%s", text);
		switch(WritingLine[playerid])
		{
		    case 1:
		    {
		        new fstring[MAX_PLAYER_NAME];
		        GetPlayerName(playerid, sendername, sizeof(sendername));
				format(fstring, sizeof(fstring), "%s", sendername);
				strmid(PaperInfo[WritingPaperNumber[playerid]][PaperMaker], fstring, 0, strlen(fstring), 255);
		        strmid(PaperInfo[WritingPaperNumber[playerid]][PaperTitle], nstring, 0, strlen(nstring), 255);
		        line = 0; WritingLine[playerid] = 2;
		        SendClientMessage(playerid, COLOR_LIGHTRED, "* Now you can write down the News Lines, 7 remaining.");
		    }
		    case 2:
		    {
		        strmid(PaperInfo[WritingPaperNumber[playerid]][PaperText1], nstring, 0, strlen(nstring), 255);
		        line = 1; WritingLine[playerid] = 3;
		    }
		    case 3:
		    {
		        strmid(PaperInfo[WritingPaperNumber[playerid]][PaperText2], nstring, 0, strlen(nstring), 255);
		        line = 2; WritingLine[playerid] = 4;
		    }
		    case 4:
		    {
		        strmid(PaperInfo[WritingPaperNumber[playerid]][PaperText3], nstring, 0, strlen(nstring), 255);
		        line = 3; WritingLine[playerid] = 5;
		    }
		    case 5:
		    {
		        strmid(PaperInfo[WritingPaperNumber[playerid]][PaperText4], nstring, 0, strlen(nstring), 255);
		        line = 4; WritingLine[playerid] = 6;
		    }
		    case 6:
		    {
		        strmid(PaperInfo[WritingPaperNumber[playerid]][PaperText5], nstring, 0, strlen(nstring), 255);
		        line = 5; WritingLine[playerid] = 7;
		    }
		    case 7:
		    {
		        strmid(PaperInfo[WritingPaperNumber[playerid]][PaperText6], nstring, 0, strlen(nstring), 255);
		        line = 6; WritingLine[playerid] = 8;
		    }
		    case 8:
		    {
		        strmid(PaperInfo[WritingPaperNumber[playerid]][PaperText7], nstring, 0, strlen(nstring), 255);
		        PaperInfo[WritingPaperNumber[playerid]][PaperUsed] = 1;
		        SavePapers();
		        line = 7; WritingLine[playerid] = 0; WritingPaper[playerid] = 0; WritingPaperNumber[playerid] = 999;
		    }
		}
		if(line > 0)
		{
			format(string, sizeof(string), "* You wrote Line %d of the Newspaper.", line);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
			if(line == 7)
			{
			    SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Your Newspaper has been added to the News List (for Paper Boys).");
			}
		}
	    return 0;
	}
	if(ConnectedToPC[playerid] == 255)
	{
		new idx;
	    tmp = strtok(text, idx);
	    if ((strcmp("Contracts", tmp, true, strlen(tmp)) == 0) && (strlen(tmp) == strlen("Contracts")))
		{
		    if(PlayerInfo[playerid][pRank] < 4)
		    {
		        SendClientMessage(playerid, COLOR_GREY, "   Only Hitman with Rank 4 or above can search and assign Contracts !");
		        return 0;
		    }
		    SearchingHit(playerid);
			return 0;
		}
		else if ((strcmp("News", tmp, true, strlen(tmp)) == 0) && (strlen(tmp) == strlen("News")))
		{
		    	new x_nr[256];
				x_nr = strtok(text, idx);

				if(!strlen(x_nr)) {
					SendClientMessage(playerid, COLOR_WHITE, "|__________________ Hitman Agency News __________________|");
					SendClientMessage(playerid, COLOR_WHITE, "USAGE: News [number] or News delete [number] or News delete all");
					format(string, sizeof(string), "1: %s :: Hitman: %s", News[hAdd1], News[hContact1]);
					SendClientMessage(playerid, COLOR_GREY, string);
					format(string, sizeof(string), "2: %s :: Hitman: %s", News[hAdd2], News[hContact2]);
					SendClientMessage(playerid, COLOR_GREY, string);
					format(string, sizeof(string), "3: %s :: Hitman: %s", News[hAdd3], News[hContact3]);
					SendClientMessage(playerid, COLOR_GREY, string);
					format(string, sizeof(string), "4: %s :: Hitman: %s", News[hAdd4], News[hContact4]);
					SendClientMessage(playerid, COLOR_GREY, string);
					format(string, sizeof(string), "5: %s :: Hitman: %s", News[hAdd5], News[hContact5]);
					SendClientMessage(playerid, COLOR_GREY, string);
					SendClientMessage(playerid, COLOR_WHITE, "|________________________________________________________|");
					return 0;
				}//lets start
				if(strcmp(x_nr,"1",true) == 0)
				{
				    if(PlacedNews[playerid] == 1) { SendClientMessage(playerid, COLOR_GREY, "   Already placed a News Message, it must be deleted first !"); return 0; }
				    if(PlayerInfo[playerid][pRank] < 3) { SendClientMessage(playerid, COLOR_GREY, "   You must be Rank 3 to write messages to the News Channel !"); return 0; }
				    if(News[hTaken1] == 0)
				    {
				        GetPlayerName(playerid, sendername, sizeof(sendername));
				        if(strlen(text)-(strlen(x_nr)) < 9) { SendClientMessage(playerid, COLOR_GREY, "   News Text to short !"); return 0; }
						format(string, sizeof(string), "%s",right(text,strlen(text)-7)); strmid(News[hAdd1], string, 0, strlen(string), 255);
						format(string, sizeof(string), "%s",sendername); strmid(News[hContact1], string, 0, strlen(string), 255);
						News[hTaken1] = 1; PlacedNews[playerid] = 1;
						SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You placed a News Message on the Hitman Agency's News Channel.");
						return 0;
				    }
				    else
				    {
				        SendClientMessage(playerid, COLOR_GREY, "   Spot 1 is already Taken !");
				        return 0;
				    }
				}
				else if(strcmp(x_nr,"2",true) == 0)
				{
				    if(PlacedNews[playerid] == 1) { SendClientMessage(playerid, COLOR_GREY, "   Already placed a News Message, it must be deleted first !"); return 0; }
				    if(PlayerInfo[playerid][pRank] < 3) { SendClientMessage(playerid, COLOR_GREY, "   You must be Rank 3 to write messages to the News Channel !"); return 0; }
				    if(News[hTaken2] == 0)
				    {
				        GetPlayerName(playerid, sendername, sizeof(sendername));
				        if(strlen(text)-(strlen(x_nr)) < 9) { SendClientMessage(playerid, COLOR_GREY, "   News Text to short !"); return 0; }
						format(string, sizeof(string), "%s",right(text,strlen(text)-7)); strmid(News[hAdd2], string, 0, strlen(string), 255);
						format(string, sizeof(string), "%s",sendername); strmid(News[hContact2], string, 0, strlen(string), 255);
						News[hTaken2] = 1; PlacedNews[playerid] = 1;
						SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You placed a News Message on the Hitman Agency's News Channel.");
						return 0;
				    }
				    else
				    {
				        SendClientMessage(playerid, COLOR_GREY, "   Spot 2 is already Taken !");
				        return 0;
				    }
				}
				else if(strcmp(x_nr,"3",true) == 0)
				{
				    if(PlacedNews[playerid] == 1) { SendClientMessage(playerid, COLOR_GREY, "   Already placed a News Message, it must be deleted first !"); return 0; }
				    if(PlayerInfo[playerid][pRank] < 3) { SendClientMessage(playerid, COLOR_GREY, "   You must be Rank 3 to write messages to the News Channel !"); return 0; }
				    if(News[hTaken3] == 0)
				    {
				        GetPlayerName(playerid, sendername, sizeof(sendername));
				        if(strlen(text)-(strlen(x_nr)) < 9) { SendClientMessage(playerid, COLOR_GREY, "   News Text to short !"); return 0; }
						format(string, sizeof(string), "%s",right(text,strlen(text)-7)); strmid(News[hAdd3], string, 0, strlen(string), 255);
						format(string, sizeof(string), "%s",sendername); strmid(News[hContact3], string, 0, strlen(string), 255);
						News[hTaken3] = 1; PlacedNews[playerid] = 1;
						SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You placed a News Message on the Hitman Agency's News Channel.");
						return 0;
				    }
				    else
				    {
				        SendClientMessage(playerid, COLOR_GREY, "   Spot 3 is already Taken !");
				        return 0;
				    }
				}
				else if(strcmp(x_nr,"4",true) == 0)
				{
				    if(PlacedNews[playerid] == 1) { SendClientMessage(playerid, COLOR_GREY, "   Already placed a News Message, it must be deleted first !"); return 0; }
				    if(PlayerInfo[playerid][pRank] < 3) { SendClientMessage(playerid, COLOR_GREY, "   You must be Rank 3 to write messages to the News Channel !"); return 0; }
				    if(News[hTaken4] == 0)
				    {
				        GetPlayerName(playerid, sendername, sizeof(sendername));
				        if(strlen(text)-(strlen(x_nr)) < 9) { SendClientMessage(playerid, COLOR_GREY, "   News Text to short !"); return 0; }
						format(string, sizeof(string), "%s",right(text,strlen(text)-7)); strmid(News[hAdd4], string, 0, strlen(string), 255);
						format(string, sizeof(string), "%s",sendername); strmid(News[hContact4], string, 0, strlen(string), 255);
						News[hTaken4] = 1; PlacedNews[playerid] = 1;
						SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You placed a News Message on the Hitman Agency's News Channel.");
						return 0;
				    }
				    else
				    {
				        SendClientMessage(playerid, COLOR_GREY, "   Spot 4 is already Taken !");
				        return 0;
				    }
				}
				else if(strcmp(x_nr,"5",true) == 0)
				{
				    if(PlacedNews[playerid] == 1) { SendClientMessage(playerid, COLOR_GREY, "   Already placed a News Message, it must be deleted first !"); return 0; }
				    if(PlayerInfo[playerid][pRank] < 3) { SendClientMessage(playerid, COLOR_GREY, "   You must be Rank 3 to write messages to the News Channel !"); return 0; }
				    if(News[hTaken5] == 0)
				    {
				        GetPlayerName(playerid, sendername, sizeof(sendername));
				        if(strlen(text)-(strlen(x_nr)) < 9) { SendClientMessage(playerid, COLOR_GREY, "   News Text to short !"); return 0; }
						format(string, sizeof(string), "%s",right(text,strlen(text)-7)); strmid(News[hAdd5], string, 0, strlen(string), 255);
						format(string, sizeof(string), "%s",sendername); strmid(News[hContact5], string, 0, strlen(string), 255);
						News[hTaken5] = 1; PlacedNews[playerid] = 1;
						SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You placed a News Message on the Hitman Agency's News Channel.");
						return 0;
				    }
				    else
				    {
				        SendClientMessage(playerid, COLOR_GREY, "   Spot 5 is already Taken !");
				        return 0;
				    }
				}
				else if(strcmp(x_nr,"delete",true) == 0)
				{
				    if(PlayerInfo[playerid][pRank] < 4)
				    {
				        SendClientMessage(playerid, COLOR_GREY, "   You must be Rank 4 to delete messages from the News Channel !");
				        return 0;
				    }
				    new string1[MAX_PLAYER_NAME];
				    new x_tel[256];
					x_tel = strtok(text, idx);
					if(!strlen(x_tel)) {
					    SendClientMessage(playerid, COLOR_WHITE, "USAGE: News delete [number] or News delete all.");
					    return 0;
					}
                    if(strcmp(x_tel,"1",true) == 0)
                    {
                        format(string, sizeof(string), "Nothing"); strmid(News[hAdd1], string, 0, strlen(string), 255);
						format(string1, sizeof(string1), "No-one");	strmid(News[hContact1], string1, 0, strlen(string1), 255);
						News[hTaken1] = 0;
						SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You deleted News Message (1) from the Hitman Agency's News Channel.");
						return 0;
                    }
                    else if(strcmp(x_tel,"2",true) == 0)
                    {
                        format(string, sizeof(string), "Nothing"); strmid(News[hAdd2], string, 0, strlen(string), 255);
						format(string1, sizeof(string1), "No-one");	strmid(News[hContact2], string1, 0, strlen(string1), 255);
						News[hTaken2] = 0;
						SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You deleted News Message (2) from the Hitman Agency's News Channel.");
						return 0;
                    }
                    else if(strcmp(x_tel,"3",true) == 0)
                    {
                        format(string, sizeof(string), "Nothing"); strmid(News[hAdd3], string, 0, strlen(string), 255);
						format(string1, sizeof(string1), "No-one");	strmid(News[hContact3], string1, 0, strlen(string1), 255);
						News[hTaken3] = 0;
						SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You deleted News Message (3) from the Hitman Agency's News Channel.");
						return 0;
                    }
                    else if(strcmp(x_tel,"4",true) == 0)
                    {
                        format(string, sizeof(string), "Nothing"); strmid(News[hAdd4], string, 0, strlen(string), 255);
						format(string1, sizeof(string1), "No-one");	strmid(News[hContact4], string1, 0, strlen(string1), 255);
						News[hTaken4] = 0;
						SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You deleted News Message (4) from the Hitman Agency's News Channel.");
						return 0;
                    }
                    else if(strcmp(x_tel,"5",true) == 0)
                    {
                        format(string, sizeof(string), "Nothing"); strmid(News[hAdd5], string, 0, strlen(string), 255);
						format(string1, sizeof(string1), "No-one");	strmid(News[hContact5], string1, 0, strlen(string1), 255);
						News[hTaken5] = 0;
						SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You deleted News Message (5) from the Hitman Agency's News Channel.");
						return 0;
                    }
                    else if(strcmp(x_tel,"all",true) == 0)
                    {
                        format(string, sizeof(string), "Nothing"); strmid(News[hAdd1], string, 0, strlen(string), 255);
						format(string1, sizeof(string1), "No-one");	strmid(News[hContact1], string1, 0, strlen(string1), 255);
						News[hTaken1] = 0;
						format(string, sizeof(string), "Nothing"); strmid(News[hAdd2], string, 0, strlen(string), 255);
						format(string1, sizeof(string1), "No-one");	strmid(News[hContact2], string1, 0, strlen(string1), 255);
						News[hTaken2] = 0;
						format(string, sizeof(string), "Nothing"); strmid(News[hAdd3], string, 0, strlen(string), 255);
						format(string1, sizeof(string1), "No-one");	strmid(News[hContact3], string1, 0, strlen(string1), 255);
						News[hTaken3] = 0;
						format(string, sizeof(string), "Nothing"); strmid(News[hAdd4], string, 0, strlen(string), 255);
						format(string1, sizeof(string1), "No-one");	strmid(News[hContact4], string1, 0, strlen(string1), 255);
						News[hTaken4] = 0;
						format(string, sizeof(string), "Nothing"); strmid(News[hAdd5], string, 0, strlen(string), 255);
						format(string1, sizeof(string1), "No-one");	strmid(News[hContact5], string1, 0, strlen(string1), 255);
						News[hTaken5] = 0;
						SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You deleted all the News Message from the Hitman Agency's News Channel.");
						return 0;
                    }
                    else
                    {
                        SendClientMessage(playerid, COLOR_WHITE, "USAGE: News delete [number] or News delete all.");
					    return 0;
                    }
				}
				else { return 0; }
		}
		else if ((strcmp("Givehit", tmp, true, strlen(tmp)) == 0) && (strlen(tmp) == strlen("Givehit")))
		{
		    if(PlayerInfo[playerid][pRank] < 4)
		    {
		        SendClientMessage(playerid, COLOR_GREY, "   You need Rank 4 to Give Contracts to Hitmans !");
		        return 0;
		    }
		    if(hitfound == 0)
		    {
		        SendClientMessage(playerid, COLOR_GREY, "   There is no Hit Founded yet, use Contracts in the Portable first !");
		        return 0;
		    }
		    tmp = strtok(text, idx);
		    if(!strlen(tmp))
			{
				SendClientMessage(playerid, COLOR_GRAD1, "USAGE: Givehit [playerid/PartOfName]");
				return 0;
			}
			//giveplayerid = strval(tmp);
			giveplayerid = ReturnUser(tmp);
			if(IsPlayerConnected(giveplayerid))
			{
			    if(giveplayerid != INVALID_PLAYER_ID)
			    {
				    if(PlayerInfo[giveplayerid][pMember] != 8)
				    {
				        SendClientMessage(playerid, COLOR_GREY, "   That player is not a Hitman !");
						return 0;
				    }
				    if(GoChase[giveplayerid] < 999)
				    {
				        SendClientMessage(playerid, COLOR_GREY, "   That Hitman is already busy with a Contract !");
						return 0;
				    }
				    if(IsPlayerConnected(hitid))
				    {
				        GetPlayerName(playerid, sendername, sizeof(sendername));
				        GetPlayerName(giveplayerid, giver, sizeof(giver));
				        GetPlayerName(hitid, giveplayer, sizeof(giveplayer));
				        //format(string, sizeof(string), "* You assigned%s to kill: %s(ID:%d), for $%d.", giver, giveplayer, hitid, PlayerInfo[hitid][pValue]);
		    			//SendClientMessage(playerid, COLOR_YELLOW, string);
				        //format(string, sizeof(string), "* Hitman %s has assigned you to kill: %s(ID:%d), for $%d.", sendername, giveplayer, hitid, PlayerInfo[hitid][pValue]);
		    			//SendClientMessage(giveplayerid, COLOR_YELLOW, string);
		    			format(string, sizeof(string), "* Hitman %s, assigned Hitman %s to kill: %s(ID:%d), for $%d.", sendername, giver, giveplayer, hitid, PlayerInfo[hitid][pHeadValue]);
		    			SendFamilyMessage(8, COLOR_YELLOW, string);
		    			GoChase[giveplayerid] = hitid;
		    			GetChased[hitid] = giveplayerid;
		    			GotHit[hitid] = 1;
		    			hitid = 0;
		    			hitfound = 0;
				        return 0;
				    }
				    else
				    {
				        SendClientMessage(playerid, COLOR_GREY, "   The Contracted Person is offline, use Contracts in the Portable again !");
				        return 0;
				    }
				}
				return 0;
			}
			else
			{
			    SendClientMessage(playerid, COLOR_GREY, "   That Hitman is not Online, or ain't a Hitman !");
			    return 0;
			}
		}
		else if ((strcmp("Ranks", tmp, true, strlen(tmp)) == 0) && (strlen(tmp) == strlen("Ranks")))
		{
			SendClientMessage(playerid, COLOR_WHITE, "|__________________ Agency's Ranks __________________|");
		    for(new i=0; i < MAX_PLAYERS; i++)
			{
				if(IsPlayerConnected(i))
				{
				    if(PlayerInfo[i][pMember] == 8||PlayerInfo[i][pLeader] == 8)
				    {
						GetPlayerName(i, giveplayer, sizeof(giveplayer));
				        format(string, sizeof(string), "* %s: Rank %d", giveplayer,PlayerInfo[i][pRank]);
						SendClientMessage(playerid, COLOR_GREY, string);
					}
				}
			}
		}
		else if ((strcmp("Order", tmp, true, strlen(tmp)) == 0) && (strlen(tmp) == strlen("Order")))
		{
		    if(OrderReady[playerid] > 0)
		    {
		        SendClientMessage(playerid, COLOR_GREY, "   You already Ordered a Package, pick it up at your Head Quarter's Front Door first !");
		        return 0;
		    }
		    tmp = strtok(text, idx);
		    if ((strcmp("1", tmp, true, strlen(tmp)) == 0) && (strlen(tmp) == strlen("1")))
			{
			    if(PlayerInfo[playerid][pRank] < 1) { SendClientMessage(playerid, COLOR_GREY, "   Your Rank is not high enough to Order that Package !"); return 0; }
			    if(GetPlayerMoney(playerid) > 4999)
			    {
			        SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You have Ordered Package 1 ($5000), it will be delivered at your Head Quarter's Front Door.");
			        OrderReady[playerid] = 1;
			        return 0;
			    }
			    else
			    {
			        SendClientMessage(playerid, COLOR_GREY,"   You can't afford that Package !");
			        return 0;
			    }
			}
			else if ((strcmp("2", tmp, true, strlen(tmp)) == 0) && (strlen(tmp) == strlen("2")))
			{
			    if(PlayerInfo[playerid][pRank] < 2) { SendClientMessage(playerid, COLOR_GREY, "   Your Rank is not high enough to Order that Package !"); return 0; }
			    if(GetPlayerMoney(playerid) > 5999)
			    {
			        SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You have Ordered Package 2 ($6000), it will be delivered at your Head Quarter's Front Door.");
			        OrderReady[playerid] = 2;
			        return 0;
			    }
			    else
			    {
			        SendClientMessage(playerid, COLOR_GREY,"   You can't afford that Package !");
			        return 0;
			    }
			}
			else if ((strcmp("3", tmp, true, strlen(tmp)) == 0) && (strlen(tmp) == strlen("3")))
			{
			    if(PlayerInfo[playerid][pRank] < 2) { SendClientMessage(playerid, COLOR_GREY, "   Your Rank is not high enough to Order that Package !"); return 0; }
			    if(GetPlayerMoney(playerid) > 5999)
			    {
			        SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You have Ordered Package 3 ($6000), it will be delivered at your Head Quarter's Front Door.");
			        OrderReady[playerid] = 3;
			        return 0;
			    }
			    else
			    {
			        SendClientMessage(playerid, COLOR_GREY,"   You can't afford that Package !");
			        return 0;
			    }
			}
			else if ((strcmp("4", tmp, true, strlen(tmp)) == 0) && (strlen(tmp) == strlen("4")))
			{
			    if(PlayerInfo[playerid][pRank] < 3) { SendClientMessage(playerid, COLOR_GREY, "   Your Rank is not high enough to Order that Package !"); return 0; }
			    if(GetPlayerMoney(playerid) > 7999)
			    {
			        SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You have Ordered Package 4 ($8000), it will be delivered at your Head Quarter's Front Door.");
			        OrderReady[playerid] = 4;
			        return 0;
			    }
			    else
			    {
			        SendClientMessage(playerid, COLOR_GREY,"   You can't afford that Package !");
			        return 0;
			    }
			}
			else if ((strcmp("5", tmp, true, strlen(tmp)) == 0) && (strlen(tmp) == strlen("5")))
			{
			    if(PlayerInfo[playerid][pRank] < 3) { SendClientMessage(playerid, COLOR_GREY, "   Your Rank is not high enough to Order that Package !"); return 0; }
			    if(GetPlayerMoney(playerid) > 7999)
			    {
			        SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You have Ordered Package 5 ($8000), it will be delivered at your Head Quarter's Front Door.");
			        OrderReady[playerid] = 5;
			        return 0;
			    }
			    else
			    {
			        SendClientMessage(playerid, COLOR_GREY,"   You can't afford that Package !");
			        return 0;
			    }
			}
			else if ((strcmp("6", tmp, true, strlen(tmp)) == 0) && (strlen(tmp) == strlen("6")))
			{
			    if(PlayerInfo[playerid][pRank] < 4) { SendClientMessage(playerid, COLOR_GREY, "   Your Rank is not high enough to Order that Package !"); return 0; }
			    if(GetPlayerMoney(playerid) > 8499)
			    {
			        SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You have Ordered Package 6 ($8500), it will be delivered at your Head Quarter's Front Door.");
			        OrderReady[playerid] = 6;
			        return 0;
			    }
			    else
			    {
			        SendClientMessage(playerid, COLOR_GREY,"   You can't afford that Package !");
			        return 0;
			    }
			}
			else if ((strcmp("7", tmp, true, strlen(tmp)) == 0) && (strlen(tmp) == strlen("7")))
			{
			    if(PlayerInfo[playerid][pRank] < 4) { SendClientMessage(playerid, COLOR_GREY, "   Your Rank is not high enough to Order that Package !"); return 0; }
			    if(GetPlayerMoney(playerid) > 8499)
			    {
			        SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You have Ordered Package 7 ($8500), it will be delivered at your Head Quarter's Front Door.");
			        OrderReady[playerid] = 7;
			        return 0;
			    }
			    else
			    {
			        SendClientMessage(playerid, COLOR_GREY,"   You can't afford that Package !");
			        return 0;
			    }
			}
			else
			{
			    SendClientMessage(playerid, COLOR_WHITE, "|__________________ Available Packages __________________|");
			    if(PlayerInfo[playerid][pRank] >= 1) { SendClientMessage(playerid, COLOR_GREY, "|(1) ($5000 ) Rank 1 - 5: Knife, Desert Eagle, MP5, Shotgun"); }
			    if(PlayerInfo[playerid][pRank] >= 2) { SendClientMessage(playerid, COLOR_GREY, "|(2) ($6000 ) Rank 2 - 5: Knife, Desert Eagle, M4, MP5, Shotgun"); }
			    if(PlayerInfo[playerid][pRank] >= 2) { SendClientMessage(playerid, COLOR_GREY, "|(3) ($6000 ) Rank 2 - 5: Knife, Desert Eagle, AK47, MP5, Shotgun"); }
			    if(PlayerInfo[playerid][pRank] >= 3) { SendClientMessage(playerid, COLOR_GREY, "|(4) ($8000) Rank 3 - 5: Knife, Desert Eagle, M4, MP5, Shotgun, Sniper"); }
			    if(PlayerInfo[playerid][pRank] >= 3) { SendClientMessage(playerid, COLOR_GREY, "|(5) ($8000) Rank 3 - 5: Knife, Desert Eagle, AK47, MP5, Shotgun, Sniper"); }
			    if(PlayerInfo[playerid][pRank] >= 4) { SendClientMessage(playerid, COLOR_GREY, "|(6) ($8500) Rank 4 - 5: Knife, Desert Eagle, M4, MP5, Shotgun, Sniper"); }
			    if(PlayerInfo[playerid][pRank] >= 4) { SendClientMessage(playerid, COLOR_GREY, "|(7) ($8500) Rank 4 - 5: Knife, Desert Eagle, AK47, MP5, Shotgun, Sniper"); }
			    SendClientMessage(playerid, COLOR_WHITE, "|________________________________________________________|");
			    return 0;
			}
		}
		else if ((strcmp("Logout", tmp, true, strlen(tmp)) == 0) && (strlen(tmp) == strlen("Logout")))
		{
		    SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You have shutdowned your Laptop, and Disconnected from your Agency.");
      		ConnectedToPC[playerid] = 0;
		    return 0;
		}
		else
		{
		    SendClientMessage(playerid, COLOR_WHITE, "|___ Hitman Agency ___|");
		    SendClientMessage(playerid, COLOR_YELLOW2, "| - News");
		    SendClientMessage(playerid, COLOR_YELLOW2, "| - Contracts");
		    SendClientMessage(playerid, COLOR_YELLOW2, "| - Givehit");
		    SendClientMessage(playerid, COLOR_YELLOW2, "| - Backup");
		    SendClientMessage(playerid, COLOR_YELLOW2, "| - Order");
		    SendClientMessage(playerid, COLOR_YELLOW2, "| - Ranks");
		    SendClientMessage(playerid, COLOR_YELLOW2, "| - Logout");
		    SendClientMessage(playerid, COLOR_YELLOW2, "|");
			SendClientMessage(playerid, COLOR_WHITE, "|______________|00:00|");
		    return 0;
		}
	    return 0;
	}
	if(CallLawyer[playerid] == 111)
	{
	    new idx;
	    tmp = strtok(text, idx);
	    if ((strcmp("yes", tmp, true, strlen(tmp)) == 0) && (strlen(tmp) == strlen("yes")))
		{
		    GetPlayerName(playerid, sendername, sizeof(sendername));
		    format(string, sizeof(string), "** %s is in Jail, and needs a Lawyer. Go to the Police Station.", sendername);
	    	SendJobMessage(2, TEAM_AZTECAS_COLOR, string);
	    	SendJobMessage(2, TEAM_AZTECAS_COLOR, "* When you are at the Police Station, ask an Officer to approve you with /accept lawyer.");
	    	SendClientMessage(playerid, COLOR_LIGHTRED, "A message has been sent to all available Lawyers, please wait.");
	    	WantLawyer[playerid] = 0;
			CallLawyer[playerid] = 0;
	    	return 0;
		}
		else
		{
		    SendClientMessage(playerid, COLOR_LIGHTRED, "There is no Lawyer available to you anymore, Jail Time started.");
		    WantLawyer[playerid] = 0;
			CallLawyer[playerid] = 0;
		    return 0;
		}
	}
	if(TalkingLive[playerid] != 255)
	{
		GetPlayerName(playerid, sendername, sizeof(sendername));
		if(PlayerInfo[playerid][pJob] == 6)
		{
		    format(string, sizeof(string), "LiveNR %s: %s", sendername, text);
			OOCNews(COLOR_LIGHTGREEN, string);
		}
		else
		{
		    format(string, sizeof(string), "LivePlayer %s: %s", sendername, text);
			OOCNews(COLOR_LIGHTGREEN, string);
		}
		return 0;
	}
	if(Mobile[playerid] != 255)
	{
		new idx;
		tmp = strtok(text, idx);
		GetPlayerName(playerid, sendername, sizeof(sendername));
		format(string, sizeof(string), "%s Says (cellphone): %s", sendername, text);
		ProxDetector(20.0, playerid, string,COLOR_FADE1,COLOR_FADE2,COLOR_FADE3,COLOR_FADE4,COLOR_FADE5);
		//printf("callers line %d called %d caller %d",Mobile[Mobile[playerid]],Mobile[playerid],playerid);
		if(Mobile[playerid] == 914)
		{
			if(!strlen(tmp))
			{
				SendClientMessage(playerid, TEAM_CYAN_COLOR, "Dispatch: Sorry I don't understand?");
				return 0;
			}
			new turner[MAX_PLAYER_NAME];
			new wanted[128];
			GetPlayerName(playerid, turner, sizeof(turner));
			SendClientMessage(playerid, TEAM_CYAN_COLOR, "Dispatch: We have alerted all units in the area.");
			SendClientMessage(playerid, TEAM_CYAN_COLOR, "Thank you for reporting this incident");
			format(wanted, sizeof(wanted), "Dispatch: All Units IA: Caller: %s",turner);
			SendTeamBeepMessage(1, TEAM_CYAN_COLOR, wanted);
			format(wanted, sizeof(wanted), "Dispatch: Incident: %s",text);
			SendTeamMessage(1, TEAM_CYAN_COLOR, wanted);
			SendClientMessage(playerid, COLOR_GRAD2, "   They Hung Up...");
			Mobile[playerid] = 255;
			return 0;
		}
		if(Mobile[playerid] == 913)
		{
			if(!strlen(tmp))
			{
				SendClientMessage(playerid, COLOR_ALLDEPT, "EMERGENCY: Sorry i dont understand?");
				return 0;
			}
			if ((strcmp("no", tmp, true, strlen(tmp)) == 0) && (strlen(tmp) == strlen("no")))
			{
				new turner[MAX_PLAYER_NAME];
				new wanted[128];
				GetPlayerName(playerid, turner, sizeof(turner));
				SendClientMessage(playerid, COLOR_DBLUE, "Police HQ: We have alerted all units in the area.");
				SendClientMessage(playerid, COLOR_DBLUE, "Thank you for reporting this crime");
				format(wanted, sizeof(wanted), "HQ: All Units APB: Reporter: %s",turner);
				SendFamilyMessage(1, COLOR_DBLUE, wanted);
				format(wanted, sizeof(wanted), "HQ: Crime: %s, Suspect: Unknown",PlayerCrime[playerid][pAccusing]);
				SendFamilyMessage(1, COLOR_DBLUE, wanted);
				SendClientMessage(playerid, COLOR_GRAD2, "   They Hung Up...");
				Mobile[playerid] = 255;
				return 0;
			}
			new badguy;
			//badguy = strval(tmp);
			badguy = ReturnUser(tmp);
			if (IsPlayerConnected(badguy))
			{
			    if(badguy != INVALID_PLAYER_ID)
			    {
					if (gTeam[badguy] == 2 || gTeam[badguy] == 1)
					{
						SendClientMessage(playerid, COLOR_DBLUE, "Police HQ: You will have to contact internal affairs. This is an emergency line");
						SendClientMessage(playerid, COLOR_GRAD2, "   They Hung Up...");
						Mobile[playerid] = 255;
						return 0;
					}
					if (WantedPoints[badguy] > 0)
					{
						SendClientMessage(playerid, COLOR_DBLUE, "Police HQ: Units are already assigned to that case");
						SendClientMessage(playerid, COLOR_DBLUE, "Thank you for reporting this crime");
						SendClientMessage(playerid, COLOR_GRAD2, "   They Hung Up...");
						Mobile[playerid] = 255;
						return 0;
					}
					if (badguy == playerid)
					{
						SendClientMessage(playerid, COLOR_DBLUE, "Police HQ: Dont Fool Around, This is an emergency line.");
						SendClientMessage(playerid, COLOR_GRAD2, "   They Hung Up...");
						Mobile[playerid] = 255;
						return 0;
					}
					SendClientMessage(playerid, COLOR_DBLUE, "Police HQ: We have alerted all units in the area.");
					SendClientMessage(playerid, COLOR_DBLUE, "Thank you for reporting this crime");
					SetPlayerCriminal(badguy,playerid, PlayerCrime[playerid][pAccusing]);
					if(WantedPoints[badguy] > 0) { } else { WantedPoints[badguy] += 2; }
					SendClientMessage(playerid, COLOR_GRAD2, "   They Hung Up...");
					Mobile[playerid] = 255;
					return 0;
				}//invalid id
				return 0;
			}//not connected
			else
			{
				format(string, sizeof(string), "Police HQ: I have no Information on %s, are you sure thats the right name?",tmp);
				SendClientMessage(playerid, COLOR_DBLUE, string);
				return 0;
			}
		}
		if(Mobile[playerid] == 912)
		{
			if(!strlen(tmp))
			{
				SendClientMessage(playerid, COLOR_ALLDEPT, "EMERGENCY: Sorry i dont understand?");
				return 0;
			}
			strmid(PlayerCrime[playerid][pAccusing], text, 0, strlen(text), 255);
			SendClientMessage(playerid, COLOR_DBLUE, "Police HQ: If you know the assailant's name or part of it say it now or just say no.");
			Mobile[playerid] = 913;
			return 0;
		}
		if(Mobile[playerid] == 911)
		{
			if(!strlen(tmp))
			{
				SendClientMessage(playerid, COLOR_ALLDEPT, "EMERGENCY: Sorry i dont understand, police or paramedic?");
				return 0;
			}
			else if ((strcmp("police", tmp, true, strlen(tmp)) == 0) && (strlen(tmp) == strlen("police")))
			{
				SendClientMessage(playerid, COLOR_ALLDEPT, "EMERGENCY: I am patching you to  Police HQ, please hold.");
				Mobile[playerid] = 912;
				SendClientMessage(playerid, COLOR_DBLUE, "Police HQ: Please give me a short description of the crime.");
				return 0;
			}
			else if ((strcmp("paramedic", tmp, true, strlen(tmp)) == 0) && (strlen(tmp) == strlen("paramedic")))
			{
				SendClientMessage(playerid, COLOR_ALLDEPT, "EMERGENCY: I am patching you to  Paramedic HQ, please hold.");
				Mobile[playerid] = 914;
				SendClientMessage(playerid, TEAM_CYAN_COLOR, "Dispatch: Please give me a short description of the Incident.");
				return 0;
			}
			else
			{
				SendClientMessage(playerid, COLOR_ALLDEPT, "EMERGENCY: Sorry i dont understand, police or paramedic?");
				return 0;
			}
		}
		if(IsPlayerConnected(Mobile[playerid]))
		{
		    if(Mobile[Mobile[playerid]] == playerid)
		    {
				SendClientMessage(Mobile[playerid], COLOR_YELLOW,string);
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_YELLOW,"Theres nobody there");
		}
		return 0;
	}
	if (realchat)
	{
	    if(gPlayerLogged[playerid] == 0)
	    {
	        return 0;
      	}
		GetPlayerName(playerid, sendername, sizeof(sendername));
		format(string, sizeof(string), "%s Says: %s", sendername, text);
		ProxDetector(20.0, playerid, string,COLOR_FADE1,COLOR_FADE2,COLOR_FADE3,COLOR_FADE4,COLOR_FADE5);
		return 0;
	}
	return 1;
}

sampCallback OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	if(gTeam[playerid] >= 3)
	{
		if (IsACopCar(vehicleid) && !ispassenger)
		{
			if(PlayerInfo[playerid][pLeader]==1||PlayerInfo[playerid][pLeader]==2||PlayerInfo[playerid][pLeader]==3) {}
		    else { WantedPoints[playerid]+=2; SetPlayerCriminal(playerid,255, "Stealing A Police Vehicle"); }
		}
		if (IsAnAmbulance(vehicleid) && !ispassenger)
		{
		    if(PlayerInfo[playerid][pMember]==4||PlayerInfo[playerid][pLeader]==4) { }
		    else { WantedPoints[playerid]+=2; SetPlayerCriminal(playerid,255, "Stealing An Ambulance"); }
		}
	}
	return 1;
}

sampCallback OnPlayerEnterCheckpoint(playerid)
{
	new string[128];
	new name[MAX_PLAYER_NAME];
	if(TaxiCallTime[playerid] > 0 && TaxiAccepted[playerid] < 999)
	{
	    TaxiAccepted[playerid] = 999;
		GameTextForPlayer(playerid, "~w~Reached destination", 5000, 1);
		TaxiCallTime[playerid] = 0;
		DisablePlayerCheckpoint(playerid);
	}
	else if(BusCallTime[playerid] > 0 && BusAccepted[playerid] < 999)
	{
	    BusAccepted[playerid] = 999;
		GameTextForPlayer(playerid, "~w~Reached destination", 5000, 1);
		BusCallTime[playerid] = 0;
		DisablePlayerCheckpoint(playerid);
	}
	else if(CP[playerid]==1)
	{
	    if(IsPlayerInAnyVehicle(playerid))
	    {
		    PlayerInfo[playerid][pJackSkill] ++;
			if(PlayerInfo[playerid][pJackSkill] == 50)
			{ SendClientMessage(playerid, COLOR_YELLOW, "* Your Car Jack Skill is now Level 2, you will earn more Money and quicker Reload Time."); }
			else if(PlayerInfo[playerid][pJackSkill] == 100)
			{ SendClientMessage(playerid, COLOR_YELLOW, "* Your Car Jack Skill is now Level 3, you will earn more Money and quicker Reload Time."); }
			else if(PlayerInfo[playerid][pJackSkill] == 200)
			{ SendClientMessage(playerid, COLOR_YELLOW, "* Your Car Jack Skill is now Level 4, you will earn more Money and quicker Reload Time."); }
			else if(PlayerInfo[playerid][pJackSkill] == 400)
			{ SendClientMessage(playerid, COLOR_YELLOW, "* Your Car Jack Skill is now Level 5, you will earn more Money and quicker Reload Time."); }
			new level = PlayerInfo[playerid][pJackSkill];
			if(level >= 0 && level <= 50)
			{
			    new rand = random(sizeof(SELLCAR1));
			    format(string, sizeof(string), "You sold a car for $%d, your reload time is 20 minutes.", SELLCAR1[rand]);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
				GivePlayerMoney(playerid, SELLCAR1[rand]);
			    PlayerInfo[playerid][pCarTime] = 1200;
			}
			else if(level >= 51 && level <= 100)
			{
			    new rand = random(sizeof(SELLCAR2));
			    format(string, sizeof(string), "You sold a car for $%d, your reload time is 18 minutes.", SELLCAR2[rand]);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
				GivePlayerMoney(playerid, SELLCAR2[rand]);
			    PlayerInfo[playerid][pCarTime] = 1080;
			}
			else if(level >= 101 && level <= 200)
			{
			    new rand = random(sizeof(SELLCAR3));
			    format(string, sizeof(string), "You sold a car for $%d, your reload time is 16 minutes.", SELLCAR3[rand]);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
				GivePlayerMoney(playerid, SELLCAR3[rand]);
			    PlayerInfo[playerid][pCarTime] = 960;
			}
			else if(level >= 201 && level <= 400)
			{
			    new rand = random(sizeof(SELLCAR4));
			    format(string, sizeof(string), "You sold a car for $%d, your reload time is 14 minutes.", SELLCAR4[rand]);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
				GivePlayerMoney(playerid, SELLCAR4[rand]);
			    PlayerInfo[playerid][pCarTime] = 840;
			}
			else if(level >= 401)
			{
			    new money = 6000;
			    format(string, sizeof(string), "You sold a car for $%d, your reload time is 12 minutes.", money);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
				GivePlayerMoney(playerid, money);
			    PlayerInfo[playerid][pCarTime] = 720;
			}
			GameTextForPlayer(playerid, "~y~Sold the car", 2500, 1);
			CP[playerid] = 0;
		    DisablePlayerCheckpoint(playerid);
		    SetVehicleToRespawn(GetPlayerVehicleID(playerid));
		}
		else
		{
		    GameTextForPlayer(playerid, "Not in a car", 5000, 1);
		}
	}
	else if(CP[playerid] == 5)
	{
	    GameTextForPlayer(playerid, "~y~At the Missions Checkpoint", 2500, 1);
		CP[playerid] = 0;
	    DisablePlayerCheckpoint(playerid);
	}
	else if(CP[playerid] == 9)//Karting
	{
		GameTextForPlayer(playerid, "~r~Wait here for more Kart Racers", 4000, 3);
		DisablePlayerCheckpoint(playerid);
	}
	else if(CP[playerid] == 10) { CP[playerid] = 11; DisablePlayerCheckpoint(playerid); SetPlayerCheckpoint(playerid,2258.7874,-2402.9712,12.7035,8.0); }
	else if(CP[playerid] == 11) { CP[playerid] = 12; DisablePlayerCheckpoint(playerid); SetPlayerCheckpoint(playerid,2225.8755,-2461.3875,12.7190,8.0); }
	else if(CP[playerid] == 12) { CP[playerid] = 13; DisablePlayerCheckpoint(playerid); SetPlayerCheckpoint(playerid,2276.9983,-2662.8328,12.8580,8.0); }
	else if(CP[playerid] == 13) { CP[playerid] = 14; DisablePlayerCheckpoint(playerid); SetPlayerCheckpoint(playerid,2449.1399,-2663.0562,12.8138,8.0); }
	else if(CP[playerid] == 14) { CP[playerid] = 15; DisablePlayerCheckpoint(playerid); SetPlayerCheckpoint(playerid,2566.9814,-2504.5686,12.7692,8.0); }
	else if(CP[playerid] == 15) { CP[playerid] = 16; DisablePlayerCheckpoint(playerid); SetPlayerCheckpoint(playerid,2719.0520,-2503.5962,12.7706,8.0); }
	else if(CP[playerid] == 16) { CP[playerid] = 17; DisablePlayerCheckpoint(playerid); SetPlayerCheckpoint(playerid,2720.7881,-2405.6589,12.7441,8.0); }
	else if(CP[playerid] == 17) { CP[playerid] = 18; DisablePlayerCheckpoint(playerid); SetPlayerCheckpoint(playerid,2571.5195,-2401.1531,12.7528,8.0); }
	else if(CP[playerid] == 18) { CP[playerid] = 19; DisablePlayerCheckpoint(playerid); SetPlayerCheckpoint(playerid,2406.6995,-2423.1182,12.6641,8.0); }
	else if(CP[playerid] == 19) { CP[playerid] = 20; DisablePlayerCheckpoint(playerid); SetPlayerCheckpoint(playerid,2322.9194,-2341.5715,12.6664,8.0); }
	else if(CP[playerid] == 20)//End of Karting
	{
	    CP[playerid] = 0;
	    DisablePlayerCheckpoint(playerid);
	    GetPlayerName(playerid, name, sizeof(name));
	    if(FirstKartWinner == 999)
	    {
	        FirstKartWinner = playerid;
	        for(new i = 0; i < MAX_PLAYERS; i++)
	        {
	            if(IsPlayerConnected(i))
	            {
		            if(PlayerKarting[i] != 0 && PlayerInKart[i] != 0)
		            {
		                format(string, sizeof(string), "* %s finished First in the Kart Race.",name);
		                SendClientMessage(i, COLOR_WHITE, string);
		            }
				}
			}
	    }
	    else if(SecondKartWinner == 999)
	    {
	        SecondKartWinner = playerid;
	        for(new i = 0; i < MAX_PLAYERS; i++)
	        {
	            if(IsPlayerConnected(i))
	            {
		            if(PlayerKarting[i] != 0 && PlayerInKart[i] != 0)
		            {
		                format(string, sizeof(string), "* %s finished Second in the Kart Race.",name);
		                SendClientMessage(i, COLOR_WHITE, string);
		            }
				}
			}
	    }
	    else if(ThirdKartWinner == 999)
	    {
	        ThirdKartWinner = playerid;
	        for(new i = 0; i < MAX_PLAYERS; i++)
	        {
	            if(IsPlayerConnected(i))
	            {
		            if(PlayerKarting[i] != 0 && PlayerInKart[i] != 0)
		            {
		                format(string, sizeof(string), "* %s finished Third in the Kart Race.",name);
		                SendClientMessage(i, COLOR_WHITE, string);
		                SendClientMessage(i, COLOR_WHITE, "** Karting Race Over **");
		                CP[i] = 0;
		                DisablePlayerCheckpoint(i);
		            }
				}
	        }
	    }
	}
	else if(MissionCheckpoint[playerid] > 0 && PlayMission[kToggle] == 1)//Missions + Checkpoint on toggle
	{
        	RingTone[playerid] = 20;
		    switch(MissionCheckpoint[playerid])
		    {
	        	case 1:
		        {
					format(string, sizeof(string), "%s", PlayMission[kGText1]);
					GameTextForPlayer(playerid, string, 8000, 3);
					format(string, sizeof(string), "%s", PlayMission[kText4]);
					SendClientMessage(playerid, COLOR_YELLOW2, string);
					format(string, sizeof(string), "%s", PlayMission[kText5]);
					SendClientMessage(playerid, COLOR_YELLOW2, string);
					format(string, sizeof(string), "%s", PlayMission[kText6]);
					SendClientMessage(playerid, COLOR_YELLOW2, string);
					DisablePlayerCheckpoint(playerid);
					SetPlayerCheckpoint(playerid, PlayMission[kCP2][0], PlayMission[kCP2][1], PlayMission[kCP2][2], 8);
					MissionCheckpoint[playerid] = 2;
		        }
		        case 2:
		        {
		            format(string, sizeof(string), "%s", PlayMission[kGText2]);
					GameTextForPlayer(playerid, string, 8000, 3);
					format(string, sizeof(string), "%s", PlayMission[kText7]);
					SendClientMessage(playerid, COLOR_YELLOW2, string);
					format(string, sizeof(string), "%s", PlayMission[kText8]);
					SendClientMessage(playerid, COLOR_YELLOW2, string);
					format(string, sizeof(string), "%s", PlayMission[kText9]);
					SendClientMessage(playerid, COLOR_YELLOW2, string);
					DisablePlayerCheckpoint(playerid);
					SetPlayerCheckpoint(playerid, PlayMission[kCP3][0], PlayMission[kCP3][1], PlayMission[kCP3][2], 8);
					MissionCheckpoint[playerid] = 3;
		        }
		        case 3:
		        {
		            format(string, sizeof(string), "%s", PlayMission[kGText3]);
					GameTextForPlayer(playerid, string, 8000, 3);
					format(string, sizeof(string), "%s", PlayMission[kText10]);
					SendClientMessage(playerid, COLOR_YELLOW2, string);
					format(string, sizeof(string), "%s", PlayMission[kText11]);
					SendClientMessage(playerid, COLOR_YELLOW2, string);
					format(string, sizeof(string), "%s", PlayMission[kText12]);
					SendClientMessage(playerid, COLOR_YELLOW2, string);
					DisablePlayerCheckpoint(playerid);
					SetPlayerCheckpoint(playerid, PlayMission[kCP4][0], PlayMission[kCP4][1], PlayMission[kCP4][2], 8);
					MissionCheckpoint[playerid] = 4;
		        }
		        case 4:
		        {
		            format(string, sizeof(string), "%s", PlayMission[kGText4]);
					GameTextForPlayer(playerid, string, 8000, 3);
					format(string, sizeof(string), "%s", PlayMission[kText13]);
					SendClientMessage(playerid, COLOR_YELLOW2, string);
					format(string, sizeof(string), "%s", PlayMission[kText14]);
					SendClientMessage(playerid, COLOR_YELLOW2, string);
					format(string, sizeof(string), "%s", PlayMission[kText15]);
					SendClientMessage(playerid, COLOR_YELLOW2, string);
					DisablePlayerCheckpoint(playerid);
					SetPlayerCheckpoint(playerid, PlayMission[kCP5][0], PlayMission[kCP5][1], PlayMission[kCP5][2], 8);
					MissionCheckpoint[playerid] = 5;
		        }
		        case 5:
		        {
		            format(string, sizeof(string), "%s", PlayMission[kGText5]);
					GameTextForPlayer(playerid, string, 8000, 3);
					format(string, sizeof(string), "%s", PlayMission[kText16]);
					SendClientMessage(playerid, COLOR_YELLOW2, string);
					format(string, sizeof(string), "%s", PlayMission[kText17]);
					SendClientMessage(playerid, COLOR_YELLOW2, string);
					format(string, sizeof(string), "%s", PlayMission[kText18]);
					SendClientMessage(playerid, COLOR_YELLOW2, string);
					DisablePlayerCheckpoint(playerid);
					SetPlayerCheckpoint(playerid, PlayMission[kCP6][0], PlayMission[kCP6][1], PlayMission[kCP6][2], 8);
					MissionCheckpoint[playerid] = 6;
		        }
		        case 6:
		        {
		            format(string, sizeof(string), "%s", PlayMission[kGText6]);
					GameTextForPlayer(playerid, string, 8000, 3);
					format(string, sizeof(string), "..:: Mission Passed : %s | Reward received: $%d ::..", PlayMission[kTitle], PlayMission[kReward]);
					SendClientMessage(playerid, COLOR_GREEN, string);
					DisablePlayerCheckpoint(playerid);
					GivePlayerMoney(playerid, PlayMission[kReward]);
					PlayerInfo[playerid][pMissionNr] = PlayerOnMission[playerid];
					MissionCheckpoint[playerid] = 0;
					PlayerOnMission[playerid] = 0;
		        }
		    }
	}
	else
	{
		switch (gPlayerCheckpointStatus[playerid])
		{
			case CHECKPOINT_HOME:
		    {
				PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
				DisablePlayerCheckpoint(playerid);
				gPlayerCheckpointStatus[playerid] = CHECKPOINT_NONE;
				GameTextForPlayer(playerid, "~w~You are~n~~y~Home", 5000, 1);
		    }
		}
	}
	return 1;
}

sampCallback OnPlayerLeaveCheckpoint(playerid)
{
	return 1;
}

sampCallback OnPlayerEnterRaceCheckpoint(playerid)
{
	return 1;
}

sampCallback OnPlayerLeaveRaceCheckpoint(playerid)
{
	return 1;
}

sampCallback OnRconCommand(cmd[])
{
	return 1;
}

public OnPlayerRequestSpawn(playerid) {
	return 0;
}

sampCallback OnObjectMoved(objectid)
{
	return 1;
}

sampCallback OnPlayerObjectMoved(playerid, objectid)
{
	return 1;
}

sampCallback OnPlayerPickUpPickup(playerid, pickupid)
{
	return 1;
}

sampCallback OnPlayerSelectedMenuRow(playerid, row)
{
	return 1;
}

sampCallback OnPlayerExitedMenu(playerid)
{
	return 1;
}

sampCallback OnPlayerStateChange(playerid, newstate, oldstate)
{
	new string[256];
	if(newstate == PLAYER_STATE_ONFOOT)
	{
	    if(PlayerKarting[playerid] > 0 && PlayerInKart[playerid] > 0)
		{
		    PlayerInKart[playerid] = 0;
		    KartingPlayers --;
		}
	    if(TransportDuty[playerid] > 0)
		{
		    if(TransportDuty[playerid] == 1)
			{
		        TaxiDrivers -= 1;
			}
			else if(TransportDuty[playerid] == 2)
			{
			    BusDrivers -= 1;
			}
			TransportDuty[playerid] = 0;
			format(string, sizeof(string), "* You are now Off Duty and earned $%d.", TransportMoney[playerid]);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
			GivePlayerMoney(playerid, TransportMoney[playerid]);
			ConsumingMoney[playerid] = 1; TransportValue[playerid] = 0; TransportMoney[playerid] = 0;
		}
		if(TransportCost[playerid] > 0 && TransportDriver[playerid] < 999)
		{
		    if(IsPlayerConnected(TransportDriver[playerid]))
			{
			    TransportMoney[TransportDriver[playerid]] += TransportCost[playerid];
			    TransportTime[TransportDriver[playerid]] = 0;
			    TransportCost[TransportDriver[playerid]] = 0;
			    format(string, sizeof(string), "~w~The ride cost~n~~r~$%d",TransportCost[playerid]);
			    GameTextForPlayer(playerid, string, 5000, 1);
			    format(string, sizeof(string), "~w~Passenger left the taxi~n~~g~Earned $%d",TransportCost[playerid]);
			    GameTextForPlayer(TransportDriver[playerid], string, 5000, 1);
				GivePlayerMoney(playerid, -TransportCost[playerid]);
				TransportCost[playerid] = 0;
				TransportTime[playerid] = 0;
				TransportDriver[playerid] = 999;
			}
		}
		TelePos[playerid][0] = 0.0;
		TelePos[playerid][1] = 0.0;
	}
	if(newstate == PLAYER_STATE_PASSENGER) // TAXI & BUSSES
	{
	    new name[MAX_PLAYER_NAME];
	    GetPlayerName(playerid, name, sizeof(name));
	    new vehicleid = GetPlayerVehicleID(playerid);
	    for(new i = 0; i < MAX_PLAYERS; i++)
	    {
	        if(IsPlayerConnected(i))
	        {
	            if(IsPlayerInVehicle(i, vehicleid) && GetPlayerState(i) == 2 && TransportDuty[i] > 0)
	            {
	                if(GetPlayerMoney(playerid) < TransportValue[i])
	                {
	                    format(string, sizeof(string), "* You need $%d to enter.", TransportValue[i]);
						SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
						RemovePlayerFromVehicle(playerid);
	                }
	                else
	                {
	                    if(TransportDuty[i] == 1)
	                    {
	                        format(string, sizeof(string), "* You paid $%d to the Taxi Driver.", TransportValue[i]);
							SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
							format(string, sizeof(string), "* Passenger %s has entered your Taxi.", name);
							SendClientMessage(i, COLOR_LIGHTBLUE, string);
							TransportTime[i] = 1;
	                    	TransportTime[playerid] = 1;
	                    	TransportCost[playerid] = TransportValue[i];
	                    	TransportCost[i] = TransportValue[i];
	                    	TransportDriver[playerid] = i;
	                    }
	                    else if(TransportDuty[i] == 2)
	                    {
	                        format(string, sizeof(string), "* You paid $%d to the Bus Driver.", TransportValue[i]);
							SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
							format(string, sizeof(string), "* Passenger %s has entered your Bus.", name);
							SendClientMessage(i, COLOR_LIGHTBLUE, string);
	                    }
						GivePlayerMoney(playerid, - TransportValue[i]);
						TransportMoney[i] += TransportValue[i];
	                }
	            }
	        }
	    }
	}
	if(newstate == PLAYER_STATE_WASTED)
	{
		if(WantedLevel[playerid] >= 1)
		{
		    new price = WantedLevel[playerid] * 4000;
			new count;
			for(new i = 0; i < MAX_PLAYERS; i++)
			{
				if(IsPlayerConnected(i))
				{
				    if(gTeam[i] == 2 && CrimInRange(30.0, playerid,i))
				    {
						count = 1;
						format(string, sizeof(string), "~w~Running Suspect~r~Killed~n~Bonus~g~$%d", price);
						GameTextForPlayer(i, string, 5000, 1);
						ConsumingMoney[i] = 1;
						GivePlayerMoney(i, price / 2);
						PlayerPlaySound(i, 1058, 0.0, 0.0, 0.0);
					}
				}
			}
			if(count == 1)
			{
				GivePlayerMoney(playerid, - price);
				PlayerInfo[playerid][pWantedDeaths] += 1;
				PlayerInfo[playerid][pJailed] = 1;
			    PlayerInfo[playerid][pJailTime] = (WantedLevel[playerid])*(600);
			    format(string, sizeof(string), "* You are in Jail for %d Seconds and lose $%d because of running away and getting shot by the Officer.", PlayerInfo[playerid][pJailTime], price);
			    SendClientMessage(playerid, COLOR_LIGHTRED, string);
			    WantedPoints[playerid] = 0;
				WantedLevel[playerid] = 0;
			}
		}
	}
	if(newstate == PLAYER_STATE_DRIVER) //buggy dont finnish
	{// 38 / 49 / 56 = SS
		new newcar = GetPlayerVehicleID(playerid);
		new oldcar = gLastCar[playerid];
		new housecar = PlayerInfo[playerid][pPhousekey]+1;
		TelePos[playerid][0] = 0.0;
		TelePos[playerid][1] = 0.0;
		if(IsABoat(newcar))
		{
		    if(PlayerInfo[playerid][pBoatLic] < 1)
			{
			    SendClientMessage(playerid, COLOR_GREY, "   You don't know how to Sail yet, so you left the Boat !");
			    RemovePlayerFromVehicle(playerid);
			}
		}
		else if(IsAPlane(newcar))
		{
		    if(PlayerInfo[playerid][pFlyLic] < 1)
			{
			    if(TakingLesson[playerid] == 1) { }
			    else {
			    SendClientMessage(playerid, COLOR_GREY, "   You don't know how to Fly yet, so you left the Plane !");
			    RemovePlayerFromVehicle(playerid); }
			}
		}
		else
		{
			if(PlayerInfo[playerid][pCarLic] < 1)
			{
			    if(PlayerDrunk[playerid] >= 5)
				{
				    WantedPoints[playerid] += 1;
					SetPlayerCriminal(playerid,255, "Drunk Driving");
				}
				if(TakingLesson[playerid] == 1) { }
				else {
				SendClientMessage(playerid, COLOR_GREY, "   You don't know how to Drive yet, so you left the Car !");
                RemovePlayerFromVehicle(playerid); }
			}
			else if(PlayerDrunk[playerid] >= 5)
			{
			    WantedPoints[playerid] += 1;
				SetPlayerCriminal(playerid,255, "Drunk Driving");
			}
		}//Done with car check
		if(IsACopCar(newcar))
		{
		    if(IsACop(playerid)) { }
		    else { RemovePlayerFromVehicle(playerid); }
		}
		else if(IsAnAmbulance(newcar))
		{
		    if(PlayerInfo[playerid][pMember] == 4||PlayerInfo[playerid][pLeader] == 4) { }
		    else { RemovePlayerFromVehicle(playerid); }
		}
		if(IsATruck(newcar))
		{
			format(string, sizeof(string), "Products: %d/%d", PlayerHaul[newcar][pLoad],PlayerHaul[newcar][pCapasity]);
			SendClientMessage(playerid, TEAM_GROVE_COLOR, string);
			SendClientMessage(playerid, COLOR_WHITE, "INFO: You can deliver Products to Businesses.");
			SendClientMessage(playerid, COLOR_WHITE, "INFO: Commands are /load /buyprods /sellprods");
		}
		if(PlayerKarting[playerid] != 0)
		{
		    new kart = GetPlayerVehicleID(playerid);
		    if(kart==110||kart==111||kart==112||kart==113||kart==114||kart==115)
		    {
		        PlayerInKart[playerid] = 1;
		    	KartingPlayers ++;
			}
		}
		if(newcar == 39 || newcar == 40)
		{
		    if(PlayerInfo[playerid][pMember] == 3 || PlayerInfo[playerid][pLeader] == 3)//national guard
		    {
		        if(PlayerInfo[playerid][pRank] < 3)
		        {
			        SendClientMessage(playerid,COLOR_GREY,"   You need Rank 3 to Fly this baby !");
			        RemovePlayerFromVehicle(playerid);
		        }
		    }
		    else
		    {
		        RemovePlayerFromVehicle(playerid);
		    }
		}
		if(newcar == 55 || newcar == 59)
		{
		    if(PlayerInfo[playerid][pMember] != 4)
		    {
		        SendClientMessage(playerid,COLOR_GREY,"   You are not a Fireman !");
		        RemovePlayerFromVehicle(playerid);
		    }
		}
		if(newcar == 64 || newcar == 65)
		{
		    if(PlayerInfo[playerid][pJob] != 14)
		    {
		        SendClientMessage(playerid,COLOR_GREY,"   You are not a Bus Driver !");
		        RemovePlayerFromVehicle(playerid);
		    }
		}
		if(newcar == 69 || newcar == 70 || newcar == 71 || newcar == 99 || newcar == 100 || newcar == 101)
		{
		    if(TakingLesson[playerid] == 1) { }
		    else if(!IsAnInstructor(playerid))
		    {
		        SendClientMessage(playerid,COLOR_GREY,"   You are not a School Instructor !");
		        RemovePlayerFromVehicle(playerid);
		    }
		}
		if(newcar == 82 || newcar == 84 || newcar == 85 || newcar == 94)
		{
		    if(PlayerInfo[playerid][pMember] == 10||PlayerInfo[playerid][pLeader] == 10) { }
		    else
			{
		        SendClientMessage(playerid,COLOR_GREY,"   You are not a Taxi Driver !");
		        RemovePlayerFromVehicle(playerid);
		    }
		}
		if(newcar == 95)
		{
		    if(PlayerInfo[playerid][pMember] == 8 || PlayerInfo[playerid][pLeader] == 8)
		    {
		        if(PlayerInfo[playerid][pRank] < 3)
			    {
			        SendClientMessage(playerid, COLOR_GREY, "   Your Rank is to Low !");
				    RemovePlayerFromVehicle(playerid);
			    }
		    }
		    else
		    {
		        SendClientMessage(playerid, COLOR_GREY, "   You are not a Hitman !");
			    RemovePlayerFromVehicle(playerid);
		    }
		}
		if(newcar == 96 || newcar == 97 || newcar == 98)
		{
			if(PlayerInfo[playerid][pMember] == 9 || PlayerInfo[playerid][pLeader] == 9){ }
			else
			{
			    SendClientMessage(playerid, COLOR_GREY, "   You are not a News Reporter !");
			    RemovePlayerFromVehicle(playerid);
			}
			if(PlayerInfo[playerid][pNewsSkill] < 200 && newcar == 96)
			{
			    SendClientMessage(playerid, COLOR_GREY, "   Your News Reporter Skill is to low, cant fly the Chopper yet !");
			    RemovePlayerFromVehicle(playerid);
			}
		}
		if(newcar==110||newcar==111||newcar==112||newcar==113||newcar==114||newcar==115)
		{
		    if(PlayerKarting[playerid] != 1)
		    {
		        RemovePlayerFromVehicle(playerid);
		    }
		}
		if(newcar >= 72 && newcar <= 74)
		{
			if (HireCar[playerid] != newcar)
			{
				format(string, sizeof(string), "~w~You can Rent this car~n~Cost:~g~$%d~n~~w~To rent type ~g~/rentcar~w~~n~to get out type ~r~/exit",SBizzInfo[0][sbEntranceCost]);
				TogglePlayerControllable(playerid, 0);
				GameTextForPlayer(playerid, string, 5000, 3);
			}
		}
		if(newcar >= 75 && newcar <= 77)
		{
			if (HireCar[playerid] != newcar)
			{
				format(string, sizeof(string), "~w~You can Rent this car~n~Cost:~g~$%d~n~~w~To rent type ~g~/rentcar~w~~n~to get out type ~r~/exit",SBizzInfo[1][sbEntranceCost]);
				TogglePlayerControllable(playerid, 0);
				GameTextForPlayer(playerid, string, 5000, 3);
			}
		}
		if(oldcar != 301)
		{
			if((housecar != oldcar && oldcar != 0) && (HireCar[playerid] != oldcar && newcar != housecar))
			{
				if(gLastDriver[oldcar] == playerid && oldcar != newcar)
				{
					gLastDriver[oldcar] = 300;
					gCarLock[oldcar] = 0;
					UnLockCar(oldcar);
				}
			}
		}
		gLastCar[playerid] = newcar;
		gLastDriver[newcar] = playerid;
	}
	if(newstate == PLAYER_STATE_SPAWNED)
	{
		new Float: lwx, Float:lwy, Float:lwz;
		GetPlayerPos(playerid, lwx, lwy, lwz);
		if((lwz > 530.0 && PlayerInfo[playerid][pInt] == 0) || PlayerToPoint(1000.0, playerid, -1041.9,-1868.4,79.1)) //the highest land point in sa = 526.8
		{
			SetPlayerSpawn(playerid);
		}
		if(WantedPoints[playerid] > 0)
		{
		    new dstring[128];
			new wanted = WantedPoints[playerid];
			new diecash = 0;
		    while(WantedPoints[playerid] > 0)
		    {
		        diecash += 500;
		        WantedPoints[playerid] --;
		    }
		    format(dstring, sizeof(dstring), "You lost $%d for dieing with %d Wanted Points.", diecash, wanted);
		    SendClientMessage(playerid, COLOR_YELLOW, dstring);
		    GivePlayerMoney(playerid, - diecash);
		    PlayerInfo[playerid][pWantedDeaths] += 1;
		}
		if(PlayerOnMission[playerid] > 0)
		{
			GameTextForPlayer(playerid, "~r~Mission failed", 5000, 3);
			PlayerOnMission[playerid] = 0;
		    PlayerInfo[playerid][pMissionNr] = 0;
		}
		WantedPoints[playerid] = 0;
		WantedLevel[playerid] = 0;
		if(PlayerInfo[playerid][pDonateRank] > 0) { SetPlayerHealth(playerid, 100.0); }
		else { SetPlayerHealth(playerid, 50.0+PlayerInfo[playerid][pSHealth]); }
		MedicBill[playerid] = 1;
		TelePos[playerid][0] = 0.0;
		TelePos[playerid][1] = 0.0;
		gPlayerSpawned[playerid] = 1;
		SafeTime[playerid] = 60;
	}
	return 1;
}

sampCallback OnPlayerExitVehicle(playerid, vehicleid)
{
	if (GetPlayerState(playerid) == 1)
	{
		return 1;
	}
	if(gGas[playerid] == 1)
	{
	    GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~Left car", 500, 3);
	}
	return 1;
}

sampCallback OnPlayerUpdate(playerid)
{
	if(IsPlayerConnected(playerid))
	{
		if(gPlayerLogged[playerid])
		{
			new string3[32];
			new playername3[MAX_PLAYER_NAME];
			GetPlayerName(playerid, playername3, sizeof(playername3));
			format(string3, sizeof(string3), "%s.ini", playername3);
			new File: hFile = fopen(string3, io_write);
			if (hFile)
			{
				new var[32];
				format(var, 32, "Key=%s\n", PlayerInfo[playerid][pKey]);fwrite(hFile, var);
				PlayerInfo[playerid][pCash] = GetPlayerMoney(playerid);
				format(var, 32, "Level=%d\n",PlayerInfo[playerid][pLevel]);fwrite(hFile, var);
				format(var, 32, "AdminLevel=%d\n",PlayerInfo[playerid][pAdmin]);fwrite(hFile, var);
				format(var, 32, "DonateRank=%d\n",PlayerInfo[playerid][pDonateRank]);fwrite(hFile, var);
				format(var, 32, "UpgradePoints=%d\n",PlayerInfo[playerid][gPupgrade]);fwrite(hFile, var);
				format(var, 32, "ConnectedTime=%d\n",PlayerInfo[playerid][pConnectTime]);fwrite(hFile, var);
				format(var, 32, "Registered=%d\n",PlayerInfo[playerid][pReg]);fwrite(hFile, var);
				format(var, 32, "Sex=%d\n",PlayerInfo[playerid][pSex]);fwrite(hFile, var);
				format(var, 32, "Age=%d\n",PlayerInfo[playerid][pAge]);fwrite(hFile, var);
				format(var, 32, "Origin=%d\n",PlayerInfo[playerid][pOrigin]);fwrite(hFile, var);
				format(var, 32, "CK=%d\n",PlayerInfo[playerid][pCK]);fwrite(hFile, var);
				format(var, 32, "Muted=%d\n",PlayerInfo[playerid][pMuted]);fwrite(hFile, var);
				format(var, 32, "Respect=%d\n",PlayerInfo[playerid][pExp]);fwrite(hFile, var);
				format(var, 32, "Money=%d\n",PlayerInfo[playerid][pCash]);fwrite(hFile, var);
				format(var, 32, "Bank=%d\n",PlayerInfo[playerid][pAccount]);fwrite(hFile, var);
				format(var, 32, "Crimes=%d\n",PlayerInfo[playerid][pCrimes]);fwrite(hFile, var);
				format(var, 32, "Kills=%d\n",PlayerInfo[playerid][pKills]);fwrite(hFile, var);
				format(var, 32, "Deaths=%d\n",PlayerInfo[playerid][pDeaths]);fwrite(hFile, var);
				format(var, 32, "Arrested=%d\n",PlayerInfo[playerid][pArrested]);fwrite(hFile, var);
				format(var, 32, "WantedDeaths=%d\n",PlayerInfo[playerid][pWantedDeaths]);fwrite(hFile, var);
				format(var, 32, "Phonebook=%d\n",PlayerInfo[playerid][pPhoneBook]);fwrite(hFile, var);
				format(var, 32, "LottoNr=%d\n",PlayerInfo[playerid][pLottoNr]);fwrite(hFile, var);
				format(var, 32, "Fishes=%d\n",PlayerInfo[playerid][pFishes]);fwrite(hFile, var);
				format(var, 32, "BiggestFish=%d\n",PlayerInfo[playerid][pBiggestFish]);fwrite(hFile, var);
				format(var, 32, "Job=%d\n",PlayerInfo[playerid][pJob]);fwrite(hFile, var);
				format(var, 32, "Paycheck=%d\n",PlayerInfo[playerid][pPayCheck]);fwrite(hFile, var);
				format(var, 32, "HeadValue=%d\n",PlayerInfo[playerid][pHeadValue]);fwrite(hFile, var);
				format(var, 32, "Jailed=%d\n",PlayerInfo[playerid][pJailed]);fwrite(hFile, var);
				format(var, 32, "JailTime=%d\n",PlayerInfo[playerid][pJailTime]);fwrite(hFile, var);
				format(var, 32, "Materials=%d\n",PlayerInfo[playerid][pMats]);fwrite(hFile, var);
				format(var, 32, "Drugs=%d\n",PlayerInfo[playerid][pDrugs]);fwrite(hFile, var);
				format(var, 32, "Leader=%d\n",PlayerInfo[playerid][pLeader]);fwrite(hFile, var);
				format(var, 32, "Member=%d\n",PlayerInfo[playerid][pMember]);fwrite(hFile, var);
				format(var, 32, "FMember=%d\n",PlayerInfo[playerid][pFMember]);fwrite(hFile, var);
				format(var, 32, "Rank=%d\n",PlayerInfo[playerid][pRank]);fwrite(hFile, var);
				format(var, 32, "Char=%d\n",PlayerInfo[playerid][pChar]);fwrite(hFile, var);
				format(var, 32, "ContractTime=%d\n",PlayerInfo[playerid][pContractTime]);fwrite(hFile, var);
				format(var, 32, "DetSkill=%d\n",PlayerInfo[playerid][pDetSkill]);fwrite(hFile, var);
				format(var, 32, "SexSkill=%d\n",PlayerInfo[playerid][pSexSkill]);fwrite(hFile, var);
				format(var, 32, "BoxSkill=%d\n",PlayerInfo[playerid][pBoxSkill]);fwrite(hFile, var);
				format(var, 32, "LawSkill=%d\n",PlayerInfo[playerid][pLawSkill]);fwrite(hFile, var);
				format(var, 32, "MechSkill=%d\n",PlayerInfo[playerid][pMechSkill]);fwrite(hFile, var);
				format(var, 32, "JackSkill=%d\n",PlayerInfo[playerid][pJackSkill]);fwrite(hFile, var);
				format(var, 32, "CarSkill=%d\n",PlayerInfo[playerid][pCarSkill]);fwrite(hFile, var);
				format(var, 32, "NewsSkill=%d\n",PlayerInfo[playerid][pNewsSkill]);fwrite(hFile, var);
				format(var, 32, "DrugsSkill=%d\n",PlayerInfo[playerid][pDrugsSkill]);fwrite(hFile, var);
				format(var, 32, "CookSkill=%d\n",PlayerInfo[playerid][pCookSkill]);fwrite(hFile, var);
				format(var, 32, "FishSkill=%d\n",PlayerInfo[playerid][pFishSkill]);fwrite(hFile, var);
				format(var, 32, "pSHealth=%.1f\n",PlayerInfo[playerid][pSHealth]);fwrite(hFile, var);
	            GetPlayerHealth(playerid,PlayerInfo[playerid][pHealth]);
				format(var, 32, "pHealth=%.1f\n",PlayerInfo[playerid][pHealth]);fwrite(hFile, var);
				format(var, 32, "Int=%d\n",PlayerInfo[playerid][pInt]);fwrite(hFile, var);
				format(var, 32, "Local=%d\n",PlayerInfo[playerid][pLocal]);fwrite(hFile, var);
				format(var, 32, "Team=%d\n",PlayerInfo[playerid][pTeam]);fwrite(hFile, var);
				format(var, 32, "Model=%d\n",PlayerInfo[playerid][pModel]);fwrite(hFile, var);
				format(var, 32, "PhoneNr=%d\n",PlayerInfo[playerid][pPnumber]);fwrite(hFile, var);
				format(var, 32, "House=%d\n",PlayerInfo[playerid][pPhousekey]);fwrite(hFile, var);
				format(var, 32, "Bizz=%d\n",PlayerInfo[playerid][pPbiskey]);fwrite(hFile, var);
				if ((PlayerInfo[playerid][pPos_x]==0.0 && PlayerInfo[playerid][pPos_y]==0.0 && PlayerInfo[playerid][pPos_z]==0.0))
				{
					PlayerInfo[playerid][pPos_x] = 1684.9;
					PlayerInfo[playerid][pPos_y] = -2244.5;
					PlayerInfo[playerid][pPos_z] = 13.5;
				}
				if(Spectate[playerid] != 255)
				{
					PlayerInfo[playerid][pPos_x] = Unspec[playerid][sPx];
					PlayerInfo[playerid][pPos_y] = Unspec[playerid][sPy];
					PlayerInfo[playerid][pPos_z] = Unspec[playerid][sPz];
					PlayerInfo[playerid][pInt] = Unspec[playerid][sPint];
					PlayerInfo[playerid][pLocal] = Unspec[playerid][sLocal];
				}
				format(var, 32, "Pos_x=%.1f\n",PlayerInfo[playerid][pPos_x]);fwrite(hFile, var);
				format(var, 32, "Pos_y=%.1f\n",PlayerInfo[playerid][pPos_y]);fwrite(hFile, var);
				format(var, 32, "Pos_z=%.1f\n",PlayerInfo[playerid][pPos_z]);fwrite(hFile, var);
				format(var, 32, "CarLic=%d\n",PlayerInfo[playerid][pCarLic]);fwrite(hFile, var);
                format(var, 32, "FlyLic=%d\n",PlayerInfo[playerid][pFlyLic]);fwrite(hFile, var);
				format(var, 32, "BoatLic=%d\n",PlayerInfo[playerid][pBoatLic]);fwrite(hFile, var);
				format(var, 32, "FishLic=%d\n",PlayerInfo[playerid][pFishLic]);fwrite(hFile, var);
				format(var, 32, "GunLic=%d\n",PlayerInfo[playerid][pGunLic]);fwrite(hFile, var);
				format(var, 32, "Gun1=%d\n",PlayerInfo[playerid][pGun1]);fwrite(hFile, var);
				format(var, 32, "Gun2=%d\n",PlayerInfo[playerid][pGun2]);fwrite(hFile, var);
				format(var, 32, "Gun3=%d\n",PlayerInfo[playerid][pGun3]);fwrite(hFile, var);
				format(var, 32, "Gun4=%d\n",PlayerInfo[playerid][pGun4]);fwrite(hFile, var);
				format(var, 32, "Ammo1=%d\n",PlayerInfo[playerid][pAmmo1]);fwrite(hFile, var);
				format(var, 32, "Ammo2=%d\n",PlayerInfo[playerid][pAmmo2]);fwrite(hFile, var);
				format(var, 32, "Ammo3=%d\n",PlayerInfo[playerid][pAmmo3]);fwrite(hFile, var);
				format(var, 32, "Ammo4=%d\n",PlayerInfo[playerid][pAmmo4]);fwrite(hFile, var);
				format(var, 32, "CarTime=%d\n",PlayerInfo[playerid][pCarTime]);fwrite(hFile, var);
				format(var, 32, "PayDay=%d\n",PlayerInfo[playerid][pPayDay]);fwrite(hFile, var);
				format(var, 32, "PayDayHad=%d\n",PlayerInfo[playerid][pPayDayHad]);fwrite(hFile, var);
				format(var, 32, "CDPlayer=%d\n",PlayerInfo[playerid][pCDPlayer]);fwrite(hFile, var);
				format(var, 32, "Wins=%d\n",PlayerInfo[playerid][pWins]);fwrite(hFile, var);
				format(var, 32, "Loses=%d\n",PlayerInfo[playerid][pLoses]);fwrite(hFile, var);
				format(var, 32, "AlcoholPerk=%d\n",PlayerInfo[playerid][pAlcoholPerk]);fwrite(hFile, var);
				format(var, 32, "DrugPerk=%d\n",PlayerInfo[playerid][pDrugPerk]);fwrite(hFile, var);
				format(var, 32, "MiserPerk=%d\n",PlayerInfo[playerid][pMiserPerk]);fwrite(hFile, var);
				format(var, 32, "PainPerk=%d\n",PlayerInfo[playerid][pPainPerk]);fwrite(hFile, var);
				format(var, 32, "TraderPerk=%d\n",PlayerInfo[playerid][pTraderPerk]);fwrite(hFile, var);
				format(var, 32, "Tutorial=%d\n",PlayerInfo[playerid][pTut]);fwrite(hFile, var);
				format(var, 32, "Mission=%d\n",PlayerInfo[playerid][pMissionNr]);fwrite(hFile, var);
				format(var, 32, "Warnings=%d\n",PlayerInfo[playerid][pWarns]);fwrite(hFile, var);
				format(var, 32, "Adjustable=%d\n",PlayerInfo[playerid][pAdjustable]);fwrite(hFile, var);
				if(PlayerInfo[playerid][pDonateRank] < 1) { PlayerInfo[playerid][pFuel] = 0; }
				format(var, 32, "Fuel=%d\n",PlayerInfo[playerid][pFuel]);fwrite(hFile, var);
				format(var, 32, "Married=%d\n",PlayerInfo[playerid][pMarried]);fwrite(hFile, var);
				format(var, 32, "MarriedTo=%s\n",PlayerInfo[playerid][pMarriedTo]);fwrite(hFile, var);
				fclose(hFile);
			}
		}
	}
	return 1;
}

Callback SyncUp()
{
	SyncTime();
	DollahScoreUpdate();
}

Callback PreparePaintball()
{
    for(new i = 0; i < MAX_PLAYERS; i++)
	{
	    if(IsPlayerConnected(i))
	    {
	        if(PlayerPaintballing[i] != 0)
	        {
	            SendClientMessage(i, COLOR_YELLOW, "Paintball Match will start in 20 seconds.");
	        }
		}
	}
 	SetTimer("StartPaintball", 20000, 0);
	return 1;
}

Callback StartPaintball()
{
	PaintballRound = 1;
	StartingPaintballRound = 0;
	PaintballWinner = 999;
	PaintballWinnerKills = 0;
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
	    if(IsPlayerConnected(i))
	    {
	        if(PlayerPaintballing[i] != 0)
	        {
	            ResetPlayerWeapons(i);
	            GivePlayerWeapon(i, 29, 999);
	            TogglePlayerControllable(i, 1);
	            SendClientMessage(i, COLOR_YELLOW, "Paintball Match started, 4 minutes left.");
	            PlayerPlaySound(i, 1057, 0.0, 0.0, 0.0);
	        }
	    }
	}
	SetTimer("PaintballEnded", 240000, 0);
	return 1;
}

Callback PaintballEnded()
{
	new string[256];
	new name[MAX_PLAYER_NAME];
    for(new i = 0; i < MAX_PLAYERS; i++)
	{
	    if(IsPlayerConnected(i))
	    {
	        if(PlayerPaintballing[i] != 0)
	        {
	            if(IsPlayerConnected(PaintballWinner))
	            {
	                GetPlayerName(PaintballWinner, name, sizeof(name));
	                format(string,sizeof(string), "** %s won the Paintball Match with %d kills **",name,PaintballWinnerKills);
	                SendClientMessage(i, COLOR_WHITE, string);
	            }
	            ResetPlayerWeapons(i);
	            PlayerPaintballing[i] = 0;
	            SetPlayerPos(i, SBizzInfo[10][sbEntranceX],SBizzInfo[10][sbEntranceY],SBizzInfo[10][sbEntranceZ]);
	        }
		}
	}
	AnnouncedPaintballRound = 0;
    PaintballRound = 0;
	return 1;
}

Callback PrepareKarting()
{
    for(new i = 0; i < MAX_PLAYERS; i++)
	{
	    if(IsPlayerConnected(i))
	    {
	        if(PlayerKarting[i] != 0 && PlayerInKart[i] != 0)
	        {
	            CP[i] = 9;
				SetPlayerCheckpoint(i,2308.3540,-2354.0039,12.6842,8.0);
				SendClientMessage(i, COLOR_YELLOW, "Kart Race will start in 20 seconds, go to the starting line.");
	        }
		}
	}
	SetTimer("StartKarting", 20000, 0);
	return 1;
}

Callback StartKarting()
{
	KartingRound = 1;
	StartingKartRound = 0;
	EndingKartRound = 0;
	FirstKartWinner = 999;
	SecondKartWinner = 999;
	ThirdKartWinner = 999;
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
	    if(IsPlayerConnected(i))
	    {
	        if(PlayerKarting[i] != 0 && PlayerInKart[i] != 0)
	        {
	            CP[i] = 10;
	            SendClientMessage(i, COLOR_YELLOW, "Green light, go go go !");
	            PlayerPlaySound(i, 1057, 0.0, 0.0, 0.0);
	            SetPlayerCheckpoint(i,2308.3540,-2354.0039,12.6842,8.0);
	        }
	    }
	}
	SetTimer("KartingEnded", 240000, 0);
	return 1;
}

Callback KartingEnded()
{
    for(new i = 0; i < MAX_PLAYERS; i++)
	{
	    if(IsPlayerConnected(i))
	    {
	        if(PlayerKarting[i] != 0 && PlayerInKart[i] != 0)
	        {
	            CP[i] = 0;
	            DisablePlayerCheckpoint(i);
	        }
		}
	}
	AnnouncedKartRound = 0;
    KartingRound = 0;
	return 1;
}

Callback Spectator()
{
	new string[256];
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i))
		{
		    if(KickPlayer[i]==1) { Kick(i); }
			else if(KickPlayer[i]==2) { Ban(i); }
			//if(GetPlayerPing(i) >= 500 && PlayerInfo[i][pAdmin] < 1) { Kick(i); }
			if(Spectate[i] < 253 && Spectate[i] != 255)
			{
				SetPlayerColor(i,COLOR_SPEC);
				TogglePlayerControllable(i, 0);
				new targetid = Spectate[i];
				if(IsPlayerConnected(targetid))
				{
				    TogglePlayerSpectating(i, 1);
				    if(PlayerInfo[i][pAdmin] >= 1)
				    {
				        new Float:health;
					    new name[MAX_PLAYER_NAME];
					    GetPlayerName(targetid, name, sizeof(name));
					    GetPlayerHealth(targetid, health);
					    format(string, sizeof(string), "~n~~n~~n~~n~~n~~n~~y~%s(ID:%d)~n~~y~health:%.1f",name,targetid,health);
					    GameTextForPlayer(i, string, 2500, 3);
				    }
				    if(IsPlayerInAnyVehicle(targetid))
					{
					    new carid = GetPlayerVehicleID(targetid);
					    PlayerSpectateVehicle(i, carid);
					}
					else
					{
					    PlayerSpectatePlayer(i, targetid);
					}
					if(GetPlayerInterior(targetid) == 0)
					{
						SetPlayerInterior(i,0);
					}
					else if(GetPlayerInterior(targetid) > 0)
					{
						SetPlayerInterior(i,GetPlayerInterior(targetid));
					}
				}//Targetid connected
			}
			if(Spectate[i] == 253)
			{
				TogglePlayerControllable(i, 1);
				TogglePlayerSpectating(i, 0);
				SetPlayerInterior(i,Unspec[i][sPint]);
				PlayerInfo[i][pInt] = Unspec[i][sPint];
				PlayerInfo[i][pLocal] = Unspec[i][sLocal];
				Unspec[i][sLocal] = 255;
				SetSpawnInfo(i, PlayerInfo[i][pTeam], PlayerInfo[i][pModel], Unspec[i][sPx],  Unspec[i][sPy], Unspec[i][sPz]-1.0, 1.0, -1, -1, -1, -1, -1, -1);
				gTeam[i] = PlayerInfo[i][pTeam];
				SetPlayerToTeamColor(i);
				MedicBill[i] = 0;
				if(PlayerInfo[i][pDonateRank] > 0)
		        {
		            SetSpawnInfo(i, PlayerInfo[i][pTeam], PlayerInfo[i][pModel], Unspec[i][Coords][0], Unspec[i][Coords][1], Unspec[i][Coords][2], 10.0, -1, -1, -1, -1, -1, -1);
					SpawnPlayer(i);
					SetCameraBehindPlayer(i);
		        }
		        else
		        {
					SpawnPlayer(i);
				}
				Spectate[i] = 255;
			}
			if(Spectate[i] == 254)
			{
				TogglePlayerControllable(i, 1);
				SetPlayerInterior(i,Unspec[i][sPint]);
				PlayerInfo[i][pInt] = Unspec[i][sPint];
				PlayerInfo[i][pLocal] = Unspec[i][sLocal];
				SetPlayerPos(i, Unspec[i][sPx],  Unspec[i][sPy], Unspec[i][sPz]);
				Spectate[i] = 255;
			}
			if(Spectate[i] == 256)
			{
				SetPlayerToTeamColor(i);
				Spectate[i] = 255;
			}
			if(Spectate[i] == 257)
			{
				Spectate[i] = 254;
			}
		}
	}
}


Callback RingToner()
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
	    if(IsPlayerConnected(i))
	    {
			if(RingTone[i] != 6 && RingTone[i] != 0 && RingTone[i] < 11)
			{
				RingTone[i] = RingTone[i] -1;
				PlayerPlaySound(i, 1138, 0.0, 0.0, 0.0);
			}
			if(RingTone[i] == 6)
			{
				RingTone[i] = RingTone[i] -1;
			}
			if(RingTone[i] == 20)
			{
				RingTone[i] = RingTone[i] -1;
				PlayerPlaySound(i, 1139, 0.0, 0.0, 0.0);
			}
		}
	}
	SetTimer("RingTonerRev", 1000, 0);
	return 1;
}

Callback RingTonerRev()
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
	    if(IsPlayerConnected(i))
	    {
			if(RingTone[i] != 5 && RingTone[i] != 0 && RingTone[i] < 10)
			{
				RingTone[i] = RingTone[i] -1;
				PlayerPlaySound(i, 1137, 0.0, 0.0, 0.0);
			}
			if(RingTone[i] == 5)
			{
				RingTone[i] = RingTone[i] -1;
			}
			if(RingTone[i] == 19)
			{
				PlayerPlaySound(i, 1139, 0.0, 0.0, 0.0);
				RingTone[i] = 0;
			}
		}
	}
	SetTimer("RingToner", 1000, 0);
	return 1;
}

Callback OtherTimer()
{
    new Float:maxspeed = 175.0;
    new plname[MAX_PLAYER_NAME];
	new string[256];
	new Float:oldposx, Float:oldposy, Float:oldposz;
    for(new i = 0; i < MAX_PLAYERS; i++)
	{
	    if(IsPlayerConnected(i))
	    {
            if(SafeTime[i] > 0)
			{
				SafeTime[i]--;
			}
			if(SafeTime[i] == 1)
			{
				if(gPlayerAccount[i] == 1 && gPlayerLogged[i] == 0)
				{
					SendClientMessage(i, COLOR_WHITE, "HINT: You can now login by typing /login <password>");
				}
			}
		    if(GetPlayerState(i) == 2)
		    {
				GetPlayerPos(i, TelePos[i][3], TelePos[i][4], TelePos[i][5]);
				if(TelePos[i][5] > 550.0)
				{
					TelePos[i][0] = 0.0;
					TelePos[i][1] = 0.0;
				}
				if(TelePos[i][0] != 0.0)
				{
					new Float:xdist = TelePos[i][3]-TelePos[i][0];
					new Float:ydist = TelePos[i][4]-TelePos[i][1];
					new Float:sqxdist = xdist*xdist;
					new Float:sqydist = ydist*ydist;
					new Float:distance = (sqxdist+sqydist)/31;
					if(gSpeedo[i] == 2)
					{
						if(distance <10)
						{
							format(string, 256, "~n~~n~~n~~n~~n~~n~~n~~g~mph :   ~w~%.0f",distance);
						}
						if(distance > 10 && distance < 100)
						{
							format(string, 256, "~n~~n~~n~~n~~n~~n~~n~~g~mph :  ~w~%.0f",distance);
						}
						if(distance > 100)
						{
							format(string, 256, "~n~~n~~n~~n~~n~~n~~n~~g~mph : ~w~%.0f",distance);
						}
						GameTextForPlayer(i, string, 2000, 5);
					}
					if(distance > maxspeed && PlayerInfo[i][pAdmin] < 1)
					{
						new tmpcar = GetPlayerVehicleID(i);
						if(!IsAPlane(tmpcar))
						{
							GetPlayerName(i, plname, sizeof(plname));
							format(string, 256, "AdmWarning: [%d]%s %.0f mph",i,plname,distance);
							ABroadCast(COLOR_YELLOW,string,1);
						}
					}
				}
				if(TelePos[i][5] < 550.0 && TelePos[i][3] != 0.0)
				{
					TelePos[i][0] = TelePos[i][3];
					TelePos[i][1] = TelePos[i][4];
				}
			}
		    if(PlayerInfo[i][pLocal] != 255 && PlayerInfo[i][pInt] != 0)
			{
				new house = PlayerInfo[i][pLocal];
				GetPlayerPos(i, oldposx, oldposy, oldposz);
				if(oldposz != 0.0)
				{
					if(oldposz < 600.0)
					{
						if(house > 10000)
						{
							new tmpcar = GetPlayerVehicleID(i);
							if (!PlayerToPoint(6, i,1040.6,-1021.0,31.7) && house == 10001 ||!PlayerToPoint(6, i,-2720.5,217.5,4.1) && house == 10002 ||!PlayerToPoint(6, i,2644.6,-2044.9,13.3) && house == 10003)
							{
								if (GetPlayerState(i) == 2)
								{
									SetVehiclePos(tmpcar, HouseCarSpawns[tmpcar-1][0], HouseCarSpawns[tmpcar-1][1], HouseCarSpawns[tmpcar-1][2]);
									SetVehicleZAngle(tmpcar, HouseCarSpawns[tmpcar-1][3]);
								}
								else
								{
									SetPlayerPos(i, HouseCarSpawns[tmpcar-1][0], HouseCarSpawns[tmpcar-1][1], HouseCarSpawns[tmpcar-1][2]);
								}
								new oldcash = gSpentCash[i];
								new Total = GetPlayerMoney(i) - oldcash;
								printf("Total %d = GetPlayerMoney(playerid) %d - oldcash %d",Total,GetPlayerMoney(i),oldcash);
								new name[MAX_PLAYER_NAME];
								GetPlayerName(i, name, sizeof(name));
								format(string,128,"<< %s has left the homemodshop with $%d >>",name,Total);
								PayLog(string);
								gSpentCash[i] = 0;
								TelePos[i][0] = 0.0;
								TelePos[i][1] = 0.0;
								PlayerInfo[i][pLocal] = 255;
								SetPlayerInterior(i,0);
								PlayerInfo[i][pInt] = 0;
								Spectate[i] = 255;
							}
						}
						if(house == 241)//City Hall
						{
						    SetPlayerInterior(i,0);
							SetPlayerPos(i,-2162.2554,-2385.9541,30.6250);
							PlayerInfo[i][pInt] = 0;
							PlayerInfo[i][pLocal] = 255;
						}
						if(house == 242)
						{
						    SetPlayerInterior(i,0);
							SetPlayerPos(i,1073.0619,-344.5148,73.9922);
							PlayerInfo[i][pInt] = 0;
							PlayerInfo[i][pLocal] = 255;
						}
						if(house >= 99 && house != 10000)
						{
							SetPlayerPos(i, BizzInfo[house-99][bEntranceX], BizzInfo[house-99][bEntranceY],BizzInfo[house-99][bEntranceZ]); // Warp the player
							PlayerInfo[i][pLocal] = 255;
							SetPlayerInterior(i,0);
							PlayerInfo[i][pInt] = 0;
						}
						else if(house < 99 && house != 10000)
						{
							SetPlayerPos(i, HouseInfo[house][hEntrancex], HouseInfo[house][hEntrancey],HouseInfo[house][hEntrancez]); // Warp the player
							PlayerInfo[i][pLocal] = 255;
							SetPlayerInterior(i,0);
							PlayerInfo[i][pInt] = 0;
						}
					}
				}
			}
		    if(CellTime[i] > 0)
			{
				if (CellTime[i] == cchargetime)
				{
					CellTime[i] = 1;
					if(Mobile[Mobile[i]] == i)
					{
						CallCost[i] = CallCost[i]+callcost;
					}
				}
				CellTime[i] = CellTime[i] +1;
				if (Mobile[Mobile[i]] == 255 && CellTime[i] == 5)
				{
				    if(IsPlayerConnected(Mobile[i]))
				    {
						new called[MAX_PLAYER_NAME];
						GetPlayerName(Mobile[i], called, sizeof(called));
						format(string, sizeof(string), "* %s's phone rings.", called);
						RingTone[Mobile[i]] = 10;
						ProxDetector(30.0, Mobile[i], string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
					}
				}
			}
			if(CellTime[i] == 0 && CallCost[i] > 0)
			{
				format(string, sizeof(string), "~w~The call cost~n~~r~$%d",CallCost[i]);
				GivePlayerMoney(i, -CallCost[i]);
				SBizzInfo[2][sbTill] += CallCost[i];
				ExtortionSBiz(2, CallCost[i]);
				GameTextForPlayer(i, string, 5000, 1);
				CallCost[i] = 0;
			}
			if(TransportTime[i] > 0)
			{//Taxi driver and passenger only
			    if(TransportTime[i] >= 16)
				{
					TransportTime[i] = 1;
					if(TransportDriver[i] < 999)
					{
						if(IsPlayerConnected(TransportDriver[i]))
						{
	      					TransportCost[i] += TransportValue[TransportDriver[i]];
						    TransportCost[TransportDriver[i]] = TransportCost[i];
						}
					}
				}
			    TransportTime[i] += 1;
			    format(string, sizeof(string), "~r~%d ~w~: ~g~$%d",TransportTime[i],TransportCost[i]);
			    GameTextForPlayer(i, string, 15000, 6);
			}
		}
	}
	return 1;
}

Callback SetPlayerUnjail()
{
	new plname[MAX_PLAYER_NAME];
	new string[256];
	if(PaintballPlayers >= 2 && PaintballRound != 1 && StartingPaintballRound != 1)
	{
		StartingPaintballRound = 1;
	   	SetTimer("PreparePaintball", 15000, 0);
	}
	if(KartingPlayers >= 2 && KartingRound != 1 && StartingKartRound != 1)
	{
	    StartingKartRound = 1;
	    SetTimer("PrepareKarting", 15000, 0);
	}
	if(KartingRound != 0 && KartingPlayers < 2)
	{
	    StartingKartRound = 0;
	    KartingRound = 0;
	    EndingKartRound = 1;
	}
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
	    if(IsPlayerConnected(i))
	    {
			new newcar = GetPlayerVehicleID(i);
			new level = PlayerInfo[i][pLevel];
			if(level >= 0 && level <= 2) { PlayerInfo[i][pPayCheck] += 1; }
			else if(level >= 3 && level <= 4) { PlayerInfo[i][pPayCheck] += 2; }
			else if(level >= 5 && level <= 6) { PlayerInfo[i][pPayCheck] += 3; }
			else if(level >= 7 && level <= 8) { PlayerInfo[i][pPayCheck] += 4; }
			else if(level >= 9 && level <= 10) { PlayerInfo[i][pPayCheck] += 5; }
			else if(level >= 11 && level <= 12) { PlayerInfo[i][pPayCheck] += 6; }
			else if(level >= 13 && level <= 14) { PlayerInfo[i][pPayCheck] += 7; }
			else if(level >= 15 && level <= 16) { PlayerInfo[i][pPayCheck] += 8; }
			else if(level >= 17 && level <= 18) { PlayerInfo[i][pPayCheck] += 9; }
			else if(level >= 19 && level <= 20) { PlayerInfo[i][pPayCheck] += 10; }
			else if(level >= 21) { PlayerInfo[i][pPayCheck] += 11; }
		    if(PlayerInfo[i][pJailed] > 0)
		    {
				if(PlayerInfo[i][pJailTime] > 0 && WantLawyer[i] == 0)
				{
					PlayerInfo[i][pJailTime]--;
				}
				if(PlayerInfo[i][pJailTime] <= 0 && WantLawyer[i] == 0)
				{
				    PlayerInfo[i][pJailTime] = 0;
					if(PlayerInfo[i][pJailed] == 1)
					{
						SetPlayerInterior(i, 6);
						SetPlayerPos(i,268.0903,77.6489,1001.0391);
					}
					else if(PlayerInfo[i][pJailed] == 2)
					{
					    SetPlayerWorldBounds(i,20000.0000,-20000.0000,20000.0000,-20000.0000); //Reset world to player
					    SetPlayerInterior(i, 0);
					    SetPlayerPos(i, 90.2101,1920.4854,17.9422);
					}
					PlayerInfo[i][pJailed] = 0;
					SendClientMessage(i, COLOR_GRAD1,"   You have paid your debt to society.");
					format(string, sizeof(string), "~g~Freedom~n~~w~Try to be a better citizen");
					GameTextForPlayer(i, string, 5000, 1);
					if(gTeam[i] == 4) { gTeam[i] = 3; }
					ClearCrime(i);
					SetPlayerToTeamColor(i);
				}
			}
			if(GetPlayerMoney(i) - CurrentMoney[i] >= 50000 && PlayerInfo[i][pAdmin] < 1)
		    {
		        if(ConsumingMoney[i])
		        {
                    CurrentMoney[i] = GetPlayerMoney(i);
					ConsumingMoney[i] = 0;
		        }
		        else
		        {
			        GetPlayerName(i, plname, sizeof(plname));
			        format(string, 256, "AdmWarning: [%d]%s just spawned above $50000 in one second (moneycheat), use /check on him.",i,plname);
					ABroadCast(COLOR_YELLOW,string,1);
					PayLog(string);
			        CurrentMoney[i] = GetPlayerMoney(i);
		        }
		    }
		    else
		    {
		        CurrentMoney[i] = GetPlayerMoney(i);
		    }
		    if(IsABoat(newcar))
			{
			    if(PlayerInfo[i][pBoatLic] < 1 && GetPlayerState(i) == 2)
				{
				    RemovePlayerFromVehicle(i);
				}
			}
			else if(IsAPlane(newcar))
			{
			    if(PlayerInfo[i][pFlyLic] < 1 && GetPlayerState(i) == 2)
				{
				    if(TakingLesson[i] == 1) { }
				    else { RemovePlayerFromVehicle(i); }
				}
			}
			else
			{
				if(PlayerInfo[i][pCarLic] < 1 && IsPlayerInAnyVehicle(i) && GetPlayerState(i) == 2)
				{
					if(TakingLesson[i] == 1) { }
				    else { RemovePlayerFromVehicle(i); }
				}
			}//Done with car check
		    if(UsedFind[i] >= 1)
		    {
		        UsedFind[i] += 1;
				if(UsedFind[i] >= 120)
				{
				    UsedFind[i] = 0;
				}
		    }
			if(MedicTime[i] > 0)
			{
			    if(MedicTime[i] == 3)
			    {
			        SetPlayerInterior(i, 5);
			        new Float:X, Float:Y, Float:Z;
			        GetPlayerPos(i, X,Y,Z);
			        SetPlayerCameraPos(i, X + 3, Y, Z);
			        SetPlayerCameraLookAt(i,X,Y,Z);
			    }
			    MedicTime[i] ++;
			    if(MedicTime[i] >= NeedMedicTime[i])
			    {
					new cut = deathcost; //PlayerInfo[playerid][pLevel]*deathcost;
					GivePlayerMoney(i, -cut);
					format(string, sizeof(string), "DOC: Your Medical Bill comes to $%d, Have a nice day.", cut);
					SendClientMessage(i, TEAM_CYAN_COLOR, string);
					TogglePlayerControllable(i, 1);
			        MedicBill[i] = 0;
			        MedicTime[i] = 0;
			        NeedMedicTime[i] = 0;
			        PlayerInfo[i][pDeaths] += 1;
			        PlayerFixRadio(i);
			        SpawnPlayer(i);
			    }
			}
			if(WantLawyer[i] >= 1)
			{
			    CallLawyer[i] = 111;
			    if(WantLawyer[i] == 1)
				{
				    SendClientMessage(i, COLOR_LIGHTRED, "Do you want a Lawyer? (Type yes or no)");
				}
				WantLawyer[i] ++;
				if(WantLawyer[i] == 8)
				{
				    SendClientMessage(i, COLOR_LIGHTRED, "Do you want a Lawyer? (Type yes or no)");
				}
	            if(WantLawyer[i] == 15)
				{
				    SendClientMessage(i, COLOR_LIGHTRED, "Do you want a Lawyer? (Type yes or no)");
				}
				if(WantLawyer[i] == 20)
				{
				    SendClientMessage(i, COLOR_LIGHTRED, "There is no Lawyer available to you anymore, Jail Time started.");
				    WantLawyer[i] = 0;
				    CallLawyer[i] = 0;
				}
			}
			if(TutTime[i] >= 1)
			{
			    TutTime[i] += 1;
			    if(TutTime[i] == 3)
			    {
			        SendClientMessage(i, COLOR_YELLOW2, "|____ Tutorial: The beginning ____|");
			        SendClientMessage(i, COLOR_YELLOW2, "Hi there, i can see that you are new, so here's a quick Tutorial.");
			        SendClientMessage(i, COLOR_YELLOW2, "Every new players needs to know what he / she, can and can't do.");
			        SendClientMessage(i, COLOR_YELLOW2, "I will give your quiet some information, so please pay attention to avoid questions later on.");
			    }
			    else if(TutTime[i] == 14)
			    {
			        SendClientMessage(i, COLOR_YELLOW, "|____ Tutorial: Kind of server ____|");
			    }
			    else if(TutTime[i] == 16)
			    {
			        SendClientMessage(i, COLOR_YELLOW2, "This server is a RP server which stands for Role Playing.");
			        SendClientMessage(i, COLOR_YELLOW2, "We are absolutely not interested in players that just come along and Deathmatch.");
			        SendClientMessage(i, COLOR_YELLOW2, "The name you have also matters alot, other players are getting used to your chosen name");
			        SendClientMessage(i, COLOR_YELLOW2, "so it's better to have a name like for example: Oliver_Wood.");
			        SendClientMessage(i, COLOR_YELLOW2, "If you want to know more about how to RP, visit our forums and search for the topic.");
			        SendClientMessage(i, COLOR_YELLOW2, "(You can find the forum on our webpage: http://www.godfather-rp.com");
			    }
			    else if(TutTime[i] == 30)
			    {
			        SendClientMessage(i, COLOR_YELLOW, "|____ Tutorial: Requesting Help ____|");
			    }
			    else if(TutTime[i] == 32)
			    {
			        SendClientMessage(i, COLOR_YELLOW2, "If you are confused and would like to know some more information when you are ingame");
			        SendClientMessage(i, COLOR_YELLOW2, "simply just ask any Player or an Admin (/admins) in a common way.");
			        SendClientMessage(i, COLOR_YELLOW2, "Just use common lines like: Hi, could you help me a sec please?");
			        SendClientMessage(i, COLOR_YELLOW2, "Don't start to shout or curse at someone, because it will only make you look worse..");
			        SendClientMessage(i, COLOR_YELLOW2, "And you might end up banned, which you want to skip of course.");
			        SendClientMessage(i, COLOR_YELLOW2, "Use the commands /o (OOC) /w (Whisper) /sms (If you have the Phone Number) to talk to someone.");
			    }
			    else if(TutTime[i] == 52)
			    {
			        SendClientMessage(i, COLOR_YELLOW, "|____ Tutorial: Cheating & Abusing ____|");
			    }
			    else if(TutTime[i] == 54)
			    {
			        SendClientMessage(i, COLOR_YELLOW2, "We wish that n0beit was never made and we certainly don't allow players to use it.");
			        SendClientMessage(i, COLOR_YELLOW2, "Thats why we don't want YOU to cheat, or allow other players to cheat.");
			        SendClientMessage(i, COLOR_YELLOW2, "If you see someone cheating, please report it with /report right away.");
			        SendClientMessage(i, COLOR_YELLOW2, "Bug abusing, or in any other way stuff abusing is just as bad as Cheating.");
			        SendClientMessage(i, COLOR_YELLOW2, "So we don't want YOU to abuse aswell, simply use the /report as well if you see");
			        SendClientMessage(i, COLOR_YELLOW2, "someone abusing something.");
			    }
			    else if(TutTime[i] == 74)
			    {
			        SendClientMessage(i, COLOR_YELLOW, "|____ Tutorial: Respect ____|");
			    }
			    else if(TutTime[i] == 76)
			    {
			        SendClientMessage(i, COLOR_YELLOW2, "First of all I like to start with Admins, respect Admins in any way.");
			        SendClientMessage(i, COLOR_YELLOW2, "We are all trying to keep everyony satisfied and trying to help everyone in anyway possible.");
			        SendClientMessage(i, COLOR_YELLOW2, "Secondly, don't curse / shout / swear at other players, this will end you up muted / banned.");
			        SendClientMessage(i, COLOR_YELLOW2, "Just treat people with respect, just like you want to be respected.");
			    }
			    else if(TutTime[i] == 96)
			    {
			        SendClientMessage(i, COLOR_YELLOW, "|____ Tutorial: Drive-by ____|");
			    }
			    else if(TutTime[i] == 98)
			    {
			        SendClientMessage(i, COLOR_YELLOW2, "We don't allow Drive-by's on this server, since it's lame and simple to kill.");
			        SendClientMessage(i, COLOR_YELLOW2, "And it's deathmatching, which we definately don't allow.");
			        SendClientMessage(i, COLOR_YELLOW2, "Don't do this if you don't want yourself to get banned.");
			    }
			    else if(TutTime[i] == 108)
			    {
			        SendClientMessage(i, COLOR_YELLOW, "|____ Tutorial: Language & Advertising ____|");
			    }
			    else if(TutTime[i] == 110)
			    {
			        SendClientMessage(i, COLOR_YELLOW2, "We'd like you to use English in any chat.");
			        SendClientMessage(i, COLOR_YELLOW2, "If you want to talk with someone in your own Language, use the /w or /sms commands");
			        SendClientMessage(i, COLOR_YELLOW2, "Advertising is not allowed aswell, advertising will get you banned aswell.");
			    }
			    else if(TutTime[i] == 119)
			    {
			        SendClientMessage(i, COLOR_YELLOW, "|____ Tutorial: The End ____|");
			    }
			    else if(TutTime[i] == 121)
			    {
			        SendClientMessage(i, COLOR_YELLOW2, "So that was it, probably obvious but we still want you to remember our rules.");
			        SendClientMessage(i, COLOR_YELLOW2, "Just keep reminding them and have fun!");
			        SendClientMessage(i, COLOR_YELLOW2, "Greetings from: Role Play - The Godfather Admin Team.");
			    }
			    else if(TutTime[i] == 127)
			    {
			        TutTime[i] = 0; PlayerInfo[i][pTut] = 1;
					gOoc[i] = 0; gNews[i] = 0; gFam[i] = 0;
					TogglePlayerControllable(i, 1);
					MedicBill[i] = 0;
					SetPlayerSpawn(i);
			    }
			}
			if(PlayerTazeTime[i] >= 1)
			{
			    PlayerTazeTime[i] += 1;
			    if(PlayerTazeTime[i] == 15)
			    {
                    PlayerTazeTime[i] = 0;
			    }
			    else
			    {
			        new Float:angle;
					GetPlayerFacingAngle(i, angle);
					SetPlayerFacingAngle(i, angle + 90);
			    }
			}
			if(PlayerDrunk[i] >= 5)
			{
			    PlayerDrunkTime[i] += 1;
			    if(PlayerDrunkTime[i] == 8)
			    {
			        PlayerDrunkTime[i] = 0;
			        new Float:angle;
					GetPlayerFacingAngle(i, angle);
					if(IsPlayerInAnyVehicle(i))
					{
					    if(GetPlayerState(i) == 2)
					    {
					    	SetVehicleZAngle(GetPlayerVehicleID(i), angle + 25);
						}
					}
					else
					{
					    ApplyAnimation(i,"PED", "WALK_DRUNK",4.0,0,1,0,0,0);
					}
			    }
			}
			if(PlayerStoned[i] >= 2)
			{
		        PlayerStoned[i] += 1;
			    if(PlayerStoned[i] == 10)
			    {
			        PlayerStoned[i] = 2;
			        new Float:angle;
					GetPlayerFacingAngle(i, angle);
					if(IsPlayerInAnyVehicle(i))
					{
					    if(GetPlayerState(i) == 2)
					    {
					    	SetVehicleZAngle(GetPlayerVehicleID(i), angle + 25);
						}
					}
					else
					{
					    SetPlayerFacingAngle(i, angle + 90);
					}
			    }
			}
			if(PlayerInfo[i][pCarTime] > 0)
			{
			    if(PlayerInfo[i][pCarTime] <= 0)
			    {
			        PlayerInfo[i][pCarTime] = 0;
			    }
			    else
			    {
			        PlayerInfo[i][pCarTime] -= 1;
			    }
			}
			if(BoxWaitTime[i] > 0)
			{
			    if(BoxWaitTime[i] >= BoxDelay)
				{
				    BoxDelay = 0;
					BoxWaitTime[i] = 0;
					PlayerPlaySound(i, 1057, 0.0, 0.0, 0.0);
					GameTextForPlayer(i, "~g~Match Started", 5000, 1);
					TogglePlayerControllable(i, 1);
					RoundStarted = 1;
				}
			    else
				{
				    format(string, sizeof(string), "%d", BoxDelay - BoxWaitTime[i]);
					GameTextForPlayer(i, string, 1500, 6);
					BoxWaitTime[i] += 1;
				}
			}
			if(RoundStarted > 0)
			{
			    if(PlayerBoxing[i] > 0)
			    {
			        new trigger = 0;
			        new Lost = 0;
		        	new Float:angle;
		            new Float:health;
					GetPlayerHealth(i, health);
		            if(health < 12)
					{
					    if(i == Boxer1) { Lost = 1; trigger = 1; }
			            else if(i == Boxer2) { Lost = 2; trigger = 1; }
					}
			        if(health < 28) { GetPlayerFacingAngle(i, angle); SetPlayerFacingAngle(i, angle + 85); }
			        if(trigger)
			        {
			            new winner[MAX_PLAYER_NAME];
			            new loser[MAX_PLAYER_NAME];
			            new titel[MAX_PLAYER_NAME];
			            if(Lost == 1)
			            {
			                if(IsPlayerConnected(Boxer1) && IsPlayerConnected(Boxer2))
			                {
					        	SetPlayerPos(Boxer1, 765.8433,3.2924,1000.7186); SetPlayerPos(Boxer2, 765.8433,3.2924,1000.7186);
					        	SetPlayerInterior(Boxer1, 5); SetPlayerInterior(Boxer2, 5);
			                	GetPlayerName(Boxer1, loser, sizeof(loser));
			                	GetPlayerName(Boxer2, winner, sizeof(winner));
		                		if(PlayerInfo[Boxer1][pJob] == 12) { PlayerInfo[Boxer1][pLoses] += 1; }
								if(PlayerInfo[Boxer2][pJob] == 12) { PlayerInfo[Boxer2][pWins] += 1; }
			                	if(TBoxer < 255)
			                	{
			                	    if(IsPlayerConnected(TBoxer))
			                	    {
				                	    if(TBoxer != Boxer2)
				                	    {
				                	        if(PlayerInfo[Boxer2][pJob] == 10)
				                	        {
				                	            TBoxer = Boxer2;
				                	            GetPlayerName(TBoxer, titel, sizeof(titel));
					                	        new nstring[MAX_PLAYER_NAME];
												format(nstring, sizeof(nstring), "%s", titel);
												strmid(Titel[TitelName], nstring, 0, strlen(nstring), 255);
					                	        Titel[TitelWins] = PlayerInfo[TBoxer][pWins];
					                	        Titel[TitelLoses] = PlayerInfo[TBoxer][pLoses];
					                	        SaveBoxer();
							                	format(string, sizeof(string), "Boxing News: %s has Won the fight against Champion %s and is now the new Boxing Champion.",  titel, loser);
												OOCOff(COLOR_WHITE,string);
				                	        }
				                	        else
				                	        {
				                	            SendClientMessage(Boxer2, COLOR_LIGHTBLUE, "* You would have been the Champion if you had the Boxer Job !");
				                	        }
										}
										else
										{
										    GetPlayerName(TBoxer, titel, sizeof(titel));
										    format(string, sizeof(string), "Boxing News: Boxing Champion %s has Won the fight against %s.",  titel, loser);
											OOCOff(COLOR_WHITE,string);
											Titel[TitelWins] = PlayerInfo[TBoxer][pWins];
				                	        Titel[TitelLoses] = PlayerInfo[Boxer2][pLoses];
				                	        SaveBoxer();
										}
									}
								}//TBoxer
								format(string, sizeof(string), "* You have Lost the Fight against %s.", winner);
								SendClientMessage(Boxer1, COLOR_LIGHTBLUE, string);
								GameTextForPlayer(Boxer1, "~r~You lost", 3500, 1);
								format(string, sizeof(string), "* You have Won the Fight against %s.", loser);
								SendClientMessage(Boxer2, COLOR_LIGHTBLUE, string);
								GameTextForPlayer(Boxer2, "~r~You won", 3500, 1);
								if(GetPlayerHealth(Boxer1, health) < 20)
								{
								    SendClientMessage(Boxer1, COLOR_LIGHTBLUE, "* You feel exhausted from the Fight, go eat somewhere.");
								    SetPlayerHealth(Boxer1, 30.0);
								}
								else
								{
								    SendClientMessage(Boxer1, COLOR_LIGHTBLUE, "* You feel perfect, even after the Fight.");
								    SetPlayerHealth(Boxer1, 50.0);
								}
								if(GetPlayerHealth(Boxer2, health) < 20)
								{
								    SendClientMessage(Boxer2, COLOR_LIGHTBLUE, "* You feel exhausted from the Fight, go eat somewhere.");
							    	SetPlayerHealth(Boxer2, 30.0);
								}
								else
								{
								    SendClientMessage(Boxer2, COLOR_LIGHTBLUE, "* You feel perfect, even after the Fight.");
								    SetPlayerHealth(Boxer2, 50.0);
								}
                                GameTextForPlayer(Boxer1, "~g~Match Over", 5000, 1); GameTextForPlayer(Boxer2, "~g~Match Over", 5000, 1);
								if(PlayerInfo[Boxer2][pJob] == 10) { PlayerInfo[Boxer2][pBoxSkill] += 1; }
								PlayerBoxing[Boxer1] = 0;
								PlayerBoxing[Boxer2] = 0;
							}
			            }
			            else if(Lost == 2)
			            {
			                if(IsPlayerConnected(Boxer1) && IsPlayerConnected(Boxer2))
			                {
					        	SetPlayerPos(Boxer1, 765.8433,3.2924,1000.7186); SetPlayerPos(Boxer2, 765.8433,3.2924,1000.7186);
					        	SetPlayerInterior(Boxer1, 5); SetPlayerInterior(Boxer2, 5);
			                	GetPlayerName(Boxer1, winner, sizeof(winner));
			                	GetPlayerName(Boxer2, loser, sizeof(loser));
		                		if(PlayerInfo[Boxer2][pJob] == 10) { PlayerInfo[Boxer2][pLoses] += 1; }
								if(PlayerInfo[Boxer1][pJob] == 10) { PlayerInfo[Boxer1][pWins] += 1; }
			                	if(TBoxer < 255)
			                	{
			                	    if(IsPlayerConnected(TBoxer))
			                	    {
				                	    if(TBoxer != Boxer1)
				                	    {
				                	        if(PlayerInfo[Boxer1][pJob] == 10)
				                	        {
					                	        TBoxer = Boxer1;
					                	        GetPlayerName(TBoxer, titel, sizeof(titel));
					                	        new nstring[MAX_PLAYER_NAME];
												format(nstring, sizeof(nstring), "%s", titel);
												strmid(Titel[TitelName], nstring, 0, strlen(nstring), 255);
					                	        Titel[TitelWins] = PlayerInfo[TBoxer][pWins];
					                	        Titel[TitelLoses] = PlayerInfo[TBoxer][pLoses];
					                	        SaveBoxer();
							                	format(string, sizeof(string), "Boxing News: %s has Won the fight against Champion %s and is now the new Boxing Champion.",  titel, loser);
												OOCOff(COLOR_WHITE,string);
											}
				                	        else
				                	        {
				                	            SendClientMessage(Boxer1, COLOR_LIGHTBLUE, "* You would have been the Champion if you had the Boxer Job !");
				                	        }
										}
										else
										{
										    GetPlayerName(TBoxer, titel, sizeof(titel));
										    format(string, sizeof(string), "Boxing News: Boxing Champion %s has Won the fight against %s.",  titel, loser);
											OOCOff(COLOR_WHITE,string);
											Titel[TitelWins] = PlayerInfo[TBoxer][pWins];
				                	        Titel[TitelLoses] = PlayerInfo[Boxer1][pLoses];
				                	        SaveBoxer();
										}
									}
								}//TBoxer
								format(string, sizeof(string), "* You have Lost the Fight against %s.", winner);
								SendClientMessage(Boxer2, COLOR_LIGHTBLUE, string);
								GameTextForPlayer(Boxer2, "~r~You lost", 3500, 1);
								format(string, sizeof(string), "* You have Won the Fight against %s.", loser);
								SendClientMessage(Boxer1, COLOR_LIGHTBLUE, string);
								GameTextForPlayer(Boxer1, "~g~You won", 3500, 1);
								if(GetPlayerHealth(Boxer1, health) < 20)
								{
								    SendClientMessage(Boxer1, COLOR_LIGHTBLUE, "* You feel exhausted from the Fight, go eat somewhere.");
								    SetPlayerHealth(Boxer1, 30.0);
								}
								else
								{
								    SendClientMessage(Boxer1, COLOR_LIGHTBLUE, "* You feel perfect, even after the Fight.");
								    SetPlayerHealth(Boxer1, 50.0);
								}
								if(GetPlayerHealth(Boxer2, health) < 20)
								{
								    SendClientMessage(Boxer2, COLOR_LIGHTBLUE, "* You feel exhausted from the Fight, go eat somewhere.");
							    	SetPlayerHealth(Boxer2, 30.0);
								}
								else
								{
								    SendClientMessage(Boxer2, COLOR_LIGHTBLUE, "* You feel perfect, even after the Fight.");
								    SetPlayerHealth(Boxer2, 50.0);
								}
                                GameTextForPlayer(Boxer1, "~g~Match Over", 5000, 1); GameTextForPlayer(Boxer2, "~g~Match Over", 5000, 1);
								if(PlayerInfo[Boxer1][pJob] == 10) { PlayerInfo[Boxer1][pBoxSkill] += 1; }
								PlayerBoxing[Boxer1] = 0;
								PlayerBoxing[Boxer2] = 0;
							}
			            }
			            InRing = 0;
			            RoundStarted = 0;
			            Boxer1 = 255;
			            Boxer2 = 255;
			            TBoxer = 255;
			            trigger = 0;
			        }
			    }
			}
			if(StartingPaintballRound == 1 && AnnouncedPaintballRound == 0)
			{
			    AnnouncedPaintballRound = 1;
			    if(PlayerPaintballing[i] != 0)
			    {
			        SendClientMessage(i, COLOR_YELLOW, "Paintball Match will be announced in 15 seconds (For getting more Paintball players).");
			    }
			}
			if(StartingKartRound == 1 && AnnouncedKartRound == 0)
			{
			    AnnouncedKartRound = 1;
			    if(PlayerKarting[i] != 0 && PlayerInKart[i] != 0)
			    {
			        SendClientMessage(i, COLOR_YELLOW, "Karting Race will be announced in 15 seconds (For getting more Kart Racers).");
			    }
			}
			if(EndingKartRound == 1)
			{
			    if(PlayerKarting[i] != 0 && PlayerInKart[i] != 0)
			    {
			        DisablePlayerCheckpoint(i);
			        CP[i] = 0;
			    }
			}
			if(FindTime[i] > 0)
			{
			    if(FindTime[i] == FindTimePoints[i]) { FindTime[i] = 0; FindTimePoints[i] = 0; DisablePlayerCheckpoint(i); PlayerPlaySound(i, 1056, 0.0, 0.0, 0.0); GameTextForPlayer(i, "~r~RedMarker gone", 2500, 1); }
			    else
				{
				    format(string, sizeof(string), "%d", FindTimePoints[i] - FindTime[i]);
					GameTextForPlayer(i, string, 1500, 6);
					FindTime[i] += 1;
				}
			}
			if(TaxiCallTime[i] > 0)
			{
			    if(TaxiAccepted[i] < 999)
			    {
				    if(IsPlayerConnected(TaxiAccepted[i]))
				    {
				        new Float:X,Float:Y,Float:Z;
						GetPlayerPos(TaxiAccepted[i], X, Y, Z);
						SetPlayerCheckpoint(i, X, Y, Z, 5);
				    }
				}
			}
			if(BusCallTime[i] > 0)
			{
			    if(BusAccepted[i] < 999)
			    {
				    if(IsPlayerConnected(BusAccepted[i]))
				    {
				        new Float:X,Float:Y,Float:Z;
						GetPlayerPos(BusAccepted[i], X, Y, Z);
						SetPlayerCheckpoint(i, X, Y, Z, 5);
				    }
				}
			}
			if(MedicCallTime[i] > 0)
			{
			    if(MedicCallTime[i] == 30) { MedicCallTime[i] = 0; DisablePlayerCheckpoint(i); PlayerPlaySound(i, 1056, 0.0, 0.0, 0.0); GameTextForPlayer(i, "~r~RedMarker gone", 2500, 1); }
			    else
				{
				    format(string, sizeof(string), "%d", 30 - MedicCallTime[i]);
					GameTextForPlayer(i, string, 1500, 6);
					MedicCallTime[i] += 1;
				}
			}
			if(MechanicCallTime[i] > 0)
			{
			    if(MechanicCallTime[i] == 30) { MechanicCallTime[i] = 0; DisablePlayerCheckpoint(i); PlayerPlaySound(i, 1056, 0.0, 0.0, 0.0); GameTextForPlayer(i, "~r~RedMarker gone", 2500, 1); }
			    else
				{
				    format(string, sizeof(string), "%d", 30 - MechanicCallTime[i]);
					GameTextForPlayer(i, string, 1500, 6);
					MechanicCallTime[i] += 1;
				}
			}
			if(Robbed[i] == 1)
			{
			    if(RobbedTime[i] <= 0)
			    {
			        RobbedTime[i] = 0;
					Robbed[i] = 0;
			    }
			    else
			    {
			        RobbedTime[i] -= 1;
			    }
			}
			if(PlayerCuffed[i] == 1)
			{
			    if(PlayerCuffedTime[i] <= 0)
			    {
			        TogglePlayerControllable(i, 1);
			        PlayerCuffed[i] = 0;
			        PlayerCuffedTime[i] = 0;
			        PlayerTazeTime[i] = 1;
			    }
			    else
			    {
			        PlayerCuffedTime[i] -= 1;
			    }
			}
			if(PlayerCuffed[i] == 2)
			{
			    if(PlayerCuffedTime[i] <= 0)
			    {
			        GameTextForPlayer(i, "~r~You broke the Cuffs, you are free!", 2500, 3);
			        TogglePlayerControllable(i, 1);
			        PlayerCuffed[i] = 0;
			        PlayerCuffedTime[i] = 0;
			    }
			    else
			    {
			        PlayerCuffedTime[i] -= 1;
			    }
			}
			if(PlayerToPoint(20, i,2015.4500,1017.0900,996.8750))
			{//Four Dragons
			    GameTextForPlayer(i, "~r~Closed", 5000, 1);
			    SetPlayerInterior(i, 0);
			    SetPlayerPos(i,1022.599975,-1123.699951,23.799999);
			}
			else if(PlayerToPoint(20, i,2233.9099,1710.7300,1011.2987))
			{//Caligula
			    GameTextForPlayer(i, "~r~Closed", 5000, 1);
			    SetPlayerInterior(i, 0);
			    SetPlayerPos(i,1022.599975,-1123.699951,23.799999);
			}
			else if(PlayerToPoint(10, i,2265.7900,1619.5800,1090.4453))
			{//Caligula Roof 1
			    GameTextForPlayer(i, "~r~Closed", 5000, 1);
			    SetPlayerInterior(i, 0);
			    SetPlayerPos(i,1022.599975,-1123.699951,23.799999);
			}
			else if(PlayerToPoint(10, i,2265.7800,1675.9301,1090.4453))
			{//Caligula Roof 2
			    GameTextForPlayer(i, "~r~Closed", 5000, 1);
			    SetPlayerInterior(i, 0);
			    SetPlayerPos(i,1022.599975,-1123.699951,23.799999);
			}
			else if(PlayerToPoint(20, i,1133.0699,-9.5731,1000.6797))
			{//West Casino place
			    GameTextForPlayer(i, "~r~Closed", 5000, 1);
			    SetPlayerInterior(i, 0);
			    SetPlayerPos(i,1022.599975,-1123.699951,23.799999);
			}
			else if(PlayerToPoint(20, i,292.0274,-36.0291,1001.5156))
			{//Ammunation 1
			    GameTextForPlayer(i, "~r~Jailed for going to ammunation", 5000, 1);
			    SetPlayerInterior(i, 6);
				SetPlayerPos(i,264.6288,77.5742,1001.0391);
				PlayerInfo[i][pJailTime] = 300;
				PlayerInfo[i][pJailed] = 1;
			}
			else if(PlayerToPoint(20, i,308.2740,-141.2833,999.6016))
			{//Ammunation 2
			    GameTextForPlayer(i, "~r~Jailed for going to ammunation", 5000, 1);
			    SetPlayerInterior(i, 6);
				SetPlayerPos(i,264.6288,77.5742,1001.0391);
				PlayerInfo[i][pJailTime] = 300;
				PlayerInfo[i][pJailed] = 1;
			}
			else if(PlayerToPoint(20, i,294.3212,-108.7869,1001.5156))
			{//Ammunation 3 (small one's)
			    GameTextForPlayer(i, "~r~Jailed for going to ammunation", 5000, 1);
			    SetPlayerInterior(i, 6);
				SetPlayerPos(i,264.6288,77.5742,1001.0391);
				PlayerInfo[i][pJailTime] = 300;
				PlayerInfo[i][pJailed] = 1;
			}
			else if(PlayerToPoint(20, i,288.8592,-80.4535,1001.5156))
			{//Ammunation 4 (small one's)
			    GameTextForPlayer(i, "~r~Jailed for going to ammunation", 5000, 1);
			    SetPlayerInterior(i, 6);
				SetPlayerPos(i,264.6288,77.5742,1001.0391);
				PlayerInfo[i][pJailTime] = 300;
				PlayerInfo[i][pJailed] = 1;
			}
			else if(PlayerToPoint(20, i,316.9583,-165.4707,999.6010))
			{//Ammunation 5 (Unprotected)
			    GameTextForPlayer(i, "~r~Jailed for going to ammunation", 5000, 1);
			    SetPlayerInterior(i, 6);
				SetPlayerPos(i,264.6288,77.5742,1001.0391);
				PlayerInfo[i][pJailTime] = 300;
				PlayerInfo[i][pJailed] = 1;
			}
		}
	}
}

Callback CheckGas()
{
	new string[256];
	for(new i=0;i<MAX_PLAYERS;i++)
	{
    	if(IsPlayerConnected(i))
       	{
       	    if(GetPlayerState(i) == PLAYER_STATE_DRIVER)
       	    {
	       		new vehicle = GetPlayerVehicleID(i);
	        	if(Gas[vehicle] >= 1)
		   		{
		   		    if(Gas[vehicle] <= 10) { PlayerPlaySound(i, 1085, 0.0, 0.0, 0.0); }
		   		    if(gGas[i] == 1) {
		      		format(string, sizeof(string), "~r~~n~~n~~n~~n~~n~~n~~n~~n~~n~Fuel:~w~ %d%",Gas[vehicle]);
		      		GameTextForPlayer(i,string,15500,3); }
					if(IsAPlane(vehicle) || IsABoat(vehicle)) { Gas[vehicle]++; }
	              	Gas[vehicle]--;
		   		}
	   			else
	           	{
	              	NoFuel[i] = 1;
	              	TogglePlayerControllable(i, 0);
		        	GameTextForPlayer(i,"~w~~n~~n~~n~~n~~n~~n~~n~~n~No fuel in Vehicle~n~Use /exit to leave the vehicle",1500,3);
				}
			}
    	}
	}
	return 1;
}

Callback Fillup()
{
	for(new i=0; i<MAX_PLAYERS; i++)
   	{
	   	if(IsPlayerConnected(i))
	   	{
		    new VID;
		    new FillUp;
		    new string[256];
		    VID = GetPlayerVehicleID(i);
		    FillUp = GasMax - Gas[VID];
			if(Refueling[i] == 1)
		    {
				if(GetPlayerMoney(i) >= FillUp+4)
				{
					Gas[VID] += FillUp;
					FillUp = FillUp * SBizzInfo[3][sbEntranceCost];
				    format(string,sizeof(string),"* Vehicle filled up, for: $%d.",FillUp);
				    SendClientMessage(i,COLOR_LIGHTBLUE,string);
					GivePlayerMoney(i, - FillUp);
					SBizzInfo[3][sbTill] += FillUp;
					ExtortionSBiz(3, FillUp);
					Refueling[i] = 0;
				}
			   	else
			   	{
			   	    format(string,sizeof(string),"* Not enough Money to refill, it costs $%d to fill your Vehicle.",FillUp);
				    SendClientMessage(i,COLOR_LIGHTBLUE,string);
			   	}
		 	}
		}
	}
	return 1;
}

Callback StoppedVehicle()
{
	new Float:x,Float:y,Float:z;
	new Float:distance,value;
	for(new i=0; i<MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i))
		{
			if(IsPlayerInAnyVehicle(i))
			{
				new VID;
				VID = GetPlayerVehicleID(i);
				GetPlayerPos(i, x, y, z);
				distance = floatsqroot(floatpower(floatabs(floatsub(x,SavePlayerPos[i][LastX])),2)+floatpower(floatabs(floatsub(y,SavePlayerPos[i][LastY])),2)+floatpower(floatabs(floatsub(z,SavePlayerPos[i][LastZ])),2));
				value = floatround(distance * 3600);
				if(UpdateSeconds > 1)
				{
					value = floatround(value / UpdateSeconds);
				}
				if(SpeedMode)
				{
	            }
				if(value == 0)
				{
					Gas[VID]++;
				}
				SavePlayerPos[i][LastX] = x;
				SavePlayerPos[i][LastY] = y;
				SavePlayerPos[i][LastZ] = z;
			}
		}
	}
	return 1;
}

Callback GameModeInitExitFunc()
{
	new string[128];
	format(string, sizeof(string), "Traveling...");
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i))
		{
			DisablePlayerCheckpoint(i);
			gPlayerCheckpointStatus[i] = CHECKPOINT_NONE;
			GameTextForPlayer(i, string, 4000, 5);
			SetPlayerCameraPos(i,1460.0, -1324.0, 287.2);
			SetPlayerCameraLookAt(i,1374.5, -1291.1, 239.0);
			OnPlayerUpdate(i);
			gPlayerLogged[i] = 0;
		}
	}
	SetTimer("GameModeExitFunc", 4000, 0);
	return 1;
}

Callback GameModeExitFunc()
{
	KillTimer(synctimer);
	KillTimer(newmistimer);
	KillTimer(unjailtimer);
	KillTimer(othtimer);
	KillTimer(cartimer);
	KillTimer(accountstimer);
	KillTimer(checkgastimer);
	KillTimer(idletimer);
	KillTimer(pickuptimer);
	KillTimer(productiontimer);
	KillTimer(spectatetimer);
	KillTimer(stoppedvehtimer);
	KillTimer(turftimer);
	GameModeExit();
}

Callback SaveAccounts()
{
    for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i))
		{
			OnPlayerUpdate(i);
			if(PlayerInfo[i][pJob] > 0)
	    	{
	    	    if(PlayerInfo[i][pContractTime] < 25)
	    	    {
					PlayerInfo[i][pContractTime] ++;
				}
	    	}
		}
	}
}

Callback IdleKick()
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i))
		{
		    if(PlayerInfo[i][pAdmin] < 1)
		    {
				GetPlayerPos(i, PlayerPos[i][0], PlayerPos[i][1], PlayerPos[i][2]);
				if(PlayerPos[i][0] == PlayerPos[i][3] && PlayerPos[i][1] == PlayerPos[i][4] && PlayerPos[i][2] == PlayerPos[i][5])
				{
					Kick(i);
				}
				PlayerPos[i][3] = PlayerPos[i][0];
				PlayerPos[i][4] = PlayerPos[i][1];
				PlayerPos[i][5] = PlayerPos[i][2];
			}
		}
	}
}

Callback LoadIntro(playerid) {
	if(gPlayerLogged[playerid]) {
		return 1;
	}

	loadedIntro[playerid] = true;

	for(new i = 0; i < 20; i++) {
		SendClientMessage(playerid, COLOR_WHITE, " ");
	}

	SendClientMessage(playerid, COLOR_YELLOW, "Witaj w Old School Role Play: Proszê czekaæ na za³adowanie mapy OSRP v1.0.");
	TextDrawHideForPlayer(playerid, SplashScreen);

	for(new i = 0; i < 4; i++) {
		TextDrawShowForPlayer(playerid, Intro[i]);
	}

	SetPlayerCameraPos(playerid, 2902.5500, -1953.4100, 106.9900);
	SetPlayerCameraLookAt(playerid, 2901.5400, -1953.3800, 106.8900);

	if(loadedIntro[playerid]) {
		queryStr[0] = EOS;
		format(queryStr, sizeof(queryStr), "SELECT `Name` FROM `Accounts` WHERE `Name` = '%s' LIMIT 1", escapedName[playerid]);
		mysql_query(queryStr);

		mysql_store_result();

		if(mysql_result_stored()) {
			if(mysql_num_rows() < 1) {
				gPlayerAccount[playerid] = 0;
				SendClientMessage(playerid, COLOR_YELLOW2, "Serwer: To konto nie jest jeszcze zarejestrowane, aby zagraæ musisz siê zarejestrowaæ.");

				mainStr[0] = EOS;
				strcat(mainStr, "{FFFFFF}Kompletny regulamin serwera Old School Role Play znajduje siê na naszej stronie internetowej www.osrp.pl.\n");
				strcat(mainStr, "Prosimy o zapoznanie siê z nim, poniewa¿ jego nieznajomoœæ nie jest usprawiedliwieniem do ³amania go.\n");
				strcat(mainStr, "Za nieprzestrzeganie regulaminu gro¿¹ kary.\n\n");
				strcat(mainStr, "Klikaj¹c przycisk Akceptuj zobowi¹zujesz siê do przestrzegania regulaminu, Odrzuæ wi¹¿e siê z opuszczeniem serwera.");
				osrp_ShowPlayerDialog(playerid, DIALOG_REGISTER_RULES, DIALOG_STYLE_MSGBOX, "Regulamin:", mainStr, "Akceptuj", "Odrzuæ");
			} else {
				gPlayerAccount[playerid] = 1;
				SendClientMessage(playerid, COLOR_YELLOW2, "Serwer: To konto jest ju¿ zarejestrowane. Mo¿esz siê zalogowaæ.");

				osrp_ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_PASSWORD, "Zaloguj:", "{FFFFFF}To konto ju¿ istnieje.\nWpisz has³o, aby siê zalogowaæ.", "Zaloguj", "WyjdŸ");
			}

			mysql_free_result();
		}
	}
	return 1;
}
