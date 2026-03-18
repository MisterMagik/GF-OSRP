/*
	Project: GodFather
	Author: MisterMagik, steeZ
	File name: variables.inc
	Date: 12.03.2026
	Modified: 12.03.2026
	Desc: All server vars, including arrays.
*/

new MySQL:mySQLHandle;
stock gString[256];
new gTeam[MAX_PLAYERS];
new Security = 0;
new CreatedCars[100];
stock CreatedCar = 0;
new Tax = 0;
new TaxValue = 0;
new Jackpot = 0;
new StartingPaintballRound = 0;
new AnnouncedPaintballRound = 0;
new PaintballPlayers = 0;
new PaintballRound = 0;
new PaintballWinner = 999;
new PaintballWinnerKills = 0;
new StartingKartRound = 0;
new EndingKartRound = 0;
new AnnouncedKartRound = 0;
new KartingPlayers = 0;
new KartingRound = 0;
new FirstKartWinner = 999;
new SecondKartWinner = 999;
new ThirdKartWinner = 999;
stock InRing = 0;
new RoundStarted = 0;
new BoxDelay = 0;
new Boxer1 = 255;
new Boxer2 = 255;
new TBoxer = 255;
new PlayerBoxing[MAX_PLAYERS];
new hitfound = 0;
new hitid = 999;
new Medics = 0;
stock MedicCall = 999;
new MedicCallTime[MAX_PLAYERS];
new Mechanics = 0;
stock MechanicCall = 999;
new MechanicCallTime[MAX_PLAYERS];
new TaxiDrivers = 0;
stock TaxiCall = 999;
new TaxiCallTime[MAX_PLAYERS];
new TaxiAccepted[MAX_PLAYERS];
new BusDrivers = 0;
stock BusCall = 999;
new BusCallTime[MAX_PLAYERS];
new BusAccepted[MAX_PLAYERS];
new TransportDuty[MAX_PLAYERS];
new TransportValue[MAX_PLAYERS];
new TransportMoney[MAX_PLAYERS];
new TransportTime[MAX_PLAYERS];
new TransportCost[MAX_PLAYERS];
new TransportDriver[MAX_PLAYERS];
new JobDuty[MAX_PLAYERS];
new RegistrationStep[MAX_PLAYERS];
new MapIconsShown[MAX_PLAYERS];
new OnCK[MAX_PLAYERS];
new GettingCK[MAX_PLAYERS];
new PlayerPaintballing[MAX_PLAYERS];
new PlayerPaintballKills[MAX_PLAYERS];
new PlayerKarting[MAX_PLAYERS];
new PlayerInKart[MAX_PLAYERS];
new SchoolSpawn[MAX_PLAYERS];
new TakingLesson[MAX_PLAYERS];
new UsedFind[MAX_PLAYERS];
new PlayersChannel[MAX_PLAYERS];
new PlayerOnMission[MAX_PLAYERS];
new MissionCheckpoint[MAX_PLAYERS];
new WatchingTV[MAX_PLAYERS];
new NoFuel[MAX_PLAYERS];
new MatsHolding[MAX_PLAYERS];
new DivorceOffer[MAX_PLAYERS];
new MarriageCeremoney[MAX_PLAYERS];
new ProposeOffer[MAX_PLAYERS];
new ProposedTo[MAX_PLAYERS];
new GotProposedBy[MAX_PLAYERS];
new MarryWitness[MAX_PLAYERS];
new MarryWitnessOffer[MAX_PLAYERS];
new TicketOffer[MAX_PLAYERS];
new TicketMoney[MAX_PLAYERS];
new PlayerStoned[MAX_PLAYERS];
new ConsumingMoney[MAX_PLAYERS];
new BringingPaper[MAX_PLAYERS]; //Paper Boys must pick up a Paper first, then use /deliver
new GotPaper[MAX_PLAYERS]; //The player has a paper so he can use /read
new WritingPaper[MAX_PLAYERS]; //Used for onplayertext so he can type in lines
new WritingPaperNumber[MAX_PLAYERS]; //To which Paper in PaperInfo will it be written
new WritingLine[MAX_PLAYERS]; //Used for onplayertext to see which line he's at
new FishCount[MAX_PLAYERS];
new SpawnChange[MAX_PLAYERS];
new TutTime[MAX_PLAYERS];
new PlayerDrunk[MAX_PLAYERS];
new PlayerDrunkTime[MAX_PLAYERS];
new PlayerTazeTime[MAX_PLAYERS];
new FindTimePoints[MAX_PLAYERS];
new FindTime[MAX_PLAYERS];
new BoxWaitTime[MAX_PLAYERS];
new TestFishes[MAX_PLAYERS];
new PaperOffer[MAX_PLAYERS];
new BoxOffer[MAX_PLAYERS];
new CarOffer[MAX_PLAYERS];
new CarPrice[MAX_PLAYERS];
new CarID[MAX_PLAYERS];
new CarCalls[MAX_PLAYERS];
new GotHit[MAX_PLAYERS];
new GoChase[MAX_PLAYERS];
new GetChased[MAX_PLAYERS];
new OrderReady[MAX_PLAYERS];
new ConnectedToPC[MAX_PLAYERS];
new MedicTime[MAX_PLAYERS];
new NeedMedicTime[MAX_PLAYERS];
new MedicBill[MAX_PLAYERS];
new PlayerTied[MAX_PLAYERS];
new PlayerCuffed[MAX_PLAYERS];
new PlayerCuffedTime[MAX_PLAYERS];
new LiveOffer[MAX_PLAYERS];
new TalkingLive[MAX_PLAYERS];
new PlacedNews[MAX_PLAYERS];
new SelectChar[MAX_PLAYERS];
new SelectCharID[MAX_PLAYERS];
new SelectCharPlace[MAX_PLAYERS];
new ChosenSkin[MAX_PLAYERS];
new GettingJob[MAX_PLAYERS];
new GuardOffer[MAX_PLAYERS];
new GuardPrice[MAX_PLAYERS];
new ApprovedLawyer[MAX_PLAYERS];
new CallLawyer[MAX_PLAYERS];
new WantLawyer[MAX_PLAYERS];
new CurrentMoney[MAX_PLAYERS];
new KickPlayer[MAX_PLAYERS];
new Robbed[MAX_PLAYERS];
new RobbedTime[MAX_PLAYERS];
new CP[MAX_PLAYERS];
new MoneyMessage[MAX_PLAYERS];
new Condom[MAX_PLAYERS];
new STDPlayer[MAX_PLAYERS];
new SexOffer[MAX_PLAYERS];
new SexPrice[MAX_PLAYERS];
new RepairOffer[MAX_PLAYERS];
new RepairPrice[MAX_PLAYERS];
new RefillOffer[MAX_PLAYERS];
new RefillPrice[MAX_PLAYERS];
new RepairCar[MAX_PLAYERS];
new DrugOffer[MAX_PLAYERS];
new DrugPrice[MAX_PLAYERS];
new DrugGram[MAX_PLAYERS];
new JailPrice[MAX_PLAYERS];
new WantedPoints[MAX_PLAYERS];
new WantedLevel[MAX_PLAYERS];
new OnDuty[MAX_PLAYERS];
new gPlayerCheckpointStatus[MAX_PLAYERS];
new gPlayerLogged[MAX_PLAYERS];
new gPlayerLogTries[MAX_PLAYERS];
new gPlayerSpawned[MAX_PLAYERS];
new gActivePlayers[MAX_PLAYERS];
new gLastCar[301];
new gOoc[MAX_PLAYERS];
new gNews[MAX_PLAYERS];
new gFam[MAX_PLAYERS];
new BigEar[MAX_PLAYERS];
new Spectate[MAX_PLAYERS];
new CellTime[MAX_PLAYERS];
new StartTime[MAX_PLAYERS];
new HireCar[MAX_PLAYERS];
new SafeTime[MAX_PLAYERS];
new HidePM[MAX_PLAYERS];
new PhoneOnline[MAX_PLAYERS];
new gDice[MAX_PLAYERS];
new gGas[MAX_PLAYERS];
new gSpeedo[MAX_PLAYERS];
new gSpentCash[MAX_PLAYERS];
new FirstSpawn[MAX_PLAYERS];
stock SwitchKey[MAX_PLAYERS];
new Fixr[MAX_PLAYERS];
new Locator[MAX_PLAYERS];
new Mobile[MAX_PLAYERS];
new RingTone[MAX_PLAYERS];
new CallCost[MAX_PLAYERS];
new gPlayerAccount[MAX_PLAYERS];
new gPlayerMission[MAX_PLAYERS];
new gLastDriver[302];
new gCarLock[265];
stock MissionPlayable = 0;
stock noooc = 0;
stock adds = 1;
stock addtimer = 60000;
stock Float:rx, Float:ry, Float:rz;
new carselect[15];
new objstore[128];
new cbjstore[128];
new motd[256];
new rccounter = 0;
//new RStart;
new ghour = 0;
new gminute = 0;
new gsecond = 0;
new numplayers = 0;
new dollah = 1000; // Amount player recieves on spawn.
new realtime = 1;
new wtime = 15;
new levelcost = 25000;
new deathcost = 500;
new callcost = 10; //20 seconds
new realchat = 1;
new timeshift = -1;
new shifthour;
new othtimer;
new synctimer;
new newmistimer;
new unjailtimer;
new turftimer;
new pickuptimer;
new spectatetimer;
new idletimer;
new productiontimer;
new accountstimer;
new checkgastimer;
new stoppedvehtimer;
new cartimer;
new intrate = 1;
new levelexp = 4;
new idletime = 600000; //10 mins
new civnokill = 0;
new suecost = 2000;
new cchargetime = 60;
stock txtcost = 25;
new pickups;
new CIV[] = {7,19,20,23,73,101,122};
stock STD1[] = {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3};
stock STD2[] = {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3};
stock STD3[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3};
stock STD4[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 2, 3};
new SELLCAR1[] = { 1000, 1124, 1245, 1349, 1475, 1574, 1636, 1762, 1895, 1946, 2000 };
new SELLCAR2[] = { 2099, 2135, 2255, 2378, 2457, 2563, 2614, 2721, 2878, 2988, 3000 };
new SELLCAR3[] = { 3058, 3175, 3212, 3377, 3454, 3555, 3678, 3751, 3865, 3964, 4000 };
new SELLCAR4[] = { 4077, 4123, 4275, 4378, 4422, 4565, 4613, 4752, 4897, 4911, 5000 };
new Float:ChangePos[MAX_PLAYERS][3];
new ChangePos2[MAX_PLAYERS][2];
new Float:PlayerPos[MAX_PLAYERS][6];
stock Float:TeleportDest[MAX_PLAYERS][3];
new Float:TelePos[MAX_PLAYERS][6];
new Gas[CAR_AMOUNT];
new Refueling[MAX_PLAYERS];

