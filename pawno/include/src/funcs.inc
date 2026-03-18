/*
	Project: GodFather
	Author: MisterMagik, steeZ
	File name: enums.inc
	Date: 12.03.2026
	Modified: 12.03.2026
	Desc: Server functions.
*/

stock ConnectingMySQL() {
	mySQLHandle = mysql_init(LOG_ALL, 1);
	mysql_connect(MYSQL_HOST, MYSQL_USER, MYSQL_PASSWORD, MYSQL_DB, mySQLHandle, 1);

	if(!mysql_ping()) {
		printf("[MYSQL] Pomyslnie polaczono z baza danych!");
	} else {
		new error[64];

		mysql_error(error);

		printf("[MYSQL] Brak polacznia z baza danych! Blad: %s", error);
		SendRconCommand("exit");
	}
}

stock osrp_ShowPlayerDialog(playerid, dialogid, style, caption[], info[], button1[], button2[]) {
	PlayerInfo[playerid][pDialog] = dialogid;
	return ShowPlayerDialog(playerid, dialogid, style, caption, info, button1, button2);
}

stock osrp_TogglePlayerSpectating(playerid, toggle) {
	PlayerInfo[playerid][pToggle] = bool:toggle;
	TogglePlayerSpectating(playerid, toggle);
}

stock GeneratePasswordSalt() {
	new salt[17];

	for(new i = 0; i < 16; i++) {
		salt[i] = random(79) + 47;
	}

	salt[16] = 0;
	return salt;
}

stock Float:GetDistanceBetweenPlayers(p1,p2)
{
	new Float:x1,Float:y1,Float:z1,Float:x2,Float:y2,Float:z2;
	if(!IsPlayerConnected(p1) || !IsPlayerConnected(p2))
	{
		return -1.00;
	}
	GetPlayerPos(p1,x1,y1,z1);
	GetPlayerPos(p2,x2,y2,z2);
	return floatsqroot(floatpower(floatabs(floatsub(x2,x1)),2)+floatpower(floatabs(floatsub(y2,y1)),2)+floatpower(floatabs(floatsub(z2,z1)),2));
}

stock SearchingHit(playerid)
{
	new string[256];
	new giveplayer[MAX_PLAYER_NAME];
	new searchhit = 0;
	for(new i=0; i<MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i))
		{
		    if(searchhit == 0)
		    {
			    if(PlayerInfo[i][pHeadValue] > 0 && GotHit[i] == 0 && PlayerInfo[i][pMember] != 8)
			    {
			        GetPlayerName(i, giveplayer, sizeof(giveplayer));
			        searchhit = 1;
			        hitfound = 1;
			        hitid = i;
			        for(new k=0; k<MAX_PLAYERS; k++)
					{
						if(IsPlayerConnected(k))
						{
				        	if(PlayerInfo[k][pMember] == 8 || PlayerInfo[k][pLeader] == 8)
				        	{
	               				SendClientMessage(k, COLOR_WHITE, "|__________________ Hitman Agency News __________________|");
				                SendClientMessage(k, COLOR_DBLUE, "*** Incoming Message: A Hit has become available. ***");
				                format(string, sizeof(string), "Person: %s   ID: %d   Value: $%d", giveplayer, i, PlayerInfo[i][pHeadValue]);
								SendClientMessage(k, COLOR_DBLUE, string);
								SendClientMessage(k, COLOR_YELLOW, "Use Givehit hitmanid, to assign the Contract to one of the Hitmans.");
								SendClientMessage(k, COLOR_WHITE, "|________________________________________________________|");
	      					}
					    }
					}
					return 0;
			    }
			}
		}
	}
	if(searchhit == 0)
	{
	    SendClientMessage(playerid, COLOR_GREY, "   No Contracts available !");
	}
	return 0;
}

stock ExtortionBiz(bizid, money)
{
    new string[256];
    format(string, sizeof(string), "No-one");
    if(strcmp(BizzInfo[bizid][bExtortion],string, true ) == 0 )
	{
	    return 0;
	}
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
	    if(IsPlayerConnected(i))
	    {
	        new name[MAX_PLAYER_NAME];
			new wstring[MAX_PLAYER_NAME];
			GetPlayerName(i, name, sizeof(name));
			format(string, sizeof(string), "%s", name);
			strmid(wstring, string, 0, strlen(string), 255);
			if(strcmp(BizzInfo[bizid][bExtortion] ,wstring, true ) == 0 )
			{
			    new value = money / 100;
			    value = value * 10;
			    GivePlayerMoney(i, value);
			    BizzInfo[bizid][bTill] -= value;
			}
		}
	}
	return 1;
}

stock ExtortionSBiz(bizid, money)
{
    new string[256];
    format(string, sizeof(string), "No-one");
    if(strcmp(SBizzInfo[bizid][sbExtortion],string, true ) == 0 )
	{
	    return 0;
	}
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
	    if(IsPlayerConnected(i))
	    {
	        new name[MAX_PLAYER_NAME];
			new wstring[MAX_PLAYER_NAME];
			GetPlayerName(i, name, sizeof(name));
			format(string, sizeof(string), "%s", name);
			strmid(wstring, string, 0, strlen(string), 255);
			if(strcmp(SBizzInfo[bizid][sbExtortion] ,wstring, true ) == 0 )
			{
			    new value = money / 100;
			    value = value * 10;
			    GivePlayerMoney(i, value);
			    SBizzInfo[bizid][sbTill] -= value;
			}
		}
	}
	return 1;
}

stock DollahScoreUpdate()
{
	new LevScore;
	for(new i=0; i<MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i))
		{
   			LevScore = PlayerInfo[i][pLevel];
			SetPlayerScore(i, LevScore);
		}
	}
	return 1;
}

stock right(source[], len)
{
	new retval[MAX_STRING], srclen;
	srclen = strlen(source);
	strmid(retval, source, srclen - len, srclen, MAX_STRING);
	return retval;
}

stock IsAnInstructor(playerid)
{
	if(IsPlayerConnected(playerid))
	{
	    new leader = PlayerInfo[playerid][pLeader];
	    new member = PlayerInfo[playerid][pMember];
	    if(member==11)
		{
		    return 1;
		}
		if(leader==11)
		{
		    return 1;
		}
	}
	return 0;
}

stock IsAMember(playerid)
{
	if(IsPlayerConnected(playerid))
	{
	    new leader = PlayerInfo[playerid][pLeader];
	    new member = PlayerInfo[playerid][pMember];
	    if(member==5 || member==6 || member==8)
		{
		    return 1;
		}
		if(leader==5 || leader==6 || leader==8)
		{
		    return 1;
		}
	}
	return 0;
}

stock IsACop(playerid)
{
	if(IsPlayerConnected(playerid))
	{
	    new leader = PlayerInfo[playerid][pLeader];
	    new member = PlayerInfo[playerid][pMember];
	    if(member==1 || member==2 || member==3)
		{
		    return 1;
		}
		else if(leader==1 || leader==2 || leader==3)
		{
		    return 1;
		}
	}
	return 0;
}

stock IsAtClothShop(playerid)
{
    if(IsPlayerConnected(playerid))
	{
        if(PlayerToPoint(25.0,playerid,207.5627,-103.7291,1005.2578) || PlayerToPoint(25.0,playerid,203.9068,-41.0728,1001.8047))
		{//Binco & Suburban
		    return 1;
		}
		else if(PlayerToPoint(30.0,playerid,214.4470,-7.6471,1001.2109) || PlayerToPoint(50.0,playerid,161.3765,-83.8416,1001.8047))
		{//Zip & Victim
		    return 1;
		}
	}
	return 0;
}

stock IsAtGasStation(playerid)
{
    if(IsPlayerConnected(playerid))
	{
		if(PlayerToPoint(6.0,playerid,1004.0070,-939.3102,42.1797) || PlayerToPoint(6.0,playerid,1944.3260,-1772.9254,13.3906))
		{//LS
		    return 1;
		}
		else if(PlayerToPoint(6.0,playerid,-90.5515,-1169.4578,2.4079) || PlayerToPoint(6.0,playerid,-1609.7958,-2718.2048,48.5391))
		{//LS
		    return 1;
		}
		else if(PlayerToPoint(6.0,playerid,-2029.4968,156.4366,28.9498) || PlayerToPoint(8.0,playerid,-2408.7590,976.0934,45.4175))
		{//SF
		    return 1;
		}
		else if(PlayerToPoint(5.0,playerid,-2243.9629,-2560.6477,31.8841) || PlayerToPoint(8.0,playerid,-1676.6323,414.0262,6.9484))
		{//Between LS and SF
		    return 1;
		}
		else if(PlayerToPoint(6.0,playerid,2202.2349,2474.3494,10.5258) || PlayerToPoint(10.0,playerid,614.9333,1689.7418,6.6968))
		{//LV
		    return 1;
		}
		else if(PlayerToPoint(8.0,playerid,-1328.8250,2677.2173,49.7665) || PlayerToPoint(6.0,playerid,70.3882,1218.6783,18.5165))
		{//LV
		    return 1;
		}
		else if(PlayerToPoint(8.0,playerid,2113.7390,920.1079,10.5255) || PlayerToPoint(6.0,playerid,-1327.7218,2678.8723,50.0625))
		{//LV
		    return 1;
		}
	}
	return 0;
}

stock IsAtFishPlace(playerid)
{
	if(IsPlayerConnected(playerid))
	{
	    if(PlayerToPoint(1.0,playerid,403.8266,-2088.7598,7.8359) || PlayerToPoint(1.0,playerid,398.7553,-2088.7490,7.8359))
		{//Fishplace at the bigwheel
		    return 1;
		}
		else if(PlayerToPoint(1.0,playerid,396.2197,-2088.6692,7.8359) || PlayerToPoint(1.0,playerid,391.1094,-2088.7976,7.8359))
		{//Fishplace at the bigwheel
		    return 1;
		}
		else if(PlayerToPoint(1.0,playerid,383.4157,-2088.7849,7.8359) || PlayerToPoint(1.0,playerid,374.9598,-2088.7979,7.8359))
		{//Fishplace at the bigwheel
		    return 1;
		}
		else if(PlayerToPoint(1.0,playerid,369.8107,-2088.7927,7.8359) || PlayerToPoint(1.0,playerid,367.3637,-2088.7925,7.8359))
		{//Fishplace at the bigwheel
		    return 1;
		}
		else if(PlayerToPoint(1.0,playerid,362.2244,-2088.7981,7.8359) || PlayerToPoint(1.0,playerid,354.5382,-2088.7979,7.8359))
		{//Fishplace at the bigwheel
		    return 1;
		}
	}
	return 0;
}

stock IsAtCookPlace(playerid)
{
	if(IsPlayerConnected(playerid))
	{
	    if(PlayerToPoint(3.0,playerid,369.9786,-4.0798,1001.8589))
	    {//Cluckin Bell
	        return 1;
	    }
	    else if(PlayerToPoint(3.0,playerid,376.4466,-60.9574,1001.5078) || PlayerToPoint(3.0,playerid,378.1215,-57.4928,1001.5078))
		{//Burgershot
		    return 1;
		}
		else if(PlayerToPoint(3.0,playerid,374.1185,-113.6361,1001.4922) || PlayerToPoint(3.0,playerid,377.7971,-113.7668,1001.4922))
		{//Well Stacked Pizza
		    return 1;
		}
	}
	return 0;
}

stock IsAtBar(playerid)
{
    if(IsPlayerConnected(playerid))
	{
		if(PlayerToPoint(4.0,playerid,495.7801,-76.0305,998.7578) || PlayerToPoint(4.0,playerid,499.9654,-20.2515,1000.6797))
		{//In grove street bar (with girlfriend), and in Havanna
		    return 1;
		}
		else if(PlayerToPoint(4.0,playerid,1215.9480,-13.3519,1000.9219) || PlayerToPoint(10.0,playerid,-2658.9749,1407.4136,906.2734))
		{//PIG Pen
		    return 1;
		}
	}
	return 0;
}

stock IsABoat(carid)
{
	if(carid >= 86 && carid <=90)
	{
		return 1;
	}
	return 0;
}

stock IsAPlane(carid)
{
	if(carid==39||carid==40||carid==60||carid==83||carid==91||carid==92||carid==93||carid==95||carid==96||carid==99||carid==100||carid==101||carid==102||carid==103||carid==104||carid==105||carid==106||carid==107||carid==108||carid==109)
	{
		return 1;
	}
	return 0;
}

stock IsACopCar(carid)
{
	if((carid >= 35) && (carid <= 60) || carid == 66 || carid == 67 || carid == 91 || carid == 92 || carid == 93 || carid == 36)
	{
	    if(carid == 45 || carid == 46 || carid == 55 || carid == 59) { return 0; }
		return 1;
	}
	return 0;
}

stock IsAnAmbulance(carid)
{
	if((carid >= 61) && (carid <= 63)|| carid == 83)
	{
		return 1;
	}
	return 0;
}

stock IsATruck(carid)
{
	if(carid >= 78 && carid <= 81)
	{
		return 1;
	}
	return 0;
}

stock ClearCK(ck)
{
    new string[MAX_PLAYER_NAME];
	format(string, sizeof(string), "No-one");
	strmid(CKInfo[ck][cSendername], string, 0, strlen(string), 255);
	strmid(CKInfo[ck][cGiveplayer], string, 0, strlen(string), 255);
	CKInfo[ck][cUsed] = 0;
	SaveCK();
	return 1;
}

stock ClearMarriage(playerid)
{
	if(IsPlayerConnected(playerid))
	{
	    new string[MAX_PLAYER_NAME];
		format(string, sizeof(string), "No-one");
		strmid(PlayerInfo[playerid][pMarriedTo], string, 0, strlen(string), 255);
		PlayerInfo[playerid][pMarried] = 0;
	}
	return 1;
}

stock ClearPaper(paper)
{
    new string[MAX_PLAYER_NAME];
	format(string, sizeof(string), "None");
	PaperInfo[paper][PaperUsed] = 0;
	strmid(PaperInfo[paper][PaperMaker], string, 0, strlen(string), 255);
	strmid(PaperInfo[paper][PaperTitle], string, 0, strlen(string), 255);
	strmid(PaperInfo[paper][PaperText1], string, 0, strlen(string), 255);
	strmid(PaperInfo[paper][PaperText2], string, 0, strlen(string), 255);
	strmid(PaperInfo[paper][PaperText3], string, 0, strlen(string), 255);
	strmid(PaperInfo[paper][PaperText4], string, 0, strlen(string), 255);
	strmid(PaperInfo[paper][PaperText5], string, 0, strlen(string), 255);
	strmid(PaperInfo[paper][PaperText6], string, 0, strlen(string), 255);
	strmid(PaperInfo[paper][PaperText7], string, 0, strlen(string), 255);
	SavePapers();
	return 1;
}

stock ClearFamily(family)
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
	    if(IsPlayerConnected(i))
	    {
	        if(PlayerInfo[i][pFMember] == family)
	        {
	            SendClientMessage(i, COLOR_LIGHTBLUE, "* The Family you are in got Deleted by the Organisation Leader, you got kicked out automaticly.");
	            PlayerInfo[i][pFMember] = 255;
	        }
	    }
	}
    new string[MAX_PLAYER_NAME];
	format(string, sizeof(string), "None");
	FamilyInfo[family][FamilyTaken] = 0;
	strmid(FamilyInfo[family][FamilyName], string, 0, strlen(string), 255);
	strmid(FamilyInfo[family][FamilyMOTD], string, 0, strlen(string), 255);
	strmid(FamilyInfo[family][FamilyLeader], string, 0, strlen(string), 255);
	format(string, sizeof(string), "0xFF000069");
	strmid(FamilyInfo[family][FamilyColor], string, 0, strlen(string), 255);
	FamilyInfo[family][FamilyMembers] = 0;
	FamilyInfo[family][FamilySpawn][0] = 0.0;
	FamilyInfo[family][FamilySpawn][1] = 0.0;
	FamilyInfo[family][FamilySpawn][2] = 0.0;
	FamilyInfo[family][FamilySpawn][3] = 0.0;
	FamilyInfo[family][FamilyInterior] = 0;
	SaveFamilies();
	return 1;
}

stock ClearCrime(playerid)
{
	if(IsPlayerConnected(playerid))
	{
		new string[MAX_PLAYER_NAME];
		format(string, sizeof(string), "********");
		strmid(PlayerCrime[playerid][pBplayer], string, 0, strlen(string), 255);
		strmid(PlayerCrime[playerid][pVictim], string, 0, strlen(string), 255);
		strmid(PlayerCrime[playerid][pAccusing], string, 0, strlen(string), 255);
		strmid(PlayerCrime[playerid][pAccusedof], string, 0, strlen(string), 255);
	}
	return 1;
}

stock FishCost(playerid, fish)
{
	if(IsPlayerConnected(playerid))
	{
		new cost = 0;
		switch (fish)
		{
		    case 1:
		    {
		        cost = 1;
		    }
		    case 2:
		    {
		        cost = 3;
		    }
		    case 3:
		    {
		        cost = 3;
		    }
		    case 5:
		    {
		        cost = 5;
		    }
		    case 6:
		    {
		        cost = 2;
		    }
		    case 8:
		    {
		        cost = 8;
		    }
		    case 9:
		    {
		        cost = 12;
		    }
		    case 11:
		    {
		        cost = 9;
		    }
		    case 12:
		    {
		        cost = 7;
		    }
		    case 14:
		    {
		        cost = 12;
		    }
		    case 15:
		    {
		        cost = 9;
		    }
		    case 16:
		    {
		        cost = 7;
		    }
		    case 17:
		    {
		        cost = 7;
		    }
		    case 18:
		    {
		        cost = 10;
		    }
		    case 19:
		    {
		        cost = 4;
		    }
		    case 21:
		    {
		        cost = 3;
		    }
		}
		return cost;
	}
	return 0;
}

stock ClearFishes(playerid)
{
	if(IsPlayerConnected(playerid))
	{
	    Fishes[playerid][pFid1] = 0; Fishes[playerid][pFid2] = 0; Fishes[playerid][pFid3] = 0;
		Fishes[playerid][pFid4] = 0; Fishes[playerid][pFid5] = 0;
		Fishes[playerid][pWeight1] = 0; Fishes[playerid][pWeight2] = 0; Fishes[playerid][pWeight3] = 0;
		Fishes[playerid][pWeight4] = 0; Fishes[playerid][pWeight5] = 0;
		new string[MAX_PLAYER_NAME];
		format(string, sizeof(string), "None");
		strmid(Fishes[playerid][pFish1], string, 0, strlen(string), 255);
		strmid(Fishes[playerid][pFish2], string, 0, strlen(string), 255);
		strmid(Fishes[playerid][pFish3], string, 0, strlen(string), 255);
		strmid(Fishes[playerid][pFish4], string, 0, strlen(string), 255);
		strmid(Fishes[playerid][pFish5], string, 0, strlen(string), 255);
	}
	return 1;
}

stock ClearFishID(playerid, fish)
{
	if(IsPlayerConnected(playerid))
	{
		new string[MAX_PLAYER_NAME];
		format(string, sizeof(string), "None");
		switch (fish)
		{
		    case 1:
		    {
		        strmid(Fishes[playerid][pFish1], string, 0, strlen(string), 255);
		        Fishes[playerid][pWeight1] = 0;
		        Fishes[playerid][pFid1] = 0;
		    }
		    case 2:
		    {
		        strmid(Fishes[playerid][pFish2], string, 0, strlen(string), 255);
		        Fishes[playerid][pWeight2] = 0;
		        Fishes[playerid][pFid2] = 0;
		    }
		    case 3:
		    {
		        strmid(Fishes[playerid][pFish3], string, 0, strlen(string), 255);
		        Fishes[playerid][pWeight3] = 0;
		        Fishes[playerid][pFid3] = 0;
		    }
		    case 4:
		    {
		        strmid(Fishes[playerid][pFish4], string, 0, strlen(string), 255);
		        Fishes[playerid][pWeight4] = 0;
		        Fishes[playerid][pFid4] = 0;
		    }
		    case 5:
		    {
		        strmid(Fishes[playerid][pFish5], string, 0, strlen(string), 255);
		        Fishes[playerid][pWeight5] = 0;
		        Fishes[playerid][pFid5] = 0;
		    }
		}
	}
	return 1;
}

stock ClearCooking(playerid)
{
	if(IsPlayerConnected(playerid))
	{
	    Cooking[playerid][pCookID1] = 0; Cooking[playerid][pCookID2] = 0; Cooking[playerid][pCookID3] = 0;
		Cooking[playerid][pCookID4] = 0; Cooking[playerid][pCookID5] = 0;
		Cooking[playerid][pCWeight1] = 0; Cooking[playerid][pCWeight2] = 0; Cooking[playerid][pCWeight3] = 0;
		Cooking[playerid][pCWeight4] = 0; Cooking[playerid][pCWeight5] = 0;
		new string[MAX_PLAYER_NAME];
		format(string, sizeof(string), "Nothing");
		strmid(Cooking[playerid][pCook1], string, 0, strlen(string), 255);
		strmid(Cooking[playerid][pCook2], string, 0, strlen(string), 255);
		strmid(Cooking[playerid][pCook3], string, 0, strlen(string), 255);
		strmid(Cooking[playerid][pCook4], string, 0, strlen(string), 255);
		strmid(Cooking[playerid][pCook5], string, 0, strlen(string), 255);
	}
	return 1;
}

