/*
	Project: GodFather
	Author: MisterMagik, steeZ, Claude Speed
	File name: dealership.inc
	Date: 12.03.2026
	Modified: 12.03.2026
	Desc: Dealership system.

	System salonów samochodowych.
	Umo¿liwia zakup wybranego pojazdu wraz z wyborem koloru oraz typu silnika.
	Iloœæ salonów bêdzie wynosi³a ok 5. S¹ one po³¹czone z systemem biznesów.
	Salon musi zostaæ stworzony obok dzia³aj¹cego biznesu.
	Doda³em tu inny styl deklarowania zmiennych lokalnych.
*/

stock PlayerText:CreateDealershipBox(playerid, Float:X, Float:Y, Float:EndX, Float:Height, Color) {
	new PlayerText:pTD = CreatePlayerTextDraw(playerid, X, Y, "_");

	PlayerTextDrawLetterSize(playerid, pTD, 0.0, Height);
	PlayerTextDrawTextSize(playerid, pTD, EndX, 0.0);
	PlayerTextDrawAlignment(playerid, pTD, 1);
	PlayerTextDrawUseBox(playerid, pTD, 1);
	PlayerTextDrawBoxColor(playerid, pTD, Color);
	PlayerTextDrawSetShadow(playerid, pTD, 0);
	PlayerTextDrawFont(playerid, pTD, 1);
	return pTD;
}

stock PlayerText:CreateDealershipLabel(playerid, Float:X, Float:Y, String[], Float:LetterX, Float:LetterY, Color, Font) {
	new PlayerText:pTD = CreatePlayerTextDraw(playerid, X, Y, String);

	PlayerTextDrawLetterSize(playerid, pTD, LetterX, LetterY);
	PlayerTextDrawAlignment(playerid, pTD, 1);
	PlayerTextDrawColor(playerid, pTD, Color);
	PlayerTextDrawSetShadow(playerid, pTD, 1);
	PlayerTextDrawFont(playerid, pTD, Font);
	PlayerTextDrawSetProportional(playerid, pTD, 1);
	return pTD;
}

stock PlayerText:CreateDealershipOption(playerid, Float:X, Float:Y, Float:EndX, Float:Height, Float:LetterX, BoxColor, String[]) {
	new PlayerText:pTD = CreatePlayerTextDraw(playerid, X, Y, String);

	PlayerTextDrawLetterSize(playerid, pTD, LetterX, Height);
	PlayerTextDrawTextSize(playerid, pTD, EndX, 0.0);
	PlayerTextDrawAlignment(playerid, pTD, 1);
	PlayerTextDrawColor(playerid, pTD, 0xFFFFFFFF);
	PlayerTextDrawUseBox(playerid, pTD, 1);
	PlayerTextDrawBoxColor(playerid, pTD, BoxColor);
	PlayerTextDrawSetShadow(playerid, pTD, 0);
	PlayerTextDrawFont(playerid, pTD, 1);
	PlayerTextDrawSetProportional(playerid, pTD, 1);
	return pTD;
}