new SavePlayerPos[MAX_PLAYERS][SavePlayerPosEnum];
new SpeedMode = 1;
new UpdateSeconds = 1;

new Music[MAX_PLAYERS];
stock Songs[7][1] = {
{1187},
{1185},
{1183},
{1097},
{1076},
{1068},
{1062}
};

stock FishNamesNumber = 22;
stock FishNames[22][20] = {
{"Jacket"},
{"Amberjack"},
{"Grouper"},
{"Red Snapper"},
{"Pants"},
{"Trout"},
{"Blue Marlin"},
{"Can"},
{"Mackeral"},
{"Sea Bass"},
{"Shoes"},
{"Pike"},
{"Sail Fish"},
{"Garbage"},
{"Tuńczyk"},
{"Eel"},
{"Delfin"},
{"Rekin"},
{"Zółw"},
{"Catfish"},
{"Money Bag"},
{"Swordfish"}
};

new Float:PaintballSpawns[7][3] = {
{-394.8027,2232.2317,42.4297},
{-430.8412,2240.5371,42.9834},
{-369.2361,2248.3127,42.4844},
{-350.8910,2218.0215,42.4912},
{-384.0544,2206.2908,42.4235},
{-395.7100,2214.9480,42.4297},
{-445.3718,2222.5481,42.4297}
};