stock ClearCookingID(playerid, cook)
{
	if(IsPlayerConnected(playerid))
	{
		new string[MAX_PLAYER_NAME];
		format(string, sizeof(string), "Nothing");
		switch (cook)
		{
		    case 1:
		    {
		        strmid(Cooking[playerid][pCook1], string, 0, strlen(string), 255);
		        Cooking[playerid][pCWeight1] = 0;
		        Cooking[playerid][pCookID1] = 0;
		    }
		    case 2:
		    {
		        strmid(Cooking[playerid][pCook2], string, 0, strlen(string), 255);
		        Cooking[playerid][pCWeight2] = 0;
		        Cooking[playerid][pCookID2] = 0;
		    }
		    case 3:
		    {
		        strmid(Cooking[playerid][pCook3], string, 0, strlen(string), 255);
		        Cooking[playerid][pCWeight3] = 0;
		        Cooking[playerid][pCookID3] = 0;
		    }
		    case 4:
		    {
		        strmid(Cooking[playerid][pCook4], string, 0, strlen(string), 255);
		        Cooking[playerid][pCWeight4] = 0;
		        Cooking[playerid][pCookID4] = 0;
		    }
		    case 5:
		    {
		        strmid(Cooking[playerid][pCook5], string, 0, strlen(string), 255);
		        Cooking[playerid][pCWeight5] = 0;
		        Cooking[playerid][pCookID5] = 0;
		    }
		}
	}
	return 1;
}

stock ClearGroceries(playerid)
{
	if(IsPlayerConnected(playerid))
	{
	    Groceries[playerid][pChickens] = 0; Groceries[playerid][pChicken] = 0;
	    Groceries[playerid][pHamburgers] = 0; Groceries[playerid][pHamburger] = 0;
	    Groceries[playerid][pPizzas] = 0; Groceries[playerid][pPizza] = 0;
	}
	return 1;
}

stock Lotto(number)
{
	new JackpotFallen = 0;
	new string[256];
	new winner[MAX_PLAYER_NAME];
	format(string, sizeof(string), "Lottery News: Today the Winning Number has fallen on: %d.", number);
    OOCOff(COLOR_WHITE, string);
    for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i))
		{
		    if(PlayerInfo[i][pLottoNr] > 0)
		    {
			    if(PlayerInfo[i][pLottoNr] == number)
			    {
			        JackpotFallen = 1;
			        GetPlayerName(i, winner, sizeof(winner));
					format(string, sizeof(string), "Lottery News: %s has won the Jackpot of $%d with his Lottery Ticket.", winner, Jackpot);
					OOCOff(COLOR_WHITE, string);
					format(string, sizeof(string), "* You have Won $%d with your Lottery Ticket.", Jackpot);
					SendClientMessage(i, COLOR_YELLOW, string);
					ConsumingMoney[i] = 1;
					GivePlayerMoney(i, Jackpot);
			    }
			    else
			    {
			        SendClientMessage(i, COLOR_LIGHTBLUE, "* You haven't won with your Lottery Ticket this time.");
			    }
			}
			PlayerInfo[i][pLottoNr] = 0;
		}
	}
	if(JackpotFallen)
	{
	    new rand = random(125000); rand += 15789;
	    Jackpot = rand;
	    SaveStuff();
	    format(string, sizeof(string), "Lottery News: The new Jackpot has been started with $%d.", Jackpot);
		OOCOff(COLOR_WHITE, string);
	}
	else
	{
	    new rand = random(15000); rand += 2158;
	    Jackpot += rand;
	    SaveStuff();
	    format(string, sizeof(string), "Lottery News: The Jackpot has been raised to $%d.", Jackpot);
		OOCOff(COLOR_WHITE, string);
	}
	return 1;
}

stock SetPlayerSpawn(playerid)
{
	if(IsPlayerConnected(playerid))
	{
	    if(PlayerInfo[playerid][pTut] == 0)
	    {
			gOoc[playerid] = 1; gNews[playerid] = 1; gFam[playerid] = 1;
			TogglePlayerControllable(playerid, 0);
			RegistrationStep[playerid] = 1;
			SendClientMessage(playerid, COLOR_YELLOW, "Welcome to Role Play - The Godfather server, please fill in some information to proceed.");
			SendClientMessage(playerid, COLOR_LIGHTRED, "Are you a Male or Female? (Type in what you are).");
	    }
		new rand;
		new house = PlayerInfo[playerid][pPhousekey];
		if(PlayerPaintballing[playerid] != 0)
		{
		    ResetPlayerWeapons(playerid);
      		GivePlayerWeapon(playerid, 29, 999);
		    rand = random(sizeof(PaintballSpawns));
			SetPlayerPos(playerid, PaintballSpawns[rand][0], PaintballSpawns[rand][1], PaintballSpawns[rand][2]);
		    return 1;
		}
		if(PlayerInfo[playerid][pJailed] == 1)
		{
		    SetPlayerInterior(playerid, 6);
			SetPlayerPos(playerid,264.6288,77.5742,1001.0391);
			SendClientMessage(playerid, COLOR_LIGHTRED, "Incomplete Jail Sentence, back to jail.");
			return 1;
		}
		if(PlayerInfo[playerid][pJailed] == 2)
		{
		    SetPlayerInterior(playerid, 0);
			SetPlayerPos(playerid,268.5777,1857.9351,9.8133);
			SetPlayerWorldBounds(playerid, 337.5694,101.5826,1940.9759,1798.7453); //285.3481,96.9720,1940.9755,1799.0811
			return 1;
		}
		if(MedicBill[playerid] == 1 && PlayerInfo[playerid][pJailed] == 0 && PlayerPaintballing[playerid] == 0)
		{
		    new string[256];
		    new cut = deathcost; //PlayerInfo[playerid][pLevel]*deathcost;
			GivePlayerMoney(playerid, -cut);
			format(string, sizeof(string), "DOC: Your Medical Bill comes to $%d, Have a nice day.", cut);
			SendClientMessage(playerid, TEAM_CYAN_COLOR, string);
			MedicBill[playerid] = 0;
			MedicTime[playerid] = 0;
			NeedMedicTime[playerid] = 0;
			PlayerInfo[playerid][pDeaths] += 1;
			SetPlayerHealth(playerid, 25.0);
		    /*SetPlayerInterior(playerid, 5);
	        rand = random(sizeof(gMedicSpawns));
			SetPlayerPos(playerid, gMedicSpawns[rand][0], gMedicSpawns[rand][1], gMedicSpawns[rand][2]); // Warp the player
			SetPlayerFacingAngle(playerid, 270.0);
	        TogglePlayerControllable(playerid, 0);
	        GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~y~You are recovering from your ~r~wounds~y~...", 35000, 3);
	        MedicTime[playerid] = 1;
	        if(PlayerInfo[playerid][pDonateRank] > 0)
	        {
	            NeedMedicTime[playerid] = 30;
	        }
	        else
	        {
	        	NeedMedicTime[playerid] = 60;
			}
	        PlayerPlaySound(playerid, 1062, 0.0, 0.0, 0.0);
		    return 1;*/
		}
		if(house !=255)
		{
		    if(SpawnChange[playerid]) //If 1, then you get to your house, else spawn somewhere else
		    {
				SetPlayerToTeamColor(playerid);
				SetPlayerInterior(playerid,HouseInfo[house][hInt]);
				SetPlayerPos(playerid, HouseInfo[house][hExitx], HouseInfo[house][hExity],HouseInfo[house][hExitz]); // Warp the player
				PlayerInfo[playerid][pLocal] = house;
				PlayerInfo[playerid][pInt] = HouseInfo[house][hInt];
				return 1;
			}
		}
		if(PlayerInfo[playerid][pLeader] == 7)//Mayor spawn
		{
		    SetPlayerToTeamColor(playerid);
		    SetPlayerInterior(playerid, 3);
		    SetPlayerPos(playerid, 356.2998,151.9914,1025.7891);
		    PlayerInfo[playerid][pInt] = 3;
			PlayerInfo[playerid][pLocal] = 241;
		    return 1;
		}
		if (PlayerInfo[playerid][pMember] == 1 || PlayerInfo[playerid][pMember] == 2 || PlayerInfo[playerid][pLeader] == 2 || PlayerInfo[playerid][pLeader] == 1)//Police Force spawn & FBI/ATF
		{
			SetPlayerToTeamColor(playerid);
		    rand = random(sizeof(gCopPlayerSpawns));
			SetPlayerPos(playerid, gCopPlayerSpawns[rand][0], gCopPlayerSpawns[rand][1], gCopPlayerSpawns[rand][2]); // Warp the player
			SetPlayerFacingAngle(playerid, 270.0);
			SetPlayerInterior(playerid,0);
			PlayerInfo[playerid][pInt] = 0;
			return 1;
	    }
		if (PlayerInfo[playerid][pMember] == 3 || PlayerInfo[playerid][pLeader] == 3)//National Guard spawn
		{
		    SetPlayerToTeamColor(playerid);
		    SetPlayerInterior(playerid, 0);
		    SetPlayerPos(playerid, -1346.2050,492.3983,11.2027);
		    PlayerInfo[playerid][pInt] = 0;
		    return 1;
		}
		if (PlayerInfo[playerid][pMember] == 4 || PlayerInfo[playerid][pLeader] == 4)//Fire/Ambulance spawn
		{
		    SetPlayerToTeamColor(playerid);
		    SetPlayerInterior(playerid, 0);
		    SetPlayerPos(playerid, -2656.0393,635.0596,14.4531);
		    PlayerInfo[playerid][pInt] = 0;
		    return 1;
		}
		if (PlayerInfo[playerid][pMember] == 5 || PlayerInfo[playerid][pLeader] == 5)//LaCosaNostra spawn
		{
		    SetPlayerToTeamColor(playerid);
		    SetPlayerInterior(playerid, 0);
		    SetPlayerPos(playerid, 1124.2415,-2037.1274,69.8847);
		    PlayerInfo[playerid][pInt] = 0;
		    return 1;
		}
		if (PlayerInfo[playerid][pMember] == 6 || PlayerInfo[playerid][pLeader] == 6)//Yakuza spawn
		{
		    SetPlayerToTeamColor(playerid);
		    SetPlayerInterior(playerid, 0);
		    SetPlayerPos(playerid, -2192.3020,646.8816,49.4375);
		    PlayerInfo[playerid][pInt] = 0;
		    return 1;
		}
	    if (PlayerInfo[playerid][pMember] == 8 || PlayerInfo[playerid][pLeader] == 8) //Hitman spawn
	    {
	        SetPlayerToTeamColor(playerid);
			SetPlayerPos(playerid, 1102.7017,-299.0774,73.9922);
			SetPlayerInterior(playerid,0);
			PlayerInfo[playerid][pInt] = 0;
	        return 1;
	    }
	    if (PlayerInfo[playerid][pMember] == 9 || PlayerInfo[playerid][pLeader] == 9) //News spawn
	    {
	        SetPlayerToTeamColor(playerid);
			SetPlayerPos(playerid, -2050.8962,460.0262,35.1719);
			SetPlayerInterior(playerid,0);
			PlayerInfo[playerid][pInt] = 0;
	        return 1;
	    }
	    if (PlayerInfo[playerid][pMember] == 10 || PlayerInfo[playerid][pLeader] == 10) //Taxi Cab Company spawn
	    {
	        SetPlayerToTeamColor(playerid);
			SetPlayerPos(playerid, -1978.5934,102.9237,27.6875);
			SetPlayerInterior(playerid,0);
			PlayerInfo[playerid][pInt] = 0;
	        return 1;
	    }
	    if(IsAnInstructor(playerid)) //Driving/Flying School spawn
	    {
			if(SchoolSpawn[playerid] == 0)
			{
		        SetPlayerToTeamColor(playerid);
				SetPlayerPos(playerid, -2032.6810,-117.4816,1035.1719);
				SetPlayerFacingAngle(playerid, 275.1114);
				SetPlayerInterior(playerid,3);
				PlayerInfo[playerid][pInt] = 3;
			}
			else if(SchoolSpawn[playerid] == 1)
			{
				SetPlayerToTeamColor(playerid);
				SetPlayerPos(playerid, 414.4144,2531.9580,19.1565);
				SetPlayerFacingAngle(playerid, 4.6505);
				SetPlayerInterior(playerid,0);
				PlayerInfo[playerid][pInt] = 0;
			}
	        return 1;
	    }
	    if ((gTeam[playerid]) == 1)
	    {
			SetPlayerToTeamColor(playerid);
			rand = random(sizeof(gMedPlayerSpawns));
			SetPlayerPos(playerid, gMedPlayerSpawns[rand][0], gMedPlayerSpawns[rand][1], gMedPlayerSpawns[rand][2]); // Warp the player
			SetPlayerFacingAngle(playerid, 270.0);
			SetPlayerInterior(playerid,0);
			PlayerInfo[playerid][pInt] = 0;
			return 1;
		}
		if(PlayerInfo[playerid][pFMember] != 255)
		{
		    new family = PlayerInfo[playerid][pFMember];
		    SetPlayerToTeamColor(playerid);
		    SetPlayerInterior(playerid, FamilyInfo[family][FamilyInterior]);
		    SetPlayerPos(playerid, FamilyInfo[family][FamilySpawn][0],FamilyInfo[family][FamilySpawn][1],FamilyInfo[family][FamilySpawn][2]);
		    SetPlayerFacingAngle(playerid, FamilyInfo[family][FamilySpawn][3]);
		    return 1;
		}
	    else
	    {
			SetPlayerToTeamColor(playerid);
			if(PlayerInfo[playerid][pOrigin] == 1)//USA
			{
			    SetPlayerPos(playerid,-2721.2612,-317.8447,7.8438);
				SetPlayerFacingAngle(playerid, 46.8583);
				SetPlayerInterior(playerid,0);
				PlayerInfo[playerid][pInt] = 0;
			}
			else if(PlayerInfo[playerid][pOrigin] == 2)//Europe
			{
			    SetPlayerPos(playerid,477.8121,-1499.7649,20.5001);
				SetPlayerFacingAngle(playerid, 262.9963);
				SetPlayerInterior(playerid,0);
				PlayerInfo[playerid][pInt] = 0;
			}
			else if(PlayerInfo[playerid][pOrigin] == 3)//Asia
			{
			    SetPlayerPos(playerid,-2155.4368,635.8173,52.3672);
				SetPlayerFacingAngle(playerid, 272.3543);
				SetPlayerInterior(playerid,0);
				PlayerInfo[playerid][pInt] = 0;
			}
			else
			{
				rand = random(sizeof(gRandomPlayerSpawns));
				SetPlayerPos(playerid, gRandomPlayerSpawns[rand][0], gRandomPlayerSpawns[rand][1], gRandomPlayerSpawns[rand][2]); // Warp the player
				SetPlayerFacingAngle(playerid, 270.0);
				SetPlayerInterior(playerid,15);
				PlayerInfo[playerid][pInt] = 15;
			}
			return 1;
		}
	}
	return 1;
}

stock CKLog(string[])
{
	new entry[256];
	format(entry, sizeof(entry), "%s\n",string);
	new File:hFile;
	hFile = fopen("ck.log", io_append);
	fwrite(hFile, entry);
	fclose(hFile);
}

stock PayLog(string[])
{
	new entry[256];
	format(entry, sizeof(entry), "%s\n",string);
	new File:hFile;
	hFile = fopen("pay.log", io_append);
	fwrite(hFile, entry);
	fclose(hFile);
}

stock KickLog(string[])
{
	new entry[256];
	format(entry, sizeof(entry), "%s\n",string);
	new File:hFile;
	hFile = fopen("kick.log", io_append);
	fwrite(hFile, entry);
	fclose(hFile);
}

stock BanLog(string[])
{
	new entry[256];
	format(entry, sizeof(entry), "%s\n",string);
	new File:hFile;
	hFile = fopen("ban.log", io_append);
	fwrite(hFile, entry);
	fclose(hFile);
}

stock SetAllPlayerCheckpoint(Float:allx, Float:ally, Float:allz, Float:radi, num)
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i))
		{
			SetPlayerCheckpoint(i,allx,ally,allz, radi);
			if (num != 255)
			{
				gPlayerCheckpointStatus[i] = num;
			}
		}
	}
}

stock SetAllCopCheckpoint(Float:allx, Float:ally, Float:allz, Float:radi)
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i))
		{
			if(gTeam[i] == 2)
			{
				SetPlayerCheckpoint(i,allx,ally,allz, radi);
			}
		}
	}
	return 1;
}

stock HireCost(carid)
{
	switch (carid)
	{
		case 69:
		{
			return 90000; //bullit
		}
		case 70:
		{
			return 130000; //infurnus
		}
		case 71:
		{
			return 100000; //turismo
		}
		case 72:
		{
			return 80000;
		}
		case 73:
		{
			return 70000;
		}
		case 74:
		{
			return 60000;
		}
	}
	return 0;
}

stock CarCheck()
{
	new string[256];
	for(new j = 0; j<MAX_PLAYERS; j++)
	{
	    if(IsPlayerConnected(j))
	    {
	        SetVehicleParamsForPlayer(99, j, 0, 0);
	        SetVehicleParamsForPlayer(100, j, 0, 0);
	        SetVehicleParamsForPlayer(101, j, 0, 0);
	        SetVehicleParamsForPlayer(102, j, 0, 0);
	        SetVehicleParamsForPlayer(103, j, 0, 0);
	        SetVehicleParamsForPlayer(104, j, 0, 0);
	        SetVehicleParamsForPlayer(105, j, 0, 0);
	        SetVehicleParamsForPlayer(106, j, 0, 0);
	        SetVehicleParamsForPlayer(107, j, 0, 0);
	        SetVehicleParamsForPlayer(108, j, 0, 0);
	        SetVehicleParamsForPlayer(109, j, 0, 0);
		    new Float:health;
		    GetPlayerHealth(j, health);
			SetPlayerHealth(j, health - 1.0);
			if(STDPlayer[j]==1)
			{
			    GetPlayerHealth(j, health);
			    SetPlayerHealth(j, health - 5.0);
			    SendClientMessage(j, COLOR_LIGHTBLUE, "* Lost 4 health due to STD.");
			}
			else if(STDPlayer[j]==2)
			{
			    GetPlayerHealth(j, health);
			    SetPlayerHealth(j, health - 12.0);
			    SendClientMessage(j, COLOR_LIGHTBLUE, "* Lost 8 health due to STD.");
			}
			else if(STDPlayer[j]==3)
			{
			    GetPlayerHealth(j, health);
			    SetPlayerHealth(j, health - 20.0);
			    SendClientMessage(j, COLOR_LIGHTBLUE, "* Lost 12 health due to STD.");
			}

			if(GetPlayerMoney(j) < 0)
			{
			    if(MoneyMessage[j]==0)
			    {
				    format(string, sizeof(string), "You are in debt, you have till next Time Check to get: $%d or you go to jail.", GetPlayerMoney(j));
					SendClientMessage(j, COLOR_LIGHTRED, string);
					MoneyMessage[j] = 1;
				}
			}
			else
			{
			    MoneyMessage[j] = 0;
			}
		}
	}
	for(new c = 1; c < 254; c++)
	{
		for(new i = 0; i < MAX_PLAYERS; i++)
		{
			if(IsPlayerConnected(i))
			{
				if (PlayerInfo[i][pJob] == 5)
				{
					SetVehicleParamsForPlayer(c, i, 0, 0);
				}
			}
		}
		if (gLastDriver[c] == 301)
		{
			CarRespawn(c);
		}
		if (gLastDriver[c] >= 300)
		{
			gLastDriver[c]++;
		}
		//foundowner = -1;
	}
	return 1;
}

stock CarInit()
{
	for(new c = 1; c < 254; c++)
	{
 		gLastDriver[c] = 299;
	}
	gLastDriver[301]=255;
	return 1;
}

stock CarTow(carid)
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i))
		{
			if(IsPlayerInVehicle(i, carid) || HireCar[i] == carid)
			{
				gLastDriver[carid] = 255;
				return 0;
			}
		}
	}
	SetVehiclePos(carid,HouseCarSpawns[carid-1][0], HouseCarSpawns[carid-1][1], HouseCarSpawns[carid-1][2]);
	SetVehicleZAngle(carid, HouseCarSpawns[carid-1][3]);
	return 1;
}