stock InitDealershipData() {
	printf("[SALON] Zaczynam ladowac salony...");

	format(DealershipInfo[0][dName], 32, "Coutt & Schutz");
	DealershipInfo[0][dPickupPos][0] = 2131.8259;
	DealershipInfo[0][dPickupPos][1] = -1151.3245;
	DealershipInfo[0][dPickupPos][2] = 24.0601;
	DealershipInfo[0][dVehSpawn][0] = 2135.9910;
	DealershipInfo[0][dVehSpawn][1] = -1143.2273;
	DealershipInfo[0][dVehSpawn][2] = 24.8318;
	DealershipInfo[0][dVehSpawn][3] = 88.1830;

	for(new i = 0; i < sizeof(cheapVehicles); i++) {
		AddDealershipOffer(0, cheapVehicles[i][0], cheapVehicles[i][1], VehicleNames[cheapVehicles[i][0] - 400]);
	}

	for(new i = 0; i < MAX_DEALERSHIPS; i++) {
		if(DealershipInfo[i][dPickupPos][0] != 0.0 && DealershipInfo[i][dPickupPos][1]) {
			DealershipInfo[i][dPickupID] = CreateDynamicPickup(1239, 1, DealershipInfo[i][dPickupPos][0], DealershipInfo[i][dPickupPos][1], DealershipInfo[i][dPickupPos][2]);

			CreateDynamic3DTextLabel("/kuppojazd", COLOR_WHITE, DealershipInfo[i][dPickupPos][0], DealershipInfo[i][dPickupPos][1], DealershipInfo[i][dPickupPos][2]+0.5, 30.0);
		}
	}

	printf("[SALON] Wczytano %d salonow i %d ofert.", MAX_DEALERSHIPS, ActualDealershipOffers);
}

stock CreateDealershipTextDraws(playerid, DealershipId) {
	new PlayerText:pTD;
	new Float:X, Float:Y;
	new String[64];

	DealershipTDs[playerid][0] = CreateDealershipBox(playerid, 0.0, 0.0, 640.0, 49.5, 0x000000A0);
	DealershipTDs[playerid][1] = CreateDealershipBox(playerid, 110.0, 95.0, 530.0, 26.4, 0x1E1E26F2);
	DealershipTDs[playerid][2] = CreateDealershipBox(playerid, 110.0, 95.0, 530.0, 2.7, 0x101016FF);
	DealershipTDs[playerid][3] = CreateDealershipBox(playerid, 110.0, 125.0, 530.0, 0.2, 0xFFAA00FF);

	DealershipTDs[playerid][4] = CreateDealershipLabel(playerid, 125.0, 99.0, DealershipInfo[DealershipId][dName], 0.5, 2.0, 0xFFFFFFFF, 2);
	DealershipTDs[playerid][5] = CreateDealershipLabel(playerid, 355.0, 108.0, "_", 0.26, 1.1, 0xFFAA00FF, 1);

	DealershipTDs[playerid][6] = CreateDealershipBox(playerid, 125.0, 135.0, 325.0, 12.0, 0x2C2C38FF);

	pTD = CreatePlayerTextDraw(playerid, 125.0, 135.0, "_");
	PlayerTextDrawFont(playerid, pTD, 5);
	PlayerTextDrawTextSize(playerid, pTD, 200.0, 132.0);
	PlayerTextDrawBackgroundColor(playerid, pTD, 0x00000000);
	PlayerTextDrawSetPreviewRot(playerid, pTD, -16.0, 0.0, -55.0, 0.9);

	DealershipTDs[playerid][7] = pTD;

	DealershipTDs[playerid][8] = CreateDealershipLabel(playerid, 128.0, 271.0, "_", 0.45, 1.9, 0xFFFFFFFF, 2);
	DealershipTDs[playerid][9] = CreateDealershipLabel(playerid, 128.0, 293.0, "_", 0.45, 1.8, 0x66FF66FF, 2);
	DealershipTDs[playerid][10] = CreateDealershipLabel(playerid, 128.0, 320.0, "_", 0.4, 1.6, 0xCCCCCCFF, 1);

	DealershipTDs[playerid][11] = CreateDealershipLabel(playerid, 345.0, 133.0, "_", 0.3, 1.3, 0xAAAAAAFF, 1);

	for(new i = 0; i < DEALERSHIP_COLORS; i++) {
		X = 347.0 + float(i % 4) * 44.0;
		Y = 150.0 + float(i / 4) * 26.0;

		DealershipTDColorFrame[playerid][i] = CreateDealershipBox(playerid, X - 2.0, Y - 2.0, X + 38.0, 2.2, 0x00000000);
		DealershipTDColor[playerid][i] = CreateDealershipBox(playerid, X, Y, X + 36.0, 1.5, DealershipColorHexes[i]);
	}

	DealershipTDs[playerid][12] = CreateDealershipLabel(playerid, 345.0, 232.0, "_", 0.3, 1.3, 0xAAAAAAFF, 1);

	for(new i = 0; i < DEALERSHIP_FUEL_TYPES; i++) {
		if(DealershipFuelPrices[i]) {
			format(String, sizeof(String), "  %s  (+$%d)", DealershipFuelNames[i], DealershipFuelPrices[i]);
		} else {
			format(String, sizeof(String), "  %s", DealershipFuelNames[i]);
		}

		DealershipTDFuel[playerid][i] = CreateDealershipOption(playerid, 345.0, 248.0 + float(i) * 24.0, 515.0, 1.9, 0.34, 0x3A3A44FF, String);
	}

	DealershipTDs[playerid][13] = CreateDealershipBox(playerid, 345.0, 133.0, 515.0, 17.0, 0x2C2C38FF);

	pTD = CreateDealershipLabel(playerid, 355.0, 140.0, "_", 0.33, 1.3, 0xFFFFFFFF, 1);
	PlayerTextDrawTextSize(playerid, pTD, 510.0, 0.0);

	DealershipTDs[playerid][14] = pTD;
	DealershipTDs[playerid][15] = CreateDealershipOption(playerid, 125.0, 352.0, 515.0, 2.0, 0.3, 0x101016FF, "_");
	return 1;
}

