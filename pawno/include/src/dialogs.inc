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

			new day, month, year, second, minute, hour;
			new date[64], IP[16];

			gettime(hour, minute, second);
			getdate(year, month, day);

			format(date, sizeof(date), "%02d/%02d/%03d %02d:%02d:%02d", day, month, year, hour, minute, second);
			format(accSalt[playerid], 17, "%s", GeneratePasswordSalt());

			SHA256_PassHash(inputtext, accSalt[playerid], accPassword[playerid], 65);
			GetPlayerIp(playerid, IP, sizeof(IP));

			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "INSERT INTO `Accounts` (`Name`, `Password`, `Salt`, `IP`, `Date`, `LastDate`) VALUES ('%s', '%s', '%s', '%s', '%s', '%s')",
				accName[playerid],
				accPassword[playerid],
				accSalt[playerid],
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

			new recommenderName[24];

			mysql_real_escape_string(inputtext, recommenderName);

			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "SELECT * FROM `Accounts` WHERE `Name` = '%s' LIMIT 1", recommenderName);
			mysql_query(queryStr);

			mysql_store_result();

			if(mysql_result_stored()) {
				if(mysql_num_rows() > 0) {
					queryStr[0] = EOS;
					format(queryStr, sizeof(queryStr), "UPDATE `Accounts` SET `Recommender` = '%s' WHERE `Name` = '%s'", escapedName[playerid]);
					mysql_query(queryStr);

					queryStr[0] = EOS;
					format(queryStr, sizeof(queryStr), "UPDATE `Accounts` SET `PendingPP` = '%d' WHERE `Name` = '%s'", RECOMMENDER_PRIZE, recommenderName);
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

			new hash[65];

			SHA256_PassHash(inputtext, accSalt[playerid], hash, sizeof(hash) - 1);

			if(!strcmp(hash, accPassword[playerid], false)) {
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
			new count, charStr[512];

			switch(listitem) {
				case 0: {
					queryStr[0] = EOS;
					format(queryStr, sizeof(queryStr), "SELECT `Name`, `Respect` FROM `Characters` WHERE `AID` = '%d'", PlayerInfo[playerid][pAID]);
					mysql_query(queryStr);

					mysql_store_result();

					if(mysql_result_stored()) {
						while(mysql_fetch_row(queryStr, "|")) {
							sscanf(queryStr, "p<|>s[24]i", Characters[count][Name], Characters[count][Hours]);
							format(charStr, sizeof(charStr), "%s\n{FFFFFF}%s (%d przegranych godzin)", charStr, Characters[count][Name], Characters[count][Hours]);

							count++;
						}

						mysql_free_result();

						if(!count) {
							SendClientMessage(playerid, COLOR_WHITE, "Serwer: Twoje konto nie posiada ¿adnej postaci. Musisz jak¹œ stworzyæ.");

							mainStr[0] = EOS;
							format(mainStr, sizeof(mainStr), "Opcje konta %s:", accName[playerid]);
							return osrp_ShowPlayerDialog(playerid, DIALOG_ACCOUNT_OPTIONS, DIALOG_STYLE_LIST, mainStr, "{FFFFFF}Zaloguj siê na postaæ\nStwórz now¹ postaæ\nUsuñ istniej¹c¹ postaæ\nAnty Crash\nZmieñ has³o do konta", "Dalej", "");
						} else if(count == 5) {
							mainStr[0] = EOS;
							format(mainStr, sizeof(mainStr), "Serwer: Wykorzysta³eœ limit tworzenia postaci (%d).", MAX_PLAYER_CHARS);
							SendClientMessage(playerid, COLOR_WHITE, mainStr);

							mainStr[0] = EOS;
							format(mainStr, sizeof(mainStr), "Opcje konta %s:", accName[playerid]);
							return osrp_ShowPlayerDialog(playerid, DIALOG_ACCOUNT_OPTIONS, DIALOG_STYLE_LIST, mainStr, "{FFFFFF}Zaloguj siê na postaæ\nStwórz now¹ postaæ\nUsuñ istniej¹c¹ postaæ\nAnty Crash\nZmieñ has³o do konta", "Dalej", "");
						}

						mainStr[0] = EOS;
						format(mainStr, sizeof(mainStr), "Postacie konta %s:", accName[playerid]);
						osrp_ShowPlayerDialog(playerid, DIALOG_ACCOUNT_CHARACTERS, DIALOG_STYLE_LIST, mainStr, charStr, "Zaloguj", "Cofnij");
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
							sscanf(queryStr, "p<|>s[24]s[32]", Characters[count][Name], Characters[count][Date]);
							format(charStr, sizeof(charStr), "%s\n{FFFFFF}%s (Ostatnia wizyta: %s)", charStr, Characters[count][Name], Characters[count][Date]);

							count++;
						}

						mysql_free_result();

						if(!count) {
							SendClientMessage(playerid, COLOR_WHITE, "Serwer: Twoje konto nie posiada ¿adnej postaci do usuniêcia.");

							mainStr[0] = EOS;
							format(mainStr, sizeof(mainStr), "Opcje konta %s:", accName[playerid]);
							return osrp_ShowPlayerDialog(playerid, DIALOG_ACCOUNT_OPTIONS, DIALOG_STYLE_LIST, mainStr, "{FFFFFF}Zaloguj siê na postaæ\nStwórz now¹ postaæ\nUsuñ istniej¹c¹ postaæ\nAnty Crash\nZmieñ has³o do konta", "Dalej", "");
						}

						mainStr[0] = EOS;
						format(mainStr, sizeof(mainStr), "Postacie konta %s:", accName[playerid]);
						osrp_ShowPlayerDialog(playerid, DIALOG_ACCOUNT_REMOVE_CHAR_INFO, DIALOG_STYLE_LIST, mainStr, charStr, "Usuñ", "Cofnij");
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
				new name[24], tmp[64];

				sscanf(inputtext, "s[24]s[64]", name, tmp);
				printf("Login: %s", name);
				OnPlayerLogin(playerid, name);
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

			new name[24];

			mysql_real_escape_string(inputtext, name);

			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "SELECT * FROM `Characters` WHERE `Name` = '%s' LIMIT 1", name);
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

			new name[24], tmp[64];

			sscanf(inputtext, "s[24]s[64]", name, tmp);
			format(PlayerInfo[playerid][pName], 24, name);

			osrp_ShowPlayerDialog(playerid, DIALOG_ACCOUNT_REMOVE_CHAR, DIALOG_STYLE_MSGBOX, "Usuniêcie postaci:", "{FFFFFF}Czy napewno chcesz usun¹æ swoj¹ postaæ?\nNie bêdziesz móg³ ju¿ nigdy ni¹ zagraæ.\nJej maj¹tek zostanie bezpowrotnie usuniêty.\n{AA3333}Zastanów siê nad t¹ decyzj¹.", "Tak", "Nie");
		}
		case DIALOG_ACCOUNT_REMOVE_CHAR: {
			if(!response) {
				mainStr[0] = EOS;
				format(mainStr, sizeof(mainStr), "Opcje konta %s:", accName[playerid]);
				return osrp_ShowPlayerDialog(playerid, DIALOG_ACCOUNT_OPTIONS, DIALOG_STYLE_LIST, mainStr, "{FFFFFF}Zaloguj siê na postaæ\nStwórz now¹ postaæ\nUsuñ istniej¹c¹ postaæ\nAnty Crash\nZmieñ has³o do konta", "Dalej", "");
			}

			new name[24];

			mysql_real_escape_string(PlayerInfo[playerid][pName], name);

			queryStr[0] = EOS;
			format(queryStr, sizeof(queryStr), "DELETE FROM `Characters` WHERE `Name` = '%s'", name);
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

			new sex = listitem;

			PlayerInfo[playerid][pSex] = sex;

			osrp_ShowPlayerDialog(playerid, DIALOG_ACCOUNT_CHAR_AGE, DIALOG_STYLE_INPUT, "Wybierz wiek swojej postaci:", "{FFFFFF}Wpisz wiek z przedzia³u od 18 do 65 lat.", "Dalej", "Cofnij");
		}
		case DIALOG_ACCOUNT_CHAR_AGE: {
			if(!response) {
				PlayerInfo[playerid][pSex] = -1;
				return osrp_ShowPlayerDialog(playerid, DIALOG_ACCOUNT_CHAR_SEX, DIALOG_STYLE_LIST, "Wybierz p³eæ Twojej postaci:", "{FFFFFF}Mê¿czyzna\nKobieta", "Dalej", "Cofnij");
			}

			new age = strval(inputtext);

			if(age > 65 || age < 18) {
				return osrp_ShowPlayerDialog(playerid, DIALOG_ACCOUNT_CHAR_AGE, DIALOG_STYLE_INPUT, "Wybierz wiek swojej postaci:", "{AA3333}Podany wiek jest nieprawid³owy.\n{FFFFFF}Wpisz wiek z przedzia³u od 18 do 65 lat.", "Dalej", "Cofnij");
			}

			PlayerInfo[playerid][pAge] = age;

			osrp_ShowPlayerDialog(playerid, DIALOG_ACCOUNT_CHAR_CONTINENT, DIALOG_STYLE_LIST, "Wybierz kontynent z którego pochodzi Twoja postaæ:", "{FFFFFF}Ameryka\nEuropa\nAustralia\nAzja\nAfryka", "Dalej", "Cofnij");
		}
		case DIALOG_ACCOUNT_CHAR_CONTINENT: {
			if(!response) {
				PlayerInfo[playerid][pAge] = 0;
				return osrp_ShowPlayerDialog(playerid, DIALOG_ACCOUNT_CHAR_AGE, DIALOG_STYLE_INPUT, "Wybierz wiek swojej postaci:", "{FFFFFF}Wpisz wiek z przedzia³u od 18 do 65 lat.", "Dalej", "Cofnij");
			}

			new continent = listitem;

			PlayerInfo[playerid][pContinent] = continent;

			osrp_ShowPlayerDialog(playerid, DIALOG_ACCOUNT_CHAR_ORIGIN, DIALOG_STYLE_LIST, "Wybierz rasê Twojej postaci:", "{FFFFFF}Bia³a\nCzarna\n¯ó³ta", "Dalej", "Cofnij");
		}
		case DIALOG_ACCOUNT_CHAR_ORIGIN: {
			if(!response) {
				PlayerInfo[playerid][pContinent] = -1;
				return osrp_ShowPlayerDialog(playerid, DIALOG_ACCOUNT_CHAR_CONTINENT, DIALOG_STYLE_LIST, "Wybierz kontynent z którego pochodzi Twoja postaæ:", "{FFFFFF}Ameryka\nEuropa\nAustralia\nAzja\nAfryka", "Dalej", "Cofnij");
			}

			new origin = listitem;

			PlayerInfo[playerid][pOrigin] = origin;

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

			new vehName[32], tmp[8];

			sscanf(inputtext, "s[32]s[8]", vehName, tmp);

			if(GetVehicleModelIDFromName(vehName) != -1) {
				AdminVehModelID = GetVehicleModelIDFromName(vehName);

				osrp_ShowPlayerDialog(playerid, DIALOG_ADMIN_VEHICLE_COLOR, DIALOG_STYLE_INPUT, "Dodawanie Pojazdu (Kolor):", "{FFFFFF}Podaj kolor pojazdu np. (0, 0): ", "Dalej", "Cofnij");
			}
		}
		case DIALOG_ADMIN_VEHICLE_COLOR: {
			if(!response) {
				callcmd::dodajpojazd(playerid, "");
				return 1;
			}

			new color[2];

			sscanf(inputtext, "p<,>ii", color[0], color[1]);

			AdminVehColor[0] = color[0];
			AdminVehColor[1] = color[1];

			osrp_ShowPlayerDialog(playerid, DIALOG_ADMIN_VEHICLE_OWNER, DIALOG_STYLE_INPUT, "Dodawanie Pojazdu (W³aœciciel):", "{FFFFFF}Podaj w³aœciciela pojazdu (ID, Typ):\nTypy:\n-1 - Nikt\n0 - Server\n1 - Gracz\n2 Biznes", "Dalej", "Cofnij");
		}
		case DIALOG_ADMIN_VEHICLE_OWNER: {
			if(!response) {
				return osrp_ShowPlayerDialog(playerid, DIALOG_ADMIN_VEHICLE_COLOR, DIALOG_STYLE_INPUT, "Dodawanie Pojazdu (Kolor):", "{FFFFFF}Podaj kolor pojazdu np. (0, 0): ", "Dalej", "Cofnij");
			}

			new ownerParms[2];

			sscanf(inputtext, "p<,>ii", ownerParms[0], ownerParms[1]);

			AdminVehOwner[0] = ownerParms[0];
			AdminVehOwner[1] = ownerParms[1];

			mainStr[0] = EOS;
			format(mainStr, sizeof(mainStr), "{FFFFFF}Nazwa: %s\nKolor1: %d, Kolor2: %d\nID Ownera: %d\nTyp Ownera: %d",
				VehicleNames[AdminVehModelID - 400],
				AdminVehColor[0],
				AdminVehColor[1],
				AdminVehOwner[0],
				AdminVehOwner[1]
			);

			osrp_ShowPlayerDialog(playerid, DIALOG_ADMIN_VEHICLE_SUMMARY, DIALOG_STYLE_MSGBOX, "Dodawanie Pojazdu (Podsumowanie):", mainStr, "Stwórz", "Cofnij");
		}
		case DIALOG_ADMIN_VEHICLE_SUMMARY: {
			if(!response) {
				return osrp_ShowPlayerDialog(playerid, DIALOG_ADMIN_VEHICLE_OWNER, DIALOG_STYLE_INPUT, "Dodawanie Pojazdu (W³aœciciel):", "{FFFFFF}Podaj w³aœciciela pojazdu (ID, Typ):\nTypy:\n-1 - Nikt\n0 - Server\n1 - Gracz\n2 Biznes", "Dalej", "Cofnij");
			}

			new Float:PosX, Float:PosY, Float:PosZ, Float:PosA;

			GetPlayerPos(playerid, PosX, PosY, PosZ);
			GetPlayerFacingAngle(playerid, PosA);

			PosX += 2.0;
			PosY += 1.0;

			AddVehicle(AdminVehOwner[0], AdminVehOwner[1], AdminVehModelID, 0, AdminVehColor[0], AdminVehColor[1], 1, PosX, PosY, PosZ, PosA);

			AdminVehModelID = 0;
			AdminVehOwner[0] = 0;
			AdminVehOwner[1] = 0;
			AdminVehColor[0] = 0;
			AdminVehColor[1] = 0;
		}
	}
	return 1;
}