stock CarRespawn(carid)
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i))
		{
			if(IsPlayerInVehicle(i, carid) || HireCar[i] == carid)
			{
				gLastDriver[carid] = 255;
				return 0;
			}
		}
	}
	SetVehicleToRespawn(carid);
	gLastDriver[carid] = 299;
	return 1;
}

stock LockCar(carid)
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i))
		{
			SetVehicleParamsForPlayer(carid,i,0,1);
		}
	}
}

stock UnLockCar(carid)
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i))
		{
			if(!IsAPlane(carid))
			{
				SetVehicleParamsForPlayer(carid,i,0,0);
			}
		}
	}
}

stock InitLockDoors(playerid)
{
    if(IsPlayerConnected(playerid))
	{
		new c;
		while (c < 254)
		{
			c++;
			if (gCarLock[c] == 1)
			{
				SetVehicleParamsForPlayer(c,playerid,0,1);
			}
		}
	}
	return 1;
}

//---------------------------------------------------------

stock SetPlayerCriminal(playerid,declare,reason[])
{//example: SetPlayerCriminal(playerid,255, "Stealing A Police Vehicle");
	if(IsPlayerConnected(playerid))
	{
	    PlayerInfo[playerid][pCrimes] += 1;
	    new points = WantedPoints[playerid];
		new turned[MAX_PLAYER_NAME];
		new turner[MAX_PLAYER_NAME];
		new turnmes[128];
		new wantedmes[128];
		new wlevel;
		strmid(PlayerCrime[playerid][pAccusedof], reason, 0, strlen(reason), 255);
		GetPlayerName(playerid, turned, sizeof(turned));
		if (declare == 255)
		{
			format(turner, sizeof(turner), "Unknown");
			strmid(PlayerCrime[playerid][pVictim], turner, 0, strlen(turner), 255);
		}
		else
		{
		    if(IsPlayerConnected(declare))
		    {
				GetPlayerName(declare, turner, sizeof(turner));
				strmid(PlayerCrime[playerid][pVictim], turner, 0, strlen(turner), 255);
				strmid(PlayerCrime[declare][pBplayer], turned, 0, strlen(turned), 255);
				strmid(PlayerCrime[declare][pAccusing], reason, 0, strlen(reason), 255);
			}
		}
		format(turnmes, sizeof(turnmes), "You've commited a Crime ( %s ). Reporter: %s.",reason,turner);
		SendClientMessage(playerid, COLOR_LIGHTRED, turnmes);
		if(points > 0)
		{
		    new yesno;
			if(points == 3) { if(WantedLevel[playerid] != 1) { WantedLevel[playerid] = 1; wlevel = 1; yesno = 1; } }
			else if(points >= 4 && points <= 5) { if(WantedLevel[playerid] != 2) { WantedLevel[playerid] = 2; wlevel = 2; yesno = 1; } }
			else if(points >= 6 && points <= 7) { if(WantedLevel[playerid] != 3) { WantedLevel[playerid] = 3; wlevel = 3; yesno = 1; } }
			else if(points >= 8 && points <= 9) { if(WantedLevel[playerid] != 4) { WantedLevel[playerid] = 4; wlevel = 4; yesno = 1; } }
			else if(points >= 10 && points <= 11) { if(WantedLevel[playerid] != 5) { WantedLevel[playerid] = 5; wlevel = 5; yesno = 1; } }
			else if(points >= 12 && points <= 13) { if(WantedLevel[playerid] != 6) { WantedLevel[playerid] = 6; wlevel = 6; yesno = 1; } }
			else if(points >= 14) { if(WantedLevel[playerid] != 10) { WantedLevel[playerid] = 10; wlevel = 10; yesno = 1; } }
			if(WantedLevel[playerid] >= 1) { if(gTeam[playerid] == 3) { gTeam[playerid] = 4; } }
			if(yesno)
			{
				format(wantedmes, sizeof(wantedmes), "Current Wanted Level: %d", wlevel);
				SendClientMessage(playerid, COLOR_YELLOW, wantedmes);
				for(new i = 0; i < MAX_PLAYERS; i++)
				{
					if(IsPlayerConnected(i))
					{
					    if(PlayerInfo[i][pMember] == 1||PlayerInfo[i][pLeader] == 1)
					    {
							format(cbjstore, sizeof(turnmes), "HQ: All Units APB: Reporter: %s",turner);
							SendClientMessage(i, TEAM_BLUE_COLOR, cbjstore);
							format(cbjstore, sizeof(turnmes), "HQ: Crime: %s, Suspect: %s",reason,turned);
							SendClientMessage(i, TEAM_BLUE_COLOR, cbjstore);
						}
					}
				}
			}
		}
	}//not connected
}
//---------------------------------------------------------

stock SetPlayerFree(playerid,declare,reason[])
{
	if(IsPlayerConnected(playerid))
	{
		ClearCrime(playerid);
		new turned[MAX_PLAYER_NAME];
		new turner[MAX_PLAYER_NAME];
		new turnmes[128];
		new crbjstore[128];
		if (declare == 255)
		{
			format(turner, sizeof(turner), "911");
		}
		else
		{
		    if(IsPlayerConnected(declare))
		    {
				GetPlayerName(declare, turner, sizeof(turner));
			}
		}
		GetPlayerName(playerid, turned, sizeof(turned));
		format(turnmes, sizeof(turnmes), "SMS: %s, Because you %s, you are no longer a Criminal, Sender: MOLE (555)",turned,reason);
		RingTone[playerid] = 20;
		SendClientMessage(playerid, COLOR_YELLOW, turnmes);
		for(new i = 0; i < MAX_PLAYERS; i++)
		{
			if(IsPlayerConnected(i))
			{
			    if(PlayerInfo[i][pMember] == 1||PlayerInfo[i][pLeader] == 1)
			    {
					format(crbjstore, sizeof(crbjstore), "HQ: All Units Officer %s Has Completed Assignment",turner);
					SendClientMessage(i, COLOR_DBLUE, crbjstore);
					format(crbjstore, sizeof(crbjstore), "HQ: %s Has Been Processed, %s",turned,reason);
					SendClientMessage(i, COLOR_DBLUE, crbjstore);
				}
			}
		}
	}
}

stock SetPlayerWeapons(playerid)
{
	if(IsPlayerConnected(playerid))
	{
	    ResetPlayerWeapons(playerid);
	    if(PlayerInfo[playerid][pJailed] < 1)
	    {
			if(gTeam[playerid] == 2 || IsACop(playerid))
			{
				GivePlayerWeapon(playerid, 41, 500); //spray
				if(OnDuty[playerid] == 1 || PlayerInfo[playerid][pMember] == 2)//Cops & FBI/ATF
				{
				    GivePlayerWeapon(playerid, 41, 500); //spray
					GivePlayerWeapon(playerid, 24, 200);
					GivePlayerWeapon(playerid, 3, 1);
					if(PlayerInfo[playerid][pChar] == 285)//SWAT
					{
					    GivePlayerWeapon(playerid, 25, 100);
					    GivePlayerWeapon(playerid, 29, 450);
					}
					else if(PlayerInfo[playerid][pChar] == 287)//Army
					{
					    GivePlayerWeapon(playerid, 25, 100);
					    GivePlayerWeapon(playerid, 31, 500);
					}
				}
				if(PlayerInfo[playerid][pMember] == 3 || PlayerInfo[playerid][pLeader] == 3)//National Guard
				{
				    GivePlayerWeapon(playerid, 24, 200);
				    GivePlayerWeapon(playerid, 31, 600);
				    GivePlayerWeapon(playerid, 29, 600);
				}
			}
			if(gTeam[playerid] >= 3)
			{
				GivePlayerWeapon(playerid, 5, 0);
			}
			if(PlayerInfo[playerid][pDonateRank] > 0)
			{
				if (PlayerInfo[playerid][pGun1] > 0)
				{
					GivePlayerWeapon(playerid, PlayerInfo[playerid][pGun1], PlayerInfo[playerid][pAmmo1]);
					PlayerInfo[playerid][pGun1] = 0; PlayerInfo[playerid][pAmmo1] = 0;
				}
				if (PlayerInfo[playerid][pGun2] > 0)
				{
					GivePlayerWeapon(playerid, PlayerInfo[playerid][pGun2], PlayerInfo[playerid][pAmmo2]);
					PlayerInfo[playerid][pGun2] = 0; PlayerInfo[playerid][pAmmo2] = 0;
				}
				if (PlayerInfo[playerid][pGun3] > 0)
				{
					GivePlayerWeapon(playerid, PlayerInfo[playerid][pGun3], PlayerInfo[playerid][pAmmo3]);
					PlayerInfo[playerid][pGun3] = 0; PlayerInfo[playerid][pAmmo3] = 0;
				}
				if (PlayerInfo[playerid][pGun4] > 0)
				{
					GivePlayerWeapon(playerid, PlayerInfo[playerid][pGun4], PlayerInfo[playerid][pAmmo4]);
					PlayerInfo[playerid][pGun4] = 0; PlayerInfo[playerid][pAmmo4] = 0;
				}
			}
			else
			{
			    if (PlayerInfo[playerid][pGun1] > 0)
				{
					GivePlayerWeapon(playerid, PlayerInfo[playerid][pGun1], PlayerInfo[playerid][pAmmo1]);
					PlayerInfo[playerid][pGun1] = 0; PlayerInfo[playerid][pAmmo1] = 0;
				}
				if (PlayerInfo[playerid][pGun2] > 0)
				{
					GivePlayerWeapon(playerid, PlayerInfo[playerid][pGun2], PlayerInfo[playerid][pAmmo2]);
					PlayerInfo[playerid][pGun2] = 0; PlayerInfo[playerid][pAmmo2] = 0;
				}
			}
		}
	}
}

stock PrintSBizInfo(playerid,targetid)
{
	if(IsPlayerConnected(playerid))
	{
		new coordsstring[256];
		SendClientMessage(playerid, COLOR_GREEN,"_______________________________________");
		format(coordsstring, sizeof(coordsstring),"*** %s ***",SBizzInfo[targetid][sbMessage]);
		SendClientMessage(playerid, COLOR_WHITE,coordsstring);
		format(coordsstring, sizeof(coordsstring), "Locked: %d EntryFee: $%d Till: $%d", SBizzInfo[targetid][sbLocked], SBizzInfo[targetid][sbEntranceCost], SBizzInfo[targetid][sbTill]);
		SendClientMessage(playerid, COLOR_GRAD1,coordsstring);
		format(coordsstring, sizeof(coordsstring), "Products: %d/%d Extortion By: %s", SBizzInfo[targetid][sbProducts],SBizzInfo[targetid][sbMaxProducts],SBizzInfo[targetid][sbExtortion]);
		SendClientMessage(playerid, COLOR_GRAD2,coordsstring);
		SendClientMessage(playerid, COLOR_GREEN,"_______________________________________");
	}
}

stock PrintBizInfo(playerid,targetid)
{
    if(IsPlayerConnected(playerid))
	{
		new coordsstring[256];
		SendClientMessage(playerid, COLOR_GREEN,"_______________________________________");
		format(coordsstring, sizeof(coordsstring),"*** %s ***",BizzInfo[targetid][bMessage]);
		SendClientMessage(playerid, COLOR_WHITE,coordsstring);
		format(coordsstring, sizeof(coordsstring), "Locked: %d EntryFee: $%d Till: $%d", BizzInfo[targetid][bLocked], BizzInfo[targetid][bEntranceCost], BizzInfo[targetid][bTill]);
		SendClientMessage(playerid, COLOR_GRAD1,coordsstring);
		format(coordsstring, sizeof(coordsstring), "Products: %d/%d Extortion By: %s", BizzInfo[targetid][bProducts],BizzInfo[targetid][bMaxProducts],BizzInfo[targetid][bExtortion]);
		SendClientMessage(playerid, COLOR_GRAD2,coordsstring);
		SendClientMessage(playerid, COLOR_GREEN,"_______________________________________");
	}
}

stock ShowStats(playerid,targetid)
{
    if(IsPlayerConnected(playerid)&&IsPlayerConnected(targetid))
	{
		new cash =  GetPlayerMoney(targetid);
		new atext[20];
		if(PlayerInfo[targetid][pSex] == 1) { atext = "Male"; }
		else if(PlayerInfo[targetid][pSex] == 2) { atext = "Female"; }
  		new otext[20];
		if(PlayerInfo[targetid][pOrigin] == 1) { otext = "USA"; }
		else if(PlayerInfo[targetid][pOrigin] == 2) { otext = "Europe"; }
		else if(PlayerInfo[targetid][pOrigin] == 3) { otext = "Asia"; }
		new ttext[20];
		if(PlayerInfo[targetid][pMember] == 4 || PlayerInfo[targetid][pLeader] == 4) { ttext = "Medic"; }
		else if(gTeam[targetid] == 3 || gTeam[targetid] == 4) { ttext = "Civilian"; }
		else if(PlayerInfo[targetid][pMember] == 1 || PlayerInfo[targetid][pLeader] == 1) { ttext = "Officer"; }
		else if(PlayerInfo[targetid][pMember] == 2 || PlayerInfo[targetid][pLeader] == 2) { ttext = "FBI Agent"; }
		else if(PlayerInfo[targetid][pMember] == 3 || PlayerInfo[targetid][pLeader] == 3) { ttext = "National Guard"; }
		else if(PlayerInfo[targetid][pMember] == 4 || PlayerInfo[targetid][pLeader] == 4) { ttext = "Firemen/Paramedic"; }
		else if(PlayerInfo[targetid][pMember] == 5 || PlayerInfo[targetid][pLeader] == 5) { ttext = "LCN"; }
		else if(PlayerInfo[targetid][pMember] == 6 || PlayerInfo[targetid][pLeader] == 6) { ttext = "Yakuza"; }
		else if(PlayerInfo[targetid][pMember] == 8 || PlayerInfo[targetid][pLeader] == 8) { ttext = "Hitmen"; }
		else if(PlayerInfo[targetid][pMember] == 9 || PlayerInfo[targetid][pLeader] == 9) { ttext = "News Reporter"; }
		else if(PlayerInfo[targetid][pMember] == 10 || PlayerInfo[targetid][pLeader] == 10) { ttext = "Taxi"; }
		else if(PlayerInfo[targetid][pMember] == 11 || PlayerInfo[targetid][pLeader] == 11) { ttext = "School Instructor"; }
		new dtext[20];
		if(STDPlayer[targetid] == 1) { dtext = "Chlamydia"; }
		else if(STDPlayer[targetid] == 2) { dtext = "Gonorrhea"; }
		else if(STDPlayer[targetid] == 3) { dtext = "Syphilis"; }
		else { dtext = "None"; }
	    new ftext[20];
	    if(PlayerInfo[targetid][pMember] == 4 || PlayerInfo[targetid][pLeader] == 4)
		{ ftext = "Firemen/Paramedics"; }
  		else if(PlayerInfo[targetid][pMember] == 5 || PlayerInfo[targetid][pLeader] == 5)
		{ ftext = "La Cosa Nostra"; }
		else if(PlayerInfo[targetid][pMember] == 6 || PlayerInfo[targetid][pLeader] == 6)
		{ ftext = "Yakuza"; }
		else if(PlayerInfo[targetid][pMember] == 11 || PlayerInfo[targetid][pLeader] == 11)
		{ ftext = "License Faction"; }
		else
		{ ftext = "None"; }
		new f2text[20];
	    if(PlayerInfo[targetid][pFMember] < 255) { f2text = FamilyInfo[PlayerInfo[targetid][pFMember]][FamilyName]; }
		else { f2text = "None"; }
	    new rtext[64];
	    if(gTeam[targetid] == 5 || PlayerInfo[targetid][pFMember] < 255)//The 2 Organisations
	    {
        	if(PlayerInfo[targetid][pRank] == 1) { rtext = "Outsider"; }
			else if(PlayerInfo[targetid][pRank] == 2) { rtext = "Associate"; }
			else if(PlayerInfo[targetid][pRank] == 3) { rtext = "Soldier"; }
			else if(PlayerInfo[targetid][pRank] == 4) { rtext = "Capo"; }
			else if(PlayerInfo[targetid][pRank] == 5) { rtext = "Underboss"; }
  			else if(PlayerInfo[targetid][pRank] == 6) { rtext = "Godfather"; }
			else { rtext = "Outsider"; }
		}
		else if(PlayerInfo[targetid][pMember] == 1 || PlayerInfo[targetid][pLeader] == 1)//PD Ranks
		{
		    if(PlayerInfo[targetid][pRank] == 1) { rtext = "Cadet"; }
			else if(PlayerInfo[targetid][pRank] == 2) { rtext = "Officer"; }
			else if(PlayerInfo[targetid][pRank] == 3) { rtext = "Sergeant"; }
			else if(PlayerInfo[targetid][pRank] == 4) { rtext = "Lieutenant"; }
			else if(PlayerInfo[targetid][pRank] == 5) { rtext = "Captain"; }
	        else if(PlayerInfo[targetid][pRank] == 6) { rtext = "Chief"; }
			else { rtext = "Cadet"; }
		}
		else if(PlayerInfo[targetid][pMember] == 2 || PlayerInfo[targetid][pLeader] == 2)//FBI Ranks
		{
		    if(PlayerInfo[targetid][pRank] == 1) { rtext = "Professional Staff"; }
			else if(PlayerInfo[targetid][pRank] == 2) { rtext = "Special Agent Trainee"; }
			else if(PlayerInfo[targetid][pRank] == 3) { rtext = "Special Agent"; }
			else if(PlayerInfo[targetid][pRank] == 4) { rtext = "Special Agent in Charge"; }
			else if(PlayerInfo[targetid][pRank] == 5) { rtext = "Assistant Director in Charge"; }
		    else if(PlayerInfo[targetid][pRank] == 6) { rtext = "Director"; }
			else { rtext = "Intern"; }
		}
		else if(PlayerInfo[targetid][pMember] == 3 || PlayerInfo[targetid][pLeader] == 3)//NG Ranks
		{
		    if(PlayerInfo[targetid][pRank] == 1) { rtext = "Private"; }
			else if(PlayerInfo[targetid][pRank] == 2) { rtext = "Sergeant"; }
			else if(PlayerInfo[targetid][pRank] == 3) { rtext = "Major"; }
			else if(PlayerInfo[targetid][pRank] == 4) { rtext = "Captain"; }
			else if(PlayerInfo[targetid][pRank] == 5) { rtext = "Lieutenant"; }
		    else if(PlayerInfo[targetid][pRank] == 6) { rtext = "General"; }
			else { rtext = "Private"; }
		}
		else if(PlayerInfo[targetid][pMember] == 8 || PlayerInfo[targetid][pLeader] == 8)//Hitman Ranks
		{
		    if(PlayerInfo[targetid][pRank] == 1) { rtext = "Freelancer"; }
			else if(PlayerInfo[targetid][pRank] == 2) { rtext = "Marksman"; }
			else if(PlayerInfo[targetid][pRank] == 3) { rtext = "Agent"; }
			else if(PlayerInfo[targetid][pRank] == 4) { rtext = "Special Agent"; }
			else if(PlayerInfo[targetid][pRank] == 5) { rtext = "Vice-Director"; }
		    else if(PlayerInfo[targetid][pRank] == 6) { rtext = "Director"; }
			else { rtext = "Freelancer"; }
		}
		else if(PlayerInfo[targetid][pMember] == 9 || PlayerInfo[targetid][pLeader] == 9)//NR Ranks
		{
		    if(PlayerInfo[targetid][pRank] == 1) { rtext = "Intern"; }
			else if(PlayerInfo[targetid][pRank] == 2) { rtext = "Local Reporter"; }
			else if(PlayerInfo[targetid][pRank] == 3) { rtext = "Local Editor"; }
			else if(PlayerInfo[targetid][pRank] == 4) { rtext = "Network Anchor"; }
			else if(PlayerInfo[targetid][pRank] == 5) { rtext = "Network Editor"; }
		    else if(PlayerInfo[targetid][pRank] == 6) { rtext = "Network Producer"; }
			else { rtext = "Intern"; }
		}
		else if(PlayerInfo[targetid][pMember] == 10 || PlayerInfo[targetid][pLeader] == 10)//Taxi Company Ranks
		{
		    if(PlayerInfo[targetid][pRank] == 1) { rtext = "Trainee"; }
			else if(PlayerInfo[targetid][pRank] == 2) { rtext = "Taxi Rookie"; }
			else if(PlayerInfo[targetid][pRank] == 3) { rtext = "Cabbie"; }
			else if(PlayerInfo[targetid][pRank] == 4) { rtext = "Dispatcher"; }
			else if(PlayerInfo[targetid][pRank] == 5) { rtext = "Shift Supervisor"; }
		    else if(PlayerInfo[targetid][pRank] == 6) { rtext = "Taxi Company Owner"; }
			else { rtext = "Trainee"; }
		}
		else if(IsAnInstructor(targetid))//Driving/Flying School Ranks
		{
		    if(PlayerInfo[targetid][pRank] == 1) { rtext = "Trainee"; }
			else if(PlayerInfo[targetid][pRank] == 2) { rtext = "Instructor"; }
			else if(PlayerInfo[targetid][pRank] == 3) { rtext = "Senior Instructor"; }
			else if(PlayerInfo[targetid][pRank] == 4) { rtext = "Manager"; }
			else if(PlayerInfo[targetid][pRank] == 5) { rtext = "Under Boss"; }
		    else if(PlayerInfo[targetid][pRank] == 6) { rtext = "Boss"; }
			else { rtext = "Trainee"; }
		}
		else
		{
		    rtext = "None";
		}
        new jtext[20];
        if(PlayerInfo[targetid][pJob] == 1) { jtext = "Detective"; }
        else if(PlayerInfo[targetid][pJob] == 2) { jtext = "Lawyer"; }
        else if(PlayerInfo[targetid][pJob] == 3) { jtext = "Whore"; }
        else if(PlayerInfo[targetid][pJob] == 4) { jtext = "Drugs Dealer"; }
        else if(PlayerInfo[targetid][pJob] == 5) { jtext = "Car Jacker"; }
        else if(PlayerInfo[targetid][pJob] == 6) { jtext = "News Reporter"; }
        else if(PlayerInfo[targetid][pJob] == 7) { jtext = "Car Mechanic"; }
        else if(PlayerInfo[targetid][pJob] == 8) { jtext = "Bodyguard"; }
        else if(PlayerInfo[targetid][pJob] == 9) { jtext = "Arms Dealer"; }
        else if(PlayerInfo[targetid][pJob] == 10) { jtext = "Car Dealer"; }
		else if(PlayerInfo[targetid][pJob] == 12) { jtext = "Boxer"; }
        else if(PlayerInfo[targetid][pJob] == 14) { jtext = "Bus Driver"; }
        else if(PlayerInfo[targetid][pJob] == 15) { jtext = "Paper Boy"; }
        else if(PlayerInfo[targetid][pJob] == 16) { jtext = "Trucker"; }
        else { jtext = "None"; }
		new drank[20];
		if(PlayerInfo[targetid][pDonateRank] == 1) { drank = "Power User"; }
		else if(PlayerInfo[targetid][pDonateRank] >= 2) { drank = "Donater"; }
		else { drank = "None"; }
		new married[20];
		strmid(married, PlayerInfo[targetid][pMarriedTo], 0, strlen(PlayerInfo[targetid][pMarriedTo]), 255);
		new age = PlayerInfo[targetid][pAge];
		new ptime = PlayerInfo[targetid][pConnectTime];
		new lotto = PlayerInfo[targetid][pLottoNr];
		new deaths = PlayerInfo[targetid][pDeaths];
		new fishes = PlayerInfo[targetid][pFishes];
		new bigfish = PlayerInfo[targetid][pBiggestFish];
		new crimes = PlayerInfo[targetid][pCrimes];
		new arrests = PlayerInfo[targetid][pArrested];
		new warrests = PlayerInfo[targetid][pWantedDeaths];
		new drugs = PlayerInfo[targetid][pDrugs];
		new mats = PlayerInfo[targetid][pMats];
		new wanted = WantedLevel[targetid];
		new level = PlayerInfo[targetid][pLevel];
		new exp = PlayerInfo[targetid][pExp];
		new kills = PlayerInfo[targetid][pKills];
		new pnumber = PlayerInfo[targetid][pPnumber];
		new account = PlayerInfo[targetid][pAccount];
		new nxtlevel = PlayerInfo[targetid][pLevel]+1;
		new expamount = nxtlevel*levelexp;
		new costlevel = nxtlevel*levelcost;//10k for testing purposes
		new housekey = PlayerInfo[targetid][pPhousekey];
		new bizkey = PlayerInfo[targetid][pPbiskey];
		new intir = PlayerInfo[targetid][pInt];
		new local = PlayerInfo[targetid][pLocal];
		new Float:shealth = PlayerInfo[targetid][pSHealth];
		new Float:health;
		new name[MAX_PLAYER_NAME];
		GetPlayerName(targetid, name, sizeof(name));
		GetPlayerHealth(targetid,health);
		new Float:px,Float:py,Float:pz;
		GetPlayerPos(targetid, px, py, pz);
		new coordsstring[256];
		SendClientMessage(playerid, COLOR_GREEN,"_______________________________________");
		format(coordsstring, sizeof(coordsstring),"*** %s ***",name);
		SendClientMessage(playerid, COLOR_WHITE,coordsstring);
		format(coordsstring, sizeof(coordsstring), "Level:[%d] Sex:[%s] Age:[%d] Origin:[%s] SpawnHealth:[%.1f] Cash:[$%d] Bank:[$%d] Ph:[%d]", level,atext,age,otext,shealth+50, cash, account, pnumber);
		SendClientMessage(playerid, COLOR_GRAD1,coordsstring);
		format(coordsstring, sizeof(coordsstring), "DonateRank:[%s] MarriedTo:[%s] PlayingHours:[%d] LottoNr:[%d] Job:[%s]", drank,married,ptime,lotto,jtext);
		SendClientMessage(playerid, COLOR_GRAD3,coordsstring);
		format(coordsstring, sizeof(coordsstring), "FishesCaught:[%d] BiggestFish:[%d] CrimesCommited:[%d] TimesArrested:[%d] WantedDeaths:[%d]", fishes,bigfish,crimes,arrests,warrests );
		SendClientMessage(playerid, COLOR_GRAD4,coordsstring);
		format(coordsstring, sizeof(coordsstring), "Kills:[%d] Deaths:[%d] NextLevel:[$%d] Respect:[%d/%d] WantedLevel:[%d] Family:[%s]",kills,deaths,costlevel,exp,expamount,wanted,f2text);
		SendClientMessage(playerid, COLOR_GRAD5,coordsstring);
		format(coordsstring, sizeof(coordsstring), "Drugs:[%d] Materials:[%d] Team:[%s] Disease:[%s] Organisation:[%s] Rank:[%s]",drugs,mats,ttext,dtext,ftext,rtext);
		SendClientMessage(playerid, COLOR_GRAD5,coordsstring);
		if (PlayerInfo[playerid][pAdmin] >= 1)
		{
			format(coordsstring, sizeof(coordsstring), "House key [%d] Business key [%d] HireKey [%d] int:[%d] local[%d]", housekey,bizkey,HireCar[targetid],intir,local);
			SendClientMessage(playerid, COLOR_GRAD6,coordsstring);
		}
		SendClientMessage(playerid, COLOR_GREEN,"_______________________________________");
	}
}
//---------------------------------------------------------