stock AddDealershipOffer(DealershipId, ModelId, Price, const Name[]) {
	if(ActualDealershipOffers >= MAX_DEALERSHIP_OFFERS) {
		printf("[SALON] Przekroczono limit ofert (%d).", MAX_DEALERSHIP_OFFERS);
		return 1;
	}

	new Id = ActualDealershipOffers;

	DealershipOffer[Id][doDealershipID] = DealershipId;
	DealershipOffer[Id][doModelID] = ModelId;
	DealershipOffer[Id][doPrice] = Price;
	format(DealershipOffer[Id][doName], 24, Name);

	ActualDealershipOffers++;
	return 1;
}

stock GetDealershipOfferCount(DealershipId) {
	new Count = 0;

	for(new i = 0; i < ActualDealershipOffers; i++) {
		if(DealershipOffer[i][doDealershipID] == DealershipId) {
			Count++;
		}
	}
	return Count;
}

stock GetDealershipOffer(DealershipId, Index) {
	new Count = 0;

	for(new i = 0; i < ActualDealershipOffers; i++) {
		if(DealershipOffer[i][doDealershipID] != DealershipId) {
			continue;
		}

		if(Count == Index) {
			return i;
		}

		Count++;
	}
	return DEALERSHIP_NONE;
}

stock GetDealershipFinalPrice(playerid) {
	new OfferId = GetDealershipOffer(pDealership[playerid], pDealershipOffer[playerid]);

	if(OfferId != DEALERSHIP_NONE) {
		return DealershipOffer[OfferId][doPrice] + DealershipFuelPrices[pDealershipFuel[playerid]];
	}
	return 0;
}

stock GetDealershipID(playerid) {
	for(new i = 0; i < MAX_DEALERSHIPS; i++) {
		if(IsPlayerInRangeOfPoint(playerid, 2.0, DealershipInfo[i][dPickupPos][0], DealershipInfo[i][dPickupPos][1], DealershipInfo[i][dPickupPos][2])) {
			return i;
		}
	}
	return DEALERSHIP_NONE;
}

