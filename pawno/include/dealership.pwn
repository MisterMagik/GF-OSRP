#define MAX_DEALERSHIP_OFFERS 64
#define DEALERSHIP_MAX_PLAYER_VEHICLES 3
#define DEALERSHIP_COLORS 12
#define DEALERSHIP_FUELS 3
#define DEALERSHIP_PICKUP_RANGE 2.5

enum {
	DEALERSHIP_COUT_SCHUTZ,
	MAX_DEALERSHIPS
};

// Kroki zakupu: kazdy zatwierdzamy klawiszem Y, cofamy klawiszem N
enum {
	DEALERSHIP_STEP_VEHICLE,
	DEALERSHIP_STEP_COLOR,
	DEALERSHIP_STEP_FUEL,
	DEALERSHIP_STEP_SUMMARY
};

// Statyczne elementy panelu (kolejnosc tworzenia = kolejnosc rysowania)
#define DEALERSHIP_TD_DIM 0
#define DEALERSHIP_TD_PANEL 1
#define DEALERSHIP_TD_HEADER 2
#define DEALERSHIP_TD_ACCENT 3
#define DEALERSHIP_TD_TITLE 4
#define DEALERSHIP_TD_STEP 5
#define DEALERSHIP_TD_PREVIEW_BG 6
#define DEALERSHIP_TD_PREVIEW 7
#define DEALERSHIP_TD_NAME 8
#define DEALERSHIP_TD_PRICE 9
#define DEALERSHIP_TD_COUNTER 10
#define DEALERSHIP_TD_COLOR_LABEL 11
#define DEALERSHIP_TD_FUEL_LABEL 12
#define DEALERSHIP_TD_SUMMARY_BG 13
#define DEALERSHIP_TD_SUMMARY 14
#define DEALERSHIP_TD_HINT 15
#define DEALERSHIP_TD_COUNT 16

enum E_DEALERSHIP_INFO {
	dsName[32],
	Float:dsPickup[3],
	Float:dsSpawn[4],
	dsPickupID
};

enum E_DEALERSHIP_OFFER {
	ofDealership,
	ofModel,
	ofPrice,
	ofName[24]
};

// Paleta kolorow: ID koloru pojazdu w GTA SA, przyblizony kolor RGBA do wyswietlenia i nazwa
new const DealershipColorIDs[DEALERSHIP_COLORS] = {0, 1, 8, 13, 3, 6, 16, 79, 7, 2, 126, 57};
new const DealershipColorRGB[DEALERSHIP_COLORS] = {0x000000FF, 0xF5F5F5FF, 0xBDBEC6FF, 0x58595AFF, 0x840410FF, 0xD78E10FF, 0x335F3FFF, 0x0E316DFF, 0x4C75B7FF, 0x2A77A1FF, 0xEC6AAEFF, 0x9C8D71FF};
new const DealershipColorNames[DEALERSHIP_COLORS][16] = {"Czarny", "Bialy", "Srebrny", "Grafitowy", "Czerwony", "Pomaranczowy", "Zielony", "Granatowy", "Niebieski", "Blekitny", "Rozowy", "Bezowy"};

// Typy paliwa: typ silnika (jak w GetVehicleEngineTypeName), doplata do ceny i nazwa
new const DealershipFuelTypes[DEALERSHIP_FUELS] = {0, 1, 2};
new const DealershipFuelPrices[DEALERSHIP_FUELS] = {0, 500, 2000};
new const DealershipFuelNames[DEALERSHIP_FUELS][16] = {"Benzyna", "Olej napedowy", "Elektryczny"};

new DealershipInfo[MAX_DEALERSHIPS][E_DEALERSHIP_INFO];
new DealershipOffers[MAX_DEALERSHIP_OFFERS][E_DEALERSHIP_OFFER];
new DealershipOffersCount;

new DealershipPlayer[MAX_PLAYERS] = {-1, ...};
new DealershipStep[MAX_PLAYERS];
new DealershipOffer[MAX_PLAYERS];
new DealershipColor[MAX_PLAYERS];
new DealershipFuel[MAX_PLAYERS];
new DealershipLastUpDown[MAX_PLAYERS];
new DealershipLastLeftRight[MAX_PLAYERS];
new Float:DealershipPos[MAX_PLAYERS][3];

new PlayerText:DealershipTD[MAX_PLAYERS][DEALERSHIP_TD_COUNT];
new PlayerText:DealershipColorFrameTD[MAX_PLAYERS][DEALERSHIP_COLORS];
new PlayerText:DealershipColorTD[MAX_PLAYERS][DEALERSHIP_COLORS];
new PlayerText:DealershipFuelTD[MAX_PLAYERS][DEALERSHIP_FUELS];