stock SetPlayerToTeamColor(playerid)
{
	if(IsPlayerConnected(playerid))
	{
	    SetPlayerColor(playerid,TEAM_HIT_COLOR); // white
	}
}

stock SaveMission(playerid,name[])
{
	if(IsPlayerConnected(playerid))
	{
	    new coordsstring[256];
	    new missionname[64];
		new var[128];
		new makername[MAX_PLAYER_NAME];
		GetPlayerName(playerid, makername, sizeof(makername));
		new rand = random(999);
		if(rand == 0) { rand = 1; }
		new number = rand;
		if(MissionInfo[mToggle] == 0 || MissionInfo[mToggle] == 1) { }
		else { MissionInfo[mToggle] = 1; }
		format(missionname, sizeof(missionname), "%s.mis",name);
		new File: hFile = fopen(missionname, io_write);
		format(var, 128, "Title=%s\n", MissionInfo[mTitle]);fwrite(hFile, var);
		format(var, 128, "Maker=%s\n", makername);fwrite(hFile, var);
		format(var, 128, "Text1=%s\n", MissionInfo[mText1]);fwrite(hFile, var);
		format(var, 128, "Text2=%s\n", MissionInfo[mText2]);fwrite(hFile, var);
		format(var, 128, "Text3=%s\n", MissionInfo[mText3]);fwrite(hFile, var);
		format(var, 128, "Text4=%s\n", MissionInfo[mText4]);fwrite(hFile, var);
		format(var, 128, "Text5=%s\n", MissionInfo[mText5]);fwrite(hFile, var);
		format(var, 128, "Text6=%s\n", MissionInfo[mText6]);fwrite(hFile, var);
		format(var, 128, "Text7=%s\n", MissionInfo[mText7]);fwrite(hFile, var);
		format(var, 128, "Text8=%s\n", MissionInfo[mText8]);fwrite(hFile, var);
		format(var, 128, "Text9=%s\n", MissionInfo[mText9]);fwrite(hFile, var);
		format(var, 128, "Text10=%s\n", MissionInfo[mText10]);fwrite(hFile, var);
		format(var, 128, "Text11=%s\n", MissionInfo[mText11]);fwrite(hFile, var);
		format(var, 128, "Text12=%s\n", MissionInfo[mText12]);fwrite(hFile, var);
		format(var, 128, "Text13=%s\n", MissionInfo[mText13]);fwrite(hFile, var);
		format(var, 128, "Text14=%s\n", MissionInfo[mText14]);fwrite(hFile, var);
		format(var, 128, "Text15=%s\n", MissionInfo[mText15]);fwrite(hFile, var);
		format(var, 128, "Text16=%s\n", MissionInfo[mText16]);fwrite(hFile, var);
		format(var, 128, "Text17=%s\n", MissionInfo[mText17]);fwrite(hFile, var);
		format(var, 128, "Text18=%s\n", MissionInfo[mText18]);fwrite(hFile, var);
		format(var, 128, "GText1=%s\n", MissionInfo[mGText1]);fwrite(hFile, var);
		format(var, 128, "GText2=%s\n", MissionInfo[mGText2]);fwrite(hFile, var);
		format(var, 128, "GText3=%s\n", MissionInfo[mGText3]);fwrite(hFile, var);
		format(var, 128, "GText4=%s\n", MissionInfo[mGText4]);fwrite(hFile, var);
		format(var, 128, "GText5=%s\n", MissionInfo[mGText5]);fwrite(hFile, var);
		format(var, 128, "GText6=%s\n", MissionInfo[mGText6]);fwrite(hFile, var);
		format(var, 128, "CP1X=%f\n", MissionInfo[mCP1][0]);fwrite(hFile, var);
		format(var, 128, "CP1Y=%f\n", MissionInfo[mCP1][1]);fwrite(hFile, var);
		format(var, 128, "CP1Z=%f\n", MissionInfo[mCP1][2]);fwrite(hFile, var);
		format(var, 128, "CP2X=%f\n", MissionInfo[mCP2][0]);fwrite(hFile, var);
		format(var, 128, "CP2Y=%f\n", MissionInfo[mCP2][1]);fwrite(hFile, var);
		format(var, 128, "CP2Z=%f\n", MissionInfo[mCP2][2]);fwrite(hFile, var);
		format(var, 128, "CP3X=%f\n", MissionInfo[mCP3][0]);fwrite(hFile, var);
		format(var, 128, "CP3Y=%f\n", MissionInfo[mCP3][1]);fwrite(hFile, var);
		format(var, 128, "CP3Z=%f\n", MissionInfo[mCP3][2]);fwrite(hFile, var);
		format(var, 128, "CP4X=%f\n", MissionInfo[mCP4][0]);fwrite(hFile, var);
		format(var, 128, "CP4Y=%f\n", MissionInfo[mCP4][1]);fwrite(hFile, var);
		format(var, 128, "CP4Z=%f\n", MissionInfo[mCP4][2]);fwrite(hFile, var);
		format(var, 128, "CP5X=%f\n", MissionInfo[mCP5][0]);fwrite(hFile, var);
		format(var, 128, "CP5Y=%f\n", MissionInfo[mCP5][1]);fwrite(hFile, var);
		format(var, 128, "CP5Z=%f\n", MissionInfo[mCP5][2]);fwrite(hFile, var);
		format(var, 128, "CP6X=%f\n", MissionInfo[mCP6][0]);fwrite(hFile, var);
		format(var, 128, "CP6Y=%f\n", MissionInfo[mCP6][1]);fwrite(hFile, var);
		format(var, 128, "CP6Z=%f\n", MissionInfo[mCP6][2]);fwrite(hFile, var);
		format(var, 128, "Number=%d\n", number);fwrite(hFile, var);
		format(var, 128, "Reward=%d\n", MissionInfo[mReward]);fwrite(hFile, var);
		format(var, 128, "Toggle=%d\n", MissionInfo[mToggle]);fwrite(hFile, var);
		fclose(hFile);
		format(coordsstring, sizeof(coordsstring), "%s Mission Saved.",name);
		SendClientMessage(playerid, COLOR_GREEN,coordsstring);
	}
	return 1;
}

stock LoadMission(playerid,name[])
{
	if(IsPlayerConnected(playerid))
	{
		new strFromFile2[128];
		new missionname[64];
		format(missionname, sizeof(missionname), "%s.mis",name);
		new File: file = fopen(missionname, io_read);
		if (file)
		{
		    new key[ 256 ] , val[ 256 ];
		    new Data[ 256 ];
		    while ( fread( file , Data , sizeof( Data ) ) )
			{
				key = ini_GetKey( Data );
				if( strcmp( key , "Title" , true ) == 0 ) { val = ini_GetValue( Data ); strmid(PlayMission[kTitle], val, 0, strlen(val), 255); }
				if( strcmp( key , "Maker" , true ) == 0 ) { val = ini_GetValue( Data ); strmid(PlayMission[kMaker], val, 0, strlen(val), 255); }
				if( strcmp( key , "Text1" , true ) == 0 ) { val = ini_GetValue( Data ); strmid(PlayMission[kText1], val, 0, strlen(val), 255); }
				if( strcmp( key , "Text2" , true ) == 0 ) { val = ini_GetValue( Data ); strmid(PlayMission[kText2], val, 0, strlen(val), 255); }
				if( strcmp( key , "Text3" , true ) == 0 ) { val = ini_GetValue( Data ); strmid(PlayMission[kText3], val, 0, strlen(val), 255); }
				if( strcmp( key , "Text4" , true ) == 0 ) { val = ini_GetValue( Data ); strmid(PlayMission[kText4], val, 0, strlen(val), 255); }
				if( strcmp( key , "Text5" , true ) == 0 ) { val = ini_GetValue( Data ); strmid(PlayMission[kText5], val, 0, strlen(val), 255); }
				if( strcmp( key , "Text6" , true ) == 0 ) { val = ini_GetValue( Data ); strmid(PlayMission[kText6], val, 0, strlen(val), 255); }
				if( strcmp( key , "Text7" , true ) == 0 ) { val = ini_GetValue( Data ); strmid(PlayMission[kText7], val, 0, strlen(val), 255); }
				if( strcmp( key , "Text8" , true ) == 0 ) { val = ini_GetValue( Data ); strmid(PlayMission[kText8], val, 0, strlen(val), 255); }
				if( strcmp( key , "Text9" , true ) == 0 ) { val = ini_GetValue( Data ); strmid(PlayMission[kText9], val, 0, strlen(val), 255); }
				if( strcmp( key , "Text10" , true ) == 0 ) { val = ini_GetValue( Data ); strmid(PlayMission[kText10], val, 0, strlen(val), 255); }
				if( strcmp( key , "Text11" , true ) == 0 ) { val = ini_GetValue( Data ); strmid(PlayMission[kText11], val, 0, strlen(val), 255); }
				if( strcmp( key , "Text12" , true ) == 0 ) { val = ini_GetValue( Data ); strmid(PlayMission[kText12], val, 0, strlen(val), 255); }
				if( strcmp( key , "Text13" , true ) == 0 ) { val = ini_GetValue( Data ); strmid(PlayMission[kText13], val, 0, strlen(val), 255); }
				if( strcmp( key , "Text14" , true ) == 0 ) { val = ini_GetValue( Data ); strmid(PlayMission[kText14], val, 0, strlen(val), 255); }
				if( strcmp( key , "Text15" , true ) == 0 ) { val = ini_GetValue( Data ); strmid(PlayMission[kText15], val, 0, strlen(val), 255); }
				if( strcmp( key , "Text16" , true ) == 0 ) { val = ini_GetValue( Data ); strmid(PlayMission[kText16], val, 0, strlen(val), 255); }
				if( strcmp( key , "Text17" , true ) == 0 ) { val = ini_GetValue( Data ); strmid(PlayMission[kText17], val, 0, strlen(val), 255); }
				if( strcmp( key , "Text18" , true ) == 0 ) { val = ini_GetValue( Data ); strmid(PlayMission[kText18], val, 0, strlen(val), 255); }
				if( strcmp( key , "GText1" , true ) == 0 ) { val = ini_GetValue( Data ); strmid(PlayMission[kGText1], val, 0, strlen(val), 255); }
				if( strcmp( key , "GText2" , true ) == 0 ) { val = ini_GetValue( Data ); strmid(PlayMission[kGText2], val, 0, strlen(val), 255); }
				if( strcmp( key , "GText3" , true ) == 0 ) { val = ini_GetValue( Data ); strmid(PlayMission[kGText3], val, 0, strlen(val), 255); }
				if( strcmp( key , "GText4" , true ) == 0 ) { val = ini_GetValue( Data ); strmid(PlayMission[kGText4], val, 0, strlen(val), 255); }
				if( strcmp( key , "GText5" , true ) == 0 ) { val = ini_GetValue( Data ); strmid(PlayMission[kGText5], val, 0, strlen(val), 255); }
				if( strcmp( key , "GText6" , true ) == 0 ) { val = ini_GetValue( Data ); strmid(PlayMission[kGText6], val, 0, strlen(val), 255); }
				if( strcmp( key , "CP1X" , true ) == 0 ) { val = ini_GetValue( Data ); PlayMission[kCP1][0] = floatstr( val ); }
				if( strcmp( key , "CP1Y" , true ) == 0 ) { val = ini_GetValue( Data ); PlayMission[kCP1][1] = floatstr( val ); }
				if( strcmp( key , "CP1Z" , true ) == 0 ) { val = ini_GetValue( Data ); PlayMission[kCP1][2] = floatstr( val ); }
				if( strcmp( key , "CP2X" , true ) == 0 ) { val = ini_GetValue( Data ); PlayMission[kCP2][0] = floatstr( val ); }
				if( strcmp( key , "CP2Y" , true ) == 0 ) { val = ini_GetValue( Data ); PlayMission[kCP2][1] = floatstr( val ); }
				if( strcmp( key , "CP2Z" , true ) == 0 ) { val = ini_GetValue( Data ); PlayMission[kCP2][2] = floatstr( val ); }
				if( strcmp( key , "CP3X" , true ) == 0 ) { val = ini_GetValue( Data ); PlayMission[kCP3][0] = floatstr( val ); }
				if( strcmp( key , "CP3Y" , true ) == 0 ) { val = ini_GetValue( Data ); PlayMission[kCP3][1] = floatstr( val ); }
				if( strcmp( key , "CP3Z" , true ) == 0 ) { val = ini_GetValue( Data ); PlayMission[kCP3][2] = floatstr( val ); }
				if( strcmp( key , "CP4X" , true ) == 0 ) { val = ini_GetValue( Data ); PlayMission[kCP4][0] = floatstr( val ); }
				if( strcmp( key , "CP4Y" , true ) == 0 ) { val = ini_GetValue( Data ); PlayMission[kCP4][1] = floatstr( val ); }
				if( strcmp( key , "CP4Z" , true ) == 0 ) { val = ini_GetValue( Data ); PlayMission[kCP4][2] = floatstr( val ); }
				if( strcmp( key , "CP5X" , true ) == 0 ) { val = ini_GetValue( Data ); PlayMission[kCP5][0] = floatstr( val ); }
				if( strcmp( key , "CP5Y" , true ) == 0 ) { val = ini_GetValue( Data ); PlayMission[kCP5][1] = floatstr( val ); }
				if( strcmp( key , "CP5Z" , true ) == 0 ) { val = ini_GetValue( Data ); PlayMission[kCP5][2] = floatstr( val ); }
				if( strcmp( key , "CP6X" , true ) == 0 ) { val = ini_GetValue( Data ); PlayMission[kCP6][0] = floatstr( val ); }
				if( strcmp( key , "CP6Y" , true ) == 0 ) { val = ini_GetValue( Data ); PlayMission[kCP6][1] = floatstr( val ); }
				if( strcmp( key , "CP6Z" , true ) == 0 ) { val = ini_GetValue( Data ); PlayMission[kCP6][2] = floatstr( val ); }
				if( strcmp( key , "Number" , true ) == 0 ) { val = ini_GetValue( Data ); PlayMission[kNumber] = strval( val ); }
				if( strcmp( key , "Reward" , true ) == 0 ) { val = ini_GetValue( Data ); PlayMission[kReward] = strval( val ); }
				if( strcmp( key , "Toggle" , true ) == 0 ) { val = ini_GetValue( Data ); PlayMission[kToggle] = strval( val ); }
			}
			fclose(file);
			format(strFromFile2, sizeof(strFromFile2), "%s Mission Loaded.",name);
			SendClientMessage(playerid, COLOR_GREEN,strFromFile2);
			format(strFromFile2, sizeof(strFromFile2), "Mission Available: %s, By : %s | Reward: $%d",PlayMission[kTitle],PlayMission[kMaker],PlayMission[kReward]);
			SendClientMessageToAll(COLOR_GREEN, strFromFile2);
			MissionPlayable = PlayMission[kNumber];
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREEN,"Mission File not found.");
		}
	}
	return 1;
}

