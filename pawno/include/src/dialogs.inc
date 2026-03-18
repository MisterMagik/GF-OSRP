/*
	Project: GodFather
	Author: MisterMagik, steeZ
	File name: dialogs.inc
	Date: 12.03.2026
	Modified: 12.03.2026
	Desc: Server dialogs.
*/

sampCallback OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]) {
	if(PlayerInfo[playerid][pDialog] != dialogid) {
		return 1;
	}

	switch(dialogid) {
		case DIALOG_REGISTER_RULES: {
			if(!response) {
				return Kick(playerid);
			}

			osrp_ShowPlayerDialog(playerid, DIALOG_REGISTER_PASS, DIALOG_STYLE_PASSWORD, "Zarejestruj:", "{FFFFFF}To konto nie jest jeszcze zarejestrowane.\nWpisz has³o, aby siê zarejestrowaæ.", "Zarejestruj", "WyjdŸ");
		}
		case DIALOG_REGISTER_PASS: {
			if(!response) {
				return Kick(playerid);
			}

			if(strlen(inputtext) < 2 || strlen(inputtext) > 32) {
				return osrp_ShowPlayerDialog(playerid, DIALOG_REGISTER_PASS, DIALOG_STYLE_PASSWORD, "Zarejestruj:", "{FFFFFF}Podane has³o jest nieprawid³owe.\nTo konto nie jest jeszcze zarejestrowane.\nWpisz has³o, aby siê zarejestrowaæ.", "Zarejestruj", "WyjdŸ");
			}

			new day, month, year, second, minute, hour;
			new date[64], IP[16];

			gettime(hour, minute, second);
			getdate(year, month, day);

			format(date, sizeof(date), "%02d/%02d/%03d %02d:%02d:%02d", day, month, year, hour, minute, second);
			format(playerSalt[playerid], 17, GeneratePasswordSalt());

			SHA256_PassHash(inputtext, playerSalt[playerid], playerPass[playerid], 65);
			GetPlayerIp(playerid, IP, sizeof(IP));

			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "INSERT INTO `Accounts` (`Name`, `Password`, `Salt`, `IP`, `Date`, `LastDate`) VALUES ('%s', '%s', '%s', '%s', '%s', '%s')",
				oocName[playerid],
				playerPass[playerid],
				playerSalt[playerid],
				IP,
				date,
				date
				);
			mysql_query(queryStr);

			gPlayerAccount[playerid] = 1;
			SendClientMessage(playerid, COLOR_YELLOW, "Konto zosta³o zarejestrowane. Jeœli chcesz zwiekszyæ bezpieczeñstwo konta podepnij swój email na www.osrp.pl");

			mainStr[0] = EOS;
			strcat(mainStr, "{FFFFFF}Pomyœlnie zarejestrowa³eœ konto.\nMo¿esz teraz wpisaæ nazwe konta osoby, która poleci³a Ci ten serwer.\n");
			strcat(mainStr, "Dostanie ona nagrody gdy osi¹gniesz odpowiedni poziom.\n");
			strcat(mainStr, "Mo¿esz pomin¹æ ten etap jeœli nie ma takiej osoby.");
			osrp_ShowPlayerDialog(playerid, DIALOG_REGISTER_RECOMMENDER, DIALOG_STYLE_INPUT, "Osoba polecaj¹ca:", mainStr, "Ok", "Pomiñ");
		}
		case DIALOG_REGISTER_RECOMMENDER: {
			if(!response) {
				return osrp_ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_PASSWORD, "Zaloguj:", "{FFFFFF}Pomyœlnie zarejestrowa³eœ konto.\nProsze wpisaæ has³o, aby siê teraz zalogowaæ.", "Zaloguj", "WyjdŸ");
			}

			osrp_ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_PASSWORD, "Zaloguj:", "{FFFFFF}Pomyœlnie zarejestrowa³eœ konto.\nProsze wpisaæ has³o, aby siê teraz zalogowaæ.", "Zaloguj", "WyjdŸ");
		}
		case DIALOG_LOGIN: {
			if(!response) {
				return Kick(playerid);
			}

			new hash[64];

			SHA256_PassHash(inputtext, playerSalt[playerid], hash, sizeof(hash));

			if(!strcmp(hash, playerPass[playerid], false)) {
				SendClientMessage(playerid, COLOR_YELLOW, "Witaj na serwerze Old School Role Play.");

				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "Serwer: Pomyœlnie zalogowa³eœ siê na konto %s.", oocName[playerid]);
				SendClientMessage(playerid, COLOR_YELLOW, mainStr);

				gPlayerLogged[playerid] = 1;

				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "Opcje konta %s:", oocName[playerid]);
				osrp_ShowPlayerDialog(playerid, DIALOG_ACCOUNT_OPTIONS, DIALOG_STYLE_LIST, mainStr, "{FFFFFF}Zaloguj siê na postaæ\nStwórz now¹ postaæ\nUsuñ istniej¹c¹ postaæ\nAnty Crash\nZmieñ has³o do konta", "Dalej", "");
			} else {
				osrp_ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_PASSWORD, "Zaloguj:", "{FFFFFF}Pomyœlnie zarejestrowa³eœ konto.\nProsze wpisaæ has³o, aby siê teraz zalogowaæ.", "Zaloguj", "WyjdŸ");
			}
		}
		case DIALOG_ACCOUNT_OPTIONS: {
			switch(listitem) {
				case 0: {
					queryStr[0] = EOS;
					format(queryStr, sizeof(queryStr), "SELECT `Name`, `Respect` FROM `Characters` WHERE `AID` = '%d'", accountID[playerid]);
					mysql_query(queryStr);

					mysql_store_result();

					enum Character {
						Name[24],
						Hours
					};

					new Characters[MAX_PLAYER_CHARS][Character];
					new count, charStr[128];

					if(mysql_result_stored()) {
						while(mysql_fetch_row(queryStr, "|")) {
							sscanf(queryStr, "p<|>s[24]i", Characters[count][Name], Characters[count][Hours]);
							format(charStr, sizeof(charStr), "%s\n{FFFFFF}", charStr, Characters[count][Name], Characters[count][Hours]);

							count++;
						}

						mysql_free_result();

						if(!count) {
							return 1;
						}

						mainStr[0] = EOS;
						format(mainStr, sizeof(mainStr), "Postacie konta %s:", oocName[playerid]);
						osrp_ShowPlayerDialog(playerid, DIALOG_ACCOUNT_CHARACTERS, DIALOG_STYLE_LIST, mainStr, "{FFFFFF}Zaloguj siê na postaæ\nStwórz now¹ postaæ\nUsuñ istniej¹c¹ postaæ\nAnty Crash\nZmieñ has³o do konta", "Zaloguj", "Cofnij");
					}
				}
				case 1: {
					osrp_ShowPlayerDialog(playerid, DIALOG_ACCOUNT_CREATE_CHAR, DIALOG_STYLE_INPUT, "Tworzenie nowej postaci:", "{FFFFFF}Wpisz imiê i nazwisko postaci, któr¹ chcesz stworzyæ.\nWzór: Imiê_Nazwisko", "Dalej", "Cofnij");
				}
				case 2: {
					
				}
				case 3: {
					
				}
				case 4: {
					
				}
			}
		}
		case DIALOG_ACCOUNT_CREATE_CHAR: {
			if(!response) {
				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "Opcje konta %s:", oocName[playerid]);
				return osrp_ShowPlayerDialog(playerid, DIALOG_ACCOUNT_OPTIONS, DIALOG_STYLE_LIST, mainStr, "{FFFFFF}Zaloguj siê na postaæ\nStwórz now¹ postaæ\nUsuñ istniej¹c¹ postaæ\nAnty Crash\nZmieñ has³o do konta", "Dalej", "");
			}

			osrp_ShowPlayerDialog(playerid, DIALOG_ACCOUNT_CHAR_AGE, DIALOG_STYLE_INPUT, "Wybierz wiek swojej postaci:", "{FFFFFF}Wpisz wiek z przedzia³u od 18 do 65 lat.", "Dalej", "Cofnij");
		}
		case DIALOG_ACCOUNT_CHAR_AGE: {
			if(!response) {
				
			}

			new age = strval(inputtext);
			PlayerInfo[playerid][pAge] = age;

			osrp_ShowPlayerDialog(playerid, DIALOG_ACCOUNT_CHAR_CONTINENT, DIALOG_STYLE_LIST, "Wybierz kontynent z którego pochodzi Twoja postaæ:", "{FFFFFF}Ameryka\nEuropa\nAustralia\nAzja\nAfryka", "Dalej", "Cofnij");
		}
		case DIALOG_ACCOUNT_CHAR_CONTINENT: {
			if(!response) {
				
			}

			new origin = strval(inputtext);
			PlayerInfo[playerid][pOrigin] = origin;

			osrp_ShowPlayerDialog(playerid, DIALOG_ACCOUNT_CHAR_ORIGIN, DIALOG_STYLE_LIST, "Wybierz rasê Twojej postaci:", "{FFFFFF}Bia³a\nCzarna\n¯ó³ta", "Dalej", "Cofnij");
		}
		case DIALOG_ACCOUNT_CHAR_ORIGIN: {
			if(!response) {
				
			}

			new origin = strval(inputtext);
			PlayerInfo[playerid][pOrigin] = origin;

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "SprawdŸ czy dane podane poni¿ej siê zgadzaj¹:\n\nNick: %s\nP³eæ: %s\nWiek: %d\nPochodzenie: %s\nRasa: %s");
			osrp_ShowPlayerDialog(playerid, DIALOG_ACCOUNT_CHAR_SUMMARY, DIALOG_STYLE_LIST, "Podsumowanie:", "{FFFFFF}Bia³a\nCzarna\n¯ó³ta", "Stwórz", "Cofnij");
		}
		case DIALOG_ACCOUNT_CHAR_SUMMARY: {
			if(!response) {
				
			}

			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "SELECT `ID` FROM `Accounts` WHERE `Name` = '%s' LIMIT 1", oocName[playerid]);
			mysql_query(queryStr);

			mysql_store_result();

			if(mysql_result_stored()) {
				accountID[playerid] = mysql_fetch_int();
				mysql_free_result();

				queryStr[0] = EOS;
				format(queryStr, sizeof(queryStr), "INSERT INTO `Accounts` (`AID`, `Name`, `Registered`, `Sex`, `Age`, `Continent`, `Origin`) VALUES ('%d', '%s', '%d', '%d', '%d', '%d', '%d')",
					accountID[playerid],
					PlayerInfo[playerid][pName],
					gPlayerAccount[playerid],
					PlayerInfo[playerid][pSex],
					PlayerInfo[playerid][pAge],
					PlayerInfo[playerid][pContinent],
					PlayerInfo[playerid][pOrigin]
				);
				mysql_query(queryStr);

				SendClientMessage(playerid, COLOR_YELLOW, "Postaæ zosta³a pomyœlnie stworzona. Teraz mo¿esz siê na ni¹ zalogowaæ.");

				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "Opcje konta %s:", oocName[playerid]);
				osrp_ShowPlayerDialog(playerid, DIALOG_ACCOUNT_OPTIONS, DIALOG_STYLE_LIST, mainStr, "{FFFFFF}Zaloguj siê na postaæ\nStwórz now¹ postaæ\nUsuñ istniej¹c¹ postaæ\nAnty Crash\nZmieñ has³o do konta", "Dalej", "");
			}
		}
	}
	return 1;
}