new Float:gRandomPlayerSpawns[1][3] = {
{2223.8,-1147.1,1025.7} // sp1
};

stock Float:gInviteSpawns[10][4] = {
{-1976.5912,166.1818,36.9623,272.6393},
{-1975.8610,162.1945,36.9623,272.0126},
{-1975.7461,157.5404,36.9623,276.1093},
{-1975.2136,151.4920,36.9623,268.2993},
{-1974.9963,145.3430,36.9623,269.2628},
{-1975.5842,140.8170,36.9623,269.8895},
{-1975.7874,134.0368,36.9623,271.7696},
{-1975.1681,129.0926,36.9623,270.8531},
{-1975.9069,121.4700,36.9623,270.5631},
{-1975.3311,112.7078,36.9623,267.7665}
};

/*new Float:gMedicSpawns[2][3] = {
{317.9066,315.6765,999.1484},
{317.6252,311.8465,999.1484}
};*/

new Float:gCopPlayerSpawns[2][3] = {
{1530.8369,-1664.8872,6.2188},
{1530.6913,-1669.4760,6.2188}
//{614.8,-608.2,17.2},
//{611.5,-607.8,17.2}
};

new Float:gMedPlayerSpawns[2][3] = {
{1178.1,-1321.0,14.1},
{1177.7,-1325.0,14.0}
};