stock LoadBoxer()
{
	new arrCoords[3][64];
	new strFromFile2[256];
	new File: file = fopen("boxer.ini", io_read);
	if (file)
	{
		fread(file, strFromFile2);
		split(strFromFile2, arrCoords, ',');
		Titel[TitelWins] = strval(arrCoords[0]);
		strmid(Titel[TitelName], arrCoords[1], 0, strlen(arrCoords[1]), 255);
		Titel[TitelLoses] = strval(arrCoords[2]);
		fclose(file);
	}
	return 1;
}

stock SaveBoxer()
{
	new coordsstring[256];
	format(coordsstring, sizeof(coordsstring), "%d,%s,%d", Titel[TitelWins],Titel[TitelName],Titel[TitelLoses]);
	new File: file2 = fopen("boxer.ini", io_write);
	fwrite(file2, coordsstring);
	fclose(file2);
	return 1;
}

stock LoadStuff()
{
	new arrCoords[4][64];
	new strFromFile2[256];
	new File: file = fopen("stuff.ini", io_read);
	if (file)
	{
		fread(file, strFromFile2);
		split(strFromFile2, arrCoords, ',');
		Jackpot = strval(arrCoords[0]);
		Tax = strval(arrCoords[1]);
		TaxValue = strval(arrCoords[2]);
		Security = strval(arrCoords[3]);
		fclose(file);
		if(Security == 0 || Security == 1)
		{
		}
		else
		{
		    GameModeExit();
		}
	}
	else
	{
	    GameModeExit();
	}
	return 1;
}

stock SaveStuff()
{
	new coordsstring[256];
	format(coordsstring, sizeof(coordsstring), "%d,%d,%d,%d", Jackpot,Tax,TaxValue,Security);
	new File: file2 = fopen("stuff.ini", io_write);
	fwrite(file2, coordsstring);
	fclose(file2);
	return 1;
}

stock LoadTurfs()
{
	new arrCoords[6][64];
	new strFromFile2[256];
	new File: file = fopen("turfs.cfg", io_read);
	if (file)
	{
		new idx;
		while (idx < sizeof(TurfInfo))
		{
			fread(file, strFromFile2);
			split(strFromFile2, arrCoords, '|');
			strmid(TurfInfo[idx][zOwner], arrCoords[0], 0, strlen(arrCoords[0]), 255);
			strmid(TurfInfo[idx][zColor], arrCoords[1], 0, strlen(arrCoords[1]), 255);
			TurfInfo[idx][zMinX] = floatstr(arrCoords[2]);
			TurfInfo[idx][zMinY] = floatstr(arrCoords[3]);
			TurfInfo[idx][zMaxX] = floatstr(arrCoords[4]);
			TurfInfo[idx][zMaxY] = floatstr(arrCoords[5]);
			//printf("Turf:%d Name: %s Owner:%s MinX:%f MinY:%f MinZ:%f MaxX:%f MaxY:%f MaxZ:%f\n",
			//idx,TurfInfo[idx][zName],TurfInfo[idx][zOwner],TurfInfo[idx][zMinX],TurfInfo[idx][zMinY],TurfInfo[idx][zMinZ],TurfInfo[idx][zMaxX],TurfInfo[idx][zMaxY],TurfInfo[idx][zMaxZ]);
			idx++;
		}
		fclose(file);
	}
	return 1;
}

stock SaveTurfs()
{
	new idx;
	new File: file2;
	while (idx < sizeof(TurfInfo))
	{
		new coordsstring[256];
		format(coordsstring, sizeof(coordsstring), "%s|%s|%f|%f|%f|%f|%f|%f\n",
		TurfInfo[idx][zOwner],
		TurfInfo[idx][zColor],
		TurfInfo[idx][zMinX],
		TurfInfo[idx][zMinY],
		TurfInfo[idx][zMaxX],
		TurfInfo[idx][zMaxY]);
		if(idx == 0)
		{
			file2 = fopen("turfs.cfg", io_write);
		}
		else
		{
			file2 = fopen("turfs.cfg", io_append);
		}
		fwrite(file2, coordsstring);
		idx++;
		fclose(file2);
	}
	return 1;
}

stock LoadCK()
{
	new arrCoords[3][64];
	new strFromFile2[256];
	new File: file = fopen("ck.cfg", io_read);
	if (file)
	{
		new idx;
		while (idx < sizeof(CKInfo))
		{
			fread(file, strFromFile2);
			split(strFromFile2, arrCoords, '|');
			strmid(CKInfo[idx][cSendername], arrCoords[0], 0, strlen(arrCoords[0]), 255);
			strmid(CKInfo[idx][cGiveplayer], arrCoords[1], 0, strlen(arrCoords[1]), 255);
			CKInfo[idx][cUsed] = strval(arrCoords[2]);
			printf("CK:%d Taken: %d Sendername:%s Giveplayer: %s",
			idx,CKInfo[idx][cUsed],CKInfo[idx][cSendername],CKInfo[idx][cGiveplayer]);
			idx++;
		}
		fclose(file);
	}
	return 1;
}

stock SaveCK()
{
	new idx;
	new File: file2;
	while (idx < sizeof(CKInfo))
	{
		new coordsstring[256];
		format(coordsstring, sizeof(coordsstring), "%s|%s|%d\n",
		CKInfo[idx][cSendername],
		CKInfo[idx][cGiveplayer],
		CKInfo[idx][cUsed]);
		if(idx == 0)
		{
			file2 = fopen("ck.cfg", io_write);
		}
		else
		{
			file2 = fopen("ck.cfg", io_append);
		}
		fwrite(file2, coordsstring);
		idx++;
		fclose(file2);
	}
	return 1;
}

stock LoadFamilies()
{
	new arrCoords[11][64];
	new strFromFile2[256];
	new File: file = fopen("families.cfg", io_read);
	if (file)
	{
		new idx;
		while (idx < sizeof(FamilyInfo))
		{
			fread(file, strFromFile2);
			split(strFromFile2, arrCoords, '|');
			FamilyInfo[idx][FamilyTaken] = strval(arrCoords[0]);
			strmid(FamilyInfo[idx][FamilyName], arrCoords[1], 0, strlen(arrCoords[1]), 255);
			strmid(FamilyInfo[idx][FamilyMOTD], arrCoords[2], 0, strlen(arrCoords[2]), 255);
			strmid(FamilyInfo[idx][FamilyColor], arrCoords[3], 0, strlen(arrCoords[3]), 255);
			strmid(FamilyInfo[idx][FamilyLeader], arrCoords[4], 0, strlen(arrCoords[4]), 255);
			FamilyInfo[idx][FamilyMembers] = strval(arrCoords[5]);
			FamilyInfo[idx][FamilySpawn][0] = floatstr(arrCoords[6]);
			FamilyInfo[idx][FamilySpawn][1] = floatstr(arrCoords[7]);
			FamilyInfo[idx][FamilySpawn][2] = floatstr(arrCoords[8]);
			FamilyInfo[idx][FamilySpawn][3] = floatstr(arrCoords[9]);
			FamilyInfo[idx][FamilyInterior] = strval(arrCoords[10]);
			printf("Family:%d Taken: %d Name:%s MOTD:%s Leader:%s Members:%d SpawnX:%f SpawnY:%f SpawnZ:%f Int:%d",
			idx,FamilyInfo[idx][FamilyTaken],FamilyInfo[idx][FamilyName],FamilyInfo[idx][FamilyMOTD],FamilyInfo[idx][FamilyLeader],FamilyInfo[idx][FamilyMembers],FamilyInfo[idx][FamilySpawn][0],FamilyInfo[idx][FamilySpawn][1],FamilyInfo[idx][FamilySpawn][2],FamilyInfo[idx][FamilyInterior]);
			idx++;
		}
		fclose(file);
	}
	return 1;
}

stock SaveFamilies()
{
	new idx;
	new File: file2;
	while (idx < sizeof(FamilyInfo))
	{
		new coordsstring[256];
		format(coordsstring, sizeof(coordsstring), "%d|%s|%s|%s|%s|%d|%f|%f|%f|%f|%d\n",
		FamilyInfo[idx][FamilyTaken],
		FamilyInfo[idx][FamilyName],
		FamilyInfo[idx][FamilyMOTD],
		FamilyInfo[idx][FamilyColor],
		FamilyInfo[idx][FamilyLeader],
		FamilyInfo[idx][FamilyMembers],
		FamilyInfo[idx][FamilySpawn][0],
		FamilyInfo[idx][FamilySpawn][1],
		FamilyInfo[idx][FamilySpawn][2],
		FamilyInfo[idx][FamilySpawn][3],
		FamilyInfo[idx][FamilyInterior]);
		if(idx == 0)
		{
			file2 = fopen("families.cfg", io_write);
		}
		else
		{
			file2 = fopen("families.cfg", io_append);
		}
		fwrite(file2, coordsstring);
		idx++;
		fclose(file2);
	}
	return 1;
}

stock LoadPapers()
{
	new arrCoords[11][64];
	new strFromFile2[256];
	new File: file = fopen("papers.cfg", io_read);
	if (file)
	{
		new idx;
		while (idx < sizeof(PaperInfo))
		{
			fread(file, strFromFile2);
			split(strFromFile2, arrCoords, '|');
			PaperInfo[idx][PaperUsed] = strval(arrCoords[0]);
			strmid(PaperInfo[idx][PaperMaker], arrCoords[1], 0, strlen(arrCoords[1]), 255);
			strmid(PaperInfo[idx][PaperTitle], arrCoords[2], 0, strlen(arrCoords[2]), 255);
			strmid(PaperInfo[idx][PaperText1], arrCoords[3], 0, strlen(arrCoords[3]), 255);
			strmid(PaperInfo[idx][PaperText2], arrCoords[4], 0, strlen(arrCoords[4]), 255);
			strmid(PaperInfo[idx][PaperText3], arrCoords[5], 0, strlen(arrCoords[5]), 255);
			strmid(PaperInfo[idx][PaperText4], arrCoords[6], 0, strlen(arrCoords[6]), 255);
			strmid(PaperInfo[idx][PaperText5], arrCoords[7], 0, strlen(arrCoords[7]), 255);
			strmid(PaperInfo[idx][PaperText6], arrCoords[8], 0, strlen(arrCoords[8]), 255);
			strmid(PaperInfo[idx][PaperText7], arrCoords[9], 0, strlen(arrCoords[9]), 255);
			PaperInfo[idx][SafeSaving] = strval(arrCoords[10]);
			printf("Paper:%d Used: %d Maker:%s Title: %s Text1: %s Text2: %s Text3: %s Text4: %s Text5: %s Text6: %s Text7: %s",
			idx,PaperInfo[idx][PaperUsed],PaperInfo[idx][PaperMaker],PaperInfo[idx][PaperTitle],PaperInfo[idx][PaperText1],PaperInfo[idx][PaperText2],PaperInfo[idx][PaperText3],PaperInfo[idx][PaperText4],PaperInfo[idx][PaperText5],PaperInfo[idx][PaperText6],PaperInfo[idx][PaperText7]);
			idx++;
		}
		fclose(file);
	}
	return 1;
}

stock SavePapers()
{
	new idx;
	new File: file2;
	while (idx < sizeof(PaperInfo))
	{
		new coordsstring[256];
		format(coordsstring, sizeof(coordsstring), "%d|%s|%s|%s|%s|%s|%s|%s|%s|%s|%d\n",
		PaperInfo[idx][PaperUsed],
		PaperInfo[idx][PaperMaker],
		PaperInfo[idx][PaperTitle],
		PaperInfo[idx][PaperText1],
		PaperInfo[idx][PaperText2],
		PaperInfo[idx][PaperText3],
		PaperInfo[idx][PaperText4],
		PaperInfo[idx][PaperText5],
		PaperInfo[idx][PaperText6],
		PaperInfo[idx][PaperText7],
		PaperInfo[idx][SafeSaving]);
		if(idx == 0)
		{
			file2 = fopen("papers.cfg", io_write);
		}
		else
		{
			file2 = fopen("papers.cfg", io_append);
		}
		fwrite(file2, coordsstring);
		idx++;
		fclose(file2);
	}
	return 1;
}

stock LoadProperty()
{
	new arrCoords[29][64];
	new strFromFile2[256];
	new File: file = fopen("property.cfg", io_read);
	if (file)
	{
		new idx;
		while (idx < sizeof(HouseInfo))
		{
			fread(file, strFromFile2);
			split(strFromFile2, arrCoords, ',');
			HouseInfo[idx][hEntrancex] = floatstr(arrCoords[0]);
			HouseInfo[idx][hEntrancey] = floatstr(arrCoords[1]);
			HouseInfo[idx][hEntrancez] = floatstr(arrCoords[2]);
			HouseInfo[idx][hExitx] = floatstr(arrCoords[3]);
			HouseInfo[idx][hExity] = floatstr(arrCoords[4]);
			HouseInfo[idx][hExitz] = floatstr(arrCoords[5]);
			HouseInfo[idx][hHealthx] = strval(arrCoords[6]);
			HouseInfo[idx][hHealthy] = strval(arrCoords[7]);
			HouseInfo[idx][hHealthz] = strval(arrCoords[8]);
			HouseInfo[idx][hArmourx] = strval(arrCoords[9]);
			HouseInfo[idx][hArmoury] = strval(arrCoords[10]);
			HouseInfo[idx][hArmourz] = strval(arrCoords[11]);
			//printf("HouseInfo hEntrancez %f",HouseInfo[idx][hEntrancez]);
			strmid(HouseInfo[idx][hOwner], arrCoords[12], 0, strlen(arrCoords[12]), 255);
			strmid(HouseInfo[idx][hDiscription], arrCoords[13], 0, strlen(arrCoords[13]), 255);
			HouseInfo[idx][hValue] = strval(arrCoords[14]);
			HouseInfo[idx][hHel] = strval(arrCoords[15]);
			HouseInfo[idx][hArm] = strval(arrCoords[16]);
			HouseInfo[idx][hInt] = strval(arrCoords[17]);
			HouseInfo[idx][hLock] = strval(arrCoords[18]);
			HouseInfo[idx][hOwned] = strval(arrCoords[19]);
			HouseInfo[idx][hRooms] = strval(arrCoords[20]);
			HouseInfo[idx][hRent] = strval(arrCoords[21]);
			HouseInfo[idx][hRentabil] = strval(arrCoords[22]);
			HouseInfo[idx][hTakings] = strval(arrCoords[23]);
			HouseInfo[idx][hVec] = strval(arrCoords[24]);
  	        if(HouseInfo[idx][hVec] == 457)
			{
				HouseInfo[idx][hVec] = 411;
			}
			HouseInfo[idx][hVcol1] = strval(arrCoords[25]);
			HouseInfo[idx][hVcol2] = strval(arrCoords[26]);
			HouseInfo[idx][hDate] = strval(arrCoords[27]);
			HouseInfo[idx][hLevel] = strval(arrCoords[28]);
			printf("HouseInfo:%d Owner:%s hTakings %d hVec %d",idx,HouseInfo[idx][hOwner],HouseInfo[idx][hTakings],HouseInfo[idx][hVec]);
			idx++;
		}
		fclose(file);
	}
	return 1;
}

stock LoadBizz()
{
	new arrCoords[19][64];
	new strFromFile2[256];
	new File: file = fopen("bizz.cfg", io_read);
	if (file)
	{
		new idx;
		while (idx < sizeof(BizzInfo))
		{
			fread(file, strFromFile2);
			split(strFromFile2, arrCoords, '|');
			BizzInfo[idx][bOwned] = strval(arrCoords[0]);
			strmid(BizzInfo[idx][bOwner], arrCoords[1], 0, strlen(arrCoords[1]), 255);
			strmid(BizzInfo[idx][bMessage], arrCoords[2], 0, strlen(arrCoords[2]), 255);
			strmid(BizzInfo[idx][bExtortion], arrCoords[3], 0, strlen(arrCoords[3]), 255);
			BizzInfo[idx][bEntranceX] = floatstr(arrCoords[4]);
			BizzInfo[idx][bEntranceY] = floatstr(arrCoords[5]);
			BizzInfo[idx][bEntranceZ] = floatstr(arrCoords[6]);
			BizzInfo[idx][bExitX] = floatstr(arrCoords[7]);
			BizzInfo[idx][bExitY] = floatstr(arrCoords[8]);
			BizzInfo[idx][bExitZ] = floatstr(arrCoords[9]);
			BizzInfo[idx][bLevelNeeded] = strval(arrCoords[10]);
			BizzInfo[idx][bBuyPrice] = strval(arrCoords[11]);
			BizzInfo[idx][bEntranceCost] = strval(arrCoords[12]);
			BizzInfo[idx][bTill] = strval(arrCoords[13]);
			BizzInfo[idx][bLocked] = strval(arrCoords[14]);
			BizzInfo[idx][bInterior] = strval(arrCoords[15]);
			BizzInfo[idx][bProducts] = strval(arrCoords[16]);
			BizzInfo[idx][bMaxProducts] = strval(arrCoords[17]);
			BizzInfo[idx][bPriceProd] = strval(arrCoords[18]);
			printf("BizzInfo:%d Owner:%s Message:%s Entfee:%d Till:%d Products:%d/%d Interior:%d.\n",
			idx,
			BizzInfo[idx][bOwner],
			BizzInfo[idx][bMessage],
			BizzInfo[idx][bEntranceCost],
			BizzInfo[idx][bTill],
			BizzInfo[idx][bProducts],
			BizzInfo[idx][bMaxProducts],
			BizzInfo[idx][bInterior]);
			idx++;
		}
		fclose(file);
	}
	return 1;
}

stock LoadSBizz()
{
	new arrCoords[16][64];
	new strFromFile2[256];
	new File: file = fopen("sbizz.cfg", io_read);
	if (file)
	{
		new idx;
		while (idx < sizeof(SBizzInfo))
		{
			fread(file, strFromFile2);
			split(strFromFile2, arrCoords, '|');
			SBizzInfo[idx][sbOwned] = strval(arrCoords[0]);
			strmid(SBizzInfo[idx][sbOwner], arrCoords[1], 0, strlen(arrCoords[1]), 255);
			strmid(SBizzInfo[idx][sbMessage], arrCoords[2], 0, strlen(arrCoords[2]), 255);
			strmid(SBizzInfo[idx][sbExtortion], arrCoords[3], 0, strlen(arrCoords[3]), 255);
			SBizzInfo[idx][sbEntranceX] = floatstr(arrCoords[4]);
			SBizzInfo[idx][sbEntranceY] = floatstr(arrCoords[5]);
			SBizzInfo[idx][sbEntranceZ] = floatstr(arrCoords[6]);
			SBizzInfo[idx][sbLevelNeeded] = strval(arrCoords[7]);
			SBizzInfo[idx][sbBuyPrice] = strval(arrCoords[8]);
			SBizzInfo[idx][sbEntranceCost] = strval(arrCoords[9]);
			SBizzInfo[idx][sbTill] = strval(arrCoords[10]);
			SBizzInfo[idx][sbLocked] = strval(arrCoords[11]);
			SBizzInfo[idx][sbInterior] = strval(arrCoords[12]);
			SBizzInfo[idx][sbProducts] = strval(arrCoords[13]);
			SBizzInfo[idx][sbMaxProducts] = strval(arrCoords[14]);
			SBizzInfo[idx][sbPriceProd] = strval(arrCoords[15]);
			printf("SBizzInfo:%d Owner:%s Message:%s Entfee:%d Till:%d Products:%d/%d Interior:%d.\n",
			idx,
			SBizzInfo[idx][sbOwner],
			SBizzInfo[idx][sbMessage],
			SBizzInfo[idx][sbEntranceCost],
			SBizzInfo[idx][sbTill],
			SBizzInfo[idx][sbProducts],
			SBizzInfo[idx][sbMaxProducts],
			SBizzInfo[idx][sbInterior]);
			idx++;
		}
		fclose(file);
	}
	return 1;
}

stock SyncTime()
{
	new string[64];
	new tmphour;
	new tmpminute;
	new tmpsecond;
	gettime(tmphour, tmpminute, tmpsecond);
	FixHour(tmphour);
	tmphour = shifthour;
	if ((tmphour > ghour) || (tmphour == 0 && ghour == 23))
	{
		format(string, sizeof(string), "SERVER: The time is now %d:00 hours",tmphour);
		BroadCast(COLOR_WHITE,string);
		ghour = tmphour;
		PayDay();
		if (realtime)
		{
			SetWorldTime(tmphour);
		}
	}
}

