/*
	Project: GodFather
	Author: MisterMagik, steeZ
	File name: variables.inc
	Date: 12.03.2026
	Modified: 12.03.2026
	Desc: All server vars, including arrays.
*/

new MySQL:mySQLHandle;

new queryStr[2048];
new mainStr[512];

new accName[MAX_PLAYERS][24];
new escapedName[MAX_PLAYERS][24];

new accPassword[MAX_PLAYERS][65];
new accSalt[MAX_PLAYERS][17];
new bool:accAntiCrash[MAX_PLAYERS];
new bool:accLastCrash[MAX_PLAYERS];

new bool:loadedIntro[MAX_PLAYERS];
new bool:createdChar[MAX_PLAYERS];
new bool:VehAnim[MAX_PLAYERS];

new AdminVehModelID;
new AdminVehColor[2];
new AdminVehOwner[2];

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
new carselect[15];
new objstore[128];
new cbjstore[128];
new motd[256];
//new RStart;
new ghour = 0;
new gminute = 0;
new gsecond = 0;
new numplayers = 0;
new dollah = 1000; // Amount player recieves on spawn.
new realtime = 1;
new wtime = 15;
new levelcost = 25000;
new callcost = 10; //20 seconds
new realchat = 1;
new timeshift = -1;
new shifthour;
new intrate = 1;
new levelexp = 4;
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
new VehicleInfo[MAX_VEHICLES][vInfo];
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

stock femaleSkinsId[] = {
	9, 10, 11, 12, 13, 31, 38, 39, 40, 41, 53,
	54, 55, 56, 63, 64, 65, 69, 75, 76, 77, 85, 87, 88, 89, 90, 91, 92, 93, 
	129, 130, 131, 138, 139, 140, 141, 145, 148, 150, 151, 152, 157, 169, 172, 178, 190,
	191, 192, 193, 194, 195, 196, 198, 199, 201, 205, 211, 214, 215, 218, 219, 224, 225, 226,
	232, 233, 237, 243, 244, 245, 246, 251, 256, 257, 263, 298, 306, 307, 308, 309
};

stock maleSkinsId[] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
	26, 27, 28, 29, 30, 32, 33, 34, 35, 36, 37, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 
	57, 58, 59, 60, 61, 62, 66, 67, 68, 70, 71, 71, 72, 73, 74, 78, 79, 80, 81, 82, 83, 84, 86, 
	94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114,
	115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 132, 133, 134, 135, 136, 137,
	142, 143, 144, 146, 147, 149, 153, 154, 155, 156, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167,
	168, 170, 171, 173, 174, 175, 176, 177, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 197,
	200, 202, 203, 204, 206, 207, 208, 209, 210, 212, 213, 216, 217, 220, 221, 222, 223, 227, 228, 229,
	230, 231, 234, 235, 236, 238, 239, 240, 241, 242, 247, 248, 249, 250, 252, 253, 254, 255, 258, 259,
	260, 261, 262, 264, 265, 266, 267, 268, 269, 270, 271, 272, 273, 274, 275, 276, 276, 277, 278, 279,
	280, 281, 282, 283, 284, 285, 286, 287, 288, 289, 290, 291, 292, 293, 294, 295, 296, 297, 299, 300,
	301, 302, 303, 304, 305, 310, 311
};

stock cheapVehicles[] = {
	
};

stock bicycyleVehicles[] = {
	
};

stock bikeVehicles[] = {
	
};