new Titel[pBoxingStats];
new CKInfo[10][cCKInfo];
new PaperInfo[10][pPaperInfo];
stock Paper[MAX_PLAYERS][pPaper];
new FamilyInfo[10][fInfo];
new TurfInfo[6][zInfo];
new Turfs[6];
new Fishes[MAX_PLAYERS][pFishing];
new Cooking[MAX_PLAYERS][pCooking];
new Groceries[MAX_PLAYERS][pGroceries];
new Unspec[MAX_PLAYERS][pSpec];
new News[hNews];
new PlayerInfo[MAX_PLAYERS][pInfo];
new HouseInfo[34][hInfo];
new BizzInfo[5][bInfo];
new SBizzInfo[12][sbInfo];
new PlayerHaul[100][pHaul];
new PlayerCrime[MAX_PLAYERS][pCrime];
new MissionInfo[mInfo];
new PlayMission[kInfo];

new RandCars[20][1] = {
{496},{542},{507},{585},
{466},{492},{579},{559},
{400},{551},{516},{475},
{561},{550},{566},{558},
{562},{562},{603},{560}
};

new RandLCars[1][1] = {
{431}// coach
};

stock GunPrice[30][1] = {
{500}, //parachute
{400}, //golfclub
{300}, //nightstick
{200}, //knife
{700}, //baseballbat
{300}, //shovel
{100}, //poolcue
{400}, //purpledildo
{780}, //whitedildo
{560}, //longwhitedildo
{530}, //whitedildo2
{200}, //flowers
{600}, //cane
{500}, //sdpistol
{1000}, //colt45
{3000}, //deagle
{2000}, //Tec9
{3000}, //uzi
{2500}, //mp5
{3000}, //shotgun
{6000}, //spas12
{4000}, //sawnoff
{5000}, //ak47
{5000}, //m4
{1000}, //rifle
{25}, //pistolammo
{40}, //shotgunammo
{25}, //smgammo
{40}, //assaultammo
{50} //rifle
};

new JoinPed[52][1] = {
{280},//POLICE_FORCE
{281},
{282},
{283},
{284},
{285},
{288},
{71},
{166},
{295},
{148},
{286},//FBI/ATF
{164},
{163},
{287},//NATIONAL_GUARD
{285},
{70},//FIRE/AMBULANCE
{274},
{275},
{276},
{277},
{278},
{279},
{258},//LA_COSA_NOSTRA
{127},
{126},
{125},
{124},
{113},
{111},
{98},
{120},//YAKUZA
{121},
{122},
{123},
{169},
{186},
{228},
{127},//HITMANS
{165},
{186},
{93},
{141},
{148},//NEWS_REPORTERS
{188},
{187},
{255},//TAXI_CAB_COMPANY
{253},
{59},//DRIVING/FLYING_SCHOOL
{60},//DRIVING/FLYING_SCHOOL
{76},//DRIVING/FLYING_SCHOOL
{150}//DRIVING/FLYING_SCHOOL
};