stock GetPlayerCash(playerid) {
	return GetPlayerMoney(playerid);
}

stock TakePlayerCash(playerid, amount) {
	return GivePlayerMoney(playerid, -amount);
}

stock AddDealershipOffer(dealership, modelid, price, const name[]) {
	if(DealershipOffersCount >= MAX_DEALERSHIP_OFFERS) {
		printf("[SALON] Przekroczono limit ofert (%d).", MAX_DEALERSHIP_OFFERS);
		return -1;
	}

	new id = DealershipOffersCount;

	DealershipOffers[id][ofDealership] = dealership;
	DealershipOffers[id][ofModel] = modelid;
	DealershipOffers[id][ofPrice] = price;
	format(DealershipOffers[id][ofName], 24, "%s", name);

	DealershipOffersCount++;
	return id;
}

stock InitDealerships() {
	new label[96];

	// Cout & Schutz (UZUPELNIJ wspolrzedne pickupa i miejsca, w ktorym pojawia sie kupiony pojazd)
	format(DealershipInfo[DEALERSHIP_COUT_SCHUTZ][dsName], 32, "Cout & Schutz");
	DealershipInfo[DEALERSHIP_COUT_SCHUTZ][dsPickup][0] = 2128.7976;
	DealershipInfo[DEALERSHIP_COUT_SCHUTZ][dsPickup][1] = -1147.0233;
	DealershipInfo[DEALERSHIP_COUT_SCHUTZ][dsPickup][2] = 24.5015;
	DealershipInfo[DEALERSHIP_COUT_SCHUTZ][dsSpawn][0] = 2128.7976+2;
	DealershipInfo[DEALERSHIP_COUT_SCHUTZ][dsSpawn][1] = -1147.0233-2;
	DealershipInfo[DEALERSHIP_COUT_SCHUTZ][dsSpawn][2] = 24.5015;
	DealershipInfo[DEALERSHIP_COUT_SCHUTZ][dsSpawn][3] = 90.0;

	// Oferta: salon, model, cena bazowa (benzyna), nazwa
	AddDealershipOffer(DEALERSHIP_COUT_SCHUTZ, 436, 5500, "Previon");
	AddDealershipOffer(DEALERSHIP_COUT_SCHUTZ, 529, 6000, "Willard");
	AddDealershipOffer(DEALERSHIP_COUT_SCHUTZ, 419, 6500, "Esperanto");
	AddDealershipOffer(DEALERSHIP_COUT_SCHUTZ, 404, 7000, "Perennial");
	AddDealershipOffer(DEALERSHIP_COUT_SCHUTZ, 496, 8000, "Blista Compact");
	AddDealershipOffer(DEALERSHIP_COUT_SCHUTZ, 549, 9000, "Tampa");
	AddDealershipOffer(DEALERSHIP_COUT_SCHUTZ, 542, 9500, "Clover");
	AddDealershipOffer(DEALERSHIP_COUT_SCHUTZ, 526, 10000, "Fortune");

	for(new i = 0; i < MAX_DEALERSHIPS; i++) {
		DealershipInfo[i][dsPickupID] = CreateDynamicPickup(1239, 1, DealershipInfo[i][dsPickup][0], DealershipInfo[i][dsPickup][1], DealershipInfo[i][dsPickup][2]);

		format(label, sizeof(label), "Salon %s\nWpisz /kuppojazd, aby przegladac oferte", DealershipInfo[i][dsName]);
		CreateDynamic3DTextLabel(label, COLOR_WHITE, DealershipInfo[i][dsPickup][0], DealershipInfo[i][dsPickup][1], DealershipInfo[i][dsPickup][2] + 0.7, 15.0);
	}

	SetTimer("DealershipUpdate", 100, true);

	printf("[SALON] Wczytano %d salonow i %d ofert.", MAX_DEALERSHIPS, DealershipOffersCount);
	return 1;
}

stock GetDealershipOfferCount(dealership) {
	new count;

	for(new i = 0; i < DealershipOffersCount; i++) {
		if(DealershipOffers[i][ofDealership] == dealership) {
			count++;
		}
	}
	return count;
}

stock GetDealershipOffer(dealership, index) {
	new count;

	for(new i = 0; i < DealershipOffersCount; i++) {
		if(DealershipOffers[i][ofDealership] != dealership) {
			continue;
		}

		if(count == index) {
			return i;
		}

		count++;
	}
	return -1;
}

stock GetDealershipFinalPrice(playerid) {
	new offer = GetDealershipOffer(DealershipPlayer[playerid], DealershipOffer[playerid]);

	if(offer == -1) {
		return 0;
	}
	return DealershipOffers[offer][ofPrice] + DealershipFuelPrices[DealershipFuel[playerid]];
}