new VehicleNames[][] = {
	"Landstalker",
	"Bravura",
	"Buffalo",
	"Linerunner",
	"Perenniel",
	"Sentinel",
	"Dumper",
	"Firetruck",
	"Trashmaster",
	"Stretch",
	"Manana",
	"Infernus",
	"Voodoo",
	"Pony",
	"Mule",
	"Cheetah",
	"Ambulance",
	"Leviathan",
	"Moonbeam",
	"Esperanto",
	"Taxi",
	"Washington",
	"Bobcat",
	"Mr Whoopee",
	"BF Injection",
	"Hunter",
	"Premier",
	"Enforcer",
	"Securicar",
	"Banshee",
	"Predator",
	"Bus",
	"Rhino",
	"Barracks",
	"Hotknife",
	"Trailer",
	"Previon",
	"Coach",
	"Cabbie",
	"Stallion",
	"Rumpo",
	"RC Bandit",
	"Romero",
	"Packer",
	"Monster",
	"Admiral",
	"Squalo",
	"Seasparrow",
	"Pizzaboy",
	"Tram",
	"Trailer",
	"Turismo",
	"Speeder",
	"Reefer",
	"Tropic",
	"Flatbed",
	"Yankee",
	"Caddy",
	"Solair",
	"Berkley's RC Van",
	"Skimmer",
	"PCJ-600",
	"Faggio",
	"Freeway",
	"RC Baron",
	"RC Raider",
	"Glendale",
	"Oceanic",
	"Sanchez",
	"Sparrow",
	"Patriot",
	"Quad",
	"Coastguard",
	"Dinghy",
	"Hermes",
	"Sabre",
	"Rustler",
	"ZR-350",
	"Walton",
	"Regina",
	"Comet",
	"BMX",
	"Burrito",
	"Camper",
	"Marquis",
	"Baggage",
	"Dozer",
	"Maverick",
	"News Chopper",
	"Rancher",
	"FBI Rancher",
	"Virgo",
	"Greenwood",
	"Jetmax",
	"Hotring",
	"Sandking",
	"Blista",
	"Police Maverick",
	"Boxville",
	"Benson",
	"Mesa",
	"RC Goblin",
	"Hotring-Racer",
	"Hotring-Racer",
	"Bloodring-Banger",
	"Rancher",
	"Super-GT",
	"Elegant",
	"Journey",
	"Bike",
	"MTB", //Rower górski
	"Beagle",
	"Cropdust",
	"Stunt",
	"Tanker",
	"RoadTrain",
	"Nebula",
	"Majestic",
	"Buccaneer",
	"Shamal",
	"Hydra",
	"FCR-900",
	"NRG-500",
	"HPV1000",
	"Cement Truck",
	"Tow Truck",
	"Fortune",
	"Cadrona",
	"FBI Truck",
	"Willard",
	"Forklift",
	"Tractor",
	"Combine",
	"Feltzer",
	"Remington",
	"Slamvan",
	"Blade",
	"Freight",
	"Streak",
	"Vortex",
	"Vincent",
	"Bullet",
	"Clover",
	"Sadler",
	"Firetruck",
	"Hustler",
	"Intruder",
	"Primo",
	"Cargobob",
	"Tampa",
	"Sunrise",
	"Merit",
	"Utility",
	"Nevada",
	"Yosemite",
	"Windsor",
	"Monster Truck A",
	"Monster Truck B",
	"Uranus",
	"Jester",
	"Sultan",
	"Stratum",
	"Elegy",
	"Raindance",
	"RC Tiger",
	"Flash",
	"Tahoma",
	"Savanna",
	"Bandito",
	"Freight",
	"Trailer",
	"Kart",
	"Mower",
	"Duneride",
	"Sweeper",
	"Broadway",
	"Tornado",
	"AT-400",
	"DFT-30",
	"Huntley",
	"Stafford",
	"BF-400",
	"Newsvan",
	"Tug",
	"Trailer",
	"Emperor",
	"Wayfarer",
	"Euros",
	"Hotdog",
	"Club",
	"Trailer",
	"Trailer",
	"Andromada",
	"Dodo",
	"RC Cam",
	"Launch",
	"LSPD",
	"SFPD",
	"LVPD",
	"PD Ranger",
	"Picador",
	"S.W.A.T. Van",
	"Alpha",
	"Phoenix",
	"Glendale",
	"Sadler",
	"Luggage Trailer",
	"Luggage Trailer",
	"Stair Trailer",
	"Boxville",
	"Farm Plow",
	"Utility Trailer"
};

new Iterator:VehItter<MAX_VEHICLES>;

new Text:SplashScreen;
new Text:Intro[4];
new Text:VehicleStats[MAX_PLAYERS];
