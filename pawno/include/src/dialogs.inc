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

			if(strlen(inputtext) < 4 || strlen(inputtext) > 32) {
				return osrp_ShowPlayerDialog(playerid, DIALOG_REGISTER_PASS, DIALOG_STYLE_PASSWORD, "Zarejestruj:", "{AA3333}Podane has³o jest nieprawid³owe.\n{FFFFFF}To konto nie jest jeszcze zarejestrowane.\nWpisz has³o, aby siê zarejestrowaæ.", "Zarejestruj", "WyjdŸ");
			}

			if(strfind(inputtext, " ", true) != -1) {
				return osrp_ShowPlayerDialog(playerid, DIALOG_REGISTER_PASS, DIALOG_STYLE_PASSWORD, "Zarejestruj:", "{AA3333}Podane has³o zawiera spacjê.\n{FFFFFF}To konto nie jest jeszcze zarejestrowane.\nWpisz has³o, aby siê zarejestrowaæ.", "Zarejestruj", "WyjdŸ");
			}

			new Day, Month, Year, Second, Minute, Hour;
			new Date[64], IP[16];

			gettime(Hour, Minute, Second);
			getdate(Year, Month, Day);

			format(Date, sizeof(Date), "%02d/%02d/%03d %02d:%02d:%02d", Day, Month, Year, Hour, Minute, Second);
			format(accSalt[playerid], 17, "%s", GeneratePasswordSalt());

			SHA256_PassHash(inputtext, accSalt[playerid], accPassword[playerid], 65);
			GetPlayerIp(playerid, IP, sizeof(IP));

			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "INSERT INTO `Accounts` (`Name`, `Password`, `Salt`, `IP`, `Date`, `LastDate`) VALUES ('%s', '%s', '%s', '%s', '%s', '%s')",
				accName[playerid],
				accPassword[playerid],
				accSalt[playerid],
				IP,
				Date,
				Date
				);
			mysql_query(queryStr);

			gPlayerAccount[playerid] = 1;
			SendClientMessage(playerid, COLOR_YELLOW, "Konto zosta³o zarejestrowane. Jeœli chcesz zwiekszyæ bezpieczeñstwo konta podepnij swój email na "WEBSITE_URL"");

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

			new RecommenderName[24];

			mysql_real_escape_string(inputtext, RecommenderName);

			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "SELECT * FROM `Accounts` WHERE `Name` = '%s' LIMIT 1", RecommenderName);
			mysql_query(queryStr);

			mysql_store_result();

			if(mysql_result_stored()) {
				if(mysql_num_rows() > 0) {
					queryStr[0] = EOS;
					format(queryStr, sizeof(queryStr), "UPDATE `Accounts` SET `Recommender` = '%s' WHERE `Name` = '%s'", escapedName[playerid]);
					mysql_query(queryStr);

					queryStr[0] = EOS;
					format(queryStr, sizeof(queryStr), "UPDATE `Accounts` SET `PendingPP` = '%d' WHERE `Name` = '%s'", RECOMMENDER_PRIZE, RecommenderName);
					mysql_query(queryStr);

					osrp_ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_PASSWORD, "Zaloguj:", "{FFFFFF}Pomyœlnie zarejestrowa³eœ konto.\nProsze wpisaæ has³o, aby siê teraz zalogowaæ.", "Zaloguj", "WyjdŸ");
				} else {
					mainStr[0] = EOS;
					strcat(mainStr, "{AA3333}Podana osoba nie istnieje.\n{FFFFFF}Pomyœlnie zarejestrowa³eœ konto.\nMo¿esz teraz wpisaæ nazwe konta osoby, która poleci³a Ci ten serwer.\n");
					strcat(mainStr, "Dostanie ona nagrody gdy osi¹gniesz odpowiedni poziom.\n");
					strcat(mainStr, "Mo¿esz pomin¹æ ten etap jeœli nie ma takiej osoby.");
					osrp_ShowPlayerDialog(playerid, DIALOG_REGISTER_RECOMMENDER, DIALOG_STYLE_INPUT, "Osoba polecaj¹ca:", mainStr, "Ok", "Pomiñ");
				}

				mysql_free_result();
			}
		}
		case DIALOG_LOGIN: {
			if(!response) {
				return Kick(playerid);
			}

			new Hash[65];

			SHA256_PassHash(inputtext, accSalt[playerid], Hash, sizeof(Hash) - 1);

			if(!strcmp(Hash, accPassword[playerid], false)) {
				SendClientMessage(playerid, COLOR_YELLOW, motd);

				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "Serwer: Pomyœlnie zalogowa³eœ siê na konto %s.", accName[playerid]);
				SendClientMessage(playerid, COLOR_YELLOW, mainStr);

				queryStr[0] = EOS;
				format(queryStr, sizeof(queryStr), "SELECT `ID` FROM `Accounts` WHERE `Name` = '%s' LIMIT 1", escapedName[playerid]);
				mysql_query(queryStr);

				mysql_store_result();

				if(mysql_result_stored()) {
					PlayerInfo[playerid][pAID] = mysql_fetch_int();
					mysql_free_result();
				}

				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "Opcje konta %s:", accName[playerid]);
				osrp_ShowPlayerDialog(playerid, DIALOG_ACCOUNT_OPTIONS, DIALOG_STYLE_LIST, mainStr, "{FFFFFF}Zaloguj siê na postaæ\nStwórz now¹ postaæ\nUsuñ istniej¹c¹ postaæ\nAnty Crash\nZmieñ has³o do konta", "Dalej", "");
			} else {
				if(gPlayerLogTries[playerid] > 1) {
					gPlayerLogTries[playerid]--;

					mainStr[0] = EOS;
					format(mainStr, sizeof(mainStr), "Serwer: Pozosta³o prób logowania: %d.", gPlayerLogTries[playerid]);
					SendClientMessage(playerid, COLOR_WHITE, mainStr);

					osrp_ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_PASSWORD, "Zaloguj:", "{FFFFFF}To konto ju¿ istnieje.\nWpisz has³o, aby siê zalogowaæ.", "Zaloguj", "WyjdŸ");

					if(gPlayerLogTries[playerid] == 3) {
						SendClientMessage(playerid, COLOR_WHITE, "Jeœli masz przypisany adres email do tego konta to mo¿esz odzyskaæ has³o w panelu gracza na www.osrp.pl");
					}
				} else {
					gPlayerLogTries[playerid] = 0;
					Kick(playerid);
				}
			}
		}
		case DIALOG_ACCOUNT_OPTIONS: {
			enum Character {
				Name[24],
				Date[32],
				Hours
			};

			new Characters[MAX_PLAYER_CHARS][Character];
			new Count, CharStr[512];

			switch(listitem) {
				case 0: {
					queryStr[0] = EOS;
					format(queryStr, sizeof(queryStr), "SELECT `Name`, `Respect` FROM `Characters` WHERE `AID` = '%d'", PlayerInfo[playerid][pAID]);
					mysql_query(queryStr);

					mysql_store_result();

					if(mysql_result_stored()) {
						while(mysql_fetch_row(queryStr, "|")) {
							sscanf(queryStr, "p<|>s[24]i", Characters[Count][Name], Characters[Count][Hours]);
							format(CharStr, sizeof(CharStr), "%s\n{FFFFFF}%s (%d przegranych godzin)", CharStr, Characters[Count][Name], Characters[Count][Hours]);

							Count++;
						}

						mysql_free_result();

						if(!Count) {
							SendClientMessage(playerid, COLOR_WHITE, "Serwer: Twoje konto nie posiada ¿adnej postaci. Musisz jak¹œ stworzyæ.");

							mainStr[0] = EOS;
							format(mainStr, sizeof(mainStr), "Opcje konta %s:", accName[playerid]);
							return osrp_ShowPlayerDialog(playerid, DIALOG_ACCOUNT_OPTIONS, DIALOG_STYLE_LIST, mainStr, "{FFFFFF}Zaloguj siê na postaæ\nStwórz now¹ postaæ\nUsuñ istniej¹c¹ postaæ\nAnty Crash\nZmieñ has³o do konta", "Dalej", "");
						} else if(Count == 5) {
							mainStr[0] = EOS;
							format(mainStr, sizeof(mainStr), "Serwer: Wykorzysta³eœ limit tworzenia postaci (%d).", MAX_PLAYER_CHARS);
							SendClientMessage(playerid, COLOR_WHITE, mainStr);

							mainStr[0] = EOS;
							format(mainStr, sizeof(mainStr), "Opcje konta %s:", accName[playerid]);
							return osrp_ShowPlayerDialog(playerid, DIALOG_ACCOUNT_OPTIONS, DIALOG_STYLE_LIST, mainStr, "{FFFFFF}Zaloguj siê na postaæ\nStwórz now¹ postaæ\nUsuñ istniej¹c¹ postaæ\nAnty Crash\nZmieñ has³o do konta", "Dalej", "");
						}

						mainStr[0] = EOS;
						format(mainStr, sizeof(mainStr), "Postacie konta %s:", accName[playerid]);
						osrp_ShowPlayerDialog(playerid, DIALOG_ACCOUNT_CHARACTERS, DIALOG_STYLE_LIST, mainStr, CharStr, "Zaloguj", "Cofnij");
					}
				}
				case 1: {
					osrp_ShowPlayerDialog(playerid, DIALOG_ACCOUNT_CREATE_CHAR, DIALOG_STYLE_INPUT, "Tworzenie nowej postaci:", "{FFFFFF}Wpisz imiê i nazwisko postaci, któr¹ chcesz stworzyæ.\nWzór: Imiê_Nazwisko", "Dalej", "Cofnij");
				}
				case 2: {
					queryStr[0] = EOS;
					format(queryStr, sizeof(queryStr), "SELECT `Name`, `Date` FROM `Characters` WHERE `AID` = '%d'", PlayerInfo[playerid][pAID]);
					mysql_query(queryStr);

					mysql_store_result();

					if(mysql_result_stored()) {
						while(mysql_fetch_row(queryStr, "|")) {
							sscanf(queryStr, "p<|>s[24]s[32]", Characters[Count][Name], Characters[Count][Date]);
							format(CharStr, sizeof(CharStr), "%s\n{FFFFFF}%s (Ostatnia wizyta: %s)", CharStr, Characters[Count][Name], Characters[Count][Date]);

							Count++;
						}

						mysql_free_result();

						if(!Count) {
							SendClientMessage(playerid, COLOR_WHITE, "Serwer: Twoje konto nie posiada ¿adnej postaci do usuniêcia.");

							mainStr[0] = EOS;
							format(mainStr, sizeof(mainStr), "Opcje konta %s:", accName[playerid]);
							return osrp_ShowPlayerDialog(playerid, DIALOG_ACCOUNT_OPTIONS, DIALOG_STYLE_LIST, mainStr, "{FFFFFF}Zaloguj siê na postaæ\nStwórz now¹ postaæ\nUsuñ istniej¹c¹ postaæ\nAnty Crash\nZmieñ has³o do konta", "Dalej", "");
						}

						mainStr[0] = EOS;
						format(mainStr, sizeof(mainStr), "Postacie konta %s:", accName[playerid]);
						osrp_ShowPlayerDialog(playerid, DIALOG_ACCOUNT_REMOVE_CHAR_INFO, DIALOG_STYLE_LIST, mainStr, CharStr, "Usuñ", "Cofnij");
					}
				}
				case 3: {
					if(!accAntiCrash[playerid]) {
						accAntiCrash[playerid] = true;

						queryStr[0] = EOS;
						format(queryStr, sizeof(queryStr), "UPDATE `Accounts` SET `AntiCrash` = '%d' WHERE `Name` = '%s'", accAntiCrash[playerid], escapedName[playerid]);
						mysql_query(queryStr);

						SendClientMessage(playerid, COLOR_YELLOW, "Funkcja Anty Crash zosta³a pomyœlnie w³¹czona. Mo¿e pomóc Ci w póŸniejszych crashach gry.");
					} else {
						SendClientMessage(playerid, COLOR_YELLOW, "Masz ju¿ w³¹czon¹ tê opcjê.");
					}

					mainStr[0] = EOS;
					format(mainStr, sizeof(mainStr), "Opcje konta %s:", accName[playerid]);
					osrp_ShowPlayerDialog(playerid, DIALOG_ACCOUNT_OPTIONS, DIALOG_STYLE_LIST, mainStr, "{FFFFFF}Zaloguj siê na postaæ\nStwórz now¹ postaæ\nUsuñ istniej¹c¹ postaæ\nAnty Crash\nZmieñ has³o do konta", "Dalej", "");
				}
				case 4: {
					osrp_ShowPlayerDialog(playerid, DIALOG_ACCOUNT_CHANGE_PASS, DIALOG_STYLE_PASSWORD, "Zmiana has³a:", "{FFFFFF}Wpisz nowe has³o do swojego konta.\nMo¿esz je zmieniæ tylko raz.", "Dalej", "Cofnij");
				}
			}
		}
		case DIALOG_ACCOUNT_CHARACTERS: {
			if(!response) {
				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "Opcje konta %s:", accName[playerid]);
				return osrp_ShowPlayerDialog(playerid, DIALOG_ACCOUNT_OPTIONS, DIALOG_STYLE_LIST, mainStr, "{FFFFFF}Zaloguj siê na postaæ\nStwórz now¹ postaæ\nUsuñ istniej¹c¹ postaæ\nAnty Crash\nZmieñ has³o do konta", "Dalej", "");
			}

			if(strlen(inputtext)) {
				new Name[24], Tmp[64];

				sscanf(inputtext, "s[24]s[64]", Name, Tmp);
				printf("Login: %s", Name);

				OnPlayerLogin(playerid, Name);
			}
		}
		case DIALOG_ACCOUNT_CREATE_CHAR: {
			if(!response) {
				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "Opcje konta %s:", accName[playerid]);
				return osrp_ShowPlayerDialog(playerid, DIALOG_ACCOUNT_OPTIONS, DIALOG_STYLE_LIST, mainStr, "{FFFFFF}Zaloguj siê na postaæ\nStwórz now¹ postaæ\nUsuñ istniej¹c¹ postaæ\nAnty Crash\nZmieñ has³o do konta", "Dalej", "");
			}

			if(strlen(inputtext) < 4) {
				return osrp_ShowPlayerDialog(playerid, DIALOG_ACCOUNT_CREATE_CHAR, DIALOG_STYLE_INPUT, "Tworzenie nowej postaci:", "{AA3333}Poda³eœ za krótkie imiê b¹dŸ nazwisko.\n{FFFFFF}Wpisz imiê i nazwisko postaci, któr¹ chcesz stworzyæ.\nWzór: Imiê_Nazwisko", "Dalej", "Cofnij");
			}

			if(strfind(inputtext, "_", false) == -1) {
				return osrp_ShowPlayerDialog(playerid, DIALOG_ACCOUNT_CREATE_CHAR, DIALOG_STYLE_INPUT, "Tworzenie nowej postaci:", "{AA3333}Brak znaku (_) w imieniu.\n{FFFFFF}Wpisz imiê i nazwisko postaci, któr¹ chcesz stworzyæ.\nWzór: Imiê_Nazwisko", "Dalej", "Cofnij");
			}

			new Name[24];

			mysql_real_escape_string(inputtext, Name);

			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "SELECT * FROM `Characters` WHERE `Name` = '%s' LIMIT 1", Name);
			mysql_query(queryStr);

			mysql_store_result();

			if(mysql_result_stored()) {
				if(mysql_num_rows() > 0) {
					osrp_ShowPlayerDialog(playerid, DIALOG_ACCOUNT_CREATE_CHAR, DIALOG_STYLE_INPUT, "Tworzenie nowej postaci:", "{AA3333}Podana postaæ ju¿ istnieje. Zmieñ dane na jakieœ inne.\n{FFFFFF}Wpisz imiê i nazwisko postaci, któr¹ chcesz stworzyæ.\nWzór: Imiê_Nazwisko", "Dalej", "Cofnij");
				} else {
					format(PlayerInfo[playerid][pName], 24, inputtext);
					osrp_ShowPlayerDialog(playerid, DIALOG_ACCOUNT_CHAR_SEX, DIALOG_STYLE_LIST, "Wybierz p³eæ Twojej postaci:", "{FFFFFF}Mê¿czyzna\nKobieta", "Dalej", "Cofnij");
				}

				mysql_free_result();
			}
		}
		case DIALOG_ACCOUNT_REMOVE_CHAR_INFO: {
			if(!response) {
				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "Opcje konta %s:", accName[playerid]);
				return osrp_ShowPlayerDialog(playerid, DIALOG_ACCOUNT_OPTIONS, DIALOG_STYLE_LIST, mainStr, "{FFFFFF}Zaloguj siê na postaæ\nStwórz now¹ postaæ\nUsuñ istniej¹c¹ postaæ\nAnty Crash\nZmieñ has³o do konta", "Dalej", "");
			}

			new Name[24], Tmp[64];

			sscanf(inputtext, "s[24]s[64]", Name, Tmp);
			format(PlayerInfo[playerid][pName], 24, Name);

			osrp_ShowPlayerDialog(playerid, DIALOG_ACCOUNT_REMOVE_CHAR, DIALOG_STYLE_MSGBOX, "Usuniêcie postaci:", "{FFFFFF}Czy napewno chcesz usun¹æ swoj¹ postaæ?\nNie bêdziesz móg³ ju¿ nigdy ni¹ zagraæ.\nJej maj¹tek zostanie bezpowrotnie usuniêty.\n{AA3333}Zastanów siê nad t¹ decyzj¹.", "Tak", "Nie");
		}
		case DIALOG_ACCOUNT_REMOVE_CHAR: {
			if(!response) {
				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "Opcje konta %s:", accName[playerid]);
				return osrp_ShowPlayerDialog(playerid, DIALOG_ACCOUNT_OPTIONS, DIALOG_STYLE_LIST, mainStr, "{FFFFFF}Zaloguj siê na postaæ\nStwórz now¹ postaæ\nUsuñ istniej¹c¹ postaæ\nAnty Crash\nZmieñ has³o do konta", "Dalej", "");
			}

			new Name[24];

			mysql_real_escape_string(PlayerInfo[playerid][pName], Name);

			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "DELETE FROM `Characters` WHERE `Name` = '%s'", Name);
			mysql_query(queryStr);

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "Pomyœlnie usun¹³eœ postaæ: %s.", PlayerInfo[playerid][pName]);
			SendClientMessage(playerid, COLOR_YELLOW, mainStr);

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "Opcje konta %s:", accName[playerid]);
			osrp_ShowPlayerDialog(playerid, DIALOG_ACCOUNT_OPTIONS, DIALOG_STYLE_LIST, mainStr, "{FFFFFF}Zaloguj siê na postaæ\nStwórz now¹ postaæ\nUsuñ istniej¹c¹ postaæ\nAnty Crash\nZmieñ has³o do konta", "Dalej", "");
		}
		case DIALOG_ACCOUNT_CHANGE_PASS: {
			if(!response) {
				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "Opcje konta %s:", accName[playerid]);
				return osrp_ShowPlayerDialog(playerid, DIALOG_ACCOUNT_OPTIONS, DIALOG_STYLE_LIST, mainStr, "{FFFFFF}Zaloguj siê na postaæ\nStwórz now¹ postaæ\nUsuñ istniej¹c¹ postaæ\nAnty Crash\nZmieñ has³o do konta", "Dalej", "");
			}

			if(strlen(inputtext) < 4 || strlen(inputtext) > 32) {
				return osrp_ShowPlayerDialog(playerid, DIALOG_ACCOUNT_CHANGE_PASS, DIALOG_STYLE_PASSWORD, "Zmiana has³a:", "{AA3333}Podane has³o jest nieprawid³owe.\n{FFFFFF}Wpisz nowe has³o do swojego konta.\nMo¿esz je zmieniæ tylko raz.", "Dalej", "Cofnij");
			}

			if(strfind(inputtext, " ", true) != -1) {
				return osrp_ShowPlayerDialog(playerid, DIALOG_ACCOUNT_CHANGE_PASS, DIALOG_STYLE_PASSWORD, "Zmiana has³a:", "{AA3333}Podane has³o zawiera spacjê.\n{FFFFFF}Wpisz nowe has³o do swojego konta.\nMo¿esz je zmieniæ tylko raz.", "Dalej", "Cofnij");
			}

			format(accSalt[playerid], 17, GeneratePasswordSalt());
			SHA256_PassHash(inputtext, accSalt[playerid], accPassword[playerid], 65);

			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "UPDATE `Accounts` SET `Password` = '%s', `Salt` = '%s' WHERE `Name` = '%s'",
				accPassword[playerid],
				accSalt[playerid],
				escapedName[playerid]
			);
			mysql_query(queryStr);

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "Pomyœlnie zmieni³eœ swoje has³o na %s. Zapamiêtaj je.", inputtext);
			SendClientMessage(playerid, COLOR_YELLOW, mainStr);

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "Opcje konta %s:", accName[playerid]);
			osrp_ShowPlayerDialog(playerid, DIALOG_ACCOUNT_OPTIONS, DIALOG_STYLE_LIST, mainStr, "{FFFFFF}Zaloguj siê na postaæ\nStwórz now¹ postaæ\nUsuñ istniej¹c¹ postaæ\nAnty Crash\nZmieñ has³o do konta", "Dalej", "");
		}
		case DIALOG_ACCOUNT_CHAR_SEX: {
			if(!response) {
				format(PlayerInfo[playerid][pName], 24, "Brak");
				return osrp_ShowPlayerDialog(playerid, DIALOG_ACCOUNT_CREATE_CHAR, DIALOG_STYLE_INPUT, "Tworzenie nowej postaci:", "{FFFFFF}Wpisz imiê i nazwisko postaci, któr¹ chcesz stworzyæ.\nWzór: Imiê_Nazwisko", "Dalej", "Cofnij");
			}

			new Sex = listitem;

			PlayerInfo[playerid][pSex] = Sex;

			osrp_ShowPlayerDialog(playerid, DIALOG_ACCOUNT_CHAR_AGE, DIALOG_STYLE_INPUT, "Wybierz wiek swojej postaci:", "{FFFFFF}Wpisz wiek z przedzia³u od 18 do 65 lat.", "Dalej", "Cofnij");
		}
		case DIALOG_ACCOUNT_CHAR_AGE: {
			if(!response) {
				PlayerInfo[playerid][pSex] = -1;
				return osrp_ShowPlayerDialog(playerid, DIALOG_ACCOUNT_CHAR_SEX, DIALOG_STYLE_LIST, "Wybierz p³eæ Twojej postaci:", "{FFFFFF}Mê¿czyzna\nKobieta", "Dalej", "Cofnij");
			}

			new Age = strval(inputtext);

			if(Age > 65 || Age < 18) {
				return osrp_ShowPlayerDialog(playerid, DIALOG_ACCOUNT_CHAR_AGE, DIALOG_STYLE_INPUT, "Wybierz wiek swojej postaci:", "{AA3333}Podany wiek jest nieprawid³owy.\n{FFFFFF}Wpisz wiek z przedzia³u od 18 do 65 lat.", "Dalej", "Cofnij");
			}

			PlayerInfo[playerid][pAge] = Age;

			osrp_ShowPlayerDialog(playerid, DIALOG_ACCOUNT_CHAR_CONTINENT, DIALOG_STYLE_LIST, "Wybierz kontynent z którego pochodzi Twoja postaæ:", "{FFFFFF}Ameryka\nEuropa\nAustralia\nAzja\nAfryka", "Dalej", "Cofnij");
		}
		case DIALOG_ACCOUNT_CHAR_CONTINENT: {
			if(!response) {
				PlayerInfo[playerid][pAge] = 0;
				return osrp_ShowPlayerDialog(playerid, DIALOG_ACCOUNT_CHAR_AGE, DIALOG_STYLE_INPUT, "Wybierz wiek swojej postaci:", "{FFFFFF}Wpisz wiek z przedzia³u od 18 do 65 lat.", "Dalej", "Cofnij");
			}

			new Continent = listitem;

			PlayerInfo[playerid][pContinent] = Continent;

			osrp_ShowPlayerDialog(playerid, DIALOG_ACCOUNT_CHAR_ORIGIN, DIALOG_STYLE_LIST, "Wybierz rasê Twojej postaci:", "{FFFFFF}Bia³a\nCzarna\n¯ó³ta", "Dalej", "Cofnij");
		}
		case DIALOG_ACCOUNT_CHAR_ORIGIN: {
			if(!response) {
				PlayerInfo[playerid][pContinent] = -1;
				return osrp_ShowPlayerDialog(playerid, DIALOG_ACCOUNT_CHAR_CONTINENT, DIALOG_STYLE_LIST, "Wybierz kontynent z którego pochodzi Twoja postaæ:", "{FFFFFF}Ameryka\nEuropa\nAustralia\nAzja\nAfryka", "Dalej", "Cofnij");
			}

			new Origin = listitem;

			PlayerInfo[playerid][pOrigin] = Origin;

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "{AA3333}SprawdŸ czy dane podane poni¿ej siê zgadzaj¹:\n\n{BDCB92}Nick: {FFFFFF}%s\n{BDCB92}P³eæ: {FFFFFF}%s\n{BDCB92}Wiek: {FFFFFF}%d\n{BDCB92}Pochodzenie: {FFFFFF}%s\n{BDCB92}Rasa: {FFFFFF}%s",
				PlayerInfo[playerid][pName],
				GetPlayerSex(playerid),
				PlayerInfo[playerid][pAge],
				GetPlayerContinent(playerid),
				GetPlayerOrigin(playerid)
			);

			osrp_ShowPlayerDialog(playerid, DIALOG_ACCOUNT_CHAR_SUMMARY, DIALOG_STYLE_MSGBOX, "Podsumowanie:", mainStr, "Stwórz", "Cofnij");
		}
		case DIALOG_ACCOUNT_CHAR_SUMMARY: {
			if(!response) {
				PlayerInfo[playerid][pOrigin] = -1;
				return osrp_ShowPlayerDialog(playerid, DIALOG_ACCOUNT_CHAR_ORIGIN, DIALOG_STYLE_LIST, "Wybierz rasê Twojej postaci:", "{FFFFFF}Bia³a\nCzarna\n¯ó³ta", "Dalej", "Cofnij");
			}

			OnPlayerRegister(playerid);

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "Opcje konta %s:", accName[playerid]);
			osrp_ShowPlayerDialog(playerid, DIALOG_ACCOUNT_OPTIONS, DIALOG_STYLE_LIST, mainStr, "{FFFFFF}Zaloguj siê na postaæ\nStwórz now¹ postaæ\nUsuñ istniej¹c¹ postaæ\nAnty Crash\nZmieñ has³o do konta", "Dalej", "");
		}
		case DIALOG_TUTORIAL: {
			if(!response) {
				TutTime[playerid] = 0;
				PlayerInfo[playerid][pTut] = 0;
				return 1;
			}

			TutTime[playerid] = 1;
		}
		case DIALOG_ADMIN_VEHICLE: {
			if(!response) {
				return 1;
			}

			new VehName[32], Tmp[8];

			sscanf(inputtext, "s[32]s[8]", VehName, Tmp);

			if(GetVehicleModelIDFromName(VehName) != -1) {
				AdminVehModelID = GetVehicleModelIDFromName(VehName);

				osrp_ShowPlayerDialog(playerid, DIALOG_ADMIN_VEHICLE_COLOR, DIALOG_STYLE_INPUT, "Wybierz kolor pojazdu:", "{FFFFFF}Podaj kolor pojazdu.\nPrzyk³ad: 0, 0: ", "Dalej", "Cofnij");
			}
		}
		case DIALOG_ADMIN_VEHICLE_COLOR: {
			if(!response) {
				callcmd::dodajpojazd(playerid, "");
				return 1;
			}

			new Color[2];

			sscanf(inputtext, "p<,>ii", Color[0], Color[1]);

			AdminVehColor[0] = Color[0];
			AdminVehColor[1] = Color[1];

			osrp_ShowPlayerDialog(playerid, DIALOG_ADMIN_VEHICLE_ENGINE, DIALOG_STYLE_INPUT, "Wybierz silnik pojazdu:", "{FFFFFF}Podaj rodzaj silnika pojazdu.\nTypy:\n\t0 - Benzyna\n\t1 - Olej napêdowy\n\t2 - Bateria\n\t3 - Paliwo lotnicze", "Dalej", "Cofnij");
		}
		case DIALOG_ADMIN_VEHICLE_ENGINE: {
			if(!response) {
				return osrp_ShowPlayerDialog(playerid, DIALOG_ADMIN_VEHICLE_COLOR, DIALOG_STYLE_INPUT, "Podaj kolor pojazdu:", "{FFFFFF}Podaj kolor pojazdu.\nPrzyk³ad: 0, 0: ", "Dalej", "Cofnij");
			}

			new EngineType = strval(inputtext);

			AdminVehEngine = EngineType;

			osrp_ShowPlayerDialog(playerid, DIALOG_ADMIN_VEHICLE_OWNER, DIALOG_STYLE_INPUT, "Wybierz w³aœciciela pojazdu:", "{FFFFFF}Podaj w³aœciciela pojazdu (ID, Typ):\nTypy:\n\t-1 - Nikt\n\t0 - Server\n\t1 - Gracz\n\t2 Biznes", "Dalej", "Cofnij");
		}
		case DIALOG_ADMIN_VEHICLE_OWNER: {
			if(!response) {
				return osrp_ShowPlayerDialog(playerid, DIALOG_ADMIN_VEHICLE_ENGINE, DIALOG_STYLE_INPUT, "Wybierz silnik pojazdu:", "{FFFFFF}Podaj rodzaj silnika pojazdu.\nTypy:\n\t0 - Benzyna\n\t1 - Olej napêdowy\n\t2 - Bateria\n\t3 - Paliwo lotnicze", "Dalej", "Cofnij");
			}

			new OwnerParms[2];

			sscanf(inputtext, "p<,>ii", OwnerParms[0], OwnerParms[1]);

			AdminVehOwner[0] = OwnerParms[0];
			AdminVehOwner[1] = OwnerParms[1];

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "{BDCB92}Nazwa: {FFFFFF}%s\n{BDCB92}Kolor1: {FFFFFF}%d\n{BDCB92}Kolor2: {FFFFFF}%d\n{BDCB92}Rodzaj silnika: {FFFFFF}%d\n{BDCB92}ID Ownera: {FFFFFF}%d\n{BDCB92}Typ Ownera: {FFFFFF}%d",
				VehicleNames[AdminVehModelID - 400],
				AdminVehColor[0],
				AdminVehColor[1],
				AdminVehEngine,
				AdminVehOwner[0],
				AdminVehOwner[1]
			);

			osrp_ShowPlayerDialog(playerid, DIALOG_ADMIN_VEHICLE_SUMMARY, DIALOG_STYLE_MSGBOX, "Podsumowanie pojazdu:", mainStr, "Stwórz", "Cofnij");
		}
		case DIALOG_ADMIN_VEHICLE_SUMMARY: {
			if(!response) {
				return osrp_ShowPlayerDialog(playerid, DIALOG_ADMIN_VEHICLE_OWNER, DIALOG_STYLE_INPUT, "Wybierz w³aœciciela pojazdu:", "{FFFFFF}Podaj w³aœciciela pojazdu (ID, Typ):\nTypy:\n\t-1 - Nikt\n\t0 - Server\n\t1 - Gracz\n\t2 Biznes", "Dalej", "Cofnij");
			}

			new Float:PosX, Float:PosY, Float:PosZ, Float:PosA;

			GetPlayerPos(playerid, PosX, PosY, PosZ);
			GetPlayerFacingAngle(playerid, PosA);

			PosX += 2.0;
			PosY += 1.0;

			AddVehicle(AdminVehOwner[0], AdminVehOwner[1], AdminVehModelID, AdminVehEngine, AdminVehColor[0], AdminVehColor[1], 1, PosX, PosY, PosZ, PosA);

			AdminVehModelID = 0;
			AdminVehColor[0] = 0;
			AdminVehColor[1] = 0;
			AdminVehEngine = 0;
			AdminVehOwner[0] = 0;
			AdminVehOwner[1] = 0;
		}
	}
	return 1;
}