// Zwraca salon, w ktorego pickupie stoi gracz (albo -1)
stock GetPlayerDealership(playerid) {
	for(new i = 0; i < MAX_DEALERSHIPS; i++) {
		if(IsPlayerInRangeOfPoint(playerid, DEALERSHIP_PICKUP_RANGE, DealershipInfo[i][dsPickup][0], DealershipInfo[i][dsPickup][1], DealershipInfo[i][dsPickup][2])) {
			return i;
		}
	}
	return -1;
}

stock CountPlayerVehicles(playerid) {
	new count;

	foreach(new i : VehItter) {
		if(VehicleInfo[i][vOwnerType] != VEHICLE_OWNER_TYPE_PLAYER) {
			continue;
		}

		if(VehicleInfo[i][vOwnerID] != PlayerInfo[playerid][pID]) {
			continue;
		}

		count++;
	}
	return count;
}

// Prostokat bez tekstu (tlo, ramki, paski, probki kolorow)
stock PlayerText:CreateDealershipBox(playerid, Float:x, Float:y, Float:endx, Float:height, color) {
	new PlayerText:td = CreatePlayerTextDraw(playerid, x, y, "_");

	PlayerTextDrawLetterSize(playerid, td, 0.0, height);
	PlayerTextDrawTextSize(playerid, td, endx, 0.0);
	PlayerTextDrawAlignment(playerid, td, 1);
	PlayerTextDrawUseBox(playerid, td, 1);
	PlayerTextDrawBoxColor(playerid, td, color);
	PlayerTextDrawSetShadow(playerid, td, 0);
	PlayerTextDrawFont(playerid, td, 1);
	return td;
}

stock PlayerText:CreateDealershipLabel(playerid, Float:x, Float:y, text[], Float:letterx, Float:lettery, color, font) {
	new PlayerText:td = CreatePlayerTextDraw(playerid, x, y, text);

	PlayerTextDrawLetterSize(playerid, td, letterx, lettery);
	PlayerTextDrawAlignment(playerid, td, 1);
	PlayerTextDrawColor(playerid, td, color);
	PlayerTextDrawSetShadow(playerid, td, 1);
	PlayerTextDrawFont(playerid, td, font);
	PlayerTextDrawSetProportional(playerid, td, 1);
	return td;
}

// Pasek z tekstem na kolorowym tle (opcje paliwa, podpowiedz klawiszy)
stock PlayerText:CreateDealershipOption(playerid, Float:x, Float:y, Float:endx, Float:height, Float:letterx, boxcolor, text[]) {
	new PlayerText:td = CreatePlayerTextDraw(playerid, x, y, text);

	PlayerTextDrawLetterSize(playerid, td, letterx, height);
	PlayerTextDrawTextSize(playerid, td, endx, 0.0);
	PlayerTextDrawAlignment(playerid, td, 1);
	PlayerTextDrawColor(playerid, td, 0xFFFFFFFF);
	PlayerTextDrawUseBox(playerid, td, 1);
	PlayerTextDrawBoxColor(playerid, td, boxcolor);
	PlayerTextDrawSetShadow(playerid, td, 0);
	PlayerTextDrawFont(playerid, td, 1);
	PlayerTextDrawSetProportional(playerid, td, 1);
	return td;
}