stock SetDealershipTextDraws(playerid) {
	new DealershipId = pDealership[playerid];
	new OfferId = GetDealershipOffer(DealershipId, pDealershipOffer[playerid]);
	new Step = pDealershipStep[playerid];
	new ColorId = DealershipColorIDs[pDealershipColor[playerid]];
	new Price = GetDealershipFinalPrice(playerid);
	new String[256];

	if(OfferId == DEALERSHIP_NONE) {
		return 1;
	}

	PlayerTextDrawSetPreviewModel(playerid, DealershipTDs[playerid][7], DealershipOffer[OfferId][doModelID]);
	PlayerTextDrawSetPreviewVehCol(playerid, DealershipTDs[playerid][7], ColorId, ColorId);
	
	PlayerTextDrawSetString(playerid, DealershipTDs[playerid][8], DealershipOffer[OfferId][doName]);

	format(String, sizeof(String), "$%d", Price);
	PlayerTextDrawSetString(playerid, DealershipTDs[playerid][9], String);

	format(String, sizeof(String), "~<~ %d/%d ~>~", pDealershipOffer[playerid] + 1, GetDealershipOfferCount(DealershipId));
	PlayerTextDrawSetString(playerid, DealershipTDs[playerid][10], String);

	format(String, sizeof(String), "Kolor: %s", DealershipColorNames[pDealershipColor[playerid]]);
	PlayerTextDrawSetString(playerid, DealershipTDs[playerid][11], String);
	PlayerTextDrawColor(playerid, DealershipTDs[playerid][11], (Step == 1 ? 0xFFAA00FF : 0xAAAAAAFF));

	format(String, sizeof(String), "Paliwo: %s", DealershipFuelNames[pDealershipFuel[playerid]]);
	PlayerTextDrawSetString(playerid, DealershipTDs[playerid][12], String);
	PlayerTextDrawColor(playerid, DealershipTDs[playerid][12], (Step == 2 ? 0xFFAA00FF : 0xAAAAAAFF));

	for(new i = 0; i < DEALERSHIP_COLORS; i++) {
		if(i == pDealershipColor[playerid]) {
			PlayerTextDrawBoxColor(playerid, DealershipTDColorFrame[playerid][i], (Step == 1 ? 0xFFFFFFFF : 0x777777FF));
		} else {
			PlayerTextDrawBoxColor(playerid, DealershipTDColorFrame[playerid][i], 0x00000000);
		}
	}

	for(new i = 1; i <= DEALERSHIP_FUEL_TYPES; i++) {
		if(i == pDealershipFuel[playerid]) {
			PlayerTextDrawBoxColor(playerid, DealershipTDFuel[playerid][i], (Step == 2 ? 0x2E7D32FF : 0x24402AFF));
		} else {
			PlayerTextDrawBoxColor(playerid, DealershipTDFuel[playerid][i], 0x3A3A44FF);
		}
	}

	switch(Step) {
		case 0: {
			PlayerTextDrawSetString(playerid, DealershipTDs[playerid][5], "Krok 1/4: Wybierz pojazd");
			PlayerTextDrawSetString(playerid, DealershipTDs[playerid][15], " ~y~Strzalki~w~ zmiana pojazdu	~g~Y~w~ dalej	~r~N~w~ zamknij");
		}
		case 1: {
			PlayerTextDrawSetString(playerid, DealershipTDs[playerid][5], "Krok 2/4: Wybierz kolor");
			PlayerTextDrawSetString(playerid, DealershipTDs[playerid][15], " ~y~Strzalki~w~ wybor koloru	~g~Y~w~ dalej	~r~N~w~ wstecz");
		}
		case 2: {
			PlayerTextDrawSetString(playerid, DealershipTDs[playerid][5], "Krok 3/4: Wybierz paliwo");
			PlayerTextDrawSetString(playerid, DealershipTDs[playerid][15], " ~y~Strzalki~w~ wybor paliwa	~g~Y~w~ dalej	~r~N~w~ wstecz");
		}
		case 3: {
			PlayerTextDrawSetString(playerid, DealershipTDs[playerid][5], "Krok 4/4: Podsumowanie");
			PlayerTextDrawSetString(playerid, DealershipTDs[playerid][15], " ~g~Y~w~ Kup	~r~N~w~ wstecz");
		}
	}

	format(String, sizeof(String), "Podsumowanie~n~~n~Pojazd: %s~n~Kolor: %s~n~Paliwo: %s~n~~n~Cena: $%d~n~Twoja gotowka: $%d", DealershipOffer[OfferId][doName], DealershipColorNames[pDealershipColor[playerid]], DealershipFuelNames[pDealershipFuel[playerid]], Price, GetPlayerMoney(playerid));
	PlayerTextDrawSetString(playerid, DealershipTDs[playerid][14], String);
	return 1;
}