new Peds[217][1] = {
{264},
{288},//TEAM_ADMIN
{286},{287},{228},{113},{120},{147},{294},{227},{61},{171},
{247},//CIVILIANS DOWN HERE
{248},{100},{256},{263},{262},{261},{260},{259},{258},{257},{256},{255},
{253},{252},{251},{249},{246},{245},{244},{243},{242},{241},{240},{239},
{238},{237},{236},{235},{234},{233},{232},{231},{230},{229},
{226},{225},{173},{174},{175},{224},{223},{222},{221},{220},{219},{218},
{217},{216},{215},{214},{213},{212},{211},{210},{209},
{207},{206},{205},{204},{203},{202},{201},{200},{199},{198},{197},{196},
{195},{194},{193},{192},{191},{190},{189},{185},{184},{183},
{182},{181},{180},{179},{178},{176},{172},{170},{168},{167},{162},
{161},{160},{159},{158},{157},{156},{155},{154},{153},{152},{151},
{146},{145},{144},{143},{142},{141},{140},{139},{138},{137},{136},{135},
{134},{133},{132},{131},{130},{129},{128},{254},{99},{97},{96},{95},{94},
{92},{90},{89},{88},{87},{85},{84},{83},{82},{81},{80},{79},{78},{77},{76},
{75},{73},{72},{69},{68},{67},{66},{64},{63},{62},{58},{57},{56},{55},
{54},{53},{52},{51},{50},{49},{45},{44},{43},{41},{39},{38},{37},{36},{35},
{34},{33},{32},{31},{30},{29},{28},{27},{26},{25},{24},{23},{22},{21},{20},
{19},{18},{17},{16},{15},{14},{13},{12},{11},{10},{1},{2},
{290},//ROSE
{291},//PAUL
{292},//CESAR
{293},//OGLOC
{187},
{296},//JIZZY
{297},//MADDOGG
{298},//CAT
{299}//ZERO
};

new Float:HouseCarSpawns[34][4] = {
{-2637.2544,165.0454,4.2919,179.9976},//House 2
{2064.4,-1694.4,13.1,271.1561},//House 1
{-2712.7625,870.3005,70.5348,89.1608},//House 2
{1109.8,-968.0,42.7,0.0},//house 3
{2497.6274,-2025.6306,13.2521,355.4281}, // House 4
{2645.0,-1990.8,13.1,180.0},//House - 5
{-2724.8965,914.8384,67.4253,110.1072},//house 6
{1910.5149,-1120.5304,25.4493,177.8350},//house 7
{828.8,-887.0,68.5,230.7095},//House 8
{2149.6,-1610.9,14.0,90.7904},//House 9
{760.1,-1687.8,4.3,180.6},//House 10
{645.5,-1616.1,14.9,0.0},//House 11
{-2635.2371,931.1931,71.5643,215.3709},//House 12
{-2665.9224,989.9724,64.6955,1.7814},//House 13
{959.5864,-901.0845,45.8584,177.3087},//House 14
{2445.8,-1326.8,23.6,18.4},//House 15
{2845.9,-1286.8,18.9,90.0},//house 16
{2159.8,-1803.9,13.3,271.4}, //House 17
{-2693.7847,132.3186,4.1676,89.5330},//House 18
{-2723.0105,977.7357,54.2926,359.9068},//House 19
{1514.0,-694.6,94.5,90.0},//House 20
{1246.7,-1107.6,25.5,266.4},//House 21
{831.7,-857.5,69.9,180.0},//House 22
{1007.9,-659.4,121.1,130.6194},//House 23
{1110.0,-726.4,100.1,90.0},//House 24
{259.7,-1221.0,74.7,202.0011},//House 25
{1463.7,-901.7,55.8,359.0},//house 26
{1440.1,-890.6,51.2,0.0},//house 27
{-2528.8298,2250.2998,4.8112,334.9590},//house 28
{-2554.7874,2270.5356,4.9064,333.9774}, //House 29
{-2371.1323,2438.4104,9.0698,159.2582},//House 30
{-2237.9492,893.7390,66.4872,89.7571},//House 31
{-2529.4817,-142.6608,19.7107,4.2929}, //House 32
{-2616.1897,-108.4479,4.1693,269.8246}//House 33
};