stock CreateDealershipTextDraws(playerid, dealership) {
	new PlayerText:td;
	new Float:x, Float:y;
	new str[48];

	// Przyciemnienie ekranu, panel, naglowek i zlota linia akcentu
	DealershipTD[playerid][DEALERSHIP_TD_DIM] = CreateDealershipBox(playerid, 0.0, 0.0, 640.0, 49.5, 0x000000A0);
	DealershipTD[playerid][DEALERSHIP_TD_PANEL] = CreateDealershipBox(playerid, 110.0, 95.0, 530.0, 26.4, 0x1E1E26F2);
	DealershipTD[playerid][DEALERSHIP_TD_HEADER] = CreateDealershipBox(playerid, 110.0, 95.0, 530.0, 2.7, 0x101016FF);
	DealershipTD[playerid][DEALERSHIP_TD_ACCENT] = CreateDealershipBox(playerid, 110.0, 125.0, 530.0, 0.2, 0xFFAA00FF);

	DealershipTD[playerid][DEALERSHIP_TD_TITLE] = CreateDealershipLabel(playerid, 125.0, 99.0, DealershipInfo[dealership][dsName], 0.5, 2.0, 0xFFFFFFFF, 2);
	DealershipTD[playerid][DEALERSHIP_TD_STEP] = CreateDealershipLabel(playerid, 355.0, 108.0, "_", 0.26, 1.1, 0xFFAA00FF, 1);

	// Lewa kolumna: podglad pojazdu, nazwa, cena, licznik ofert
	DealershipTD[playerid][DEALERSHIP_TD_PREVIEW_BG] = CreateDealershipBox(playerid, 125.0, 135.0, 325.0, 12.0, 0x2C2C38FF);

	td = CreatePlayerTextDraw(playerid, 125.0, 135.0, "_");
	PlayerTextDrawFont(playerid, td, 5);
	PlayerTextDrawTextSize(playerid, td, 200.0, 132.0);
	PlayerTextDrawBackgroundColor(playerid, td, 0x00000000);
	PlayerTextDrawSetPreviewRot(playerid, td, -16.0, 0.0, -55.0, 0.9);
	DealershipTD[playerid][DEALERSHIP_TD_PREVIEW] = td;

	DealershipTD[playerid][DEALERSHIP_TD_NAME] = CreateDealershipLabel(playerid, 128.0, 271.0, "_", 0.45, 1.9, 0xFFFFFFFF, 2);
	DealershipTD[playerid][DEALERSHIP_TD_PRICE] = CreateDealershipLabel(playerid, 128.0, 293.0, "_", 0.45, 1.8, 0x66FF66FF, 2);
	DealershipTD[playerid][DEALERSHIP_TD_COUNTER] = CreateDealershipLabel(playerid, 128.0, 320.0, "_", 0.4, 1.6, 0xCCCCCCFF, 1);

	// Prawa kolumna: kolor i paliwo
	DealershipTD[playerid][DEALERSHIP_TD_COLOR_LABEL] = CreateDealershipLabel(playerid, 345.0, 133.0, "_", 0.3, 1.3, 0xAAAAAAFF, 1);

	for(new i = 0; i < DEALERSHIP_COLORS; i++) {
		x = 347.0 + float(i % 4) * 44.0;
		y = 150.0 + float(i / 4) * 26.0;

		DealershipColorFrameTD[playerid][i] = CreateDealershipBox(playerid, x - 2.0, y - 2.0, x + 38.0, 2.2, 0x00000000);
		DealershipColorTD[playerid][i] = CreateDealershipBox(playerid, x, y, x + 36.0, 1.8, DealershipColorRGB[i]);
	}

	DealershipTD[playerid][DEALERSHIP_TD_FUEL_LABEL] = CreateDealershipLabel(playerid, 345.0, 232.0, "_", 0.3, 1.3, 0xAAAAAAFF, 1);

	for(new i = 0; i < DEALERSHIP_FUELS; i++) {
		if(DealershipFuelPrices[i]) {
			format(str, sizeof(str), "  %s  (+%d$)", DealershipFuelNames[i], DealershipFuelPrices[i]);
		} else {
			format(str, sizeof(str), "  %s", DealershipFuelNames[i]);
		}

		DealershipFuelTD[playerid][i] = CreateDealershipOption(playerid, 345.0, 248.0 + float(i) * 24.0, 515.0, 1.9, 0.34, 0x3A3A44FF, str);
	}

	// Podsumowanie (zastepuje kolory i paliwo na ostatnim kroku)
	DealershipTD[playerid][DEALERSHIP_TD_SUMMARY_BG] = CreateDealershipBox(playerid, 345.0, 133.0, 515.0, 17.0, 0x2C2C38FF);

	td = CreateDealershipLabel(playerid, 355.0, 140.0, "_", 0.33, 1.3, 0xFFFFFFFF, 1);
	PlayerTextDrawTextSize(playerid, td, 510.0, 0.0);
	DealershipTD[playerid][DEALERSHIP_TD_SUMMARY] = td;

	// Dolny pasek z podpowiedzia klawiszy
	DealershipTD[playerid][DEALERSHIP_TD_HINT] = CreateDealershipOption(playerid, 125.0, 352.0, 515.0, 2.0, 0.3, 0x101016FF, "_");
	return 1;
}