stock ShowDealershipTextDraws(playerid) {
	for(new i = 0; i < 16; i++) {
		PlayerTextDrawShow(playerid, DealershipTDs[playerid][i]);
	}

	for(new i = 0; i < DEALERSHIP_COLORS; i++) {
		PlayerTextDrawShow(playerid, DealershipTDColorFrame[playerid][i]);
		PlayerTextDrawShow(playerid, DealershipTDColor[playerid][i]);
	}

	for(new i = 0; i < DEALERSHIP_FUEL_TYPES; i++) {
		PlayerTextDrawShow(playerid, DealershipTDFuel[playerid][i]);
	}
}

stock UpdateDealershipTextDraws(playerid) {
	if(!SetDealershipTextDraws(playerid)) {
		return 1;
	}

	new bool:bSummary = (pDealershipStep[playerid] == 3);

	PlayerTextDrawShow(playerid, DealershipTDs[playerid][7]);
	PlayerTextDrawShow(playerid, DealershipTDs[playerid][5]);
	PlayerTextDrawShow(playerid, DealershipTDs[playerid][15]);

	if(bSummary) {
		PlayerTextDrawHide(playerid, DealershipTDs[playerid][11]);
		PlayerTextDrawHide(playerid, DealershipTDs[playerid][12]);

		for(new i = 0; i < DEALERSHIP_COLORS; i++) {
			PlayerTextDrawHide(playerid, DealershipTDColorFrame[playerid][i]);
			PlayerTextDrawHide(playerid, DealershipTDColor[playerid][i]);
		}

		for(new i = 0; i < DEALERSHIP_FUEL_TYPES; i++) {
			PlayerTextDrawHide(playerid, DealershipTDFuel[playerid][i]);
		}

		PlayerTextDrawShow(playerid, DealershipTDs[playerid][13]);
		PlayerTextDrawShow(playerid, DealershipTDs[playerid][14]);
	} else {
		PlayerTextDrawHide(playerid, DealershipTDs[playerid][13]);
		PlayerTextDrawHide(playerid, DealershipTDs[playerid][14]);

		PlayerTextDrawShow(playerid, DealershipTDs[playerid][11]);
		PlayerTextDrawShow(playerid, DealershipTDs[playerid][12]);

		for(new i = 0; i < DEALERSHIP_COLORS; i++) {
			PlayerTextDrawShow(playerid, DealershipTDColorFrame[playerid][i]);
			PlayerTextDrawShow(playerid, DealershipTDColor[playerid][i]);
		}

		for(new i = 0; i < DEALERSHIP_FUEL_TYPES; i++) {
			PlayerTextDrawShow(playerid, DealershipTDFuel[playerid][i]);
		}
	}
	return 1;
}

stock ShowDealershipInterface(playerid, DealershipId) {
	if(pDealership[playerid] != DEALERSHIP_NONE) {
		return 1;
	}

	if(!GetDealershipOfferCount(DealershipId)) {
		return 1;
	}

	pDealership[playerid] = DealershipId;
	pDealershipStep[playerid] = 0;
	pDealershipOffer[playerid] = 0;
	pDealershipColor[playerid] = 0;
	pDealershipFuel[playerid] = VEHICLE_ENGINE_NONE;
	pDealershipLastUDKey[playerid] = 0;
	pDealershipLastLRKey[playerid] = 0;

	osrp_TogglePlayerControllable(playerid, 0);

	CreateDealershipTextDraws(playerid, DealershipId);
	ShowDealershipTextDraws(playerid);
	UpdateDealershipTextDraws(playerid);
	return 1;
}