stock IsPlayerInTurf(playerid, turfid)
{
	if(IsPlayerConnected(playerid))
	{
		if(turfid == -1)
		{
			return 0;
		}
		new Float:x, Float:y, Float:z;
		GetPlayerPos(playerid,x,y,z);
		if(x >= TurfInfo[turfid][zMinX] && x < TurfInfo[turfid][zMaxX] && y >= TurfInfo[turfid][zMinY] && y < TurfInfo[turfid][zMaxY])
		{
	 		return 1;
		}
	}
	return 0;
}

stock GetClosestPlayer(p1)
{
	new x,Float:dis,Float:dis2,player;
	player = -1;
	dis = 99999.99;
	for (x=0;x<MAX_PLAYERS;x++)
	{
		if(IsPlayerConnected(x))
		{
			if(x != p1)
			{
				dis2 = GetDistanceBetweenPlayers(x,p1);
				if(dis2 < dis && dis2 != -1.00)
				{
					dis = dis2;
					player = x;
				}
			}
		}
	}
	return player;
}

stock Production()
{
	new string[256];
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i))
		{
		    if(PlayerInfo[i][pFishes] >= 5) { if(FishCount[i] >= 3) { PlayerInfo[i][pFishes] = 0; } else { FishCount[i] += 1; } }
		    if(PlayerDrunk[i] > 0) { PlayerDrunk[i] = 0; PlayerDrunkTime[i] = 0; GameTextForPlayer(i, "~p~Drunk effect~n~~w~Gone", 3500, 1); }
		    if(PlayerInfo[i][pPayDay] < 6) { PlayerInfo[i][pPayDay] += 1; } //+ 5 min to PayDay anti-abuse
		    for(new k = 0; k < MAX_PLAYERS; k++)
			{
				if(IsPlayerConnected(k))
				{
				    if(gTeam[k] == 2 && CrimInRange(80.0, i,k))
				    {
					}
					else
					{
					    WantedPoints[i] -= 3;
					    if(WantedPoints[i] < 0) { WantedPoints[i] = 0; }
					    new points = WantedPoints[i];
					    new wlevel;
					    if(points > 0)
						{
						    new yesno;
							if(points == 3) { if(WantedLevel[i] != 1) { WantedLevel[i] = 1; wlevel = 1; yesno = 1; } }
							else if(points >= 4 && points <= 5) { if(WantedLevel[i] != 2) { WantedLevel[i] = 2; wlevel = 2; yesno = 1; } }
							else if(points >= 6 && points <= 7) { if(WantedLevel[i] != 3) { WantedLevel[i] = 3; wlevel = 3; yesno = 1; } }
							else if(points >= 8 && points <= 9) { if(WantedLevel[i] != 4) { WantedLevel[i] = 4; wlevel = 4; yesno = 1; } }
							else if(points >= 10 && points <= 11) { if(WantedLevel[i] != 5) { WantedLevel[i] = 5; wlevel = 5; yesno = 1; } }
							else if(points >= 12 && points <= 13) { if(WantedLevel[i] != 6) { WantedLevel[i] = 6; wlevel = 6; yesno = 1; } }
							else if(points >= 14) { if(WantedLevel[i] != 10) { WantedLevel[i] = 10; wlevel = 10; yesno = 1; } }
							else if(points <= 0) { if(WantedLevel[i] != 0) { ClearCrime(i); WantedLevel[i] = 0; wlevel = 0; yesno = 1;} }
							if(yesno)
							{
								format(string, sizeof(string), "Current Wanted Level: %d", wlevel);
								SendClientMessage(i, COLOR_YELLOW, string);
							}
						}
					}
				}
			}
		}
	}
}

stock DateProp(playerid)
{
	new playername[MAX_PLAYER_NAME];
	GetPlayerName(playerid, playername, sizeof(playername));
	new curdate = getdate();
	for(new h = 0; h < sizeof(HouseInfo); h++)
	{
		if (strcmp(playername, HouseInfo[h][hOwner], true) == 0)
		{
			HouseInfo[h][hDate] = curdate;
			OnPropUpdate();
		}
	}
	return 1;
}

stock Checkprop()
{
	new olddate;
	new string[256];
	new curdate = getdate();
	for(new h = 0; h < sizeof(HouseInfo); h++)
	{
		if(HouseInfo[h][hOwned] == 1 && HouseInfo[h][hDate] > 9)
		{
			olddate = HouseInfo[h][hDate];
			if(curdate-olddate >= 5)
			{
				HouseInfo[h][hHel] = 0;
				HouseInfo[h][hArm] = 0;
				HouseInfo[h][hHealthx] = 0;
				HouseInfo[h][hHealthy] = 0;
				HouseInfo[h][hHealthz] = 0;
				HouseInfo[h][hArmourx] = 0;
				HouseInfo[h][hArmoury] = 0;
				HouseInfo[h][hArmourz] = 0;
				HouseInfo[h][hLock] = 1;
				HouseInfo[h][hOwned] = 0;
				HouseInfo[h][hVec] = 418;
				HouseInfo[h][hVcol1] = -1;
				HouseInfo[h][hVcol2] = -1;
				strmid(HouseInfo[h][hOwner], "The State", 0, strlen("The State"), 255);
				format(string, sizeof(string), "REAL ESTATE: A House is available at a value of $%d",HouseInfo[h][hValue]);
				SendClientMessageToAll(TEAM_BALLAS_COLOR, string);
				OnPropUpdate();
			}
		}
	}
	return 1;
}

stock PayDay()
{
	new string[128];
	new account,interest;
	new rent = 0;
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i))
		{
		    if(PlayerInfo[i][pLevel] > 0)
		    {
			    if(MoneyMessage[i]==1)
				{
				    SendClientMessage(i, COLOR_LIGHTRED, "You failed to pay your debt, Jail time.");
				    GameTextForPlayer(i, "~r~Busted!", 2000, 1);
				    SetPlayerInterior(i, 6);
			   		SetPlayerPos(i, 264.6288,77.5742,1001.0391);
		            PlayerInfo[i][pJailed] = 1;
		            ResetPlayerWeapons(i);
					WantedPoints[i] = 0;
					PlayerInfo[i][pJailTime] = 240;
					format(string, sizeof(string), "You are jailed for %d seconds.   Bail: Unable", PlayerInfo[i][pJailTime]);
					SendClientMessage(i, COLOR_LIGHTBLUE, string);
				}
				new playername2[MAX_PLAYER_NAME];
				GetPlayerName(i, playername2, sizeof(playername2));
				account = PlayerInfo[i][pAccount];
				new key = PlayerInfo[i][pPhousekey];
				if(key != 255)
				{
					rent = HouseInfo[key][hRent];
					if(strcmp(playername2, HouseInfo[key][hOwner], true) == 0)
					{
						rent = 0;
					}
					else if(rent > GetPlayerMoney(i))
					{
						PlayerInfo[i][pPhousekey] = 255;
						SendClientMessage(i, COLOR_WHITE, "You have been evicted.");
						rent = 0;
					}
					HouseInfo[key][hTakings] = HouseInfo[key][hTakings]+rent;
				}
				new tmpintrate;
				if (key != 255 && strcmp(playername2, HouseInfo[key][hOwner], true) == 0)
				{
				    if(PlayerInfo[i][pDonateRank] > 0) { tmpintrate = intrate+4; }
					else { tmpintrate = intrate+2; }//HouseInfo[key][hLevel]
				}
				else
				{
				    if(PlayerInfo[i][pDonateRank] > 0) { tmpintrate = 3; }
					else { tmpintrate = 1; }
				}
				if(PlayerInfo[i][pPayDay] >= 5)
				{
				    Tax += TaxValue;//Should work for every player online
				    PlayerInfo[i][pAccount] -= TaxValue;
				    if(PlayerInfo[i][pDonateRank] > 0)
					{
					    new bonus = PlayerInfo[i][pPayCheck] / 2;
					    PlayerInfo[i][pPayCheck] += bonus;
					}
					new checks = PlayerInfo[i][pPayCheck];
				    new ebill = (PlayerInfo[i][pAccount]/10000)*(PlayerInfo[i][pLevel]);
				    ConsumingMoney[i] = 1;
				    GivePlayerMoney(i, checks);
				    if(PlayerInfo[i][pAccount] > 0)
				    {
				    	PlayerInfo[i][pAccount] -= ebill;
				    	SBizzInfo[4][sbTill] += ebill;
					}
					else
					{
					    ebill = 0;
					}
					interest = (PlayerInfo[i][pAccount]/1000)*(tmpintrate);
					PlayerInfo[i][pExp]++;
					PlayerPlayMusic(i);
					PlayerInfo[i][pAccount] = account+interest;
					SendClientMessage(i, COLOR_WHITE, "|___ BANK STATMENT ___|");
					format(string, sizeof(string), "  Paycheck: $%d   Tax Money: -$%d", checks, TaxValue);
					SendClientMessage(i, COLOR_GRAD1, string);
					if(PlayerInfo[i][pPhousekey] != 255 || PlayerInfo[i][pPbiskey] != 255)
					{
					    format(string, sizeof(string), "  Electricity Bill: -$%d", ebill);
						SendClientMessage(i, COLOR_GRAD1, string);
					}
					format(string, sizeof(string), "  Balance: $%d", account);
					SendClientMessage(i, COLOR_GRAD1, string);
					format(string, sizeof(string), "  Interest Rate: 0.%d percent",tmpintrate);
					SendClientMessage(i, COLOR_GRAD2, string);
					format(string, sizeof(string), "  Interest Gained $%d", interest);
					SendClientMessage(i, COLOR_GRAD3, string);
					SendClientMessage(i, COLOR_GRAD4, "|--------------------------------------|");
					format(string, sizeof(string), "  New Balance: $%d", PlayerInfo[i][pAccount]);
					SendClientMessage(i, COLOR_GRAD5, string);
					format(string, sizeof(string), "  Rent: -$%d", rent);
					SendClientMessage(i, COLOR_GRAD5, string);
					format(string, sizeof(string), "~y~PayDay~n~~w~Paycheck");
					GameTextForPlayer(i, string, 5000, 1);
					rent = 0;
					PlayerInfo[i][pPayDay] = 0;
					PlayerInfo[i][pPayCheck] = 0;
					PlayerInfo[i][pConnectTime] += 1;
					if(PlayerInfo[i][pDonateRank] > 0)
					{
					    PlayerInfo[i][pPayDayHad] += 1;
					    if(PlayerInfo[i][pPayDayHad] >= 5)
					    {
					        PlayerInfo[i][pExp]++;
					        PlayerInfo[i][pPayDayHad] = 0;
					    }
					}
				}
				else
				{
				    SendClientMessage(i, COLOR_LIGHTRED, "* You haven't played long enough to obtain a PayDay.");
				}
			}
		}
	}
	Checkprop();
	return 1;
}

stock strtok(const string[], &index)
{
	new length = strlen(string);
	while ((index < length) && (string[index] <= ' '))
	{
		index++;
	}

	new offset = index;
	new result[20];
	while ((index < length) && (string[index] > ' ') && ((index - offset) < (sizeof(result) - 1)))
	{
		result[index - offset] = string[index];
		index++;
	}
	result[index - offset] = EOS;
	return result;
}

stock OnPlayerRegister(playerid, password[])
{
	if(IsPlayerConnected(playerid))
	{
			new string3[32];
			new playername3[MAX_PLAYER_NAME];
			GetPlayerName(playerid, playername3, sizeof(playername3));
			format(string3, sizeof(string3), "%s.ini", playername3);
			new File: hFile = fopen(string3, io_write);
			if (hFile)
			{
			    strmid(PlayerInfo[playerid][pKey], password, 0, strlen(password), 255);
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
				format(var, 32, "Fuel=%d\n",PlayerInfo[playerid][pFuel]);fwrite(hFile, var);
				format(var, 32, "Married=%d\n",PlayerInfo[playerid][pMarried]);fwrite(hFile, var);
				format(var, 32, "MarriedTo=%s\n",PlayerInfo[playerid][pMarriedTo]);fwrite(hFile, var);
				fclose(hFile);
				SendClientMessage(playerid, COLOR_YELLOW, "Account registered, you can login now (/login [password]).");
			}
	}
	return 1;
}

stock OnPlayerLogin(playerid,password[])
{
	new tmp2[256];
    new string2[64];
	new playername2[MAX_PLAYER_NAME];
    GetPlayerName(playerid, playername2, sizeof(playername2));
	format(string2, sizeof(string2), "%s.ini", playername2);
	new File: UserFile = fopen(string2, io_read);
	if ( UserFile )
	{
	    new PassData[256];
	    new keytmp[256], valtmp[256];
	    fread( UserFile , PassData , sizeof( PassData ) );
	    keytmp = ini_GetKey( PassData );
	    if( strcmp( keytmp , "Key" , true ) == 0 )
		{
			valtmp = ini_GetValue( PassData );
			strmid(PlayerInfo[playerid][pKey], valtmp, 0, strlen(valtmp)-1, 255);
		}
		if(strcmp(PlayerInfo[playerid][pKey],password, true ) == 0 )
		{
			    new key[ 256 ] , val[ 256 ];
			    new Data[ 256 ];
			    while ( fread( UserFile , Data , sizeof( Data ) ) )
				{
					key = ini_GetKey( Data );
					if( strcmp( key , "Level" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pLevel] = strval( val ); }
			    	if( strcmp( key , "AdminLevel" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pAdmin] = strval( val ); }
			        if( strcmp( key , "DonateRank" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pDonateRank] = strval( val ); }
			        if( strcmp( key , "UpgradePoints" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][gPupgrade] = strval( val ); }
			        if( strcmp( key , "ConnectedTime" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pConnectTime] = strval( val ); }
			        if( strcmp( key , "Registered" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pReg] = strval( val ); }
			        if( strcmp( key , "Sex" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pSex] = strval( val ); }
			        if( strcmp( key , "Age" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pAge] = strval( val ); }
			        if( strcmp( key , "Origin" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pOrigin] = strval( val ); }
			        if( strcmp( key , "CK" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pCK] = strval( val ); }
			        if( strcmp( key , "Muted" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pMuted] = strval( val ); }
			        if( strcmp( key , "Respect" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pExp] = strval( val ); }
			        if( strcmp( key , "Money" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pCash] = strval( val ); }
			        if( strcmp( key , "Bank" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pAccount] = strval( val ); }
			        if( strcmp( key , "Crimes" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pCrimes] = strval( val ); }
			        if( strcmp( key , "Kills" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pKills] = strval( val ); }
			        if( strcmp( key , "Deaths" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pDeaths] = strval( val ); }
			        if( strcmp( key , "Arrested" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pArrested] = strval( val ); }
			        if( strcmp( key , "WantedDeaths" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pWantedDeaths] = strval( val ); }
			        if( strcmp( key , "Phonebook" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pPhoneBook] = strval( val ); }
			        if( strcmp( key , "LottoNr" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pLottoNr] = strval( val ); }
			        if( strcmp( key , "Fishes" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pFishes] = strval( val ); }
			        if( strcmp( key , "BiggestFish" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pBiggestFish] = strval( val ); }
			        if( strcmp( key , "Job" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pJob] = strval( val ); }
			        if( strcmp( key , "Paycheck" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pPayCheck] = strval( val ); }
			        if( strcmp( key , "HeadValue" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pHeadValue] = strval( val ); }
			        if( strcmp( key , "Jailed" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pJailed] = strval( val ); }
			        if( strcmp( key , "JailTime" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pJailTime] = strval( val ); }
			        if( strcmp( key , "Materials" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pMats] = strval( val ); }
			        if( strcmp( key , "Drugs" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pDrugs] = strval( val ); }
			        if( strcmp( key , "Leader" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pLeader] = strval( val ); }
			        if( strcmp( key , "Member" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pMember] = strval( val ); }
			        if( strcmp( key , "FMember" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pFMember] = strval( val ); }
			        if( strcmp( key , "Rank" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pRank] = strval( val ); }
			        if( strcmp( key , "Char" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pChar] = strval( val ); }
			        if( strcmp( key , "ContractTime" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pContractTime] = strval( val ); }
			        if( strcmp( key , "DetSkill" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pDetSkill] = strval( val ); }
			        if( strcmp( key , "SexSkill" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pSexSkill] = strval( val ); }
			        if( strcmp( key , "BoxSkill" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pBoxSkill] = strval( val ); }
			        if( strcmp( key , "LawSkill" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pLawSkill] = strval( val ); }
			        if( strcmp( key , "MechSkill" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pMechSkill] = strval( val ); }
			        if( strcmp( key , "JackSkill" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pJackSkill] = strval( val ); }
			        if( strcmp( key , "CarSkill" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pCarSkill] = strval( val ); }
			        if( strcmp( key , "NewsSkill" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pNewsSkill] = strval( val ); }
			        if( strcmp( key , "DrugsSkill" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pDrugsSkill] = strval( val ); }
			        if( strcmp( key , "CookSkill" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pCookSkill] = strval( val ); }
			        if( strcmp( key , "FishSkill" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pFishSkill] = strval( val ); }
			        if( strcmp( key , "pSHealth" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pSHealth] = floatstr( val ); }
			        if( strcmp( key , "pHealth" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pHealth] = floatstr( val ); }
			        if( strcmp( key , "Int" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pInt] = strval( val ); }
			        if( strcmp( key , "Local" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pLocal] = strval( val ); }
			        if( strcmp( key , "Team" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pTeam] = strval( val ); }
			        if( strcmp( key , "Model" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pModel] = strval( val ); }
			        if( strcmp( key , "PhoneNr" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pPnumber] = strval( val ); }
			        if( strcmp( key , "House" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pPhousekey] = strval( val ); }
			        if( strcmp( key , "Bizz" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pPbiskey] = strval( val ); }
			        if( strcmp( key , "Pos_x" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pPos_x] = floatstr( val ); }
			        if( strcmp( key , "Pos_y" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pPos_y] = floatstr( val ); }
			        if( strcmp( key , "Pos_z" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pPos_z] = floatstr( val ); }
			        if( strcmp( key , "CarLic" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pCarLic] = strval( val ); }
                    if( strcmp( key , "FlyLic" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pFlyLic] = strval( val ); }
					if( strcmp( key , "BoatLic" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pBoatLic] = strval( val ); }
			        if( strcmp( key , "FishLic" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pFishLic] = strval( val ); }
			        if( strcmp( key , "GunLic" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pGunLic] = strval( val ); }
			        if( strcmp( key , "Gun1" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pGun1] = strval( val ); }
			        if( strcmp( key , "Gun2" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pGun2] = strval( val ); }
			        if( strcmp( key , "Gun3" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pGun3] = strval( val ); }
			        if( strcmp( key , "Gun4" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pGun4] = strval( val ); }
			        if( strcmp( key , "Ammo1" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pAmmo1] = strval( val ); }
			        if( strcmp( key , "Ammo2" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pAmmo2] = strval( val ); }
			        if( strcmp( key , "Ammo3" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pAmmo3] = strval( val ); }
			        if( strcmp( key , "Ammo4" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pAmmo4] = strval( val ); }
			        if( strcmp( key , "CarTime" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pCarTime] = strval( val ); }
			        if( strcmp( key , "PayDay" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pPayDay] = strval( val ); }
			        if( strcmp( key , "PayDayHad" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pPayDayHad] = strval( val ); }
			        if( strcmp( key , "CDPlayer" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pCDPlayer] = strval( val ); }
			        if( strcmp( key , "Wins" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pWins] = strval( val ); }
			        if( strcmp( key , "Loses" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pLoses] = strval( val ); }
			        if( strcmp( key , "AlcoholPerk" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pAlcoholPerk] = strval( val ); }
			        if( strcmp( key , "DrugPerk" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pDrugPerk] = strval( val ); }
			        if( strcmp( key , "MiserPerk" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pMiserPerk] = strval( val ); }
			        if( strcmp( key , "PainPerk" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pPainPerk] = strval( val ); }
			        if( strcmp( key , "TraderPerk" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pTraderPerk] = strval( val ); }
			        if( strcmp( key , "Tutorial" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pTut] = strval( val ); }
			        if( strcmp( key , "Mission" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pMissionNr] = strval( val ); }
			        if( strcmp( key , "Warnings" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pWarns] = strval( val ); }
			        if( strcmp( key , "Adjustable" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pAdjustable] = strval( val ); }
			        if( strcmp( key , "Fuel" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pFuel] = strval( val ); }
			        if( strcmp( key , "Married" , true ) == 0 ) { val = ini_GetValue( Data ); PlayerInfo[playerid][pMarried] = strval( val ); }
			        if( strcmp( key , "MarriedTo" , true ) == 0 ) { val = ini_GetValue( Data ); strmid(PlayerInfo[playerid][pMarriedTo], val, 0, strlen(val)-1, 255); }
                }//end while
                fclose(UserFile);//close the file after everything has been read in the while
		}
		else
		{
			SendClientMessage(playerid, COLOR_WHITE, "SERVER: Password does not match your name.");
	        fclose(UserFile);
	        gPlayerLogTries[playerid] += 1;
	        if(gPlayerLogTries[playerid] == 4) { Ban(playerid); }
	        return 1;
		}
		PlayerInfo[playerid][pAdjustable] = 0;
		ResetPlayerMoney(playerid);
		ConsumingMoney[playerid] = 1;
		GivePlayerMoney(playerid,PlayerInfo[playerid][pCash]);
		CurrentMoney[playerid] = PlayerInfo[playerid][pCash];
		if(PlayerInfo[playerid][pReg] == 0)
		{
			PlayerInfo[playerid][pLevel] = 1;
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
			PlayerInfo[playerid][pAccount] = 50000;
			PlayerInfo[playerid][pReg] = 1;
			GivePlayerMoney(playerid, 5000);
		}
		if(PlayerInfo[playerid][pLevel] == -999) //autoban
		{
			Ban(playerid);
		}
		else if(PlayerInfo[playerid][pCK] > 0)
		{
		    Kick(playerid);
		}
		format(string2, sizeof(string2), "SERVER: Welcome %s",playername2);
		SendClientMessage(playerid, COLOR_WHITE,string2);
		printf("%s has logged in.",playername2);
		if (PlayerInfo[playerid][pDonateRank] > 0)
		{
			SendClientMessage(playerid, COLOR_WHITE,"SERVER: You are a Premium Account user.");
		}
		if (PlayerInfo[playerid][pAdmin] > 0)
		{
			format(string2, sizeof(string2), "SERVER: You are logged in as a Level %d Admin.",PlayerInfo[playerid][pAdmin]);
			SendClientMessage(playerid, COLOR_WHITE,string2);
		}
		SetSpawnInfo(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pModel], PlayerInfo[playerid][pPos_x], PlayerInfo[playerid][pPos_y], PlayerInfo[playerid][pPos_z], 1.0, -1, -1, -1, -1, -1, -1);
		if(gTeam[playerid] == 0)
		{
			gTeam[playerid] = 3;
		}
		else
		{
			gTeam[playerid] = PlayerInfo[playerid][pTeam];
		}
		gPlayerLogged[playerid] = 1;
		SpawnPlayer(playerid);
		format(tmp2, sizeof(tmp2), "~w~Welcome ~n~~y~   %s", playername2);
		DateProp(playerid);
		GameTextForPlayer(playerid, tmp2, 5000, 1);
		SendClientMessage(playerid, COLOR_YELLOW, motd);
		if(PlayerInfo[playerid][pFMember] < 255)
		{
		    format(tmp2, sizeof(tmp2), "Family MOTD: %s.", FamilyInfo[PlayerInfo[playerid][pFMember]][FamilyMOTD]);
		    SendClientMessage(playerid, COLOR_YELLOW, tmp2);
		}
	}
	return 1;
}