new CarSpawns[182][eCars] = {
	{405,-2125.7424,658.0462,52.2988,93.9612},//carid 90
	{426,-2158.0222,657.3932,52.2775,272.8372},
	{445,-1926.3204,585.6179,34.9963,359.8303},
	{492,2229.2,-1170.2,25.7,86.9},
	{507,-2214.8047,-82.7890,35.0474,0.6476},
	{545,2217.0,-1157.2,25.7,269.8},
	{547,405.9748,-1264.3921,50.1237,24.2110},
	{550,-1497.4576,845.8479,6.9382,88.5201},
	{551,-1741.0051,811.0620,24.5782,270.6681},
	{560,2106.4695,-1248.7920,24.0461,0.1524},
	{566,2196.2891,-1277.7905,24.2147,180.4522},
	{402,-1704.3132,999.7747,17.3646,90.0725},
	{405,216.5521,-1431.4004,13.0853,132.5749},
	{554,334.2231,-1343.7405,14.3828,209.9581},
	{507,697.4343,-1230.9486,16.5063,298.7916},
	{545,723.9850,-1121.5535,18.1450,333.9010},
	{536,666.8468,-467.6579,16.0734,90.8623},
	{560,668.1161,-546.2436,16.0413,89.4239},
	{540,912.2176,-996.2035,38.1402,7.5764},
	{482,-1758.3512,910.7219,24.5923,269.8633},
	{547,981.8715,-917.3546,41.5443,88.0589},
	{550,1188.4082,-925.1859,42.8590,277.5563},
	{400,-1699.4597,1035.9624,45.0934,91.6588},
	{405,1450.2,-937.1,36.2,269.6909}, //116
	{492,2148.3257,-1175.2518,24.1959,269.6909},
	{507,-1786.7155,1205.1598,24.7812,178.8758},
	{545,-1716.5907,1350.4829,6.8346,44.2506},
	{540,2348.2910,-1167.9983,27.3637,323.1586},
	{482,2502.0388,-1134.9507,39.1953,150.9506},
	{547,-2166.4534,1251.1536,27.2650,1.0352},
	{550,2853.1858,-1326.8011,11.1511,278.9301},
	{551,-2040.4761,1107.7072,53.4166,89.8473},
	{533,2796.9031,-1567.2024,10.6386,272.4041},
	{482,2813.2175,-1673.0276,9.6638,2.3369},
	{547,2827.6736,-1703.9755,9.7308,77.2896},
	{550,2809.3872,-1837.2391,9.7398,268.9880},
	{551,-2438.0784,1341.1190,7.6988,84.5107},
	{566,2411.5386,-2134.7576,13.9352,0.7795},
	{554,1389.7467,-2695.9370,13.4164,121.1818},
	{405,783.1359,-1601.8208,13.2577,270.9069},
	{554,782.7205,-1619.3584,13.2653,93.0550},
	{426,923.0841,-1361.7990,13.0324,181.1371},
	{445,-2644.6819,1342.3251,6.8981,270.7903},
	{492,1174.6599,-922.1939,43.1189,276.8927},
	{507,1363.0210,-1288.3124,13.2839,180.1453},
	{545,1363.2723,-1260.8229,13.0954,179.5841},
	{540,2383.5627,-1927.9207,13.2436,359.6281},
	{482,-2635.0933,1377.1693,6.8692,180.6415},
	{547,-2513.1277,1209.6135,37.1506,270.2610},
	{550,2396.6899,-1966.8123,13.2793,271.6838},
	{551,2391.1135,-1500.6554,23.6355,269.7709},
	{560,-2273.8679,921.3550,66.3095,0.6336},
	{405,-2153.0779,953.6602,79.7271,180.3209},
	{554,334.3586,-1789.3143,4.6717,178.7722},
	{426,343.8039,-1808.9827,4.3090,181.8368},
	{445,-2129.2915,787.6183,69.3346,87.1812},
	{492,646.4998,-1771.6411,13.2905,348.7706},
	{507,-2151.9524,395.9857,34.9395,180.7696},//150
	{545,-2078.8027,265.4074,35.1672,268.0607},
	{540,-2034.8334,178.8471,28.5682,269.9615},
	{482,438.9431,-1625.4088,25.7951,0.1850},
	{547,453.3896,-1494.3240,30.7917,7.7513},
	{550,487.6469,-1516.2312,20.0235,185.5384},
	{551,300.5775,-1490.8882,24.3748,235.1359},
	{560,-2180.1323,41.8542,35.1717,269.9866},
	{566,524.0590,-1375.0093,15.8231,193.3626},
	{405,598.9131,-1519.1414,14.8214,180.4083},
	{554,-2488.1333,-133.0336,25.3507,90.1064},
	{426,-2499.5225,45.0666,25.2641,89.9251},
	{445,-2636.7976,-55.4094,4.0630,359.9826},
	{492,-2718.5115,-124.4794,4.3505,269.1428},
	{507,736.8572,-1337.1550,13.3140,271.3832},
	{545,856.7003,-1363.1852,13.4093,179.8542},//165
	{482,888.1506,-1659.2727,13.3296,1.2414},
	{547,879.1024,-1669.2560,13.3305,180.5853},
	{550,-2134.1443,-453.9576,35.1479,95.0877},
	{551,920.4441,-1823.0966,12.3452,84.1821},
	{560,-1639.3900,-567.5057,13.9530,80.1994},
	{566,1062.6744,-1757.9412,13.1956,89.0572},
	{405,-2265.1501,148.9554,34.8837,269.3405},
	{554,1081.8948,-1629.9564,13.4064,90.0880},
	{426,981.7941,-1523.5115,13.3379,267.2751},
	{445,1014.7464,-1434.4586,13.3292,266.3129},
	{492,492.6386,-1555.3513,17.1462,213.1128},//DERBY
	{507,2684.6,-2019.0,13.3 ,0.8777},
	{545,1096.1,-1379.9,13.3,270.1909},//178
	{540,-2743.6772,-303.1675,7.1422,49.0919},//179 DERBY
	{482,1182.2568,-1219.2407,18.4163,0.5578},
	{547,1260.9978,-1187.1921,23.3559,183.3606},
	{550,1331.9304,-1081.3899,24.9941,90.4092},
	{551,1284.8755,-1525.5013,13.3451,269.4388},//near taxi
	{560,1279.1887,-1539.2032,13.3201,94.8070},//near taxi
	{566,1275.9120,-1646.7448,13.3273,267.2669},
	{405,-2200.5999,-2503.3606,30.4213,321.7648},
	{554,1253.9153,-1833.3832,13.1734,175.3692},
	{426,1279.2875,-1814.4156,13.1657,93.6385},
	{445,-2205.5234,-2439.3523,30.4224,51.1660},
	{492,1479.9131,-1737.8813,13.2418,269.5805},
	{507,1508.1047,-1737.7089,13.2418,270.0250},
	{545,1618.0411,-1891.1044,13.3278,0.3364},
	{540,1623.7291,-1892.7234,13.3307,180.0126},
	{482,-2079.6389,-2303.7983,30.3466,322.7155},
	{547,1743.5837,-1844.6041,13.3557,180.3384},
	{550,1838.1904,-1871.3842,13.1703,358.5452},
	{551,-1557.8568,-2741.5632,48.3481,144.5150},
	{560,1777.1376,-1910.0310,13.1681,91.0725},
	{566,-16.7753,-2503.6228,36.4593,121.7103},
	{566,1981.0780,-1986.3513,13.3275,2.1479},
	{405,218.4485,-173.3024,1.3809,90.0117},
	{554,199.5586,-155.4912,1.3827,0.3471},
	{426,1984.7471,-2066.7776,13.1625,359.7226},
	{445,1938.0565,-2086.8459,13.3429,268.3414},
	{492,318.4840,-86.0588,2.0804,90.9324},
	{507,-113.9556,-39.4382,2.9209,164.0464},
	{545,115.3321,-217.1147,1.3028,89.7911},
	{540,1748.0751,-2084.2090,13.3324,0.4337},
	{482,1560.5026,-2260.5457,13.3258,268.7398},
	{547,1461.6943,-1505.1688,13.2541,356.9007},
	{550,1426.4930,-1402.3170,13.1800,181.0290},
	{551,1435.0645,-1325.6835,13.2580,270.9400},
	{560,1513.9486,-1272.5691,14.2685,181.0697},
	{566,1583.7561,-1338.7435,16.1896,359.8619},
	{405,-2760.5156,-312.1838,7.1557,3.8747},//DERBY
	{554,-2766.6875,-281.2887,7.1613,180.1256},//DERBY
	{426,1430.2316,-1054.8555,22.8693,359.3625},
	{445,1574.1168,-1036.7643,23.6151,145.6786},
	//{492,1617.6676,-1009.8663,23.6052,356.8697},
	{507,1645.3188,-1036.5238,23.6027,0.7258},
	{545,485.9422,-1467.4543,18.3154,157.6833},//DERBY
	{540,1770.4874,-1060.9886,23.6658,179.2750},
	{482,-2781.4741,-281.6054,7.1515,181.0279},//DERBY
	{547,1653.1766,-1134.8994,23.6110,178.6835},
	{550,1617.3746,-1132.8293,23.6117,91.7300},
	{551,1790.0190,-1292.9065,13.2653,267.2964},
	{560,1754.3009,-1476.8170,13.2402,269.6320},
	{554,2003.3417,-1121.4993,26.3879,357.4926},
	{426,2084.2334,-1170.0986,24.2042,91.8975},
	{492,2229.2278,-1345.4033,23.6892,93.3009},
	{507,2332.5684,-1362.4845,23.7297,358.1198},
	{545,2384.1567,-1275.6326,23.9198,101.6528},
	{540,2432.3149,-1226.0785,24.9941,17.9805},
	{482,2426.9612,-1224.4158,25.0000,202.7159},
	{547,2438.4309,-1321.6925,24.1225,269.7535},
	{551,2612.9702,-1262.6970,48.2461,269.4752},
	{560,2659.4529,-1428.4343,30.1790,266.5051},
	{566,2659.7053,-1422.6743,30.1714,89.8159},
	{405,2485.5313,-1556.1823,23.7478,178.8338},
	{554,2478.7664,-1555.7006,23.7226,183.6043},
	{426,2605.3967,-1365.8829,34.6461,359.9891},
	{445,2754.7136,-1373.0253,40.1154,91.4169},
	{492,2717.3662,-1468.0308,30.0894,1.0298},
	{507,2816.7195,-1449.4285,15.9549,268.9106},
	{545,2816.9937,-1441.5880,15.9544,90.7779},
	{540,2681.9016,-1673.3879,9.1290,0.5605},
	{482,2442.5845,-1642.7507,13.1644,180.3454},
	{547,2361.3120,-1674.6146,13.2505,357.4959},
	{550,2298.3535,-1633.7542,14.3849,80.8107},
	{551,2297.9077,-1639.9464,14.4352,94.4292},
	{560,2255.4045,-1664.5736,15.1304,74.6898},
	{566,2234.1057,-1726.9386,13.1665,271.7536},
	{405,2319.3833,-1716.6823,13.2518,359.8540},
	{554,2474.5105,-1755.9194,13.2522,270.5967},
	{426,2501.8213,-1754.2794,13.1208,176.4916}, //= 255
	{445,2489.1560,-1952.6886,13.1366,178.1629},
	{492,2495.4326,-1953.2922,13.1299,356.5514},
	{507,2306.7168,-1989.6796,13.2639,184.8385},
	{482,2056.1807,-1904.7751,13.2502,2.2910},
	{550,2064.9871,-1919.1674,13.2504,180.8575},
	{551,1886.4812,-2022.9338,13.0964,179.4265},
	{560,1824.8976,-2019.8374,13.0875,272.5273},
	{566,1942.1669,-1862.6425,13.2679,264.5590},
	{405,1923.9409,-1795.5616,13.0877,90.0886},
	{554,1807.0905,-1571.7120,13.1659,125.1048},
	{426,1809.9016,-1676.0603,13.2422,180.7589},
	{445,1809.6266,-1653.3402,13.2365,180.6530},
	{492,1809.7056,-1660.3019,13.2380,180.6262},
	{507,1978.4003,-1675.0157,15.6741,269.7336},
	{545,1974.8230,-1693.5488,15.6741,92.1162},
	{540,1929.2253,-1584.6954,13.2700,185.5542},
	{482,1731.9725,-1590.8959,13.1630,77.7249},
	{547,1721.5776,-1589.2834,13.1526,80.9057},
	{550,1695.1428,-1519.2667,13.1671,0.7121},
	{551,1694.7080,-1501.7454,13.1675,357.8150}
    };