// Ustawia tresci i kolory na podstawie aktualnego wyboru gracza (bez pokazywania)
stock SetDealershipTextDraws(playerid) {
	new dealership = DealershipPlayer[playerid];
	new offer = GetDealershipOffer(dealership, DealershipOffer[playerid]);
	new step = DealershipStep[playerid];
	new colorid = DealershipColorIDs[DealershipColor[playerid]];
	new price = GetDealershipFinalPrice(playerid);
	new cash = GetPlayerCash(playerid);
	new str[256];

	if(offer == -1) {
		return 0;
	}

	PlayerTextDrawSetPreviewModel(playerid, DealershipTD[playerid][DEALERSHIP_TD_PREVIEW], DealershipOffers[offer][ofModel]);
	PlayerTextDrawSetPreviewVehCol(playerid, DealershipTD[playerid][DEALERSHIP_TD_PREVIEW], colorid, colorid);

	PlayerTextDrawSetString(playerid, DealershipTD[playerid][DEALERSHIP_TD_NAME], DealershipOffers[offer][ofName]);

	format(str, sizeof(str), "%d$", price);
	PlayerTextDrawSetString(playerid, DealershipTD[playerid][DEALERSHIP_TD_PRICE], str);

	format(str, sizeof(str), "<   %d/%d   >", DealershipOffer[playerid] + 1, GetDealershipOfferCount(dealership));
	PlayerTextDrawSetString(playerid, DealershipTD[playerid][DEALERSHIP_TD_COUNTER], str);

	format(str, sizeof(str), "KOLOR: %s", DealershipColorNames[DealershipColor[playerid]]);
	PlayerTextDrawSetString(playerid, DealershipTD[playerid][DEALERSHIP_TD_COLOR_LABEL], str);
	PlayerTextDrawColor(playerid, DealershipTD[playerid][DEALERSHIP_TD_COLOR_LABEL], (step == DEALERSHIP_STEP_COLOR) ? 0xFFAA00FF : 0xAAAAAAFF);

	format(str, sizeof(str), "PALIWO: %s", DealershipFuelNames[DealershipFuel[playerid]]);
	PlayerTextDrawSetString(playerid, DealershipTD[playerid][DEALERSHIP_TD_FUEL_LABEL], str);
	PlayerTextDrawColor(playerid, DealershipTD[playerid][DEALERSHIP_TD_FUEL_LABEL], (step == DEALERSHIP_STEP_FUEL) ? 0xFFAA00FF : 0xAAAAAAFF);

	// Ramka wybranego koloru i podswietlenie wybranego paliwa (jasniejsze tylko na aktywnym kroku)
	for(new i = 0; i < DEALERSHIP_COLORS; i++) {
		if(i == DealershipColor[playerid]) {
			PlayerTextDrawBoxColor(playerid, DealershipColorFrameTD[playerid][i], (step == DEALERSHIP_STEP_COLOR) ? 0xFFFFFFFF : 0x777777FF);
		} else {
			PlayerTextDrawBoxColor(playerid, DealershipColorFrameTD[playerid][i], 0x00000000);
		}
	}

	for(new i = 0; i < DEALERSHIP_FUELS; i++) {
		if(i == DealershipFuel[playerid]) {
			PlayerTextDrawBoxColor(playerid, DealershipFuelTD[playerid][i], (step == DEALERSHIP_STEP_FUEL) ? 0x2E7D32FF : 0x24402AFF);
		} else {
			PlayerTextDrawBoxColor(playerid, DealershipFuelTD[playerid][i], 0x3A3A44FF);
		}
	}

	// Naglowek kroku i podpowiedz klawiszy
	switch(step) {
		case DEALERSHIP_STEP_VEHICLE: {
			PlayerTextDrawSetString(playerid, DealershipTD[playerid][DEALERSHIP_TD_STEP], "KROK 1/4: WYBIERZ POJAZD");
			PlayerTextDrawSetString(playerid, DealershipTD[playerid][DEALERSHIP_TD_HINT], "  ~y~STRZALKI~w~ zmiana pojazdu     ~g~Y~w~ dalej     ~r~N~w~ zamknij");
		}
		case DEALERSHIP_STEP_COLOR: {
			PlayerTextDrawSetString(playerid, DealershipTD[playerid][DEALERSHIP_TD_STEP], "KROK 2/4: WYBIERZ KOLOR");
			PlayerTextDrawSetString(playerid, DealershipTD[playerid][DEALERSHIP_TD_HINT], "  ~y~STRZALKI~w~ wybor koloru     ~g~Y~w~ dalej     ~r~N~w~ wstecz");
		}
		case DEALERSHIP_STEP_FUEL: {
			PlayerTextDrawSetString(playerid, DealershipTD[playerid][DEALERSHIP_TD_STEP], "KROK 3/4: WYBIERZ PALIWO");
			PlayerTextDrawSetString(playerid, DealershipTD[playerid][DEALERSHIP_TD_HINT], "  ~y~STRZALKI~w~ wybor paliwa     ~g~Y~w~ dalej     ~r~N~w~ wstecz");
		}
		case DEALERSHIP_STEP_SUMMARY: {
			PlayerTextDrawSetString(playerid, DealershipTD[playerid][DEALERSHIP_TD_STEP], "KROK 4/4: PODSUMOWANIE");
			PlayerTextDrawSetString(playerid, DealershipTD[playerid][DEALERSHIP_TD_HINT], "  ~g~Y~w~ KUP POJAZD     ~r~N~w~ wstecz");
		}
	}

	// Tresc podsumowania
	if(cash >= price) {
		format(str, sizeof(str), "PODSUMOWANIE ZAKUPU~n~~n~Pojazd: %s~n~Kolor: %s~n~Paliwo: %s~n~~n~Cena: %d$~n~Twoja gotowka: %d$~n~Po zakupie: %d$", DealershipOffers[offer][ofName], DealershipColorNames[DealershipColor[playerid]], DealershipFuelNames[DealershipFuel[playerid]], price, cash, cash - price);
	} else {
		format(str, sizeof(str), "PODSUMOWANIE ZAKUPU~n~~n~Pojazd: %s~n~Kolor: %s~n~Paliwo: %s~n~~n~Cena: %d$~n~Twoja gotowka: %d$~n~~r~Brakuje: %d$", DealershipOffers[offer][ofName], DealershipColorNames[DealershipColor[playerid]], DealershipFuelNames[DealershipFuel[playerid]], price, cash, price - cash);
	}

	PlayerTextDrawSetString(playerid, DealershipTD[playerid][DEALERSHIP_TD_SUMMARY], str);
	return 1;
}