stock ini_GetKey( line[] )
{
	new keyRes[256];
	keyRes[0] = 0;
    if ( strfind( line , "=" , true ) == -1 ) return keyRes;
    strmid( keyRes , line , 0 , strfind( line , "=" , true ) , sizeof( keyRes) );
    return keyRes;
}

stock ini_GetValue( line[] )
{
	new valRes[256];
	valRes[0]=0;
	if ( strfind( line , "=" , true ) == -1 ) return valRes;
	strmid( valRes , line , strfind( line , "=" , true )+1 , strlen( line ) , sizeof( valRes ) );
	return valRes;
}

stock OnPropUpdate()
{
	new idx;
	new File: file2;
	while (idx < sizeof(HouseInfo))
	{
		new coordsstring[256];
		format(coordsstring, sizeof(coordsstring), "%f,%f,%f,%f,%f,%f,%d,%d,%d,%d,%d,%d,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
		HouseInfo[idx][hEntrancex],
		HouseInfo[idx][hEntrancey],
		HouseInfo[idx][hEntrancez],
		HouseInfo[idx][hExitx],
		HouseInfo[idx][hExity],
		HouseInfo[idx][hExitz],
		HouseInfo[idx][hHealthx],
		HouseInfo[idx][hHealthy],
		HouseInfo[idx][hHealthz],
		HouseInfo[idx][hArmourx],
		HouseInfo[idx][hArmoury],
		HouseInfo[idx][hArmourz],
		HouseInfo[idx][hOwner],
		HouseInfo[idx][hDiscription],
		HouseInfo[idx][hValue],
		HouseInfo[idx][hHel],
		HouseInfo[idx][hArm],
		HouseInfo[idx][hInt],
		HouseInfo[idx][hLock],
		HouseInfo[idx][hOwned],
		HouseInfo[idx][hRooms],
		HouseInfo[idx][hRent],
		HouseInfo[idx][hRentabil],
		HouseInfo[idx][hTakings],
		HouseInfo[idx][hVec],
		HouseInfo[idx][hVcol1],
		HouseInfo[idx][hVcol2],
		HouseInfo[idx][hDate],
		HouseInfo[idx][hLevel]);
		if(idx == 0)
		{
			file2 = fopen("property.cfg", io_write);
		}
		else
		{
			file2 = fopen("property.cfg", io_append);
		}
		fwrite(file2, coordsstring);
		idx++;
		fclose(file2);
	}
	idx = 0;
	while (idx < sizeof(BizzInfo))
	{
		new coordsstring[256];
		format(coordsstring, sizeof(coordsstring), "%d|%s|%s|%s|%f|%f|%f|%f|%f|%f|%d|%d|%d|%d|%d|%d|%d|%d|%d\n",
		BizzInfo[idx][bOwned],
		BizzInfo[idx][bOwner],
		BizzInfo[idx][bMessage],
		BizzInfo[idx][bExtortion],
		BizzInfo[idx][bEntranceX],
		BizzInfo[idx][bEntranceY],
		BizzInfo[idx][bEntranceZ],
		BizzInfo[idx][bExitX],
		BizzInfo[idx][bExitY],
		BizzInfo[idx][bExitZ],
		BizzInfo[idx][bLevelNeeded],
		BizzInfo[idx][bBuyPrice],
		BizzInfo[idx][bEntranceCost],
		BizzInfo[idx][bTill],
		BizzInfo[idx][bLocked],
		BizzInfo[idx][bInterior],
		BizzInfo[idx][bProducts],
		BizzInfo[idx][bMaxProducts],
		BizzInfo[idx][bPriceProd]);
		if(idx == 0)
		{
			file2 = fopen("bizz.cfg", io_write);
		}
		else
		{
			file2 = fopen("bizz.cfg", io_append);
		}
		fwrite(file2, coordsstring);
		idx++;
		fclose(file2);
	}
	idx = 0;
	while (idx < sizeof(SBizzInfo))
	{
		new coordsstring[256];
		format(coordsstring, sizeof(coordsstring), "%d|%s|%s|%s|%f|%f|%f|%d|%d|%d|%d|%d|%d|%d|%d|%d\n",
		SBizzInfo[idx][sbOwned],
		SBizzInfo[idx][sbOwner],
		SBizzInfo[idx][sbMessage],
		SBizzInfo[idx][sbExtortion],
		SBizzInfo[idx][sbEntranceX],
		SBizzInfo[idx][sbEntranceY],
		SBizzInfo[idx][sbEntranceZ],
		SBizzInfo[idx][sbLevelNeeded],
		SBizzInfo[idx][sbBuyPrice],
		SBizzInfo[idx][sbEntranceCost],
		SBizzInfo[idx][sbTill],
		SBizzInfo[idx][sbLocked],
		SBizzInfo[idx][sbInterior],
		SBizzInfo[idx][sbProducts],
		SBizzInfo[idx][sbMaxProducts],
		SBizzInfo[idx][sbPriceProd]);
		if(idx == 0)
		{
			file2 = fopen("sbizz.cfg", io_write);
		}
		else
		{
			file2 = fopen("sbizz.cfg", io_append);
		}
		fwrite(file2, coordsstring);
		idx++;
		fclose(file2);
	}
	return 1;
}

stock BroadCast(color,const string[])
{
	SendClientMessageToAll(color, string);
	return 1;
}

stock ABroadCast(color,const string[],level)
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i))
		{
			if (PlayerInfo[i][pAdmin] >= level)
			{
				SendClientMessage(i, color, string);
				printf("%s", string);
			}
		}
	}
	return 1;
}

stock OOCOff(color,const string[])
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i))
		{
		    if(!gOoc[i])
		    {
				SendClientMessage(i, color, string);
			}
		}
	}
}

stock OOCNews(color,const string[])
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i))
		{
		    if(!gNews[i])
		    {
				SendClientMessage(i, color, string);
			}
		}
	}
}

stock SendTeamMessage(team, color, string[])
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i))
		{
		    if(gTeam[i] == team)
		    {
				SendClientMessage(i, color, string);
			}
		}
	}
}

stock SendRadioMessage(member, color, string[])
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i))
		{
		    if(PlayerInfo[i][pMember] == member || PlayerInfo[i][pLeader] == member)
		    {
				SendClientMessage(i, color, string);
			}
		}
	}
}

stock SendJobMessage(job, color, string[])
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i))
		{
		    if(PlayerInfo[i][pJob] == job)
		    {
				SendClientMessage(i, color, string);
			}
		}
	}
}

stock SendNewFamilyMessage(family, color, string[])
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i))
		{
		    if(PlayerInfo[i][pFMember] == family)
		    {
                if(!gFam[i])
                {
					SendClientMessage(i, color, string);
				}
			}
		}
	}
}

stock SendFamilyMessage(family, color, string[])
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i))
		{
		    if(PlayerInfo[i][pMember] == family || PlayerInfo[i][pLeader] == family)
		    {
                if(!gFam[i])
                {
					SendClientMessage(i, color, string);
				}
			}
		}
	}
}

stock SendTeamBeepMessage(team, color, string[])
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i))
		{
		    if(gTeam[i] == team)
		    {
				SendClientMessage(i, color, string);
				RingTone[i] = 20;
			}
		}
	}
}

stock SendEnemyMessage(color, string[])
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i))
		{
		    if(gTeam[i] >= 3)
		    {
				SendClientMessage(i, color, string);
			}
		}
	}
}

stock SendAdminMessage(color, string[])
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i))
		{
		    if(PlayerInfo[i][pAdmin] >= 1)
		    {
				SendClientMessage(i, color, string);
			}
		}
	}
}

stock AddCar(carcoords)
{
	new randcol = random(126);
	new randcol2 = 1;
	if (rccounter == 14)
	{
		rccounter = 0;
	}
	AddStaticVehicleEx(carselect[rccounter], CarSpawns[carcoords][pos_x], CarSpawns[carcoords][pos_y], CarSpawns[carcoords][pos_z], CarSpawns[carcoords][z_angle], randcol, randcol2, 60000);
	rccounter++;
	return 1;
}

stock PlayerPlayMusic(playerid)
{
	if(IsPlayerConnected(playerid))
	{
		SetTimer("StopMusic", 5000, 0);
		PlayerPlaySound(playerid, 1068, 0.0, 0.0, 0.0);
	}
}

stock StopMusic()
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i))
		{
			PlayerPlaySound(i, 1069, 0.0, 0.0, 0.0);
		}
	}
}

stock PlayerFixRadio(playerid)
{
    if(IsPlayerConnected(playerid))
	{
	    SetTimer("PlayerFixRadio2", 1000, 0);
		PlayerPlaySound(playerid, 1068, 0.0, 0.0, 0.0);
		Fixr[playerid] = 1;
	}
}

stock PlayerFixRadio2()
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i))
		{
			if(Fixr[i])
			{
				PlayerPlaySound(i, 1069, 0.0, 0.0, 0.0);
				Fixr[i] = 0;
			}
		}
	}
}

stock HouseLevel(playerid)
{
	if(IsPlayerConnected(playerid))
	{
		new h = PlayerInfo[playerid][pPhousekey];
		if(h == 255) { return 0; }
		if(h <= 4) { return 1; }
		if(h >= 5 && h <= 9)  { return 2; }
		if(h >= 10 && h <= 18) { return 3; }
		if(h >= 19 && h <= 22) { return 4; }
		if(h >= 23 && h <= 25) { return 5; }
		if(h == 26) { return 6; }
		if(h == 27) { return 7; }
		if(h >= 28 && h <= 31) { return 7; }
	}
	return 0;
}

stock CHouseLevel(houseid)
{
	if(houseid <= 4) { return 3; }
	if(houseid >= 29 && houseid <= 30) { return 4; }
	if(houseid >= 5 && houseid <= 9) { return 5; }
	if(houseid >= 10 && houseid <= 18 || houseid == 28) { return 7; }
	if(houseid >= 19 && houseid <= 22) { return 8; }
	if(houseid >= 23 && houseid <= 25) { return 9; }
	if(houseid == 26) { return 10; }
	if(houseid == 27) { return 11; }
	if(houseid >= 28 && houseid <= 31) { return 12; }
	return 0;
}

stock ProxDetector(Float:radi, playerid, string[],col1,col2,col3,col4,col5)
{
	if(IsPlayerConnected(playerid))
	{
		new Float:posx, Float:posy, Float:posz;
		new Float:oldposx, Float:oldposy, Float:oldposz;
		new Float:tempposx, Float:tempposy, Float:tempposz;
		GetPlayerPos(playerid, oldposx, oldposy, oldposz);
		//radi = 2.0; //Trigger Radius
		for(new i = 0; i < MAX_PLAYERS; i++)
		{
			if(IsPlayerConnected(i))
			{
				if(!BigEar[i])
				{
					GetPlayerPos(i, posx, posy, posz);
					tempposx = (oldposx -posx);
					tempposy = (oldposy -posy);
					tempposz = (oldposz -posz);
					//printf("DEBUG: X:%f Y:%f Z:%f",posx,posy,posz);
					if (((tempposx < radi/16) && (tempposx > -radi/16)) && ((tempposy < radi/16) && (tempposy > -radi/16)) && ((tempposz < radi/16) && (tempposz > -radi/16)))
					{
						SendClientMessage(i, col1, string);
					}
					else if (((tempposx < radi/8) && (tempposx > -radi/8)) && ((tempposy < radi/8) && (tempposy > -radi/8)) && ((tempposz < radi/8) && (tempposz > -radi/8)))
					{
						SendClientMessage(i, col2, string);
					}
					else if (((tempposx < radi/4) && (tempposx > -radi/4)) && ((tempposy < radi/4) && (tempposy > -radi/4)) && ((tempposz < radi/4) && (tempposz > -radi/4)))
					{
						SendClientMessage(i, col3, string);
					}
					else if (((tempposx < radi/2) && (tempposx > -radi/2)) && ((tempposy < radi/2) && (tempposy > -radi/2)) && ((tempposz < radi/2) && (tempposz > -radi/2)))
					{
						SendClientMessage(i, col4, string);
					}
					else if (((tempposx < radi) && (tempposx > -radi)) && ((tempposy < radi) && (tempposy > -radi)) && ((tempposz < radi) && (tempposz > -radi)))
					{
						SendClientMessage(i, col5, string);
					}
				}
				else
				{
					SendClientMessage(i, col1, string);
				}
			}
		}
	}//not connected
	return 1;
}

stock CrimInRange(Float:radi, playerid,copid)
{
	if(IsPlayerConnected(playerid)&&IsPlayerConnected(copid))
	{
		new Float:posx, Float:posy, Float:posz;
		new Float:oldposx, Float:oldposy, Float:oldposz;
		new Float:tempposx, Float:tempposy;
		GetPlayerPos(playerid, oldposx, oldposy, oldposz);
		GetPlayerPos(copid, posx, posy, posz);
		tempposx = (oldposx -posx);
		tempposy = (oldposy -posy);
		if (((tempposx < radi) && (tempposx > -radi)) && ((tempposy < radi) && (tempposy > -radi)))
		{
			return 1;
		}
	}
	return 0;
}

stock ProxDetectorS(Float:radi, playerid, targetid)
{
    if(IsPlayerConnected(playerid)&&IsPlayerConnected(targetid))
	{
		new Float:posx, Float:posy, Float:posz;
		new Float:oldposx, Float:oldposy, Float:oldposz;
		new Float:tempposx, Float:tempposy, Float:tempposz;
		GetPlayerPos(playerid, oldposx, oldposy, oldposz);
		//radi = 2.0; //Trigger Radius
		GetPlayerPos(targetid, posx, posy, posz);
		tempposx = (oldposx -posx);
		tempposy = (oldposy -posy);
		tempposz = (oldposz -posz);
		//printf("DEBUG: X:%f Y:%f Z:%f",posx,posy,posz);
		if (((tempposx < radi) && (tempposx > -radi)) && ((tempposy < radi) && (tempposy > -radi)) && ((tempposz < radi) && (tempposz > -radi)))
		{
			return 1;
		}
	}
	return 0;
}

stock PlayerToPoint(Float:radi, playerid, Float:x, Float:y, Float:z)
{
    if(IsPlayerConnected(playerid))
	{
		new Float:oldposx, Float:oldposy, Float:oldposz;
		new Float:tempposx, Float:tempposy, Float:tempposz;
		GetPlayerPos(playerid, oldposx, oldposy, oldposz);
		tempposx = (oldposx -x);
		tempposy = (oldposy -y);
		tempposz = (oldposz -z);
		//printf("DEBUG: X:%f Y:%f Z:%f",posx,posy,posz);
		if (((tempposx < radi) && (tempposx > -radi)) && ((tempposy < radi) && (tempposy > -radi)) && ((tempposz < radi) && (tempposz > -radi)))
		{
			return 1;
		}
	}
	return 0;
}

