/*
	Project: GodFather
	Author: MisterMagik, steeZ
	File name: timers.inc
	Date: 12.03.2026
	Modified: 12.03.2026
	Desc: Server timers.
*/

Timer:GlobalTimer[1000]() {
	new plname[MAX_PLAYER_NAME];
	new string[256];
    new Float:maxspeed = 175.0;
	new Float:oldposx, Float:oldposy, Float:oldposz;
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
            if(SafeTime[i] > 0)
			{
				SafeTime[i]--;
			}
			if(SafeTime[i] == 1)
			{
				if(gPlayerAccount[i] == 1 && gPlayerLogged[i] == 0)
				{
					
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
							if (!PlayerToPoint(6, i,1040.6,-1021.0,31.7) && house == 10001 ||!PlayerToPoint(6, i,-2720.5,217.5,4.1) && house == 10002 ||!PlayerToPoint(6, i,2644.6,-2044.9,13.3) && house == 10003)
							{
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

			foreach(new j : VehItter) {
				if(VehicleInfo[j][vSpawned]) {
					if(VehicleInfo[j][vEngine]) {
						GetVehicleHealth(j, VehicleInfo[j][vEngineHp]);

						switch(GetVehicleSpeed(j)) {
							case 1 .. 50: {
								VehicleInfo[j][vFuel] -= 0.01;
							}
							case 51 .. 90: {
								VehicleInfo[j][vFuel] -= 0.04;
							}
							case 91 .. 120: {
								VehicleInfo[j][vFuel] -= 0.05;
							}
							case 121 .. 220: {
								VehicleInfo[j][vFuel] -= 0.1;
							}
							default: {
								VehicleInfo[j][vFuel] -= 0.001;
							}
						}

						if(GetVehicleSpeed(j) > 0) {
							CountVehicleMileage(j);
						}

						if(VehicleInfo[j][vFuel] < 0.0) {
							new engine, lights, alarm, doors, bonnet, boot, objective;

							VehicleInfo[j][vFuel] = 0.0;
							VehicleInfo[j][vEngine] = false;

							GetVehicleParamsEx(j, engine, lights, alarm, doors, bonnet, boot, objective);
							SetVehicleParamsEx(j, VehicleInfo[j][vEngine], lights, alarm, doors, bonnet, boot, objective);

							if(IsPlayerInVehicle(i, j)) {
								SendClientMessage(i, COLOR_YELLOW, "Skoñczy³o Ci siê paliwo w pojeŸdzie. Silnik zosta³ wy³¹czony.");
							}
						}
					}

					if(IsPlayerInAnyVehicle(i) && GetPlayerVehicleID(i) == j) {
						new str[256];

						if(VehicleInfo[j][vLock]) {
							format(str, sizeof(str), "~g~OTWARTY");
						} else {
							format(str, sizeof(str), "~r~ZAMKNIETY");
						}

						if(VehicleInfo[j][vEngine]) {
							format(str, sizeof(str), "%s~n~~n~~w~SILNIK: ~g~ON", str);
						} else {
							format(str, sizeof(str), "%s~n~~n~~w~SILNIK: ~r~OFF", str);
						}

						format(str, sizeof(str), "%s~n~~w~DIESEL: %0.1f L~n~~n~PREDKOSC: %d KM/H~n~ PRZEBIEG: %d", str, VehicleInfo[j][vFuel], GetVehicleSpeed(j), FloatToInt(VehicleInfo[j][vMileage]));
						TextDrawSetString(VehicleStats[i], str);

						TextDrawShowForPlayer(i, VehicleStats[i]);
					}
				}
			}
		}
	}
}

Timer:SyncUp[60000]() {
	SyncTime();
	DollahScoreUpdate();
}

Timer:CarCheck[30000]() {
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

Timer:CustomPickups[1000]() {
	new Float:oldposx, Float:oldposy, Float:oldposz;
	new string[128];
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

Timer:Spectator[2000]() {
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

Timer:IdleKick[600000]() {
	foreach(new i : Player)
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

Timer:Production[300000]() {
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

Timer:SaveAccounts[1800000]() {
    for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i))
		{
			SavePlayerData(i);
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

Timer:CheckGas[15000]() {
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

Timer:StoppedVehicle[15000]() {
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