stock ShowDealershipTextDraws(playerid) {
	for(new i = 0; i < DEALERSHIP_TD_COUNT; i++) {
		PlayerTextDrawShow(playerid, DealershipTD[playerid][i]);
	}

	for(new i = 0; i < DEALERSHIP_COLORS; i++) {
		PlayerTextDrawShow(playerid, DealershipColorFrameTD[playerid][i]);
		PlayerTextDrawShow(playerid, DealershipColorTD[playerid][i]);
	}

	for(new i = 0; i < DEALERSHIP_FUELS; i++) {
		PlayerTextDrawShow(playerid, DealershipFuelTD[playerid][i]);
	}
	return 1;
}

// Po zmianie wyboru lub kroku: odswieza wartosci i pokazuje ponownie elementy, ktorych wlasciwosci sie zmienily
stock RefreshDealershipTextDraws(playerid) {
	if(!SetDealershipTextDraws(playerid)) {
		return 0;
	}

	new bool:summary = (DealershipStep[playerid] == DEALERSHIP_STEP_SUMMARY);

	PlayerTextDrawShow(playerid, DealershipTD[playerid][DEALERSHIP_TD_PREVIEW]);
	PlayerTextDrawShow(playerid, DealershipTD[playerid][DEALERSHIP_TD_STEP]);
	PlayerTextDrawShow(playerid, DealershipTD[playerid][DEALERSHIP_TD_HINT]);

	if(summary) {
		PlayerTextDrawHide(playerid, DealershipTD[playerid][DEALERSHIP_TD_COLOR_LABEL]);
		PlayerTextDrawHide(playerid, DealershipTD[playerid][DEALERSHIP_TD_FUEL_LABEL]);

		for(new i = 0; i < DEALERSHIP_COLORS; i++) {
			PlayerTextDrawHide(playerid, DealershipColorFrameTD[playerid][i]);
			PlayerTextDrawHide(playerid, DealershipColorTD[playerid][i]);
		}

		for(new i = 0; i < DEALERSHIP_FUELS; i++) {
			PlayerTextDrawHide(playerid, DealershipFuelTD[playerid][i]);
		}

		PlayerTextDrawShow(playerid, DealershipTD[playerid][DEALERSHIP_TD_SUMMARY_BG]);
		PlayerTextDrawShow(playerid, DealershipTD[playerid][DEALERSHIP_TD_SUMMARY]);
	} else {
		PlayerTextDrawHide(playerid, DealershipTD[playerid][DEALERSHIP_TD_SUMMARY_BG]);
		PlayerTextDrawHide(playerid, DealershipTD[playerid][DEALERSHIP_TD_SUMMARY]);

		PlayerTextDrawShow(playerid, DealershipTD[playerid][DEALERSHIP_TD_COLOR_LABEL]);
		PlayerTextDrawShow(playerid, DealershipTD[playerid][DEALERSHIP_TD_FUEL_LABEL]);

		for(new i = 0; i < DEALERSHIP_COLORS; i++) {
			PlayerTextDrawShow(playerid, DealershipColorFrameTD[playerid][i]);
			PlayerTextDrawShow(playerid, DealershipColorTD[playerid][i]);
		}

		for(new i = 0; i < DEALERSHIP_FUELS; i++) {
			PlayerTextDrawShow(playerid, DealershipFuelTD[playerid][i]);
		}
	}
	return 1;
}