stock CustomPickups()
{
	new Float:oldposx, Float:oldposy, Float:oldposz;
	new string[128];
	NameTimer();
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i))
		{
			GetPlayerPos(i, oldposx, oldposy, oldposz);
			new tmpcar = GetPlayerVehicleID(i);
			if(oldposx!=0.0 && oldposy!=0.0 && oldposz!=0.0)
			{
				for(new h = 0; h < sizeof(SBizzInfo); h++)
				{
					if(IsATruck(tmpcar) && PlayerToPoint(10.0, i, SBizzInfo[h][sbEntranceX], SBizzInfo[h][sbEntranceY], SBizzInfo[h][sbEntranceZ]))
					{
						format(string, sizeof(string), "~w~%s~n~~r~Products Required~w~: %d~n~~y~Price per Product: ~w~: $%d~n~~g~Funds: ~w~: $%d",SBizzInfo[h][sbMessage],(SBizzInfo[h][sbMaxProducts]-SBizzInfo[h][sbProducts]),SBizzInfo[h][sbPriceProd],SBizzInfo[h][sbTill]);
						GameTextForPlayer(i, string, 5000, 3);
						return 1;
					}
					if(PlayerToPoint(2.0, i, SBizzInfo[h][sbEntranceX], SBizzInfo[h][sbEntranceY], SBizzInfo[h][sbEntranceZ]))
					{
						if(SBizzInfo[h][sbOwned] == 1)
						{
							format(string, sizeof(string), "~w~%s~w~~n~Owner : %s~n~Extortion by : %s~n~Entrance Fee : ~g~$%d ~w~Level : %d ~n~to enter type /enter",SBizzInfo[h][sbMessage],SBizzInfo[h][sbOwner],SBizzInfo[h][sbExtortion],SBizzInfo[h][sbEntranceCost],SBizzInfo[h][sbLevelNeeded]);
						}
						else
						{
							format(string, sizeof(string), "~w~%s~w~~n~This Business is for sale~n~Cost: ~g~$%d ~w~Level : %d ~n~to buy this Business type /buybiz",SBizzInfo[h][sbMessage],SBizzInfo[h][sbBuyPrice],SBizzInfo[h][sbLevelNeeded]);
						}
						GameTextForPlayer(i, string, 5000, 3);
						return 1;
					}
				}
				for(new h = 0; h < sizeof(HouseInfo); h++)
				{
					if(PlayerToPoint(2.0, i, HouseInfo[h][hEntrancex], HouseInfo[h][hEntrancey], HouseInfo[h][hEntrancez]))
					{
						if(HouseInfo[h][hOwned] == 1)
						{
							if(HouseInfo[h][hRentabil] == 0)
							{
								format(string, sizeof(string), "~w~This House is owned by~n~%s~n~Level : %d",HouseInfo[h][hOwner],HouseInfo[h][hLevel]);
							}
							else
							{
								format(string, sizeof(string), "~w~This House is owned by~n~%s~n~Rent: $%d Level : %d~n~Type /rentroom to rent a room",HouseInfo[h][hOwner],HouseInfo[h][hRent],HouseInfo[h][hLevel]);
							}
							GameTextForPlayer(i, string, 5000, 3);
							return 1;
						}
						else
						{
							format(string, sizeof(string), "~w~This House is for sale~n~Discription: %s ~n~Cost: ~g~$%d~n~~w~ Level : %d~n~to buy this house type /buyhouse",HouseInfo[h][hDiscription],HouseInfo[h][hValue],HouseInfo[h][hLevel]);
						}
						GameTextForPlayer(i, string, 5000, 3);
						return 1;
					}
				}
				for(new h = 0; h < sizeof(BizzInfo); h++)
				{
					if(IsATruck(tmpcar) && PlayerToPoint(10.0, i, BizzInfo[h][bEntranceX], BizzInfo[h][bEntranceY], BizzInfo[h][bEntranceZ]))
					{
						format(string, sizeof(string), "~w~%s~n~~r~Products Required~w~: %d~n~~y~Price per Product: ~w~: $%d~n~~g~Funds: ~w~: $%d",BizzInfo[h][bMessage],(BizzInfo[h][bMaxProducts]-BizzInfo[h][bProducts]),BizzInfo[h][bPriceProd],BizzInfo[h][bTill]);
						GameTextForPlayer(i, string, 5000, 3);
						return 1;
					}
					if(PlayerToPoint(2.0, i, BizzInfo[h][bEntranceX], BizzInfo[h][bEntranceY], BizzInfo[h][bEntranceZ]))
					{
						if(BizzInfo[h][bOwned] == 1)
						{
							format(string, sizeof(string), "~w~%s~w~~n~Owner : %s~n~Extortion by : %s~n~Entrance Fee : ~g~$%d ~w~Level : %d ~n~to enter type /enter",BizzInfo[h][bMessage],BizzInfo[h][bOwner],BizzInfo[h][bExtortion],BizzInfo[h][bEntranceCost],BizzInfo[h][bLevelNeeded]);
						}
						else
						{
							format(string, sizeof(string), "~w~%s~w~~n~This Business is for sale~n~Cost: ~g~$%d ~w~Level : %d ~n~to buy this Business type /buybiz",BizzInfo[h][bMessage],BizzInfo[h][bBuyPrice],BizzInfo[h][bLevelNeeded]);
						}
						GameTextForPlayer(i, string, 5000, 3);
						return 1;
					}
				}
			}//custompickups end
			if (PlayerToPoint(2.0, i, 1173.2563,-1323.3102,15.3943))
			{// Hospital near Ammu
				GameTextForPlayer(i, "~w~Type /healme to cure yourself", 5000, 5);
			}
			else if (PlayerToPoint(2.0, i, 2029.5945,-1404.6426,17.2512))
			{// Hospital near speedway
				GameTextForPlayer(i, "~w~Type /healme to cure yourself", 5000, 5);
			}
			else if (PlayerToPoint(2.0, i, 323.0342,1118.5804,1083.8828))
			{//Buyable Drugs for Drug Dealers
			    GameTextForPlayer(i, "~w~Type /get drugs, to get some ~r~Drugs~y~~n~Skill Level matters to price", 5000, 3);
			}
			else if (PlayerToPoint(3, i,-2162.2554,-2385.9541,30.6250))
			{
			    GameTextForPlayer(i, "~y~Welcome to the ~r~City Hall~n~~w~Type /enter to go in", 5000, 5);
			}
			else if (GetPlayerState(i) == 1 && PlayerToPoint(2.0, i,359.5408,206.7693,1008.3828))
			{
			    if(PlayerInfo[i][pJob] > 0 || PlayerInfo[i][pMember] > 0) {}
			    else { GameTextForPlayer(i, "~g~Welcome,~n~~y~you can become a ~r~Detective~y~ here ~n~~w~Type /join if you wish to become one", 5000, 3); }
			}
			else if (GetPlayerState(i) == 1 && PlayerToPoint(2.0, i,347.7374,193.7241,1014.1875))
			{
			    if(PlayerInfo[i][pJob] > 0) {}
			    else { GameTextForPlayer(i, "~g~Welcome,~n~~y~you can become a ~r~Lawyer~y~ here ~n~~w~Type /join if you wish to become one", 5000, 3); }
			}
			else if (GetPlayerState(i) == 1 && PlayerToPoint(2.0, i,1215.1304,-11.8431,1000.9219))
			{
			    if(PlayerInfo[i][pJob] > 0 || PlayerInfo[i][pMember] > 0) {}
			    else { GameTextForPlayer(i, "~g~Welcome,~n~~y~you can become a ~r~Whore~y~ here ~n~~w~Type /join if you wish to become one", 5000, 3); }
			}
			else if (GetPlayerState(i) == 1 && PlayerToPoint(2.0, i,2166.3772,-1675.3829,15.0859))
			{
			    if(PlayerInfo[i][pJob] > 0 || PlayerInfo[i][pMember] > 0) {}
			    else { GameTextForPlayer(i, "~g~Welcome,~n~~y~you can become a ~r~Drugs Dealer~y~ here ~n~~w~Type /join if you wish to become one", 5000, 3); }
			}
			else if (GetPlayerState(i) == 1 && PlayerToPoint(2.0, i,1109.3318,-1796.3042,16.5938))
			{
			    if(PlayerInfo[i][pJob] > 0) {}
			    else { GameTextForPlayer(i, "~g~Welcome,~n~~y~you can become a ~r~Car Jacker~y~ here ~n~~w~Type /join if you wish to become one", 5000, 3); }
			}
			else if (GetPlayerState(i) == 1 && PlayerToPoint(2.0, i,-2050.8962,460.0262,35.1719))
			{
			    if(PlayerInfo[i][pMember] == 9 || PlayerInfo[i][pLeader] == 9) { GameTextForPlayer(i, "~w~Type ~r~/paper ~w~to create a newspaper",5000,3); }
			    else if(PlayerInfo[i][pJob] == 15) { GameTextForPlayer(i, "~w~Type ~r~/papers ~w~to see all the made newspapers",5000, 3); }
			}
			else if (GetPlayerState(i) == 1 && PlayerToPoint(2.0, i,-1932.3859,276.2117,41.0391))
			{
			    if(PlayerInfo[i][pJob] > 0 || PlayerInfo[i][pMember] > 0) {}
			    else { GameTextForPlayer(i, "~g~Welcome,~n~~y~you can become a ~r~Car Mechanic~y~ here ~n~~w~Type /join if you wish to become one", 5000, 3); }
			}
			else if (GetPlayerState(i) == 1 && PlayerToPoint(2.0, i,2226.1716,-1718.1792,13.5165))
			{
			    if(PlayerInfo[i][pJob] > 0 || PlayerInfo[i][pMember] > 0) {}
			    else { GameTextForPlayer(i, "~g~Welcome,~n~~y~you can become a ~r~Bodyguard~y~ here ~n~~w~Type /join if you wish to become one", 5000, 3); }
			}
			else if (GetPlayerState(i) == 1 && PlayerToPoint(2.0, i,1366.4325,-1275.2096,13.5469))
			{
			    if(PlayerInfo[i][pJob] > 0 || PlayerInfo[i][pMember] > 0) {}
			    else { GameTextForPlayer(i, "~g~Welcome,~n~~y~you can become a ~r~Arms Dealer~y~ here ~n~~w~Type /join if you wish to become one", 5000, 3); }
			}
			else if (GetPlayerState(i) == 1 && PlayerToPoint(2.0, i,531.7930,-1292.4044,17.2422))
			{
			    if(PlayerInfo[i][pJob] > 0) {}
			    else { GameTextForPlayer(i, "~g~Welcome,~n~~y~you can become a ~r~Car Dealer~y~ here ~n~~w~Type /join if you wish to become one", 5000, 3); }
			}
			else if (GetPlayerState(i) == 1 && PlayerToPoint(2.0, i,766.0804,14.5133,1000.7004))
			{
			    if(PlayerInfo[i][pJob] > 0 || PlayerInfo[i][pMember] > 0) {}
			    else { GameTextForPlayer(i, "~g~Welcome,~n~~y~you can become a ~r~Boxer~y~ here ~n~~w~Type /join if you wish to become one", 5000, 3); }
			}
			else if (GetPlayerState(i) == 1 && PlayerToPoint(2.0, i,1154.2208,-1770.8203,16.5992))
			{
			    if(PlayerInfo[i][pJob] > 0 || PlayerInfo[i][pMember] > 0) {}
			    else { GameTextForPlayer(i, "~g~Welcome,~n~~y~you can become a ~r~Bus Driver~y~ here ~n~~w~Type /join if you wish to become one", 5000, 3); }
			}
			else if (GetPlayerState(i) == 1 && PlayerToPoint(2.0, i,-77.7288,-1136.3896,1.0781))
			{
			    if(PlayerInfo[i][pJob] > 0 || PlayerInfo[i][pMember] > 0) {}
			    else { GameTextForPlayer(i, "~g~Welcome,~n~~y~you can become a ~r~Trucker~y~ here ~n~~w~Type /join if you wish to become one", 5000, 3); }
			}
			else if (GetPlayerState(i) == 1 && PlayerToPoint(2.0, i,1381.0413,-1088.8511,27.3906))
			{
			    GameTextForPlayer(i, "~g~Welcome,~n~~y~Use /mission to take on a Mission", 5000, 3);
			}
			else if(PlayerToPoint(2.0, i,1073.0619,-344.5148,73.9922))
			{
			    if(OrderReady[i] > 0)
			    {
			        switch (OrderReady[i])
			        {
			            case 1:
			            {
			                GivePlayerWeapon(i, 24, 50); GivePlayerWeapon(i, 29, 500); GivePlayerWeapon(i, 25, 50); GivePlayerWeapon(i, 4, 1);
			                GivePlayerMoney(i, - 5000);
			                SendClientMessage(i, COLOR_LIGHTBLUE, "* You picked up your Ordered Package.");
			            }
			            case 2:
			            {
			                GivePlayerWeapon(i, 24, 50); GivePlayerWeapon(i, 29, 500); GivePlayerWeapon(i, 25, 50); GivePlayerWeapon(i, 31, 500); GivePlayerWeapon(i, 4, 1);
			                GivePlayerMoney(i, - 6000);
			                SendClientMessage(i, COLOR_LIGHTBLUE, "* You picked up your Ordered Package.");
			            }
			            case 3:
			            {
			                GivePlayerWeapon(i, 24, 50); GivePlayerWeapon(i, 29, 500); GivePlayerWeapon(i, 25, 50); GivePlayerWeapon(i, 30, 500); GivePlayerWeapon(i, 4, 1);
			                GivePlayerMoney(i, - 6000);
			                SendClientMessage(i, COLOR_LIGHTBLUE, "* You picked up your Ordered Package.");
			            }
			            case 4:
			            {
			                GivePlayerWeapon(i, 24, 50); GivePlayerWeapon(i, 29, 500); GivePlayerWeapon(i, 25, 50); GivePlayerWeapon(i, 31, 500); GivePlayerWeapon(i, 4, 1); GivePlayerWeapon(i, 34, 20);
			                GivePlayerMoney(i, - 8000);
			                SendClientMessage(i, COLOR_LIGHTBLUE, "* You picked up your Ordered Package.");
			            }
			            case 5:
			            {
			                GivePlayerWeapon(i, 24, 50); GivePlayerWeapon(i, 29, 500); GivePlayerWeapon(i, 25, 50); GivePlayerWeapon(i, 30, 500); GivePlayerWeapon(i, 4, 1); GivePlayerWeapon(i, 34, 20);
			                GivePlayerMoney(i, - 8000);
			                SendClientMessage(i, COLOR_LIGHTBLUE, "* You picked up your Ordered Package.");
			            }
			            case 6:
			            {
			                GivePlayerWeapon(i, 24, 50); GivePlayerWeapon(i, 29, 500); GivePlayerWeapon(i, 25, 50); GivePlayerWeapon(i, 31, 500); GivePlayerWeapon(i, 4, 1); GivePlayerWeapon(i, 34, 20);
							GivePlayerMoney(i, - 8500);
							SendClientMessage(i, COLOR_LIGHTBLUE, "* You picked up your Ordered Package.");
			            }
			            case 7:
			            {
			                GivePlayerWeapon(i, 24, 50); GivePlayerWeapon(i, 29, 500); GivePlayerWeapon(i, 25, 50); GivePlayerWeapon(i, 30, 500); GivePlayerWeapon(i, 4, 1); GivePlayerWeapon(i, 34, 20);
			                GivePlayerMoney(i, - 8500);
			                SendClientMessage(i, COLOR_LIGHTBLUE, "* You picked up your Ordered Package.");
			            }
			        }
			        OrderReady[i] = 0;
			    }
			}//Hitman delivery stuff
			else if(PlayerOnMission[i] > 0 && PlayMission[kToggle] == 0)
			{
			    if(MissionCheckpoint[i] == 1 && PlayerToPoint(10.0, i,PlayMission[kCP1][0],PlayMission[kCP1][1],PlayMission[kCP1][2]))
				{
				    RingTone[i] = 20;
				    format(string, sizeof(string), "%s", PlayMission[kGText1]);
					GameTextForPlayer(i, string, 8000, 3);
					format(string, sizeof(string), "%s", PlayMission[kText4]);
					SendClientMessage(i, COLOR_YELLOW2, string);
					format(string, sizeof(string), "%s", PlayMission[kText5]);
					SendClientMessage(i, COLOR_YELLOW2, string);
					format(string, sizeof(string), "%s", PlayMission[kText6]);
					SendClientMessage(i, COLOR_YELLOW2, string);
					MissionCheckpoint[i] = 2;
				}
				else if(MissionCheckpoint[i] == 2 && PlayerToPoint(10.0, i,PlayMission[kCP2][0],PlayMission[kCP2][1],PlayMission[kCP2][2]))
				{
				    RingTone[i] = 20;
				    format(string, sizeof(string), "%s", PlayMission[kGText2]);
					GameTextForPlayer(i, string, 8000, 3);
					format(string, sizeof(string), "%s", PlayMission[kText7]);
					SendClientMessage(i, COLOR_YELLOW2, string);
					format(string, sizeof(string), "%s", PlayMission[kText8]);
					SendClientMessage(i, COLOR_YELLOW2, string);
					format(string, sizeof(string), "%s", PlayMission[kText9]);
					SendClientMessage(i, COLOR_YELLOW2, string);
					MissionCheckpoint[i] = 3;
				}
				else if(MissionCheckpoint[i] == 3 && PlayerToPoint(10.0, i,PlayMission[kCP3][0],PlayMission[kCP3][1],PlayMission[kCP3][2]))
				{
				    RingTone[i] = 20;
				    format(string, sizeof(string), "%s", PlayMission[kGText3]);
					GameTextForPlayer(i, string, 8000, 3);
					format(string, sizeof(string), "%s", PlayMission[kText10]);
					SendClientMessage(i, COLOR_YELLOW2, string);
					format(string, sizeof(string), "%s", PlayMission[kText11]);
					SendClientMessage(i, COLOR_YELLOW2, string);
					format(string, sizeof(string), "%s", PlayMission[kText12]);
					SendClientMessage(i, COLOR_YELLOW2, string);
					MissionCheckpoint[i] = 4;
				}
				else if(MissionCheckpoint[i] == 4 && PlayerToPoint(10.0, i,PlayMission[kCP4][0],PlayMission[kCP4][1],PlayMission[kCP4][2]))
				{
				    RingTone[i] = 20;
				    format(string, sizeof(string), "%s", PlayMission[kGText4]);
					GameTextForPlayer(i, string, 8000, 3);
					format(string, sizeof(string), "%s", PlayMission[kText13]);
					SendClientMessage(i, COLOR_YELLOW2, string);
					format(string, sizeof(string), "%s", PlayMission[kText14]);
					SendClientMessage(i, COLOR_YELLOW2, string);
					format(string, sizeof(string), "%s", PlayMission[kText15]);
					SendClientMessage(i, COLOR_YELLOW2, string);
					MissionCheckpoint[i] = 5;
				}
				else if(MissionCheckpoint[i] == 5 && PlayerToPoint(10.0, i,PlayMission[kCP5][0],PlayMission[kCP5][1],PlayMission[kCP5][2]))
				{
				    RingTone[i] = 20;
				    format(string, sizeof(string), "%s", PlayMission[kGText5]);
					GameTextForPlayer(i, string, 8000, 3);
					format(string, sizeof(string), "%s", PlayMission[kText16]);
					SendClientMessage(i, COLOR_YELLOW2, string);
					format(string, sizeof(string), "%s", PlayMission[kText17]);
					SendClientMessage(i, COLOR_YELLOW2, string);
					format(string, sizeof(string), "%s", PlayMission[kText18]);
					SendClientMessage(i, COLOR_YELLOW2, string);
					MissionCheckpoint[i] = 6;
				}
				else if(MissionCheckpoint[i] == 6 && PlayerToPoint(10.0, i,PlayMission[kCP6][0],PlayMission[kCP6][1],PlayMission[kCP6][2]))
				{
				    RingTone[i] = 20;
				    format(string, sizeof(string), "%s", PlayMission[kGText6]);
					GameTextForPlayer(i, string, 8000, 3);
					format(string, sizeof(string), "..:: Mission Passed : %s | Reward received: $%d ::..", PlayMission[kTitle], PlayMission[kReward]);
					SendClientMessage(i, COLOR_GREEN, string);
					GivePlayerMoney(i, PlayMission[kReward]);
					PlayerInfo[i][pMissionNr] = PlayerOnMission[i];
					MissionCheckpoint[i] = 0;
					PlayerOnMission[i] = 0;
				}
			}
		}
	}
	return 1;
}

stock SetCamBack(playerid)
{
    if(IsPlayerConnected(playerid))
    {
		new Float:plocx,Float:plocy,Float:plocz;
		GetPlayerPos(playerid, plocx, plocy, plocz);
		SetPlayerPos(playerid, -1863.15, -21.6598, 1060.15); // Warp the player
		SetPlayerInterior(playerid,14);
	}
}

stock FixHour(hour)
{
	hour = timeshift+hour;
	if (hour < 0)
	{
		hour = hour+24;
	}
	else if (hour > 23)
	{
		hour = hour-24;
	}
	shifthour = hour;
	return 1;
}

stock AddsOn()
{
	adds=1;
	return 1;
}

stock osrp_Usage(playerid, const message[]) {
	new str[128];

	format(str, sizeof(str), "U¿yj: %s", message);
	SendClientMessage(playerid, COLOR_GRAD1, str);
}

// Stuff from old incs
stock IsNumeric(const string[])
{
	for (new i = 0, j = strlen(string); i < j; i++)
	{
		if (string[i] > '9' || string[i] < '0') return 0;
	}
	return 1;
}

stock ReturnUser(text[], playerid = INVALID_PLAYER_ID)
{
	new pos = 0;
	while (text[pos] < 0x21) // Strip out leading spaces
	{
		if (text[pos] == 0) return INVALID_PLAYER_ID; // No passed text
		pos++;
	}
	new userid = INVALID_PLAYER_ID;
	if (IsNumeric(text[pos])) // Check whole passed string
	{
		// If they have a numeric name you have a problem (although names are checked on id failure)
		userid = strval(text[pos]);
		if (userid >=0 && userid < MAX_PLAYERS)
		{
			if(!IsPlayerConnected(userid))
			{
				/*if (playerid != INVALID_PLAYER_ID)
				{
					SendClientMessage(playerid, 0xFF0000AA, "User not connected");
				}*/
				userid = INVALID_PLAYER_ID;
			}
			else
			{
				return userid; // A player was found
			}
		}
		/*else
		{
			if (playerid != INVALID_PLAYER_ID)
			{
				SendClientMessage(playerid, 0xFF0000AA, "Invalid user ID");
			}
			userid = INVALID_PLAYER_ID;
		}
		return userid;*/
		// Removed for fallthrough code
	}
	// They entered [part of] a name or the id search failed (check names just incase)
	new len = strlen(text[pos]);
	new count = 0;
	new name[MAX_PLAYER_NAME];
	for (new i = 0; i < MAX_PLAYERS; i++)
	{
		if (IsPlayerConnected(i))
		{
			GetPlayerName(i, name, sizeof (name));
			if (strcmp(name, text[pos], true, len) == 0) // Check segment of name
			{
				if (len == strlen(name)) // Exact match
				{
					return i; // Return the exact player on an exact match
					// Otherwise if there are two players:
					// Me and MeYou any time you entered Me it would find both
					// And never be able to return just Me's id
				}
				else // Partial match
				{
					count++;
					userid = i;
				}
			}
		}
	}
	if (count != 1)
	{
		if (playerid != INVALID_PLAYER_ID)
		{
			if (count)
			{
				SendClientMessage(playerid, 0xFF0000AA, "Multiple users found, please narrow earch");
			}
			else
			{
				SendClientMessage(playerid, 0xFF0000AA, "No matching user found");
			}
		}
		userid = INVALID_PLAYER_ID;
	}
	return userid; // INVALID_USER_ID for bad return
}