stock HideDealershipInterface(playerid) {
	if(pDealership[playerid] == DEALERSHIP_NONE) {
		return 1;
	}

	pDealership[playerid] = DEALERSHIP_NONE;
	osrp_TogglePlayerControllable(playerid, 1);

	for(new i = 0; i < 16; i++) {
		PlayerTextDrawDestroy(playerid, DealershipTDs[playerid][i]);

		DealershipTDs[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
	}

	for(new i = 0; i < DEALERSHIP_COLORS; i++) {
		PlayerTextDrawDestroy(playerid, DealershipTDColorFrame[playerid][i]);
		PlayerTextDrawDestroy(playerid, DealershipTDColor[playerid][i]);

		DealershipTDColorFrame[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
		DealershipTDColor[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
	}

	for(new i = 0; i < DEALERSHIP_FUEL_TYPES; i++) {
		PlayerTextDrawDestroy(playerid, DealershipTDFuel[playerid][i]);

		DealershipTDFuel[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
	}
	return 1;
}

stock BuyDealershipVehicle(playerid) {
	new DealershipId = pDealership[playerid];
	new OfferId = GetDealershipOffer(DealershipId, pDealershipOffer[playerid]);

	if(OfferId == DEALERSHIP_NONE) {
		return 1;
	}

	new Price = GetDealershipFinalPrice(playerid);
	new ColorId = DealershipColorIDs[pDealershipColor[playerid]];
	new EngineType = DealershipFuelTypes[pDealershipFuel[playerid]];

	AddVehicle(PlayerInfo[playerid][pID], VEHICLE_OWNER_TYPE_PLAYER, DealershipOffer[OfferId][doModelID], EngineType, ColorId, ColorId, 1, DealershipInfo[DealershipId][dVehSpawn][0], DealershipInfo[DealershipId][dVehSpawn][1], DealershipInfo[DealershipId][dVehSpawn][2], DealershipInfo[DealershipId][dVehSpawn][3]);

	HideDealershipInterface(playerid);
	return 1;
}

stock MoveDealershipSelection(playerid, Horz, Vert) {
	new Delta = 0;

	switch(pDealershipStep[playerid]) {
		case 0: {
			new Count = GetDealershipOfferCount(pDealership[playerid]);

			if(!Horz || Count < 2) {
				return 1;
			}

			pDealershipOffer[playerid] = ((pDealershipOffer[playerid] + Horz) % Count + Count) % Count;
		}
		case 1: {
			Delta = Horz + Vert * 4;
			pDealershipColor[playerid] = ((pDealershipColor[playerid] + Delta) % DEALERSHIP_COLORS + DEALERSHIP_COLORS) % DEALERSHIP_COLORS;
		}
		case 2: {
			Delta = Horz + Vert;
			pDealershipFuel[playerid] = ((pDealershipFuel[playerid] + Delta) % DEALERSHIP_FUEL_TYPES + DEALERSHIP_FUEL_TYPES) % DEALERSHIP_FUEL_TYPES;
		}
		default: {
			return 1;
		}
	}

	UpdateDealershipTextDraws(playerid);
	return 1;
}

stock NextDealershipKeyStep(playerid) {
	if(pDealershipStep[playerid] == 3) {
		return BuyDealershipVehicle(playerid);
	}

	pDealershipStep[playerid]++;

	UpdateDealershipTextDraws(playerid);
	return 1;
}

stock BackDealershipKeyStep(playerid) {
	if(pDealershipStep[playerid] == 0) {
		return HideDealershipInterface(playerid);
	}

	pDealershipStep[playerid]--;

	UpdateDealershipTextDraws(playerid);
	return 1;
}

CMD:kuppojazd(playerid, params[]) {
	ShowDealershipInterface(playerid, 0);
	return 1;
}