stock OpenDealership(playerid, dealership) {
	if(DealershipPlayer[playerid] != -1) {
		return 0;
	}

	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) {
		return 0;
	}

	if(!GetDealershipOfferCount(dealership)) {
		return 0;
	}

	DealershipPlayer[playerid] = dealership;
	DealershipStep[playerid] = DEALERSHIP_STEP_VEHICLE;
	DealershipOffer[playerid] = 0;
	DealershipColor[playerid] = 0;
	DealershipFuel[playerid] = 0;
	DealershipLastUpDown[playerid] = 0;
	DealershipLastLeftRight[playerid] = 0;

	GetPlayerPos(playerid, DealershipPos[playerid][0], DealershipPos[playerid][1], DealershipPos[playerid][2]);

	CreateDealershipTextDraws(playerid, dealership);
	ShowDealershipTextDraws(playerid);
	RefreshDealershipTextDraws(playerid);
	return 1;
}

stock CloseDealership(playerid) {
	if(DealershipPlayer[playerid] == -1) {
		return 0;
	}

	DealershipPlayer[playerid] = -1;

	for(new i = 0; i < DEALERSHIP_TD_COUNT; i++) {
		PlayerTextDrawDestroy(playerid, DealershipTD[playerid][i]);
		DealershipTD[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
	}

	for(new i = 0; i < DEALERSHIP_COLORS; i++) {
		PlayerTextDrawDestroy(playerid, DealershipColorFrameTD[playerid][i]);
		PlayerTextDrawDestroy(playerid, DealershipColorTD[playerid][i]);
		DealershipColorFrameTD[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
		DealershipColorTD[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
	}

	for(new i = 0; i < DEALERSHIP_FUELS; i++) {
		PlayerTextDrawDestroy(playerid, DealershipFuelTD[playerid][i]);
		DealershipFuelTD[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
	}
	return 1;
}

stock BuyDealershipVehicle(playerid) {
	new dealership = DealershipPlayer[playerid];
	new offer = GetDealershipOffer(dealership, DealershipOffer[playerid]);

	if(offer == -1) {
		return 0;
	}

	new price = GetDealershipFinalPrice(playerid);
	new colorid = DealershipColorIDs[DealershipColor[playerid]];
	new enginetype = DealershipFuelTypes[DealershipFuel[playerid]];
	new plate[32], str[128], name[MAX_PLAYER_NAME];

	if(CountPlayerVehicles(playerid) >= DEALERSHIP_MAX_PLAYER_VEHICLES) {
		format(str, sizeof(str), "Możesz posiadać maksymalnie %d pojazdy.", DEALERSHIP_MAX_PLAYER_VEHICLES);
		SendClientMessage(playerid, COLOR_GRAD1, str);
		return 0;
	}

	if(GetPlayerCash(playerid) < price) {
		SendClientMessage(playerid, COLOR_GRAD1, "Nie stać Cię na ten pojazd.");
		return 0;
	}

	format(plate, sizeof(plate), "%s", GenerateNewNumberPlate());

	new vehicleid = AddVehicle(PlayerInfo[playerid][pID], VEHICLE_OWNER_TYPE_PLAYER, DealershipOffers[offer][ofModel], enginetype, colorid, colorid, 1, DealershipInfo[dealership][dsSpawn][0], DealershipInfo[dealership][dsSpawn][1], DealershipInfo[dealership][dsSpawn][2], DealershipInfo[dealership][dsSpawn][3], plate);

	if(vehicleid == INVALID_VEHICLE_ID) {
		SendClientMessage(playerid, COLOR_GRAD1, "Nie można teraz kupić pojazdu, spróbuj później.");
		return 0;
	}

	// Pieniadze zabieramy dopiero po udanym dodaniu pojazdu
	TakePlayerCash(playerid, price);

	GetPlayerName(playerid, name, sizeof(name));
	printf("[SALON] %s kupil %s (model %d, kolor %d, silnik %d) za %d$, slot: %d, tablica: %s", name, DealershipOffers[offer][ofName], DealershipOffers[offer][ofModel], colorid, enginetype, price, vehicleid, plate);

	new fuelname[16], offername[24];

	format(fuelname, sizeof(fuelname), "%s", DealershipFuelNames[DealershipFuel[playerid]]);
	format(offername, sizeof(offername), "%s", DealershipOffers[offer][ofName]);

	CloseDealership(playerid);
	PutPlayerInVehicle(playerid, vehicleid, 0);

	format(str, sizeof(str), "Kupiłeś pojazd %s za %d$ (paliwo: %s). Tablica rejestracyjna: %s.", offername, price, fuelname, plate);
	SendClientMessage(playerid, COLOR_YELLOW, str);
	return 1;
}

// Zmiana wyboru strzalkami: horizontal -1/1 (lewo/prawo), vertical -1/1 (gora/dol)
stock MoveDealershipSelection(playerid, horizontal, vertical) {
	new delta;

	switch(DealershipStep[playerid]) {
		case DEALERSHIP_STEP_VEHICLE: {
			new count = GetDealershipOfferCount(DealershipPlayer[playerid]);

			if(!horizontal || count < 2) {
				return 0;
			}

			DealershipOffer[playerid] = ((DealershipOffer[playerid] + horizontal) % count + count) % count;
		}
		case DEALERSHIP_STEP_COLOR: {
			// Siatka 4 kolumny: gora/dol przeskakuja o caly rzad
			delta = horizontal + vertical * 4;

			DealershipColor[playerid] = ((DealershipColor[playerid] + delta) % DEALERSHIP_COLORS + DEALERSHIP_COLORS) % DEALERSHIP_COLORS;
		}
		case DEALERSHIP_STEP_FUEL: {
			delta = horizontal + vertical;

			DealershipFuel[playerid] = ((DealershipFuel[playerid] + delta) % DEALERSHIP_FUELS + DEALERSHIP_FUELS) % DEALERSHIP_FUELS;
		}
		default: {
			return 0;
		}
	}

	RefreshDealershipTextDraws(playerid);
	return 1;
}

// Klawisz Y: nastepny krok, na podsumowaniu zakup
stock ConfirmDealershipStep(playerid) {
	if(DealershipStep[playerid] == DEALERSHIP_STEP_SUMMARY) {
		return BuyDealershipVehicle(playerid);
	}

	DealershipStep[playerid]++;

	RefreshDealershipTextDraws(playerid);
	return 1;
}

// Klawisz N: poprzedni krok, na pierwszym zamkniecie salonu
stock BackDealershipStep(playerid) {
	if(DealershipStep[playerid] == DEALERSHIP_STEP_VEHICLE) {
		return CloseDealership(playerid);
	}

	DealershipStep[playerid]--;

	RefreshDealershipTextDraws(playerid);
	return 1;
}

// Wywolaj w OnPlayerKeyStateChange, zwraca 1 gdy klawisz zostal obsluzony przez salon
stock HandleDealershipKeys(playerid, newkeys, oldkeys) {
	if(DealershipPlayer[playerid] == -1) {
		return 0;
	}

	if((newkeys & KEY_YES) && !(oldkeys & KEY_YES)) {
		ConfirmDealershipStep(playerid);
		return 1;
	}

	if((newkeys & KEY_NO) && !(oldkeys & KEY_NO)) {
		BackDealershipStep(playerid);
		return 1;
	}
	return 0;
}

// Co 100 ms: strzalki (jednorazowo przy nacisnieciu), pilnowanie gracza w miejscu
Callback DealershipUpdate() {
	new keys, updown, leftright;

	foreach(new i : Player) {
		if(DealershipPlayer[i] == -1) {
			continue;
		}

		if(GetPlayerState(i) != PLAYER_STATE_ONFOOT) {
			CloseDealership(i);
			continue;
		}

		if(!IsPlayerInRangeOfPoint(i, 1.0, DealershipPos[i][0], DealershipPos[i][1], DealershipPos[i][2])) {
			SetPlayerPos(i, DealershipPos[i][0], DealershipPos[i][1], DealershipPos[i][2]);
		}

		GetPlayerKeys(i, keys, updown, leftright);

		if(leftright != DealershipLastLeftRight[i]) {
			DealershipLastLeftRight[i] = leftright;

			if(leftright < 0) {
				MoveDealershipSelection(i, -1, 0);
			} else if(leftright > 0) {
				MoveDealershipSelection(i, 1, 0);
			}
		}

		// Odswiezenie moglo zamknac salon, wiec sprawdzamy to jeszcze raz
		if(DealershipPlayer[i] == -1) {
			continue;
		}

		if(updown != DealershipLastUpDown[i]) {
			DealershipLastUpDown[i] = updown;

			if(updown < 0) {
				MoveDealershipSelection(i, 0, -1);
			} else if(updown > 0) {
				MoveDealershipSelection(i, 0, 1);
			}
		}
	}
	return 1;
}

CMD:kuppojazd(playerid, params[]) {
	if(DealershipPlayer[playerid] != -1) {
		return 1;
	}

	new dealership = GetPlayerDealership(playerid);

	if(dealership == -1) {
		return SendClientMessage(playerid, COLOR_GRAD1, "Nie znajdujesz się w salonie samochodowym.");
	}

	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) {
		return SendClientMessage(playerid, COLOR_GRAD1, "Musisz być pieszo, aby przeglądać ofertę salonu.");
	}

	if(!OpenDealership(playerid, dealership)) {
		return SendClientMessage(playerid, COLOR_GRAD1, "Ten salon nie ma obecnie żadnych ofert.");
	}
	return 1;
}
