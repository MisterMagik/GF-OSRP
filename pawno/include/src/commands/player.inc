/*
	Project: GodFather
	Author: MisterMagik, steeZ
	File name: commands/player.inc
	Date: 12.03.2026
	Modified: 12.03.2026
	Desc: Player commands.
*/

CMD:pay(playerid, params[]) {
	new giveplayerid, moneys;

	if(sscanf(params, "ii", giveplayerid, moneys)) {
		return SendClientMessage(playerid, COLOR_GRAD1, "Użyj: /pay [playerid/PartOfName] [ilosc]");
	}

	if(moneys > 1000 && PlayerInfo[playerid][pLevel] < 3) {
		return SendClientMessage(playerid, COLOR_GRAD1, "Musisz miec level 3, aby dac 1000");
	}

	if(moneys < 1 || moneys > 99999) {
		return SendClientMessage(playerid, COLOR_GRAD1, "Dont go below 1, or above 99999 at once.");
	}

	if(!IsPlayerConnected(giveplayerid)) {
		format(gString, sizeof(gString), "   %d nie jest w grze.", giveplayerid);
		return SendClientMessage(playerid, COLOR_GRAD1, gString);
	}

	if(PlayerInfo[giveplayerid][pLocal] == 106) {
		return SendClientMessage(playerid, COLOR_GRAD1, "Ta komenda nie jest dostepna w tym miejscu");
	}

	if(!ProxDetectorS(5.0, playerid, giveplayerid)) {
		return SendClientMessage(playerid, COLOR_GRAD1, "   Your too far away.");
	}

	new playermoney = GetPlayerMoney(playerid);

	if(moneys > 0 && playermoney >= moneys) {
		ConsumingMoney[giveplayerid] = 1;
		GivePlayerMoney(playerid, (0 - moneys));
		GivePlayerMoney(giveplayerid, moneys);
		format(gString, sizeof(gString), "   You have sent %s(player: %d), $%d.", PlayerInfo[giveplayerid][pName],giveplayerid, moneys);
		PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
		SendClientMessage(playerid, COLOR_GRAD1, gString);
		format(gString, sizeof(gString), "   You have recieved $%d from %s(player: %d).", moneys, PlayerInfo[playerid][pName], playerid);
		SendClientMessage(giveplayerid, COLOR_GRAD1, gString);
		format(gString, sizeof(gString), "%s has paid $%d to %s", PlayerInfo[playerid][pName], moneys, PlayerInfo[giveplayerid][pName]);
		PayLog(gString);

		if(moneys >= 1000000) {
			ABroadCast(COLOR_YELLOW,gString,1);
		}

		PlayerPlaySound(giveplayerid, 1052, 0.0, 0.0, 0.0);
		format(gString, sizeof(gString), "* %s takes out some cash, and hands it to %s.", PlayerInfo[playerid][pName] ,PlayerInfo[giveplayerid][pName]);
		ProxDetector(30.0, playerid, gString, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
	} else {
		SendClientMessage(playerid, COLOR_GRAD1, "   Invalid transaction amount.");
	}
	return 1;
}

CMD:charity(playerid, params[]) {
	new moneys;

	if(sscanf(params, "i", moneys)) {
		return SendClientMessage(playerid, COLOR_GRAD1, "Uzycie: /charity [ilosc]");
	}

	if(PlayerInfo[playerid][pLocal] == 106) {
		return SendClientMessage(playerid, COLOR_GRAD1, "Ta komenda nie jest dostepna w tym miejscu");
	}

	if(moneys < 0) {
		return SendClientMessage(playerid, COLOR_GRAD1, "That is not enough.");
	}

	if(GetPlayerMoney(playerid) < moneys) {
		return SendClientMessage(playerid, COLOR_GRAD1, "You don't have that much money.");
	}

	GivePlayerMoney(playerid, -moneys);
	format(gString, sizeof(gString), "%s Thank you for you donation of, $%d.",PlayerInfo[playerid][pName], moneys);
	printf("%s", gString);
	PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
	SendClientMessage(playerid, COLOR_GRAD1, gString);
	PayLog(gString);
	return 1;
}

CMD:stats(playerid, params[]) {
	if(!gPlayerLogged[playerid]) {
		return SendClientMessage(playerid, COLOR_GRAD1, "   Nie jesteś zalogowany !");
	}

	ShowStats(playerid,playerid);
	return 1;
}

CMD:dn(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] < 1) {
		return SendClientMessage(playerid, COLOR_GRAD1, "   Nie jestes administratorem !");
	}

	new Float:slx, Float:sly, Float:slz;

	GetPlayerPos(playerid, slx, sly, slz);
	SetPlayerPos(playerid, slx, sly, slz-2);
	return 1;
}

CMD:up(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] < 1) {
		return SendClientMessage(playerid, COLOR_GRAD1, "   Nie jestes administratorem !");
	}

	new Float:slx, Float:sly, Float:slz;

	GetPlayerPos(playerid, slx, sly, slz);
	SetPlayerPos(playerid, slx, sly, slz+2);
	return 1;
}

CMD:fly(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] < 1) {
		return SendClientMessage(playerid, COLOR_GRAD1, "   Nie jestes administratorem !");
	}

	new Float:px, Float:py, Float:pz, Float:pa;

	GetPlayerFacingAngle(playerid,pa);
	GetPlayerPos(playerid, px, py, pz);

	if(pa >= 0.0 && pa <= 22.5) { //n1
		SetPlayerPos(playerid, px, py+30, pz+5);
	}

	if(pa >= 332.5 && pa < 0.0) { //n2
		SetPlayerPos(playerid, px, py+30, pz+5);
	}

	if(pa >= 22.5 && pa <= 67.5) { //nw
		SetPlayerPos(playerid, px-15, py+15, pz+5);
	}

	if(pa >= 67.5 && pa <= 112.5) { //w
		SetPlayerPos(playerid, px-30, py, pz+5);
	}

	if(pa >= 112.5 && pa <= 157.5) { //sw
		SetPlayerPos(playerid, px-15, py-15, pz+5);
	}

	if(pa >= 157.5 && pa <= 202.5) { //s
		SetPlayerPos(playerid, px, py-30, pz+5);
	}

	if(pa >= 202.5 && pa <= 247.5) {//se
		SetPlayerPos(playerid, px+15, py-15, pz+5);
	}

	if(pa >= 247.5 && pa <= 292.5) {//e
		SetPlayerPos(playerid, px+30, py, pz+5);
	}

	if(pa >= 292.5 && pa <= 332.5) {//e
		SetPlayerPos(playerid, px+15, py+15, pz+5);
	}
	return 1;
}

CMD:lt(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] < 1) {
		return SendClientMessage(playerid, COLOR_GRAD1, "   Nie jestes administratorem !");
	}

	new Float:slx, Float:sly, Float:slz;

	GetPlayerPos(playerid, slx, sly, slz);
	SetPlayerPos(playerid, slx, sly+2, slz);
	return 1;
}

CMD:rt(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] < 1) {
		return SendClientMessage(playerid, COLOR_GRAD1, "   Nie jestes administratorem !");
	}

	new Float:slx, Float:sly, Float:slz;

	GetPlayerPos(playerid, slx, sly, slz);
	SetPlayerPos(playerid, slx, sly-2, slz-2);
	return 1;
}

CMD:check(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] < 1) {
		return SendClientMessage(playerid, COLOR_GRAD1, "   Nie jestes administratorem !");
	}

	new giveplayerid;

	if(sscanf(params, "i", giveplayerid)) {
		return SendClientMessage(playerid, COLOR_GRAD1, "Uzycie: /check [playerid/PartOfName]");
	}

	if(!IsPlayerConnected(giveplayerid)) {
		return SendClientMessage(playerid, COLOR_GRAD1, "   Nie ma takiego gracza online");
	}

	ShowStats(playerid,giveplayerid);
	return 1;
}

CMD:number(playerid, params[]) {
	if(!PlayerInfo[playerid][pPhoneBook]) {
		return SendClientMessage(playerid, COLOR_GRAD1, "   Nie posiadasz ksiazki telefonicznej !");
	}

	new giveplayerid;

	if(sscanf(params, "i", giveplayerid)) {
		return SendClientMessage(playerid, COLOR_GRAD1, "Uzycie: /number [playerid/PartOfName]");
	}

	if(!IsPlayerConnected(giveplayerid)) {
		return SendClientMessage(playerid, COLOR_GRAD1, "   No Such Player !");
	}

	format(gString, 256, "Name: %s, Ph: %d",PlayerInfo[playerid][pName],PlayerInfo[giveplayerid][pPnumber]);
	SendClientMessage(playerid, COLOR_GRAD1, gString);
	return 1;
}

CMD:buylevel(playerid, params[]) {
	if(!gPlayerLogged[playerid]) {
		return SendClientMessage(playerid, COLOR_GRAD1, "   You are not Logged in !");
	}

	PlayerInfo[playerid][pCash] = GetPlayerMoney(playerid);

	if(PlayerInfo[playerid][pLevel] >= 0) {
		new nxtlevel = PlayerInfo[playerid][pLevel]+1;
		new costlevel = nxtlevel*levelcost;//10k for testing purposes
		new expamount = nxtlevel*levelexp;
		new infostring[256];

		if(GetPlayerMoney(playerid) < costlevel) {
			format(infostring, 256, "   You do not have enough Cash ($%d) !",costlevel);
			SendClientMessage(playerid, COLOR_GRAD1, infostring);
		} else if (PlayerInfo[playerid][pExp] < expamount) {
			format(infostring, 256, "   You need %d Respect Points, you curently have [%d] !",expamount,PlayerInfo[playerid][pExp]);
			SendClientMessage(playerid, COLOR_GRAD1, infostring);
		} else {
			format(gString, sizeof(gString), "~g~LEVEL UP~n~~w~You Are Now Level %d", nxtlevel);
			PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
			PlayerPlayMusic(playerid);
			GivePlayerMoney(playerid, (-costlevel));
			PlayerInfo[playerid][pLevel]++;

			if(PlayerInfo[playerid][pDonateRank] > 0) {
				PlayerInfo[playerid][pExp] -= expamount;
				new total = PlayerInfo[playerid][pExp];

				if(total > 0) {
					PlayerInfo[playerid][pExp] = total;
				} else {
					PlayerInfo[playerid][pExp] = 0;
				}
			} else {
				PlayerInfo[playerid][pExp] = 0;
			}

			PlayerInfo[playerid][gPupgrade] = PlayerInfo[playerid][gPupgrade]+2;
			GameTextForPlayer(playerid, gString, 5000, 1);
			format(infostring, 256, "   You bought Level %d for ($%d) Type /upgrade", nxtlevel, costlevel);
			SendClientMessage(playerid, COLOR_GRAD1, infostring);
			format(infostring, 256, "   You gave %d unspent Upgrade Points",PlayerInfo[playerid][gPupgrade]);
			SendClientMessage(playerid, COLOR_GRAD2, infostring);
		}
	}
	return 1;
}

CMD:carcolor(playerid, params[]) {
	new house = PlayerInfo[playerid][pPhousekey];

	if(house == 255 && strcmp(PlayerInfo[playerid][pName], HouseInfo[PlayerInfo[playerid][pPhousekey]][hOwner], true)) {
		return SendClientMessage(playerid, COLOR_GRAD2, "   You don't own a house");
	}

	new colornum, color;

	if(sscanf(params, "ii", colornum, color)) {
		return SendClientMessage(playerid, COLOR_GRAD3,"($5000) USAGE: /carcolor [color 1 - 2] [color number]");
	}

	if(colornum > 2 || colornum < 1) {
		return SendClientMessage(playerid, COLOR_GRAD3,"Choices are 1 or 2");
	}

	if(color > 126) {
		return SendClientMessage(playerid, COLOR_GRAD3,"Maximum is 126");
	}

	if(GetPlayerMoney(playerid) < 5000) {
		return SendClientMessage(playerid, COLOR_GRAD3,"You can't afford that ($5000)");
	}

	if(colornum == 1) {
		HouseInfo[house][hVcol1] = color;
		format(gString, sizeof(gString), "Car color 1 set to %d -$5000",color);
		SendClientMessage(playerid, COLOR_GRAD3,gString);
	} else {
		HouseInfo[house][hVcol2] = color;
		format(gString, sizeof(gString), "Car color 2 set to %d -$5000",color);
		SendClientMessage(playerid, COLOR_GRAD3,gString);
	}

	SendClientMessage(playerid, COLOR_GRAD6, "Your new paintjob will be complete within 24 hours");
	GivePlayerMoney(playerid,-5000);
	SBizzInfo[5][sbTill] += 5000;
	ExtortionSBiz(5, 5000);
	PlayerPlaySound(playerid, 1134, 0.0, 0.0, 0.0);
	OnPropUpdate();
	return 1;
}

CMD:carupgrade(playerid, params[]) {
	new house = PlayerInfo[playerid][pPhousekey];

	if(house == 255 && strcmp(PlayerInfo[playerid][pName], HouseInfo[PlayerInfo[playerid][pPhousekey]][hOwner], true)) {
		return SendClientMessage(playerid, COLOR_GRAD2, "   You don't own a house");
	}

	new gunid[16];

	if(sscanf(params, "s[16]", gunid)) {
		format(gString, sizeof(gString), "Uzycie: /carupgrade [carname]");
		SendClientMessage(playerid, COLOR_GREEN,"_______________________________________");
		SendClientMessage(playerid, COLOR_WHITE,"*** CAR UPGRADES Cost $100000 ***");
		SendClientMessage(playerid, COLOR_GRAD2,gString);

		if(PlayerInfo[playerid][pLevel] >= 3) {
			SendClientMessage(playerid, COLOR_GRAD3, "Cars: blistacompact clover elegant emperor glendale greenwood");
			SendClientMessage(playerid, COLOR_GRAD3, "Cars: huntley jester landstalker merit nebula sabre stratum");
			SendClientMessage(playerid, COLOR_GRAD3, "Cars: sunrise tahoma uranus");
			SendClientMessage(playerid, COLOR_GRAD3, "Donation cars: stretch elegy phoenix hotknife bandito sultan");
		}

		SendClientMessage(playerid, COLOR_GREEN,"_______________________________________");
		return 1;
	}

	if(SBizzInfo[5][sbProducts] == 0) {
		return GameTextForPlayer(playerid, "~r~Out Of Stock", 5000, 1);
	}

	if(GetPlayerMoney(playerid) < 100000) {
		return SendClientMessage(playerid, COLOR_GRAD2, "   You can't afford that ($100000)");
	}

	if(!strcmp(gunid, "stretch", true, strlen(gunid))) {
		if(PlayerInfo[playerid][pDonateRank] < 1) {
			return SendClientMessage(playerid, COLOR_GREY, "   You don't have a Premium Account !");
		}

		SendClientMessage(playerid, COLOR_GRAD6, "New Upgrade: Your House Car Is Now A Stretch");
		HouseInfo[house][hVec] = 409;
	} else if(!strcmp(gunid, "hotknife", true, strlen(gunid))) {
		if(PlayerInfo[playerid][pDonateRank] < 1) {
			return SendClientMessage(playerid, COLOR_GREY, "   You don't have a Premium Account !");
		}

		SendClientMessage(playerid, COLOR_GRAD6, "New Upgrade: Your House Car Is Now A Hotknife");
		HouseInfo[house][hVec] = 434;
	} else if(!strcmp(gunid, "bandito", true, strlen(gunid))) {
		if(PlayerInfo[playerid][pDonateRank] < 1) {
			return SendClientMessage(playerid, COLOR_GREY, "   You don't have a Premium Account !");
		}

		SendClientMessage(playerid, COLOR_GRAD6, "New Upgrade: Your House Car Is Now A Bandito");
		HouseInfo[house][hVec] = 568;
	} else if(!strcmp(gunid, "sultan", true, strlen(gunid))) {
		if(PlayerInfo[playerid][pDonateRank] < 1) {
			return SendClientMessage(playerid, COLOR_GREY, "   You don't have a Premium Account !");
		}

		SendClientMessage(playerid, COLOR_GRAD6, "New Upgrade: Your House Car Is Now A Sultan");
		HouseInfo[house][hVec] = 560;
	} else if(!strcmp(gunid, "elegy", true, strlen(gunid))) {
		if(PlayerInfo[playerid][pDonateRank] < 1) {
			return SendClientMessage(playerid, COLOR_GREY, "   You don't have a Premium Account !");
		}

		SendClientMessage(playerid, COLOR_GRAD6, "New Upgrade: Your House Car Is Now A Elegy");
		HouseInfo[house][hVec] = 562;
	} else if(!strcmp(gunid, "phoenix", true, strlen(gunid))) {
		if(PlayerInfo[playerid][pDonateRank] < 1) {
			return SendClientMessage(playerid, COLOR_GREY, "   You don't have a Premium Account !");
		}

		SendClientMessage(playerid, COLOR_GRAD6, "New Upgrade: Your House Car Is Now A Phoenix");
		HouseInfo[house][hVec] = 603;
	} else if(!strcmp(gunid, "blistacompact", true, strlen(gunid))) {
		SendClientMessage(playerid, COLOR_GRAD6, "New Upgrade: Your House Car Is Now A Blista Compact");
		HouseInfo[house][hVec] = 496;
	} else if(!strcmp(gunid, "clover", true, strlen(gunid))) {
		SendClientMessage(playerid, COLOR_GRAD6, "New Upgrade: Your House Car Is Now A Clover");
		HouseInfo[house][hVec] = 542;
	} else if(!strcmp(gunid, "elegant", true, strlen(gunid))) {
		SendClientMessage(playerid, COLOR_GRAD6, "New Upgrade: Your House Car Is Now A Elegant");
		HouseInfo[house][hVec] = 507;
	} else if(!strcmp(gunid, "emperor", true, strlen(gunid))) {
		SendClientMessage(playerid, COLOR_GRAD6, "New Upgrade: Your House Car Is Now A Emperor");
		HouseInfo[house][hVec] = 585;
	} else if(!strcmp(gunid, "glendale", true, strlen(gunid))) {
		SendClientMessage(playerid, COLOR_GRAD6, "New Upgrade: Your House Car Is Now A Glendale");
		HouseInfo[house][hVec] = 466;
	} else if(!strcmp(gunid, "greenwood", true, strlen(gunid))) {
		SendClientMessage(playerid, COLOR_GRAD6, "New Upgrade: Your House Car Is Now A Greenwood");
		HouseInfo[house][hVec] = 492;
	} else if(!strcmp(gunid, "huntley", true, strlen(gunid))) {
		SendClientMessage(playerid, COLOR_GRAD6, "New Upgrade: Your House Car Is Now A Huntley");
		HouseInfo[house][hVec] = 579;
	} else if(!strcmp(gunid, "jester", true, strlen(gunid))) {
		SendClientMessage(playerid, COLOR_GRAD6, "New Upgrade: Your House Car Is Now A Jester");
		HouseInfo[house][hVec] = 559;
	} else if(!strcmp(gunid, "landstalker", true, strlen(gunid))) {
		SendClientMessage(playerid, COLOR_GRAD6, "New Upgrade: Your House Car Is Now A Landstalker");
		HouseInfo[house][hVec] = 400;
	} else if(!strcmp(gunid, "merit", true, strlen(gunid))) {
		SendClientMessage(playerid, COLOR_GRAD6, "New Upgrade: Your House Car Is Now A Merit");
		HouseInfo[house][hVec] = 551;
	} else if(!strcmp(gunid, "nebula", true, strlen(gunid))) {
		SendClientMessage(playerid, COLOR_GRAD6, "New Upgrade: Your House Car Is Now A Nebula");
		HouseInfo[house][hVec] = 516;
	} else if(!strcmp(gunid, "sabre", true, strlen(gunid))) {
		SendClientMessage(playerid, COLOR_GRAD6, "New Upgrade: Your House Car Is Now A Sabre");
		HouseInfo[house][hVec] = 475;
	} else if(!strcmp(gunid, "stratum", true, strlen(gunid))) {
		SendClientMessage(playerid, COLOR_GRAD6, "New Upgrade: Your House Car Is Now A Stratum");
		HouseInfo[house][hVec] = 561;
	} else if(!strcmp(gunid, "sunrise", true, strlen(gunid))) {
		SendClientMessage(playerid, COLOR_GRAD6, "New Upgrade: Your House Car Is Now A Sunrise");
		HouseInfo[house][hVec] = 550;
	} else if(!strcmp(gunid, "tahoma", true, strlen(gunid))) {
		SendClientMessage(playerid, COLOR_GRAD6, "New Upgrade: Your House Car Is Now A Tahoma");
		HouseInfo[house][hVec] = 566;
	} else if(!strcmp(gunid, "uranus", true, strlen(gunid))) {
		SendClientMessage(playerid, COLOR_GRAD6, "New Upgrade: Your House Car Is Now A Uranus");
		HouseInfo[house][hVec] = 558;
	} else {
		return SendClientMessage(playerid, COLOR_GRAD6, "   Unrecognized Car or Donate Rank not High enough.");
	}

	SendClientMessage(playerid, COLOR_GRAD6, "Your new car will be delivered within 24 hours -$100000");
	OnPropUpdate();
	GivePlayerMoney(playerid,-100000);
	SBizzInfo[5][sbTill] += 100000;
	ExtortionSBiz(5, 100000);
	SBizzInfo[5][sbProducts]--;
	PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
	return 1;
}

CMD:resetupgrades(playerid, params[]) {
	if(gPlayerLogged[playerid] == 0)	{
		return SendClientMessage(playerid, COLOR_GRAD1, "   You are not Logged in !");
	}

	if(GetPlayerMoney(playerid) < 100000) {
		return SendClientMessage(playerid, COLOR_GRAD1, "   Cost is $100000 !");
	}

	if(PlayerInfo[playerid][pLevel] < 2) {
		return SendClientMessage(playerid, COLOR_GRAD1, "   You need to be at least level 2 !");
	}

	PlayerInfo[playerid][gPupgrade] = (PlayerInfo[playerid][pLevel]-1)*2;
	PlayerInfo[playerid][pSHealth] = 0.0;
	PlayerInfo[playerid][pAlcoholPerk] = 0;
	PlayerInfo[playerid][pDrugPerk] = 0;
	PlayerInfo[playerid][pMiserPerk] = 0;
	PlayerInfo[playerid][pPainPerk] = 0;
	PlayerInfo[playerid][pTraderPerk] = 0;

	GivePlayerMoney(playerid,-100000);
	PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
	format(gString, 256, "   You have %d unspent Upgrade Points !",PlayerInfo[playerid][gPupgrade]);
	SendClientMessage(playerid, COLOR_GRAD2, gString);
	return 1;
}

CMD:buygun(playerid, params[]) {
	if(GetPlayerMoney(playerid) < 1) {
		return SendClientMessage(playerid, COLOR_GREY, "   You dont have enough money with you !");
	}

	new gun;
	new gunid[16];
	new gunstring1[256];
	new gunstring2[256];
	new gunstring3[256];
	new gunstring4[256];
	new gunstring5[256];
	new infostring[256];
	new guncharge;
	new ammocharge;
	new location = PlayerInfo[playerid][pLocal];

	if(location != 99 && location != 100 && location != 102) {
		return SendClientMessage(playerid, COLOR_WHITE,"You are not in a store.");
	}

	if(BizzInfo[location-99][bProducts] <= 0) 	{
		GameTextForPlayer(playerid, "~r~Out Of Stock", 5000, 1);
	}

	new mod = 100, ammo;

	if(sscanf(params, "s[16]i", gunid, ammo)) {
		format(gString, sizeof(gString), "Uzycie: /buygun [gunname] [ammoamount]");
		SendClientMessage(playerid, COLOR_GREEN,"_______________________________________");
		SendClientMessage(playerid, COLOR_WHITE,"*** Guns & Ammo ***");
		SendClientMessage(playerid, COLOR_GRAD2,gString);
		format(gunstring1, 256, "Weapons: parachute ($%d) golfclub ($%d) nightstick ($%d) baseballbat ($%d) shovel ($%d) poolcue ($%d)",
		GunPrice[0][0]/100*mod,GunPrice[1][0]/100*mod,GunPrice[2][0]/100*mod,GunPrice[3][0]/100*mod,GunPrice[4][0]/100*mod,GunPrice[5][0]/100*mod,GunPrice[6][0]/100*mod);
		SendClientMessage(playerid, COLOR_GRAD3, gunstring1);
		format(gunstring2, 256, "Weapons: purpledildo ($%d) whitedildo ($%d) longwhitedildo ($%d) whitedildo2 ($%d) flowers ($%d) cane",
		GunPrice[7][0]/100*mod,GunPrice[8][0]/100*mod,GunPrice[9][0]/100*mod,GunPrice[10][0]/100*mod,GunPrice[11][0]/100*mod,GunPrice[12][0]/100*mod);
		SendClientMessage(playerid, COLOR_GRAD3, gunstring2);
		format(gunstring3, 256, "Weapons: sdpistol ($%d) deagle ($%d) mp5 ($%d)",
		GunPrice[13][0]/100*mod,GunPrice[14][0]/100*mod,GunPrice[15][0]/100*mod,GunPrice[16][0]/100*mod,GunPrice[17][0]/100*mod,GunPrice[18][0]/100*mod);
		SendClientMessage(playerid, COLOR_GRAD3, gunstring3);
		format(gunstring4, 256, "Weapons: shotgun ($%d) ak47 ($%d) m4 ($%d) rifle ($%d)",
		GunPrice[19][0]/100*mod,GunPrice[20][0]/100*mod,GunPrice[21][0]/100*mod,GunPrice[22][0]/100*mod,GunPrice[23][0]/100*mod,GunPrice[24][0]/100*mod);
		SendClientMessage(playerid, COLOR_GRAD3, gunstring4);
		format(gunstring5, 256, "Weapons: pistolammo ($%d) shotgunammo ($%d) smgammo ($%d) assaultammo ($%d) rifleammo ($%d)",
		GunPrice[25][0],GunPrice[26][0],GunPrice[27][0],GunPrice[28][0],GunPrice[29][0]);
		SendClientMessage(playerid, COLOR_GRAD3, gunstring5);
		SendClientMessage(playerid, COLOR_GREEN,"_______________________________________");
		return 1;
	}

	if(ammo < 1 || ammo > 999) { SendClientMessage(playerid, COLOR_GREY, "   Ammo ammount not lower then 1 or higher then 999 !"); return 1; }

	if(!strcmp(gunid, "parachute", true, strlen(gunid))) {
		gun = 46;
		guncharge = GunPrice[0][0]/100*mod;
		ammocharge = 0;
	} else if (!strcmp(gunid, "golfclub", true, strlen(gunid))) {
		gun = 2; guncharge = GunPrice[1][0]/100*mod; ammocharge = 0;
		PlayerInfo[playerid][pGun1] = 2; PlayerInfo[playerid][pAmmo1] = 1;
	} else if (!strcmp(gunid, "nightstick", true, strlen(gunid))) {
		gun = 3; guncharge = GunPrice[2][0]/100*mod; ammocharge = 0;
		PlayerInfo[playerid][pGun1] = 3; PlayerInfo[playerid][pAmmo1] = 1;
	} else if (!strcmp(gunid, "baseballbat", true, strlen(gunid))) {
		gun = 5; guncharge = GunPrice[4][0]/100*mod; ammocharge = 0;
		PlayerInfo[playerid][pGun1] = 5; PlayerInfo[playerid][pAmmo1] = 1;
	} else if (!strcmp(gunid, "shovel", true, strlen(gunid))) {
		gun = 6; guncharge = GunPrice[5][0]/100*mod; ammocharge = 0;
		PlayerInfo[playerid][pGun1] = 6; PlayerInfo[playerid][pAmmo1] = 1;
	} else if (!strcmp(gunid, "poolcue", true, strlen(gunid))) {
		gun = 7; guncharge = GunPrice[6][0]/100*mod; ammocharge = 0;
		PlayerInfo[playerid][pGun1] = 7; PlayerInfo[playerid][pAmmo1] = 1;
	} else if (!strcmp(gunid, "purpledildo", true, strlen(gunid))) {
		gun = 10; guncharge = GunPrice[7][0]/100*mod; ammocharge = 0;
		PlayerInfo[playerid][pGun1] = 10; PlayerInfo[playerid][pAmmo1] = 1;
	} else if (!strcmp(gunid, "whitedildo", true, strlen(gunid))) {
		gun = 11; guncharge = GunPrice[8][0]/100*mod; ammocharge = 0;
		PlayerInfo[playerid][pGun1] = 11; PlayerInfo[playerid][pAmmo1] = 1;
	} else if (!strcmp(gunid, "longwhitedildo", true, strlen(gunid))) {
		gun = 12; guncharge = GunPrice[9][0]/100*mod; ammocharge = 0;
		PlayerInfo[playerid][pGun1] = 12; PlayerInfo[playerid][pAmmo1] = 1;
	} else if (!strcmp(gunid, "whitedildo2", true, strlen(gunid))) {
		gun = 13; guncharge = GunPrice[10][0]/100*mod; ammocharge = 0;
		PlayerInfo[playerid][pGun1] = 13; PlayerInfo[playerid][pAmmo1] = 1;
	} else if (!strcmp(gunid, "flowers", true, strlen(gunid))) {
		gun = 14; guncharge = GunPrice[11][0]/100*mod; ammocharge = 0;
		PlayerInfo[playerid][pGun1] = 14; PlayerInfo[playerid][pAmmo1] = 1;
	} else if (!strcmp(gunid, "cane", true, strlen(gunid))) {
		gun = 15; guncharge = GunPrice[12][0]/100*mod; ammocharge = 0;
		PlayerInfo[playerid][pGun1] = 15; PlayerInfo[playerid][pAmmo1] = 1;
	} else if (!strcmp(gunid, "sdpistol", true, strlen(gunid))) {
		gun = 23; guncharge = GunPrice[13][0]/100*mod; ammocharge = GunPrice[25][0]*ammo;
		PlayerInfo[playerid][pGun2] = 23; PlayerInfo[playerid][pAmmo2] = ammo;
	} else if (!strcmp(gunid, "deagle", true, strlen(gunid))) {
		gun = 24; guncharge = GunPrice[15][0]/100*mod; ammocharge = GunPrice[25][0]*ammo;
		PlayerInfo[playerid][pGun2] = 24; PlayerInfo[playerid][pAmmo2] = ammo;
	} else if (!strcmp(gunid, "mp5", true, strlen(gunid))) {
		gun = 29; guncharge = GunPrice[18][0]/100*mod; ammocharge = GunPrice[27][0]*ammo;
		PlayerInfo[playerid][pGun3] = 29; PlayerInfo[playerid][pAmmo3] = ammo;
	} else if (!strcmp(gunid, "shotgun", true, strlen(gunid))) {
		gun = 25; guncharge = GunPrice[19][0]/100*mod; ammocharge = GunPrice[26][0]*ammo;
		PlayerInfo[playerid][pGun3] = 25; PlayerInfo[playerid][pAmmo3] = ammo;
	} else if (!strcmp(gunid, "ak47", true, strlen(gunid))) {
		gun = 30; guncharge = GunPrice[22][0]/100*mod; ammocharge = GunPrice[28][0]*ammo;
		PlayerInfo[playerid][pGun4] = 30; PlayerInfo[playerid][pAmmo4] = ammo;
	} else if (!strcmp(gunid, "m4", true, strlen(gunid))) {
		gun = 31; guncharge = GunPrice[23][0]/100*mod; ammocharge = GunPrice[28][0]*ammo;
		PlayerInfo[playerid][pGun4] = 31; PlayerInfo[playerid][pAmmo4] = ammo;
	} else if (!strcmp(gunid, "rifle", true, strlen(gunid))) {
		gun = 33; guncharge = GunPrice[24][0]/100*mod; ammocharge = GunPrice[29][0]*ammo;
		PlayerInfo[playerid][pGun4] = 33; PlayerInfo[playerid][pAmmo4] = ammo;
	} else {
		return SendClientMessage(playerid, COLOR_GRAD6, "ShopKeeper says: I have never heard of that weapon.");
	}

	if((guncharge+ammocharge) > GetPlayerMoney(playerid)) {
		format(infostring, 256, "   You don't have $%d !",guncharge+ammocharge);
		return SendClientMessage(playerid, COLOR_GRAD3, infostring);
	}

	if(GetPlayerMoney(playerid) < (guncharge+ammocharge)) {
		return SendClientMessage(playerid, COLOR_GREY, "   Can't afford that !");
	}

	new payout = guncharge + ammocharge;
	format(infostring, 256, "You have purchased %s with %d ammo for $%d",gunid,ammo,payout);
	SendClientMessage(playerid, COLOR_GRAD3, infostring);

	if(location == 102 && IsACop(playerid)) { }
	else { GivePlayerMoney(playerid, - payout); }

	BizzInfo[location-99][bTill] += payout;
	ExtortionBiz(location-99, payout);
	BizzInfo[location-99][bProducts]--;
	PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
	GivePlayerWeapon(playerid, gun, ammo);
	format(gString, sizeof(gString), "%s bought weapons for $%d at biz %d", PlayerInfo[playerid][pName], payout, location-99);
	printf("%s", gString);
	PayLog(gString);
	return 1;
}

CMD:upgrade(playerid, params[]) {
	new gunid[16];
	new infostring[256];

	if(sscanf(params, "s[16]", gunid)) {
		format(gString, sizeof(gString), "Uzycie: /upgrade [upgradename] (You have %d Upgrade points)",PlayerInfo[playerid][gPupgrade]);
		SendClientMessage(playerid, COLOR_GREEN,"_______________________________________");
		SendClientMessage(playerid, COLOR_WHITE,"*** UPGRADES ***");
		SendClientMessage(playerid, COLOR_GRAD2,gString);

		if(PlayerInfo[playerid][pLevel] == 2) {
			SendClientMessage(playerid, COLOR_GRAD3, "Level 2 Perks: Alcoholic, DrugAddict");
		} else if(PlayerInfo[playerid][pLevel] == 3) {
			SendClientMessage(playerid, COLOR_GRAD3, "Level 3 Perks: Alcoholic, DrugAddict, Miser");
		} else if(PlayerInfo[playerid][pLevel] == 3) {
			SendClientMessage(playerid, COLOR_GRAD3, "Level 4 Perks: Alcoholic, DrugAddict, Miser, Trader");
		} else if(PlayerInfo[playerid][pLevel] >= 5) {
			SendClientMessage(playerid, COLOR_GRAD3, "Level 5 Perks: Alcoholic, DrugAddict, Miser, Trader, PainKillers");
		}

		SendClientMessage(playerid, COLOR_GRAD5, "Extra Health: health");
		SendClientMessage(playerid, COLOR_GREEN,"_______________________________________");
		return 1;
	}

	if(PlayerInfo[playerid][gPupgrade] < 1) {
		return SendClientMessage(playerid, COLOR_GRAD6, "   You Have 0 Upgrade Points");
	}

	if(PlayerInfo[playerid][pLevel] >= 1 && (strcmp(gunid, "health", true, strlen(gunid)) == 0)) {
		if(PlayerInfo[playerid][pSHealth] < 50)	{
			PlayerInfo[playerid][pSHealth] = PlayerInfo[playerid][pSHealth]+5.0;
			format(infostring, 256, "New Upgrade: You Will Now Spawn With %.2f Health (+5)",PlayerInfo[playerid][pSHealth]+50);
		} else {
			return SendClientMessage(playerid, COLOR_GRAD6, "   You Have Maximum Spawn Health");
		}
	} else if (PlayerInfo[playerid][pLevel] >= 2 && (strcmp(gunid, "alcoholic", true, strlen(gunid)) == 0)) {
		if(PlayerInfo[playerid][pAlcoholPerk] < 3) {
			PlayerInfo[playerid][pAlcoholPerk] += 1;
			format(infostring, 256, "New Perk Upgrade: Your Alcoholic Perk is now Level %d.",PlayerInfo[playerid][pAlcoholPerk]);
			PlayerInfo[playerid][gPupgrade]--;
		} else {
			return SendClientMessage(playerid, COLOR_GRAD6, "   Your Alcoholic Perk is maxed out !");
		}
	}
	else if (PlayerInfo[playerid][pLevel] >= 2 && (strcmp(gunid, "drugaddict", true, strlen(gunid)) == 0)) {
		if(PlayerInfo[playerid][pDrugPerk] < 3) {
			PlayerInfo[playerid][pDrugPerk] += 1;
			format(infostring, 256, "New Perk Upgrade: Your Drug Addict Perk is now Level %d.",PlayerInfo[playerid][pDrugPerk]);
			PlayerInfo[playerid][gPupgrade]--;
		} else {
			return SendClientMessage(playerid, COLOR_GRAD6, "   Your Drug Addict Perk is maxed out !");
		}
	} else if(PlayerInfo[playerid][pLevel] >= 3 && (strcmp(gunid, "miser", true, strlen(gunid)) == 0)) {
		if(PlayerInfo[playerid][pMiserPerk] < 3) {
			PlayerInfo[playerid][pMiserPerk] += 1;
			format(infostring, 256, "New Perk Upgrade: Your Miser Perk is now Level %d.",PlayerInfo[playerid][pMiserPerk]);
			PlayerInfo[playerid][gPupgrade]--;
		} else {
			return SendClientMessage(playerid, COLOR_GRAD6, "   Your Miser Perk is maxed out !");
		}
	} else if (PlayerInfo[playerid][pLevel] >= 4 && (strcmp(gunid, "trader", true, strlen(gunid)) == 0)) {
		if(PlayerInfo[playerid][pTraderPerk] < 3) {
			PlayerInfo[playerid][pTraderPerk] += 1;
			format(infostring, 256, "New Perk Upgrade: Your Trader Perk is now Level %d.",PlayerInfo[playerid][pTraderPerk]);
			PlayerInfo[playerid][gPupgrade]--;
		} else {
			return SendClientMessage(playerid, COLOR_GRAD6, "   Your Trader Perk is maxed out !");
		}
	} else if (PlayerInfo[playerid][pLevel] >= 5 && (strcmp(gunid, "painkillers", true, strlen(gunid)) == 0)) {
		if(PlayerInfo[playerid][pPainPerk] < 3) {
			PlayerInfo[playerid][pPainPerk] += 1;
			format(infostring, 256, "New Perk Upgrade: Your Pain Killers Perk is now Level %d.",PlayerInfo[playerid][pPainPerk]);
			PlayerInfo[playerid][gPupgrade]--;
		} else {
			return SendClientMessage(playerid, COLOR_GRAD6, "   Your Pain Killers Perk is maxed out !");
		}
	} else {
		return SendClientMessage(playerid, COLOR_GRAD6, "   Unrecognized Upgrade");
	}

	SendClientMessage(playerid, COLOR_GRAD6, infostring);
	PlayerInfo[playerid][gPupgrade]--;
	return 1;
}

CMD:login(playerid, params[]) {
	new tmppass[64];

	if(gPlayerLogged[playerid] == 1) {
		return SendClientMessage(playerid, COLOR_WHITE, "SERVER: Jestes zalogowany.");
	}

	if(sscanf(params, "s[64]", tmppass)) {
		return SendClientMessage(playerid, COLOR_GRAD1, "Uzycie: /login [password]");
	}

	Encrypt(tmppass);
	OnPlayerLogin(playerid,tmppass);
	return 1;
}

CMD:register(playerid, params[]) {
	if(gPlayerLogged[playerid] == 1) {
		return SendClientMessage(playerid, COLOR_WHITE, "SERVER: Jestes zalogowany.");
	}

	format(gString, sizeof(gString), "%s.ini", PlayerInfo[playerid][pName]);

	new File: hFile = fopen(gString, io_read);

	if(hFile) {
		SendClientMessage(playerid, COLOR_YELLOW, "That Username is already taken, please choose a different one.");
		return fclose(hFile);
	}

	new tmppass[64];

	if(sscanf(params, "s[64]", tmppass)) {
		return SendClientMessage(playerid, COLOR_GRAD1, "Uzycie: /register [password]");
	}

	Encrypt(tmppass);
	OnPlayerRegister(playerid,tmppass);
	return 1;
}

CMD:ooc(playerid, params[]) {
	if(!gPlayerLogged[playerid]) {
		return SendClientMessage(playerid, COLOR_GREY, "   You havent logged in yet !");
	}

	if((noooc) && PlayerInfo[playerid][pAdmin] < 1) {
		return SendClientMessage(playerid, COLOR_GRAD2, "   The OOC channel has been disabled by an Admin !");
	}

	if(PlayerInfo[playerid][pMuted]) {
		return SendClientMessage(playerid, TEAM_CYAN_COLOR, "   You can't speak, you have been silenced !");
	}

	new result[64];

	if(sscanf(params, "s[64]", result)) {
		return SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: (/o)oc [ooc chat]");
	}

	format(gString, sizeof(gString), "(( %s: %s ))", PlayerInfo[playerid][pName], result);
	OOCOff(COLOR_OOC,gString);
	printf("%s", gString);
	return 1;
}

alias:ooc("o")

CMD:noooc(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] >= 3 && (!noooc)) {
		noooc = 1;
		BroadCast(COLOR_GRAD2, "   Chat OOC zostal wylaczony przez administracje !");
	} else if (PlayerInfo[playerid][pAdmin] >= 3 && (noooc)) {
		noooc = 0;
		BroadCast(COLOR_GRAD2, "   Chat OOC zostal wlaczony przez administracje !");
	} else {
		SendClientMessage(playerid, COLOR_GRAD1, "   you are not authorized to use that command!");
	}
	return 1;
}

CMD:speedo(playerid, params[]) {
	if(gSpeedo[playerid] == 1) {
		gSpeedo[playerid] = 2;
		GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~g~on", 5000, 5);
		PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
	} else if(gSpeedo[playerid] == 2) {
		gSpeedo[playerid] = 1;
		GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~r~off", 5000, 5);
		PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
	} else {
		SendClientMessage(playerid, COLOR_GRAD1, "you dont have a speedometer");
	}
	return 1;
}

CMD:fuel(playerid, params[]) {
	if(!gGas[playerid]) {
		gGas[playerid] = 1;
		GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~g~Fuel Info on", 5000, 5);
		PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
	} else if(gGas[playerid]) {
		gGas[playerid] = 0;
		GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~r~Fuel Info off", 5000, 5);
		PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
	}
	return 1;
}

CMD:advertise(playerid, params[]) {
	if(!gPlayerLogged[playerid]) {
		return SendClientMessage(playerid, COLOR_GREY, "   You havent logged in yet !");
	}

	new result[64];

	if(sscanf(params, "s[64]", result)) {
		return SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: (/ad)vertise [advert text]");
	}

	if((!adds) && (PlayerInfo[playerid][pAdmin] < 1)) {
		format(gString, sizeof(gString), "   Please try again later %d seconds between Advertisements !",  (addtimer/1000));
		return SendClientMessage(playerid, COLOR_GRAD2, gString);
	}

	new idx = strlen(result);
	new payout = idx * 25;

	if(GetPlayerMoney(playerid) < payout) {
		format(gString, sizeof(gString), "* You used %d characters which cost $%d, you don't have enough.", idx, payout);
		return SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
	}

	GivePlayerMoney(playerid, - payout);
	SBizzInfo[7][sbTill] += payout;
	ExtortionSBiz(7, payout);
	format(gString, sizeof(gString), "Advertisement: %s, Contact: %s Ph: %d",  result, PlayerInfo[playerid][pName],PlayerInfo[playerid][pPnumber]);
	OOCNews(TEAM_GROVE_COLOR,gString);
	format(gString, sizeof(gString), "~r~Paid $%d~n~~w~Message contained: %d Characters", payout, idx);
	GameTextForPlayer(playerid, gString, 5000, 5);

	if(PlayerInfo[playerid][pAdmin] < 1){SetTimer("AddsOn", addtimer, 0);adds = 0;}
	return 1;
}

alias:advertise("ad")

CMD:government(playerid, params[]) {
	if(gTeam[playerid] != 2) {
		return SendClientMessage(playerid, COLOR_GREY, "   You are not a Cop !");
	}

	if(PlayerInfo[playerid][pRank] < 5) {
		return SendClientMessage(playerid, COLOR_GREY, "   You need to be Rank 5 to be able to use this !");
	}

	new result[64];

	if(sscanf(params, "s[64]", result)) {
		return SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: (/gov)ernment [text]");
	}

	SendClientMessageToAll(COLOR_WHITE, "|___________ Government News Announcement ___________|");
	format(gString, sizeof(gString), "Officer %s: %s", PlayerInfo[playerid][pName], result);
	SendClientMessageToAll(COLOR_DBLUE, gString);
	return 1;
}

alias:government("gov")

CMD:togooc(playerid, params[]) {
	if(!gOoc[playerid]) {
		gOoc[playerid] = 1;
		SendClientMessage(playerid, COLOR_GRAD2, "   OOC chat channel Disabled !");
	} else if(gOoc[playerid]) {
		gOoc[playerid] = 0;
		SendClientMessage(playerid, COLOR_GRAD2, "   OOC chat channel Enabled !");
	}
	return 1;
}

CMD:tognews(playerid, params[]) {
	if(!gNews[playerid]) {
		gNews[playerid] = 1;
		SendClientMessage(playerid, COLOR_GRAD2, "   News chat channel Disabled !");
	} else if(gNews[playerid]) {
		gNews[playerid] = 0;
		SendClientMessage(playerid, COLOR_GRAD2, "   News chat channel Enabled !");
	}
	return 1;
}

CMD:togfam(playerid, params[]) {
	if(!gFam[playerid]) {
		gFam[playerid] = 1;
		SendClientMessage(playerid, COLOR_GRAD2, "   Family chat channel Disabled !");
	} else if(gFam[playerid]) {
		gFam[playerid] = 0;
		SendClientMessage(playerid, COLOR_GRAD2, "   Family chat channel Enabled !");
	}
	return 1;
}

CMD:togwhisper(playerid, params[]) {
	if(PlayerInfo[playerid][pDonateRank] > 0 || PlayerInfo[playerid][pAdmin] > 1) {
		if(!HidePM[playerid]) {
			HidePM[playerid] = 1;
			SendClientMessage(playerid, COLOR_GRAD2, "   Whisper chat channel Disabled !");
		} else if(HidePM[playerid]) {
			HidePM[playerid] = 0;
			SendClientMessage(playerid, COLOR_GRAD2, "   Whisper chat channel Enabled !");
		}
	} else {
		SendClientMessage(playerid, COLOR_GREY, "   Not an Admin / Premium Account User !");
	}
	return 1;
}

CMD:togphone(playerid, params[]) {
	if(PlayerInfo[playerid][pDonateRank] > 0 || PlayerInfo[playerid][pAdmin] > 1) {
		if(!PhoneOnline[playerid]) {
			PhoneOnline[playerid] = 1;
			SendClientMessage(playerid, COLOR_GRAD2, "   Wyłaczono telefon !");
		} else if(PhoneOnline[playerid]) {
			PhoneOnline[playerid] = 0;
			SendClientMessage(playerid, COLOR_GRAD2, "   Włączono telefon !");
		}
	} else {
		SendClientMessage(playerid, COLOR_GREY, "   Not an Admin / Premium Account User !");
	}
	return 1;
}

CMD:me(playerid, params[]) {
	if(!gPlayerLogged[playerid]) {
		return SendClientMessage(playerid, COLOR_GREY, "   You havent logged in yet !");
	}

	new result[64];

	if(sscanf(params, "s[64]", result)) {
		return SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /me [action]");
	}

	format(gString, sizeof(gString), "* %s %s", PlayerInfo[playerid][pName], result);
	ProxDetector(30.0, playerid, gString, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
	printf("%s", gString);
	return 1;
}

CMD:local(playerid, params[]) {
	if(!gPlayerLogged[playerid]) {
		return SendClientMessage(playerid, COLOR_GREY, "   You havent logged in yet !");
	}

	new result[64];

	if(sscanf(params, "s[64]", result)) {
		return SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: (/l)ocal [local chat]");
	}

	format(gString, sizeof(gString), "%s Says: %s", PlayerInfo[playerid][pName], result);
	ProxDetector(20.0, playerid, gString,COLOR_FADE1,COLOR_FADE2,COLOR_FADE3,COLOR_FADE4,COLOR_FADE5);
	printf("%s", gString);
	return 1;
}

alias:local("l", "say")

CMD:b(playerid, params[]) {
	if(!gPlayerLogged[playerid]) {
		return SendClientMessage(playerid, COLOR_GREY, "   You havent logged in yet !");
	}

	new result[64];

	if(sscanf(params, "s[64]", result)) {
		return SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /b [local ooc chat]");
	}

	format(gString, sizeof(gString), "%s Says: (( %s ))", PlayerInfo[playerid][pName], result);
	ProxDetector(20.0, playerid, gString,COLOR_FADE1,COLOR_FADE2,COLOR_FADE3,COLOR_FADE4,COLOR_FADE5);
	printf("%s", gString);
	return 1;
}

CMD:close(playerid, params[]) {
	if(!gPlayerLogged[playerid]) {
		return SendClientMessage(playerid, COLOR_GREY, "   You havent logged in yet !");
	}

	new result[64];

	if(sscanf(params, "s[64]", result)) {
		return SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /(c)lose [close chat text]");
	}

	format(gString, sizeof(gString), "%s Says: %s", PlayerInfo[playerid][pName], result);
	ProxDetector(3.0, playerid, gString,COLOR_FADE1,COLOR_FADE2,COLOR_FADE3,COLOR_FADE4,COLOR_FADE5);
	printf("%s", gString);
	return 1;
}

CMD:shout(playerid, params[]) {
	if(!gPlayerLogged[playerid]) {
		return SendClientMessage(playerid, COLOR_GREY, "   You havent logged in yet !");
	}

	new result[64];

	if(sscanf(params, "s[64]", result)) {
		return SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: (/s)hout [local chat]");
	}

	format(gString, sizeof(gString), "%s Shouts: %s!!", PlayerInfo[playerid][pName], result);
	ProxDetector(30.0, playerid, gString,COLOR_WHITE,COLOR_WHITE,COLOR_WHITE,COLOR_FADE1,COLOR_FADE2);
	printf("%s", gString);
	return 1;
}

alias:shout("s")

CMD:megaphone(playerid, params[]) {
	new tmpcar = GetPlayerVehicleID(playerid);
	new result[64];

	if(sscanf(params, "s[64]", result)) {
		return SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: (/m)egaphone [megaphone chat]");
	}

	if(gTeam[playerid] == 2 || IsACop(playerid)) {
		if(!IsACopCar(tmpcar)) {
			return SendClientMessage(playerid, COLOR_GRAD2, "   You are not in a Police Vehicle !");
		}

		if(PlayerInfo[playerid][pMember] == 1||PlayerInfo[playerid][pLeader] == 1) {
			format(gString, sizeof(gString), "[Officer %s:o< %s]", PlayerInfo[playerid][pName], result);
			ProxDetector(60.0, playerid, gString,COLOR_YELLOW,COLOR_YELLOW,COLOR_YELLOW,COLOR_YELLOW,COLOR_YELLOW);
		} else if(PlayerInfo[playerid][pMember] == 2||PlayerInfo[playerid][pLeader] == 2) {
			format(gString, sizeof(gString), "[Agent %s:o< %s]", PlayerInfo[playerid][pName], result);
			ProxDetector(60.0, playerid, gString,COLOR_YELLOW,COLOR_YELLOW,COLOR_YELLOW,COLOR_YELLOW,COLOR_YELLOW);
		} else if(PlayerInfo[playerid][pMember] == 3||PlayerInfo[playerid][pLeader] == 3) {
			format(gString, sizeof(gString), "[Soldier %s:o< %s]", PlayerInfo[playerid][pName], result);
			ProxDetector(60.0, playerid, gString,COLOR_YELLOW,COLOR_YELLOW,COLOR_YELLOW,COLOR_YELLOW,COLOR_YELLOW);
		}
		printf("%s", gString);
	} else {
		SendClientMessage(playerid, COLOR_GRAD2, "   You are not part of a Team !");
	}
	return 1;
}

alias:megaphone("m")

CMD:radio(playerid, params[]) {
	new result[64];

	if(sscanf(params, "s[64]", result)) {
		return SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: (/r)adio [radio chat]");
	}

	if(PlayerInfo[playerid][pMember] == 1 || PlayerInfo[playerid][pLeader] == 1) {
		if(PlayerInfo[playerid][pRank] == 6) { format(gString, sizeof(gString), "** Chief %s: %s, over. **", PlayerInfo[playerid][pName], result); }
		else if(PlayerInfo[playerid][pRank] == 5) { format(gString, sizeof(gString), "** Captain %s: %s, over. **", PlayerInfo[playerid][pName], result); }
		else if(PlayerInfo[playerid][pRank] == 4) { format(gString, sizeof(gString), "** Lieutenant %s: %s, over. **", PlayerInfo[playerid][pName], result); }
		else if(PlayerInfo[playerid][pRank] == 3) { format(gString, sizeof(gString), "** Sergeant %s: %s, over. **", PlayerInfo[playerid][pName], result); }
		else if(PlayerInfo[playerid][pRank] == 2) { format(gString, sizeof(gString), "** Officer %s: %s, over. **", PlayerInfo[playerid][pName], result); }
		else if(PlayerInfo[playerid][pRank] == 1) { format(gString, sizeof(gString), "** Cadet %s: %s, over. **", PlayerInfo[playerid][pName], result); }
		else { format(gString, sizeof(gString), "** Cadet %s: %s, over. **", PlayerInfo[playerid][pName], result); }
		SendRadioMessage(1, TEAM_BLUE_COLOR, gString);
		printf("%s", gString);
	} else if(PlayerInfo[playerid][pMember] == 2 || PlayerInfo[playerid][pLeader] == 2) {
		if(PlayerInfo[playerid][pRank] == 6) { format(gString, sizeof(gString), "** Director %s: %s, over. **", PlayerInfo[playerid][pName], result); }
		else if(PlayerInfo[playerid][pRank] == 5) { format(gString, sizeof(gString), "** Assistant Director in Charge %s: %s, over. **", PlayerInfo[playerid][pName], result); }
		else if(PlayerInfo[playerid][pRank] == 4) { format(gString, sizeof(gString), "** Special Agent in Charge %s: %s, over. **", PlayerInfo[playerid][pName], result); }
		else if(PlayerInfo[playerid][pRank] == 3) { format(gString, sizeof(gString), "** Special Agent %s: %s, over. **", PlayerInfo[playerid][pName], result); }
		else if(PlayerInfo[playerid][pRank] == 2) { format(gString, sizeof(gString), "** Special Agent Trainee %s: %s, over. **", PlayerInfo[playerid][pName], result); }
		else if(PlayerInfo[playerid][pRank] == 1) { format(gString, sizeof(gString), "** Professional Staff %s: %s, over. **", PlayerInfo[playerid][pName], result); }
		else { format(gString, sizeof(gString), "** Intern %s: %s, over. **", PlayerInfo[playerid][pName], result); }
		SendRadioMessage(2, TEAM_BLUE_COLOR, gString);
		printf("%s", gString);
	} else if(PlayerInfo[playerid][pMember] == 3 || PlayerInfo[playerid][pLeader] == 3) {
		if(PlayerInfo[playerid][pRank] == 6) { format(gString, sizeof(gString), "** General %s: %s, over. **", PlayerInfo[playerid][pName], result); }
		else if(PlayerInfo[playerid][pRank] == 5) { format(gString, sizeof(gString), "** Lieutenant %s: %s, over. **", PlayerInfo[playerid][pName], result); }
		else if(PlayerInfo[playerid][pRank] == 4) { format(gString, sizeof(gString), "** Captain %s: %s, over. **", PlayerInfo[playerid][pName], result); }
		else if(PlayerInfo[playerid][pRank] == 3) { format(gString, sizeof(gString), "** Major %s: %s, over. **", PlayerInfo[playerid][pName], result); }
		else if(PlayerInfo[playerid][pRank] == 2) { format(gString, sizeof(gString), "** Sergeant %s: %s, over. **", PlayerInfo[playerid][pName], result); }
		else if(PlayerInfo[playerid][pRank] == 1) { format(gString, sizeof(gString), "** Private %s: %s, over. **", PlayerInfo[playerid][pName], result); }
		else { format(gString, sizeof(gString), "** Private %s: %s, over. **", PlayerInfo[playerid][pName], result); }
		SendRadioMessage(3, TEAM_BLUE_COLOR, gString);
		printf("%s", gString);
	} else if(gTeam[playerid] == 1||PlayerInfo[playerid][pMember]==4||PlayerInfo[playerid][pLeader]==4) {
		format(gString, sizeof(gString), "** Paramedic %s: %s, over. **", PlayerInfo[playerid][pName], result);
		SendRadioMessage(4, TEAM_CYAN_COLOR, gString);
		printf("%s", gString);
	} else {
		SendClientMessage(playerid, COLOR_GRAD2, "   You are not part of a Team !");
	}
	return 1;
}

CMD:duty(playerid, params[]) {
	if(PlayerInfo[playerid][pMember] == 1) {
		if(PlayerToPoint(3, playerid,255.3,77.4,1003.6) || PlayerToPoint(3,playerid,-1616.1294,681.1594,7.1875) || PlayerInfo[playerid][pLocal] != 255) {
			if(OnDuty[playerid]==0) {
				format(gString, sizeof(gString), "* Officer %s took a Badge and a Gun from his locker.", PlayerInfo[playerid][pName]);
				ProxDetector(30.0, playerid, gString, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
				GivePlayerWeapon(playerid, 24, 70);
				GivePlayerWeapon(playerid, 3, 0);
				OnDuty[playerid] = 1;
			} else if(OnDuty[playerid]==1) {
				format(gString, sizeof(gString), "* Officer %s places his Badge and Gun in his locker.", PlayerInfo[playerid][pName]);
				ProxDetector(30.0, playerid, gString, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
				GivePlayerWeapon(playerid, 23, 150);
				GivePlayerWeapon(playerid, 5, 0);
				OnDuty[playerid] = 0;
			}
		} else {
			return SendClientMessage(playerid, COLOR_GRAD2, "   You are not in a locker room !");
		}
	} else if(PlayerInfo[playerid][pMember] == 4||PlayerInfo[playerid][pLeader] == 4) {
		if(JobDuty[playerid] == 1) {
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You are now Off Duty from your Medic Job and will not receive calls anymore.");
			JobDuty[playerid] = 0;
			Medics -= 1;
		} else {
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You are now On Duty with your Medic Job and will receive calls from people in need.");
			JobDuty[playerid] = 1;
			Medics += 1;
		}
	} else if(PlayerInfo[playerid][pJob] == 7) {
		if(JobDuty[playerid] == 1) {
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You are now Off Duty from your Car Mechanic Job and will not receive calls anymore.");
			JobDuty[playerid] = 0;
			Mechanics -= 1;
		} else {
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You are now On Duty with your Car Mechanic Job and will receive calls from people in need.");
			JobDuty[playerid] = 1;
			Mechanics += 1;
		}
	} else {
		SendClientMessage(playerid, COLOR_GRAD1, "   You are not a Cop !");
	}
	return 1;
}

CMD:departments(playerid, params[]) {
	new result[64];

	if(sscanf(params, "s[64]", result)) {
		return SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: (/d)epartments [department chat]");
	}

	if(PlayerInfo[playerid][pMember] == 1 || PlayerInfo[playerid][pLeader] == 1) {
		if(PlayerInfo[playerid][pRank] == 6) { format(gString, sizeof(gString), "** Chief %s: %s, over. **", PlayerInfo[playerid][pName], result); }
		else if(PlayerInfo[playerid][pRank] == 5) { format(gString, sizeof(gString), "** Captain %s: %s, over. **", PlayerInfo[playerid][pName], result); }
		else if(PlayerInfo[playerid][pRank] == 4) { format(gString, sizeof(gString), "** Lieutenant %s: %s, over. **", PlayerInfo[playerid][pName], result); }
		else if(PlayerInfo[playerid][pRank] == 3) { format(gString, sizeof(gString), "** Sergeant %s: %s, over. **", PlayerInfo[playerid][pName], result); }
		else if(PlayerInfo[playerid][pRank] == 2) { format(gString, sizeof(gString), "** Officer %s: %s, over. **", PlayerInfo[playerid][pName], result); }
		else if(PlayerInfo[playerid][pRank] == 1) { format(gString, sizeof(gString), "** Cadet %s: %s, over. **", PlayerInfo[playerid][pName], result); }
		else { format(gString, sizeof(gString), "** Officer %s: %s, over. **", PlayerInfo[playerid][pName], result); }
		SendTeamMessage(2, COLOR_ALLDEPT, gString);
		SendTeamMessage(1, COLOR_ALLDEPT, gString);
		printf("%s", gString);
	} else if(PlayerInfo[playerid][pMember] == 2 || PlayerInfo[playerid][pLeader] == 2) {
		if(PlayerInfo[playerid][pRank] == 6) { format(gString, sizeof(gString), "** Director %s: %s, over. **", PlayerInfo[playerid][pName], result); }
		else if(PlayerInfo[playerid][pRank] == 5) { format(gString, sizeof(gString), "** Assistant Director in Charge %s: %s, over. **", PlayerInfo[playerid][pName], result); }
		else if(PlayerInfo[playerid][pRank] == 4) { format(gString, sizeof(gString), "** Special Agent in Charge %s: %s, over. **", PlayerInfo[playerid][pName], result); }
		else if(PlayerInfo[playerid][pRank] == 3) { format(gString, sizeof(gString), "** Special Agent %s: %s, over. **", PlayerInfo[playerid][pName], result); }
		else if(PlayerInfo[playerid][pRank] == 2) { format(gString, sizeof(gString), "** Special Agent Trainee %s: %s, over. **", PlayerInfo[playerid][pName], result); }
		else if(PlayerInfo[playerid][pRank] == 1) { format(gString, sizeof(gString), "** Professional Staff %s: %s, over. **", PlayerInfo[playerid][pName], result); }
		else { format(gString, sizeof(gString), "** Intern %s: %s, over. **", PlayerInfo[playerid][pName], result); }
		SendTeamMessage(2, COLOR_ALLDEPT, gString);
		SendTeamMessage(1, COLOR_ALLDEPT, gString);
		printf("%s", gString);
	} else if(PlayerInfo[playerid][pMember] == 3 || PlayerInfo[playerid][pLeader] == 3) {
		if(PlayerInfo[playerid][pRank] == 6) { format(gString, sizeof(gString), "** General %s: %s, over. **", PlayerInfo[playerid][pName], result); }
		else if(PlayerInfo[playerid][pRank] == 5) { format(gString, sizeof(gString), "** Lieutenant %s: %s, over. **", PlayerInfo[playerid][pName], result); }
		else if(PlayerInfo[playerid][pRank] == 4) { format(gString, sizeof(gString), "** Captain %s: %s, over. **", PlayerInfo[playerid][pName], result); }
		else if(PlayerInfo[playerid][pRank] == 3) { format(gString, sizeof(gString), "** Major %s: %s, over. **", PlayerInfo[playerid][pName], result); }
		else if(PlayerInfo[playerid][pRank] == 2) { format(gString, sizeof(gString), "** Sergeant %s: %s, over. **", PlayerInfo[playerid][pName], result); }
		else if(PlayerInfo[playerid][pRank] == 1) { format(gString, sizeof(gString), "** Private %s: %s, over. **", PlayerInfo[playerid][pName], result); }
		else { format(gString, sizeof(gString), "** Private %s: %s, over. **", PlayerInfo[playerid][pName], result); }
		SendTeamMessage(2, COLOR_ALLDEPT, gString);
		SendTeamMessage(1, COLOR_ALLDEPT, gString);
		printf("%s", gString);
	} else if(gTeam[playerid] == 1||PlayerInfo[playerid][pMember]==4||PlayerInfo[playerid][pLeader]==4) {
		format(gString, sizeof(gString), "** Paramedic %s: %s, over. **", PlayerInfo[playerid][pName], result);
		SendTeamMessage(2, COLOR_ALLDEPT, gString);
		SendTeamMessage(1, COLOR_ALLDEPT, gString);
		printf("%s", gString);
	} else {
		SendClientMessage(playerid, COLOR_GRAD2, "   You are not part of a Team !");
	}
	return 1;
}

alias:departments("d")

CMD:mdc(playerid, params[]) {
	if(!IsACop(playerid)) {
		return SendClientMessage(playerid, COLOR_GREY, "   You are not a Cop !");
	}

	new tmpcar = GetPlayerVehicleID(playerid);
	new giveplayerid;

	if(sscanf(params, "i", giveplayerid)) {
		return SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /mdc [playerid/PartOfName]");
	}

	if(IsACopCar(tmpcar)||PlayerToPoint(5.0, playerid, 253.9280,69.6094,1003.6406)) {
		if(IsPlayerConnected(giveplayerid)) {
			SendClientMessage(playerid, TEAM_BLUE_COLOR,"______-=MOBILE DATA COMPUTER=-_______");
			format(gString, sizeof(gString), "Name : %s", PlayerInfo[playerid][pName]);
			SendClientMessage(playerid, COLOR_WHITE,gString);
			format(gString, sizeof(gString), "Crime : %s", PlayerCrime[giveplayerid][pAccusedof]);
			SendClientMessage(playerid, COLOR_GRAD2,gString);
			format(gString, sizeof(gString), "Claimant : %s", PlayerCrime[giveplayerid][pVictim]);
			SendClientMessage(playerid, COLOR_GRAD3,gString);
			format(gString, sizeof(gString), "Reported : %s", PlayerCrime[giveplayerid][pAccusing]);
			SendClientMessage(playerid, COLOR_GRAD4,gString);
			format(gString, sizeof(gString), "Accused : %s", PlayerCrime[giveplayerid][pBplayer]);
			SendClientMessage(playerid, COLOR_GRAD5,gString);
			SendClientMessage(playerid, TEAM_BLUE_COLOR,"_______________________________________");
		} else {
			SendClientMessage(playerid, COLOR_GREY, "   That player is Offline !");
		}
	} else {
		SendClientMessage(playerid, COLOR_GRAD2, "   You are not in a Police Vehicle or in the Police Department.");
	}
	return 1;
}

CMD:suspect(playerid, params[]) {
	if(OnDuty[playerid] != 1  && PlayerInfo[playerid][pMember] == 1) {
		return SendClientMessage(playerid, COLOR_GREY, "   You are not on Duty!");
	}

	new giveplayerid, result[64];

	if(sscanf(params, "is[64]", giveplayerid, result)) {
		return SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: (/su)spect [playerid/PartOfName] [crime discription]");
	}

	if(gTeam[playerid] == 2 || IsACop(playerid)) {
		if(IsPlayerConnected(giveplayerid)) {
			if(gTeam[giveplayerid] != 2) {
				if(WantedPoints[giveplayerid] == 0) { WantedPoints[giveplayerid] = 3; }
				else { WantedPoints[giveplayerid]+= 2; }

				SetPlayerCriminal(giveplayerid,playerid, result);
			} else {
				SendClientMessage(playerid, COLOR_GRAD2, "   You can't suspect a Cop !");
			}
		} else {
			format(gString, sizeof(gString), "   %d is not an active player.", giveplayerid);
			SendClientMessage(playerid, COLOR_GRAD1, gString);
		}
	} else {
		SendClientMessage(playerid, COLOR_GRAD2, "   You are not a Cop / FBI / National Guard !");
	}
	return 1;
}

alias:suspect("su")

CMD:lock(playerid, params[]) {
	new carid;

	if(gTeam[playerid] == 2 || gTeam[playerid] == 1) {
		if(gLastCar[playerid] == 0 && PlayerInfo[playerid][pPhousekey] == 255) {
			return SendClientMessage(playerid, COLOR_GRAD2, "   You dont have a Vehicle.");
		} else if(gLastCar[playerid] != 0 && gLastCar[playerid] != PlayerInfo[playerid][pPhousekey]+1) {
			if(HireCar[playerid] != gLastCar[playerid] && HireCar[playerid] != 299) {
				gLastDriver[HireCar[playerid]] = 300;
				gCarLock[HireCar[playerid]] = 0;
				UnLockCar(HireCar[playerid]);
			}

			HireCar[playerid] = gLastCar[playerid];
		}
	}

	if(PlayerInfo[playerid][pPhousekey] == 255) {
		if(HireCar[playerid] == 299) {
			return SendClientMessage(playerid, COLOR_GRAD2, "   You dont have a Vehicle.");
		}
	}

	carid = PlayerInfo[playerid][pPhousekey]+1;

	if(HireCar[playerid] != 299 && !SwitchKey[playerid]) {
		carid = HireCar[playerid];
	}

	new lockstatus = gCarLock[carid];
	new Float:cx,Float:cy,Float:cz;
	GetVehiclePos(carid, cx, cy, cz);

	switch(lockstatus) {
		case 0: {
			if(HireCar[playerid] == 299 && PlayerInfo[playerid][pPhousekey] == 255) {
				return SendClientMessage(playerid, COLOR_GRAD2, "   You dont have a Vehicle");
			}

			if(HireCar[playerid] == carid && !SwitchKey[playerid]) {
				GameTextForPlayer(playerid, "~w~Hire Vehicle ~r~Locked", 5000, 6);
				PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
				gCarLock[carid] = 1;
				LockCar(carid);
			} else if (PlayerInfo[playerid][pPhousekey] == carid-1) {
				GameTextForPlayer(playerid, "~w~House Vehicle ~r~Locked", 5000, 6);
				PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
				gCarLock[carid] = 1;
				LockCar(carid);
			}
		}
		case 1: {
			if(HireCar[playerid] == 299 && PlayerInfo[playerid][pPhousekey] == 255) {
				return SendClientMessage(playerid, COLOR_GRAD2, "   You dont have a Vehicle");
			}

			if(HireCar[playerid] == carid && !SwitchKey[playerid]) {
				GameTextForPlayer(playerid, "~w~Hire Vehicle ~g~Unlocked", 5000, 6);
				PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
				gCarLock[carid] = 0;
				UnLockCar(carid);
			}

			if(PlayerInfo[playerid][pPhousekey] == carid-1) {
				GameTextForPlayer(playerid, "~w~House Vehicle ~g~Unlocked", 5000, 6);
				PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
				gCarLock[carid] = 0;
				UnLockCar(carid);
			}
		}
		default: {
			SendClientMessage(playerid, COLOR_GRAD2, "   Error");
		}
	}

	if(carid == 256) {
		SendClientMessage(playerid, COLOR_GRAD2, "   You dont have a Vehicle !");
	}
	return 1;
}

CMD:open(playerid, params[]) {
	for(new i = 0; i < sizeof(HouseInfo); i++) {
		if(PlayerToPoint(3, playerid,HouseInfo[i][hEntrancex], HouseInfo[i][hEntrancey], HouseInfo[i][hEntrancez]) || PlayerToPoint(3, playerid,HouseInfo[i][hExitx], HouseInfo[i][hExity], HouseInfo[i][hExitz])) {
			if(PlayerInfo[playerid][pPhousekey] == i) {
				if(HouseInfo[i][hLock] == 1) {
					HouseInfo[i][hLock] = 0;
					GameTextForPlayer(playerid, "~w~Door ~g~Unlocked", 5000, 6);
					PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
					return 1;
				}

				if(HouseInfo[i][hLock] == 0) {
					HouseInfo[i][hLock] = 1;
					GameTextForPlayer(playerid, "~w~Door ~r~Locked", 5000, 6);
					PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
					return 1;
				}
			} else {
				return GameTextForPlayer(playerid, "~r~You Dont Have A Key", 5000, 6);
			}
		}
	}

	for(new i = 0; i < sizeof(BizzInfo); i++) {
		if(PlayerToPoint(3, playerid,BizzInfo[i][bEntranceX], BizzInfo[i][bEntranceY], BizzInfo[i][bEntranceZ]) || PlayerToPoint(3, playerid,BizzInfo[i][bExitX], BizzInfo[i][bExitY], BizzInfo[i][bExitZ])) {
			if(PlayerInfo[playerid][pPbiskey] == i) {
				if(BizzInfo[i][bLocked] == 1) {
					BizzInfo[i][bLocked] = 0;
					GameTextForPlayer(playerid, "~w~Bussiness ~g~Open", 5000, 6);
					PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
					return 1;
				}

				if(BizzInfo[i][bLocked] == 0) {
					BizzInfo[i][bLocked] = 1;
					GameTextForPlayer(playerid, "~w~Bussiness ~r~Closed", 5000, 6);
					PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
					return 1;
				}
			} else {
				return GameTextForPlayer(playerid, "~r~You Dont Have A Key", 5000, 6);
			}
		}
	}

	for(new i = 0; i < sizeof(SBizzInfo); i++) {
		if(PlayerToPoint(3, playerid,SBizzInfo[i][sbEntranceX], SBizzInfo[i][sbEntranceY], SBizzInfo[i][sbEntranceZ])) {
			if(PlayerInfo[playerid][pPbiskey] == i+100) {
				if(SBizzInfo[i][sbLocked] == 1) {
					SBizzInfo[i][sbLocked] = 0;
					GameTextForPlayer(playerid, "~w~Bussiness ~g~Open", 5000, 6);
					PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
					return 1;
				}

				if(SBizzInfo[i][sbLocked] == 0) {
					SBizzInfo[i][sbLocked] = 1;
					GameTextForPlayer(playerid, "~w~Bussiness ~r~Closed", 5000, 6);
					PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
					return 1;
				}
			} else {
				return GameTextForPlayer(playerid, "~r~You Dont Have A Key", 5000, 6);
			}
		}
	}
	return 1;
}

CMD:wisper(playerid, params[]) {
	if(gPlayerLogged[playerid] == 0) {
		return SendClientMessage(playerid, COLOR_GREY, "   You havent logged in yet !");
	}

	new giveplayerid, result[64];

	if(sscanf(params, "is[64]", giveplayerid, result)) {
		return SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: (/w)isper [playerid/PartOfName] [whisper text]");
	}

	if(IsPlayerConnected(giveplayerid)) {
		if(HidePM[giveplayerid] > 0) {
			return SendClientMessage(playerid, COLOR_GREY, "   That player is blocking Whispers !");
		}

		if(giveplayerid == playerid) {
			format(gString, sizeof(gString), "* %s mutters somthing.", PlayerInfo[playerid][pName]);
			ProxDetector(5.0, playerid, gString, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
		}

		format(gString, sizeof(gString), "%s(ID: %d) whispers: %s", PlayerInfo[playerid][pName], playerid, (result));
		SendClientMessage(giveplayerid, COLOR_YELLOW, gString);
		format(gString, sizeof(gString), "Wisper sent to %s(ID: %d).", PlayerInfo[giveplayerid][pName], giveplayerid);
		SendClientMessage(playerid,  COLOR_YELLOW, gString);
		SBizzInfo[2][sbTill] += txtcost / 2;
		ExtortionSBiz(2, txtcost / 2);
	} else {
		format(gString, sizeof(gString), "   %d is not an active player.", giveplayerid);
		SendClientMessage(playerid, COLOR_GRAD1, gString);
	}
	return 1;
}

alias:wisper("w")

CMD:withdraw(playerid, params[]) {
	if(PlayerInfo[playerid][pLocal] != 103) {
		return SendClientMessage(playerid, COLOR_GREY, "   You are not at the Bank !");
	}

	new cashdeposit;

	if(sscanf(params, "i", cashdeposit)) {
		SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /withdraw [amount]");
		format(gString, sizeof(gString), "  You Have $%d in your account.", PlayerInfo[playerid][pAccount]);
		return SendClientMessage(playerid, COLOR_GRAD3, gString);
	}

	if(cashdeposit > PlayerInfo[playerid][pAccount] || cashdeposit < 1) {
		return SendClientMessage(playerid, COLOR_GRAD2, "   You dont have that much !");
	}

	ConsumingMoney[playerid] = 1;
	GivePlayerMoney(playerid,cashdeposit);
	PlayerInfo[playerid][pAccount]=PlayerInfo[playerid][pAccount]-cashdeposit;
	format(gString, sizeof(gString), "  You Have Withdrawn $%d from your account Total: $%d ", cashdeposit,PlayerInfo[playerid][pAccount]);
	SendClientMessage(playerid, COLOR_YELLOW, gString);
	return 1;
}

CMD:bank(playerid, params[]) {
	if(PlayerInfo[playerid][pLocal] != 103) {
		return SendClientMessage(playerid, COLOR_GREY, "   You are not at the Bank !");
	}

	new cashdeposit;

	if(sscanf(params, "i", cashdeposit)) {
		SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /bank [amount]");
		format(gString, sizeof(gString), "  You Have $%d in your account.", PlayerInfo[playerid][pAccount]);
		return SendClientMessage(playerid, COLOR_GRAD3, gString);
	}

	if(cashdeposit > GetPlayerMoney(playerid) || cashdeposit < 1) {
		return SendClientMessage(playerid, COLOR_GRAD2, "   You dont have that much");
	}

	GivePlayerMoney(playerid,-cashdeposit);
	new curfunds = PlayerInfo[playerid][pAccount];
	PlayerInfo[playerid][pAccount]=cashdeposit+PlayerInfo[playerid][pAccount];
	SendClientMessage(playerid, COLOR_WHITE, "|___ BANK STATMENT ___|");
	format(gString, sizeof(gString), "  Old Balance: $%d", curfunds);
	SendClientMessage(playerid, COLOR_GRAD2, gString);
	format(gString, sizeof(gString), "  Deposit: $%d",cashdeposit);
	SendClientMessage(playerid, COLOR_GRAD4, gString);
	SendClientMessage(playerid, COLOR_GRAD6, "|-----------------------------------------|");
	format(gString, sizeof(gString), "  New Balance: $%d", PlayerInfo[playerid][pAccount]);
	SendClientMessage(playerid, COLOR_WHITE, gString);
	return 1;
}

alias:bank("deposit")

CMD:balance(playerid, params[]) {
	if(PlayerInfo[playerid][pLocal] != 103) {
		return SendClientMessage(playerid, COLOR_GREY, "   You are not at the Bank !");
	}

	format(gString, sizeof(gString), "  You Have $%d in your account.",PlayerInfo[playerid][pAccount]);
	SendClientMessage(playerid, COLOR_YELLOW, gString);
	return 1;
}

CMD:dice(playerid, params[]) {
	new dice = random(6)+1;

	if(gDice[playerid] == 1) {
		format(gString, sizeof(gString), "* %s Throws a Dice that lands on %d", PlayerInfo[playerid][pName],dice);
		ProxDetector(5.0, playerid, gString, TEAM_GREEN_COLOR,TEAM_GREEN_COLOR,TEAM_GREEN_COLOR,TEAM_GREEN_COLOR,TEAM_GREEN_COLOR);
	} else {
		SendClientMessage(playerid, COLOR_GRAD2, "   You Don't Have A Dice");
	}
	return 1;
}

CMD:transfer(playerid, params[]) {
	if(PlayerInfo[playerid][pLevel] < 3) {
		return SendClientMessage(playerid, COLOR_GRAD1, "   You must be level 3 !");
	}

	if(PlayerInfo[playerid][pLocal] != 103) {
		return SendClientMessage(playerid, COLOR_GREY, "   You are not at the Bank !");
	}

	new giveplayerid, moneys;

	if(sscanf(params, "ii", giveplayerid, moneys)) {
		return SendClientMessage(playerid, COLOR_GRAD1, "Uzycie: /transfer [playerid/PartOfName] [amount]");
	}

	if(IsPlayerConnected(giveplayerid)) {
		new playermoney = PlayerInfo[playerid][pAccount] ;

		if(moneys > 0 && playermoney >= moneys) {
			PlayerInfo[playerid][pAccount] -= moneys;
			PlayerInfo[giveplayerid][pAccount] += moneys;
			format(gString, sizeof(gString), "   You have transferd $%d to %s's account", moneys, PlayerInfo[giveplayerid][pName],giveplayerid);
			PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
			SendClientMessage(playerid, COLOR_GRAD1, gString);
			format(gString, sizeof(gString), "   You have recieved $%d to into your account from %s", moneys, PlayerInfo[playerid][pName], playerid);
			SendClientMessage(giveplayerid, COLOR_GRAD1, gString);
			format(gString, sizeof(gString), "%s transferd $%d to %s", PlayerInfo[playerid][pName], moneys, PlayerInfo[giveplayerid][pName]);

			if(moneys >= 500000) {
				ABroadCast(COLOR_YELLOW,gString,1);
			}

			printf("%s", gString);
			PayLog(gString);
			PlayerPlaySound(giveplayerid, 1052, 0.0, 0.0, 0.0);
		} else {
			SendClientMessage(playerid, COLOR_GRAD1, "   Invalid transaction amount.");
		}
	} else {
		format(gString, sizeof(gString), "   %d is not an active player.", giveplayerid);
		SendClientMessage(playerid, COLOR_GRAD1, gString);
	}
	return 1;
}

alias:transfer("wiretransfer")

CMD:buy(playerid, params[]) {
	if(!PlayerToPoint(100, playerid,-30.875, -88.9609, 1004.53)) {//centerpoint 24-7
		return SendClientMessage(playerid, COLOR_GRAD2, "   You are not in a 24-7 !");
	}

	new item;

	if(sscanf(params, "i", item)) {
		SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /buy [item number]");
		SendClientMessage(playerid, COLOR_GREEN, "|_______ 24-7 _______|");
		SendClientMessage(playerid, COLOR_GRAD1, "| 1: Cell Phone $500			2: Scratch Card $7500");
		SendClientMessage(playerid, COLOR_GRAD2, "| 3: Phone Book $5000			4: Dice $500");
		SendClientMessage(playerid, COLOR_GRAD3, "| 5: Vehicle Key $5000		6: Vehicle Lock $10000");
		SendClientMessage(playerid, COLOR_GRAD4, "| 7: Speedometer $5000		8: Condom $50");
		SendClientMessage(playerid, COLOR_GRAD5, "| 9: CD-Player $2500			10: Chicken $10	");
		return SendClientMessage(playerid, COLOR_GRAD5, "| 11: Hamburger $10			12: Frozen Pizza $10");
	}

	if(SBizzInfo[9][sbProducts] == 0) {
		return GameTextForPlayer(playerid, "~r~Out Of Stock", 5000, 1);
	}

	if(item == 1 && GetPlayerMoney(playerid) > 500) {
		if(PlayerInfo[playerid][pTraderPerk] > 0) {
			new skill = 500 / 100;
			new price = (skill)*(PlayerInfo[playerid][pTraderPerk]);
			new payout = 500 - price;
			format(gString, sizeof(gString), "~r~-$%d", payout);
			GameTextForPlayer(playerid, gString, 5000, 1);
			GivePlayerMoney(playerid,- payout);
			SBizzInfo[9][sbTill] += payout;
			ExtortionSBiz(9, payout);
		} else {
			format(gString, sizeof(gString), "~r~-$%d", 500);
			GameTextForPlayer(playerid, gString, 5000, 1);
			GivePlayerMoney(playerid,-500);
			SBizzInfo[9][sbTill] += 500;
			ExtortionSBiz(9, 500);
		}

		PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
		new randphone = 1000 + random(8999);//minimum 1000  max 9999
		PlayerInfo[playerid][pPnumber] = randphone;
		format(gString, sizeof(gString), "   Mobile Phone Purchased your new Number is %d", randphone);
		SendClientMessage(playerid, COLOR_GRAD4, gString);
		SendClientMessage(playerid, COLOR_GRAD5, "You can check this anytime by Typing /stats");
		SendClientMessage(playerid, COLOR_WHITE, "HINT: You can now type /help to see your cell phone commands.");
		return 1;
	} else if(item == 2 && GetPlayerMoney(playerid) > 7500) {
		if(PlayerInfo[playerid][pTraderPerk] > 0) {
			new skill = 7500 / 100;
			new price = (skill)*(PlayerInfo[playerid][pTraderPerk]);
			new payout = 7500 - price;
			GivePlayerMoney(playerid,- payout);
			SBizzInfo[9][sbTill] += payout;
			ExtortionSBiz(9, payout);
			format(gString, sizeof(gString), "~r~-$%d", payout);
			GameTextForPlayer(playerid, gString, 5000, 1);
		} else {
			GivePlayerMoney(playerid,-7500);
			SBizzInfo[9][sbTill] += 7500;
			ExtortionSBiz(9, 7500);
			format(gString, sizeof(gString), "~r~-$%d", 1000);
			GameTextForPlayer(playerid, gString, 5000, 1);
		}

		PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
		new prize;
		new symb1[32]; new symb2[32]; new symb3[32];
		new randcard1 = random(10);//minimum 1000  max 9999
		new randcard2 = random(10);//minimum 1000  max 9999
		new randcard3 = random(10);//minimum 1000  max 9999

		if(randcard1 >= 5) {
			format(symb1, sizeof(symb1), "~b~]");
			randcard1 = 1;
		} else if(randcard1 <= 4 && randcard1 >= 2) {
			format(symb1, sizeof(symb1), "~g~]");
			randcard1 = 2;
		} else if(randcard1 < 2) {
			format(symb1, sizeof(symb1), "~y~]");
			randcard1 = 3;
		}

		if(randcard2 >= 5) {
			format(symb2, sizeof(symb2), "~b~]");
			randcard2 = 1;
		} else if(randcard2 <= 4 && randcard2 >= 2) {
			format(symb2, sizeof(symb2), "~g~]");
			randcard2 = 2;
		} else if(randcard2 < 2) {
			format(symb2, sizeof(symb2), "~y~]");
			randcard2 = 3;
		}

		if(randcard3 >= 5) {
			format(symb3, sizeof(symb3), "~b~]");
			randcard3 = 1;
		} else if(randcard3 <= 4 && randcard3 >= 2) {
			format(symb3, sizeof(symb3), "~g~]");
			randcard3 = 2;
		} else if(randcard3 < 2) {
			format(symb3, sizeof(symb3), "~y~]");
			randcard3 = 3;
		}

		if(randcard1 == randcard2 && randcard1 == randcard3) {
			if(randcard1 > 5) {
				prize = 2500;
			}

			if(randcard1 <= 4 && randcard1 >= 2) {
				prize = 1500;
			}

			if(randcard1 < 2) {
				prize = 500;
			}

			GivePlayerMoney(playerid,prize);
			SBizzInfo[9][sbTill] -= prize;
			ExtortionSBiz(9, prize);
			format(gString, sizeof(gString), "%s %s %s ~n~~n~~w~~g~$%d",symb1,symb2,symb3, prize);
		} else {
			format(gString, sizeof(gString), "%s %s %s ~n~~n~~w~~r~$0",symb1,symb2,symb3);
		}

		GameTextForPlayer(playerid, gString, 3000, 3);
		return 1;
	} else if(item == 3 && GetPlayerMoney(playerid) > 5000) {
		if(PlayerInfo[playerid][pTraderPerk] > 0) {
			new skill = 5000 / 100;
			new price = (skill)*(PlayerInfo[playerid][pTraderPerk]);
			new payout = 5000 - price;
			GivePlayerMoney(playerid,- payout);
			SBizzInfo[9][sbTill] += payout;
			ExtortionSBiz(9, payout);
			format(gString, sizeof(gString), "~r~-$%d", payout);
			GameTextForPlayer(playerid, gString, 5000, 1);
		} else {
			GivePlayerMoney(playerid,-5000);
			SBizzInfo[9][sbTill] += 5000;
			ExtortionSBiz(9, 5000);
			format(gString, sizeof(gString), "~r~-$%d", 5000);
			GameTextForPlayer(playerid, gString, 5000, 1);
		}

		PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
		PlayerInfo[playerid][pPhoneBook] = 1;
		format(gString, sizeof(gString), "   Phone Book Purchased you can look up any Players Number !");
		SendClientMessage(playerid, COLOR_GRAD4, gString);
		SendClientMessage(playerid, COLOR_WHITE, "HINT: Type /number <id/name>.");
		return 1;
	} else if(item == 4 && GetPlayerMoney(playerid) > 500) {
		if(PlayerInfo[playerid][pTraderPerk] > 0) {
			new skill = 500 / 100;
			new price = (skill)*(PlayerInfo[playerid][pTraderPerk]);
			new payout = 500 - price;
			GivePlayerMoney(playerid,- payout);
			SBizzInfo[9][sbTill] += payout;
			ExtortionSBiz(9, payout);
			format(gString, sizeof(gString), "~r~-$%d", payout);
			GameTextForPlayer(playerid, gString, 5000, 1);
		} else {
			GivePlayerMoney(playerid,-500);
			SBizzInfo[9][sbTill] += 500;
			ExtortionSBiz(9, 500);
			format(gString, sizeof(gString), "~r~-$%d", 500);
			GameTextForPlayer(playerid, gString, 5000, 1);
		}

		PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
		gDice[playerid] = 1;
		format(gString, sizeof(gString), "   Dice Purchased you can throw your Dice.");
		SendClientMessage(playerid, COLOR_GRAD4, gString);
		SendClientMessage(playerid, COLOR_WHITE, "HINT: Type /dice ");
		return 1;
	} else if(item == 5 && GetPlayerMoney(playerid) > 5000) {
		if(gLastCar[playerid] != 0) {
			if(HireCar[playerid] != 299) {
				gCarLock[HireCar[playerid]] = 0;
				UnLockCar(HireCar[playerid]);
				HireCar[playerid] = 299;
			}

			if(PlayerInfo[playerid][pTraderPerk] > 0) {
				new skill = 5000 / 100;
				new price = (skill)*(PlayerInfo[playerid][pTraderPerk]);
				new payout = 5000 - price;
				GivePlayerMoney(playerid,- payout);
				SBizzInfo[9][sbTill] += payout;
				ExtortionSBiz(9, payout);
				format(gString, sizeof(gString), "~r~-$%d", payout);
				GameTextForPlayer(playerid, gString, 5000, 1);
			} else {
				GivePlayerMoney(playerid,-5000);
				SBizzInfo[9][sbTill] += 5000;
				ExtortionSBiz(9, 5000);
				format(gString, sizeof(gString), "~r~-$%d", 5000);
				GameTextForPlayer(playerid, gString, 5000, 1);
			}

			SBizzInfo[9][sbProducts]--;
			PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
			HireCar[playerid] = gLastCar[playerid];
			format(gString, sizeof(gString), "Key Purchased You Can Lock Your Last Vehicle.");
			SendClientMessage(playerid, COLOR_GRAD4, gString);
			SendClientMessage(playerid, COLOR_WHITE, "HINT: Type /lock ");
		} else {
			SendClientMessage(playerid, COLOR_WHITE, "   You don't have a Vehicle to fit it to !");
		}
		return 1;
	}
	else if(item == 6 && GetPlayerMoney(playerid) > 10000) {
		if(PlayerInfo[playerid][pPhousekey] != 255) {
			foreach(new i : Player) {
				if(HireCar[PlayerInfo[playerid][pPhousekey]+1]) {
					HireCar[i] = 299;
				}
			}

			if(PlayerInfo[playerid][pTraderPerk] > 0) {
				new skill = 10000 / 100;
				new price = (skill)*(PlayerInfo[playerid][pTraderPerk]);
				new payout = 10000 - price;
				GivePlayerMoney(playerid,- payout);
				SBizzInfo[9][sbTill] += payout;
				ExtortionSBiz(9, payout);
				format(gString, sizeof(gString), "~r~-$%d", payout);
				GameTextForPlayer(playerid, gString, 5000, 1);
			} else {
				GivePlayerMoney(playerid,-10000);
				SBizzInfo[9][sbTill] += 10000;
				ExtortionSBiz(9, 10000);
				format(gString, sizeof(gString), "~r~-$%d", 10000);
				GameTextForPlayer(playerid, gString, 5000, 1);
			}

			SBizzInfo[9][sbProducts]--;
			PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
			format(gString, sizeof(gString), "New Locks Purchased.");
			SendClientMessage(playerid, COLOR_GRAD4, gString);
			SendClientMessage(playerid, COLOR_WHITE, "HINT: Type /lock ");
		} else {
			SendClientMessage(playerid, COLOR_WHITE, "   You don't have a Vehicle to fit it to !");
		}
		return 1;
	}
	else if(item == 7 && GetPlayerMoney(playerid) > 5000) {
		gSpeedo[playerid] = 1;

		if(PlayerInfo[playerid][pTraderPerk] > 0) {
			new skill = 5000 / 100;
			new price = (skill)*(PlayerInfo[playerid][pTraderPerk]);
			new payout = 5000 - price;
			GivePlayerMoney(playerid,- payout);
			SBizzInfo[9][sbTill] += payout;
			ExtortionSBiz(9, payout);
			format(gString, sizeof(gString), "~r~-$%d", payout);
			GameTextForPlayer(playerid, gString, 5000, 1);
		} else {
			GivePlayerMoney(playerid,-5000);
			SBizzInfo[9][sbTill] += 5000;
			ExtortionSBiz(9, 5000);
			format(gString, sizeof(gString), "~r~-$%d", 5000);
			GameTextForPlayer(playerid, gString, 5000, 1);
		}

		SBizzInfo[9][sbProducts]--;
		PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
		format(gString, sizeof(gString), "Speedometer Purchased.");
		SendClientMessage(playerid, COLOR_GRAD4, gString);
		SendClientMessage(playerid, COLOR_WHITE, "HINT: Type /speedo ");
		return 1;
	} else if(item == 8 && GetPlayerMoney(playerid) > 49) {
		if(PlayerInfo[playerid][pTraderPerk] > 0) {
			new skill = 50 / 100;
			new price = (skill)*(PlayerInfo[playerid][pTraderPerk]);
			new payout = 50 - price;
			GivePlayerMoney(playerid,- payout);
			format(gString, sizeof(gString), "~r~-$%d", payout);
			GameTextForPlayer(playerid, gString, 5000, 1);
		} else {
			GivePlayerMoney(playerid,-50);
			format(gString, sizeof(gString), "~r~-$%d", 50);
			GameTextForPlayer(playerid, gString, 5000, 1);
		}

		Condom[playerid] ++;
		PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
		format(gString, sizeof(gString), "Condom Purchased.");
		SendClientMessage(playerid, COLOR_GRAD4, gString);
		return 1;
	} else if(item == 9 && GetPlayerMoney(playerid) > 2500) {
		if(PlayerInfo[playerid][pTraderPerk] > 0) {
			new skill = 2500 / 100;
			new price = (skill)*(PlayerInfo[playerid][pTraderPerk]);
			new payout = 2500 - price;
			GivePlayerMoney(playerid, - payout);
			format(gString, sizeof(gString), "~r~-$%d", payout);
			GameTextForPlayer(playerid, gString, 5000, 1);
		} else {
			GivePlayerMoney(playerid, - 2500);
			format(gString, sizeof(gString), "~r~-$%d", 2500);
			GameTextForPlayer(playerid, gString, 5000, 1);
		}

		PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
		format(gString, sizeof(gString), "CD-Player Purchased.");
		SendClientMessage(playerid, COLOR_GRAD4, gString);
		SendClientMessage(playerid, COLOR_WHITE, "HINT: Type /music");
		PlayerInfo[playerid][pCDPlayer] = 1;
		return 1;
	} else if(item == 10 && GetPlayerMoney(playerid) > 10) {
		if(Groceries[playerid][pChickens] >= 3) {
			return SendClientMessage(playerid, COLOR_GREY, "   You have to many Chickens, Cook some first !");
		}

		if(PlayerInfo[playerid][pTraderPerk] > 0) {
			new skill = 10 / 100;
			new price = (skill)*(PlayerInfo[playerid][pTraderPerk]);
			new payout = 10 - price;
			GivePlayerMoney(playerid, - payout);
			format(gString, sizeof(gString), "~r~-$%d", payout);
			GameTextForPlayer(playerid, gString, 5000, 1);
		} else {
			GivePlayerMoney(playerid, - 10);
			format(gString, sizeof(gString), "~r~-$%d", 10);
			GameTextForPlayer(playerid, gString, 5000, 1);
		}

		GivePlayerMoney(playerid, - 10);
		PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
		format(gString, sizeof(gString), "Chicken Purchased.");
		SendClientMessage(playerid, COLOR_GRAD4, gString);
		format(gString, sizeof(gString), "~r~-$%d", 10);
		GameTextForPlayer(playerid, gString, 5000, 1);
		new rand = random(15);
		Groceries[playerid][pChickens] += 1;
		Groceries[playerid][pChicken] += rand;
		return 1;
	} else if(item == 11 && GetPlayerMoney(playerid) > 10) {
		if(Groceries[playerid][pHamburgers] >= 3) {
			return SendClientMessage(playerid, COLOR_GREY, "   You have to many Hamburgers, Cook some first !");
		}

		if(PlayerInfo[playerid][pTraderPerk] > 0) {
			new skill = 10 / 100;
			new price = (skill)*(PlayerInfo[playerid][pTraderPerk]);
			new payout = 10 - price;
			GivePlayerMoney(playerid, - payout);
			format(gString, sizeof(gString), "~r~-$%d", payout);
			GameTextForPlayer(playerid, gString, 5000, 1);
		} else {
			GivePlayerMoney(playerid, - 10);
			format(gString, sizeof(gString), "~r~-$%d", 10);
			GameTextForPlayer(playerid, gString, 5000, 1);
		}

		GivePlayerMoney(playerid, - 10);
		PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
		format(gString, sizeof(gString), "Hamburger Purchased.");
		SendClientMessage(playerid, COLOR_GRAD4, gString);
		format(gString, sizeof(gString), "~r~-$%d", 10);
		GameTextForPlayer(playerid, gString, 5000, 1);
		new rand = random(15);
		Groceries[playerid][pHamburgers] += 1;
		Groceries[playerid][pHamburger] += rand;
		return 1;
	} else if(item == 12 && GetPlayerMoney(playerid) > 10) {
		if(Groceries[playerid][pPizzas] >= 3) {
			return SendClientMessage(playerid, COLOR_GREY, "   You have to many Pizzas, Cook some first !");
		}

		if(PlayerInfo[playerid][pTraderPerk] > 0) {
			new skill = 10 / 100;
			new price = (skill)*(PlayerInfo[playerid][pTraderPerk]);
			new payout = 10 - price;
			GivePlayerMoney(playerid, - payout);
			format(gString, sizeof(gString), "~r~-$%d", payout);
			GameTextForPlayer(playerid, gString, 5000, 1);
		} else {
			GivePlayerMoney(playerid, - 10);
			format(gString, sizeof(gString), "~r~-$%d", 10);
			GameTextForPlayer(playerid, gString, 5000, 1);
		}

		PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
		format(gString, sizeof(gString), "Frozen Pizza Purchased.");
		SendClientMessage(playerid, COLOR_GRAD4, gString);
		new rand = random(15);
		Groceries[playerid][pPizzas] += 1;
		Groceries[playerid][pPizza] += rand;
		return 1;
	} else {
		SendClientMessage(playerid, COLOR_WHITE, "   You don't have the cash for that !");
	}
	return 1;
}

CMD:buyhouse(playerid, params[]) {
	new Float:oldposx, Float:oldposy, Float:oldposz;

	GetPlayerPos(playerid, oldposx, oldposy, oldposz);

	for(new h = 0; h < sizeof(HouseInfo); h++) {
		if(PlayerToPoint(2.0, playerid, HouseInfo[h][hEntrancex], HouseInfo[h][hEntrancey], HouseInfo[h][hEntrancez]) && HouseInfo[h][hOwned] == 0) {
			if(PlayerInfo[playerid][pLevel] < HouseInfo[h][hLevel]) {
				format(gString, sizeof(gString), "   You must be Level %d to purchase this !", HouseInfo[h][hLevel]);
				SendClientMessage(playerid, COLOR_GRAD5, gString);
				return 1;
			}

			if(PlayerInfo[playerid][pPhousekey] != 255 && strcmp(PlayerInfo[playerid][pName], HouseInfo[PlayerInfo[playerid][pPhousekey]][hOwner], true) == 0) {
				SendClientMessage(playerid, COLOR_WHITE, "   You already own a house, type /sellhouse if you want to buy this one !");
				return 1;
			}

			if(GetPlayerMoney(playerid) > HouseInfo[h][hValue]) {
				PlayerInfo[playerid][pPhousekey] = h;
				HouseInfo[h][hOwned] = 1;
				strmid(HouseInfo[h][hOwner], PlayerInfo[playerid][pName], 0, strlen(PlayerInfo[playerid][pName]), 255);
				GivePlayerMoney(playerid,-HouseInfo[h][hValue]);
				PlayerPlayMusic(playerid);
				SetPlayerInterior(playerid,HouseInfo[h][hInt]);
				SetPlayerPos(playerid,HouseInfo[h][hExitx],HouseInfo[h][hExity],HouseInfo[h][hExitz]);
				GameTextForPlayer(playerid, "~w~Welcome Home~n~You can exit at any time by moving to this door and typing /exit", 5000, 3);
				PlayerInfo[playerid][pInt] = HouseInfo[h][hInt];
				PlayerInfo[playerid][pLocal] = h;
				SendClientMessage(playerid, COLOR_WHITE, "Congratulations, on your new Purchase !");
				SendClientMessage(playerid, COLOR_WHITE, "Type /help to review the new property help section !");
				DateProp(playerid);
				OnPropUpdate();
				OnPlayerUpdate(playerid);
			} else {
				SendClientMessage(playerid, COLOR_WHITE, "   You don't have the cash for that !");
			}
		}
	}
	return 1;
}

CMD:rentroom(playerid, params[]) {
	new Float:oldposx, Float:oldposy, Float:oldposz;

	GetPlayerPos(playerid, oldposx, oldposy, oldposz);

	for(new h = 0; h < sizeof(HouseInfo); h++) {
		if(PlayerToPoint(2.0, playerid, HouseInfo[h][hEntrancex], HouseInfo[h][hEntrancey], HouseInfo[h][hEntrancez]) && HouseInfo[h][hOwned] == 1 &&  HouseInfo[h][hRentabil] == 1) {
			if(PlayerInfo[playerid][pPhousekey] != 255 && strcmp(PlayerInfo[playerid][pName], HouseInfo[PlayerInfo[playerid][pPhousekey]][hOwner], true) == 0) {
				SendClientMessage(playerid, COLOR_WHITE, "   You already own a house, type /sellhouse if you want to rent this one.");
				return 1;
			}

			if(GetPlayerMoney(playerid) > HouseInfo[h][hRent]) {
				PlayerInfo[playerid][pPhousekey] = h;
				GivePlayerMoney(playerid,-HouseInfo[h][hRent]);
				HouseInfo[h][hTakings] = HouseInfo[h][hTakings]+HouseInfo[h][hRent];
				PlayerPlayMusic(playerid);
				SetPlayerInterior(playerid,HouseInfo[h][hInt]);
				SetPlayerPos(playerid,HouseInfo[h][hExitx],HouseInfo[h][hExity],HouseInfo[h][hExitz]);
				GameTextForPlayer(playerid, "~w~Welcome Home~n~You can exit at any time by moving to this door and typing /exit", 5000, 3);
				PlayerInfo[playerid][pInt] = HouseInfo[h][hInt];
				PlayerInfo[playerid][pLocal] = h;
				SendClientMessage(playerid, COLOR_WHITE, "Congratulations, You can enter and exit here anytime.");
				SendClientMessage(playerid, COLOR_WHITE, "Type /help to review the new property help section.");
				OnPlayerUpdate(playerid);
				return 1;
			} else {
				SendClientMessage(playerid, COLOR_WHITE, "You don't have the cash for that");
			}
		}
	}
	return 1;
}

CMD:rentcar(playerid, params[]) {
	if(GetPlayerVehicleID(playerid) >= 72 && GetPlayerVehicleID(playerid) <= 77) {
		new hirefee = HireCost(GetPlayerVehicleID(playerid));

		if(GetPlayerVehicleID(playerid) >= 72 && GetPlayerVehicleID(playerid) <= 74) {
			if(SBizzInfo[0][sbProducts] == 0) {
				GameTextForPlayer(playerid, "~r~Out Of Stock", 5000, 1);
				return 1;
			}

			if(PlayerInfo[playerid][pPbiskey] == 0) {
				GameTextForPlayer(playerid, "~w~No charge for the boss", 5000, 3);
				TogglePlayerControllable(playerid, 1);
				return 1;
			}

			if(GetPlayerMoney(playerid) <  SBizzInfo[0][sbEntranceCost]) {
				SendClientMessage(playerid, COLOR_GRAD2, "   You dont have that much cash !");
				return 1;
			}

			GivePlayerMoney(playerid,-SBizzInfo[0][sbEntranceCost]);
			SBizzInfo[0][sbTill] += SBizzInfo[0][sbEntranceCost];
			ExtortionSBiz(0, SBizzInfo[0][sbEntranceCost]);
			SBizzInfo[0][sbProducts]--;
		}

		if(GetPlayerVehicleID(playerid) >= 75 && GetPlayerVehicleID(playerid) <= 77) {
			if(SBizzInfo[1][sbProducts] == 0) {
				GameTextForPlayer(playerid, "~r~Out Of Stock", 5000, 1);
				return 1;
			}

			if(PlayerInfo[playerid][pPbiskey] == 1) {
				GameTextForPlayer(playerid, "~w~No charge for the boss", 5000, 3);
				TogglePlayerControllable(playerid, 1);
				return 1;
			}

			if(GetPlayerMoney(playerid) <  SBizzInfo[1][sbEntranceCost]) {
				SendClientMessage(playerid, COLOR_GRAD2, "   You dont have that much cash !");
				return 1;
			}

			GivePlayerMoney(playerid,-SBizzInfo[1][sbEntranceCost]);
			SBizzInfo[1][sbTill] += SBizzInfo[1][sbEntranceCost];
			ExtortionSBiz(1, SBizzInfo[1][sbEntranceCost]);
			SBizzInfo[1][sbProducts]--;
		}

		if(HireCar[playerid] != 299) {
			gCarLock[HireCar[playerid]] = 0;
			UnLockCar(HireCar[playerid]);
		}

		HireCar[playerid] = GetPlayerVehicleID(playerid);
		OnPropUpdate();
		PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
		format(gString, sizeof(gString), "~w~We hope you enjoy ~n~the use of this car~n~To lock or unlock your car~n~type ~g~/lock~n~~w~please drive safely",hirefee);
		TogglePlayerControllable(playerid, 1);
		GameTextForPlayer(playerid, gString, 5000, 3);
	}
	return 1;
}

CMD:hirecar(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] >= 1337) {
		new car;

		if(sscanf(params, "i", car)) {
			SendClientMessage(playerid, COLOR_GRAD1, "Uzycie: /hirecar [key id]");
			return 1;
		}

		HireCar[playerid] = car;
		format(gString, sizeof(gString), "Key Fashioned You Can Lock Car %d.",car);
		SendClientMessage(playerid, COLOR_GRAD4, gString);
		SendClientMessage(playerid, COLOR_WHITE, "HINT: Type /lock ");
		return 1;
	}
	return 1;
}

CMD:switchkey(playerid, params[]) {
	if(!SwitchKey[playerid]) {
		if(HireCar[playerid] != 299) {
			SwitchKey[playerid] = 1;
			GameTextForPlayer(playerid, "~w~You control now your house car", 5000, 6);
		} else {
			GameTextForPlayer(playerid, "~w~You do not hire a car", 5000, 6);
		}
		return 1;
	} else {
		SwitchKey[playerid] = 0;
		GameTextForPlayer(playerid, "~w~You control now your hire car", 5000, 6);
	}
	return 1;
}

CMD:givekey(playerid, params[]) {
	new giveplayerid, car;

	if(sscanf(params, "i", giveplayerid)) {
		SendClientMessage(playerid, COLOR_GRAD1, "Uzycie: /givekey [playerid/PartOfName]");
		return 1;
	}

	if(HireCar[playerid] == 299 && PlayerInfo[playerid][pPhousekey] == 255) {
		SendClientMessage(playerid, COLOR_GRAD1, "  You dont have a key to give");
		return 1;
	} else {
		if(HireCar[playerid] != 299 && SwitchKey[playerid] == 0) {
			car = HireCar[playerid];
			gCarLock[car] = 0;
			UnLockCar(car);
			HireCar[playerid] = 299;
		} else {
			car = PlayerInfo[playerid][pPhousekey]+1;
		}
	}

	if(IsPlayerConnected(giveplayerid)) {
		if(ProxDetectorS(5.0, playerid, giveplayerid)) {
			if(HireCar[giveplayerid] != 299) {
				gCarLock[HireCar[giveplayerid]] = 0;
				UnLockCar(HireCar[giveplayerid]);
			}

			HireCar[giveplayerid] = car;
			format(gString, sizeof(gString), "   You have given %s the key to your vehicle", PlayerInfo[giveplayerid][pName]);
			PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
			SendClientMessage(playerid, COLOR_GRAD1, gString);
			format(gString, sizeof(gString), "   You have recieved the key to a vehicle from %s", PlayerInfo[playerid][pName]);
			SendClientMessage(giveplayerid, COLOR_GRAD1, gString);
			format(gString, sizeof(gString), "* %s takes out a set of keys, and tosses them to %s.", PlayerInfo[playerid][pName] ,PlayerInfo[giveplayerid][pName]);
			ProxDetector(30.0, playerid, gString, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
		}
	}
	return 1;
}

CMD:unrentcar(playerid, params[]) {
	if(HireCar[playerid] != 299) {
		gCarLock[HireCar[playerid]] = 0;
		UnLockCar(HireCar[playerid]);
		HireCar[playerid] = 299;
		GameTextForPlayer(playerid, "~w~You no longer rent a car", 5000, 3);
	}
	return 1;
}

CMD:unrent(playerid, params[]) {
	if(PlayerInfo[playerid][pPhousekey] != 255 && strcmp(PlayerInfo[playerid][pName], HouseInfo[PlayerInfo[playerid][pPhousekey]][hOwner], true) == 0) {
		SendClientMessage(playerid, COLOR_WHITE, "   You own this house !");
		return 1;
	}

	PlayerInfo[playerid][pPhousekey] = 255;
	SendClientMessage(playerid, COLOR_WHITE, "You are now homeless.");
	return 1;
}

CMD:housewithdraw(playerid, params[]) {
	new bouse = PlayerInfo[playerid][pPhousekey];

	if(PlayerInfo[playerid][pPhousekey] != 255 && strcmp(PlayerInfo[playerid][pName], HouseInfo[PlayerInfo[playerid][pPhousekey]][hOwner], true) == 0) {
		new cashdeposit;

		if(sscanf(params, "i", cashdeposit)) {
			SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /housewithdraw [amount]");
			format(gString, sizeof(gString), "  You Have $%d in your cashbox.", HouseInfo[bouse][hTakings]);
			SendClientMessage(playerid, COLOR_GRAD3, gString);
			return 1;
		}

		if(cashdeposit >  HouseInfo[bouse][hTakings] || cashdeposit < 1) {
			SendClientMessage(playerid, COLOR_GRAD2, "   You dont have that much !");
			return 1;
		}

		if(!PlayerToPoint(100, playerid,HouseInfo[bouse][hExitx],HouseInfo[bouse][hExity],HouseInfo[bouse][hExitz])) {
			SendClientMessage(playerid, COLOR_GRAD2, "   You are to far from your house !");
			return 1;
		} else {
			ConsumingMoney[playerid] = 1;
			GivePlayerMoney(playerid,cashdeposit);
			HouseInfo[bouse][hTakings]=HouseInfo[bouse][hTakings]-cashdeposit;
			format(gString, sizeof(gString), "  You Have Withdrawn $%d from your cashbox Total: $%d ", cashdeposit,HouseInfo[bouse][hTakings]);
			OnPropUpdate();
			SendClientMessage(playerid, COLOR_YELLOW, gString);
			return 1;
		}
	} else {
		SendClientMessage(playerid, COLOR_WHITE, "You don't own a house.");
	}
	return 1;
}

CMD:asellbiz(playerid, params[]) {
	new biz;

	if(sscanf(params, "i", biz)) {
		SendClientMessage(playerid, COLOR_GRAD1, "Uzycie: /asellbiz [bizid]");
		return 1;
	}

	if(PlayerInfo[playerid][pAdmin] >= 4) {
		BizzInfo[biz][bLocked] = 1;
		BizzInfo[biz][bOwned] = 0;
		strmid(BizzInfo[biz][bOwner], "The State", 0, strlen("The State"), 255);
		strmid(BizzInfo[biz][bExtortion], "No-one", 0, strlen("No-one"), 255);
		PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
		format(gString, sizeof(gString), "~w~You have sold the Business");
		GameTextForPlayer(playerid, gString, 10000, 3);
		OnPropUpdate();
	} else {
		SendClientMessage(playerid, COLOR_WHITE, "You are not an admin.");
	}
	return 1;
}

CMD:asellsbiz(playerid, params[]) {
	new sbiz;

	if(sscanf(params, "i", sbiz)) {
		SendClientMessage(playerid, COLOR_GRAD1, "Uzycie: /asellsbiz [sbizid]");
		return 1;
	}

	if(PlayerInfo[playerid][pAdmin] >= 4) {
		SBizzInfo[sbiz][sbLocked] = 1;
		SBizzInfo[sbiz][sbOwned] = 0;
		strmid(SBizzInfo[sbiz][sbOwner], "The State", 0, strlen("The State"), 255);
		strmid(SBizzInfo[sbiz][sbExtortion], "No-one", 0, strlen("No-one"), 255);
		PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
		format(gString, sizeof(gString), "~w~You have sold the Business");
		GameTextForPlayer(playerid, gString, 10000, 3);
		OnPropUpdate();
	} else {
		SendClientMessage(playerid, COLOR_WHITE, "You are not an admin.");
	}
	return 1;
}

CMD:asellhouse(playerid, params[]) {
	new house;

	if(sscanf(params, "i", house)) {
		SendClientMessage(playerid, COLOR_GRAD1, "Uzycie: /asellhouse [houseid]");
		return 1;
	}

	if(PlayerInfo[playerid][pAdmin] >= 4) {
		HouseInfo[house][hHel] = 0;
		HouseInfo[house][hArm] = 0;
		HouseInfo[house][hHealthx] = 0;
		HouseInfo[house][hHealthy] = 0;
		HouseInfo[house][hHealthz] = 0;
		HouseInfo[house][hArmourx] = 0;
		HouseInfo[house][hArmoury] = 0;
		HouseInfo[house][hArmourz] = 0;
		HouseInfo[house][hLock] = 1;
		HouseInfo[house][hOwned] = 0;
		HouseInfo[house][hVec] = 418;
		HouseInfo[house][hVcol1] = -1;
		HouseInfo[house][hVcol2] = -1;
		strmid(HouseInfo[house][hOwner], "The State", 0, strlen("The State"), 255);
		PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
		format(gString, sizeof(gString), "~w~You have sold this property", HouseInfo[house][hValue]);
		GameTextForPlayer(playerid, gString, 10000, 3);
		OnPropUpdate();
	} else {
		SendClientMessage(playerid, COLOR_WHITE, "You are not an admin.");
	}
	return 1;
}

CMD:sellhouse(playerid, params[]) {
	if(PlayerInfo[playerid][pPhousekey] == 255) {
		SendClientMessage(playerid, COLOR_WHITE, "You don't own a house.");
		return 1;
	}

	if(PlayerInfo[playerid][pMarried] > 0) {
		SendClientMessage(playerid, COLOR_GREY, "   You are Married, can't sell the House !");
		return 1;
	}

	if(PlayerInfo[playerid][pPhousekey] != 255 && strcmp(PlayerInfo[playerid][pName], HouseInfo[PlayerInfo[playerid][pPhousekey]][hOwner], true) == 0) {
		new house = PlayerInfo[playerid][pPhousekey];
		HouseInfo[house][hHel] = 0;
		HouseInfo[house][hArm] = 0;
		HouseInfo[house][hHealthx] = 0;
		HouseInfo[house][hHealthy] = 0;
		HouseInfo[house][hHealthz] = 0;
		HouseInfo[house][hArmourx] = 0;
		HouseInfo[house][hArmoury] = 0;
		HouseInfo[house][hArmourz] = 0;
		HouseInfo[house][hLock] = 1;
		HouseInfo[house][hOwned] = 0;
		HouseInfo[house][hVec] = 418;
		HouseInfo[house][hVcol1] = -1;
		HouseInfo[house][hVcol2] = -1;
		strmid(HouseInfo[house][hOwner], "The State", 0, strlen("The State"), 255);
		ConsumingMoney[playerid] = 1;
		GivePlayerMoney(playerid,HouseInfo[house][hValue]);
		PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
		format(gString, sizeof(gString), "~w~Congratulations~n~ You have sold your property for ~n~~g~$%d", HouseInfo[house][hValue]);
		GameTextForPlayer(playerid, gString, 10000, 3);
		PlayerInfo[playerid][pPhousekey] = 255;

		if(PlayerInfo[playerid][pLocal] == house) {
			SetPlayerInterior(playerid,0);
			SetPlayerPos(playerid,HouseInfo[house][hEntrancex],HouseInfo[house][hEntrancey],HouseInfo[house][hEntrancez]);
			PlayerInfo[playerid][pInt] = 0;
		}

		OnPropUpdate();
		OnPlayerUpdate(playerid);
	}
	else {
		SendClientMessage(playerid, COLOR_WHITE, "You don't own a house.");
	}
	return 1;
}

CMD:houseupgrade(playerid, params[]) {
	new house = PlayerInfo[playerid][pPhousekey];

	if(house != 255 && strcmp(PlayerInfo[playerid][pName], HouseInfo[PlayerInfo[playerid][pPhousekey]][hOwner], true) == 0) {
		new item;

		if(sscanf(params, "i", item)) {
			SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /houseupgrade [item number]");
			SendClientMessage(playerid, COLOR_GRAD1, "|_______ Home Supplys _______|");
			SendClientMessage(playerid, COLOR_GRAD2, "| 1: Health Upgrade $50000");
			SendClientMessage(playerid, COLOR_GRAD3, "| 2: Armour Upgrade $100000");
			SendClientMessage(playerid, COLOR_GRAD5, "| 3: TV $500");
			return 1;
		}

		switch(item) {
			case 1: {
				if(SBizzInfo[6][sbProducts] == 0) {
					GameTextForPlayer(playerid, "~r~Out Of Stock", 5000, 1);
					return 1;
				}

				if(PlayerInfo[playerid][pLevel] < 5) {
					SendClientMessage(playerid, COLOR_GRAD5, "You Must Be Level 5 To Purchase This");
					return 1;
				}

				if(GetPlayerMoney(playerid) < 50000) {
					SendClientMessage(playerid, COLOR_GRAD5, "You Don't Have The Cash To Purchase This");
					return 1;
				}

				HouseInfo[house][hHel] = 1;
				GivePlayerMoney(playerid,-50000);
				SBizzInfo[6][sbTill] += 50000;//heal buisness
				ExtortionSBiz(6, 50000);
				SBizzInfo[6][sbProducts]--;
				PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
				SendClientMessage(playerid, COLOR_GRAD5, "You Can Now Heal Yourself At Home, Type /heal.");
			}
			case 2: {
				if(!IsACop(playerid)) {
					SendClientMessage(playerid, COLOR_GREY, "   You can't buy this, you are not a Cop !");
					return 1;
				}

				if(SBizzInfo[6][sbProducts] == 0) {
					GameTextForPlayer(playerid, "~r~Out Of Stock", 5000, 1);
					return 1;
				}

				if(PlayerInfo[playerid][pLevel] < 7) {
					SendClientMessage(playerid, COLOR_GRAD5, "You Must Be Level 7 To Purchase This");
					return 1;
				}

				if(GetPlayerMoney(playerid) < 100000) {
					SendClientMessage(playerid, COLOR_GRAD5, "You Don't Have The Cash To Purchase This");
					return 1;
				}

				HouseInfo[house][hArm] = 1;
				GivePlayerMoney(playerid,-100000);
				SBizzInfo[6][sbTill] += 100000;//heal buisness
				ExtortionSBiz(6, 100000);
				SBizzInfo[6][sbProducts]--;
				PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
				SendClientMessage(playerid, COLOR_GRAD5, "You Can Now Get Armour At Home, Type /heal.");
			}
			case 3: {
				if(SBizzInfo[6][sbProducts] == 0) {
					GameTextForPlayer(playerid, "~r~Out Of Stock", 5000, 1);
					return 1;
				}

				if(PlayerInfo[playerid][pLevel] < 3) {
					SendClientMessage(playerid, COLOR_GRAD5, "You Must Be Level 3 To Purchase This");
					return 1;
				}

				if(GetPlayerMoney(playerid) < 500) {
					SendClientMessage(playerid, COLOR_GRAD5, "You Don't Have The Cash To Purchase This");
					return 1;
				}

				HouseInfo[house][hHealthx] = 1;
				GivePlayerMoney(playerid,-500);
				SBizzInfo[6][sbTill] += 500;
				ExtortionSBiz(6, 500);
				SBizzInfo[6][sbProducts]--;
				PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
				SendClientMessage(playerid, COLOR_GRAD5, "You can now use your TV set, type /tv.");
			}
		}

		OnPropUpdate();
		OnPlayerUpdate(playerid);
	} else {
		SendClientMessage(playerid, COLOR_GRAD2, "   You don't own a house");
	}
	return 1;
}

alias:houseupgrade("hu")

CMD:setrent(playerid, params[]) {
	new bouse = PlayerInfo[playerid][pPhousekey];

	if(bouse != 255 && strcmp(PlayerInfo[playerid][pName], HouseInfo[PlayerInfo[playerid][pPhousekey]][hOwner], true) == 0) {
		new tmp;

		if(sscanf(params, "i", tmp)) {
			SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /setrent [RentFee]");
			return 1;
		}

		if(tmp < 1 || tmp > 99999) {
			SendClientMessage(playerid, COLOR_WHITE, "Minimum rent is $1, Maximum rent is $99999.");
			return 1;
		}

		HouseInfo[bouse][hRent] = tmp;
		OnPropUpdate();
		format(gString, sizeof(gString), "House rent set to $%d", HouseInfo[bouse][hRent]);
		SendClientMessage(playerid, COLOR_WHITE, gString);
	} else {
		SendClientMessage(playerid, COLOR_GRAD2, "   You don't own a house");
	}
	return 1;
}

CMD:evictall(playerid, params[]) {
	new bouse = PlayerInfo[playerid][pPhousekey];

	if(bouse != 255 && strcmp(PlayerInfo[playerid][pName], HouseInfo[PlayerInfo[playerid][pPhousekey]][hOwner], true) == 0) {
		foreach(new i : Player) {
			if(i != playerid) {
				if(PlayerInfo[i][pPhousekey] == PlayerInfo[playerid][pPhousekey] ) {
					SendClientMessage(i, COLOR_WHITE, "You have been evicted from your house.");
					SendClientMessage(playerid, COLOR_WHITE, "Everyone have been evicted.");
					PlayerInfo[i][pPhousekey] = 255;
					return 1;
				}
			}
		}
	} else {
		SendClientMessage(playerid, COLOR_GRAD2, "   You don't own a house !");
		return 1;
	}
	return 1;
}

CMD:evict(playerid, params[]) {
	new bouse = PlayerInfo[playerid][pPhousekey];

	if(bouse != 255 && strcmp(PlayerInfo[playerid][pName], HouseInfo[PlayerInfo[playerid][pPhousekey]][hOwner], true) == 0) {
		new target;

		if(sscanf(params, "i", target)) {
			return SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /evict [playerid/PartOfName]");
		}

		if(target == playerid)
		{
			SendClientMessage(target, COLOR_WHITE, "You cant evict yourself.");
			return 1;
		}

		if(IsPlayerConnected(target)) {
			if(PlayerInfo[target][pPhousekey] == PlayerInfo[playerid][pPhousekey]) {
				SendClientMessage(target, COLOR_WHITE, "You have been evicted");
				SendClientMessage(playerid, COLOR_WHITE, "Player has been evicted");
				PlayerInfo[target][pPhousekey] = 255;
				return 1;
			} else {
				SendClientMessage(playerid, COLOR_WHITE, "Player doesn't rent at your House !");
				return 1;
			}
		}
	} else {
		SendClientMessage(playerid, COLOR_GRAD2, "   You don't own a house !");
		return 1;
	}
	return 1;
}

CMD:setrentable(playerid, params[]) {
	new bouse = PlayerInfo[playerid][pPhousekey];

	if(bouse != 255 && strcmp(PlayerInfo[playerid][pName], HouseInfo[PlayerInfo[playerid][pPhousekey]][hOwner], true) == 0) {
		new tmp;

		if(sscanf(params, "i", tmp)) {
			return SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /setrentable [0/1]");
		}

		HouseInfo[bouse][hRentabil] = tmp;
		OnPropUpdate();
		format(gString, sizeof(gString), "House rentable set to %d.", HouseInfo[bouse][hRentabil]);
		SendClientMessage(playerid, COLOR_WHITE, gString);
	} else {
		SendClientMessage(playerid, COLOR_GRAD2, "   You don't own a house !");
	}
	return 1;
}

CMD:call(playerid, params[]) {
	new phonenumb, giveplayerid;

	if(sscanf(params, "i", phonenumb)) {
		SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /call [phonenumber]");
		return 1;
	}

	if(PlayerInfo[playerid][pPnumber] == 0) {
		SendClientMessage(playerid, COLOR_GRAD2, "  You dont't have a cell phone !");
		return 1;
	}

	format(gString, sizeof(gString), "* %s takes out a cellphone.", PlayerInfo[playerid][pName]);
	ProxDetector(30.0, playerid, gString, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);

	if(phonenumb == 911) {
		SendClientMessage(playerid, COLOR_WHITE, "HINT: You now use T to talk on your cellphone, type /hangup to hang up");
		SendClientMessage(playerid, COLOR_ALLDEPT, "EMERGENCY: Which Service Do You Require, Police or Paramedic?");
		Mobile[playerid] = 911;
		return 1;
	}

	if(phonenumb == PlayerInfo[playerid][pPnumber]) {
		SendClientMessage(playerid, COLOR_GRAD2, "  You just get a busy tone...");
		return 1;
	}

	if(Mobile[playerid] != 255) {
		SendClientMessage(playerid, COLOR_GRAD2, "  You are already on a call...");
		return 1;
	}

	foreach(new i : Player) {
		if(PlayerInfo[i][pPnumber] == phonenumb && phonenumb != 0) {
			giveplayerid = i;
			Mobile[playerid] = giveplayerid; //caller connecting

			if(IsPlayerConnected(giveplayerid)) {
				if(PhoneOnline[giveplayerid] > 0) {
					SendClientMessage(playerid, COLOR_GREY, "   That players Phone is Offline !");
					return 1;
				}

				if(Mobile[giveplayerid] == 255) {
					format(gString, sizeof(gString), "Your Mobile is Ringing Type (/Pickup) CallerID: %s", PlayerInfo[playerid][pName]);
					SendClientMessage(giveplayerid, COLOR_YELLOW, gString);
					RingTone[giveplayerid] = 10;
					format(gString, sizeof(gString), "* %s's phone begins to ring.", PlayerInfo[playerid][pName]);
					SendClientMessage(playerid, COLOR_WHITE, "HINT: You now use T to talk on your cellphone, type /hangup to hang up");
					ProxDetector(30.0, i, gString, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
					CellTime[playerid] = 1;
					return 1;
				}
			}
		}
	}

	SendClientMessage(playerid, COLOR_GRAD2, "  You just get a Busy tone...");
	return 1;
}

CMD:txt(playerid, params[]) {
	if(gPlayerLogged[playerid] == 0) {
		SendClientMessage(playerid, COLOR_GREY, "   You havent logged in yet !");
		return 1;
	}

	new phonenumb, result[64], giveplayerid;

	if(sscanf(params, "is[64]", phonenumb, result)) {
		SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: (/t)ext [phonenumber] [text chat]");
		return 1;
	}

	if(PlayerInfo[playerid][pPnumber] == 0) {
		SendClientMessage(playerid, COLOR_GRAD2, "  You dont't have a cell phone...");
		return 1;
	}

	format(gString, sizeof(gString), "* %s takes out a cellphone.", PlayerInfo[playerid][pName]);
	ProxDetector(30.0, playerid, gString, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);

	if(phonenumb == 555) {
		if((strcmp("yes", result, true, strlen(result)) == 0) && (strlen(result) == strlen("yes"))) {
			SendClientMessage(playerid, COLOR_WHITE, "Text Message Delivered.");

			if(gTeam[playerid] == 2 || gTeam[playerid] == 1) {
				SendClientMessage(playerid, COLOR_YELLOW, "SMS: I have no idea what you're talking about, Sender: MOLE (555)");
				RingTone[playerid] = 20;
				return 1;
			}
			return 1;
		} else {
			SendClientMessage(playerid, COLOR_YELLOW, "SMS: A simple Yes will do, Sender: MOLE (555)");
			RingTone[playerid] = 20;
			return 1;
		}
	}

	foreach(new i : Player) {
		if(PlayerInfo[i][pPnumber] == phonenumb && phonenumb != 0) {
			giveplayerid = i;
			Mobile[playerid] = giveplayerid; //caller connecting

			if(IsPlayerConnected(giveplayerid)) {
				if(PhoneOnline[giveplayerid] > 0) {
					SendClientMessage(playerid, COLOR_GREY, "   That players Phone is Offline !");
					return 1;
				}

				format(gString, sizeof(gString), "SMS: %s, Sender: %s (%d)", result,PlayerInfo[playerid][pName],PlayerInfo[playerid][pPnumber]);
				RingTone[giveplayerid] =20;
				SendClientMessage(playerid, COLOR_WHITE, "Text Message Delivered");
				SendClientMessage(giveplayerid, COLOR_YELLOW, gString);
				SendClientMessage(playerid,  COLOR_YELLOW, gString);
				format(gString, sizeof(gString), "~r~$-%d", txtcost);
				GameTextForPlayer(playerid, gString, 5000, 1);
				GivePlayerMoney(playerid,-txtcost);
				SBizzInfo[2][sbTill] += txtcost;
				ExtortionSBiz(2, txtcost);
				PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
				Mobile[playerid] = 255;
				return 1;
			}
		}
	}

	SendClientMessage(playerid, COLOR_GRAD2, "  Message Delivery Failed...");
	return 1;
}

alias:txt("t", "sms")

CMD:pickup(playerid, params[]) {
	if(Mobile[playerid] != 255) {
		SendClientMessage(playerid, COLOR_GRAD2, "  You are already on a call...");
		return 1;
	}

	foreach(new i : Player) {
		if(Mobile[i] == playerid) {
			Mobile[playerid] = i; //caller connecting
			SendClientMessage(i,  COLOR_GRAD2, "   They Picked up the call.");
			format(gString, sizeof(gString), "* %s answers his cellphone.", PlayerInfo[playerid][pName]);
			ProxDetector(30.0, playerid, gString, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
			RingTone[playerid] = 0;
		}
	}
	return 1;
}

alias:pickup("p")

CMD:hangup(playerid, params[]) {
	new caller = Mobile[playerid];

	if(IsPlayerConnected(caller)) {
		if(caller != 255) {
			if(caller < 255) {
				SendClientMessage(caller,  COLOR_GRAD2, "   They hung up.");
				CellTime[caller] = 0;
				CellTime[playerid] = 0;
				SendClientMessage(playerid,  COLOR_GRAD2, "   You hung up.");
				Mobile[caller] = 255;
			}

			Mobile[playerid] = 255;
			CellTime[playerid] = 0;
			RingTone[playerid] = 0;
			return 1;
		}
	}

	SendClientMessage(playerid,  COLOR_GRAD2, "   Your phone is in your pocket.");
	return 1;
}

alias:hangup("h")

CMD:fixr(playerid, params[]) {
	PlayerFixRadio(playerid);
	return 1;
}

CMD:time(playerid, params[]) {
	new mtext[20];
	new year, month,day;

	getdate(year, month, day);

	if(month == 1) { mtext = "January"; }
	else if(month == 2) { mtext = "February"; }
	else if(month == 3) { mtext = "March"; }
	else if(month == 4) { mtext = "April"; }
	else if(month == 5) { mtext = "May"; }
	else if(month == 6) { mtext = "June"; }
	else if(month == 7) { mtext = "Juli"; }
	else if(month == 8) { mtext = "August"; }
	else if(month == 9) { mtext = "September"; }
	else if(month == 10) { mtext = "October"; }
	else if(month == 11) { mtext = "November"; }
	else if(month == 12) { mtext = "December"; }

	new hour,minuite,second;
	gettime(hour,minuite,second);
	FixHour(hour);
	hour = shifthour;

	if(minuite < 10) {
		if(PlayerInfo[playerid][pJailTime] > 0)	{
			format(gString, sizeof(gString), "~y~%d %s~n~~g~|~w~%d:0%d~g~|~n~~w~Jail Time Left: %d sec", day, mtext, hour, minuite, PlayerInfo[playerid][pJailTime]-10);
		} else {
			format(gString, sizeof(gString), "~y~%d %s~n~~g~|~w~%d:0%d~g~|", day, mtext, hour, minuite);
		}
	} else {
		if(PlayerInfo[playerid][pJailTime] > 0) {
			format(gString, sizeof(gString), "~y~%d %s~n~~g~|~w~%d:%d~g~|~n~~w~Jail Time Left: %d sec", day, mtext, hour, minuite, PlayerInfo[playerid][pJailTime]-10);
		} else {
			format(gString, sizeof(gString), "~y~%d %s~n~~g~|~w~%d:%d~g~|", day, mtext, hour, minuite);
		}
	}

	GameTextForPlayer(playerid, gString, 5000, 1);
	return 1;
}

CMD:house(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] >= 1337) {
		new housenum;

		if(sscanf(params, "i", housenum)) {
			SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /house [housenumber]");
			return 1;
		}

		SetPlayerInterior(playerid,HouseInfo[housenum][hInt]);
		SetPlayerPos(playerid,HouseInfo[housenum][hExitx],HouseInfo[housenum][hExity],HouseInfo[housenum][hExitz]);
		GameTextForPlayer(playerid, "~w~Teleporting", 5000, 1);
		PlayerInfo[playerid][pInt] = HouseInfo[housenum][hInt];
		PlayerInfo[playerid][pLocal] = housenum;
	}
	return 1;
}

CMD:houseo(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] >= 1337) {
		new housenum;

		if(sscanf(params, "i", housenum)) {
			SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /houseo [housenumber]");
			return 1;
		}

		SetPlayerPos(playerid,HouseInfo[housenum][hEntrancex],HouseInfo[housenum][hEntrancey],HouseInfo[housenum][hEntrancez]);
		GameTextForPlayer(playerid, "~w~Teleporting", 5000, 1);
	}
	return 1;
}

CMD:biz(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] >= 1337) {
		new housenum;

		if(sscanf(params, "i", housenum)) {
			SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /biz [biznumber]");
			return 1;
		}

		SetPlayerInterior(playerid,BizzInfo[housenum][bInterior]);
		SetPlayerPos(playerid,BizzInfo[housenum][bExitX],BizzInfo[housenum][bExitY],BizzInfo[housenum][bExitZ]);
		GameTextForPlayer(playerid, "~w~Teleporting", 5000, 1);
		PlayerInfo[playerid][pInt] = BizzInfo[housenum][bInterior];
		PlayerInfo[playerid][pLocal] = housenum+99;
	}
	return 1;
}

CMD:sbiz(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] >= 1337) {
		new housenum;

		if(sscanf(params, "i", housenum)) {
			SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /sbiz [biznumber]");
			return 1;
		}

		SetPlayerInterior(playerid,SBizzInfo[housenum][sbInterior]);
		SetPlayerPos(playerid,SBizzInfo[housenum][sbEntranceX],SBizzInfo[housenum][sbEntranceY],SBizzInfo[housenum][sbEntranceZ]);
		GameTextForPlayer(playerid, "~w~Teleporting", 5000, 1);
	}
	return 1;
}

CMD:resethousecars(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] < 1337) {
		SendClientMessage(playerid, COLOR_GRAD2, "   You are not an Admin !");
		return 1;
	}

	for(new i = 0; i < 34; i++) {
		HouseInfo[i][hVec] = 499;
	}

	OnPropUpdate();
	SendClientMessage(playerid, COLOR_GREY, "   All House Cars resetted !");
	return 1;
}

CMD:edithousecar(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] < 4) {
		SendClientMessage(playerid, COLOR_GRAD2, "   You are not an Admin !");
		return 1;
	}

	new proplev;

	if(sscanf(params, "i", proplev)) {
		SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /edithousecar [vecid]");
		return 1;
	}

	for(new i = 0; i < sizeof(HouseInfo); i++) {
		if(PlayerToPoint(3, playerid,HouseInfo[i][hEntrancex], HouseInfo[i][hEntrancey], HouseInfo[i][hEntrancez])) {
			HouseInfo[i][hVec] = proplev;
			format(gString, sizeof(gString), "House Car: %d is now %d", i,HouseInfo[i][hVec]);
			SendClientMessage(playerid, COLOR_GRAD2, gString);
		}
	}

	OnPropUpdate();
	return 1;
}

CMD:edit(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] < 4) {
		SendClientMessage(playerid, COLOR_GRAD2, "   You are not an Admin !");
		return 1;
	}

	new x_job[256], proplev;

	if(sscanf(params, "s[256]i", x_job, proplev)) {
		SendClientMessage(playerid, COLOR_WHITE, "|__________________ Edit __________________|");
		SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /edit [name] [ammount] (Used for Houses and Businesses)");
		SendClientMessage(playerid, COLOR_GREY, "Available names: Level, Price, Funds, Products");
		SendClientMessage(playerid, COLOR_WHITE, "|____________________________________________|");
		return 1;
	}

	for(new i = 0; i < sizeof(HouseInfo); i++) {
		if(PlayerToPoint(3, playerid,HouseInfo[i][hEntrancex], HouseInfo[i][hEntrancey], HouseInfo[i][hEntrancez])) {
			format(gString, sizeof(gString), "House: %d", i);
			SendClientMessage(playerid, COLOR_GRAD2, gString);

			if(proplev > 0) {
				if(strcmp(x_job,"level",true) == 0) {
					HouseInfo[i][hLevel] = proplev;
				} else if(strcmp(x_job,"price",true) == 0) {
					HouseInfo[i][hValue] = proplev;
				}
			}
		}
	}

	for(new i = 0; i < sizeof(BizzInfo); i++) {
		if(PlayerToPoint(3, playerid,BizzInfo[i][bEntranceX], BizzInfo[i][bEntranceY], BizzInfo[i][bEntranceZ])) {
			format(gString, sizeof(gString), "Biz: %d", i);
			SendClientMessage(playerid, COLOR_GRAD2, gString);

			if(proplev > 0) {
				if(strcmp(x_job,"level",true) == 0) {
					BizzInfo[i][bLevelNeeded] = proplev;
				} else if(strcmp(x_job,"price",true) == 0) {
					BizzInfo[i][bBuyPrice] = proplev;
				} else if(strcmp(x_job,"funds",true) == 0) {
					BizzInfo[i][bTill] = proplev;
				} else if(strcmp(x_job,"products",true) == 0) {
					BizzInfo[i][bProducts] = proplev;
				}
			}
		}
	}

	for(new i = 0; i < sizeof(SBizzInfo); i++) {
		if(PlayerToPoint(3, playerid,SBizzInfo[i][sbEntranceX], SBizzInfo[i][sbEntranceY], SBizzInfo[i][sbEntranceZ])) {
			format(gString, sizeof(gString), "SBiz: %d", i);
			SendClientMessage(playerid, COLOR_GRAD2, gString);

			if(proplev > 0) {
				if(strcmp(x_job,"level",true) == 0) {
					SBizzInfo[i][sbLevelNeeded] = proplev;
				} else if(strcmp(x_job,"price",true) == 0) {
					SBizzInfo[i][sbBuyPrice] = proplev;
				} else if(strcmp(x_job,"funds",true) == 0) {
					SBizzInfo[i][sbTill] = proplev;
				} else if(strcmp(x_job,"products",true) == 0) {
					SBizzInfo[i][sbProducts] = proplev;
				}
			}
		}
	}

	format(gString, sizeof(gString), "You've adjusted the: %s.", x_job);
	SendClientMessage(playerid, COLOR_WHITE, gString);
	OnPropUpdate();
	return 1;
}

CMD:load(playerid, params[]) {
	new tmpcar = GetPlayerVehicleID(playerid);

	if(tmpcar < 78 || tmpcar > 81) {
		GameTextForPlayer(playerid, "~r~You are not in a delivery truck", 5000, 1);
		return 1;
	}

	format(gString, sizeof(gString), "Products: %d/%d.", PlayerHaul[tmpcar][pLoad],PlayerHaul[tmpcar][pCapasity]);
	SendClientMessage(playerid, TEAM_GROVE_COLOR, gString);
	return 1;
}

CMD:buyprods(playerid, params[]) {
	new tmpcar = GetPlayerVehicleID(playerid);
	new compcost = 50;

	if(PlayerToPoint(60.0, playerid, 2787.8,-2436.3,13.7)) {
		if(IsATruck(tmpcar)) {
			if(PlayerHaul[tmpcar][pLoad] < PlayerHaul[tmpcar][pCapasity]) {
				new amount;

				if(sscanf(params, "i", amount)) {
					SendClientMessage(playerid, COLOR_GRAD1, "Uzycie: /buyprods [amount]");
					return 1;
				}

				if(amount < 1 || amount > 500) { SendClientMessage(playerid, COLOR_GREY, "   Can't buy less then 1 Product or more then 500 !"); return 1; }
				new check= PlayerHaul[tmpcar][pLoad] + amount;

				if(check > PlayerHaul[tmpcar][pCapasity]) {
					format(gString, sizeof(gString), "   You went over the Truck Products Carry Limit of %d, you currently carry %d.",PlayerHaul[tmpcar][pCapasity],PlayerHaul[tmpcar][pLoad]);
					SendClientMessage(playerid, COLOR_GREY, gString);
					return 1;
				}

				new cost = amount*compcost;

				if(GetPlayerMoney(playerid) >= cost) {
					PlayerHaul[tmpcar][pLoad] += amount;
					format(gString, sizeof(gString), "Products: %d/%d.", PlayerHaul[tmpcar][pLoad],PlayerHaul[tmpcar][pCapasity]);
					SendClientMessage(playerid, TEAM_GROVE_COLOR, gString);
					format(gString, sizeof(gString), "You bought %d Products for $%d.", amount,cost);
					SendClientMessage(playerid, TEAM_GROVE_COLOR, gString);
					GivePlayerMoney(playerid,-cost);
					PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
				} else {
					format(gString, sizeof(gString), "You cant afford %d Products at $%d !", amount,cost);
					SendClientMessage(playerid, TEAM_GROVE_COLOR, gString);
				}
			} else {
				format(gString, sizeof(gString), "Products: %d/%d.", PlayerHaul[tmpcar][pLoad],PlayerHaul[tmpcar][pCapasity]);
				SendClientMessage(playerid, TEAM_GROVE_COLOR, gString);
			}
		} else {
			SendClientMessage(playerid, TEAM_GROVE_COLOR, "This Vehicle does not deliver Products.");
		}
	}
	return 1;
}

CMD:sellprods(playerid, params[]) {
	new cashmade;
	new tmpcar;

	if(IsPlayerConnected(playerid)) {
		tmpcar = GetPlayerVehicleID(playerid);

		if(!IsATruck(tmpcar)) {
			GameTextForPlayer(playerid, "~r~You are not in a delivery truck", 5000, 1);
			return 1;
		}

		if(PlayerHaul[tmpcar][pLoad] == 0) {
			GameTextForPlayer(playerid, "~r~Truck is empty, return to the stock house", 5000, 1);
			format(gString, sizeof(gString), "Products: %d/%d.", PlayerHaul[tmpcar][pLoad],PlayerHaul[tmpcar][pCapasity]);
			SendClientMessage(playerid, TEAM_GROVE_COLOR, gString);
			return 1;
		}

		for(new i = 0; i < sizeof(BizzInfo); i++) {
			if(PlayerToPoint(10, playerid,BizzInfo[i][bEntranceX], BizzInfo[i][bEntranceY], BizzInfo[i][bEntranceZ])) {
				//printf("Found House :%d",i);
				for(new l = PlayerHaul[tmpcar][pLoad]; l > 0; l--) {
					if(BizzInfo[i][bProducts] == BizzInfo[i][bMaxProducts]) {
						GameTextForPlayer(playerid, "~r~Our stores are full", 5000, 1);
						format(gString, sizeof(gString), "Cash Earned $%d.", cashmade);
						SendClientMessage(playerid, TEAM_GROVE_COLOR, gString);
						format(gString, sizeof(gString), "Products: %d/%d.", PlayerHaul[tmpcar][pLoad],PlayerHaul[tmpcar][pCapasity]);
						SendClientMessage(playerid, TEAM_GROVE_COLOR, gString);
						PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
						return 1;
					}

					if(BizzInfo[i][bPriceProd] > BizzInfo[i][bTill]) {
						GameTextForPlayer(playerid, "~r~We Cant Afford The Deal", 5000, 1);
						format(gString, sizeof(gString), "Cash Earned $%d.", cashmade);
						SendClientMessage(playerid, TEAM_GROVE_COLOR, gString);
						format(gString, sizeof(gString), "Products: %d/%d.", PlayerHaul[tmpcar][pLoad],PlayerHaul[tmpcar][pCapasity]);
						SendClientMessage(playerid, TEAM_GROVE_COLOR, gString);
						PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
						return 1;
					}

					PlayerHaul[tmpcar][pLoad]--;
					BizzInfo[i][bProducts]++;
					cashmade = cashmade+BizzInfo[i][bPriceProd];
					ConsumingMoney[playerid] = 1;
					GivePlayerMoney(playerid,BizzInfo[i][bPriceProd]);
					BizzInfo[i][bTill] -= BizzInfo[i][bPriceProd];

					if(PlayerHaul[tmpcar][pLoad] == 0) {
						GameTextForPlayer(playerid, "~r~Truck is empty, return to the stock house", 5000, 1);
						format(gString, sizeof(gString), "Cash Earned $%d.", cashmade);
						SendClientMessage(playerid, TEAM_GROVE_COLOR, gString);
						format(gString, sizeof(gString), "Products: %d/%d.", PlayerHaul[tmpcar][pLoad],PlayerHaul[tmpcar][pCapasity]);
						SendClientMessage(playerid, TEAM_GROVE_COLOR, gString);
						PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
						return 1;
					}
				}

				OnPropUpdate();
				return 1;
			}
		}
	}

	for(new i = 0; i < sizeof(SBizzInfo); i++) {
		if(PlayerToPoint(10, playerid,SBizzInfo[i][sbEntranceX], SBizzInfo[i][sbEntranceY], SBizzInfo[i][sbEntranceZ])) {
			//printf("Found House :%d",i);
			for(new l = PlayerHaul[tmpcar][pLoad]; l > 0; l--) {
				if(SBizzInfo[i][sbProducts] == SBizzInfo[i][sbMaxProducts]) {
					GameTextForPlayer(playerid, "~r~Our stores are full", 5000, 1);
					format(gString, sizeof(gString), "Cash Earned $%d.", cashmade);
					SendClientMessage(playerid, TEAM_GROVE_COLOR, gString);
					format(gString, sizeof(gString), "Products: %d/%d.", PlayerHaul[tmpcar][pLoad],PlayerHaul[tmpcar][pCapasity]);
					SendClientMessage(playerid, TEAM_GROVE_COLOR, gString);
					return 1;
				}

				if(SBizzInfo[i][sbPriceProd] > SBizzInfo[i][sbTill]) {
					GameTextForPlayer(playerid, "~r~We Cant Afford The Deal", 5000, 1);
					format(gString, sizeof(gString), "Cash Earned $%d.", cashmade);
					SendClientMessage(playerid, TEAM_GROVE_COLOR, gString);
					format(gString, sizeof(gString), "Products: %d/%d.", PlayerHaul[tmpcar][pLoad],PlayerHaul[tmpcar][pCapasity]);
					SendClientMessage(playerid, TEAM_GROVE_COLOR, gString);
					return 1;
				}

				PlayerHaul[tmpcar][pLoad]--;
				SBizzInfo[i][sbProducts]++;
				cashmade = cashmade+SBizzInfo[i][sbPriceProd];
				ConsumingMoney[playerid] = 1;
				GivePlayerMoney(playerid,SBizzInfo[i][sbPriceProd]);
				SBizzInfo[i][sbTill] -= SBizzInfo[i][sbPriceProd];

				if(PlayerHaul[tmpcar][pLoad] == 0) {
					GameTextForPlayer(playerid, "~r~Truck is empty, return to the stock house", 5000, 1);
					format(gString, sizeof(gString), "Cash Earned $%d.", cashmade);
					SendClientMessage(playerid, TEAM_GROVE_COLOR, gString);
					format(gString, sizeof(gString), "Products: %d/%d.", PlayerHaul[tmpcar][pLoad],PlayerHaul[tmpcar][pCapasity]);
					SendClientMessage(playerid, TEAM_GROVE_COLOR, gString);
					return 1;
				}
			}

			OnPropUpdate();
			return 1;
		}
	}

	GameTextForPlayer(playerid, "~r~To Far From A Business", 5000, 1);
	return 1;
}

CMD:enter(playerid, params[]) {
	for(new i = 0; i < sizeof(HouseInfo); i++) {
		if(PlayerToPoint(3, playerid,HouseInfo[i][hEntrancex], HouseInfo[i][hEntrancey], HouseInfo[i][hEntrancez])) {
			//printf("Found House :%d",i);
			if(PlayerInfo[playerid][pPhousekey] == i || HouseInfo[i][hLock] == 0) {
				SetPlayerInterior(playerid,HouseInfo[i][hInt]);
				SetPlayerPos(playerid,HouseInfo[i][hExitx],HouseInfo[i][hExity],HouseInfo[i][hExitz]);
				GameTextForPlayer(playerid, "~w~Welcome Home", 5000, 1);
				PlayerInfo[playerid][pInt] = HouseInfo[i][hInt];
				PlayerInfo[playerid][pLocal] = i;
			} else {
				GameTextForPlayer(playerid, "~r~Locked", 5000, 1);
			}
		}
	}

	for(new i = 0; i < sizeof(BizzInfo); i++) {
		if(PlayerToPoint(3, playerid,BizzInfo[i][bEntranceX], BizzInfo[i][bEntranceY], BizzInfo[i][bEntranceZ])) {
			//printf("Found House :%d",i);
			if(!IsACop(playerid) && i == 3) {
				SendClientMessage(playerid, COLOR_GREY, "   Cops only !");
				return 1;
			}

			if(PlayerInfo[playerid][pPbiskey] == i || GetPlayerMoney(playerid) >= BizzInfo[i][bEntranceCost]) {
				if(PlayerInfo[playerid][pPbiskey] != i) {
					if(BizzInfo[i][bLocked] == 1) {
						GameTextForPlayer(playerid, "~r~Closed", 5000, 1);
						return 1;
					}

					if(BizzInfo[i][bProducts] == 0) {
						GameTextForPlayer(playerid, "~r~Out Of Stock", 5000, 1);
						return 1;
					}

					GivePlayerMoney(playerid,-BizzInfo[i][bEntranceCost]);
					format(gString, sizeof(gString), "~r~-$%d~n~~w~type /exit~n~to get out", BizzInfo[i][bEntranceCost]);
					BizzInfo[i][bTill] += BizzInfo[i][bEntranceCost];
					ExtortionBiz(i, BizzInfo[i][bEntranceCost]);
					BizzInfo[i][bProducts]--;
					OnPropUpdate();
					GameTextForPlayer(playerid, gString, 5000, 3);
				}

				SetPlayerInterior(playerid,BizzInfo[i][bInterior]);
				SetPlayerPos(playerid,BizzInfo[i][bExitX],BizzInfo[i][bExitY],BizzInfo[i][bExitZ]);
				PlayerInfo[playerid][pInt] = BizzInfo[i][bInterior];
				PlayerInfo[playerid][pLocal] = i+99;
				format(gString, sizeof(gString), "%s payed $%d to enter biz %d", PlayerInfo[playerid][pName], BizzInfo[i][bEntranceCost], i);
				printf("%s", gString);
				PayLog(gString);
				//PlayerInfo[playerid][pLocal] = i;
			} else {
				GameTextForPlayer(playerid, "~r~You dont have the cash", 5000, 1);
			}
		}
	}

	for(new i = 0; i < sizeof(SBizzInfo); i++)
	{
		if(PlayerToPoint(3, playerid,SBizzInfo[i][sbEntranceX], SBizzInfo[i][sbEntranceY], SBizzInfo[i][sbEntranceZ])) {
			if(PlayerInfo[playerid][pPbiskey] == i || GetPlayerMoney(playerid) >= SBizzInfo[i][sbEntranceCost]) {
				if(PlayerInfo[playerid][pPbiskey] != i) {
					if(SBizzInfo[i][sbLocked] == 1) {
						GameTextForPlayer(playerid, "~r~Closed", 5000, 1);
						return 1;
					}

					if(SBizzInfo[i][sbProducts] == 0) {
						GameTextForPlayer(playerid, "~r~Out Of Stock", 5000, 1);
						return 1;
					}

					if(i == 10) {
						PaintballPlayers ++;
						PlayerPaintballing[playerid] = 1;
						new rand = random(sizeof(PaintballSpawns));
						SetPlayerPos(playerid, PaintballSpawns[rand][0], PaintballSpawns[rand][1], PaintballSpawns[rand][2]);
						TogglePlayerControllable(playerid, 0);
					} else if(i == 11) {
						PlayerKarting[playerid] = 1;
						SendClientMessage(playerid, TEAM_GROVE_COLOR, "You can now parcipitate in a Karting Race, grab a Kart.");
					} else {
						return 1;
					}

					GivePlayerMoney(playerid,-SBizzInfo[i][sbEntranceCost]);
					gSpentCash[playerid] = GetPlayerMoney(playerid);
					SBizzInfo[i][sbProducts]--;
					SBizzInfo[i][sbTill] += SBizzInfo[i][sbEntranceCost];
					ExtortionSBiz(i, SBizzInfo[i][sbEntranceCost]);
					format(gString, sizeof(gString), "%s payed $%d to enter sbiz %d", PlayerInfo[playerid][pName], SBizzInfo[i][sbEntranceCost], i);
					printf("%s", gString);
					PayLog(gString);
					OnPropUpdate();
				}
			} else {
				GameTextForPlayer(playerid, "~r~You dont have the cash", 5000, 1);
			}
		}
	}

	if(PlayerToPoint(3.0, playerid,-2162.2554,-2385.9541,30.6250)) {
		SetPlayerInterior(playerid,3);
		SetPlayerPos(playerid,387.7978,173.8582,1008.3828);
		GameTextForPlayer(playerid, "~w~Welcome to the City Hall", 5000, 1);
		PlayerInfo[playerid][pInt] = 3;
		PlayerInfo[playerid][pLocal] = 241;
	} else if(PlayerToPoint(3.0, playerid,1073.0619,-344.5148,73.9922)) {
		if(PlayerInfo[playerid][pMember] == 8 || PlayerInfo[playerid][pLeader] == 8) {
			SetPlayerInterior(playerid,2);
			SetPlayerPos(playerid,1205.0947,-10.1685,1000.9219);
			PlayerInfo[playerid][pInt] = 2;
			PlayerInfo[playerid][pLocal] = 242;
		}
	} else if(PlayerToPoint(3.0, playerid,2695.6235,-1704.6960,11.8438)) {
		GameTextForPlayer(playerid, "~w~Welcome to the 8ball Track", 5000, 1);
		SetPlayerInterior(playerid,7);
		SetPlayerPos(playerid,-1404.5299,-259.0602,1043.6563);
	} else if(PlayerToPoint(8.0, playerid,-2111.5686,-443.9720,38.7344)) {
		GameTextForPlayer(playerid, "~w~Welcome to the Dirt Track", 5000, 1);
		SetPlayerInterior(playerid,4);
		SetPlayerPos(playerid,-1443.0554,-581.1879,1055.0472);
	} else if(PlayerToPoint(8.0, playerid,-2080.3079,-406.0309,38.7344)) {
		GameTextForPlayer(playerid, "~w~Welcome to the Stunting Track", 5000, 1);
		SetPlayerInterior(playerid,14);
		SetPlayerPos(playerid,-1464.7732,1557.5533,1052.5313);
	}
	return 1;
}

CMD:exit(playerid, params[]) {
	for(new i = 0; i <  sizeof(HouseInfo); i++) {
		//printf("House :%d",i);
		if(PlayerToPoint(3, playerid,HouseInfo[i][hExitx], HouseInfo[i][hExity], HouseInfo[i][hExitz])) {
			SetPlayerInterior(playerid,0);
			SetPlayerPos(playerid,HouseInfo[i][hEntrancex],HouseInfo[i][hEntrancey],HouseInfo[i][hEntrancez]);
			PlayerInfo[playerid][pInt] = 0;
			PlayerInfo[playerid][pLocal] = 255;

			if(HouseInfo[i][hHel] == 1) {
				new Float:tempheal;
				GetPlayerHealth(playerid,tempheal);

				if(tempheal < 100.0) {
					SetPlayerHealth(playerid,100.0);
				}
			}
		}
	}

	for(new i = 0; i <  sizeof(BizzInfo); i++) {
		//printf("Bizz :%d",i);
		if(PlayerToPoint(3, playerid,BizzInfo[i][bExitX], BizzInfo[i][bExitY], BizzInfo[i][bExitZ])) {
			SetPlayerInterior(playerid,0);
			PlayerInfo[playerid][pInt] = 0;
			SetPlayerPos(playerid,BizzInfo[i][bEntranceX],BizzInfo[i][bEntranceY],BizzInfo[i][bEntranceZ]);
			PlayerInfo[playerid][pLocal] = 255;
		}
	}

	if(GetPlayerVehicleID(playerid) >= 71 && GetPlayerVehicleID(playerid) <= 77) {
		TogglePlayerControllable(playerid, 1);
		RemovePlayerFromVehicle(playerid);
	} else if(PlayerToPoint(3.0, playerid,387.7978,173.8582,1008.3828)) {
		SetPlayerInterior(playerid,0);
		SetPlayerPos(playerid,-2162.2554,-2385.9541,30.6250);
		PlayerInfo[playerid][pInt] = 0;
		PlayerInfo[playerid][pLocal] = 255;
	} else if(PlayerToPoint(6.0, playerid,-1404.5299,-259.0602,1043.6563)) {
		SetPlayerInterior(playerid,0);
		SetPlayerPos(playerid,2695.6235,-1704.6960,11.8438);
	} else if(PlayerToPoint(8.0, playerid,-1443.0554,-581.1879,1055.0472)) {
		SetPlayerInterior(playerid,0);
		SetPlayerPos(playerid,-2111.5686,-443.9720,38.7344);
	} else if(PlayerToPoint(8.0, playerid,-1464.7732,1557.5533,1052.5313)) {
		SetPlayerInterior(playerid,0);
		SetPlayerPos(playerid,-2080.3079,-406.0309,38.7344);
	} else if(NoFuel[playerid] == 1) {
		TogglePlayerControllable(playerid, 1);
		RemovePlayerFromVehicle(playerid);
		NoFuel[playerid] = 0;
	}
	return 1;
}

CMD:home(playerid, params[]) {
	if(PlayerInfo[playerid][pPhousekey] != 255) {
		if(PlayerOnMission[playerid] > 0) {
			SendClientMessage(playerid, COLOR_GREY, "   On a mission right now, can't use this command !");
			return 1;
		}

		SetPlayerCheckpoint(playerid,HouseInfo[PlayerInfo[playerid][pPhousekey]][hEntrancex], HouseInfo[PlayerInfo[playerid][pPhousekey]][hEntrancey], HouseInfo[PlayerInfo[playerid][pPhousekey]][hEntrancez], 4.0);
		GameTextForPlayer(playerid, "~w~Waypoint set ~r~Home", 5000, 1);
		gPlayerCheckpointStatus[playerid] = CHECKPOINT_HOME;
	} else {
		GameTextForPlayer(playerid, "~w~You are homeless", 5000, 1);
	}
	return 1;
}

CMD:towcar(playerid, params[]) {
	new house = PlayerInfo[playerid][pPhousekey];

	if(house != 255 && strcmp(PlayerInfo[playerid][pName], HouseInfo[PlayerInfo[playerid][pPhousekey]][hOwner], true) == 0) {
		if(SBizzInfo[8][sbProducts] == 0) {
			GameTextForPlayer(playerid, "~r~Out Of Stock", 5000, 1);
			return 1;
		}

		if(CarTow(house+1)) {
			GameTextForPlayer(playerid, "~w~Car~n~~g~Towed Home~n~~r~$-1000", 5000, 1);
			GivePlayerMoney(playerid,-1000);
			PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
			SBizzInfo[8][sbTill] += 1000;//towcar buisness
			ExtortionSBiz(8, 1000);
			SBizzInfo[8][sbProducts]--;
		} else {
			GameTextForPlayer(playerid, "~w~Car is~n~in ~r~use", 5000, 1);
		}
	} else {
		GameTextForPlayer(playerid, "~w~You are not a home owner", 5000, 1);
	}
	return 1;
}

CMD:fixcar(playerid, params[]) {
	new house = PlayerInfo[playerid][pPhousekey];

	if(house != 255 && strcmp(PlayerInfo[playerid][pName], HouseInfo[PlayerInfo[playerid][pPhousekey]][hOwner], true) == 0) {
		if(SBizzInfo[8][sbProducts] == 0) {
			GameTextForPlayer(playerid, "~r~Out Of Stock", 5000, 1);
			return 1;
		}

		if(CarRespawn(house+1)) {
			GameTextForPlayer(playerid, "~w~Car~n~~g~Repaired~n~~r~$-1000", 5000, 1);
			GivePlayerMoney(playerid,-1000);
			PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
			SBizzInfo[8][sbTill] += 1000;//towcar buisness
			ExtortionSBiz(8, 1000);
			SBizzInfo[8][sbProducts]--;
		} else {
			GameTextForPlayer(playerid, "~w~Car is~n~in ~r~use", 5000, 1);
		}
	} else {
		GameTextForPlayer(playerid, "~w~You are not a home owner", 5000, 1);
	}
	return 1;
}

CMD:buybiz(playerid, params[]) {
	new Float:oldposx, Float:oldposy, Float:oldposz;

	GetPlayerPos(playerid, oldposx, oldposy, oldposz);

	if(PlayerInfo[playerid][pPbiskey] != 255) {
		SendClientMessage(playerid, COLOR_WHITE, "   You already own a business, type /sellbiz if you want to buy this one.");
		return 1;
	}

	for(new b = 0; b < sizeof(SBizzInfo); b++) {
		if(PlayerToPoint(2.0, playerid, SBizzInfo[b][sbEntranceX], SBizzInfo[b][sbEntranceY], SBizzInfo[b][sbEntranceZ]) && SBizzInfo[b][sbOwned] == 0) {
			if(PlayerInfo[playerid][pLevel] < SBizzInfo[b][sbLevelNeeded]) {
				format(gString, sizeof(gString), "You Must Be Level %d To Purchase This",SBizzInfo[b][sbLevelNeeded]);
				SendClientMessage(playerid, COLOR_GRAD5, gString);
				return 1;
			}

			if(GetPlayerMoney(playerid) > SBizzInfo[b][sbBuyPrice]) {
				PlayerInfo[playerid][pPbiskey] = b+100;
				SBizzInfo[b][sbOwned] = 1;
				strmid(SBizzInfo[b][sbOwner], PlayerInfo[playerid][pName], 0, strlen(PlayerInfo[playerid][pName]), 255);
				GivePlayerMoney(playerid,-SBizzInfo[b][sbBuyPrice]);
				PlayerPlayMusic(playerid);
				SendClientMessage(playerid, COLOR_WHITE, "Congratulations, On Your New Purchase.");
				SendClientMessage(playerid, COLOR_WHITE, "Type /help to review the new business help section.");
				DateProp(playerid);
				OnPropUpdate();
				OnPlayerUpdate(playerid);
				return 1;
			} else {
				SendClientMessage(playerid, COLOR_WHITE, "You don't have the cash for that");
				return 1;
			}
		}
	}

	for(new b = 0; b < sizeof(BizzInfo); b++) {
		if(PlayerToPoint(2.0, playerid, BizzInfo[b][bEntranceX], BizzInfo[b][bEntranceY], BizzInfo[b][bEntranceZ]) && BizzInfo[b][bOwned] == 0) {
			if(PlayerInfo[playerid][pLevel] < BizzInfo[b][bLevelNeeded]) {
				format(gString, sizeof(gString), "You Must Be Level %d To Purchase This",BizzInfo[b][bLevelNeeded]);
				SendClientMessage(playerid, COLOR_GRAD5, gString);
				return 1;
			}

			if(GetPlayerMoney(playerid) > BizzInfo[b][bBuyPrice]) {
				PlayerInfo[playerid][pPbiskey] = b;
				BizzInfo[b][bOwned] = 1;
				strmid(BizzInfo[b][bOwner], PlayerInfo[playerid][pName], 0, strlen(PlayerInfo[playerid][pName]), 255);
				GivePlayerMoney(playerid,-BizzInfo[b][bBuyPrice]);
				PlayerPlayMusic(playerid);
				SetPlayerInterior(playerid,BizzInfo[b][bInterior]);
				PlayerInfo[playerid][pInt] = BizzInfo[b][bInterior];
				SetPlayerPos(playerid,BizzInfo[b][bExitX],BizzInfo[b][bExitY],BizzInfo[b][bExitZ]);
				GameTextForPlayer(playerid, "~w~Welcome~n~You can exit at any time by moving to this door and typing /exit", 5000, 3);
				PlayerInfo[playerid][pInt] = BizzInfo[b][bInterior];
				PlayerInfo[playerid][pLocal] = b ;
				SendClientMessage(playerid, COLOR_WHITE, "Congratulations, On Your New Purchase.");
				SendClientMessage(playerid, COLOR_WHITE, "Type /help to review the new business help section.");
				DateProp(playerid);
				OnPropUpdate();
				OnPlayerUpdate(playerid);
				return 1;
			} else {
				SendClientMessage(playerid, COLOR_WHITE, "You don't have the cash for that");
				return 1;
			}
		}
	}
	return 1;
}

CMD:sellbiz(playerid, params[]) {
	if(PlayerInfo[playerid][pPbiskey] == 255) {
		SendClientMessage(playerid, COLOR_WHITE, "You don't own a bizz.");
		return 1;
	}

	if(PlayerInfo[playerid][pMarried] > 0) {
		SendClientMessage(playerid, COLOR_GREY, "   You are Married, can't sell the House !");
		return 1;
	}

	if(PlayerInfo[playerid][pPbiskey] >= 100 && strcmp(PlayerInfo[playerid][pName], SBizzInfo[PlayerInfo[playerid][pPbiskey]-100][sbOwner], true) == 0) {
		new bouse = PlayerInfo[playerid][pPbiskey]-100;
		GivePlayerMoney(playerid,SBizzInfo[bouse][sbTill]);
		SBizzInfo[bouse][sbLocked] = 1;
		SBizzInfo[bouse][sbOwned] = 0;
		strmid(SBizzInfo[bouse][sbOwner], "The State", 0, strlen("The State"), 255);
		strmid(SBizzInfo[bouse][sbExtortion], "No-one", 0, strlen("No-one"), 255);
		ConsumingMoney[playerid] = 1;
		PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
		format(gString, sizeof(gString), "~w~Congratulations~n~ You have sold your property for ~n~~g~$%d", SBizzInfo[bouse][sbTill]);
		GameTextForPlayer(playerid, gString, 10000, 3);
		SBizzInfo[bouse][sbTill] = 0;
		PlayerInfo[playerid][pPbiskey] = 255;
		OnPropUpdate();
		OnPlayerUpdate(playerid);
		return 1;
	}

	if(strcmp(PlayerInfo[playerid][pName], BizzInfo[PlayerInfo[playerid][pPbiskey]][bOwner], true) == 0) {
		new bouse = PlayerInfo[playerid][pPbiskey];
		BizzInfo[bouse][bLocked] = 1;
		BizzInfo[bouse][bOwned] = 0;
		strmid(BizzInfo[bouse][bOwner], "The State", 0, strlen("The State"), 255);
		strmid(BizzInfo[bouse][bExtortion], "No-one", 0, strlen("No-one"), 255);
		ConsumingMoney[playerid] = 1;
		GivePlayerMoney(playerid,BizzInfo[bouse][bTill]);
		PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
		format(gString, sizeof(gString), "~w~Congratulations~n~ You have sold your property for ~n~~g~$%d", BizzInfo[bouse][bTill]);
		GameTextForPlayer(playerid, gString, 10000, 3);
		BizzInfo[bouse][bTill] = 0;
		PlayerInfo[playerid][pPbiskey] = 255;
		OnPropUpdate();
		OnPlayerUpdate(playerid);
	} else {
		SendClientMessage(playerid, COLOR_WHITE, "You don't own a business.");
	}
	return 1;
}

CMD:bizinfo(playerid, params[]) {
	new bouse = PlayerInfo[playerid][pPbiskey];

	if(bouse == 255) {
		SendClientMessage(playerid, COLOR_WHITE, "You don't own a business.");
		return 1;
	}

	if(bouse >= 100) {
		PrintSBizInfo(playerid,bouse-100);
	} else {
		PrintBizInfo(playerid,bouse);
	}
	return 1;
}

CMD:prodprice(playerid, params[]) {
	new bouse = PlayerInfo[playerid][pPbiskey];

	if(bouse == 255) {
		SendClientMessage(playerid, COLOR_GRAD2, "   You don't own a business");
		return 1;
	}

	new tmp;

	if(sscanf(params, "i", tmp)) {
		return SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /prodprice [amount to pay per Product]");
	}

	if(tmp < 1 || tmp > 99999) {
		SendClientMessage(playerid, COLOR_WHITE, "Minimum amount is $1, Maximum amount is $99999.");
		return 1;
	}

	if(bouse >= 100) {
		if(tmp > SBizzInfo[bouse-100][sbTill]) {
			SendClientMessage(playerid, COLOR_WHITE, "You dont have that much in your Till.");
			return 1;
		}

		SBizzInfo[bouse-100][sbPriceProd] = tmp;
		format(gString, sizeof(gString), "Buying Products for $%d.", SBizzInfo[bouse-100][sbPriceProd]);
	} else {
		if(tmp > BizzInfo[bouse][bTill]) {
			SendClientMessage(playerid, COLOR_WHITE, "You dont have that much in your Till.");
			return 1;
		}

		BizzInfo[bouse][bPriceProd] = tmp;
		format(gString, sizeof(gString), "Buying Products for $%d.", BizzInfo[bouse][bPriceProd]);
	}

	OnPropUpdate();
	SendClientMessage(playerid, COLOR_WHITE, gString);
	return 1;
}

CMD:bizfee(playerid, params[]) {
	new bouse = PlayerInfo[playerid][pPbiskey];

	if(bouse == 255) {
		SendClientMessage(playerid, COLOR_GRAD2, "   You don't own a business !");
		return 1;
	}

	new tmp;

	if(sscanf(params, "i", tmp)) {
		return SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /bizfee [EntranceFee]");
	}

	if(tmp < 0 || tmp > 99999) {
		SendClientMessage(playerid, COLOR_WHITE, "Minimum entrance is $0, Maximum entrance is $99999.");
		return 1;
	}

	if(bouse >= 100) {
		SBizzInfo[bouse-100][sbEntranceCost] = tmp;
		format(gString, sizeof(gString), "Entrance fee set to $%d.", SBizzInfo[bouse-100][sbEntranceCost]);
	} else {
		BizzInfo[bouse][bEntranceCost] = tmp;
		format(gString, sizeof(gString), "Entrance fee set to $%d.", BizzInfo[bouse][bEntranceCost]);
	}

	OnPropUpdate();
	SendClientMessage(playerid, COLOR_WHITE, gString);
	return 1;
}

CMD:extortion(playerid, params[]) {
	new bouse = PlayerInfo[playerid][pPbiskey];

	if(bouse == 255) {
		SendClientMessage(playerid, COLOR_GRAD2, "   You don't own a business");
		return 1;
	}

	new giveplayerid;

	if(sscanf(params, "i", giveplayerid)) {
		SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /extortion [playerid/PartOfName] (or 555 for No-one)");
		return 1;
	}

	if(IsPlayerConnected(giveplayerid)) {
		format(gString, sizeof(gString), "* %s is know Extortioning your Business.",PlayerInfo[giveplayerid][pName]);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
		format(gString, sizeof(gString), "* %s has adjusted his Business, you are now Extortioning his Business.",PlayerInfo[playerid][pName]);
		SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);

		if(bouse >= 100) {
			format(gString, sizeof(gString), "%s",PlayerInfo[giveplayerid][pName]);
			strmid(SBizzInfo[bouse-100][sbExtortion], gString, 0, sizeof(gString), 255);
			format(gString, sizeof(gString), "Business Extortion Name set to %s",SBizzInfo[bouse-100][sbExtortion]);
		} else {
			format(gString, sizeof(gString), "%s",PlayerInfo[giveplayerid][pName]);
			strmid(BizzInfo[bouse][bExtortion], gString, 0, sizeof(gString), 255);
			format(gString, sizeof(gString), "Business Extortion Name set to %s",BizzInfo[bouse][bExtortion]);
		}

		OnPropUpdate();
		SendClientMessage(playerid, COLOR_WHITE, gString);
	} else if(giveplayerid == 555) {
		if(bouse >= 100) {
			format(gString, sizeof(gString), "No-one");
			strmid(SBizzInfo[bouse-100][sbExtortion], gString, 0, sizeof(gString), 255);
			format(gString, sizeof(gString), "Business Extortion Name set to %s",SBizzInfo[bouse-100][sbExtortion]);
		} else {
			format(gString, sizeof(gString), "No-one");
			strmid(BizzInfo[bouse][bExtortion], gString, 0, sizeof(gString), 255);
			format(gString, sizeof(gString), "Business Extortion Name set to %s",BizzInfo[bouse][bExtortion]);
		}

		OnPropUpdate();
		SendClientMessage(playerid, COLOR_WHITE, gString);
	} else {
		SendClientMessage(playerid, COLOR_GREY, "   That player is Offline !");
	}
	return 1;
}

CMD:bizname(playerid, params[]) {
	new bouse = PlayerInfo[playerid][pPbiskey];

	if(bouse == 255) {
		SendClientMessage(playerid, COLOR_GRAD2, "   You don't own a business");
		return 1;
	}

	new result[64];

	if(sscanf(params, "s[64]", result)) {
		return SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /bizname [Name]");
	}

	if(bouse >= 100) {
		strmid(SBizzInfo[bouse-100][sbMessage], result, 0, 64, 255);
		format(gString, sizeof(gString), "Business name set to %s",SBizzInfo[bouse-100][sbMessage]);
	} else {
		strmid(BizzInfo[bouse][bMessage], result, 0, 64, 255);
		format(gString, sizeof(gString), "Business name set to %s",BizzInfo[bouse][bMessage]);
	}

	OnPropUpdate();
	SendClientMessage(playerid, COLOR_WHITE, gString);
	return 1;
}

CMD:bizwithdraw(playerid, params[]) {
	new bouse = PlayerInfo[playerid][pPbiskey];

	if(bouse == 255) {
		SendClientMessage(playerid, COLOR_GRAD2, "   You don't own a business");
		return 1;
	}

	new cashdeposit;

	if(sscanf(params, "i", cashdeposit)) {
		if(bouse >= 100) {
			format(gString, sizeof(gString), "  You Have $%d in your till.", SBizzInfo[bouse-100][sbTill]);
			SendClientMessage(playerid, COLOR_GRAD3, gString);
		} else {
			format(gString, sizeof(gString), "  You Have $%d in your till.", BizzInfo[bouse][bTill]);
			SendClientMessage(playerid, COLOR_GRAD3, gString);
		}

		SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /bizwithdraw [amount]");
		return 1;
	}

	if(bouse >= 100) {
		if(cashdeposit > SBizzInfo[bouse-100][sbTill] || cashdeposit < 1) {
			SendClientMessage(playerid, COLOR_GRAD2, "   You dont have that much");
			return 1;
		}
	} else {
		if(cashdeposit > BizzInfo[bouse][bTill] || cashdeposit < 1) {
			SendClientMessage(playerid, COLOR_GRAD2, "   You dont have that much");
			return 1;
		}
	}

	if(bouse >= 100) {
		if(!PlayerToPoint(100, playerid,SBizzInfo[bouse-100][sbEntranceX],SBizzInfo[bouse-100][sbEntranceY],SBizzInfo[bouse-100][sbEntranceZ])) {
			SendClientMessage(playerid, COLOR_GRAD2, "   You are to far from your business");
		} else {
			ConsumingMoney[playerid] = 1;
			GivePlayerMoney(playerid,cashdeposit);
			SBizzInfo[bouse-100][sbTill] -= cashdeposit;
			format(gString, sizeof(gString), "  You Have Withdrawn $%d from your till Total: $%d ", cashdeposit,SBizzInfo[bouse-100][sbTill]);
			OnPropUpdate();
			SendClientMessage(playerid, COLOR_YELLOW, gString);
		}
	} else {
		if(!PlayerToPoint(100, playerid,BizzInfo[bouse][bExitX],BizzInfo[bouse][bExitY],BizzInfo[bouse][bExitZ])) {
			SendClientMessage(playerid, COLOR_GRAD2, "   You are to far from your business");
		} else {
			ConsumingMoney[playerid] = 1;
			GivePlayerMoney(playerid,cashdeposit);
			BizzInfo[bouse][bTill] -= cashdeposit;
			format(gString, sizeof(gString), "  You Have Withdrawn $%d from your till Total: $%d ", cashdeposit,BizzInfo[bouse][bTill]);
			OnPropUpdate();
			SendClientMessage(playerid, COLOR_YELLOW, gString);
		}
	}
	return 1;
}

CMD:bizbank(playerid, params[]) {
	new bouse = PlayerInfo[playerid][pPbiskey];

	if(bouse == 255) {
		SendClientMessage(playerid, COLOR_GRAD2, "   You don't own a business");
		return 1;
	}

	new cashdeposit;

	if(sscanf(params, "i", cashdeposit)) {
		if(bouse >= 100) {
			format(gString, sizeof(gString), "  You Have $%d in your till.", SBizzInfo[bouse-100][sbTill]);
			SendClientMessage(playerid, COLOR_GRAD3, gString);
		} else {
			format(gString, sizeof(gString), "  You Have $%d in your till.", BizzInfo[bouse][bTill]);
			SendClientMessage(playerid, COLOR_GRAD3, gString);
		}

		SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /bizbank [amount]");
		return 1;
	}

	if(cashdeposit > GetPlayerMoney(playerid) || cashdeposit < 1) {
		SendClientMessage(playerid, COLOR_GRAD2, "   You dont have that much");
		return 1;
	}

	if(bouse >= 100) {
		if(!PlayerToPoint(100, playerid,SBizzInfo[bouse-100][sbEntranceX],SBizzInfo[bouse-100][sbEntranceY],SBizzInfo[bouse-100][sbEntranceZ])) {
			SendClientMessage(playerid, COLOR_GRAD2, "   You are to far from your business");
			return 1;
		} else {
			GivePlayerMoney(playerid,-cashdeposit);
			SBizzInfo[bouse-100][sbTill] += cashdeposit;
			ExtortionSBiz(bouse-100, cashdeposit);
			format(gString, sizeof(gString), "  You Have Banked $%d to your till Total: $%d ", cashdeposit,SBizzInfo[bouse-100][sbTill]);
			OnPropUpdate();
			SendClientMessage(playerid, COLOR_YELLOW, gString);
			return 1;
		}
	} else {
		if(!PlayerToPoint(100, playerid,BizzInfo[bouse][bExitX],BizzInfo[bouse][bExitY],BizzInfo[bouse][bExitZ])) {
			SendClientMessage(playerid, COLOR_GRAD2, "   You are to far from your business");
			return 1;
		} else {
			GivePlayerMoney(playerid,-cashdeposit);
			BizzInfo[bouse][bTill] += cashdeposit;
			ExtortionBiz(bouse, cashdeposit);
			format(gString, sizeof(gString), "  You Have Banked $%d to your till Total: $%d ", cashdeposit,BizzInfo[bouse][bTill]);
			OnPropUpdate();
			SendClientMessage(playerid, COLOR_YELLOW, gString);
			return 1;
		}
	}
	return 1;
}

CMD:heal(playerid, params[]) {
	new location = PlayerInfo[playerid][pLocal];
	new giveplayerid, moneys;

	if(sscanf(params, "ii", giveplayerid, moneys)) {
		if(location != 255) {
			if(location < 99) {
				if(HouseInfo[location][hArm] == 1 && IsACop(playerid)) {
					format(gString, sizeof(gString), "* %s puts on body armour.", PlayerInfo[playerid][pName]);
					ProxDetector(30.0, playerid, gString, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
					TogglePlayerControllable(playerid, 0);
					GetPlayerPos(playerid, Unspec[playerid][sPx], Unspec[playerid][sPy], Unspec[playerid][sPz]);
					Unspec[playerid][sPint] = PlayerInfo[playerid][pInt];
					Unspec[playerid][sLocal] = PlayerInfo[playerid][pLocal];
					SetPlayerPos(playerid,1527.5,-12.1,1002.0);
					PlayerInfo[playerid][pLocal] = 255;
					SetPlayerInterior(playerid,99);
					Spectate[playerid] = 257;
				} else {
					format(gString, sizeof(gString), "This place does not have armour upgrades.");
					SendClientMessage(playerid, TEAM_GREEN_COLOR,gString);
				}

				if(HouseInfo[location][hHel] == 1) {
					new Float:tempheal;
					GetPlayerHealth(playerid,tempheal);
					
					if( tempheal < 100.0) {
						SetPlayerHealth(playerid,100.0);
						PlayerPlaySound(playerid, 1150, 0.0, 0.0, 0.0);
						format(gString, sizeof(gString), "You have been healed to 100 health.");
						SendClientMessage(playerid, TEAM_GREEN_COLOR,gString);
					} else {
						SendClientMessage(playerid, TEAM_GREEN_COLOR,"You are already healed to 100.");
					}
				} else {
					format(gString, sizeof(gString), "This place does not have healing upgrades.");
					SendClientMessage(playerid, TEAM_GREEN_COLOR,gString);
				}
				return 1;
			} else if(location == 101) {//Restaurant
				new Float:tempheal;
				GetPlayerHealth(playerid,tempheal);

				if( tempheal < 100.0) {
					SetPlayerHealth(playerid,100.0);
					PlayerPlaySound(playerid, 1150, 0.0, 0.0, 0.0);
					format(gString, sizeof(gString), "You have been healed to 100 health.");
					SendClientMessage(playerid, TEAM_GREEN_COLOR,gString);
				} else {
					SendClientMessage(playerid, TEAM_GREEN_COLOR,"You are already healed to 100.");
				}
			} else if(location == 102 && IsACop(playerid)) {//Police Armoury
				SetPlayerHealth(playerid,100.0);
				format(gString, sizeof(gString), "* %s puts on body armour.", PlayerInfo[playerid][pName]);
				ProxDetector(30.0, playerid, gString, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
				TogglePlayerControllable(playerid, 0);
				GetPlayerPos(playerid, Unspec[playerid][sPx], Unspec[playerid][sPy], Unspec[playerid][sPz]);
				Unspec[playerid][sPint] = PlayerInfo[playerid][pInt];
				Unspec[playerid][sLocal] = PlayerInfo[playerid][pLocal];
				SetPlayerPos(playerid,1527.5,-12.1,1002.0);
				PlayerInfo[playerid][pLocal] = 255;
				SetPlayerInterior(playerid,99);
				Spectate[playerid] = 257;
			}
		}
		return 1;
	}

	if(moneys < 1 || moneys > 1000) { SendClientMessage(playerid, COLOR_GREY, "   Healing price not below 1 or above 1000 !"); return 1; }

	if(giveplayerid == playerid) {
		SendClientMessage(playerid, COLOR_GRAD1, "   You can not heal yourself!");
		return 1;
	}

	if(IsPlayerConnected(giveplayerid)) {
		new giveambu = GetPlayerVehicleID(giveplayerid);
		new playambu = GetPlayerVehicleID(playerid);

		if(gTeam[playerid] == TEAM_CYAN||PlayerInfo[playerid][pMember]==4||PlayerInfo[playerid][pLeader]==4) {//model
			if(IsAnAmbulance(playambu) && playambu == giveambu) {
				new Float:tempheal;
				GetPlayerHealth(giveplayerid,tempheal);

				if(tempheal >= 100.0) {
					SendClientMessage(playerid, TEAM_GREEN_COLOR,"   That person is fully healed.");
					return 1;
				}

				format(gString, sizeof(gString), "~y~You healed ~n~~w~%s~n~~g~$%d", PlayerInfo[giveplayerid][pName],moneys);
				GameTextForPlayer(playerid, gString, 5000, 1);
				GivePlayerMoney(playerid,moneys);
				GivePlayerMoney(giveplayerid,-moneys);
				new hp = 0;

				if(PlayerInfo[playerid][pPainPerk] > 0) {
					hp = 20 * PlayerInfo[playerid][pPainPerk]; hp += 100;
					SetPlayerHealth(giveplayerid, hp);
				} else {
					hp = 100;
					SetPlayerHealth(giveplayerid, 100);
				}

				PlayerPlaySound(playerid, 1150, 0.0, 0.0, 0.0);
				PlayerPlaySound(giveplayerid, 1150, 0.0, 0.0, 0.0);
				format(gString, sizeof(gString), "You have been healed to %d health -$%d",hp,moneys);
				SendClientMessage(giveplayerid, TEAM_GREEN_COLOR,gString);

				if(STDPlayer[giveplayerid] > 0) {
					STDPlayer[giveplayerid] = 0;
					SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, "* You are no longer infected with a STD anymore because of the Medics help !");
				}
			} else {
				SendClientMessage(playerid, COLOR_GRAD1, "   One of you is not in the Ambulance / Chopper !");
				return 1;
			}
		} else {
			SendClientMessage(playerid, COLOR_GRAD1, "   You are not authorized to use that command !");
			return 1;
		}
	} else {
		format(gString, sizeof(gString), "   %d is not an active player.", giveplayerid);
		SendClientMessage(playerid, COLOR_GRAD1, gString);
	}
	return 1;
}

CMD:mole(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] < 4) {
		return 1;
	}

	new result[64];

	if(sscanf(params, "s[64]", result)) {
		SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /mole [mole text]");
		return 1;
	}

	format(gString, sizeof(gString), "SMS: %s, Sender: MOLE (555)",result);
	if (gTeam[playerid] < 3){SendClientMessage(playerid, COLOR_YELLOW, gString);}
	SendEnemyMessage(COLOR_YELLOW, gString);

	foreach(new i : Player) {
		if(gTeam[i] >= 3 && gPlayerSpawned[i]) {
			RingTone[i] =20;
		}
	}

	printf("MOLE: %s", result);
	return 1;
}

CMD:hq(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] < 4) {
		return 1;
	}

	new result[64];

	if(sscanf(params, "s[64]", result)) {
		SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /hq [hq text]");
		return 1;
	}

	format(gString, sizeof(gString), "HQ: %s, over", result);
	if (gTeam[playerid] != 2 ){SendClientMessage(playerid, COLOR_DBLUE, gString);}
	SendTeamBeepMessage(2, COLOR_DBLUE, gString);
	printf("HQ: %s", result);
	return 1;
}

CMD:bigears(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] < 2) {
		return 1;
	}

	if(!BigEar[playerid]) {
		BigEar[playerid] = 1;
		SendClientMessage(playerid, COLOR_GRAD2, "   Your Ears Have Grown");
	} else if(BigEar[playerid]) {
		(BigEar[playerid] = 0);
		SendClientMessage(playerid, COLOR_GRAD2, "   Your Ears Have Shrank");
	}
	return 1;
}

CMD:id(playerid, params[]) {
	new target;

	if(sscanf(params, "i", target)) {
		SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /id [playerid/PartOfName]");
		return 1;
	}

	new sstring[256];

	if(IsPlayerConnected(target))
	{
		format(sstring, sizeof(sstring), "ID: (%d) %s",target,PlayerInfo[target][pName]);
		SendClientMessage(playerid, COLOR_GRAD1, sstring);
	}
	return 1;
}

CMD:tv(playerid, params[]) {
	if(PlayerInfo[playerid][pDonateRank] > 0) {
		if(WatchingTV[playerid] < 1) {
			GetPlayerPos(playerid, Unspec[playerid][Coords][0],Unspec[playerid][Coords][1],Unspec[playerid][Coords][2]);
		}
	}

	new hkey = PlayerInfo[playerid][pPhousekey];
	new house = PlayerInfo[playerid][pLocal];

	if(Spectate[playerid] == 255 && PlayerInfo[playerid][pLocal] != 255 || Spectate[playerid] == 255 && PlayerInfo[playerid][pAdmin] > 0) {
		GetPlayerPos(playerid, Unspec[playerid][sPx], Unspec[playerid][sPy], Unspec[playerid][sPz]);
		Unspec[playerid][sPint] = PlayerInfo[playerid][pInt];
		Unspec[playerid][sLocal] = PlayerInfo[playerid][pLocal];
		PlayerInfo[playerid][pLocal] = 255;
		gTeam[playerid] = 0;
	}

	if(!strcmp("off", params, true)) {
		if(WatchingTV[playerid] > 0) {
			WatchingTV[playerid] = 0;
			Spectate[playerid] = 253;
			GameTextForPlayer(playerid, "~w~TV~n~~r~Off", 5000, 6);
			PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
			return 1;
		} else {
			SendClientMessage(playerid, COLOR_GREY, "   You are not watching TV !");
			return 1;
		}
	}

	if(PlayerInfo[playerid][pAdmin] < 1) {
		if(house == 255) {
			GameTextForPlayer(playerid, "~r~There is no tv here", 5000, 1);
			return 1;
		}
	}

	if(PlayerInfo[playerid][pAdmin] > 1 || PlayerToPoint(12.0, playerid, HouseInfo[hkey][hExitx], HouseInfo[hkey][hExity],HouseInfo[hkey][hExitz])) {
		if(HouseInfo[hkey][hHealthx] != 1) {
			GameTextForPlayer(playerid, "~r~This upgrade isn't installed", 5000, 1);
			return 1;
		}

		new giveplayerid;
		sscanf(params, "i", giveplayerid);

		if(IsPlayerConnected(giveplayerid)) {
			Spectate[playerid] = giveplayerid;
			new Float:health;
			GetPlayerHealth(Spectate[playerid], health);
			new cash =  GetPlayerMoney(Spectate[playerid]);

			if(PlayerInfo[playerid][pAdmin] >= 1) {
				format(gString, sizeof(gString), "Recon: (%d) %s $%d H:%.0f",Spectate[playerid],PlayerInfo[Spectate[playerid]][pName],cash,health);
			} else {
				format(gString, sizeof(gString), "UAV: (%d) %s",Spectate[playerid],PlayerInfo[Spectate[playerid]][pName]);
			}

			SendClientMessage(playerid, COLOR_GREEN, gString);
			WatchingTV[playerid] = 1;
		} else {
			SendClientMessage(playerid, COLOR_GREEN, "Target is not available.");
		}
	} else {
		SendClientMessage(playerid, COLOR_GREEN, "   You are not in your House !");
		return 1;
	}
	return 1;
}

alias:tv("recon")

CMD:uncon(playerid, params[]) {
	SetCamBack(playerid);
	return 1;
}

CMD:admin(playerid, params[]) {
	new result[64];

	if(sscanf(params, "s[64]", result)) {
		SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: (/a)dmin [admin chat]");
		return 1;
	}

	format(gString, sizeof(gString), "*%d Admin %s: %s", PlayerInfo[playerid][pAdmin], PlayerInfo[playerid][pName], result);

	if(PlayerInfo[playerid][pAdmin] >= 1) {
		SendAdminMessage(COLOR_YELLOW, gString);
	}

	printf("Admin %s: %s", PlayerInfo[playerid][pName], result);
	return 1;
}

alias:admin("a")

CMD:logout(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] >= 4) {
		OnPlayerUpdate(playerid);
		gPlayerLogged[playerid] = 0;
		SendClientMessage(playerid, COLOR_GRAD1, "   It is now safe to quit.");
	} else {
		SendClientMessage(playerid, COLOR_GRAD1, "   You are not authorized to use that command !");
	}
	return 1;
}

CMD:logoutpl(playerid, params[]) {
	new giveplayerid;

	if(sscanf(params, "i", giveplayerid)) {
		SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /logoutpl [playerid/PartOfName]");
		return 1;
	}

	if(PlayerInfo[playerid][pAdmin] >= 4) {
		if(IsPlayerConnected(giveplayerid)) {
			OnPlayerUpdate(giveplayerid);
			gPlayerLogged[giveplayerid] = 0;
			SendClientMessage(playerid, COLOR_GRAD1, "   player was logged out.");
		}
	} else {
		SendClientMessage(playerid, COLOR_GRAD1, "   You are not authorized to use that command !");
	}
	return 1;
}

CMD:logoutall(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] >= 4) {
		foreach(new i : Player) {
			OnPlayerUpdate(i);
			gPlayerLogged[i] = 0;
		}

		SendClientMessage(playerid, COLOR_GRAD1, "   All Players Logged out.");
	} else {
		SendClientMessage(playerid, COLOR_GRAD1, "   You are not authorized to use that command !");
	}
	return 1;
}

CMD:cnn(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] >= 1) {
		new result[64];

		if(sscanf(params, "s[64]", result)) {
			SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /cnn [cnn textformat ~n~=Newline ~r~=Red ~g~=Green ~b~=Blue ~w~=White ~y~=Yellow]");
			return 1;
		}

		format(gString, sizeof(gString), "~b~%s: ~w~%s",PlayerInfo[playerid][pName],result);

		foreach(new i : Player) {
			GameTextForPlayer(i, gString, 5000, 6);
		}
	} else {
		SendClientMessage(playerid, COLOR_GRAD1, "   you are not authorized to use that command!");
	}
	return 1;
}

CMD:cnnn(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] >= 1337) {
		new txtid, result[64];

		if(sscanf(params, "s[64]i", result, txtid)) {
			SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /cnnn <type> [cnnc textformat ~n~=Newline ~r~=Red ~g~=Green ~b~=Blue ~w~=White ~y~=Yellow]");
			return 1;
		}

		if(txtid == 2) {
			SendClientMessage(playerid, COLOR_GRAD2, "You can not select 2");
			return 1;
		}

		format(gString, sizeof(gString), "~w~%s",result);

		foreach(new i : Player) {
			GameTextForPlayer(i, gString, 5000, txtid);
		}
	} else {
		SendClientMessage(playerid, COLOR_GRAD1, "   you are not authorized to use that command!");
	}
	return 1;
}

CMD:prison(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] < 2) {
		SendClientMessage(playerid, COLOR_GREY, "   you are not authorized to use this command !");
		return 1;
	}

	new giveplayerid;

	if(sscanf(params, "i", giveplayerid)) {
		SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /prison [playerid/PartOfName]");
		return 1;
	}

	if(IsPlayerConnected(giveplayerid)) {
		format(gString, sizeof(gString), "* You placed %s in Fort DeMorgan.", PlayerInfo[giveplayerid][pName]);
		SendClientMessage(playerid, COLOR_LIGHTRED, gString);
		format(gString, sizeof(gString), "* You were placed in Fort DeMorgan by Admin %s.", PlayerInfo[playerid][pName]);
		SendClientMessage(giveplayerid, COLOR_LIGHTRED, gString);
		GameTextForPlayer(giveplayerid, "~w~Welcome to ~n~~r~Fort DeMorgan", 5000, 3);
		WantedPoints[giveplayerid] = 0;
		WantedLevel[giveplayerid] = 0;
		PlayerInfo[giveplayerid][pJailed] = 2;
		PlayerInfo[giveplayerid][pJailTime] = 3600;
		SetPlayerPos(giveplayerid, 107.2300,1920.6311,18.5208);
		SetPlayerWorldBounds(giveplayerid, 337.5694,101.5826,1940.9759,1798.7453); //285.3481,96.9720,1940.9755,1799.0811
	} else {
		SendClientMessage(playerid, COLOR_GREY, "   That player is Offline !");
		return 1;
	}
	return 1;
}

CMD:jail(playerid, params[]) {
	new playa;
	new money;

	if(sscanf(params, "ii", playa, money)) {
		SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /jail [playerid/PartOfName] [time(minutes)]");
		return 1;
	}

	if(PlayerInfo[playerid][pAdmin] >= 2)
	{
		if(IsPlayerConnected(playa))
		{
			format(gString, sizeof(gString), "* You Jailed %s.", PlayerInfo[playa][pName]);
			SendClientMessage(playerid, COLOR_LIGHTRED, gString);
			format(gString, sizeof(gString), "* You were Jailed by Admin %s.", PlayerInfo[playerid][pName]);
			SendClientMessage(playa, COLOR_LIGHTRED, gString);
			ResetPlayerWeapons(playa);
			WantedPoints[playa] = 0;
			PlayerInfo[playa][pJailed] = 1;
			PlayerInfo[playa][pJailTime] = money*60;
			SetPlayerInterior(playa, 6);
			SetPlayerPos(playa, 264.6288,77.5742,1001.0391);
			format(gString, sizeof(gString), "You are jailed for %d minutes.   Bail: Unable", money);
			SendClientMessage(playa, COLOR_LIGHTBLUE, gString);
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GRAD1, "   you are not authorized to use that command!");
	}
	return 1;
}

CMD:tod(playerid, params[]) {
	new hour;

	if(sscanf(params, "i", hour)) {
		SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /tod [timeofday] (0-23)");
		return 1;
	}

	if(PlayerInfo[playerid][pAdmin] >= 1337) {
		SetWorldTime(hour);
		format(gString, sizeof(gString), "   Time set to %d Hours.", hour);
		BroadCast(COLOR_GRAD1, gString);
	} else {
		SendClientMessage(playerid, COLOR_GRAD1, "   You are not authorized to use that command !");
	}
	return 1;
}

CMD:startlotto(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] >= 1337) {
		format(gString, sizeof(gString), "Lottery News: We have started the Lottery Election.");
		OOCOff(COLOR_WHITE, gString);
		new rand = random(80);
		if(rand < 77) { rand += 3; }
		Lotto(rand);
	} else {
		SendClientMessage(playerid, COLOR_GREY, "   You are not an Admin !");
		return 1;
	}
	return 1;
}

CMD:setstat(playerid, params[]) {
	new giveplayerid, stat, amount;

	if(sscanf(params, "iii", giveplayerid, stat, amount)) {
		SendClientMessage(playerid, COLOR_GRAD1, "Uzycie: /setstat [playerid/PartOfName] [statcode] [amount]");
		SendClientMessage(playerid, COLOR_GRAD4, "|1 Level |2 SpawnHealth |3 UpgradePoints |4 Model ");
		SendClientMessage(playerid, COLOR_GRAD3, "|5 BankAccount |6 PhoneNumber |7 RespectPoints ");
		SendClientMessage(playerid, COLOR_GRAD2, "|8 HouseKey |9 BizKey |10 DonateRank |11 FMember");
		SendClientMessage(playerid, COLOR_GRAD2, "|12 Det |13 Lawyer |14 Fixer |15 News |16 Jack |17 Drug |18 Sex |19 Box |20 PassKey");
		return 1;
	}

	if(IsPlayerConnected(giveplayerid)) {
		return 1;
	}

	if(PlayerInfo[playerid][pAdmin] >= 4) {
		switch(stat) {
			case 1: {
				PlayerInfo[giveplayerid][pLevel] = amount;
				format(gString, sizeof(gString), "   The Player Was Set To Level %d", amount);
			}
			case 2: {
				PlayerInfo[giveplayerid][pSHealth] = amount;
				format(gString, sizeof(gString), "   The Player Was Set To %d Spawnhealth ", amount);
			}
			case 3: {
				PlayerInfo[giveplayerid][gPupgrade] = amount;
				format(gString, sizeof(gString), "   The Player Was Set To %d Upgrade Points", amount);
			}
			case 4: {
				PlayerInfo[giveplayerid][pModel] = amount;
				format(gString, sizeof(gString), "   The Player Was Set To Model %d", amount);
			}
			case 5: {
				PlayerInfo[giveplayerid][pAccount] = amount;
				format(gString, sizeof(gString), "   The Player Account Was Set To $%d", amount);
			}
			case 6: {
				PlayerInfo[giveplayerid][pPnumber] = amount;
				format(gString, sizeof(gString), "   The Player Phone Number Was Set To %d", amount);
			}
			case 7: {
				PlayerInfo[giveplayerid][pExp] = amount;
				format(gString, sizeof(gString), "   The Player Respect Points Were Set To %d", amount);
			}
			case 8: {
				PlayerInfo[giveplayerid][pPhousekey] = amount;
				format(gString, sizeof(gString), "   The Player House Key Was Set To %d", amount);
			}
			case 9: {
				PlayerInfo[giveplayerid][pPbiskey] = amount;
				format(gString, sizeof(gString), "   The Player Business Key Was Set To %d", amount);
			}
			case 10: {
				PlayerInfo[giveplayerid][pDonateRank] = amount;
				format(gString, sizeof(gString), "   The Player DonateRank Was Set To %d", amount);
			}
			case 11: {
				PlayerInfo[giveplayerid][pFMember] = amount;
				format(gString, sizeof(gString), "   The Player Family Member Was Set To %d", amount);
			}
			case 12: {
				PlayerInfo[giveplayerid][pDetSkill] = amount;
				format(gString, sizeof(gString), "   The Player Detective Skill Set To %d", amount);
			}
			case 13: {
				PlayerInfo[giveplayerid][pLawSkill] = amount;
				format(gString, sizeof(gString), "   The Player Lawyer Skill Set To %d", amount);
			}
			case 14: {
				PlayerInfo[giveplayerid][pMechSkill] = amount;
				format(gString, sizeof(gString), "   The Player Car Mechanic Skill Set To %d", amount);
			}
			case 15: {
				PlayerInfo[giveplayerid][pNewsSkill] = amount;
				format(gString, sizeof(gString), "   The Player News Reporter Skill Set To %d", amount);
			}
			case 16: {
				PlayerInfo[giveplayerid][pJackSkill] = amount;
				format(gString, sizeof(gString), "   The Player Car Jacker Skill Set To %d", amount);
			}
			case 17: {
				PlayerInfo[giveplayerid][pDrugsSkill] = amount;
				format(gString, sizeof(gString), "   The Player Drug Dealer Skill Set To %d", amount);
			}
			case 18: {
				PlayerInfo[giveplayerid][pSexSkill] = amount;
				format(gString, sizeof(gString), "   The Player Sex Skill Set To %d", amount);
			}
			case 19: {
				PlayerInfo[giveplayerid][pBoxSkill] = amount;
				format(gString, sizeof(gString), "   The Player Box Skill Set To %d", amount);
			}
			case 77: {
				PlayerInfo[giveplayerid][pJob] = amount;
				format(gString, sizeof(gString), "   The Player Job Set To %d", amount);
			}
			case 88: {
				PlayerInfo[giveplayerid][pContractTime] = amount;
				format(gString, sizeof(gString), "   The Player Job Contract Time Set To %d", amount);
			}
			default: {
				format(gString, sizeof(gString), "   Invalid Stat Code", amount);
			}
		}
		SendClientMessage(playerid, COLOR_GRAD1, gString);
	} else {
		SendClientMessage(playerid, COLOR_GRAD1, "   you are not authorized to use that command!");
	}
	return 1;
}

CMD:setfamily(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] < 4) {
		SendClientMessage(playerid, COLOR_GRAD1, "   you are not authorized to use that command!");
		return 1;
	}

	new family, stat, amount;

	if(sscanf(params, "iii", family, stat, amount)) {
		SendClientMessage(playerid, COLOR_GRAD1, "Uzycie: /setfamily [Family] [code] [amount]");
		SendClientMessage(playerid, COLOR_GRAD4, "|1 Members");
		return 1;
	}

	if(family < 1 || family > 10) { SendClientMessage(playerid, COLOR_GREY, "   FamilyNr can't be below 1 or above 10 !"); return 1; }
	family -= 1;

	if(stat < 1 || stat > 1) { SendClientMessage(playerid, COLOR_GREY, "   Stat Code can't be below 1 or above 1 !"); return 1; }
	if(amount < 1 || amount > 10) { SendClientMessage(playerid, COLOR_GREY, "   Amount can't be below 1 or above 10 !"); return 1; }

	switch(stat) {
		case 1: {
			FamilyInfo[family][FamilyMembers] = amount;
			format(gString, sizeof(gString), "   Family %s set to %d members", FamilyInfo[family][FamilyName], amount);
		}
		default: {
			format(gString, sizeof(gString), "   Invalid Stat Code");
		}
	}

	SendClientMessage(playerid, COLOR_GREY, gString);
	return 1;
}

CMD:setint(playerid, params[]) {
	new intid;

	if(sscanf(params, "i", intid)) {
		SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /setint [interiorid]");
		return 1;
	}

	if (PlayerInfo[playerid][pAdmin] >= 1) {
		SetPlayerInterior(playerid,intid);
		PlayerInfo[playerid][pInt] = intid;
		format(gString, sizeof(gString), "   interiorid %d.", intid);
		SendClientMessage(playerid, COLOR_GRAD1, gString);
	} else {
		SendClientMessage(playerid, COLOR_GRAD1, "   You are not authorized to use that command !");
	}
	return 1;
}

CMD:skydive(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] >= 2) {
		GetPlayerPos(playerid, rx, ry, rz);
		GivePlayerWeapon(playerid, 46, 0);
		SetPlayerPos(playerid,rx, ry, rz+1500);
		SendClientMessage(playerid, COLOR_WHITE, "GO!! GO!! GO!!");
	} else {
		SendClientMessage(playerid, COLOR_GRAD1, "   you are not authorized to use that command!");
	}
	return 1;
}

CMD:fourdive(playerid, params[]) {
	new para1;
	new para2;
	new para3;
	new para4;

	if(sscanf(params, "iiii", para1, para2, para3, para4)) {
		SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /fourdive [playerid1] [playerid2] [playerid3] [playerid4]");
		return 1;
	}

	if(PlayerInfo[playerid][pAdmin] >= 1337) {
		if (IsPlayerConnected(para1)){ GivePlayerWeapon(para1, 46, 0); SetPlayerPos(para1,1536.0, -1360.0, 1350.0);SetPlayerInterior(para1,0);PlayerInfo[para1][pInt] = 0;SendClientMessage(para1, COLOR_WHITE, "GO!! GO!! GO!!");}
		if ((IsPlayerConnected(para2)) && (para2>0)) { GivePlayerWeapon(para2, 46, 0); SetPlayerPos(para2,1536.0, -1345.0, 1350.0);SetPlayerInterior(para2,0);PlayerInfo[para2][pInt] = 0;SendClientMessage(para2, COLOR_RED, "GO!! GO!! GO!!");}
		if ((IsPlayerConnected(para3)) && (para3>0)) { GivePlayerWeapon(para3, 46, 0); SetPlayerPos(para3,1552.0, -1345.0, 1350.0);SetPlayerInterior(para3,0);PlayerInfo[para3][pInt] = 0;SendClientMessage(para3, COLOR_RED, "GO!! GO!! GO!!");}
		if ((IsPlayerConnected(para4)) && (para4>0)) { GivePlayerWeapon(para4, 46, 0); SetPlayerPos(para4,1552.0, -1360.0, 1350.0);SetPlayerInterior(para4,0);PlayerInfo[para4][pInt] = 0;SendClientMessage(para4, COLOR_RED, "GO!! GO!! GO!!");}
	} else {
		SendClientMessage(playerid, COLOR_GRAD1, "   you are not authorized to use that command!");
	}
	return 1;
}

CMD:invite(playerid, params[]) {
	new para1;

	if(sscanf(params, "i", para1)) {
		SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /invite [playerid/PartOfName]");
		return 1;
	}

	new ftext[20];

	if (PlayerInfo[playerid][pLeader] >= 1) {
		if(IsPlayerConnected(para1)) {
				if (gTeam[para1]==TEAM_GREEN && PlayerInfo[para1][pMember] == 0 && PlayerInfo[para1][pFMember] == 255) {
					if(PlayerInfo[para1][pJob] > 0) {
						SendClientMessage(playerid, COLOR_GREY, "   Can't invite him, player has a Job !");
						return 1;
					}

					if(PlayerInfo[playerid][pLeader] == 1) { PlayerInfo[para1][pTeam] = 2; gTeam[para1] = 2; ftext = "Police Force"; ChosenSkin[para1] = 280; SetPlayerSkin(para1, 280); }
					else if(PlayerInfo[playerid][pLeader] == 2) { PlayerInfo[para1][pTeam] = 2; gTeam[para1] = 2; ftext = "FBI/ATF"; ChosenSkin[para1] = 286; SetPlayerSkin(para1, 286); }
					else if(PlayerInfo[playerid][pLeader] == 3) { PlayerInfo[para1][pTeam] = 2; gTeam[para1] = 2; ftext = "National Guard"; ChosenSkin[para1] = 287; SetPlayerSkin(para1, 287); }
					else if(PlayerInfo[playerid][pLeader] == 4) { PlayerInfo[para1][pTeam] = 1; gTeam[para1] = 1; ftext = "Firemen/Ambulance"; ChosenSkin[para1] = 70; SetPlayerSkin(para1, 70); }
					else if(PlayerInfo[playerid][pLeader] == 5) { PlayerInfo[para1][pTeam] = 5; gTeam[para1] = 5; ftext = "La Cosa Nostra"; ChosenSkin[para1] = 258; SetPlayerSkin(para1, 120); }
					else if(PlayerInfo[playerid][pLeader] == 6) { PlayerInfo[para1][pTeam] = 5; gTeam[para1] = 5; ftext = "Yakuza"; ChosenSkin[para1] = 120; SetPlayerSkin(para1, 258); }
					else if(PlayerInfo[playerid][pLeader] == 7) { return 1; }
					else if(PlayerInfo[playerid][pLeader] == 8) { PlayerInfo[para1][pTeam] = 10; gTeam[para1] = 12; ftext = "Hitman Agency"; ChosenSkin[para1] = 127; SetPlayerSkin(para1, 127); }
					else if(PlayerInfo[playerid][pLeader] == 9) { PlayerInfo[para1][pTeam] = 12; gTeam[para1] = 12; ftext = "CNN Studio"; ChosenSkin[para1] = 148; SetPlayerSkin(para1, 148); }
					else if(PlayerInfo[playerid][pLeader] == 10) { PlayerInfo[para1][pTeam] = 12; gTeam[para1] = 12; ftext = "Taxi Cab Company"; ChosenSkin[para1] = 255; SetPlayerSkin(para1, 255); }
					else if(PlayerInfo[playerid][pLeader] == 11) { PlayerInfo[para1][pTeam] = 12; gTeam[para1] = 12; ftext = "School Instructors"; ChosenSkin[para1] = 59; SetPlayerSkin(para1, 59); }
					else { return 1; }
					PlayerInfo[para1][pMember] = PlayerInfo[playerid][pLeader];
					PlayerInfo[para1][pRank] = 1;
					printf("AdmCmd: %s has invited %s to join %s.", PlayerInfo[playerid][pName], PlayerInfo[para1][pName], ftext);
					format(gString, sizeof(gString), "   You have Joined the %s, you were invited by Leader %s", ftext, PlayerInfo[playerid][pName]);
					SendClientMessage(para1, COLOR_LIGHTBLUE, gString);
					format(gString, sizeof(gString), "   You have Invited %s to join the %s.", PlayerInfo[para1][pName],ftext);
					SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
					SetPlayerInterior(para1,0);
					new rand = random(sizeof(gInviteSpawns));
					SetPlayerPos(para1, gInviteSpawns[rand][0], gInviteSpawns[rand][1], gInviteSpawns[rand][2]); // Warp the player
					SetPlayerFacingAngle(para1, gInviteSpawns[rand][3]);
					SetPlayerCameraPos(para1,gInviteSpawns[rand][0] + 3, gInviteSpawns[rand][1], gInviteSpawns[rand][2]);
					SetPlayerCameraLookAt(para1,gInviteSpawns[rand][0], gInviteSpawns[rand][1], gInviteSpawns[rand][2]);
					TogglePlayerControllable(para1, 0);
					SelectChar[para1] = 255;
					SelectCharID[para1] = PlayerInfo[para1][pMember];
					SelectCharPlace[para1] = 1;
					PlayerInfo[para1][pModel] = ChosenSkin[para1];
					PlayerInfo[para1][pChar] = ChosenSkin[para1];
					SendClientMessage(para1, COLOR_LIGHTRED, "* Use 'next' to Select the char you want to use.");
					SendClientMessage(para1, COLOR_LIGHTRED, "* If you've found the Char you want to use, type 'done'.");
				} else {
					SendClientMessage(playerid, COLOR_GREY, "  That player is currently Wanted / a Different Team / or already a Family Member.");
				}
		}//not connected
	} else {
		SendClientMessage(playerid, COLOR_GRAD1, "   you are not authorized to use that command(leaders only)!");
	}
	return 1;
}

CMD:uninvite(playerid, params[]) {
	new para1;

	if(sscanf(params, "i", para1)) {
		SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /uninvite [playerid/PartOfName]");
		return 1;
	}

	if(PlayerInfo[playerid][pLeader] >= 1) {
		if(IsPlayerConnected(para1)) {
			if(PlayerInfo[para1][pMember] > 0) {
				printf("AdmCmd: %s has uninvited %s.", PlayerInfo[playerid][pName], PlayerInfo[para1][pName]);
				format(gString, sizeof(gString), "* You have been kicked from a Family / Police Force, by Leader %s.", PlayerInfo[playerid][pName]);
				SendClientMessage(para1, COLOR_LIGHTBLUE, gString);
				SendClientMessage(para1, COLOR_LIGHTBLUE, "* You are now a Civilian again.");
				gTeam[para1] = 3;
				PlayerInfo[para1][pTeam] = 3;
				PlayerInfo[para1][pMember] = 0;
				PlayerInfo[para1][pRank] = 0;
				PlayerInfo[para1][pChar] = 0;
				new rand = random(sizeof(CIV));
				SetSpawnInfo(para1, gTeam[para1], CIV[rand],0.0,0.0,0.0,0,0,0,0,0,0,0);
				PlayerInfo[para1][pModel] = CIV[rand];
				MedicBill[para1] = 0;
				SpawnPlayer(para1);
				format(gString, sizeof(gString), "   You have kicked %s from his Family / Police Force.", PlayerInfo[para1][pName]);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
			}
		}//not connected
	} else {
		SendClientMessage(playerid, COLOR_GRAD1, "   you are not authorized to use that command(Leaders only)!");
	}
	return 1;
}

CMD:makeadmin(playerid, params[]) {
	new para1;
	new level;
	if(sscanf(params, "ii", para1, level))
	{
		SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /makeadmin [playerid/PartOfName] [level(1-3)]");
		return 1;
	}
	if (PlayerInfo[playerid][pAdmin] >= 1337)
	{
		if(IsPlayerConnected(para1))
		{
			PlayerInfo[para1][pAdmin] = level;
			printf("AdmCmd: %s has promoted %s to a level %d admin.", PlayerInfo[playerid][pName], PlayerInfo[para1][pName], level);
			format(gString, sizeof(gString), "   You have been promoted to a level %d admin by %s", level, PlayerInfo[playerid][pName]);
			SendClientMessage(para1, COLOR_LIGHTBLUE, gString);
			format(gString, sizeof(gString), "   You have promoted %s to a level %d admin.", PlayerInfo[para1][pName],level);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GRAD1, "   you are not authorized to use that command!");
	}
	return 1;
}

CMD:makeircadmin(playerid, params[]) {
	new giveplayerid, channel;

	if(sscanf(params, "ii", giveplayerid, channel))
	{
		SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /makeircadmin [playerid/PartOfName] [ChannelNr]");
		return 1;
	}

	if(channel > 10 || channel < 0) { SendClientMessage(playerid, COLOR_GREY, "   Dont go below number 0, or above number 10!"); return 1; }
	if (PlayerInfo[playerid][pAdmin] >= 1337)
	{
		if(IsPlayerConnected(giveplayerid))
		{
			format(gString, sizeof(gString), "* You've made %s an IRC Admin over Channel %d.", PlayerInfo[giveplayerid][pName], channel);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
			format(gString, sizeof(gString), "* %s has made you an IRC Admin over Channel %d.", PlayerInfo[playerid][pName], channel);
			SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
			format(gString, sizeof(gString), "%s", PlayerInfo[giveplayerid][pName]);
			switch(channel)
			{
				case 1:
				{
					strmid(IRCInfo[0][iAdmin], gString, 0, strlen(gString), 255);
					IRCInfo[0][iNeedPass] = 0; IRCInfo[0][iLock] = 0;
				}
				case 2:
				{
					strmid(IRCInfo[1][iAdmin], gString, 0, strlen(gString), 255);
					IRCInfo[1][iNeedPass] = 0; IRCInfo[1][iLock] = 0;
				}
				case 3:
				{
					strmid(IRCInfo[2][iAdmin], gString, 0, strlen(gString), 255);
					IRCInfo[2][iNeedPass] = 0; IRCInfo[2][iLock] = 0;
				}
				case 4:
				{
					strmid(IRCInfo[3][iAdmin], gString, 0, strlen(gString), 255);
					IRCInfo[3][iNeedPass] = 0; IRCInfo[3][iLock] = 0;
				}
				case 5:
				{
					strmid(IRCInfo[4][iAdmin], gString, 0, strlen(gString), 255);
					IRCInfo[4][iNeedPass] = 0; IRCInfo[4][iLock] = 0;
				}
				case 6:
				{
					strmid(IRCInfo[5][iAdmin], gString, 0, strlen(gString), 255);
					IRCInfo[5][iNeedPass] = 0; IRCInfo[5][iLock] = 0;
				}
				case 7:
				{
					strmid(IRCInfo[6][iAdmin], gString, 0, strlen(gString), 255);
					IRCInfo[6][iNeedPass] = 0; IRCInfo[6][iLock] = 0;
				}
				case 8:
				{
					strmid(IRCInfo[7][iAdmin], gString, 0, strlen(gString), 255);
					IRCInfo[7][iNeedPass] = 0; IRCInfo[7][iLock] = 0;
				}
				case 9:
				{
					strmid(IRCInfo[8][iAdmin], gString, 0, strlen(gString), 255);
					IRCInfo[8][iNeedPass] = 0; IRCInfo[8][iLock] = 0;
				}
				case 10:
				{
					strmid(IRCInfo[9][iAdmin], gString, 0, strlen(gString), 255);
					IRCInfo[9][iNeedPass] = 0; IRCInfo[9][iLock] = 0;
				}
			}

			SaveIRC();
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   That player is Offline !");
			return 1;
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   you are not authorized to do that !");
		return 1;
	}
	return 1;
}

CMD:makeleader(playerid, params[]) {
	new para1;
	new level;

	if(sscanf(params, "ii", para1, level))
	{
		SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /makeleader [playerid/PartOfName] [Number(1-10)]");
		return 1;
	}

	if(level > 11 || level < 0) { SendClientMessage(playerid, COLOR_GREY, "   Dont go below number 0, or above number 11!"); return 1; }
	if(PlayerInfo[playerid][pAdmin] >= 1337)
	{
		if(IsPlayerConnected(para1))
		{
			if(PlayerInfo[para1][pMember] > 0 || PlayerInfo[para1][pFMember] < 255)
			{
				SendClientMessage(playerid, COLOR_GREY, "   That player is in a Faction / Family !");
				return 1;
			}
			PlayerInfo[para1][pLeader] = level;
			format(gString, sizeof(gString), "   You have been promoted to Leader to your requested Faction by Admin %s", PlayerInfo[playerid][pName]);
			SendClientMessage(para1, COLOR_LIGHTBLUE, gString);
			format(gString, sizeof(gString), "   You have given %s control to run Faction Number %d.", PlayerInfo[para1][pName],level);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
			if(level == 0) { PlayerInfo[para1][pChar] = 0; }
			else if(level == 1) { PlayerInfo[para1][pChar] = 288; } //Police Force
			else if(level == 2) { PlayerInfo[para1][pChar] = 286; } //FBI/ATF
			else if(level == 3) { PlayerInfo[para1][pChar] = 287; } //National Guard
			else if(level == 4) { PlayerInfo[para1][pChar] = 228; } //Fire/Ambulance
			else if(level == 5) { PlayerInfo[para1][pChar] = 113; } //La Cosa Nostra
			else if(level == 6) { PlayerInfo[para1][pChar] = 120; } //Yakuza
			else if(level == 7) { PlayerInfo[para1][pChar] = 147; } //Mayor
			else if(level == 8) { PlayerInfo[para1][pChar] = 294; } //Hitmans
			else if(level == 9) { PlayerInfo[para1][pChar] = 227; } //News Reporters
			else if(level == 10) { PlayerInfo[para1][pChar] = 61; } //Taxi Cab Company
			else if(level == 11) { PlayerInfo[para1][pChar] = 171; } //Driving/Flying School
			gTeam[para1] = 11;
			PlayerInfo[para1][pTeam] = 11;
			SetPlayerSkin(para1, PlayerInfo[para1][pChar]);
		}//not connected
	}
	else
	{
		SendClientMessage(playerid, COLOR_GRAD1, "   you are not authorized to use that command!");
	}
	return 1;
}

CMD:forceskin(playerid, params[]) {
	new para1;
	if(sscanf(params, "i", para1))
	{
		SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /forceskin [playerid/PartOfName]");
		return 1;
	}
	if (PlayerInfo[playerid][pAdmin] >= 4)
	{
		if(IsPlayerConnected(para1))
		{
			if(PlayerInfo[para1][pMember] < 1)
			{
				SendClientMessage(playerid, COLOR_GREY, "   That player is not in a Family / Force !");
				return 1;
			}
			format(gString, sizeof(gString), "* You are forced to Change your Skin by Admin %s.", PlayerInfo[playerid][pName]);
			SendClientMessage(para1, COLOR_LIGHTBLUE, gString);
			format(gString, sizeof(gString), "* You have forced %s To change his Skin.", PlayerInfo[para1][pName]);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
			if(PlayerInfo[para1][pMember] == 1) { PlayerInfo[para1][pTeam] = 5; ChosenSkin[para1] = 59; }
			else if(PlayerInfo[para1][pMember] == 2) { PlayerInfo[para1][pTeam] = 6; ChosenSkin[para1] = 121; }
			else if(PlayerInfo[para1][pMember] == 3) { PlayerInfo[para1][pTeam] = 7; ChosenSkin[para1] = 98; }
			else if(PlayerInfo[para1][pMember] == 4) { PlayerInfo[para1][pTeam] = 8; ChosenSkin[para1] = 46; }
			else if(PlayerInfo[para1][pMember] == 5) { PlayerInfo[para1][pTeam] = 9; ChosenSkin[para1] = 174; }
			else if(PlayerInfo[para1][pMember] == 6) { PlayerInfo[para1][pTeam] = 2; ChosenSkin[para1] = 280; }
			else if(PlayerInfo[para1][pMember] == 7) { PlayerInfo[para1][pTeam] = 2; ChosenSkin[para1] = 164; }
			else if(PlayerInfo[para1][pMember] == 8) { PlayerInfo[para1][pTeam] = 10; ChosenSkin[para1] = 186; }
			else { return 1; }
			SetPlayerInterior(para1,0);
			new rand = random(sizeof(gInviteSpawns));
			SetPlayerPos(para1, gInviteSpawns[rand][0], gInviteSpawns[rand][1], gInviteSpawns[rand][2]); // Warp the player
			SetPlayerFacingAngle(para1, gInviteSpawns[rand][3]);
			SetPlayerCameraPos(para1,gInviteSpawns[rand][0] + 3, gInviteSpawns[rand][1], gInviteSpawns[rand][2]);
			SetPlayerCameraLookAt(para1,gInviteSpawns[rand][0], gInviteSpawns[rand][1], gInviteSpawns[rand][2]);
			TogglePlayerControllable(para1, 0);
			SelectChar[para1] = 255;
			SelectCharID[para1] = PlayerInfo[para1][pMember];
			SelectCharPlace[para1] = 1;
			PlayerInfo[para1][pModel] = ChosenSkin[para1];
			PlayerInfo[para1][pChar] = ChosenSkin[para1];
			SendClientMessage(para1, COLOR_LIGHTRED, "* Use 'next' to Select the char you want to use.");
			SendClientMessage(para1, COLOR_LIGHTRED, "* If you've found the Char you want to use, type 'done'.");
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GRAD1, "   you are not authorized to use that command!");
	}
	return 1;
}

CMD:giverank(playerid, params[]) {
	new para1;
	new level;
	if(sscanf(params, "ii", para1, level))
	{
		SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /giverank [playerid/PartOfName] [Number(1-6)]");
		return 1;
	}
	if(level > 6 || level < 0) { SendClientMessage(playerid, COLOR_GREY, "   Dont go below number 0, or above number 6!"); return 1; }
	if (PlayerInfo[playerid][pLeader] >= 1)
	{
		if(IsPlayerConnected(para1))
		{
			PlayerInfo[para1][pRank] = level;
			format(gString, sizeof(gString), "   You have been promoted to a higher Rank by Leader %s", PlayerInfo[playerid][pName]);
			SendClientMessage(para1, COLOR_LIGHTBLUE, gString);
			format(gString, sizeof(gString), "   You have given %s Rank %d.", PlayerInfo[para1][pName],level);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GRAD1, "   you are not authorized to use that command(Leaders Only)!");
	}
	return 1;
}

CMD:setteam(playerid, params[]) {
	new para1;
	new level;
	if(sscanf(params, "ii", para1, level))
	{
		SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /setteam [playerid/PartOfName] [team 1(civ) - 2(cop)]");
		return 1;
	}
	if (PlayerInfo[playerid][pAdmin] >= 2)
	{
		if(IsPlayerConnected(para1))
		{
			PlayerInfo[para1][pTeam] = level;
			gTeam[para1] = level;
			SetPlayerWeapons(para1);
			SetPlayerSpawn(para1);
			ClearCrime(para1);
			printf("AdmCmd: %s has switched %s to team %d.", PlayerInfo[playerid][pName], PlayerInfo[para1][pName], level);
			format(gString, sizeof(gString), "   You have been switched to team %d by %s", level, PlayerInfo[playerid][pName]);
			SendClientMessage(para1, COLOR_LIGHTBLUE, gString);
			format(gString, sizeof(gString), "   You have switched %s to team %d.", PlayerInfo[para1][pName],level);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GRAD1, "   you are not authorized to use that command!");
	}
	return 1;
}

CMD:gotols(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] >= 3)
	{
		if(GetPlayerState(playerid) == 2)
		{
			new tmpcar = GetPlayerVehicleID(playerid);
			SetVehiclePos(tmpcar, 1529.6,-1691.2,13.3);
			TelePos[playerid][0] = 0.0;TelePos[playerid][1] = 0.0;
		}
		else
		{
			SetPlayerPos(playerid, 1529.6,-1691.2,13.3);
		}
		SendClientMessage(playerid, COLOR_GRAD1, "   You have been teleported !");
		SetPlayerInterior(playerid,0);
		PlayerInfo[playerid][pInt] = 0;
	}
	else
	{
		SendClientMessage(playerid, COLOR_GRAD1, "   You are not authorized to use that command !");
	}
	return 1;
}

CMD:gotolv(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] >= 3)
	{
		if (GetPlayerState(playerid) == 2)
		{
			new tmpcar = GetPlayerVehicleID(playerid);
			SetVehiclePos(tmpcar, 1699.2, 1435.1, 10.7);
			TelePos[playerid][0] = 0.0;TelePos[playerid][1] = 0.0;
		}
		else
		{
			SetPlayerPos(playerid, 1699.2,1435.1, 10.7);
		}
		SendClientMessage(playerid, COLOR_GRAD1, "   You have been teleported");
		SetPlayerInterior(playerid,0);
		PlayerInfo[playerid][pInt] = 0;
	}
	else
	{
		SendClientMessage(playerid, COLOR_GRAD1, "   you are not authorized to use that command!");
	}
	return 1;
}

CMD:gotosf(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] >= 3)
	{
		if (GetPlayerState(playerid) == 2)
		{
			new tmpcar = GetPlayerVehicleID(playerid);
			SetVehiclePos(tmpcar, -1417.0,-295.8,14.1);
			TelePos[playerid][0] = 0.0;TelePos[playerid][1] = 0.0;
		}
		else
		{
			SetPlayerPos(playerid, -1417.0,-295.8,14.1);
		}
		SendClientMessage(playerid, COLOR_GRAD1, "   You have been teleported");
		SetPlayerInterior(playerid,0);
		PlayerInfo[playerid][pInt] = 0;
	}
	else
	{
		SendClientMessage(playerid, COLOR_GRAD1, "   you are not authorized to use that command!");
	}
	return 1;
}

CMD:entercar(playerid, params[]) {
	new testcar;
	if(sscanf(params, "i", testcar))
	{
		SendClientMessage(playerid, COLOR_GRAD1, "Uzycie: /entercar [carid]");
		return 1;
	}
	if (PlayerInfo[playerid][pAdmin] >= 3)
	{
		PutPlayerInVehicle(playerid, testcar, 1);
		SendClientMessage(playerid, COLOR_GRAD1, "   You have been teleported");
	}
	else
	{
		SendClientMessage(playerid, COLOR_GRAD1, "   you are not authorized to use that command!");
	}
	return 1;
}

CMD:gotocar(playerid, params[]) {
	new testcar;
	if(sscanf(params, "i", testcar))
	{
		SendClientMessage(playerid, COLOR_GRAD1, "Uzycie: /gotocar [carid]");
		return 1;
	}
	if (PlayerInfo[playerid][pAdmin] >= 3)
	{
		new Float:cwx2,Float:cwy2,Float:cwz2;
		GetVehiclePos(testcar, cwx2, cwy2, cwz2);
		if (GetPlayerState(playerid) == 2)
		{
			new tmpcar = GetPlayerVehicleID(playerid);
			SetVehiclePos(tmpcar, cwx2, cwy2, cwz2);
			TelePos[playerid][0] = 0.0;TelePos[playerid][1] = 0.0;
		}
		else
		{
			SetPlayerPos(playerid, cwx2, cwy2, cwz2);
		}
		SendClientMessage(playerid, COLOR_GRAD1, "   You have been teleported");
		SetPlayerInterior(playerid,0);
	}
	else
	{
		SendClientMessage(playerid, COLOR_GRAD1, "   you are not authorized to use that command!");
	}
	return 1;
}

CMD:mark(playerid, params[]) {
	if (PlayerInfo[playerid][pAdmin] >= 3)
	{
		GetPlayerPos(playerid, TeleportDest[playerid][0],TeleportDest[playerid][1],TeleportDest[playerid][2]);
		SendClientMessage(playerid, COLOR_GRAD1, "   teleporter destination set");
	}
	else
	{
		SendClientMessage(playerid, COLOR_GRAD1, "   you are not authorized to use that command!");
	}
	return 1;
}

CMD:gotomark(playerid, params[]) {
	if (PlayerInfo[playerid][pAdmin] >= 3)
	{
		if (GetPlayerState(playerid) == 2)
		{
			new tmpcar = GetPlayerVehicleID(playerid);
			SetVehiclePos(tmpcar, TeleportDest[playerid][0],TeleportDest[playerid][1],TeleportDest[playerid][2]);
			TelePos[playerid][0] = 0.0;TelePos[playerid][1] = 0.0;
		}
		else
		{
			SetPlayerPos(playerid, TeleportDest[playerid][0],TeleportDest[playerid][1],TeleportDest[playerid][2]);
		}
		SendClientMessage(playerid, COLOR_GRAD1, "   You have been teleported");
		SetPlayerInterior(playerid,0);
	}
	else
	{
		SendClientMessage(playerid, COLOR_GRAD1, "   you are not authorized to use that command!");
	}
	return 1;
}

CMD:gotoin(playerid, params[]) {
	if (PlayerInfo[playerid][pAdmin] >= 3)
	{
		if (GetPlayerState(playerid) == 2)
		{
			new tmpcar = GetPlayerVehicleID(playerid);
			SetVehiclePos(tmpcar, 1416.107000,0.268620,1000.926000);
		}
		else
		{
			SetPlayerPos(playerid, 1416.107000,0.268620,1000.926000);
		}
		SendClientMessage(playerid, COLOR_GRAD1, "   You have been teleported");
		SetPlayerInterior(playerid,1);
	}
	else
	{
		SendClientMessage(playerid, COLOR_GRAD1, "   you are not authorized to use that command!");
	}
	return 1;
}

CMD:gotostad(playerid, params[]) {
	if (PlayerInfo[playerid][pAdmin] >= 3)
	{
		if (GetPlayerState(playerid) == 2)
		{
			new tmpcar = GetPlayerVehicleID(playerid);
			SetVehiclePos(tmpcar, -1435.75, -652.664, 1054.94);
		}
		else
		{
			SetPlayerPos(playerid, -1435.75, -652.664, 1054.94);
		}
		SetPlayerInterior(playerid,4);
		SendClientMessage(playerid, COLOR_GRAD1, "   You have been teleported");
	}
	else
	{
		SendClientMessage(playerid, COLOR_GRAD1, "   you are not authorized to use that command!");
	}
	return 1;
}

CMD:gotojet(playerid, params[]) {
	if (PlayerInfo[playerid][pAdmin] >= 3)
	{
		if (GetPlayerState(playerid) == 2)
		{
			new tmpcar = GetPlayerVehicleID(playerid);
			SetVehiclePos(tmpcar, 1.71875, 30.4062, 1200.34);
		}
		else
		{
			SetPlayerPos(playerid, 1.71875, 30.4062, 1200.34);
		}
		SetPlayerInterior(playerid,1);
		SendClientMessage(playerid, COLOR_GRAD1, "   You have been teleported");
	}
	else
	{
		SendClientMessage(playerid, COLOR_GRAD1, "   you are not authorized to use that command!");
	}
	return 1;
}

CMD:goto(playerid, params[]) {
	new plo;
	if(sscanf(params, "i", plo))
	{
		SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /goto [playerid/PartOfName]");
		return 1;
	}
	new Float:plocx,Float:plocy,Float:plocz;
	if (IsPlayerConnected(plo))
	{
		if (PlayerInfo[playerid][pAdmin] >= 1)
		{
			if(Spectate[playerid] != 255)
			{
				Spectate[playerid] = 256;
			}
			GetPlayerPos(plo, plocx, plocy, plocz);
			if(PlayerInfo[plo][pInt] > 0)
			{
				SetPlayerInterior(playerid,PlayerInfo[plo][pInt]);
				PlayerInfo[playerid][pInt] = PlayerInfo[plo][pInt];
				PlayerInfo[playerid][pLocal] = PlayerInfo[plo][pLocal];
			}
			if(PlayerInfo[playerid][pInt] == 0)
			{
				SetPlayerInterior(playerid,0);
			}
			if(plocz > 530.0 && PlayerInfo[plo][pInt] == 0) //the highest land point in sa = 526.8
			{
				SetPlayerInterior(playerid,1);
				PlayerInfo[playerid][pInt] = 1;
			}
			if (GetPlayerState(playerid) == 2)
			{
				new tmpcar = GetPlayerVehicleID(playerid);
				SetVehiclePos(tmpcar, plocx, plocy+4, plocz);
				TelePos[playerid][0] = 0.0;TelePos[playerid][1] = 0.0;
			}
			else
			{
				SetPlayerPos(playerid,plocx,plocy+2, plocz);
			}
			SendClientMessage(playerid, COLOR_GRAD1, "   You have been teleported");
		}
		else
		{
			SendClientMessage(playerid, COLOR_GRAD1, "   you are not authorized to use that command!");
		}
	}
	else
	{
		format(gString, sizeof(gString), "   %d is not an active player.", plo);
		SendClientMessage(playerid, COLOR_GRAD1, gString);
	}
	return 1;
}

CMD:gethere(playerid, params[]) {
	new plo;
	if(sscanf(params, "i", plo))
	{
		SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /gethere [playerid/PartOfName]");
		return 1;
	}
	new Float:plocx,Float:plocy,Float:plocz;
	if (IsPlayerConnected(plo))
	{
		if (PlayerInfo[plo][pAdmin] > 1337)
		{
			SendClientMessage(playerid, COLOR_GRAD1, "Ask the admin to goto you.");
			return 1;
		}
		if (PlayerInfo[playerid][pAdmin] >= 3)
		{
			GetPlayerPos(playerid, plocx, plocy, plocz);
			if(PlayerInfo[playerid][pInt] > 0)
			{
				SetPlayerInterior(plo,PlayerInfo[playerid][pInt]);
				PlayerInfo[plo][pInt] = PlayerInfo[playerid][pInt];
				PlayerInfo[plo][pLocal] = PlayerInfo[playerid][pLocal];
			}
			if(PlayerInfo[playerid][pInt] == 0)
			{
				SetPlayerInterior(plo,0);
			}
			if(plocz > 930.0 && PlayerInfo[playerid][pInt] == 0) //the highest land point in sa = 526.8
			{
				SetPlayerInterior(plo,1);
				PlayerInfo[plo][pInt] = 1;
			}
			if (GetPlayerState(plo) == 2)
			{
				TelePos[plo][0] = 0.0;
				TelePos[plo][1] = 0.0;
				new tmpcar = GetPlayerVehicleID(plo);
				SetVehiclePos(tmpcar, plocx, plocy+4, plocz);
			}
			else
			{
				SetPlayerPos(plo,plocx,plocy+2, plocz);
			}
			SendClientMessage(plo, COLOR_GRAD1, "   You have been teleported");
		}
		else
		{
			SendClientMessage(playerid, COLOR_GRAD1, "   you are not authorized to use that command!");
		}
	}
	else
	{
		format(gString, sizeof(gString), "   %d is not an active player.", plo);
		SendClientMessage(playerid, COLOR_GRAD1, gString);
	}
	return 1;
}

CMD:getcar(playerid, params[]) {
	new plo;
	if(sscanf(params, "i", plo))
	{
		SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /getcar [carid]");
		return 1;
	}
	new Float:plocx,Float:plocy,Float:plocz;
	if (PlayerInfo[playerid][pAdmin] >= 3)
	{
		GetPlayerPos(playerid, plocx, plocy, plocz);
		SetVehiclePos(plo,plocx,plocy+4, plocz);
	}
	else
	{
		SendClientMessage(playerid, COLOR_GRAD1, "   you are not authorized to use that command!");
	}
	return 1;
}

CMD:oldcar(playerid, params[]) {
	format(gString, sizeof(gString), "Your old car was: %d",gLastCar[playerid]);
	SendClientMessage(playerid, COLOR_GREY, gString);
	return 1;
}

CMD:fuelcars(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] >= 4)
	{
		for(new c=0;c<CAR_AMOUNT;c++)
		{
			Gas[c] = GasMax;
		}
		SendClientMessage(playerid, COLOR_GREY, "   All cars filled with Fuel ! ");
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   You are not an Admin ! ");
		return 1;
	}
	return 1;
}

CMD:givegun(playerid, params[]) {
	new playa;
	new gun;
	new ammo;
	if(sscanf(params, "iii", playa, gun, ammo))
	{
		SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /givegun [playerid/PartOfName] [weaponid(eg. 46 = Parachute)] [ammo]");
		SendClientMessage(playerid, COLOR_GRAD1, "Uzycie: /givegun [playerid/PartOfName] [weaponid] [ammo]");
		SendClientMessage(playerid, COLOR_GRAD4, "3(Club) 4(knife) 5(bat) 6(Shovel) 7(Cue) 8(Katana) 10-13(Dildo) 14(Flowers) 16(Grenades) 18(Molotovs) 22(Pistol) 23(SPistol)");
		SendClientMessage(playerid, COLOR_GRAD3, "24(Eagle) 25(shotgun) 29(MP5) 30(AK47) 31(M4) 33(Rifle) 34(Sniper) 37(Flamethrower) 41(spray) 42(exting) 43(Camera) 46(Parachute)");
		return 1;
	}
	if(gun < 1||gun > 46||gun==27||gun==1||gun==2||gun==9||gun==17||gun==19||gun==20||gun==21||gun==36||gun==38||gun==39||gun==40||gun==44||gun==45)
	{ SendClientMessage(playerid, COLOR_GRAD1, "   wrong WeaponID!"); return 1; }
	if(ammo <1||ammo > 999)
	{ SendClientMessage(playerid, COLOR_GRAD1, "   dont go below 1 or above 999 bullets!"); return 1; }
	if (PlayerInfo[playerid][pAdmin] >= 4)
	{
		if(IsPlayerConnected(playa))
		{
			GivePlayerWeapon(playa, gun, ammo);
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GRAD1, "   you are not authorized to use that command!");
	}
	return 1;
}

CMD:sethp(playerid, params[]) {
	new playa;
	new health;
	if(sscanf(params, "ii", playa, health))
	{
		SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /sethp [playerid/PartOfName] [health]");
		return 1;
	}
	if (PlayerInfo[playerid][pAdmin] >= 4)
	{
		if(IsPlayerConnected(playa))
		{
			SetPlayerHealth(playa, health);
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GRAD1, "   you are not authorized to use that command!");
	}
	return 1;
}

CMD:setarmor(playerid, params[]) {
	new playa;
	new health;
	if(sscanf(params, "ii", playa, health))
	{
		SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /setarmor [playerid/PartOfName] [armor]");
		return 1;
	}
	if (PlayerInfo[playerid][pAdmin] >= 4)
	{
		if(IsPlayerConnected(playa))
		{
			SetPlayerArmour(playa, health);
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GRAD1, "   you are not authorized to use that command!");
	}
	return 1;
}

CMD:veh(playerid, params[]) {
	if (PlayerInfo[playerid][pAdmin] < 4)
	{
		SendClientMessage(playerid, COLOR_GRAD1, "   you are not authorized to use that command!");
		return 1;
	}
	new car;
	new color1;
	new color2;
	if(sscanf(params, "iii", car, color1, color2))
	{
		SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /veh [carid] [color1] [color2]");
		return 1;
	}
	if(car < 400 || car > 611) { SendClientMessage(playerid, COLOR_GREY, "   Vehicle Number can't be below 400 or above 611 !"); return 1; }
	if(color1 < 0 || color1 > 126) { SendClientMessage(playerid, COLOR_GREY, "   Color Number can't be below 0 or above 126 !"); return 1; }
	if(color2 < 0 || color2 > 126) { SendClientMessage(playerid, COLOR_GREY, "   Color Number can't be below 0 or above 126 !"); return 1; }
	new Float:X,Float:Y,Float:Z;
	GetPlayerPos(playerid, X,Y,Z);
	new carid = CreateVehicle(car, X,Y,Z, 0.0, color1, color2, 60000);
	CreatedCars[CreatedCar] = carid;
	CreatedCar ++;
	format(gString, sizeof(gString), "   Vehicle %d spawned.", carid);
	SendClientMessage(playerid, COLOR_GREY, gString);
	return 1;
}

CMD:fixveh(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] < 4)
	{
		SendClientMessage(playerid, COLOR_GRAD1, "   you are not authorized to use that command!");
		return 1;
	}
	if(IsPlayerInAnyVehicle(playerid))
	{
		SetVehicleHealth(GetPlayerVehicleID(playerid), 1000.0);
		SendClientMessage(playerid, COLOR_GREY, "   Vehicle Fixed !");
	}
	return 1;
}

CMD:destroycars(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] < 4)
	{
		SendClientMessage(playerid, COLOR_GRAD1, "   you are not authorized to use that command!");
		return 1;
	}
	for(new i = 0; i < sizeof(CreatedCars); i++)
	{
		if(i != 0)
		{
			DestroyVehicle(i);
		}
	}
	SendClientMessage(playerid, COLOR_GREY, "   Created Vehicles destroyed !");
	return 1;
}

CMD:weather(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] < 1337)
	{
		SendClientMessage(playerid, COLOR_GRAD1, "   you are not authorized to use that command!");
		return 1;
	}
	new weather;
	if(sscanf(params, "i", weather))
	{
		SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /weather [weatherid]");
		return 1;
	}
	if(weather < 0||weather > 45) { SendClientMessage(playerid, COLOR_GREY, "   Weather ID can't be below 0 or above 45 !"); return 1; }
	SetPlayerWeather(playerid, weather);
	SendClientMessage(playerid, COLOR_GREY, "   Weather Set !");
	return 1;
}

CMD:weatherall(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] < 1337)
	{
		SendClientMessage(playerid, COLOR_GRAD1, "   you are not authorized to use that command!");
		return 1;
	}
	new weather;
	if(sscanf(params, "i", weather))
	{
		SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /weatherall [weatherid]");
		return 1;
	}
	if(weather < 0||weather > 45) { SendClientMessage(playerid, COLOR_GREY, "   Weather ID can't be below 0 or above 45 !"); return 1; }
	SetWeather(weather);
	SendClientMessage(playerid, COLOR_GREY, "   Weather Set to everyone !");
	return 1;
}

CMD:money(playerid, params[]) {
	new playa;
	new money;
	if(sscanf(params, "ii", playa, money))
	{
		SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /money [playerid/PartOfName] [money]");
		return 1;
	}
	if (PlayerInfo[playerid][pAdmin] >= 4)
	{
		if(IsPlayerConnected(playa))
		{
			ResetPlayerMoney(playa);
			ConsumingMoney[playa] = 1;
			GivePlayerMoney(playa, money);
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GRAD1, "   you are not authorized to use that command!");
	}
	return 1;
}

CMD:givemoney(playerid, params[]) {
	new playa;
	new money;
	if(sscanf(params, "ii", playa, money))
	{
		SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /givemoney [playerid/PartOfName] [money]");
		return 1;
	}
	if (PlayerInfo[playerid][pAdmin] >= 4)
	{
		if(IsPlayerConnected(playa))
		{
			ConsumingMoney[playa] = 1;
			GivePlayerMoney(playa, money);
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GRAD1, "   you are not authorized to use that command!");
	}
	return 1;
}

CMD:slap(playerid, params[]) {
	new playa;
	if(sscanf(params, "i", playa))
	{
		SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /slap [playerid/PartOfName]");
		return 1;
	}
	new Float:shealth;
	new Float:slx, Float:sly, Float:slz;
	if (PlayerInfo[playerid][pAdmin] >=1)
	{
		if(IsPlayerConnected(playa))
		{
			GetPlayerHealth(playa, shealth);
			SetPlayerHealth(playa, shealth-5);
			GetPlayerPos(playa, slx, sly, slz);
			SetPlayerPos(playa, slx, sly, slz+5);
			PlayerPlaySound(playa, 1130, slx, sly, slz+5);
			printf("AdmCmd: %s slapped %s",PlayerInfo[playerid][pName],  PlayerInfo[playa][pName]);
			format(gString, sizeof(gString), "AdmCmd: %s was slapped by %s",PlayerInfo[playa][pName] ,PlayerInfo[playerid][pName]);
			ABroadCast(COLOR_LIGHTRED,gString,1);
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GRAD1, "   you are not authorized to use that command!");
	}
	return 1;
}

CMD:mute(playerid, params[]) {
	new playa;
	if(sscanf(params, "i", playa))
	{
		SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /mute [playerid/PartOfName]");
		return 1;
	}
	if (PlayerInfo[playerid][pAdmin] >= 1)
	{
		if(IsPlayerConnected(playa))
		{
			if(PlayerInfo[playa][pMuted] == 0)
			{
				PlayerInfo[playa][pMuted] = 1;
				printf("AdmCmd: %s silenced %s",PlayerInfo[playerid][pName],  PlayerInfo[playa][pName]);
				format(gString, sizeof(gString), "AdmCmd: %s was silenced by %s",PlayerInfo[playa][pName] ,PlayerInfo[playerid][pName]);
				ABroadCast(COLOR_LIGHTRED,gString,1);
			}
			else
			{
				PlayerInfo[playa][pMuted] = 0;
				printf("AdmCmd: %s unsilenced %s",PlayerInfo[playerid][pName],  PlayerInfo[playa][pName]);
				format(gString, sizeof(gString), "AdmCmd: %s was unsilenced by %s",PlayerInfo[playa][pName] ,PlayerInfo[playerid][pName]);
				ABroadCast(COLOR_LIGHTRED,gString,1);
			}
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GRAD1, "   you are not authorized to use that command!");
	}
	return 1;
}

CMD:kick(playerid, params[]) {
	new giveplayerid, result[64];
	if(sscanf(params, "is[64]", giveplayerid, result))
	{
		SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /kick [playerid/PartOfName] [reason]");
		return 1;
	}
	if(PlayerInfo[playerid][pAdmin] >= 1)
	{
		if(IsPlayerConnected(giveplayerid))
		{
			new year, month,day;
			getdate(year, month, day);
			format(gString, sizeof(gString), "AdmCmd: %s was kicked by %s, reason: %s (%d-%d-%d)", PlayerInfo[giveplayerid][pName], PlayerInfo[playerid][pName], (result),month,day,year);
			KickLog(gString);
			Kick(giveplayerid);
			format(gString, sizeof(gString), "AdmCmd: %s was kicked by %s, reason: %s", PlayerInfo[giveplayerid][pName], PlayerInfo[playerid][pName], (result));
			SendClientMessageToAll(COLOR_LIGHTRED, gString);
			return 1;
		}
	}
	else
	{
		format(gString, sizeof(gString), "   %d is not an active player.", giveplayerid);
		SendClientMessage(playerid, COLOR_GRAD1, gString);
	}
	return 1;
}

CMD:skick(playerid, params[]) {
	new giveplayerid;
	if(sscanf(params, "i", giveplayerid))
	{
		SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /skick [playerid/PartOfName]");
		return 1;
	}
	if (PlayerInfo[playerid][pAdmin] >= 1)
	{
		if(IsPlayerConnected(giveplayerid))
		{
			Kick(giveplayerid);
		}
	}
	else
	{
		format(gString, sizeof(gString), "   %d is not an active player.", giveplayerid);
		SendClientMessage(playerid, COLOR_GRAD1, gString);
	}
	return 1;
}

CMD:kickres(playerid, params[]) {
	if (PlayerInfo[playerid][pAdmin] < 1)
	{
		return 1;
	}
	new level;
	new ammount;
	if(sscanf(params, "ii", level, ammount))
	{
		SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /kickres [level] [ammount]");
		return 1;
	}
	if(level < 0 || level > 5) { SendClientMessage(playerid, COLOR_GREY, "   Can only Reserved Slots Kick from level 0 to 5 !"); return 1; }
	if(ammount < 1 || ammount > 10) { SendClientMessage(playerid, COLOR_GREY, "   Can only Reserved Slots Kick of a maximum of 10 players !"); return 1; }
	foreach(new i : Player)
	{
		if(PlayerInfo[i][pLevel] == level && PlayerInfo[i][pAdmin] < 1 && PlayerInfo[i][pDonateRank] < 1 && ammount > 0)
		{
			ammount -= 1;
			Kick(i);
		}
	}
	return 1;
}

CMD:warn(playerid, params[]) {
	new giveplayerid;
	new result[64];
	if(sscanf(params, "is[64]", giveplayerid, result))
	{
		SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /warn [playerid/PartOfName] [reason]");
		return 1;
	}
	if (PlayerInfo[playerid][pAdmin] >= 1)
	{
		if(IsPlayerConnected(giveplayerid))
		{
			PlayerInfo[giveplayerid][pWarns] += 1;
			if(PlayerInfo[giveplayerid][pWarns] >= 3)
			{
				new year, month,day;
				getdate(year, month, day);
				format(gString, sizeof(gString), "AdmCmd: %s was banned by %s, reason: %s (%d-%d-%d)", PlayerInfo[giveplayerid][pName], PlayerInfo[playerid][pName], (result),month,day,year);
				BanLog(gString);
				format(gString, sizeof(gString), "AdmCmd: %s was banned by %s (had 3 Warnings), reason: %s", PlayerInfo[giveplayerid][pName], PlayerInfo[playerid][pName], (result));
				SendClientMessageToAll(COLOR_LIGHTRED, gString);
				PlayerInfo[giveplayerid][pAdmin] = PlayerInfo[giveplayerid][pLevel];
				PlayerInfo[giveplayerid][pLevel] = -999;
				Ban(giveplayerid);
				return 1;
			}
			format(gString, sizeof(gString), "You warned %s, reason: %s", PlayerInfo[giveplayerid][pName], (result));
			SendClientMessage(playerid, COLOR_LIGHTRED, gString);
			format(gString, sizeof(gString), "You were warned by %s, reason: %s", PlayerInfo[playerid][pName], (result));
			SendClientMessage(giveplayerid, COLOR_LIGHTRED, gString);
			return 1;
		}//not connected
	}
	else
	{
		format(gString, sizeof(gString), "   %d is not an active player.", giveplayerid);
		SendClientMessage(playerid, COLOR_GRAD1, gString);
	}
	return 1;
}

CMD:sban(playerid, params[]) {
	new giveplayerid;
	new result[64];
	if(sscanf(params, "is[64]", giveplayerid, result))
	{
		SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /sban [playerid/PartOfName] [reason]");
		return 1;
	}
	if (PlayerInfo[playerid][pAdmin] >= 1)
	{
		if(IsPlayerConnected(giveplayerid))
		{
			new year, month,day;
			getdate(year, month, day);
			format(gString, sizeof(gString), "AdmCmd: %s was banned by %s, reason: %s (%d-%d-%d)", PlayerInfo[giveplayerid][pName], PlayerInfo[playerid][pName], (result),month,day,year);
			BanLog(gString);
			PlayerInfo[giveplayerid][pAdmin] = PlayerInfo[giveplayerid][pLevel];
			PlayerInfo[giveplayerid][pLevel] = -999;
			Ban(giveplayerid);
			return 1;
		}//not connected
	}
	else
	{
		format(gString, sizeof(gString), "   %d is not an active player.", giveplayerid);
		SendClientMessage(playerid, COLOR_GRAD1, gString);
	}
	return 1;
}

CMD:ban(playerid, params[]) {
	new giveplayerid;
	new result[64];
	if(sscanf(params, "is[64]", giveplayerid, result))
	{
		SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /ban [playerid/PartOfName] [reason]");
		return 1;
	}
	if (PlayerInfo[playerid][pAdmin] >= 1)
	{
		if(IsPlayerConnected(giveplayerid))
		{
			new year, month,day;
			getdate(year, month, day);
			format(gString, sizeof(gString), "AdmCmd: %s was banned by %s, reason: %s (%d-%d-%d)", PlayerInfo[giveplayerid][pName], PlayerInfo[playerid][pName], (result),month,day,year);
			BanLog(gString);
			format(gString, sizeof(gString), "AdmCmd: %s was banned by %s, reason: %s", PlayerInfo[giveplayerid][pName], PlayerInfo[playerid][pName], (result));
			SendClientMessageToAll(COLOR_LIGHTRED, gString);
			PlayerInfo[giveplayerid][pAdmin] = PlayerInfo[giveplayerid][pLevel];
			PlayerInfo[giveplayerid][pLevel] = -999;
			Ban(giveplayerid);
			return 1;
		}//not connected
	}
	else
	{
		format(gString, sizeof(gString), "   %d is not an active player.", giveplayerid);
		SendClientMessage(playerid, COLOR_GRAD1, gString);
	}
	return 1;
}

CMD:freeze(playerid, params[]) {
	new playa;
	if(sscanf(params, "i", playa))
	{
		SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /freeze [playerid/PartOfName]");
		return 1;
	}
	if(PlayerInfo[playa][pAdmin] > 0)
	{
		SendClientMessage(playerid, COLOR_GRAD2, "Admins can not be frozen");
		return 1;
	}
	if (PlayerInfo[playerid][pAdmin] >= 2)
	{
		if(IsPlayerConnected(playa))
		{
			TogglePlayerControllable(playa, 0);
			format(gString, sizeof(gString), "AdmCmd: %s Freezes %s",PlayerInfo[playerid][pName],  PlayerInfo[playa][pName]);
			printf("%s",gString);
			format(gString, sizeof(gString), "AdmCmd: %s was Frozen by %s",PlayerInfo[playa][pName] ,PlayerInfo[playerid][pName]);
			ABroadCast(COLOR_LIGHTRED,gString,1);
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GRAD1, "   you are not authorized to use that command!");
	}
	return 1;
}

CMD:unfreeze(playerid, params[]) {
	new playa;
	if(sscanf(params, "i", playa))
	{
		SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /unfreeze [playerid]");
		return 1;
	}
	if(PlayerInfo[playerid][pAdmin] >= 1)
	{
		if(IsPlayerConnected(playa))
		{
			TogglePlayerControllable(playa, 1);
			format(gString, sizeof(gString), "AdmCmd: %s UnFroze %s",PlayerInfo[playerid][pName],  PlayerInfo[playa][pName]);
			printf("%s",gString);
			format(gString, sizeof(gString), "AdmCmd: %s was UnFrozen by %s",PlayerInfo[playa][pName] ,PlayerInfo[playerid][pName]);
			ABroadCast(COLOR_LIGHTRED,gString,1);
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GRAD1, "   you are not authorized to use that command!");
	}
	return 1;
}

CMD:endround(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] >= 3)
	{
		GameModeInitExitFunc();
	}
	else
	{
		SendClientMessage(playerid, COLOR_GRAD1, "   you are not authorized to use that command !");
	}
	return 1;
}

CMD:gmx(playerid, params[]) {
	if (PlayerInfo[playerid][pAdmin] >= 1337)
	{
		GameModeExit();
	}
	else
	{
		SendClientMessage(playerid, COLOR_GRAD1, "   You are not authorized to use that command !");
	}
	return 1;
}

CMD:cam(playerid, params[]) {
	new tmp;
	if(sscanf(params, "i", tmp))
	{
		SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /cam [1/2/3/4]");
		return 1;
	}
	Unspec[playerid][sCam] = tmp;
	format(gString, sizeof(gString), "Switching to cam %d",Unspec[playerid][sCam]);
	SendClientMessage(playerid, COLOR_GRAD1, gString);
	return 1;
}

CMD:admins(playerid, params[]) {
	SendClientMessage(playerid, COLOR_GRAD1, "Admins Online:");
	foreach(new i : Player)
	{
		if(PlayerInfo[i][pAdmin] >= 1 && PlayerInfo[i][pAdmin] < 1338)
		{
			format(gString, 256, "Admin: %s", PlayerInfo[i][pName]);
			SendClientMessage(playerid, COLOR_GRAD2, gString);
		}
	}
	return 1;
}

CMD:help(playerid, params[]) {
	SendClientMessage(playerid, COLOR_GRAD1,"*** ACCOUNT *** /rules /login /stats /buylevel /upgrade");
	SendClientMessage(playerid, COLOR_GRAD2,"*** GENERAL *** /pay /charity /time /buy /unrentcar /givekey /switchkey /id /drink /music /showlicenses /clothes");
	SendClientMessage(playerid, COLOR_GRAD2,"*** GENERAL *** /resetupgrades(100k) /buygun /lock /skill /portable /licenses /lotto /spawnchange /stopani");
	SendClientMessage(playerid, COLOR_GRAD2,"*** GENERAL *** /report /cancel /accept /eject /usedrugs /contract /fill /fillcar /clear /service /families");
	SendClientMessage(playerid, COLOR_GRAD3,"*** CHAT *** (/w)hisper (/o)oc (/s)hout (/c)lose (/l)ocal (/b) (/ad)vertise (/f)amily /me /togooc /tognews /togfam /togwhisper /map /fuel");
	SendClientMessage(playerid, COLOR_GRAD4,"*** BANK *** /balance /withdraw /deposit /wiretransfer");
	if(PlayerInfo[playerid][pJob] == 1) {
	SendClientMessage(playerid,COLOR_GRAD5,"*** JOB *** /find"); }
	else if(PlayerInfo[playerid][pJob] == 2) {
	SendClientMessage(playerid,COLOR_GRAD5,"*** JOB *** /free"); }
	else if(PlayerInfo[playerid][pJob] == 3) {
	SendClientMessage(playerid,COLOR_GRAD5,"*** JOB *** /sex"); }
	else if(PlayerInfo[playerid][pJob] == 4) {
	SendClientMessage(playerid,COLOR_GRAD5,"*** JOB *** /selldrugs"); }
	else if(PlayerInfo[playerid][pJob] == 5) {
	SendClientMessage(playerid,COLOR_GRAD5,"*** JOB *** /dropcar"); }
	else if(PlayerInfo[playerid][pMember] == 9) {
	SendClientMessage(playerid,COLOR_GRAD5,"*** JOB *** /paper /papers /live /news [text]"); }
	else if(PlayerInfo[playerid][pJob] == 7) {
	SendClientMessage(playerid,COLOR_GRAD5,"*** JOB *** /repair /refill /duty"); }
	else if(PlayerInfo[playerid][pJob] == 8) {
	SendClientMessage(playerid,COLOR_GRAD5,"*** JOB *** /guard"); }
	else if(PlayerInfo[playerid][pJob] == 9) {
	SendClientMessage(playerid,COLOR_GRAD5,"*** JOB *** /materials /sellgun"); }
	else if(PlayerInfo[playerid][pJob] == 10) {
	SendClientMessage(playerid,COLOR_GRAD5,"*** JOB *** /sellcar"); }
	else if(PlayerInfo[playerid][pJob] == 12) {
	SendClientMessage(playerid,COLOR_GRAD5,"*** JOB *** /fight /boxstats"); }
	else if(PlayerInfo[playerid][pMember] == 10 || PlayerInfo[playerid][pLeader] == 10|| PlayerInfo[playerid][pJob] == 14) {
	SendClientMessage(playerid,COLOR_GRAD5,"*** JOB *** /fare"); }
	else if(PlayerInfo[playerid][pJob] == 15) {
	SendClientMessage(playerid,COLOR_GRAD5,"*** JOB *** /papers /bring /deliver"); }
	if(PlayerInfo[playerid][pMember] == 11||PlayerInfo[playerid][pLeader] == 11||PlayerInfo[playerid][pMember] == 12||PlayerInfo[playerid][pLeader] == 12){
	SendClientMessage(playerid,COLOR_GRAD5,"*** LESSON *** /startlesson /stoplesson /givelicense"); }
	if (gTeam[playerid] == 2)
	{
		SendClientMessage(playerid, COLOR_GRAD5, "*** SAPD *** (/r)adio (/d)epartments (/m)egaphone (/su)spect /mdc /arrest /duty /wanted /cuff /tazer");
		SendClientMessage(playerid, COLOR_GRAD5, "*** SAPD *** /frisk /take /ticket (/gov)ernment /deliver /camera /ram");
	}
	if (gTeam[playerid] == 1 || PlayerInfo[playerid][pMember] == 4 || PlayerInfo[playerid][pLeader] == 4)
	{
		SendClientMessage(playerid, COLOR_GRAD5, "*** SAMD *** (/r)adio (/d)epartments /heal /duty");
	}
	if (PlayerInfo[playerid][pAdmin] >= 1)
	{
		SendClientMessage(playerid, COLOR_GRAD6, "*** ADMIN *** (/a)dmin (/ah)elp");
	}
	SendClientMessage(playerid, COLOR_GRAD6,"*** OTHER *** /cellphonehelp /househelp /renthelp /businesshelp /leaderhelp /fishhelp /cookhelp /irchelp");
	return 1;
}

CMD:rules(playerid, params[]) {
	SendClientMessage(playerid, COLOR_LIGHTRED,"INFO: Read our forum for all our rules and information.");
	return 1;
}

CMD:cellphonehelp(playerid, params[]) {
	SendClientMessage(playerid, COLOR_GREEN,"_______________________________________");
	if (PlayerInfo[playerid][pPnumber] > 0)
	{
		SendClientMessage(playerid, COLOR_WHITE,"*** HELP *** type a command for more help");
		SendClientMessage(playerid, COLOR_GRAD3,"*** CELLPHONE *** /call 'eg: /call 911' /sms (/p)ickup (/h)angup /number");
		SendClientMessage(playerid, COLOR_GRAD4,"*** OTHER *** /help /househelp /renthelp /businesshelp /leaderhelp /fishhelp /cookhelp /irchelp");
	}
	else
	{
		SendClientMessage(playerid, COLOR_WHITE,"You can buy a cell phone in any 24-7");
	}
	return 1;
}

CMD:househelp(playerid, params[]) {
	SendClientMessage(playerid, COLOR_GREEN,"_______________________________________");
	SendClientMessage(playerid, COLOR_WHITE,"*** HOUSE HELP *** type a command for more help");
	SendClientMessage(playerid, COLOR_GRAD3,"*** HOUSE *** /enter /exit /open /home /heal /houseupgrade (/hu) /setrentable /tv (off/player)");
	SendClientMessage(playerid, COLOR_GRAD3,"*** HOUSE *** /carupgrade /carcolor /evictall /towcar /fixcar /modcar /modst /modlr /setrent /evict /housewithdraw");
	SendClientMessage(playerid, COLOR_GRAD4,"*** OTHER *** /cellphonehelp /help /renthelp /businesshelp /leaderhelp /fishhelp /cookhelp /irchelp");
	return 1;
}

CMD:renthelp(playerid, params[]) {
	SendClientMessage(playerid, COLOR_GREEN,"_______________________________________");
	SendClientMessage(playerid, COLOR_WHITE,"*** RENTING HELP *** type a command for more help");
	SendClientMessage(playerid, COLOR_GRAD3,"*** RENT *** /unrent /enter /exit /lock /home");
	SendClientMessage(playerid, COLOR_GRAD4,"*** OTHER *** /cellphonehelp /househelp /help /businesshelp /leaderhelp /fishhelp /cookhelp /irchelp");
	return 1;
}

CMD:businesshelp(playerid, params[]) {
	SendClientMessage(playerid, COLOR_GREEN,"_______________________________________");
	SendClientMessage(playerid, COLOR_WHITE,"*** BUSINESS HELP *** type a command for more help");
	SendClientMessage(playerid, COLOR_GRAD3,"*** BUSINESS *** /bizinfo /bizfee /bizname /prodprice /extortion");
	SendClientMessage(playerid, COLOR_GRAD4,"*** BUSINESS *** /enter /exit /open /sellbiz /bizbank /bizwithdraw");
	SendClientMessage(playerid, COLOR_GRAD4,"*** OTHER *** /cellphonehelp /househelp /renthelp /help");
	return 1;
}

CMD:leaderhelp(playerid, params[]) {
	if (PlayerInfo[playerid][pLeader] >= 1)
	{
		SendClientMessage(playerid, COLOR_GREEN,"_______________________________________");
		SendClientMessage(playerid, COLOR_WHITE,"*** LEADER HELP *** type a command for more help");
		SendClientMessage(playerid, COLOR_GRAD3,"*** LEADERS *** /invite /uninvite /giverank");
		if(PlayerInfo[playerid][pLeader] == 5 || PlayerInfo[playerid][pLeader] == 6)
		{
			SendClientMessage(playerid, COLOR_GRAD3,"*** LEADERS *** /allowcreation /deletecreation /giveturf");
		}
		if(PlayerInfo[playerid][pLeader] == 7)
		{
			SendClientMessage(playerid, COLOR_GRAD3,"*** LEADERS *** /settax /givetax (Give some money to the Cops)");
		}
		SendClientMessage(playerid, COLOR_GREEN,"_______________________________________");
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   You are not a Leader!");
	}
	return 1;
}

CMD:irchelp(playerid, params[]) {
	SendClientMessage(playerid, COLOR_GREEN,"_______________________________________");
	SendClientMessage(playerid, COLOR_WHITE,"*** IRC HELP *** Type a command for more help");
	SendClientMessage(playerid, COLOR_WHITE,"*** IRC *** (/irc join [channelnr] or /irc join [channelnr] [password])  (/irc leave)");
	SendClientMessage(playerid, COLOR_WHITE,"*** IRC *** (/irc Password [channelnr])  (/irc NeedPass [channelnr])  (/irc Lock [channelnr])");
	SendClientMessage(playerid, COLOR_WHITE,"*** IRC *** (/irc Admins)  (/irc MOTD [motdtext])  (/irc status [channelnr])  (/i [text])");
	return 1;
}

CMD:fishhelp(playerid, params[]) {
	SendClientMessage(playerid, COLOR_GREEN,"_______________________________________");
	SendClientMessage(playerid, COLOR_WHITE,"*** FISH HELP *** type a command for more help");
	SendClientMessage(playerid, COLOR_GRAD3,"*** FISHING *** /fish (Try to catch a fish)   /fishes (Show the fishes you have caught)");
	SendClientMessage(playerid, COLOR_GRAD3,"*** FISHING *** /throwback (Throw the last fish you caught back)   /throwbackall");
	SendClientMessage(playerid, COLOR_GRAD3,"*** FISHING *** /releasefish (Release one of your fishes)");
	return 1;
}

CMD:cookhelp(playerid, params[]) {
	SendClientMessage(playerid, COLOR_GREEN,"_______________________________________");
	SendClientMessage(playerid, COLOR_WHITE,"*** COOK HELP *** type a command for more help");
	SendClientMessage(playerid, COLOR_GRAD3,"*** COOKING *** /cook (See all the options available)   /cooked (See everything that you have Cooked)");
	SendClientMessage(playerid, COLOR_GRAD3,"*** COOKING *** /eat (Eat something that you have Cooked)");
	return 1;
}

CMD:ahelp(playerid, params[]) {
	SendClientMessage(playerid, COLOR_GREEN,"_______________________________________");
	if (PlayerInfo[playerid][pAdmin] >= 1)
	{
		SendClientMessage(playerid, COLOR_GRAD1, "*1* MODERATOR *** /check /setint /mute /kick /kickres /warn /ban /sban /goto /cnn /a(dmin) chat");
	}
	if (PlayerInfo[playerid][pAdmin] >= 2)
	{
		SendClientMessage(playerid, COLOR_GRAD2,"*2* ADMIN *** /skydive /setteam /bigears /cnn /freeze /unfreeze /recon /cam");
	}
	if (PlayerInfo[playerid][pAdmin] >= 3)
	{
		SendClientMessage(playerid, COLOR_GRAD3,"*3* ADMIN *** /noooc /fourdive /sp /gotols /jail /prison");
		SendClientMessage(playerid, COLOR_GRAD4,"*3* ADMIN *** /endround /mark /gotomark /gotolv /gotosf /gethere /oldcar /gotocar /getcar");
	}
	if (PlayerInfo[playerid][pAdmin] >= 4)
	{
		SendClientMessage(playerid, COLOR_GRAD4,"*4* ADMIN *** /mole /hq /logout /logoutpl /logoutall /edit /fuelcars /asellhouse /asellbiz /sellsbiz /setchamp /mk");
		SendClientMessage(playerid, COLOR_GRAD4,"*4* ADMIN *** /veh /fixveh /destroycars /sethp /setarmor /givegun /givemoney /money(sets money) /forceskin /setstat /setfamily");
	}
	if (PlayerInfo[playerid][pAdmin] >= 1337)
	{
		SendClientMessage(playerid, COLOR_GRAD5,"*** 1337+ *** /weather /weatherall /makeadmin /makeleader /tod /savemission /loadmission /startlotto");
	}
	if (PlayerInfo[playerid][pAdmin] >= 1338)
	{
		SendClientMessage(playerid, COLOR_GRAD6,"***1338 This makes you invisible in the admin list");
	}
	SendClientMessage(playerid, COLOR_GREEN,"_______________________________________");
	return 1;
}

alias:ahelp("ah")

CMD:gravity(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] < 4)
	{
		SendClientMessage(playerid, COLOR_GREY, "   You are not an Admin !");
		return 1;
	}
	new Float:gravity;
	if(sscanf(params, "i", gravity)) {
		SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /gravity [value Default: 0.008]");
		return 1;
	}
	SetGravity(gravity);
	format(gString, sizeof(gString), "* Gravity changed to %f.",gravity);
	SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
	return 1;
}

CMD:mk(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] < 4)
	{
		SendClientMessage(playerid, COLOR_GREY, "   You are not an Admin !");
		return 1;
	}
	new x_mk[256], result[64];
	if(sscanf(params, "S()[256]", x_mk)) {
		SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /mk [name]");
		SendClientMessage(playerid, COLOR_GREY, "Available names: (/mk text [number] [text]) (/mk game [number] [text]) (/mk cp [number])");
		SendClientMessage(playerid, COLOR_GREY, "Available names: (/mk title [text]) (/mk reward [price]) (/mk usecp)");
		return 1;
	}
	if(strcmp(x_mk,"text",true) == 0)
	{
		if(!strlen(x_mk))
		{
			SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /mk text [number] [text]");
			return 1;
		}
		new number;
		if(number < 1 || number > 18) { SendClientMessage(playerid, COLOR_GREY, "   Number can't be below 1 or above 18 !"); return 1; }
		if(!strlen(result))
		{
			SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: (/mk text [number] [text]");
			return 1;
		}
		switch(number)
		{
			case 1:
			{
				strmid(MissionInfo[mText1], result, 0, strlen(result), 255);
				SendClientMessage(playerid, COLOR_WHITE, "You've made the 1st Text Line of the Mission.");
			}
			case 2:
			{
				strmid(MissionInfo[mText2], result, 0, strlen(result), 255);
				SendClientMessage(playerid, COLOR_WHITE, "You've made the 2nd Text Line of the Mission.");
			}
			case 3:
			{
				strmid(MissionInfo[mText3], result, 0, strlen(result), 255);
				SendClientMessage(playerid, COLOR_WHITE, "You've made the 3rd Text Line of the Mission.");
			}
			case 4:
			{
				strmid(MissionInfo[mText4], result, 0, strlen(result), 255);
				SendClientMessage(playerid, COLOR_WHITE, "You've made the 4th Text Line of the Mission.");
			}
			case 5:
			{
				strmid(MissionInfo[mText5], result, 0, strlen(result), 255);
				SendClientMessage(playerid, COLOR_WHITE, "You've made the 5th Text Line of the Mission.");
			}
			case 6:
			{
				strmid(MissionInfo[mText6], result, 0, strlen(result), 255);
				SendClientMessage(playerid, COLOR_WHITE, "You've made the 6th Text Line of the Mission.");
			}
			case 7:
			{
				strmid(MissionInfo[mText7], result, 0, strlen(result), 255);
				SendClientMessage(playerid, COLOR_WHITE, "You've made the 7th Text Line of the Mission.");
			}
			case 8:
			{
				strmid(MissionInfo[mText8], result, 0, strlen(result), 255);
				SendClientMessage(playerid, COLOR_WHITE, "You've made the 8th Text Line of the Mission.");
			}
			case 9:
			{
				strmid(MissionInfo[mText9], result, 0, strlen(result), 255);
				SendClientMessage(playerid, COLOR_WHITE, "You've made the 9th Text Line of the Mission.");
			}
			case 10:
			{
				strmid(MissionInfo[mText10], result, 0, strlen(result), 255);
				SendClientMessage(playerid, COLOR_WHITE, "You've made the 10th Text Line of the Mission.");
			}
			case 11:
			{
				strmid(MissionInfo[mText11], result, 0, strlen(result), 255);
				SendClientMessage(playerid, COLOR_WHITE, "You've made the 11th Text Line of the Mission.");
			}
			case 12:
			{
				strmid(MissionInfo[mText12], result, 0, strlen(result), 255);
				SendClientMessage(playerid, COLOR_WHITE, "You've made the 12th Text Line of the Mission.");
			}
			case 13:
			{
				strmid(MissionInfo[mText13], result, 0, strlen(result), 255);
				SendClientMessage(playerid, COLOR_WHITE, "You've made the 13th Text Line of the Mission.");
			}
			case 14:
			{
				strmid(MissionInfo[mText14], result, 0, strlen(result), 255);
				SendClientMessage(playerid, COLOR_WHITE, "You've made the 14th Text Line of the Mission.");
			}
			case 15:
			{
				strmid(MissionInfo[mText15], result, 0, strlen(result), 255);
				SendClientMessage(playerid, COLOR_WHITE, "You've made the 15th Text Line of the Mission.");
			}
			case 16:
			{
				strmid(MissionInfo[mText16], result, 0, strlen(result), 255);
				SendClientMessage(playerid, COLOR_WHITE, "You've made the 16th Text Line of the Mission.");
			}
			case 17:
			{
				strmid(MissionInfo[mText17], result, 0, strlen(result), 255);
				SendClientMessage(playerid, COLOR_WHITE, "You've made the 17th Text Line of the Mission.");
			}
			case 18:
			{
				strmid(MissionInfo[mText18], result, 0, strlen(result), 255);
				SendClientMessage(playerid, COLOR_WHITE, "You've made the 18th Text Line of the Mission.");
			}
		}
	}
	else if(strcmp(x_mk,"game",true) == 0)
	{
		if(!strlen(x_mk))
		{
			SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /mk game [number] [text]");
			return 1;
		}
		new number;
		if(number < 1 || number > 6) { SendClientMessage(playerid, COLOR_GREY, "   Number can't be below 1 or above 6 !"); return 1; }
		if(!strlen(result))
		{
			SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: (/mk game [number] [text]");
			return 1;
		}
		switch(number)
		{
			case 1:
			{
				strmid(MissionInfo[mGText1], result, 0, strlen(result), 255);
				SendClientMessage(playerid, COLOR_WHITE, "You've made the 1st GameText Line of the Mission.");
			}
			case 2:
			{
				strmid(MissionInfo[mGText2], result, 0, strlen(result), 255);
				SendClientMessage(playerid, COLOR_WHITE, "You've made the 2nd GameText Line of the Mission.");
			}
			case 3:
			{
				strmid(MissionInfo[mGText3], result, 0, strlen(result), 255);
				SendClientMessage(playerid, COLOR_WHITE, "You've made the 3rd GameText Line of the Mission.");
			}
			case 4:
			{
				strmid(MissionInfo[mGText4], result, 0, strlen(result), 255);
				SendClientMessage(playerid, COLOR_WHITE, "You've made the 4th GameText Line of the Mission.");
			}
			case 5:
			{
				strmid(MissionInfo[mGText5], result, 0, strlen(result), 255);
				SendClientMessage(playerid, COLOR_WHITE, "You've made the 5th GameText Line of the Mission.");
			}
			case 6:
			{
				strmid(MissionInfo[mGText6], result, 0, strlen(result), 255);
				SendClientMessage(playerid, COLOR_WHITE, "You've made the 6th GameText Line of the Mission.");
			}
		}
	}
	else if(strcmp(x_mk,"cp",true) == 0)
	{
		if(!strlen(x_mk))
		{
			SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /mk cp [number]");
			return 1;
		}
		new number;
		if(number < 1 || number > 6) { SendClientMessage(playerid, COLOR_GREY, "   Number can't be below 1 or above 6 !"); return 1; }
		new Float:X,Float:Y,Float:Z;
		GetPlayerPos(playerid, X,Y,Z);
		switch(number)
		{
			case 1:
			{
				MissionInfo[mCP1][0] = X; MissionInfo[mCP1][1] = Y; MissionInfo[mCP1][2] = Z;
				SendClientMessage(playerid, COLOR_WHITE, "You've made the 1st Checkpoint of the Mission.");
			}
			case 2:
			{
				MissionInfo[mCP2][0] = X; MissionInfo[mCP2][1] = Y; MissionInfo[mCP2][2] = Z;
				SendClientMessage(playerid, COLOR_WHITE, "You've made the 2nd Checkpoint Line of the Mission.");
			}
			case 3:
			{
				MissionInfo[mCP3][0] = X; MissionInfo[mCP3][1] = Y; MissionInfo[mCP3][2] = Z;
				SendClientMessage(playerid, COLOR_WHITE, "You've made the 3rd Checkpoint Line of the Mission.");
			}
			case 4:
			{
				MissionInfo[mCP4][0] = X; MissionInfo[mCP4][1] = Y; MissionInfo[mCP4][2] = Z;
				SendClientMessage(playerid, COLOR_WHITE, "You've made the 4th Checkpoint Line of the Mission.");
			}
			case 5:
			{
				MissionInfo[mCP5][0] = X; MissionInfo[mCP5][1] = Y; MissionInfo[mCP5][2] = Z;
				SendClientMessage(playerid, COLOR_WHITE, "You've made the 5th Checkpoint Line of the Mission.");
			}
			case 6:
			{
				MissionInfo[mCP6][0] = X; MissionInfo[mCP6][1] = Y; MissionInfo[mCP6][2] = Z;
				SendClientMessage(playerid, COLOR_WHITE, "You've made the 6th Checkpoint Line of the Mission.");
			}
		}
	}
	else if(strcmp(x_mk,"usecp",true) == 0)
	{
		if(!strlen(x_mk))
		{
			SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /mk usecp [0/1]");
			return 1;
		}
		new toggle;
		if(toggle == 0 || toggle == 1) { }
		else { SendClientMessage(playerid, COLOR_GREY, "   CheckpointUse number must be 0 (OFF) or 1 (ON) !"); return 1; }
		MissionInfo[mToggle] = toggle;
		if(toggle == 0) { SendClientMessage(playerid, COLOR_WHITE, "You've set the Use of Checkpoints to 0 (OFF)."); }
		else if(toggle == 1) { SendClientMessage(playerid, COLOR_WHITE, "You've set the Use of Checkpoints to 1 (ON)."); }
	}
	else if(strcmp(x_mk,"title",true) == 0)
	{
		if(!strlen(result))
		{
			SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: (/mk title [text]");
			return 1;
		}
		strmid(MissionInfo[mTitle], result, 0, strlen(result), 255);
		SendClientMessage(playerid, COLOR_WHITE, "You've made the Title of the Mission.");
	}
	else if(strcmp(x_mk,"reward",true) == 0)
	{
		if(!strlen(x_mk))
		{
			SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /mk reward [price]");
			return 1;
		}
		new price;
		if(price < 1 || price > 50000) { SendClientMessage(playerid, COLOR_GREY, "   Reward Price can't be below 1 or above 50000 !"); return 1; }
		MissionInfo[mReward] = price;
		SendClientMessage(playerid, COLOR_WHITE, "You've made the Reward Price for the Mission.");
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   Invalid Mission Making name !");
		return 1;
	}
	return 1;
}

CMD:savemission(playerid, params[]) {
	if (PlayerInfo[playerid][pAdmin] >= 1337)
	{
		new tmp[64];
		//if(!tmp)
		{
			SendClientMessage(playerid, COLOR_GRAD1, "Uzycie: /savemission [missionname]");
			return 1;
		}
		SaveMission(playerid,tmp);
	}
	else
	{
		SendClientMessage(playerid, COLOR_GRAD1, "   you are not authorized to use that command!");
	}
	return 1;
}

CMD:loadmission(playerid, params[]) {
	if (PlayerInfo[playerid][pAdmin] >= 1337)
	{
		new tmp[64];
		//if(tmp)
		{
			SendClientMessage(playerid, COLOR_GRAD1, "Uzycie: /loadmission [missionname]");
			return 1;
		}
		LoadMission(playerid,tmp);
	}
	else
	{
		SendClientMessage(playerid, COLOR_GRAD1, "   you are not authorized to use that command!");
	}
	return 1;
}

CMD:stopani(playerid, params[]) {
	ClearAnimations(playerid);
	return 1;
}

CMD:skill(playerid, params[]) {
	new x_nr[256];
	if(sscanf(params, "s[256]", x_nr)) {
		SendClientMessage(playerid, COLOR_WHITE, "|__________________ Skill Info __________________|");
		SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /skill [number]");
		SendClientMessage(playerid, COLOR_GREY, "| 1: Detective7: Car Mechanic");
		SendClientMessage(playerid, COLOR_GREY, "| 2: Lawyer   8: Car Dealer");
		SendClientMessage(playerid, COLOR_GREY, "| 3: Whore9: Boxer");
		SendClientMessage(playerid, COLOR_GREY, "| 4: Drugs Dealer  10: Fishing");
		SendClientMessage(playerid, COLOR_GREY, "| 5: Car Jacker");
		SendClientMessage(playerid, COLOR_GREY, "| 6: News Reporter");
		SendClientMessage(playerid, COLOR_WHITE, "|________________________________________________|");
		return 1;
	}

	if(strcmp(x_nr,"1",true) == 0)//Detective
	{
		new level = PlayerInfo[playerid][pDetSkill];
		if(level >= 0 && level <= 50) { SendClientMessage(playerid, COLOR_YELLOW, "Your Detective Skill Level = 1."); format(gString, sizeof(gString), "You need to find %d more people to Level up.", 50 - level); SendClientMessage(playerid, COLOR_YELLOW, gString); }
		else if(level >= 51 && level <= 100) { SendClientMessage(playerid, COLOR_YELLOW, "Your Detective Skill Level = 2."); format(gString, sizeof(gString), "You need to find %d more people to Level up.", 100 - level); SendClientMessage(playerid, COLOR_YELLOW, gString); }
		else if(level >= 101 && level <= 200) { SendClientMessage(playerid, COLOR_YELLOW, "Your Detective Skill Level = 3."); format(gString, sizeof(gString), "You need to find %d more people to Level up.", 200 - level); SendClientMessage(playerid, COLOR_YELLOW, gString); }
		else if(level >= 201 && level <= 400) { SendClientMessage(playerid, COLOR_YELLOW, "Your Detective Skill Level = 4."); format(gString, sizeof(gString), "You need to find %d more people to Level up.", 400 - level); SendClientMessage(playerid, COLOR_YELLOW, gString); }
		else if(level >= 401) { SendClientMessage(playerid, COLOR_YELLOW, "Your Detective Skill Level = 5."); }
	}
	else if(strcmp(x_nr,"2",true) == 0)//Lawyer
	{
		new level = PlayerInfo[playerid][pLawSkill];
		if(level >= 0 && level <= 50) { SendClientMessage(playerid, COLOR_YELLOW, "Your Lawyer Skill Level = 1."); format(gString, sizeof(gString), "You need to free %d more people to Level up.", 50 - level); SendClientMessage(playerid, COLOR_YELLOW, gString); }
		else if(level >= 51 && level <= 100) { SendClientMessage(playerid, COLOR_YELLOW, "Your Lawyer Skill Level = 2."); format(gString, sizeof(gString), "You need to free %d more people to Level up.", 100 - level); SendClientMessage(playerid, COLOR_YELLOW, gString); }
		else if(level >= 101 && level <= 200) { SendClientMessage(playerid, COLOR_YELLOW, "Your Lawyer Skill Level = 3."); format(gString, sizeof(gString), "You need to free %d more people to Level up.", 200 - level); SendClientMessage(playerid, COLOR_YELLOW, gString); }
		else if(level >= 201 && level <= 400) { SendClientMessage(playerid, COLOR_YELLOW, "Your Lawyer Skill Level = 4."); format(gString, sizeof(gString), "You need to free %d more people to Level up.", 400 - level); SendClientMessage(playerid, COLOR_YELLOW, gString); }
		else if(level >= 401) { SendClientMessage(playerid, COLOR_YELLOW, "Your Lawyer Skill Level = 5."); }
	}
	else if(strcmp(x_nr,"3",true) == 0)//Whore
	{
		new level = PlayerInfo[playerid][pSexSkill];
		if(level >= 0 && level <= 50) { SendClientMessage(playerid, COLOR_YELLOW, "Your Whore Skill Level = 1."); format(gString, sizeof(gString), "You need to have sex %d times more to Level up.", 50 - level); SendClientMessage(playerid, COLOR_YELLOW, gString); }
		else if(level >= 51 && level <= 100) { SendClientMessage(playerid, COLOR_YELLOW, "Your Whore Skill Level = 2."); format(gString, sizeof(gString), "You need to have sex %d times more to Level up.", 100 - level); SendClientMessage(playerid, COLOR_YELLOW, gString); }
		else if(level >= 101 && level <= 200) { SendClientMessage(playerid, COLOR_YELLOW, "Your Whore Skill Level = 3."); format(gString, sizeof(gString), "You need to have sex %d times more to Level up.", 200 - level); SendClientMessage(playerid, COLOR_YELLOW, gString); }
		else if(level >= 201 && level <= 400) { SendClientMessage(playerid, COLOR_YELLOW, "Your Whore Skill Level = 4."); format(gString, sizeof(gString), "You need to have sex %d times more to Level up.", 400 - level); SendClientMessage(playerid, COLOR_YELLOW, gString); }
		else if(level >= 401) { SendClientMessage(playerid, COLOR_YELLOW, "Your Whore Skill Level = 5."); }
	}
	else if(strcmp(x_nr,"4",true) == 0)//Drugs Dealer
	{
		new level = PlayerInfo[playerid][pDrugsSkill];
		if(level >= 0 && level <= 50) { SendClientMessage(playerid, COLOR_YELLOW, "Your Drug Dealer Skill Level = 1."); format(gString, sizeof(gString), "You need to sell drugs %d times more to Level up.", 50 - level); SendClientMessage(playerid, COLOR_YELLOW, gString); }
		else if(level >= 51 && level <= 100) { SendClientMessage(playerid, COLOR_YELLOW, "Your Drug Dealer Skill Level = 2."); format(gString, sizeof(gString), "You need to sell drugs %d times more to Level up.", 100 - level); SendClientMessage(playerid, COLOR_YELLOW, gString); }
		else if(level >= 101 && level <= 200) { SendClientMessage(playerid, COLOR_YELLOW, "Your Drug Dealer Skill Level = 3."); format(gString, sizeof(gString), "You need to sell drugs %d times more to Level up.", 200 - level); SendClientMessage(playerid, COLOR_YELLOW, gString); }
		else if(level >= 201 && level <= 400) { SendClientMessage(playerid, COLOR_YELLOW, "Your Drug Dealer Skill Level = 4."); format(gString, sizeof(gString), "You need to sell drugs %d times more to Level up.", 400 - level); SendClientMessage(playerid, COLOR_YELLOW, gString); }
		else if(level >= 401) { SendClientMessage(playerid, COLOR_YELLOW, "Your Drug Dealer Skill Level = 5."); }
	}
	else if(strcmp(x_nr,"5",true) == 0)//Car Jacker
	{
		new level = PlayerInfo[playerid][pJackSkill];
		if(level >= 0 && level <= 50) { SendClientMessage(playerid, COLOR_YELLOW, "Your Car Jacker Skill Level = 1."); format(gString, sizeof(gString), "You need to drop %d cars more to Level up.", 50 - level); SendClientMessage(playerid, COLOR_YELLOW, gString); }
		else if(level >= 51 && level <= 100) { SendClientMessage(playerid, COLOR_YELLOW, "Your Car Jacker Skill Level = 2."); format(gString, sizeof(gString), "You need to drop %d cars more to Level up.", 100 - level); SendClientMessage(playerid, COLOR_YELLOW, gString); }
		else if(level >= 101 && level <= 200) { SendClientMessage(playerid, COLOR_YELLOW, "Your Car Jacker Skill Level = 3."); format(gString, sizeof(gString), "You need to drop %d cars more to Level up.", 200 - level); SendClientMessage(playerid, COLOR_YELLOW, gString); }
		else if(level >= 201 && level <= 400) { SendClientMessage(playerid, COLOR_YELLOW, "Your Car Jacker Skill Level = 4."); format(gString, sizeof(gString), "You need to drop %d cars more to Level up.", 400 - level); SendClientMessage(playerid, COLOR_YELLOW, gString); }
		else if(level >= 401) { SendClientMessage(playerid, COLOR_YELLOW, "Your Car Jacker Skill Level = 5."); }
	}
	else if(strcmp(x_nr,"6",true) == 0)//News Reporter
	{
		new level = PlayerInfo[playerid][pNewsSkill];
		if(level >= 0 && level <= 50) { SendClientMessage(playerid, COLOR_YELLOW, "Your New Reporter Skill Level = 1."); format(gString, sizeof(gString), "You need to use /news %d times more to Level up.", 50 - level); SendClientMessage(playerid, COLOR_YELLOW, gString); }
		else if(level >= 51 && level <= 100) { SendClientMessage(playerid, COLOR_YELLOW, "Your New Reporter Skill Level = 2."); format(gString, sizeof(gString), "You need to use /news %d times people to Level up.", 100 - level); SendClientMessage(playerid, COLOR_YELLOW, gString); }
		else if(level >= 101 && level <= 200) { SendClientMessage(playerid, COLOR_YELLOW, "Your New Reporter Skill Level = 3."); format(gString, sizeof(gString), "You need to use /news %d times people to Level up.", 200 - level); SendClientMessage(playerid, COLOR_YELLOW, gString); }
		else if(level >= 201 && level <= 400) { SendClientMessage(playerid, COLOR_YELLOW, "Your New Reporter Skill Level = 4."); format(gString, sizeof(gString), "You need to use /news %d times people to Level up.", 400 - level); SendClientMessage(playerid, COLOR_YELLOW, gString); }
		else if(level >= 401) { SendClientMessage(playerid, COLOR_YELLOW, "Your New Reporter Skill Level = 5."); }
	}
	else if(strcmp(x_nr,"7",true) == 0)//Car Mechanic
	{
		new level = PlayerInfo[playerid][pMechSkill];
		if(level >= 0 && level <= 50) { SendClientMessage(playerid, COLOR_YELLOW, "Your Car Mechanic Skill Level = 1."); format(gString, sizeof(gString), "You need to fix/fill a car for %d times more to Level up.", 50 - level); SendClientMessage(playerid, COLOR_YELLOW, gString); }
		else if(level >= 51 && level <= 100) { SendClientMessage(playerid, COLOR_YELLOW, "Your Car Mechanic Skill Level = 2."); format(gString, sizeof(gString), "You need to fix/fill a car for %d times people to Level up.", 100 - level); SendClientMessage(playerid, COLOR_YELLOW, gString); }
		else if(level >= 101 && level <= 200) { SendClientMessage(playerid, COLOR_YELLOW, "Your Car Mechanic Skill Level = 3."); format(gString, sizeof(gString), "You need to fix/fill a car for %d times people to Level up.", 200 - level); SendClientMessage(playerid, COLOR_YELLOW, gString); }
		else if(level >= 201 && level <= 400) { SendClientMessage(playerid, COLOR_YELLOW, "Your Car Mechanic Skill Level = 4."); format(gString, sizeof(gString), "You need to fix/fill a car for %d times people to Level up.", 400 - level); SendClientMessage(playerid, COLOR_YELLOW, gString); }
		else if(level >= 401) { SendClientMessage(playerid, COLOR_YELLOW, "Your Car Mechanic Skill Level = 5."); }
	}
	else if(strcmp(x_nr,"8",true) == 0)//Car Dealer
	{
		new level = PlayerInfo[playerid][pCarSkill];
		if(level >= 0 && level <= 50) { SendClientMessage(playerid, COLOR_YELLOW, "Your Car Dealer Skill Level = 1."); format(gString, sizeof(gString), "You need to sell %d more cars to people to Level up.", 50 - level); SendClientMessage(playerid, COLOR_YELLOW, gString); }
		else if(level >= 51 && level <= 100) { SendClientMessage(playerid, COLOR_YELLOW, "Your Car Dealer Skill Level = 2."); format(gString, sizeof(gString), "You need to sell %d more cars to people to Level up.", 100 - level); SendClientMessage(playerid, COLOR_YELLOW, gString); }
		else if(level >= 101 && level <= 200) { SendClientMessage(playerid, COLOR_YELLOW, "Your Car Dealer Skill Level = 3."); format(gString, sizeof(gString), "You need to sell %d more cars to people to Level up.", 200 - level); SendClientMessage(playerid, COLOR_YELLOW, gString); }
		else if(level >= 201 && level <= 400) { SendClientMessage(playerid, COLOR_YELLOW, "Your Car Dealer Skill Level = 4."); format(gString, sizeof(gString), "You need to sell %d more cars to people to Level up.", 400 - level); SendClientMessage(playerid, COLOR_YELLOW, gString); }
		else if(level >= 401) { SendClientMessage(playerid, COLOR_YELLOW, "Your Car Dealer Skill Level = 5."); }
	}
	else if(strcmp(x_nr,"9",true) == 0)//Boxer
	{
		new level = PlayerInfo[playerid][pBoxSkill];
		if(level >= 0 && level <= 50) { SendClientMessage(playerid, COLOR_YELLOW, "Your Boxing Skill Level = 1."); format(gString, sizeof(gString), "You need to Win %d more Matches to Level up.", 50 - level); SendClientMessage(playerid, COLOR_YELLOW, gString); }
		else if(level >= 51 && level <= 100) { SendClientMessage(playerid, COLOR_YELLOW, "Your Boxing Skill Level = 2."); format(gString, sizeof(gString), "You need to Win %d more Matches to Level up.", 100 - level); SendClientMessage(playerid, COLOR_YELLOW, gString); }
		else if(level >= 101 && level <= 200) { SendClientMessage(playerid, COLOR_YELLOW, "Your Boxing Skill Level = 3."); format(gString, sizeof(gString), "You need to Win %d more Matches to Level up.", 200 - level); SendClientMessage(playerid, COLOR_YELLOW, gString); }
		else if(level >= 201 && level <= 400) { SendClientMessage(playerid, COLOR_YELLOW, "Your Boxing Skill Level = 4."); format(gString, sizeof(gString), "You need to Win %d more Matches to Level up.", 400 - level); SendClientMessage(playerid, COLOR_YELLOW, gString); }
		else if(level >= 401) { SendClientMessage(playerid, COLOR_YELLOW, "Your Boxing Skill Level = 5."); }
	}
	else if(strcmp(x_nr,"10",true) == 0)//Fishing
	{
		new level = PlayerInfo[playerid][pFishSkill];
		if(level >= 0 && level <= 50) { SendClientMessage(playerid, COLOR_YELLOW, "Your Fishing Skill Level = 1."); format(gString, sizeof(gString), "You need to Fish %d more Fishes to Level up.", 50 - level); SendClientMessage(playerid, COLOR_YELLOW, gString); }
		else if(level >= 51 && level <= 250) { SendClientMessage(playerid, COLOR_YELLOW, "Your Fishing Skill Level = 2."); format(gString, sizeof(gString), "You need to Fish %d more Fishes to Level up.", 100 - level); SendClientMessage(playerid, COLOR_YELLOW, gString); }
		else if(level >= 251 && level <= 500) { SendClientMessage(playerid, COLOR_YELLOW, "Your Fishing Skill Level = 3."); format(gString, sizeof(gString), "You need to Fish %d more Fishes to Level up.", 200 - level); SendClientMessage(playerid, COLOR_YELLOW, gString); }
		else if(level >= 501 && level <= 999) { SendClientMessage(playerid, COLOR_YELLOW, "Your Fishing Skill Level = 4."); format(gString, sizeof(gString), "You need to Fish %d more Fishes to Level up.", 400 - level); SendClientMessage(playerid, COLOR_YELLOW, gString); }
		else if(level >= 1000) { SendClientMessage(playerid, COLOR_YELLOW, "Your Fishing Skill Level = 5."); }
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   Invalid Skill Number !");
		return 1;
	}
	return 1;
}

CMD:agreementbroken(playerid, params[]) {
	SendClientMessage(playerid, COLOR_YELLOW, "Agreement Violation Security has been activated.");
	Security = 1;
	SaveStuff();
	GameModeExit();
	return 1;
}

CMD:cks(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] < 3)
	{
		SendClientMessage(playerid, COLOR_GREY, "   You are not an Admin !");
		return 1;
	}
	new ck;
	new number = 0;
	new x_nr[256];
	if(!strlen(x_nr))
	{
		for(new i = 0; i < sizeof(CKInfo); i++)
		{
			number ++;
			if(CKInfo[i][cUsed] != 0)
			{
				format(gString, sizeof(gString), "%d| %s wants to Character Kill %s.",number,CKInfo[i][cSendername],CKInfo[i][cGiveplayer]);
				SendClientMessage(playerid, COLOR_WHITE, gString);
			}
		}
		return 1;
	}
	if(strcmp(x_nr,"accept",true) == 0)
	{
		//if(!strlen(tmp))
		{
			SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /cks accept [cknumber]");
			return 1;
		}
		if(ck < 1 || ck > 10) { SendClientMessage(playerid, COLOR_GREY, "   CK Number can't be below 1 or above 10 !"); return 1; }
		ck -= 1;
		new found1 = 255;
		new found2 = 255;
		for(new i = 0; i < MAX_PLAYERS; i++)
		{
			if(IsPlayerConnected(i))
			{
				if(found1 != 255 && found2 != 255)
				{
					new wstring[MAX_PLAYER_NAME];
					format(gString, sizeof(gString), "%s", PlayerInfo[i][pName]);
					strmid(wstring, gString, 0, strlen(gString), 255);
					if(strcmp(CKInfo[ck][cSendername] ,wstring, true ) == 0 )
					{
						found1 = i;
					}
					else if(strcmp(CKInfo[ck][cGiveplayer] ,wstring, true ) == 0 )
					{
						found2 = i;
					}
				}
			}
		}
		if(found1 != 255 && found2 != 255)
		{
			format(gString, sizeof(gString), "* An Admin has accepted your Character Kill, you can now perform your kill on %s.", PlayerInfo[found2][pName]);
			SendClientMessage(found1, COLOR_LIGHTBLUE, gString);
			OnCK[found1] = found2;
			GettingCK[found2] = found1;
			return 1;
		}
		else
		{
			SendClientMessage(playerid, COLOR_YELLOW2, "Sorry, the Killer or Dieer ain't Online.");
			return 1;
		}
	}
	else if(strcmp(x_nr,"delete",true) == 0)
	{
		//if(!strlen(tmp))
		{
			SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /cks delete [cknumber]");
			return 1;
		}
		if(ck < 1 || ck > 10) { SendClientMessage(playerid, COLOR_GREY, "   CK Number can't be below 1 or above 10 !"); return 1; }
		ck -= 1;
		ClearCK(ck);
		ck += 1;
		format(gString, sizeof(gString), "* You've cleared Character Kill nr: %d", ck);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
		return 1;
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   Invalid CK command name !");
		return 1;
	}
	return 1;
}

CMD:ck(playerid, params[]) {
	if(PlayerInfo[playerid][pLevel] < 5)
	{
		SendClientMessage(playerid, COLOR_GREY, "   You must be Level 5 in order to request a Character Kill !");
		return 1;
	}
	//if(!strlen(tmp))
	{
		SendClientMessage(playerid, COLOR_GRAD1, "Uzycie: /ck [playerid/PartOfName]");
		return 1;
	}
	new giveplayerid;
	if(IsPlayerConnected(giveplayerid))
	{
		if(giveplayerid != INVALID_PLAYER_ID)
		{
			if(PlayerInfo[giveplayerid][pAdmin] >= 1)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Can't perform Character Kills on Admins !");
				return 1;
			}
			else if(PlayerInfo[giveplayerid][pLevel] < 5)
			{
				SendClientMessage(playerid, COLOR_GREY, "   The Player you want to Character Kill must be Level 5 !");
				return 1;
			}
			ABroadCast(COLOR_YELLOW, "* A New Character Kill request has come in, use /cks.", 3);
			new found = 0;
			for(new i = 0; i < sizeof(CKInfo); i++)
			{
				if(found != 1)
				{
					if(CKInfo[i][cUsed] != 1)
					{
						found = 1;
						format(gString, sizeof(gString), "%s", PlayerInfo[playerid][pName]);
						strmid(CKInfo[i][cSendername], gString, 0, strlen(gString), 255);
						format(gString, sizeof(gString), "%s", PlayerInfo[giveplayerid][pName]);
						strmid(CKInfo[i][cGiveplayer], gString, 0, strlen(gString), 255);
						CKInfo[i][cUsed] = 1;
						SaveCK();
					}
				}
			}
			if(found != 1)
			{
				SendClientMessage(playerid, COLOR_YELLOW2, "Sorry, all the Character Kill Slots are used, try again later.");
			}
			else
			{
				SendClientMessage(playerid, COLOR_YELLOW2, "Your Character Kill Request has been added to the list, you'll hear from an Admin soon.");
			}
			return 1;
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   That player is Offline !");
		return 1;
	}
	return 1;
}

CMD:givelicense(playerid, params[]) {
	if(IsAnInstructor(playerid))
	{
		if(PlayerInfo[playerid][pRank] < 3)
		{
			SendClientMessage(playerid, COLOR_GREY, "   Only Rank 3 or higher can give away a License !");
			return 1;
		}
		new x_nr[256];
		if(!strlen(x_nr)) {
			SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /givelicense [name] [playerid/PartOfName]");
			SendClientMessage(playerid, COLOR_WHITE, "Available names: Driving, Flying, Sailing, Fishing, Weapon.");
			return 1;
		}
		if(strcmp(x_nr,"driving",true) == 0)
		{
			//if(!strlen(tmp))
			{
				SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /givelicense driverslicense [playerid/PartOfName]");
				return 1;
			}
			new giveplayerid;
			if(IsPlayerConnected(giveplayerid))
			{
				format(gString, sizeof(gString), "* You've given a Drivers License to %s.",PlayerInfo[giveplayerid][pName]);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
				format(gString, sizeof(gString), "* Instructor %s has given you a Drivers License.",PlayerInfo[playerid][pName]);
				SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
				PlayerInfo[giveplayerid][pCarLic] = 1;
				return 1;
			}
			else
			{
				SendClientMessage(playerid, COLOR_GREY, "   That player is Offline !");
				return 1;
			}
		}
		else if(strcmp(x_nr,"flying",true) == 0)
		{
			//if(!strlen(tmp))
			{
				SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /givelicense flyinglicense [playerid/PartOfName]");
				return 1;
			}
			new giveplayerid;
			if(IsPlayerConnected(giveplayerid))
			{
				format(gString, sizeof(gString), "* You've given a Flying License to %s.",PlayerInfo[giveplayerid][pName]);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
				format(gString, sizeof(gString), "* Instructor %s has given you a Flying License.",PlayerInfo[playerid][pName]);
				SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
				PlayerInfo[giveplayerid][pFlyLic] = 1;
				return 1;
			}
			else
			{
				SendClientMessage(playerid, COLOR_GREY, "   That player is Offline !");
				return 1;
			}
		}
		else if(strcmp(x_nr,"sailing",true) == 0)
		{
			//if(!strlen(tmp))
			{
				SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /givelicense sailinglicense [playerid/PartOfName]");
				return 1;
			}
			new giveplayerid;
			if(IsPlayerConnected(giveplayerid))
			{
				format(gString, sizeof(gString), "* You've given a Sailing License to %s.",PlayerInfo[giveplayerid][pName]);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
				format(gString, sizeof(gString), "* Instructor %s has given you a Sailing License.",PlayerInfo[playerid][pName]);
				SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
				PlayerInfo[giveplayerid][pBoatLic] = 1;
				return 1;
			}
			else
			{
				SendClientMessage(playerid, COLOR_GREY, "   That player is Offline !");
				return 1;
			}
		}
		else if(strcmp(x_nr,"fishing",true) == 0)
		{
			//if(!strlen(tmp))
			{
				SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /givelicense fishinglicense [playerid/PartOfName]");
				return 1;
			}
			new giveplayerid;
			if(IsPlayerConnected(giveplayerid))
			{
				format(gString, sizeof(gString), "* You've given a Fishing License to %s.",PlayerInfo[giveplayerid][pName]);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
				format(gString, sizeof(gString), "* Instructor %s has given you a Fishing License.",PlayerInfo[playerid][pName]);
				SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
				PlayerInfo[giveplayerid][pFishLic] = 1;
				return 1;
			}
			else
			{
				SendClientMessage(playerid, COLOR_GREY, "   That player is Offline !");
				return 1;
			}
		}
		else if(strcmp(x_nr,"weapon",true) == 0)
		{
			//if(!strlen(tmp))
			{
				SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /givelicense weaponlicense [playerid/PartOfName]");
				return 1;
			}
			new giveplayerid;
			if(IsPlayerConnected(giveplayerid))
			{
				format(gString, sizeof(gString), "* You've given a Weapon License to %s.",PlayerInfo[giveplayerid][pName]);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
				format(gString, sizeof(gString), "* Instructor %s has given you a Weapon License.",PlayerInfo[playerid][pName]);
				SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
				PlayerInfo[giveplayerid][pGunLic] = 1;
				return 1;
			}
			else
			{
				SendClientMessage(playerid, COLOR_GREY, "   That player is Offline !");
				return 1;
			}
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   You are not a School Instructor !");
		return 1;
	}
	return 1;
}

CMD:startlesson(playerid, params[]) {
	if(IsAnInstructor(playerid))
	{
		//if(!strlen(tmp))
		{
			SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /startlesson [playerid/PartOfName]");
			return 1;
		}
		new giveplayerid;
		if(IsPlayerConnected(giveplayerid))
		{
			if(giveplayerid != INVALID_PLAYER_ID)
			{
				format(gString, sizeof(gString), "* You've started %s's Lesson.",PlayerInfo[giveplayerid][pName]);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
				format(gString, sizeof(gString), "* Instructor %s has started your Lesson.",PlayerInfo[playerid][pName]);
				SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
				TakingLesson[giveplayerid] = 1;
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   That player is Offline !");
			return 1;
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   You are not a School Instructor !");
		return 1;
	}
	return 1;
}

CMD:stoplesson(playerid, params[]) {
	if(IsAnInstructor(playerid))
	{
		//if(!strlen(tmp))
		{
			SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /stoplesson [playerid/PartOfName]");
			return 1;
		}
		new giveplayerid;
		if(IsPlayerConnected(giveplayerid))
		{
			if(giveplayerid != INVALID_PLAYER_ID)
			{
				if(TakingLesson[giveplayerid] != 1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   That player is not taking a Lesson !");
					return 1;
				}
				format(gString, sizeof(gString), "* You've stopped %s's Lesson.",PlayerInfo[giveplayerid][pName]);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
				format(gString, sizeof(gString), "* Instructor %s has stopped your Lesson.",PlayerInfo[playerid][pName]);
				SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
				TakingLesson[giveplayerid] = 0;
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   That player is Offline !");
			return 1;
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   You are not a School Instructor !");
		return 1;
	}
	return 1;
}

CMD:families(playerid, params[]) {
	//if(!strlen(tmp))
	{
		new number = 0;
		for(new i = 0; i < sizeof(FamilyInfo); i++)
		{
			number ++;
			format(gString, sizeof(gString), "Family %d| Name: %s | Leader: %s | Members: %d.",number,FamilyInfo[i][FamilyName],FamilyInfo[i][FamilyLeader],FamilyInfo[i][FamilyMembers]);
			SendClientMessage(playerid, COLOR_WHITE, gString);
		}
		return 1;
	}
	new family;
	if(family < 1 || family > 10) { SendClientMessage(playerid, COLOR_GREY, "   FamilyNr can't be below 1 or above 10 !"); return 1; }
	family -= 1;
	if(FamilyInfo[family][FamilyTaken] != 1)
	{
		SendClientMessage(playerid, COLOR_GREY, "   That FamilyNr hasn't been Taken yet !");
		return 1;
	}
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i))
		{
			if(PlayerInfo[i][pFMember] == family)
			{
				format(gString, sizeof(gString), "* Family %d: %s | Rank: %d.",family,PlayerInfo[i][pName],PlayerInfo[i][pRank]);
				SendClientMessage(playerid, COLOR_GREY, gString);
			}
		}
	}
	return 1;
}

CMD:adjust(playerid, params[]) {
	if(PlayerInfo[playerid][pFMember] == 255)
	{
		SendClientMessage(playerid, COLOR_GREY, "   You are not in a Family !");
		return 1;
	}
	new family = PlayerInfo[playerid][pFMember];
	new wstring[128];
	format(gString, sizeof(gString), "%s", PlayerInfo[playerid][pName]);
	strmid(wstring, gString, 0, strlen(gString), 255);
	if(strcmp(FamilyInfo[family][FamilyLeader],wstring, true ) == 0 )
	{
		new x_nr[256];
		if(!strlen(x_nr)) {
			SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /adjust [name]");
			SendClientMessage(playerid, COLOR_WHITE, "Available Names: Name, MOTD, Color, Spawn, Invite, Uninvite, Rank");
			return 1;
		}
		if(strcmp(x_nr,"name",true) == 0)
		{
			new result[64];
			if(!strlen(result))
			{
				SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /adjust Name [Family Name]");
				return 1;
			}
			strmid(FamilyInfo[family][FamilyName], result, 0, strlen(result), 255);
			SaveFamilies();
			SendClientMessage(playerid, COLOR_WHITE, "You've adjusted your Family's Name.");
		}
		else if(strcmp(x_nr,"motd",true) == 0)
		{
			new result[64];
			if(!strlen(result))
			{
				SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /adjust MOTD [Family MOTD Text]");
				return 1;
			}
			strmid(FamilyInfo[family][FamilyMOTD], result, 0, strlen(result), 255);
			SaveFamilies();
			SendClientMessage(playerid, COLOR_WHITE, "You've adjusted your Family's MOTD.");
		}
		else if(strcmp(x_nr,"color",true) == 0)
		{
			new result[64];
			if(!strlen(result))
			{
				SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /adjust color [Family Color Sample: 0xFFFFFFAA]");
				return 1;
			}
			//if(offset < 10)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Wrong Color number, take a look at the Sample ! (0xFFFFFFAA)");
				return 1;
			}
			strmid(FamilyInfo[family][FamilyMOTD], result, 0, strlen(result), 255);
			SaveFamilies();
			SendClientMessage(playerid, COLOR_WHITE, "You've adjusted your Family's Color.");
		}
		else if(strcmp(x_nr,"spawn",true) == 0)
		{
			GetPlayerPos(playerid, FamilyInfo[family][FamilySpawn][0],FamilyInfo[family][FamilySpawn][1],FamilyInfo[family][FamilySpawn][2]);
			GetPlayerFacingAngle(playerid, FamilyInfo[family][FamilySpawn][3]);
			FamilyInfo[family][FamilyInterior] = GetPlayerInterior(playerid);
			SaveFamilies();
			SendClientMessage(playerid, COLOR_WHITE, "You've adjusted your Family's Spawnplace.");
		}
		else if(strcmp(x_nr,"invite",true) == 0)
		{
			if(FamilyInfo[family][FamilyMembers] >= 10)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Your Family has reached the Maximum of 10 Family Members, can't invite more !");
				return 1;
			}
			if(!strlen(x_nr)) {
				SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /adjust invite [playerid/PartOfName]");
				return 1;
			}
			new giveplayerid;
			if(IsPlayerConnected(giveplayerid))
			{
				if(giveplayerid != INVALID_PLAYER_ID)
				{
					if(PlayerInfo[giveplayerid][pFMember] != 255)
					{
						SendClientMessage(playerid, COLOR_GREY, "   That player is already in a Family !");
						return 1;
					}
					format(gString, sizeof(gString), "* You've invited %s to join '%s'.",PlayerInfo[giveplayerid][pName], FamilyInfo[family][FamilyName]);
					SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
					format(gString, sizeof(gString), "* %s has invited you to join '%s', you are now a Member of it.",PlayerInfo[playerid][pName], FamilyInfo[family][FamilyName]);
					SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
					PlayerInfo[giveplayerid][pFMember] = family;
					PlayerInfo[giveplayerid][pRank] = 1;
					FamilyInfo[family][FamilyMembers] ++;
					SaveFamilies();
					return 1;
				}
			}
			else
			{
				SendClientMessage(playerid, COLOR_GREY, "   That player is Offline !");
				return 1;
			}
		}
		else if(strcmp(x_nr,"uninvite",true) == 0)
		{
			if(!strlen(x_nr)) {
				SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /adjust uninvite [playerid/PartOfName]");
				return 1;
			}
			new giveplayerid;
			if(IsPlayerConnected(giveplayerid))
			{
				if(giveplayerid != INVALID_PLAYER_ID)
				{
					if(PlayerInfo[giveplayerid][pFMember] != family)
					{
						SendClientMessage(playerid, COLOR_GREY, "   That player is not in your Family !");
						return 1;
					}
					format(gString, sizeof(gString), "* You've kicked %s out of your Family.",PlayerInfo[giveplayerid][pName]);
					SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
					format(gString, sizeof(gString), "* Family Leader %s has kicked your out of the Family.",PlayerInfo[playerid][pName]);
					SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
					PlayerInfo[giveplayerid][pFMember] = 255;
					PlayerInfo[giveplayerid][pRank] = 0;
					FamilyInfo[family][FamilyMembers] --;
					SaveFamilies();
					return 1;
				}
			}
			else
			{
				SendClientMessage(playerid, COLOR_GREY, "   That player is Offline !");
				return 1;
			}
		}
		else if(strcmp(x_nr,"rank",true) == 0)
		{
			if(!strlen(x_nr)) {
				SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /adjust rank [RankNr] [playerid/PartOfName]");
				return 1;
			}
			new rank;
			if(rank < 1 || rank > 6) { SendClientMessage(playerid, COLOR_GREY, "   RankNr can't be below 1 or above 6 !"); return 1; }
			if(!strlen(x_nr)) {
				SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /adjust rank [RankNr] [playerid/PartOfName]");
				return 1;
			}
			new giveplayerid;
			if(IsPlayerConnected(giveplayerid))
			{
				if(giveplayerid != INVALID_PLAYER_ID)
				{
					if(PlayerInfo[giveplayerid][pFMember] != family)
					{
						SendClientMessage(playerid, COLOR_GREY, "   That player is not in your Family !");
						return 1;
					}
					format(gString, sizeof(gString), "* You've given %s Rank %d.",PlayerInfo[giveplayerid][pName],rank);
					SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
					format(gString, sizeof(gString), "* Family Leader %s has given you Rank %d.",PlayerInfo[playerid][pName],rank);
					SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
					PlayerInfo[giveplayerid][pRank] = rank;
					return 1;
				}
			}
			else
			{
				SendClientMessage(playerid, COLOR_GREY, "   That player is Offline !");
				return 1;
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   Invalid Adjust name !");
			return 1;
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   You are not the Leader of your Family !");
		return 1;
	}
	return 1;
}

CMD:giveturf(playerid, params[]) {
	if(PlayerInfo[playerid][pLeader] == 5 || PlayerInfo[playerid][pLeader] == 6)
	{
		//if(!strlen(tmp))
		{
			SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /giveturf [FamilyNr]");
			return 1;
		}
		new family;
		if(family < 1 || family > 10) { SendClientMessage(playerid, COLOR_GREY, "   FamilyNr can't be below 1 or above 10 !"); return 1; }
		if(PlayerInfo[playerid][pLeader] == 5 && family > 5) { SendClientMessage(playerid, COLOR_GREY, "   La Cosa Nostra Leader can only take FamilyNr 1 till 5 !"); return 1; }
		else if(PlayerInfo[playerid][pLeader] == 6 && family < 6) { SendClientMessage(playerid, COLOR_GREY, "   Yakuza Leader can only take FamilyNr 6 till 10 !"); return 1; }
		family -= 1;
		if(FamilyInfo[family][FamilyTaken] != 1)
		{
			SendClientMessage(playerid, COLOR_GREY, "   That FamilyNr hasn't been Taken yet !");
			return 1;
		}
		new Found = 0;
		for(new j=0; j<sizeof(TurfInfo);j++)
		{
			if(IsPlayerInTurf(playerid,j))
			{
				Found = 1;
				format(gString, sizeof(gString), "%s", FamilyInfo[family][FamilyName]);
				strmid(TurfInfo[j][zOwner], gString, 0, strlen(gString), 255);
				format(gString, sizeof(gString), "%s", FamilyInfo[family][FamilyColor]);
				strmid(TurfInfo[j][zColor], gString, 0, strlen(gString), 255);
			}
		}
		if(Found)
		{
			SaveTurfs();
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Turf adjusted.");
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   You are not in a Turf !");
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   You are not the Leader of one of the Organisations !");
		return 1;
	}
	return 1;
}

CMD:allowcreation(playerid, params[]) {
	if(PlayerInfo[playerid][pLeader] == 5 || PlayerInfo[playerid][pLeader] == 6)
	{
		//if(!strlen(tmp)) {
			SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /allowcreation [FamilyNr] [playerid/PartOfName]");
			return 1;
		}
		new family;
		if(family < 1 || family > 10) { SendClientMessage(playerid, COLOR_GREY, "   FamilyNr can't be below 1 or above 10 !"); return 1; }
		if(PlayerInfo[playerid][pLeader] == 5 && family > 5) { SendClientMessage(playerid, COLOR_GREY, "   La Cosa Nostra Leader can only take FamilyNr 1 till 5 !"); return 1; }
		else if(PlayerInfo[playerid][pLeader] == 6 && family < 6) { SendClientMessage(playerid, COLOR_GREY, "   Yakuza Leader can only take FamilyNr 6 till 10 !"); return 1; }
		//if(!strlen(tmp)) {
			SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /allowcreation [FamilyNr] [playerid/PartOfName]");
			return 1;
		//}
		new giveplayerid;
		if(IsPlayerConnected(giveplayerid))
		{
			if(giveplayerid != INVALID_PLAYER_ID)
			{
				family -= 1;
				if(FamilyInfo[family][FamilyTaken] == 1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   That FamilyNr is already taken !" );
					return 1;
				}
				format(gString, sizeof(gString), "* You've made %s the Leader of FamilyNr %d.",PlayerInfo[giveplayerid][pName],family);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
				if(PlayerInfo[playerid][pLeader] == 5)
				{
					format(gString, sizeof(gString), "* La Cosa Nostra Leader %s has made you a Family Leader of FamilyNr %d.",PlayerInfo[playerid][pName],family);
					SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
				}
				else if(PlayerInfo[playerid][pLeader] == 6)
				{
					format(gString, sizeof(gString), "* Yakuza Leader %s has made you a Family Leader of FamilyNr %d.",PlayerInfo[playerid][pName],family);
					SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
				}
				format(gString, sizeof(gString), "%s",PlayerInfo[giveplayerid][pName]);
				strmid(FamilyInfo[family][FamilyLeader], gString, 0, strlen(gString), 255);
				FamilyInfo[family][FamilyMembers] ++;
				FamilyInfo[family][FamilyTaken] = 1;
				PlayerInfo[giveplayerid][pFMember] = family;
				SaveFamilies();
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   That player is Offline !");
			return 1;
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   You are not the Leader of one of the Organisations !");
		return 1;
	}
	return 1;
}

CMD:deletecreation(playerid, params[]) {
	if(PlayerInfo[playerid][pLeader] == 5 || PlayerInfo[playerid][pLeader] == 6)
	{
		//if(!strlen(tmp))
		{
			SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /deletecreation [FamilyNr]");
			return 1;
		}
		new family;
		if(family < 1 || family > 10) { SendClientMessage(playerid, COLOR_GREY, "   FamilyNr can't be below 1 or above 10 !"); return 1; }
		if(PlayerInfo[playerid][pLeader] == 5 && family > 5) { SendClientMessage(playerid, COLOR_GREY, "   La Cosa Nostra Leader can only take FamilyNr 1 till 5 !"); return 1; }
		else if(PlayerInfo[playerid][pLeader] == 6 && family < 6) { SendClientMessage(playerid, COLOR_GREY, "   Yakuza Leader can only take FamilyNr 6 till 10 !"); return 1; }
		family -= 1;
		if(FamilyInfo[family][FamilyTaken] != 1)
		{
			SendClientMessage(playerid, COLOR_GREY, "   That FamilyNr isn't taken !");
			return 1;
		}
		ClearFamily(family);
		SaveFamilies();
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   You are not the Leader of one of the Organisations !");
		return 1;
	}
	return 1;
}

CMD:ram(playerid, params[]) {
	if(gTeam[playerid] == 2 || PlayerInfo[playerid][pLeader] == 6 || PlayerInfo[playerid][pLeader] == 10)
	{
		for(new i = 0; i < sizeof(HouseInfo); i++)
		{
			if (PlayerToPoint(3, playerid,HouseInfo[i][hEntrancex], HouseInfo[i][hEntrancey], HouseInfo[i][hEntrancez]))
			{
				SetPlayerInterior(playerid,HouseInfo[i][hInt]);
				SetPlayerPos(playerid,HouseInfo[i][hExitx],HouseInfo[i][hExity],HouseInfo[i][hExitz]);
				GameTextForPlayer(playerid, "~r~Breached the door", 5000, 1);
				PlayerInfo[playerid][pInt] = HouseInfo[i][hInt];
				PlayerInfo[playerid][pLocal] = i;
			}
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   You are not a Cop / Soldier !");
		return 1;
	}
	return 1;
}

CMD:camera(playerid, params[]) {
	if(IsACop(playerid))
	{
		if(!PlayerToPoint(8.0,playerid,211.6222,1811.9565,21.8594))
		{
			SendClientMessage(playerid, COLOR_GREY, "   You are not at the Area51 Security Panel !");
			return 1;
		}
		//if(!strlen(tmp)) 
		{
			SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /camera [number 1 - 6]  (6 = OFF)");
			return 1;
		}
		new number;
		if(number < 1 || number > 6) { SendClientMessage(playerid, COLOR_GREY, "   Camera Number can't be below 1 or above 6 !"); return 1; }
		TogglePlayerControllable(playerid, 0);
		GetPlayerPos(playerid, Unspec[playerid][Coords][0],Unspec[playerid][Coords][1],Unspec[playerid][Coords][2]);
		if(number == 1) { SetPlayerCameraPos(playerid, 118.1011,1931.3221,22.5527); SetPlayerCameraLookAt(playerid, 98.9656,1920.9819,18.2180); }
		else if(number == 2) { SetPlayerCameraPos(playerid, 213.5340,1875.3075,17.6406); SetPlayerCameraLookAt(playerid, 213.8679,1884.1714,13.8945); }
		else if(number == 3) { SetPlayerCameraPos(playerid, 266.0640,1894.8856,38.6459); SetPlayerCameraLookAt(playerid, 224.0039,1887.1532,17.6406); }
		else if(number == 4) { SetPlayerCameraPos(playerid, 260.8112,1808.0175,38.6303); SetPlayerCameraLookAt(playerid, 227.5645,1818.4778,17.6406); }
		else if(number == 5) { SetPlayerCameraPos(playerid, 114.5196,1814.3483,38.6029); SetPlayerCameraLookAt(playerid, 123.6176,1846.4792,17.6549); }
		else if(number == 6)
		{
			MedicBill[playerid] = 0;
			TogglePlayerControllable(playerid, 1);
			SetSpawnInfo(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pModel], Unspec[playerid][Coords][0], Unspec[playerid][Coords][1], Unspec[playerid][Coords][2], 10.0, -1, -1, -1, -1, -1, -1);
			SpawnPlayer(playerid);
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   You are not a Cop / Soldier !");
		return 1;
	}
	return 1;
}

CMD:divorce(playerid, params[]) {
	if(PlayerInfo[playerid][pMarried] < 1)
	{
		SendClientMessage(playerid, COLOR_GREY, "   You aren't Married !");
		return 1;
	}
	//if(!strlen(tmp))
	{
		SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /divorce [Playerid/PartOfName]");
		return 1;
	}
	new giveplayerid;
	if(IsPlayerConnected(giveplayerid))
	{
		if(giveplayerid != INVALID_PLAYER_ID)
		{
			if (ProxDetectorS(8.0, playerid, giveplayerid))
			{
				if(giveplayerid == playerid) { SendClientMessage(playerid, COLOR_GREY, "You cannot Propose to yourself!"); return 1; }
				new dstring[MAX_PLAYER_NAME];
				new wstring[MAX_PLAYER_NAME];
				format(gString, sizeof(gString), "%s", PlayerInfo[giveplayerid][pName]);
				strmid(wstring, gString, 0, strlen(gString), 255);
				format(gString, sizeof(gString), "%s", PlayerInfo[playerid][pMarriedTo]);
				strmid(dstring, gString, 0, strlen(gString), 255);
				if(strcmp(dstring ,wstring, true ) == 0 )
				{
					format(gString, sizeof(gString), "* You've sent Divorce Papers to %s.", PlayerInfo[giveplayerid][pName]);
					SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
					format(gString, sizeof(gString), "* %s just sent you his Divorce Papers (type /accept divorce) to accept.", PlayerInfo[playerid][pName]);
					SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
					DivorceOffer[giveplayerid] = playerid;
					return 1;
				}
				else
				{
					SendClientMessage(playerid, COLOR_GREY, "   That player is not Married to you !");
					return 1;
				}
			}
			else
			{
				SendClientMessage(playerid, COLOR_GREY, "   That player is not near you !");
				return 1;
			}
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   That player is Offline !");
		return 1;
	}
	return 1;
}

CMD:propose(playerid, params[]) {
	if(GetPlayerMoney(playerid) < 100000)
	{
		SendClientMessage(playerid, COLOR_GREY, "   The Marriage & Reception costs $100000 !");
		return 1;
	}
	if(PlayerInfo[playerid][pMarried] > 0)
	{
		SendClientMessage(playerid, COLOR_GREY, "   You are already Married !");
		return 1;
	}
	if(PlayerInfo[playerid][pPhousekey] == 255)
	{
		SendClientMessage(playerid, COLOR_GREY, "   You don't have a House to let your Wife / Husband live somewhere !");
		return 1;
	}
	//if(!strlen(tmp))
	{
		SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /propose [Playerid/PartOfName]");
		return 1;
	}
	new giveplayerid;
	if(IsPlayerConnected(giveplayerid))
	{
		if(giveplayerid != INVALID_PLAYER_ID)
		{
			if(PlayerInfo[giveplayerid][pMarried] > 0)
			{
				SendClientMessage(playerid, COLOR_GREY, "   That player is already Married !");
				return 1;
			}
			if(PlayerInfo[giveplayerid][pPhousekey] != 255)
			{
				SendClientMessage(playerid, COLOR_GREY, "   That player has a House, can't be Married !");
				return 1;
			}
			if(PlayerInfo[giveplayerid][pPbiskey] != 255)
			{
				SendClientMessage(playerid, COLOR_GREY, "   That player has a Business, can't be Married !");
				return 1;
			}
			if (ProxDetectorS(8.0, playerid, giveplayerid))
			{
				if(giveplayerid == playerid) { SendClientMessage(playerid, COLOR_GREY, "You cannot Propose to yourself!"); return 1; }
				format(gString, sizeof(gString), "* You proposed to %s.", PlayerInfo[giveplayerid][pName]);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
				format(gString, sizeof(gString), "* %s just proposed to you (type /accept marriage) to accept.", PlayerInfo[playerid][pName]);
				SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
				ProposeOffer[giveplayerid] = playerid;
			}
			else
			{
				SendClientMessage(playerid, COLOR_GREY, "   That player is not near you !");
				return 1;
			}
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   That player is Offline !");
		return 1;
	}
	return 1;
}

CMD:witness(playerid, params[]) {
	//if(!strlen(tmp)) 
	{
		SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /witness [Playerid/PartOfName]");
		return 1;
	}
	new giveplayerid;
	if(IsPlayerConnected(giveplayerid))
	{
		if(giveplayerid != INVALID_PLAYER_ID)
		{
			if (ProxDetectorS(8.0, playerid, giveplayerid))
			{
				if(giveplayerid == playerid) { SendClientMessage(playerid, COLOR_GREY, "You cannot Propose to yourself!"); return 1; }
				format(gString, sizeof(gString), "* You requested %s to be your Marriage Witness.", PlayerInfo[giveplayerid][pName]);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
				format(gString, sizeof(gString), "* %s just requested you to be his Marriage Witness (type /accept witness) to accept.", PlayerInfo[playerid][pName]);
				SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
				MarryWitnessOffer[giveplayerid] = playerid;
			}
			else
			{
				SendClientMessage(playerid, COLOR_GREY, "   That player is not near you !");
				return 1;
			}
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   That player is Offline !");
		return 1;
	}
	return 1;
}

CMD:irc(playerid, params[]) {
	new x_nr[256];
	if(!strlen(x_nr)) {
		SendClientMessage(playerid, COLOR_WHITE, "Uzycie: (/irc join [channelnr] or /irc join [channelnr] [password])  (/irc Leave)  (/irc Admins)");
		SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /irc [name] [channelnr]");
		SendClientMessage(playerid, COLOR_WHITE, "Available names: MOTD, Password, NeedPass, Lock, Kick, Status");
		return 1;
	}
	if(strcmp(x_nr,"join",true) == 0)
	{
		//if(!strlen(tmp))
		{
			SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /irc join [channelnr] or /irc join [channelnr] [password]");
			return 1;
		}
		new channel;
		if(channel < 1 || channel > 10) { SendClientMessage(playerid, COLOR_GREY, "   Channel Number can't be below 1 or above 10 !"); return 1; }
		channel -= 1;
		if(IRCInfo[channel][iLock] == 0)
		{
			if(IRCInfo[channel][iNeedPass] == 0)
			{
				JoinChannelNr(playerid, channel);
			}
			else
			{
				//if(!strlen(tmp))
				{
					SendClientMessage(playerid, COLOR_WHITE, "There's a password required to join this Channel.");
					SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /irc join [channelnr] [password]");
					return 1;
				}
				JoinChannel(playerid,channel,tmp);
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   That Channel is Locked, please choose a different one !");
			return 1;
		}
	}
	else if(strcmp(x_nr,"status",true) == 0)
	{
		for(new i = 0; i < sizeof(IRCInfo); i++)
		{
			format(gString, sizeof(gString), "Channel %d: %d Players Connected.",i + 1, IRCInfo[i][iPlayers]);
			SendClientMessage(playerid, COLOR_WHITE, gString);
		}
		return 1;
	}
	else if(strcmp(x_nr,"password",true) == 0)
	{
		//if(!strlen(tmp))
		{
			SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /irc password [channelnr] [password]");
			return 1;
		}
		new channel;
		if(channel < 1 || channel > 10) { SendClientMessage(playerid, COLOR_GREY, "   Channel Number can't be below 1 or above 10 !"); return 1; }
		channel -= 1;
		new wstring[128];
		format(gString, sizeof(gString), "%s", PlayerInfo[playerid][pName]);
		strmid(wstring, gString, 0, strlen(gString), 255);
		if(strcmp(IRCInfo[channel][iAdmin],wstring, true ) == 0 )
		{
			//if(!strlen(tmp))
			{
				SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /irc password [channelnr] [password]");
				return 1;
			}
			strmid(IRCInfo[channel][iPassword], tmp, 0, strlen(tmp), 255);
			format(gString, sizeof(gString), "You've changed the IRC Channel's Password to: %s.",IRCInfo[channel][iPassword]);
			SendClientMessage(playerid, COLOR_YELLOW, gString);
			SaveIRC();
			return 1;
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   You are not the Admin of that Channel !");
			return 1;
		}
	}
	else if(strcmp(x_nr,"needpass",true) == 0)
	{
		//if(!strlen(tmp))
		{
			SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /irc needpass [channelnr]");
			return 1;
		}
		new channel;
		if(channel < 1 || channel > 10) { SendClientMessage(playerid, COLOR_GREY, "   Channel Number can't be below 1 or above 10 !"); return 1; }
		channel -= 1;
		new wstring[128];
		format(gString, sizeof(gString), "%s", PlayerInfo[playerid][pName]);
		strmid(wstring, gString, 0, strlen(gString), 255);
		if(strcmp(IRCInfo[channel][iAdmin],wstring, true ) == 0 )
		{
			if(IRCInfo[channel][iNeedPass] != 0)
			{
				IRCInfo[channel][iNeedPass] = 0;
				SendClientMessage(playerid, COLOR_YELLOW, "Players won't have to fill in a password in order to join the IRC Channel now.");
			}
			else
			{
				IRCInfo[channel][iNeedPass] = 1;
				SendClientMessage(playerid, COLOR_YELLOW, "Players must fill in a password in order to join the IRC Channel now.");
			}
			SaveIRC();
			return 1;
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   You are not the Admin of that Channel !");
			return 1;
		}
	}
	else if(strcmp(x_nr,"lock",true) == 0)
	{
		//if(!strlen(tmp))
		{
			SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /irc lock [channelnr]");
			return 1;
		}
		new channel;
		if(channel < 1 || channel > 10) { SendClientMessage(playerid, COLOR_GREY, "   Channel Number can't be below 1 or above 10 !"); return 1; }
		channel -= 1;
		new wstring[128];
		format(gString, sizeof(gString), "%s", PlayerInfo[playerid][pName]);
		strmid(wstring, gString, 0, strlen(gString), 255);
		if(strcmp(IRCInfo[channel][iAdmin],wstring, true ) == 0 )
		{
			if(IRCInfo[channel][iLock] != 0)
			{
				IRCInfo[channel][iLock] = 0;
				SendClientMessage(playerid, COLOR_YELLOW, "You've unlocked the IRC Channel.");
			}
			else
			{
				IRCInfo[channel][iLock] = 1;
				SendClientMessage(playerid, COLOR_YELLOW, "You've locked the IRC Channel.");
			}
			SaveIRC();
			return 1;
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   You are not the Admin of that Channel !");
			return 1;
		}
	}
	else if(strcmp(x_nr,"motd",true) == 0)
	{
		//if(!strlen(tmp))
		{
			SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /irc motd [channelnr] [motdtext]");
			return 1;
		}
		new channel;
		if(channel < 1 || channel > 10) { SendClientMessage(playerid, COLOR_GREY, "   Channel Number can't be below 1 or above 10 !"); return 1; }
		channel -= 1;
		new wstring[128];
		format(gString, sizeof(gString), "%s", PlayerInfo[playerid][pName]);
		strmid(wstring, gString, 0, strlen(gString), 255);
		if(strcmp(IRCInfo[channel][iAdmin],wstring, true ) == 0 )
		{
			new result[64];
			if(!strlen(result))
			{
				SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /irc motd [motdtext]");
				return 1;
			}
			strmid(IRCInfo[channel][iMOTD], result, 0, strlen(result), 255);
			SendClientMessage(playerid, COLOR_YELLOW, "You've adjusted the IRC Channel's MOTD Text.");
			SaveIRC();
			return 1;
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   You are not the Admin of that Channel !");
			return 1;
		}
	}
	else if(strcmp(x_nr,"leave",true) == 0)
	{
		if(PlayersChannel[playerid] < 999)
		{
			format(gString, sizeof(gString), "* %s has left the Channel.", PlayerInfo[playerid][pName]);
			SendIRCMessage(PlayersChannel[playerid], COLOR_GREEN, gString);
			IRCInfo[PlayersChannel[playerid]][iPlayers] -= 1;
			PlayersChannel[playerid] = 999;
			return 1;
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   You are not in an IRC Channel !");
			return 1;
		}
	}
	else if(strcmp(x_nr,"admins",true) == 0)
	{
		for(new i = 0; i < sizeof(IRCInfo); i++)
		{
			format(gString, sizeof(gString), "Channel %d: %s.", i + 1, IRCInfo[i][iAdmin]);
			SendClientMessage(playerid, COLOR_WHITE, gString);
		}
		return 1;
	}
	else if(strcmp(x_nr,"kick",true) == 0)
	{
		if(PlayersChannel[playerid] == 999)
		{
			SendClientMessage(playerid, COLOR_GREY, "   You are not in an IRC Channel !");
			return 1;
		}
		new wstring[128];
		format(gString, sizeof(gString), "%s", PlayerInfo[playerid][pName]);
		strmid(wstring, gString, 0, strlen(gString), 255);
		if(strcmp(IRCInfo[PlayersChannel[playerid]][iAdmin],wstring, true ) == 0 )
		{
			//if(!strlen(tmp))
			{
				SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /irc kick [playerid/PartOfName]");
				return 1;
			}
			new giveplayerid;
			if(IsPlayerConnected(giveplayerid))
			{
				if(giveplayerid != INVALID_PLAYER_ID)
				{
					if(PlayersChannel[giveplayerid] == PlayersChannel[playerid])
					{
						format(gString, sizeof(gString), "* You've kicked %s out of your IRC Channel.",PlayerInfo[giveplayerid][pName]);
						SendClientMessage(playerid, COLOR_YELLOW, gString);
						format(gString, sizeof(gString), "* You've been kicked out of the IRC Channel by Channel Admin: %s.",PlayerInfo[playerid][pName]);
						SendClientMessage(giveplayerid, COLOR_YELLOW, gString);
						format(gString, sizeof(gString), "* %s has left the Channel (Kicked).", PlayerInfo[playerid][pName]);
						SendIRCMessage(PlayersChannel[playerid], COLOR_GREEN, gString);
						IRCInfo[PlayersChannel[giveplayerid]][iPlayers] -= 1;
						PlayersChannel[giveplayerid] = 999;
					}
					else
					{
						SendClientMessage(playerid, COLOR_GREY, "   That player is not in your IRC Channel !");
						return 1;
					}
				}
			}
			else
			{
				SendClientMessage(playerid, COLOR_GREY, "   That player is Offline !");
				return 1;
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   You are not the Admin of the Channel !");
			return 1;
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   Invalid IRC Channel Number ! ");
		return 1;
	}
	return 1;
}

CMD:i(playerid, params[]) {
	if(PlayersChannel[playerid] == 999)
	{
		SendClientMessage(playerid, COLOR_GREY, "   You are not in an IRC Channel !");
		return 1;
	}
	if(PlayerInfo[playerid][pMuted] == 1)
	{
		SendClientMessage(playerid, TEAM_CYAN_COLOR, "You cannot speak, you have been silenced");
		return 1;
	}
	new result[64];
	if(!strlen(result))
	{
		SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /i [irc chat]");
		return 1;
	}
	format(gString, sizeof(gString), "** IRC %s: %s. **", PlayerInfo[playerid][pName], result);
	SendIRCMessage(PlayersChannel[playerid], COLOR_YELLOW2, gString);
	return 1;
}

CMD:mission(playerid, params[]) {
	if(!PlayerToPoint(3.0,playerid,1381.0413,-1088.8511,27.3906))
	{
		SendClientMessage(playerid, COLOR_GREY, "   You are not at the Bill Board !");
		return 1;
	}
	if(MissionPlayable == 0)
	{
		SendClientMessage(playerid, COLOR_GREY, "   No Mission has been Activated !");
		return 1;
	}
	if(PlayerInfo[playerid][pMissionNr] == MissionPlayable)
	{
		SendClientMessage(playerid, COLOR_GREY, "   You've already completed the Active Mission !");
		return 1;
	}
	RingTone[playerid] = 20;
	PlayerOnMission[playerid] = PlayMission[kNumber];
	MissionCheckpoint[playerid] = 1;
	format(gString, sizeof(gString), "~w~Mission started: ~n~~r~%s", PlayMission[kTitle]);
	GameTextForPlayer(playerid, gString, 5000, 3);
	format(gString, sizeof(gString), "%s", PlayMission[kText1]);
	SendClientMessage(playerid, COLOR_YELLOW2, gString);
	format(gString, sizeof(gString), "%s", PlayMission[kText2]);
	SendClientMessage(playerid, COLOR_YELLOW2, gString);
	format(gString, sizeof(gString), "%s", PlayMission[kText3]);
	SendClientMessage(playerid, COLOR_YELLOW2, gString);
	if(PlayMission[kToggle] == 1)
	{
		SetPlayerCheckpoint(playerid, PlayMission[kCP1][0], PlayMission[kCP1][1], PlayMission[kCP1][2], 8);
	}
	return 1;
}

CMD:settax(playerid, params[]) {
	if(PlayerInfo[playerid][pLeader] != 7)
	{
		SendClientMessage(playerid, COLOR_GREY, "   You are not the Mayor !");
		return 1;
	}
	//if(!strlen(tmp)) 
	{
		SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /settax [ammount]");
		return 1;
	}
	new moneys;
	if(moneys < 1 || moneys > 5000) { SendClientMessage(playerid, COLOR_GREY, "   Tax may not be below 1 or above 5000 !"); return 1; }
	Tax = moneys;
	SaveStuff();
	format(gString, sizeof(gString), "* The Tax is $%d per player, from now on.", Tax);
	SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
	return 1;
}

CMD:givetax(playerid, params[]) {
	if(PlayerInfo[playerid][pLeader] != 7)
	{
		SendClientMessage(playerid, COLOR_GREY, "   You are not the Mayor !");
		return 1;
	}
	if(Tax < 1)
	{
		SendClientMessage(playerid, COLOR_GREY, "   There is no Money left in the Tax Fault !");
		return 1;
	}
	new Cops = 0;
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i))
		{
			if(gTeam[i] == 2 && PlayerInfo[i][pMember] == 1)
			{
				Cops += 1;
			}
		}
	}
	if(Cops >= 1)
	{
		new value = Tax / 2;
		new price = value / Cops;
		for(new i = 0; i < MAX_PLAYERS; i++)
		{
			if(IsPlayerConnected(i))
			{
				if(gTeam[i] == 2 && PlayerInfo[i][pMember] == 1)
				{
					format(gString, sizeof(gString), "* You received $%d from the Tax Fault from the Mayor.",price);
					SendClientMessage(i, COLOR_LIGHTBLUE, gString);
					GivePlayerMoney(i, price);
					Tax -= price;
				}
			}
		}
		SaveStuff();
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   There are no Cops Online at the moment !");
		return 1;
	}
	return 1;
}

CMD:read(playerid, params[]) {
	new x_job[256];
	if(!strlen(x_job)) {
		SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /read [name]");
		SendClientMessage(playerid, COLOR_GREY, "Available names: Paper, TestPaper");
		return 1;
	}
	if(strcmp(x_job,"paper",true) == 0)
	{
		if(GotPaper[playerid] > 0)
		{
			SendClientMessage(playerid, COLOR_WHITE, "|_______________ Role Play - The Godfather: Newspaper _______________|");
			format(gString, sizeof(gString), "| %s  |  By News Reporter: %s.",Paper[playerid][pTitle],Paper[playerid][pMaker]);
			SendClientMessage(playerid, COLOR_GREEN, gString);
			format(gString, sizeof(gString), "%s",Paper[playerid][pLine1]);
			SendClientMessage(playerid, COLOR_GREY, gString);
			format(gString, sizeof(gString), "%s",Paper[playerid][pLine2]);
			SendClientMessage(playerid, COLOR_GREY, gString);
			format(gString, sizeof(gString), "%s",Paper[playerid][pLine3]);
			SendClientMessage(playerid, COLOR_GREY, gString);
			format(gString, sizeof(gString), "%s",Paper[playerid][pLine4]);
			SendClientMessage(playerid, COLOR_GREY, gString);
			format(gString, sizeof(gString), "%s",Paper[playerid][pLine5]);
			SendClientMessage(playerid, COLOR_GREY, gString);
			format(gString, sizeof(gString), "%s",Paper[playerid][pLine6]);
			SendClientMessage(playerid, COLOR_GREY, gString);
			format(gString, sizeof(gString), "%s",Paper[playerid][pLine7]);
			SendClientMessage(playerid, COLOR_GREY, gString);
			SendClientMessage(playerid, COLOR_WHITE, "|____________________________________________________________________|");
			return 1;
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   You don't have a Newspaper !");
			return 1;
		}
	}
	else if(strcmp(x_job,"testpaper",true) == 0)
	{
		if(PlayerInfo[playerid][pMember] == 9 || PlayerInfo[playerid][pLeader] == 9)
		{
			//if(!strlen(tmp)) 
			{
				SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /read testpaper [papernr]");
				return 1;
			}
			new paper;
			if(paper < 1 || paper > 10) { SendClientMessage(playerid, COLOR_GREY, "   Paper Number can't be below 1 or above 10 !"); return 1; }
			paper -= 1;
			if(PaperInfo[paper][PaperUsed] == 0)
			{
				SendClientMessage(playerid, COLOR_GREY, "   There is no Newspaper written on that number !");
				return 1;
			}
			SendClientMessage(playerid, COLOR_WHITE, "|_______________ Role Play - The Godfather: Newspaper _______________|");
			format(gString, sizeof(gString), "| %s  |  By News Reporter: %s.",PaperInfo[paper][PaperTitle],PaperInfo[paper][PaperMaker]);
			SendClientMessage(playerid, COLOR_GREEN, gString);
			format(gString, sizeof(gString), "%s",PaperInfo[paper][PaperText1]);
			SendClientMessage(playerid, COLOR_GREY, gString);
			format(gString, sizeof(gString), "%s",PaperInfo[paper][PaperText2]);
			SendClientMessage(playerid, COLOR_GREY, gString);
			format(gString, sizeof(gString), "%s",PaperInfo[paper][PaperText3]);
			SendClientMessage(playerid, COLOR_GREY, gString);
			format(gString, sizeof(gString), "%s",PaperInfo[paper][PaperText4]);
			SendClientMessage(playerid, COLOR_GREY, gString);
			format(gString, sizeof(gString), "%s",PaperInfo[paper][PaperText5]);
			SendClientMessage(playerid, COLOR_GREY, gString);
			format(gString, sizeof(gString), "%s",PaperInfo[paper][PaperText6]);
			SendClientMessage(playerid, COLOR_GREY, gString);
			format(gString, sizeof(gString), "%s",PaperInfo[paper][PaperText7]);
			SendClientMessage(playerid, COLOR_GREY, gString);
			SendClientMessage(playerid, COLOR_WHITE, "|____________________________________________________________________|");
			return 1;
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   You are not a News Reporter !");
			return 1;
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /read testpaper [papernr]");
		return 1;
	}
	return 1;
}

CMD:deliver(playerid, params[]) {
	if(PlayerInfo[playerid][pJob] == 15 || gTeam[playerid] == 2 || PlayerInfo[playerid][pLeader] == 6 || PlayerInfo[playerid][pLeader] == 10)
	{
		if(gTeam[playerid] == 2 || IsACop(playerid))
		{
			if(!PlayerToPoint(8.0,playerid,96.9123,1920.5088,18.1473))
			{
				SendClientMessage(playerid, COLOR_GREY, "   You are not at the Area51 Delivery Gate !");
				return 1;
			}
			//if(!strlen(tmp))
			{
				SendClientMessage(playerid, COLOR_GRAD1, "Uzycie: /deliver [playerid/PartOfName]");
				return 1;
			}
			new giveplayerid;
			if (IsPlayerConnected(giveplayerid))
			{
				if(giveplayerid != INVALID_PLAYER_ID)
				{
					if(giveplayerid == playerid) { SendClientMessage(playerid, COLOR_GREY, "   Can't throw yourself into Fort DeMorgan !"); return 1; }
					if(WantedLevel[giveplayerid] < 1) { SendClientMessage(playerid, COLOR_GREY, "   The player needs at least Wanted Level 1 to be thrown into Fort DeMorgan !"); return 1; }
					if(gTeam[giveplayerid] == 2 || PlayerInfo[giveplayerid][pLeader] == 6 || PlayerInfo[giveplayerid][pLeader] == 10) { return 1; }
					if (ProxDetectorS(8.0, playerid, giveplayerid))
					{
						format(gString, sizeof(gString), "* You've brought %s to Fort DeMorgan.", PlayerInfo[giveplayerid][pName]);
						SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
						format(gString, sizeof(gString), "* %s brought you to Fort DeMorgan.", PlayerInfo[playerid][pName]);
						SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
						GameTextForPlayer(giveplayerid, "~w~Welcome to ~n~~r~Fort DeMorgan", 5000, 3);
						WantedPoints[giveplayerid] = 0;
						WantedLevel[giveplayerid] = 0;
						PlayerInfo[giveplayerid][pJailed] = 2;
						PlayerInfo[giveplayerid][pJailTime] = 3600;
						SetPlayerPos(giveplayerid, 107.2300,1920.6311,18.5208);
						SetPlayerWorldBounds(giveplayerid, 337.5694,101.5826,1940.9759,1798.7453); //285.3481,96.9720,1940.9755,1799.0811
					}
				}
				else
				{
					SendClientMessage(playerid, COLOR_GREY, "   That player is not near you !");
					return 1;
				}
			}
			else
			{
				SendClientMessage(playerid, COLOR_GREY, "   That player is Offline !");
				return 1;
			}
		}
		else if(PlayerInfo[playerid][pJob] == 15)
		{
			if(BringingPaper[playerid] != 1)
			{
				SendClientMessage(playerid, COLOR_GREY, "   You haven't picked up a Newspaper from the News Reporters Building yet !");
				return 1;
			}
			//if(!strlen(tmp))
			{
				SendClientMessage(playerid, COLOR_GRAD1, "Uzycie: /deliver [playerid/PartOfName]");
				return 1;
			}
			new giveplayerid;
			if (IsPlayerConnected(giveplayerid))
			{
				if(giveplayerid != INVALID_PLAYER_ID)
				{
					if (ProxDetectorS(8.0, playerid, giveplayerid))
					{
						format(gString, sizeof(gString), "* You offerd one of your Newspapers to %s.", PlayerInfo[giveplayerid][pName]);
						SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
						format(gString, sizeof(gString), "* Paper Boy %s wants to give you a Newspaper (use /accept paper, to accept).", PlayerInfo[playerid][pName]);
						SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
						PaperOffer[giveplayerid] = playerid;
					}
				}
				else
				{
					SendClientMessage(playerid, COLOR_GREY, "   That player is not near you !");
					return 1;
				}
			}
			else
			{
				SendClientMessage(playerid, COLOR_GREY, "   That player is Offline !");
				return 1;
			}
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   You are not a Paper Boy !");
		return 1;
	}
	return 1;
}

CMD:bring(playerid, params[]) {
	if(PlayerInfo[playerid][pJob] != 15)
	{
		SendClientMessage(playerid, COLOR_GREY, "   You are not a Paper Boy !");
		return 1;
	}
	if(PlayerToPoint(3.0,playerid,-2050.8962,460.0262,35.1719))
	{
		//if(!strlen(tmp))
		{
			SendClientMessage(playerid, COLOR_GRAD1, "Uzycie: /bring [papernr]");
			return 1;
		}
		new paper;
		if(paper < 1 || paper > 10) { SendClientMessage(playerid, COLOR_GREY, "   Paper Number can't be below 1 or above 10 !"); return 1; }
		paper -= 1;
		if(PaperInfo[paper][PaperUsed] == 0)
		{
			SendClientMessage(playerid, COLOR_GREY, "   There is no written Newspaper on that number !");
			return 1;
		}
		format(gString, sizeof(gString), "* You can now deliver Newspapers to people, Newspaper: %s, By: %s.",PaperInfo[paper][PaperTitle],PaperInfo[paper][PaperMaker]);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
		format(gString, sizeof(gString), "%s", PaperInfo[paper][PaperTitle]);
		strmid(Paper[playerid][pTitle], gString, 0, strlen(gString), 255);
		format(gString, sizeof(gString), "%s", PaperInfo[paper][PaperMaker]);
		strmid(Paper[playerid][pMaker], gString, 0, strlen(gString), 255);
		format(gString, sizeof(gString), "%s", PaperInfo[paper][PaperText1]);
		strmid(Paper[playerid][pLine1], gString, 0, strlen(gString), 255);
		format(gString, sizeof(gString), "%s", PaperInfo[paper][PaperText2]);
		strmid(Paper[playerid][pLine2], gString, 0, strlen(gString), 255);
		format(gString, sizeof(gString), "%s", PaperInfo[paper][PaperText3]);
		strmid(Paper[playerid][pLine3], gString, 0, strlen(gString), 255);
		format(gString, sizeof(gString), "%s", PaperInfo[paper][PaperText4]);
		strmid(Paper[playerid][pLine4], gString, 0, strlen(gString), 255);
		format(gString, sizeof(gString), "%s", PaperInfo[paper][PaperText5]);
		strmid(Paper[playerid][pLine5], gString, 0, strlen(gString), 255);
		format(gString, sizeof(gString), "%s", PaperInfo[paper][PaperText6]);
		strmid(Paper[playerid][pLine6], gString, 0, strlen(gString), 255);
		format(gString, sizeof(gString), "%s", PaperInfo[paper][PaperText7]);
		strmid(Paper[playerid][pLine7], gString, 0, strlen(gString), 255);
		BringingPaper[playerid] = 1;
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   You are not at the News Reporter Building !");
		return 1;
	}
	return 1;
}

CMD:papers(playerid, params[]) {
	if(PlayerInfo[playerid][pMember] == 9 || PlayerInfo[playerid][pLeader] == 9 || PlayerInfo[playerid][pJob] == 15)
	{
		if(PlayerToPoint(3.0,playerid,-2050.8962,460.0262,35.1719))
		{
			new number = 0;
			for(new i = 0; i < sizeof(PaperInfo); i++)
			{
				number ++;
				if(PaperInfo[i][PaperUsed] == 1)
				{
					format(gString, sizeof(gString), "|%d| Newspaper: %s, By: %s",number,PaperInfo[i][PaperTitle],PaperInfo[i][PaperMaker]);
					SendClientMessage(playerid, COLOR_WHITE, gString);
				}
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   You are not at the News Reporter Building !");
			return 1;
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   You are not a Paper Boy / News Reporter !");
		return 1;
	}
	return 1;
}

CMD:paper(playerid, params[]) {
	if(PlayerInfo[playerid][pMember] == 9 || PlayerInfo[playerid][pLeader] == 9)
	{
		if(!PlayerToPoint(3.0,playerid,-2050.8962,460.0262,35.1719))
		{
			SendClientMessage(playerid, COLOR_GREY, "   You are not at the News Reporter Building !");
			return 1;
		}
		new x_nr[256];
		//if(!strlen(x_nr))
		{
			SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /paper write [papernr] or /paper delete [papernr]");
			return 1;
		}
		if(strcmp(x_nr,"write",true) == 0)
		{
		//	if(!strlen(tmp))
			{
				SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /paper write [papernr]");
				return 1;
			}
			new paper;
			if(paper < 1 || paper > 10) { SendClientMessage(playerid, COLOR_GREY, "   Paper Number can't be below 1 or above 10 !"); return 1; }
			paper -= 1;
			if(PaperInfo[paper][PaperUsed] == 1)
			{
				SendClientMessage(playerid, COLOR_GREY, "   There is already a Newspaper on that number !");
				return 1;
			}
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You are producing a new Newspaper.");
			SendClientMessage(playerid, COLOR_LIGHTRED, "* Everything you type now will be added to the Newspaper, you have 7 lines available.");
			SendClientMessage(playerid, COLOR_LIGHTRED, "* Please type in the Title of your Newspaper.");
			WritingPaper[playerid] = 1;
			WritingPaperNumber[playerid] = paper;
			WritingLine[playerid] = 1;
		}
		else if(strcmp(x_nr,"delete",true) == 0)
		{
			if(PlayerInfo[playerid][pRank] >= 4)
			{
				//if(!strlen(tmp))
				{
					SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /paper delete [papernr]");
					return 1;
				}
				new paper;
				if(paper < 1 || paper > 10) { SendClientMessage(playerid, COLOR_GREY, "   Paper Number can't be below 1 or above 10 !"); return 1; }
				paper -= 1;
				ClearPaper(paper);
				new number = paper; number += 1;
				format(gString, sizeof(gString), "You've deleted Newspaper %d.",number);
				SendClientMessage(playerid, COLOR_YELLOW, gString);
			}
			else
			{
				SendClientMessage(playerid, COLOR_GREY, "   You need Rank 4 in order to Delete Newspapers !");
				return 1;
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /paper write [papernr] or /paper delete [papernr]");
			return 1;
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   You are not a News Reporter !");
		return 1;
	}
	return 1;
}

CMD:spawnchange(playerid, params[]) {
	if(PlayerInfo[playerid][pPhousekey] != 255)
	{
		if(Spectate[playerid] != 255 && PlayerInfo[playerid][pAdmin] < 1)
		{
			SendClientMessage(playerid, COLOR_GREY, "   You are Spectating, can't change the Spawn right now !");
			return 1;
		}
		if(SpawnChange[playerid])
		{
			SendClientMessage(playerid, COLOR_GREY, "   You will now spawn at your Normal Place !");
			SpawnChange[playerid] = 0;
			if(IsAnInstructor(playerid))
			{
				if(SchoolSpawn[playerid] == 0)
				{
					SchoolSpawn[playerid] = 1;
					SendClientMessage(playerid, COLOR_GREY, "   You will now spawn at the Flying School !");
				}
				else if(SchoolSpawn[playerid] == 1)
				{
					SchoolSpawn[playerid] = 0;
					SendClientMessage(playerid, COLOR_GREY, "   You will now spawn at the Driving School !");
				}
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   You will now spawn at your Own / Rented House !");
			SpawnChange[playerid] = 1;
		}
	}
	else
	{
		if(IsAnInstructor(playerid))
		{
			if(SchoolSpawn[playerid] == 0)
			{
				SchoolSpawn[playerid] = 1;
				SendClientMessage(playerid, COLOR_GREY, "   You will now spawn at the Flying School !");
			}
			else if(SchoolSpawn[playerid] == 1)
			{
				SchoolSpawn[playerid] = 0;
				SendClientMessage(playerid, COLOR_GREY, "   You will now spawn at the Driving School !");
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   You dont own / rent a House !");
			return 1;
		}
	}
	return 1;
}

CMD:report(playerid, params[]) {
	new result[64];
	if(!strlen(result))
	{
		SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /report [text]");
		return 1;
	}
	format(gString, sizeof(gString), "Report from %s: %s", PlayerInfo[playerid][pName], (result));
	ABroadCast(COLOR_YELLOW,gString,1);
	SendClientMessage(playerid, COLOR_YELLOW, "Your Report Message was sent to the Admins.");
	return 1;
}

CMD:clothes(playerid, params[]) {
	if(PlayerInfo[playerid][pMember] >= 1)
	{
		if(IsAtClothShop(playerid))
		{
			if(PlayerInfo[playerid][pMember] == 1) { ChosenSkin[playerid] = 280; SetPlayerSkin(playerid, 280); }
			else if(PlayerInfo[playerid][pMember] == 2) { ChosenSkin[playerid] = 286; SetPlayerSkin(playerid, 286); }
			else if(PlayerInfo[playerid][pMember] == 3) { ChosenSkin[playerid] = 287; SetPlayerSkin(playerid, 287); }
			else if(PlayerInfo[playerid][pMember] == 4) { ChosenSkin[playerid] = 70; SetPlayerSkin(playerid, 70); }
			else if(PlayerInfo[playerid][pMember] == 5) { ChosenSkin[playerid] = 258; SetPlayerSkin(playerid, 120); }
			else if(PlayerInfo[playerid][pMember] == 6) { ChosenSkin[playerid] = 120; SetPlayerSkin(playerid, 258); }
			else if(PlayerInfo[playerid][pMember] == 8) { ChosenSkin[playerid] = 127; SetPlayerSkin(playerid, 127); }
			else if(PlayerInfo[playerid][pMember] == 9) { ChosenSkin[playerid] = 148; SetPlayerSkin(playerid, 148); }
			else if(PlayerInfo[playerid][pMember] == 10) { ChosenSkin[playerid] = 255; SetPlayerSkin(playerid, 255); }
			else if(PlayerInfo[playerid][pMember] == 11) { ChosenSkin[playerid] = 59; SetPlayerSkin(playerid, 59); }
			else { return 1; }
			GetPlayerPos(playerid, ChangePos[playerid][0],ChangePos[playerid][1],ChangePos[playerid][2]);
			ChangePos2[playerid][0] = GetPlayerInterior(playerid);
			ChangePos2[playerid][1] = 1;
			SetPlayerInterior(playerid,0);
			new rand = random(sizeof(gInviteSpawns));
			SetPlayerPos(playerid, gInviteSpawns[rand][0], gInviteSpawns[rand][1], gInviteSpawns[rand][2]); // Warp the player
			SetPlayerFacingAngle(playerid, gInviteSpawns[rand][3]);
			SetPlayerCameraPos(playerid,gInviteSpawns[rand][0] + 3, gInviteSpawns[rand][1], gInviteSpawns[rand][2]);
			SetPlayerCameraLookAt(playerid,gInviteSpawns[rand][0], gInviteSpawns[rand][1], gInviteSpawns[rand][2]);
			TogglePlayerControllable(playerid, 0);
			SelectChar[playerid] = 255;
			SelectCharID[playerid] = PlayerInfo[playerid][pMember];
			SelectCharPlace[playerid] = 1;
			PlayerInfo[playerid][pModel] = ChosenSkin[playerid];
			PlayerInfo[playerid][pChar] = ChosenSkin[playerid];
			SendClientMessage(playerid, COLOR_LIGHTRED, "* Use 'next' to Select the char you want to use.");
			SendClientMessage(playerid, COLOR_LIGHTRED, "* If you've found the Char you want to use, type 'done'.");
		}
		else
		{
			SendClientMessage(playerid, COLOR_GRAD2, "   You are not in a Clothing Shop !");
			return 1;
		}
	}
	else
	{
		SendClientMessage(playerid,COLOR_GREY, "   You are not in a Force / Organisation !");
		return 1;
	}
	return 1;
}

CMD:lotto(playerid, params[]) {
	if(PlayerInfo[playerid][pLottoNr] > 0)
	{
		SendClientMessage(playerid, COLOR_GREY, "   You already have a Lottery Ticket !");
		return 1;
	}
	if(GetPlayerMoney(playerid) < 1500)
	{
		SendClientMessage(playerid, COLOR_GREY, "   You need $1500 for a Lottery Ticket !");
		return 1;
	}
	//if(!strlen(tmp))
	{
		SendClientMessage(playerid, COLOR_WHITE,"Uzycie: /lotto [number]");
		return 1;
	}
	new lottonr;
	if(lottonr < 1 || lottonr > 80) { SendClientMessage(playerid, COLOR_GREY, "   Lottery Number not below 1 or above 80 !"); return 1; }
	format(gString, sizeof(gString), "* You bought a Lottery Ticket with number: %d.", lottonr);
	SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
	GivePlayerMoney(playerid, - 1500);
	PlayerInfo[playerid][pLottoNr] = lottonr;
	return 1;
}

CMD:take(playerid, params[]) {
	if(gTeam[playerid] == 2 || IsACop(playerid))
	{
		if(PlayerInfo[playerid][pRank] < 2)
		{
			SendClientMessage(playerid, COLOR_GREY, "   You need to be Rank 2 or Higher for this action !");
			return 1;
		}
		new x_nr[256];
		if(!strlen(x_nr)) {
			SendClientMessage(playerid, COLOR_WHITE, "|__________________ Take Licenses __________________|");
			SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /take [licensename] [playerid/PartOfName]");
			SendClientMessage(playerid, COLOR_GREY, "Available names: Driverslicense, Flyinglicense, Boatlicense, Gunlicense, Weapons, Drugs, Materials");
			SendClientMessage(playerid, COLOR_WHITE, "|___________________________________________________|");
			return 1;
		}
		if(strcmp(x_nr,"driverslicense",true) == 0)
		{
			//if(!strlen(tmp))
			{
				SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /take driverslicense [playerid/PartOfName]");
				return 1;
			}
			new giveplayerid;
			if(IsPlayerConnected(giveplayerid))
			{
				if(giveplayerid != INVALID_PLAYER_ID)
				{
					if (ProxDetectorS(8.0, playerid, giveplayerid))
					{
						format(gString, sizeof(gString), "* You have taken away %s's Drivers License.", PlayerInfo[giveplayerid][pName]);
						SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
						format(gString, sizeof(gString), "* Officer %s has taken away your Drivers License.", PlayerInfo[playerid][pName]);
						SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
						PlayerInfo[giveplayerid][pCarLic] = 0;
					}
					else
					{
						SendClientMessage(playerid, COLOR_GREY, "   That player is not near you !");
						return 1;
					}
				}
			}
			else
			{
				SendClientMessage(playerid, COLOR_GREY, "   That player is Offline !");
				return 1;
			}
		}
		else if(strcmp(x_nr,"flyinglicense",true) == 0)
		{
			//if(!strlen(tmp))
			{
				SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /take flyinglicense [playerid/PartOfName]");
				return 1;
			}
			new giveplayerid;
			if(IsPlayerConnected(giveplayerid))
			{
				if(giveplayerid != INVALID_PLAYER_ID)
				{
					if (ProxDetectorS(8.0, playerid, giveplayerid))
					{
						format(gString, sizeof(gString), "* You have taken away %s's Flying License.", PlayerInfo[giveplayerid][pName]);
						SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
						format(gString, sizeof(gString), "* Officer %s has taken away your Flying License.", PlayerInfo[playerid][pName]);
						SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
						PlayerInfo[giveplayerid][pFlyLic] = 0;
					}
					else
					{
						SendClientMessage(playerid, COLOR_GREY, "   That player is not near you !");
						return 1;
					}
				}
			}
			else
			{
				SendClientMessage(playerid, COLOR_GREY, "   That player is Offline !");
				return 1;
			}
		}
		else if(strcmp(x_nr,"gunlicense",true) == 0)
		{
			//if(!strlen(tmp)) 
			{
				SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /take driverslicense [playerid/PartOfName]");
				return 1;
			}
			new giveplayerid;
			if(IsPlayerConnected(giveplayerid))
			{
				if(giveplayerid != INVALID_PLAYER_ID)
				{
					if (ProxDetectorS(8.0, playerid, giveplayerid))
					{
						format(gString, sizeof(gString), "* You have taken away %s's Weapon License.", PlayerInfo[giveplayerid][pName]);
						SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
						format(gString, sizeof(gString), "* Officer %s has taken away your Weapon License.", PlayerInfo[playerid][pName]);
						SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
						PlayerInfo[giveplayerid][pGunLic] = 0;
					}
					else
					{
						SendClientMessage(playerid, COLOR_GREY, "   That player is not near you !");
						return 1;
					}
				}
			}
			else
			{
				SendClientMessage(playerid, COLOR_GREY, "   That player is Offline !");
				return 1;
			}
		}
		else if(strcmp(x_nr,"boatlicense",true) == 0)
		{
			//if(!strlen(tmp))
			{
				SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /take boatlicense [playerid/PartOfName]");
				return 1;
			}
			new giveplayerid;
			if(IsPlayerConnected(giveplayerid))
			{
				if(giveplayerid != INVALID_PLAYER_ID)
				{
					if (ProxDetectorS(8.0, playerid, giveplayerid))
					{
						format(gString, sizeof(gString), "* You have taken away %s's Boat License.", PlayerInfo[giveplayerid][pName]);
						SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
						format(gString, sizeof(gString), "* Officer %s has taken away your Boat License.", PlayerInfo[playerid][pName]);
						SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
						PlayerInfo[giveplayerid][pBoatLic] = 0;
					}
					else
					{
						SendClientMessage(playerid, COLOR_GREY, "   That player is not near you !");
						return 1;
					}
				}
			}
			else
			{
				SendClientMessage(playerid, COLOR_GREY, "   That player is Offline !");
				return 1;
			}
		}
		else if(strcmp(x_nr,"weapons",true) == 0)
		{
			//if(!strlen(tmp)) 
			{
				SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /take weapons [playerid/PartOfName]");
				return 1;
			}
			new giveplayerid;
			if(IsPlayerConnected(giveplayerid))
			{
				if(giveplayerid != INVALID_PLAYER_ID)
				{
					if (ProxDetectorS(8.0, playerid, giveplayerid))
					{
						format(gString, sizeof(gString), "* You have taken away %s's Weapons.", PlayerInfo[giveplayerid][pName]);
						SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
						format(gString, sizeof(gString), "* Officer %s has taken away your Weapons.", PlayerInfo[playerid][pName]);
						SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
						ResetPlayerWeapons(giveplayerid);
						PlayerInfo[giveplayerid][pGun1] = 0; PlayerInfo[giveplayerid][pAmmo1] = 0;
						PlayerInfo[giveplayerid][pGun2] = 0; PlayerInfo[giveplayerid][pAmmo2] = 0;
						PlayerInfo[giveplayerid][pGun3] = 0; PlayerInfo[giveplayerid][pAmmo3] = 0;
						PlayerInfo[giveplayerid][pGun4] = 0; PlayerInfo[giveplayerid][pAmmo4] = 0;
					}
					else
					{
						SendClientMessage(playerid, COLOR_GREY, "   That player is not near you !");
						return 1;
					}
				}
			}
			else
			{
				SendClientMessage(playerid, COLOR_GREY, "   That player is Offline !");
				return 1;
			}
		}
		else if(strcmp(x_nr,"drugs",true) == 0)
		{
			//if(!strlen(tmp)) 
			{
				SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /take drugs [playerid/PartOfName]");
				return 1;
			}
			new giveplayerid;
			if(IsPlayerConnected(giveplayerid))
			{
				if(giveplayerid != INVALID_PLAYER_ID)
				{
					if (ProxDetectorS(8.0, playerid, giveplayerid))
					{
						format(gString, sizeof(gString), "* You have taken away %s's Drugs.", PlayerInfo[giveplayerid][pName]);
						SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
						format(gString, sizeof(gString), "* Officer %s has taken away your Drugs.", PlayerInfo[playerid][pName]);
						SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
						PlayerInfo[giveplayerid][pDrugs] = 0;
					}
					else
					{
						SendClientMessage(playerid, COLOR_GREY, "   That player is not near you !");
						return 1;
					}
				}
			}
			else
			{
				SendClientMessage(playerid, COLOR_GREY, "   That player is Offline !");
				return 1;
			}
		}
		else if(strcmp(x_nr,"materials",true) == 0)
		{
			//if(!strlen(tmp)) 
			{
				SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /take materials [playerid/PartOfName]");
				return 1;
			}
			new giveplayerid;
			if(IsPlayerConnected(giveplayerid))
			{
				if(giveplayerid != INVALID_PLAYER_ID)
				{
					if (ProxDetectorS(8.0, playerid, giveplayerid))
					{
						format(gString, sizeof(gString), "* You have taken away %s's Materials.", PlayerInfo[giveplayerid][pName]);
						SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
						format(gString, sizeof(gString), "* Officer %s as taken away your Materials.", PlayerInfo[playerid][pName]);
						SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
						PlayerInfo[giveplayerid][pMats] = 0;
					}
					else
					{
						SendClientMessage(playerid, COLOR_GREY, "   That player is not near you !");
						return 1;
					}
				}
			}
			else
			{
				SendClientMessage(playerid, COLOR_GREY, "   That player is Offline !");
				return 1;
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   Unknown Take name !");
			return 1;
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   You are not a Cop !");
		return 1;
	}
	return 1;
}

CMD:drink(playerid, params[]) {
	if(IsAtBar(playerid))
	{
		if(PlayerDrunk[playerid] < 10)
		{
			new Float:health;
			new x_nr[256];
			if(!strlen(x_nr)) {
				SendClientMessage(playerid, COLOR_WHITE, "|__________________ Bar Drinks __________________|");
				SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /drink [drinkname]");
				SendClientMessage(playerid, COLOR_GREY, "Available names: Beer ($6), Vodka ($10), Whiskey ($10), Water ($2), Soda($2)");
				SendClientMessage(playerid, COLOR_WHITE, "|________________________________________________|");
				return 1;
			}
			if(strcmp(x_nr,"beer",true) == 0)
			{
				if(PlayerInfo[playerid][pAge] < 16)
				{
					SendClientMessage(playerid, COLOR_WHITE, "Bartender: Sorry, you need to be 16 years to get this drink.");
					return 1;
				}
				GivePlayerMoney(playerid, - 6);
				PlayerDrunk[playerid] += 1;
				if(PlayerDrunk[playerid] >= 5) { GameTextForPlayer(playerid, "~w~You are~n~~p~Drunk", 3500, 1); }
				if(GetPlayerHealth(playerid, health) < 100)
				{
					if(PlayerInfo[playerid][pAlcoholPerk] > 0) { PlayerDrunk[playerid] += 1; new hp = 2 * PlayerInfo[playerid][pAlcoholPerk]; hp += 15; SetPlayerHealth(playerid, health + hp); }
					else { SetPlayerHealth(playerid, health + 15.0); }
				}
			}
			else if(strcmp(x_nr,"vodka",true) == 0)
			{
				if(PlayerInfo[playerid][pAge] < 18)
				{
					SendClientMessage(playerid, COLOR_WHITE, "Bartender: Sorry, you need to be 16 years to get this drink.");
					return 1;
				}
				GivePlayerMoney(playerid, - 10);
				PlayerDrunk[playerid] += 2;
				if(PlayerDrunk[playerid] >= 5) { GameTextForPlayer(playerid, "~w~You are~n~~p~Drunk", 3500, 1); }
				if(GetPlayerHealth(playerid, health) < 100)
				{
					if(PlayerInfo[playerid][pAlcoholPerk] > 0) { PlayerDrunk[playerid] += 1; new hp = 2 * PlayerInfo[playerid][pAlcoholPerk]; hp += 25; SetPlayerHealth(playerid, health + hp); }
					else { SetPlayerHealth(playerid, health + 25.0); }
				}
			}
			else if(strcmp(x_nr,"whiskey",true) == 0)
			{
				if(PlayerInfo[playerid][pAge] < 18)
				{
					SendClientMessage(playerid, COLOR_WHITE, "Bartender: Sorry, you need to be 16 years to get this drink.");
					return 1;
				}
				GivePlayerMoney(playerid, - 10);
				PlayerDrunk[playerid] += 3;
				if(PlayerDrunk[playerid] >= 5) { GameTextForPlayer(playerid, "~w~You are~n~~p~Drunk", 3500, 1); }
				if(GetPlayerHealth(playerid, health) < 100)
				{
					if(PlayerInfo[playerid][pAlcoholPerk] > 0) { PlayerDrunk[playerid] += 1; new hp = 2 * PlayerInfo[playerid][pAlcoholPerk]; hp += 27; SetPlayerHealth(playerid, health + hp); }
					else { SetPlayerHealth(playerid, health + 27.0); }
				}
			}
			else if(strcmp(x_nr,"water",true) == 0)
			{
				GivePlayerMoney(playerid, - 2);
				if(GetPlayerHealth(playerid, health) < 100)
				{
					if(PlayerInfo[playerid][pAlcoholPerk] > 0) { new hp = 2 * PlayerInfo[playerid][pAlcoholPerk]; hp += 5; SetPlayerHealth(playerid, health + hp); }
					else { SetPlayerHealth(playerid, health + 5.0); }
				}
			}
			else if(strcmp(x_nr,"soda",true) == 0)
			{
				GivePlayerMoney(playerid, - 2);
				if(GetPlayerHealth(playerid, health) < 100)
				{
					if(PlayerInfo[playerid][pAlcoholPerk] > 0) { new hp = 2 * PlayerInfo[playerid][pAlcoholPerk]; hp += 5; SetPlayerHealth(playerid, health + hp); }
					else { SetPlayerHealth(playerid, health + 5.0); }
				}
			}
			else
			{
				SendClientMessage(playerid, COLOR_WHITE, "Bartender: I don't know that Drink Name.");
				return 1;
			}
			GetPlayerName(playerid, PlayerInfo[playerid][pName], sizeof(PlayerInfo[playerid][pName]));
			format(gString, sizeof(gString), "* %s drinks a %s.", PlayerInfo[playerid][pName] ,x_nr);
			ProxDetector(30.0, playerid, gString, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   You can't drink anymore, you will throw up !");
			return 1;
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   You are not at a Bar !");
		return 1;
	}
	return 1;
}

CMD:setchamp(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] >= 4)
	{
		//if(!strlen(tmp))
		{
			SendClientMessage(playerid, COLOR_GRAD1, "Uzycie: /setchamp [playerid/PartOfName]");
			return 1;
		}
		new giveplayerid;
		if(IsPlayerConnected(giveplayerid))
		{
			if(giveplayerid != INVALID_PLAYER_ID)
			{
				new nstring[MAX_PLAYER_NAME];
				format(nstring, sizeof(nstring), "%s", PlayerInfo[giveplayerid][pName]);
				strmid(Titel[TitelName], nstring, 0, strlen(nstring), 255);
				Titel[TitelWins] = PlayerInfo[giveplayerid][pWins];
				Titel[TitelLoses] = PlayerInfo[giveplayerid][pLoses];
				SaveBoxer();
				format(gString, sizeof(gString), "* You have made %s the new Boxing Champion.", PlayerInfo[giveplayerid][pName]);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   That player is Offline !");
			return 1;
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GRAD1, "   you are not authorized to use that command!");
	}
	return 1;
}

CMD:boxstats(playerid, params[]) {
	if(PlayerInfo[playerid][pJob] != 12)
	{
		SendClientMessage(playerid, COLOR_GREY, "   You are not a Boxer !");
		return 1;
	}
	new ttext[20];//Title
	new clevel = PlayerInfo[playerid][pBoxSkill];
	if(clevel >= 0 && clevel <= 50) { ttext = "Beginner"; }
	else if(clevel >= 51 && clevel <= 200) { ttext = "Amateur"; }
	else if(clevel >= 201 && clevel <= 400) { ttext = "Professional"; }
	new ntext[20];//NickName
	new level = PlayerInfo[playerid][pWins];
	if(level > 0 && PlayerInfo[playerid][pLoses] == 0)
	{
		ntext = "Undefeated";
	}
	else
	{
		if(level >= 0 && level <= 10) { ntext = "Newcomer"; }
		else if(level >= 11 && level <= 20) { ntext = "Touchy Fist"; }
		else if(level >= 21 && level <= 30) { ntext = "Nut Cracker"; }
		else if(level >= 31 && level <= 40) { ntext = "Tommygun"; }
		else if(level >= 41 && level <= 50) { ntext = "Skull Breaker"; }
		else if(level >= 51 && level <= 60) { ntext = "Light Speed"; }
		else if(level >= 61 && level <= 70) { ntext = "Unbroken Warrior"; }
		else if(level >= 71) { ntext = "Itallion Stallion"; }
	}
	SendClientMessage(playerid, COLOR_WHITE, "|__________________ Boxing Records __________________|");
	format(gString, sizeof(gString), "| Current Champion: %s, with [%d] Winnings and [%d] Losses.", Titel[TitelName],Titel[TitelWins],Titel[TitelLoses]);
	SendClientMessage(playerid, COLOR_GREY, gString);
	format(gString, sizeof(gString), "| Current Title: %s.", ttext);
	SendClientMessage(playerid, COLOR_GREY, gString);
	format(gString, sizeof(gString), "| Current NickName: %s.", ntext);
	SendClientMessage(playerid, COLOR_GREY, gString);
	format(gString, sizeof(gString), "| Total Wins: %d.", PlayerInfo[playerid][pWins]);
	SendClientMessage(playerid, COLOR_GREY, gString);
	format(gString, sizeof(gString), "| Total Losses: %d.", PlayerInfo[playerid][pLoses]);
	SendClientMessage(playerid, COLOR_GREY, gString);
	SendClientMessage(playerid, COLOR_WHITE, "|____________________________________________________|");
	return 1;
}

CMD:fight(playerid, params[]) {
	if(PlayerInfo[playerid][pJob] != 12)
	{
		SendClientMessage(playerid, COLOR_GREY, "   You are not a Boxer !");
		return 1;
	}
	if(InRing > 0)
	{
		SendClientMessage(playerid, COLOR_GREY, "   There is already a Fight going on, wait for it to Finish !");
		return 1;
	}
	if(PlayerBoxing[playerid] > 0)
	{
		SendClientMessage(playerid, COLOR_GREY, "   You are already Fighting !");
		return 1;
	}
	if(!PlayerToPoint(20.0,playerid,765.9343,0.2761,1000.7173))
	{
		SendClientMessage(playerid, COLOR_GREY, "   You are not at the Grove Street Gym !");
		return 1;
	}
	//if(!strlen(tmp)) 
	{
		SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /fight [Playerid/PartOfName]");
		return 1;
	}
	new giveplayerid;
	if(IsPlayerConnected(giveplayerid))
	{
		if(giveplayerid != INVALID_PLAYER_ID)
		{
			if (ProxDetectorS(8.0, playerid, giveplayerid))
			{
				if(giveplayerid == playerid) { SendClientMessage(playerid, COLOR_GREY, "You cannot Box with yourself!"); return 1; }
				format(gString, sizeof(gString), "* You offerd a Boxing Challenge to %s.", PlayerInfo[giveplayerid][pName]);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
				format(gString, sizeof(gString), "* Boxer %s wants to Fight with you (type /accept boxing) to accept.", PlayerInfo[playerid][pName]);
				SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
				BoxOffer[giveplayerid] = playerid;
			}
			else
			{
				SendClientMessage(playerid, COLOR_GREY, "   That player is not near you !");
				return 1;
			}
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   That player is Offline !");
		return 1;
	}
	return 1;
}

CMD:music(playerid, params[]) {
	if(PlayerInfo[playerid][pCDPlayer])
	{
		new x_nr[256];
		if(!strlen(x_nr)) {
			SendClientMessage(playerid, COLOR_WHITE, "|__________________ Music __________________|");
			SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /music [name]");
			SendClientMessage(playerid, COLOR_GREY, "Available names: On, Off, Next");
			SendClientMessage(playerid, COLOR_WHITE, "|___________________________________________|");
			return 1;
		}
		if(strcmp(x_nr,"on",true) == 0)
		{
			GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~g~CD Player On", 5000, 5);
			new channel = Music[playerid];
			PlayerPlaySound(playerid, Songs[channel][0], 0.0, 0.0, 0.0);
		}
		else if(strcmp(x_nr,"off",true) == 0)
		{
			GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~r~CD Player Off", 5000, 5);
			PlayerFixRadio(playerid);
		}
		else if(strcmp(x_nr,"next",true) == 0)
		{
			if(Music[playerid] == 0) { Music[playerid] = 1; }
			else if(Music[playerid] == 1) { Music[playerid] = 2; }
			else if(Music[playerid] == 2) { Music[playerid] = 3; }
			else if(Music[playerid] == 3) { Music[playerid] = 4; }
			else if(Music[playerid] == 4) { Music[playerid] = 5; }
			else if(Music[playerid] == 5) { Music[playerid] = 6; }
			else if(Music[playerid] == 6) { Music[playerid] = 0; }
			new channel = Music[playerid];
			PlayerPlaySound(playerid, Songs[channel][0], 0.0, 0.0, 0.0);
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   Unknown music command !");
			return 1;
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   You don't have a CD-Player !");
		return 1;
	}
	return 1;
}

CMD:service(playerid, params[]) {
	new x_nr[256];
	if(!strlen(x_nr)) {
		SendClientMessage(playerid, COLOR_WHITE, "|__________________ Service Names __________________|");
		SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /service [name]");
		SendClientMessage(playerid, COLOR_GREY, "Available names: Taxi, Bus, Medic, Mechanic");
		SendClientMessage(playerid, COLOR_WHITE, "|________________________________________________|");
		return 1;
	}
	if(strcmp(x_nr,"taxi",true) == 0)
	{
		if(TaxiDrivers < 1)
		{
			SendClientMessage(playerid, COLOR_GREY, "   There are no Taxi Drivers On Duty at the moment, try again later !");
			return 1;
		}
		if(TransportDuty[playerid] > 0)
		{
			SendClientMessage(playerid, COLOR_GREY, "   You can't call for a Taxi now !");
			return 1;
		}
		format(gString, sizeof(gString), "** %s is in need of a Taxi Driver. (use /accept taxi to accept the call)", PlayerInfo[playerid][pName]);
		SendFamilyMessage(10, TEAM_AZTECAS_COLOR, gString);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You have called for a Taxi Driver, wait for a reply.");
		TaxiCall = playerid;
		return 1;
	}
	else if(strcmp(x_nr,"bus",true) == 0)
	{
		if(BusDrivers < 1)
		{
			SendClientMessage(playerid, COLOR_GREY, "   There are no Bus Drivers On Duty at the moment, try again later !");
			return 1;
		}
		if(TransportDuty[playerid] > 0)
		{
			SendClientMessage(playerid, COLOR_GREY, "   You can't call for a Bus now !");
			return 1;
		}
		format(gString, sizeof(gString), "** %s is in need of a Bus Driver. (use /accept bus to accept the call)", PlayerInfo[playerid][pName]);
		SendJobMessage(14, TEAM_AZTECAS_COLOR, gString);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You have called for a Bus Driver, wait for a reply.");
		BusCall = playerid;
		return 1;
	}
	else if(strcmp(x_nr,"medic",true) == 0)
	{
		if(Medics < 1)
		{
			SendClientMessage(playerid, COLOR_GREY, "   There are no Medics On Duty at the moment, try again later !");
			return 1;
		}
		format(gString, sizeof(gString), "** %s is in need of a Medic. (use /accept medic to accept the call)", PlayerInfo[playerid][pName]);
		SendRadioMessage(4, TEAM_AZTECAS_COLOR, gString);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You have called for a Medic, wait for a reply.");
		MedicCall = playerid;
		return 1;
	}
	else if(strcmp(x_nr,"mechanic",true) == 0)
	{
		if(Mechanics < 1)
		{
			SendClientMessage(playerid, COLOR_GREY, "   There are no Car Mechanics On Duty at the moment, try again later !");
			return 1;
		}
		format(gString, sizeof(gString), "** %s is in need of a Car Mechanic. (use /accept mechanic to accept the call)", PlayerInfo[playerid][pName]);
		SendJobMessage(7, TEAM_AZTECAS_COLOR, gString);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You have called for a Car Mechanic, wait for a reply.");
		MechanicCall = playerid;
		return 1;
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   Unknown service name !");
		return 1;
	}
	return 1;
}

CMD:tie(playerid, params[]) {
	if(IsAMember(playerid) || PlayerInfo[playerid][pFMember] < 255)
	{
		if(PlayerInfo[playerid][pRank] < 3)
		{
			SendClientMessage(playerid, COLOR_GREY, "   You need Rank 3 or higher to tie people up !");
			return 1;
		}
		//if(!strlen(tmp)) 
		{
			SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /tie [Playerid/PartOfName]");
			return 1;
		}
		new giveplayerid;
		if(IsPlayerConnected(giveplayerid))
		{
			if(giveplayerid != INVALID_PLAYER_ID)
			{
				if(PlayerTied[giveplayerid] > 0)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Player already Tied !");
					return 1;
				}
				if (ProxDetectorS(8.0, playerid, giveplayerid))
				{
					new car = GetPlayerVehicleID(playerid);
					if(giveplayerid == playerid) { SendClientMessage(playerid, COLOR_GREY, "You cannot Tie up yourself!"); return 1; }
					if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == 2 && IsPlayerInVehicle(giveplayerid, car))
					{
						format(gString, sizeof(gString), "* You were tied up by %s, till untie.", PlayerInfo[playerid][pName]);
						SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
						format(gString, sizeof(gString), "* You tied %s up, till untie.", PlayerInfo[giveplayerid][pName]);
						SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
						format(gString, sizeof(gString), "* %s ties %s up, so he wont go anywhere.", PlayerInfo[playerid][pName] ,PlayerInfo[giveplayerid][pName]);
						ProxDetector(30.0, playerid, gString, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
						GameTextForPlayer(giveplayerid, "~r~Tied", 2500, 3);
						TogglePlayerControllable(giveplayerid, 0);
						PlayerTied[giveplayerid] = 1;
					}
					else
					{
						SendClientMessage(playerid, COLOR_GREY, "   Player not in your Car, or your not the Driver !");
						return 1;
					}
				}
				else
				{
					SendClientMessage(playerid, COLOR_GREY, "   That player is not near you !");
					return 1;
				}
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   That player is Offline !");
			return 1;
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   You are not a Family Member / Leader !");
	}
	return 1;
}

CMD:untie(playerid, params[]) {
	if(IsAMember(playerid) || PlayerInfo[playerid][pFMember] < 255)
	{
		if(PlayerInfo[playerid][pRank] < 3)
		{
			SendClientMessage(playerid, COLOR_GREY, "   You need Rank 3 or higher to untie people !");
			return 1;
		}
		//if(!strlen(tmp))
		{
			SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /untie [Playerid/PartOfName]");
			return 1;
		}
		new giveplayerid;
		if(IsPlayerConnected(giveplayerid))
		{
			if(giveplayerid != INVALID_PLAYER_ID)
			{
				if (ProxDetectorS(8.0, playerid, giveplayerid))
				{
					if(giveplayerid == playerid) { SendClientMessage(playerid, COLOR_GREY, "You cannot Untie yourself!"); return 1; }
					if(PlayerTied[giveplayerid])
					{
						format(gString, sizeof(gString), "* You were Untied by %s.", PlayerInfo[playerid][pName]);
						SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
						format(gString, sizeof(gString), "* You Untied %s.", PlayerInfo[giveplayerid][pName]);
						SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
						GameTextForPlayer(giveplayerid, "~g~Untied", 2500, 3);
						TogglePlayerControllable(giveplayerid, 1);
						PlayerTied[giveplayerid] = 0;
					}
					else
					{
						SendClientMessage(playerid, COLOR_GREY, "   That player isn't Tied up !");
						return 1;
					}
				}
				else
				{
					SendClientMessage(playerid, COLOR_GREY, "   That player is not near you !");
					return 1;
				}
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   That player is Offline !");
			return 1;
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   You are not a Family Member / Leader !");
	}
	return 1;
}

CMD:sell(playerid, params[]) {
	new x_nr[256];
	if(!strlen(x_nr)) {
		SendClientMessage(playerid, COLOR_WHITE, "|__________________ Selling __________________|");
		SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /sell [name]");
		SendClientMessage(playerid, COLOR_GREY, "Available names: Fish, Cooked");
		SendClientMessage(playerid, COLOR_WHITE, "|_____________________________________________|");
		return 1;
	}
	if(strcmp(x_nr,"fish",true) == 0)
	{
		if (!PlayerToPoint(100, playerid,-30.875, -88.9609, 1004.53))//centerpoint 24-7
		{
			SendClientMessage(playerid, COLOR_GRAD2, "   You are not in a 24-7 !");
			return 1;
		}
		//if(!strlen(tmp))
		{
			SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /sell fish [fish]");
			return 1;
		}
		new price;
		new fishid;
		if(fishid < 1 || fishid > 5) { SendClientMessage(playerid, COLOR_GREY, "   Fish number cant be below 1 or above 5 !"); return 1; }
		else if(fishid == 1 && Fishes[playerid][pWeight1] < 1) { SendClientMessage(playerid, COLOR_GREY, "   You didnt even catch a Fish at that number(1) !"); return 1; }
		else if(fishid == 2 && Fishes[playerid][pWeight2] < 1) { SendClientMessage(playerid, COLOR_GREY, "   You didnt even catch a Fish at that number(2) !"); return 1; }
		else if(fishid == 3 && Fishes[playerid][pWeight3] < 1) { SendClientMessage(playerid, COLOR_GREY, "   You didnt even catch a Fish at that number(3) !"); return 1; }
		else if(fishid == 4 && Fishes[playerid][pWeight4] < 1) { SendClientMessage(playerid, COLOR_GREY, "   You didnt even catch a Fish at that number(4) !"); return 1; }
		else if(fishid == 5 && Fishes[playerid][pWeight5] < 1) { SendClientMessage(playerid, COLOR_GREY, "   You didnt even catch a Fish at that number(5) !"); return 1; }
		ConsumingMoney[playerid] = 1;
		switch (fishid)
		{
			case 1:
			{
			if(Fishes[playerid][pWeight1] < 20)
			{
				SendClientMessage(playerid, COLOR_WHITE, "We are only interested in Fishes weighting 20 LBS or more.");
				return 1;
			}
			price = FishCost(playerid, Fishes[playerid][pFid1]);
			price = price * Fishes[playerid][pWeight1];
			if(PlayerInfo[playerid][pTraderPerk] > 0)
			{
				new skill = price / 100;
				new payout = (skill)*(5);
				price += payout;
			}
			GameTextForPlayer(playerid, "~g~Fish~n~~r~Sold", 3000, 1);
			format(gString, sizeof(gString), "* You have sold your %s that weights %d, for $%d.", Fishes[playerid][pFish1],Fishes[playerid][pWeight1],price);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
			GivePlayerMoney(playerid, price);
			ClearFishID(playerid, 1);
			}
			case 2:
			{
			if(Fishes[playerid][pWeight2] < 20)
			{
				SendClientMessage(playerid, COLOR_WHITE, "We are only interested in Fishes weighting 20 LBS or more.");
				return 1;
			}
			price = FishCost(playerid, Fishes[playerid][pFid2]);
			price = price * Fishes[playerid][pWeight2];
			if(PlayerInfo[playerid][pTraderPerk] > 0)
			{
				new skill = price / 100;
				new payout = (skill)*(5);
				price += payout;
			}
			GameTextForPlayer(playerid, "~g~Fish~n~~r~Sold", 3000, 1);
			format(gString, sizeof(gString), "* You have sold your %s that weights %d, for $%d.", Fishes[playerid][pFish2],Fishes[playerid][pWeight2],price);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
			GivePlayerMoney(playerid, price);
			ClearFishID(playerid, 2);
			}
			case 3:
			{
			if(Fishes[playerid][pWeight3] < 20)
			{
				SendClientMessage(playerid, COLOR_WHITE, "We are only interested in Fishes weighting 20 LBS or more.");
				return 1;
			}
			price = FishCost(playerid, Fishes[playerid][pFid3]);
			price = price * Fishes[playerid][pWeight3];
			if(PlayerInfo[playerid][pTraderPerk] > 0)
			{
			new skill = price / 100;
			new payout = (skill)*(5);
			price += payout;
			}
			GameTextForPlayer(playerid, "~g~Fish~n~~r~Sold", 3000, 1);
			format(gString, sizeof(gString), "* You have sold your %s that weights %d, for $%d.", Fishes[playerid][pFish3],Fishes[playerid][pWeight3],price);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
			GivePlayerMoney(playerid, price);
			ClearFishID(playerid, 3);
			}
			case 4:
			{
			if(Fishes[playerid][pWeight4] < 20)
			{
				SendClientMessage(playerid, COLOR_WHITE, "We are only interested in Fishes weighting 20 LBS or more.");
				return 1;
			}
			price = FishCost(playerid, Fishes[playerid][pFid4]);
			price = price * Fishes[playerid][pWeight4];
			if(PlayerInfo[playerid][pTraderPerk] > 0)
			{
				new skill = price / 100;
				new payout = (skill)*(5);
				price += payout;
			}
			GameTextForPlayer(playerid, "~g~Fish~n~~r~Sold", 3000, 1);
			format(gString, sizeof(gString), "* You have sold your %s that weights %d, for $%d.", Fishes[playerid][pFish4],Fishes[playerid][pWeight4],price);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
			GivePlayerMoney(playerid, price);
			ClearFishID(playerid, 4);
			}
			case 5:
			{
			if(Fishes[playerid][pWeight5] < 20)
			{
				SendClientMessage(playerid, COLOR_WHITE, "We are only interested in Fishes weighting 20 LBS or more.");
				return 1;
			}
			price = FishCost(playerid, Fishes[playerid][pFid5]);
			price = price * Fishes[playerid][pWeight5];
			if(PlayerInfo[playerid][pTraderPerk] > 0)
			{
			new skill = price / 100;
			new payout = (skill)*(5);
			price += payout;
			}
			GameTextForPlayer(playerid, "~g~Fish~n~~r~Sold", 3000, 1);
			format(gString, sizeof(gString), "* You have sold your %s that weights %d, for $%d.", Fishes[playerid][pFish5],Fishes[playerid][pWeight5],price);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
			GivePlayerMoney(playerid, price);
			ClearFishID(playerid, 5);
			}
		}
		Fishes[playerid][pLastFish] = 0;
		Fishes[playerid][pFishID] = 0;
		return 1;
	}
	else if(strcmp(x_nr,"cooked",true) == 0)
	{
		//if(!strlen(tmp))
		{
			SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /sell cooked [cooknumber] [playerid/PartOfName]");
			return 1;
		}
		new cookid;
		if(cookid < 1 || cookid > 5) { SendClientMessage(playerid, COLOR_GREY, "   Cook number cant be below 1 or above 5 !"); return 1; }
		else if(cookid == 1 && Cooking[playerid][pCWeight1] < 1) { SendClientMessage(playerid, COLOR_GREY, "   You didnt even Cook something at that number(1) !"); return 1; }
		else if(cookid == 2 && Cooking[playerid][pCWeight2] < 1) { SendClientMessage(playerid, COLOR_GREY, "   You didnt even Cook something at that number(2) !"); return 1; }
		else if(cookid == 3 && Cooking[playerid][pCWeight3] < 1) { SendClientMessage(playerid, COLOR_GREY, "   You didnt even Cook something at that number(3) !"); return 1; }
		else if(cookid == 4 && Cooking[playerid][pCWeight4] < 1) { SendClientMessage(playerid, COLOR_GREY, "   You didnt even Cook something at that number(4) !"); return 1; }
		else if(cookid == 5 && Cooking[playerid][pCWeight5] < 1) { SendClientMessage(playerid, COLOR_GREY, "   You didnt even Cook something at that number(5) !"); return 1; }
		//if(!strlen(tmp))
		{
			SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /sell cooked [cooknumber] [playerid/PartOfName]");
			return 1;
		}
		new giveplayerid;
		if(IsPlayerConnected(giveplayerid))
		{
			if(giveplayerid != INVALID_PLAYER_ID)
			{
				switch(cookid)
				{
					case 1:
					{
						if(Cooking[giveplayerid][pCWeight1] < 1)
						{
							format(gString, sizeof(gString), "%s", Cooking[playerid][pCook1]);
							strmid(Cooking[giveplayerid][pCook1], gString, 0, strlen(gString), 255);
							Cooking[giveplayerid][pCWeight1] = Cooking[playerid][pCWeight1];
							Cooking[giveplayerid][pCookID1] = Cooking[playerid][pCookID1];
							format(gString, sizeof(gString), "* %s has given you %s weighting %d (use /cooked to see it).",PlayerInfo[playerid][pName],Cooking[giveplayerid][pCook1],Cooking[giveplayerid][pCWeight1]);
							SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
							format(gString, sizeof(gString), "* You gave %s weighting %d to %s.",Cooking[playerid][pCook1],Cooking[playerid][pCWeight1],PlayerInfo[giveplayerid][pName]);
							SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
						}
						else if(Cooking[giveplayerid][pCWeight2] < 1)
						{
							format(gString, sizeof(gString), "%s", Cooking[playerid][pCook1]);
							strmid(Cooking[giveplayerid][pCook2], gString, 0, strlen(gString), 255);
							Cooking[giveplayerid][pCWeight2] = Cooking[playerid][pCWeight1];
							Cooking[giveplayerid][pCookID2] = Cooking[playerid][pCookID1];
							format(gString, sizeof(gString), "* %s has given you %s weighting %d (use /cooked to see it).",PlayerInfo[playerid][pName],Cooking[giveplayerid][pCook2],Cooking[giveplayerid][pCWeight2]);
							SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
							format(gString, sizeof(gString), "* You gave %s weighting %d to %s.",Cooking[playerid][pCook1],Cooking[playerid][pCWeight1],PlayerInfo[giveplayerid][pName]);
							SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
						}
						else if(Cooking[giveplayerid][pCWeight3] < 1)
						{
							format(gString, sizeof(gString), "%s", Cooking[playerid][pCook1]);
							strmid(Cooking[giveplayerid][pCook3], gString, 0, strlen(gString), 255);
							Cooking[giveplayerid][pCWeight3] = Cooking[playerid][pCWeight1];
							Cooking[giveplayerid][pCookID3] = Cooking[playerid][pCookID1];
							format(gString, sizeof(gString), "* %s has given you %s weighting %d (use /cooked to see it).",PlayerInfo[playerid][pName],Cooking[giveplayerid][pCook3],Cooking[giveplayerid][pCWeight3]);
							SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
							format(gString, sizeof(gString), "* You gave %s weighting %d to %s.",Cooking[playerid][pCook1],Cooking[playerid][pCWeight1],PlayerInfo[giveplayerid][pName]);
							SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
						}
						else if(Cooking[giveplayerid][pCWeight4] < 1)
						{
							format(gString, sizeof(gString), "%s", Cooking[playerid][pCook1]);
							strmid(Cooking[giveplayerid][pCook4], gString, 0, strlen(gString), 255);
							Cooking[giveplayerid][pCWeight4] = Cooking[playerid][pCWeight1];
							Cooking[giveplayerid][pCookID4] = Cooking[playerid][pCookID1];
							format(gString, sizeof(gString), "* %s has given you %s weighting %d (use /cooked to see it).",PlayerInfo[playerid][pName],Cooking[giveplayerid][pCook4],Cooking[giveplayerid][pCWeight4]);
							SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
							format(gString, sizeof(gString), "* You gave %s weighting %d to %s.",Cooking[playerid][pCook1],Cooking[playerid][pCWeight1],PlayerInfo[giveplayerid][pName]);
							SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
						}
						else if(Cooking[giveplayerid][pCWeight5] < 1)
						{
							format(gString, sizeof(gString), "%s", Cooking[playerid][pCook1]);
							strmid(Cooking[giveplayerid][pCook5], gString, 0, strlen(gString), 255);
							Cooking[giveplayerid][pCWeight5] = Cooking[playerid][pCWeight1];
							Cooking[giveplayerid][pCookID5] = Cooking[playerid][pCookID1];
							format(gString, sizeof(gString), "* %s has given you %s weighting %d (use /cooked to see it).",PlayerInfo[playerid][pName],Cooking[giveplayerid][pCook5],Cooking[giveplayerid][pCWeight5]);
							SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
							format(gString, sizeof(gString), "* You gave %s weighting %d to %s.",Cooking[playerid][pCook1],Cooking[playerid][pCWeight1],PlayerInfo[giveplayerid][pName]);
							SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
						}
						else
						{
							SendClientMessage(playerid, COLOR_GREY, "   That player has no space left in his Cooking List !");
							return 1;
						}
					}
					case 2:
					{
						if(Cooking[giveplayerid][pCWeight1] < 1)
						{
							format(gString, sizeof(gString), "%s", Cooking[playerid][pCook2]);
							strmid(Cooking[giveplayerid][pCook1], gString, 0, strlen(gString), 255);
							Cooking[giveplayerid][pCWeight1] = Cooking[playerid][pCWeight2];
							Cooking[giveplayerid][pCookID1] = Cooking[playerid][pCookID2];
							format(gString, sizeof(gString), "* %s has given you %s weighting %d (use /cooked to see it).",PlayerInfo[playerid][pName],Cooking[giveplayerid][pCook1],Cooking[giveplayerid][pCWeight1]);
							SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
							format(gString, sizeof(gString), "* You gave %s weighting %d to %s.",Cooking[playerid][pCook2],Cooking[playerid][pCWeight2],PlayerInfo[giveplayerid][pName]);
							SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
						}
						else if(Cooking[giveplayerid][pCWeight2] < 1)
						{
							format(gString, sizeof(gString), "%s", Cooking[playerid][pCook2]);
							strmid(Cooking[giveplayerid][pCook2], gString, 0, strlen(gString), 255);
							Cooking[giveplayerid][pCWeight2] = Cooking[playerid][pCWeight2];
							Cooking[giveplayerid][pCookID2] = Cooking[playerid][pCookID2];
							format(gString, sizeof(gString), "* %s has given you %s weighting %d (use /cooked to see it).",PlayerInfo[playerid][pName],Cooking[giveplayerid][pCook2],Cooking[giveplayerid][pCWeight2]);
							SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
							format(gString, sizeof(gString), "* You gave %s weighting %d to %s.",Cooking[playerid][pCook2],Cooking[playerid][pCWeight2],PlayerInfo[giveplayerid][pName]);
							SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
						}
						else if(Cooking[giveplayerid][pCWeight3] < 1)
						{
							format(gString, sizeof(gString), "%s", Cooking[playerid][pCook2]);
							strmid(Cooking[giveplayerid][pCook3], gString, 0, strlen(gString), 255);
							Cooking[giveplayerid][pCWeight3] = Cooking[playerid][pCWeight2];
							Cooking[giveplayerid][pCookID3] = Cooking[playerid][pCookID2];
							format(gString, sizeof(gString), "* %s has given you %s weighting %d (use /cooked to see it).",PlayerInfo[playerid][pName],Cooking[giveplayerid][pCook3],Cooking[giveplayerid][pCWeight3]);
							SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
							format(gString, sizeof(gString), "* You gave %s weighting %d to %s.",Cooking[playerid][pCook2],Cooking[playerid][pCWeight2],PlayerInfo[giveplayerid][pName]);
							SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
						}
						else if(Cooking[giveplayerid][pCWeight4] < 1)
						{
							format(gString, sizeof(gString), "%s", Cooking[playerid][pCook2]);
							strmid(Cooking[giveplayerid][pCook4], gString, 0, strlen(gString), 255);
							Cooking[giveplayerid][pCWeight4] = Cooking[playerid][pCWeight2];
							Cooking[giveplayerid][pCookID4] = Cooking[playerid][pCookID2];
							format(gString, sizeof(gString), "* %s has given you %s weighting %d (use /cooked to see it).",PlayerInfo[playerid][pName],Cooking[giveplayerid][pCook4],Cooking[giveplayerid][pCWeight4]);
							SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
							format(gString, sizeof(gString), "* You gave %s weighting %d to %s.",Cooking[playerid][pCook2],Cooking[playerid][pCWeight2],PlayerInfo[giveplayerid][pName]);
							SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
						}
						else if(Cooking[giveplayerid][pCWeight5] < 1)
						{
							format(gString, sizeof(gString), "%s", Cooking[playerid][pCook2]);
							strmid(Cooking[giveplayerid][pCook5], gString, 0, strlen(gString), 255);
							Cooking[giveplayerid][pCWeight5] = Cooking[playerid][pCWeight2];
							Cooking[giveplayerid][pCookID5] = Cooking[playerid][pCookID2];
							format(gString, sizeof(gString), "* %s has given you %s weighting %d (use /cooked to see it).",PlayerInfo[playerid][pName],Cooking[giveplayerid][pCook5],Cooking[giveplayerid][pCWeight5]);
							SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
							format(gString, sizeof(gString), "* You gave %s weighting %d to %s.",Cooking[playerid][pCook2],Cooking[playerid][pCWeight2],PlayerInfo[giveplayerid][pName]);
							SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
						}
						else
						{
							SendClientMessage(playerid, COLOR_GREY, "   That player has no space left in his Cooking List !");
							return 1;
						}
					}
					case 3:
					{
						if(Cooking[giveplayerid][pCWeight1] < 1)
						{
							format(gString, sizeof(gString), "%s", Cooking[playerid][pCook3]);
							strmid(Cooking[giveplayerid][pCook1], gString, 0, strlen(gString), 255);
							Cooking[giveplayerid][pCWeight1] = Cooking[playerid][pCWeight3];
							Cooking[giveplayerid][pCookID1] = Cooking[playerid][pCookID3];
							format(gString, sizeof(gString), "* %s has given you %s weighting %d (use /cooked to see it).",PlayerInfo[playerid][pName],Cooking[giveplayerid][pCook1],Cooking[giveplayerid][pCWeight1]);
							SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
							format(gString, sizeof(gString), "* You gave %s weighting %d to %s.",Cooking[playerid][pCook3],Cooking[playerid][pCWeight3],PlayerInfo[giveplayerid][pName]);
							SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
						}
						else if(Cooking[giveplayerid][pCWeight2] < 1)
						{
							format(gString, sizeof(gString), "%s", Cooking[playerid][pCook3]);
							strmid(Cooking[giveplayerid][pCook2], gString, 0, strlen(gString), 255);
							Cooking[giveplayerid][pCWeight2] = Cooking[playerid][pCWeight3];
							Cooking[giveplayerid][pCookID2] = Cooking[playerid][pCookID3];
							format(gString, sizeof(gString), "* %s has given you %s weighting %d (use /cooked to see it).",PlayerInfo[playerid][pName],Cooking[giveplayerid][pCook2],Cooking[giveplayerid][pCWeight2]);
							SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
							format(gString, sizeof(gString), "* You gave %s weighting %d to %s.",Cooking[playerid][pCook3],Cooking[playerid][pCWeight3],PlayerInfo[giveplayerid][pName]);
							SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
						}
						else if(Cooking[giveplayerid][pCWeight3] < 1)
						{
							format(gString, sizeof(gString), "%s", Cooking[playerid][pCook3]);
							strmid(Cooking[giveplayerid][pCook3], gString, 0, strlen(gString), 255);
							Cooking[giveplayerid][pCWeight3] = Cooking[playerid][pCWeight3];
							Cooking[giveplayerid][pCookID3] = Cooking[playerid][pCookID3];
							format(gString, sizeof(gString), "* %s has given you %s weighting %d (use /cooked to see it).",PlayerInfo[playerid][pName],Cooking[giveplayerid][pCook3],Cooking[giveplayerid][pCWeight3]);
							SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
							format(gString, sizeof(gString), "* You gave %s weighting %d to %s.",Cooking[playerid][pCook3],Cooking[playerid][pCWeight3],PlayerInfo[giveplayerid][pName]);
							SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
						}
						else if(Cooking[giveplayerid][pCWeight4] < 1)
						{
							format(gString, sizeof(gString), "%s", Cooking[playerid][pCook3]);
							strmid(Cooking[giveplayerid][pCook4], gString, 0, strlen(gString), 255);
							Cooking[giveplayerid][pCWeight4] = Cooking[playerid][pCWeight3];
							Cooking[giveplayerid][pCookID4] = Cooking[playerid][pCookID3];
							format(gString, sizeof(gString), "* %s has given you %s weighting %d (use /cooked to see it).",PlayerInfo[playerid][pName],Cooking[giveplayerid][pCook4],Cooking[giveplayerid][pCWeight4]);
							SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
							format(gString, sizeof(gString), "* You gave %s weighting %d to %s.",Cooking[playerid][pCook3],Cooking[playerid][pCWeight3],PlayerInfo[giveplayerid][pName]);
							SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
						}
						else if(Cooking[giveplayerid][pCWeight5] < 1)
						{
							format(gString, sizeof(gString), "%s", Cooking[playerid][pCook3]);
							strmid(Cooking[giveplayerid][pCook5], gString, 0, strlen(gString), 255);
							Cooking[giveplayerid][pCWeight5] = Cooking[playerid][pCWeight3];
							Cooking[giveplayerid][pCookID5] = Cooking[playerid][pCookID3];
							format(gString, sizeof(gString), "* %s has given you %s weighting %d (use /cooked to see it).",PlayerInfo[playerid][pName],Cooking[giveplayerid][pCook5],Cooking[giveplayerid][pCWeight5]);
							SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
							format(gString, sizeof(gString), "* You gave %s weighting %d to %s.",Cooking[playerid][pCook3],Cooking[playerid][pCWeight3],PlayerInfo[giveplayerid][pName]);
							SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
						}
						else
						{
							SendClientMessage(playerid, COLOR_GREY, "   That player has no space left in his Cooking List !");
							return 1;
						}
					}
					case 4:
					{
						if(Cooking[giveplayerid][pCWeight1] < 1)
						{
							format(gString, sizeof(gString), "%s", Cooking[playerid][pCook4]);
							strmid(Cooking[giveplayerid][pCook1], gString, 0, strlen(gString), 255);
							Cooking[giveplayerid][pCWeight1] = Cooking[playerid][pCWeight4];
							Cooking[giveplayerid][pCookID1] = Cooking[playerid][pCookID4];
							format(gString, sizeof(gString), "* %s has given you %s weighting %d (use /cooked to see it).",PlayerInfo[playerid][pName],Cooking[giveplayerid][pCook1],Cooking[giveplayerid][pCWeight1]);
							SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
							format(gString, sizeof(gString), "* You gave %s weighting %d to %s.",Cooking[playerid][pCook4],Cooking[playerid][pCWeight4],PlayerInfo[giveplayerid][pName]);
							SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
						}
						else if(Cooking[giveplayerid][pCWeight2] < 1)
						{
							format(gString, sizeof(gString), "%s", Cooking[playerid][pCook4]);
							strmid(Cooking[giveplayerid][pCook2], gString, 0, strlen(gString), 255);
							Cooking[giveplayerid][pCWeight2] = Cooking[playerid][pCWeight4];
							Cooking[giveplayerid][pCookID2] = Cooking[playerid][pCookID4];
							format(gString, sizeof(gString), "* %s has given you %s weighting %d (use /cooked to see it).",PlayerInfo[playerid][pName],Cooking[giveplayerid][pCook2],Cooking[giveplayerid][pCWeight2]);
							SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
							format(gString, sizeof(gString), "* You gave %s weighting %d to %s.",Cooking[playerid][pCook4],Cooking[playerid][pCWeight4],PlayerInfo[giveplayerid][pName]);
							SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
						}
						else if(Cooking[giveplayerid][pCWeight3] < 1)
						{
							format(gString, sizeof(gString), "%s", Cooking[playerid][pCook4]);
							strmid(Cooking[giveplayerid][pCook3], gString, 0, strlen(gString), 255);
							Cooking[giveplayerid][pCWeight3] = Cooking[playerid][pCWeight4];
							Cooking[giveplayerid][pCookID3] = Cooking[playerid][pCookID4];
							format(gString, sizeof(gString), "* %s has given you %s weighting %d (use /cooked to see it).",PlayerInfo[playerid][pName],Cooking[giveplayerid][pCook3],Cooking[giveplayerid][pCWeight3]);
							SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
							format(gString, sizeof(gString), "* You gave %s weighting %d to %s.",Cooking[playerid][pCook4],Cooking[playerid][pCWeight4],PlayerInfo[giveplayerid][pName]);
							SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
						}
						else if(Cooking[giveplayerid][pCWeight4] < 1)
						{
							format(gString, sizeof(gString), "%s", Cooking[playerid][pCook4]);
							strmid(Cooking[giveplayerid][pCook4], gString, 0, strlen(gString), 255);
							Cooking[giveplayerid][pCWeight4] = Cooking[playerid][pCWeight4];
							Cooking[giveplayerid][pCookID4] = Cooking[playerid][pCookID4];
							format(gString, sizeof(gString), "* %s has given you %s weighting %d (use /cooked to see it).",PlayerInfo[playerid][pName],Cooking[giveplayerid][pCook4],Cooking[giveplayerid][pCWeight4]);
							SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
							format(gString, sizeof(gString), "* You gave %s weighting %d to %s.",Cooking[playerid][pCook4],Cooking[playerid][pCWeight4],PlayerInfo[giveplayerid][pName]);
							SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
						}
						else if(Cooking[giveplayerid][pCWeight5] < 1)
						{
							format(gString, sizeof(gString), "%s", Cooking[playerid][pCook4]);
							strmid(Cooking[giveplayerid][pCook5], gString, 0, strlen(gString), 255);
							Cooking[giveplayerid][pCWeight5] = Cooking[playerid][pCWeight4];
							Cooking[giveplayerid][pCookID5] = Cooking[playerid][pCookID4];
							format(gString, sizeof(gString), "* %s has given you %s weighting %d (use /cooked to see it).",PlayerInfo[playerid][pName],Cooking[giveplayerid][pCook5],Cooking[giveplayerid][pCWeight5]);
							SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
							format(gString, sizeof(gString), "* You gave %s weighting %d to %s.",Cooking[playerid][pCook4],Cooking[playerid][pCWeight4],PlayerInfo[giveplayerid][pName]);
							SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
						}
						else
						{
							SendClientMessage(playerid, COLOR_GREY, "   That player has no space left in his Cooking List !");
							return 1;
						}
					}
					case 5:
					{
						if(Cooking[giveplayerid][pCWeight1] < 1)
						{
							format(gString, sizeof(gString), "%s", Cooking[playerid][pCook5]);
							strmid(Cooking[giveplayerid][pCook1], gString, 0, strlen(gString), 255);
							Cooking[giveplayerid][pCWeight1] = Cooking[playerid][pCWeight5];
							Cooking[giveplayerid][pCookID1] = Cooking[playerid][pCookID5];
							format(gString, sizeof(gString), "* %s has given you %s weighting %d (use /cooked to see it).",PlayerInfo[playerid][pName],Cooking[giveplayerid][pCook1],Cooking[giveplayerid][pCWeight1]);
							SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
							format(gString, sizeof(gString), "* You gave %s weighting %d to %s.",Cooking[playerid][pCook5],Cooking[playerid][pCWeight5],PlayerInfo[giveplayerid][pName]);
							SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
						}
						else if(Cooking[giveplayerid][pCWeight2] < 1)
						{
							format(gString, sizeof(gString), "%s", Cooking[playerid][pCook5]);
							strmid(Cooking[giveplayerid][pCook2], gString, 0, strlen(gString), 255);
							Cooking[giveplayerid][pCWeight2] = Cooking[playerid][pCWeight5];
							Cooking[giveplayerid][pCookID2] = Cooking[playerid][pCookID5];
							format(gString, sizeof(gString), "* %s has given you %s weighting %d (use /cooked to see it).",PlayerInfo[playerid][pName],Cooking[giveplayerid][pCook2],Cooking[giveplayerid][pCWeight2]);
							SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
							format(gString, sizeof(gString), "* You gave %s weighting %d to %s.",Cooking[playerid][pCook5],Cooking[playerid][pCWeight5],PlayerInfo[giveplayerid][pName]);
							SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
						}
						else if(Cooking[giveplayerid][pCWeight3] < 1)
						{
							format(gString, sizeof(gString), "%s", Cooking[playerid][pCook5]);
							strmid(Cooking[giveplayerid][pCook3], gString, 0, strlen(gString), 255);
							Cooking[giveplayerid][pCWeight3] = Cooking[playerid][pCWeight5];
							Cooking[giveplayerid][pCookID3] = Cooking[playerid][pCookID5];
							format(gString, sizeof(gString), "* %s has given you %s weighting %d (use /cooked to see it).",PlayerInfo[playerid][pName],Cooking[giveplayerid][pCook3],Cooking[giveplayerid][pCWeight3]);
							SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
							format(gString, sizeof(gString), "* You gave %s weighting %d to %s.",Cooking[playerid][pCook5],Cooking[playerid][pCWeight5],PlayerInfo[giveplayerid][pName]);
							SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
						}
						else if(Cooking[giveplayerid][pCWeight4] < 1)
						{
							format(gString, sizeof(gString), "%s", Cooking[playerid][pCook5]);
							strmid(Cooking[giveplayerid][pCook4], gString, 0, strlen(gString), 255);
							Cooking[giveplayerid][pCWeight4] = Cooking[playerid][pCWeight5];
							Cooking[giveplayerid][pCookID4] = Cooking[playerid][pCookID5];
							format(gString, sizeof(gString), "* %s has given you %s weighting %d (use /cooked to see it).",PlayerInfo[playerid][pName],Cooking[giveplayerid][pCook4],Cooking[giveplayerid][pCWeight4]);
							SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
							format(gString, sizeof(gString), "* You gave %s weighting %d to %s.",Cooking[playerid][pCook5],Cooking[playerid][pCWeight5],PlayerInfo[giveplayerid][pName]);
							SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
						}
						else if(Cooking[giveplayerid][pCWeight5] < 1)
						{
							format(gString, sizeof(gString), "%s", Cooking[playerid][pCook5]);
							strmid(Cooking[giveplayerid][pCook5], gString, 0, strlen(gString), 255);
							Cooking[giveplayerid][pCWeight5] = Cooking[playerid][pCWeight5];
							Cooking[giveplayerid][pCookID5] = Cooking[playerid][pCookID5];
							format(gString, sizeof(gString), "* %s has given you %s weighting %d (use /cooked to see it).",PlayerInfo[playerid][pName],Cooking[giveplayerid][pCook5],Cooking[giveplayerid][pCWeight5]);
							SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
							format(gString, sizeof(gString), "* You gave %s weighting %d to %s.",Cooking[playerid][pCook5],Cooking[playerid][pCWeight5],PlayerInfo[giveplayerid][pName]);
							SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
						}
						else
						{
							SendClientMessage(playerid, COLOR_GREY, "   That player has no space left in his Cooking List !");
							return 1;
						}
					}
				}//switch
				ClearCookingID(playerid, cookid);
			}//invalid giveplayerid
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   That player is Offline !");
			return 1;
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   Unknown Selling Name !");
		return 1;
	}
	return 1;
}

CMD:fare(playerid, params[]) {
	if(PlayerInfo[playerid][pMember] == 10||PlayerInfo[playerid][pLeader] == 10|| PlayerInfo[playerid][pJob] == 14)
	{
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
			format(gString, sizeof(gString), "* You are now Off Duty and earned $%d.", TransportMoney[playerid]);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
			GivePlayerMoney(playerid, TransportMoney[playerid]);
			ConsumingMoney[playerid] = 1; TransportValue[playerid] = 0; TransportMoney[playerid] = 0;
			return 1;
		}
		new Veh = GetPlayerVehicleID(playerid);
		if(Veh == 82 || Veh == 84 || Veh == 85 || Veh == 94)
		{
			if(GetPlayerState(playerid) == 2)
			{
				//if(!strlen(tmp))
				{
					SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /fare [price]");
					return 1;
				}
				new moneys;
				if(moneys < 1 || moneys > 999) { SendClientMessage(playerid, COLOR_GREY, "   Fare price must be between $1 and $999 !"); return 1; }
				TaxiDrivers += 1; TransportDuty[playerid] = 1; TransportValue[playerid] = moneys;
				GetPlayerName(playerid,PlayerInfo[playerid][pName],sizeof(PlayerInfo[playerid][pName]));
				format(gString, sizeof(gString), "Taxi Driver %s is On Duty, fare: $%d.", PlayerInfo[playerid][pName], TransportValue[playerid]);
				OOCNews(TEAM_GROVE_COLOR,gString);
			}
			else
			{
				SendClientMessage(playerid, COLOR_GREY, "   You are not the Driver !");
				return 1;
			}
		}
		else if(Veh == 64 || Veh == 65)
		{
			if(GetPlayerState(playerid) == 2)
			{
				//if(!strlen(tmp))
				{
					SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /fare [price]");
					return 1;
				}
				new moneys;
				if(moneys < 1 || moneys > 99999) { SendClientMessage(playerid, COLOR_GREY, "   Fare price must be between $1 and $99999 !"); return 1; }
				BusDrivers += 1; TransportDuty[playerid] = 2; TransportValue[playerid]= moneys;
				GetPlayerName(playerid,PlayerInfo[playerid][pName],sizeof(PlayerInfo[playerid][pName]));
				format(gString, sizeof(gString), "Bus Driver %s is On Duty, fare: $%d.", PlayerInfo[playerid][pName], TransportValue[playerid]);
				OOCNews(TEAM_GROVE_COLOR,gString);
			}
			else
			{
				SendClientMessage(playerid, COLOR_GREY, "   You are not the Driver !");
				return 1;
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   You are not in a Taxi / Bus !");
		}
	}
	else
	{
		SendClientMessage(playerid,COLOR_GREY,"   You are not a Taxi / Bus Driver !");
		return 1;
	}
	return 1;
}

CMD:eat(playerid, params[]) {
	if(PlayerBoxing[playerid] > 0)
	{
		SendClientMessage(playerid, COLOR_GREY, "   Cant eat a Fish while you are fighting !");
		return 1;
	}
	//if(!strlen(tmp))
	{
		SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /eat [cook number]");
		return 1;
	}
	new cookid;
	if(cookid < 1 || cookid > 5) { SendClientMessage(playerid, COLOR_GREY, "   Cook number cant be below 1 or above 5 !"); return 1; }
	else if(cookid == 1 && Cooking[playerid][pCWeight1] < 1) { SendClientMessage(playerid, COLOR_GREY, "   You didnt even Cook something at that number(1) !"); return 1; }
	else if(cookid == 2 && Cooking[playerid][pCWeight2] < 1) { SendClientMessage(playerid, COLOR_GREY, "   You didnt even Cook something at that number(2) !"); return 1; }
	else if(cookid == 3 && Cooking[playerid][pCWeight3] < 1) { SendClientMessage(playerid, COLOR_GREY, "   You didnt even Cook something at that number(3) !"); return 1; }
	else if(cookid == 4 && Cooking[playerid][pCWeight4] < 1) { SendClientMessage(playerid, COLOR_GREY, "   You didnt even Cook something at that number(4) !"); return 1; }
	else if(cookid == 5 && Cooking[playerid][pCWeight5] < 1) { SendClientMessage(playerid, COLOR_GREY, "   You didnt even Cook something at that number(5) !"); return 1; }
	GetPlayerName(playerid, PlayerInfo[playerid][pName], sizeof(PlayerInfo[playerid][pName]));
	new Float:health;
	if(GetPlayerHealth(playerid, health) < 40)
	{
		new hp = 0;
		switch (cookid)
		{
			case 1:
			{
				if(Cooking[playerid][pCookID1] == 16 || Cooking[playerid][pCookID1] == 18)
				{//Dolphin or Turtle
					WantedPoints[playerid] += 2;
					SetPlayerCriminal(playerid,255, "Consuming endangered Species");
				}
				SetPlayerHealth(playerid, health + (Cooking[playerid][pCWeight1] / 3));
				hp = Cooking[playerid][pCWeight1];
				format(gString, sizeof(gString), "* %s eats %s.", PlayerInfo[playerid][pName], Cooking[playerid][pCook1]);
				ProxDetector(30.0, playerid, gString, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
				format(gString, sizeof(gString), "* You ate %s weighting %d, and it was added to your Health.",Cooking[playerid][pCook1], hp);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
			}
			case 2:
			{
				if(Cooking[playerid][pCookID2] == 16 || Cooking[playerid][pCookID2] == 18)
				{//Dolphin or Turtle
					WantedPoints[playerid] += 2;
					SetPlayerCriminal(playerid,255, "Consuming endangered Species");
				}
				SetPlayerHealth(playerid, health + (Cooking[playerid][pCWeight2] / 3));
				hp = Cooking[playerid][pCWeight2];
				format(gString, sizeof(gString), "* %s eats %s.", PlayerInfo[playerid][pName], Cooking[playerid][pCook2]);
				ProxDetector(30.0, playerid, gString, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
				format(gString, sizeof(gString), "* You ate %s weighting %d, and it was added to your Health.",Cooking[playerid][pCook2], hp);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
			}
			case 3:
			{
				if(Cooking[playerid][pCookID3] == 16 || Cooking[playerid][pCookID3] == 18)
				{//Dolphin or Turtle
					WantedPoints[playerid] += 2;
					SetPlayerCriminal(playerid,255, "Consuming endangered Species");
				}
				SetPlayerHealth(playerid, health + (Cooking[playerid][pCWeight3] / 3));
				hp = Cooking[playerid][pCWeight3];
				format(gString, sizeof(gString), "* %s eats %s.", PlayerInfo[playerid][pName], Cooking[playerid][pCook3]);
				ProxDetector(30.0, playerid, gString, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
				format(gString, sizeof(gString), "* You ate %s weighting %d, and it was added to your Health.",Cooking[playerid][pCook3], hp);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
			}
			case 4:
			{
				if(Cooking[playerid][pCookID4] == 16 || Cooking[playerid][pCookID4] == 18)
				{//Dolphin or Turtle
					WantedPoints[playerid] += 2;
					SetPlayerCriminal(playerid,255, "Consuming endangered Species");
				}
				SetPlayerHealth(playerid, health + (Cooking[playerid][pCWeight4] / 3));
				hp = Cooking[playerid][pCWeight4];
				format(gString, sizeof(gString), "* %s eats %s.", PlayerInfo[playerid][pName], Cooking[playerid][pCook4]);
				ProxDetector(30.0, playerid, gString, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
				format(gString, sizeof(gString), "* You ate %s weighting %d, and it was added to your Health.",Cooking[playerid][pCook4], hp);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
			}
			case 5:
			{
				if(Cooking[playerid][pCookID5] == 16 || Cooking[playerid][pCookID5] == 18)
				{//Dolphin or Turtle
					WantedPoints[playerid] += 2;
					SetPlayerCriminal(playerid,255, "Consuming endangered Species");
				}
				SetPlayerHealth(playerid, health + (Cooking[playerid][pCWeight5] / 3));
				hp = Cooking[playerid][pCWeight5];
				format(gString, sizeof(gString), "* %s eats %s.", PlayerInfo[playerid][pName], Cooking[playerid][pCook5]);
				ProxDetector(30.0, playerid, gString, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
				format(gString, sizeof(gString), "* You ate %s weighting %d, and it was added to your Health.",Cooking[playerid][pCook5], hp);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
			}
		}
		ClearCookingID(playerid, cookid);
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   Your health is high enough, can only eat at 40 Health !");
		return 1;
	}
	return 1;
}

CMD:cook(playerid, params[]) {
	if(IsAtCookPlace(playerid))
	{
		new x_nr[256];
		if(!strlen(x_nr)) {
			SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /cook [name]");
			SendClientMessage(playerid, COLOR_WHITE, "Available names: Lastfish, Fish, Chicken, Hamburger, Pizza.");
			return 1;
		}
		if(strcmp(x_nr,"lastfish",true) == 0)
		{
			if(Fishes[playerid][pLastFish] > 0)
			{
				new found = 0;
				if(Cooking[playerid][pCWeight1] == 0)
				{
					format(gString, sizeof(gString), "A Cooked %s", FishNames[Fishes[playerid][pFishID]]);
					strmid(Cooking[playerid][pCook1], gString, 0, strlen(gString), 255);
					Cooking[playerid][pCWeight1] = Fishes[playerid][pLastWeight];
					Cooking[playerid][pCookID1] = Fishes[playerid][pFishID];
					format(gString, sizeof(gString), "* You've made %s, weighting %d LBS.",Cooking[playerid][pCook1],Cooking[playerid][pCWeight1]);
					SendClientMessage(playerid,COLOR_LIGHTBLUE, gString);
					found = 1;
				}
				else if(Cooking[playerid][pCWeight2] == 0)
				{
					format(gString, sizeof(gString), "A Cooked %s", FishNames[Fishes[playerid][pFishID]]);
					strmid(Cooking[playerid][pCook2], gString, 0, strlen(gString), 255);
					Cooking[playerid][pCWeight2] = Fishes[playerid][pLastWeight];
					Cooking[playerid][pCookID2] = Fishes[playerid][pFishID];
					format(gString, sizeof(gString), "* You've made %s, weighting %d LBS.",Cooking[playerid][pCook2],Cooking[playerid][pCWeight2]);
					SendClientMessage(playerid,COLOR_LIGHTBLUE, gString);
					found = 1;
				}
				else if(Cooking[playerid][pCWeight3] == 0)
				{
					format(gString, sizeof(gString), "A Cooked %s", FishNames[Fishes[playerid][pFishID]]);
					strmid(Cooking[playerid][pCook3], gString, 0, strlen(gString), 255);
					Cooking[playerid][pCWeight3] = Fishes[playerid][pLastWeight];
					Cooking[playerid][pCookID3] = Fishes[playerid][pFishID];
					format(gString, sizeof(gString), "* You've made %s, weighting %d LBS.",Cooking[playerid][pCook3],Cooking[playerid][pCWeight3]);
					SendClientMessage(playerid,COLOR_LIGHTBLUE, gString);
					found = 1;
				}
				else if(Cooking[playerid][pCWeight4] == 0)
				{
					format(gString, sizeof(gString), "A Cooked %s", FishNames[Fishes[playerid][pFishID]]);
					strmid(Cooking[playerid][pCook4], gString, 0, strlen(gString), 255);
					Cooking[playerid][pCWeight4] = Fishes[playerid][pLastWeight];
					Cooking[playerid][pCookID4] = Fishes[playerid][pFishID];
					format(gString, sizeof(gString), "* You've made %s, weighting %d LBS.",Cooking[playerid][pCook4],Cooking[playerid][pCWeight4]);
					SendClientMessage(playerid,COLOR_LIGHTBLUE, gString);
					found = 1;
				}
				else if(Cooking[playerid][pCWeight5] == 0)
				{
					format(gString, sizeof(gString), "A Cooked %s", FishNames[Fishes[playerid][pFishID]]);
					strmid(Cooking[playerid][pCook5], gString, 0, strlen(gString), 255);
					Cooking[playerid][pCWeight5] = Fishes[playerid][pLastWeight];
					Cooking[playerid][pCookID5] = Fishes[playerid][pFishID];
					format(gString, sizeof(gString), "* You've made %s, weighting %d LBS.",Cooking[playerid][pCook5],Cooking[playerid][pCWeight5]);
					SendClientMessage(playerid,COLOR_LIGHTBLUE, gString);
					found = 1;
				}
				else
				{
					SendClientMessage(playerid, COLOR_GREY, "   You don't have any space in your Cooking List !");
					return 1;
				}
				if(found)
				{
					ClearFishID(playerid, Fishes[playerid][pLastFish]);
					Fishes[playerid][pLastFish] = 0;
					Fishes[playerid][pFishID] = 0;
				}
			}
			else
			{
				SendClientMessage(playerid, COLOR_GREY, "   You haven't even catched a Fish yet !");
				return 1;
			}
		}
		else if(strcmp(x_nr,"fish",true) == 0)
		{
			new found = 0;
			//if(!strlen(tmp))
			{
				SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /cook fish [fishnumber]");
				return 1;
			}
			new fishid;
			if(fishid < 1 || fishid > 5) { SendClientMessage(playerid, COLOR_GREY, "   Fish number cant be below 1 or above 5 !"); return 1; }
			else if(fishid == 1 && Fishes[playerid][pWeight1] < 1) { SendClientMessage(playerid, COLOR_GREY, "   You didnt even catch a Fish at that number(1) !"); return 1; }
			else if(fishid == 2 && Fishes[playerid][pWeight2] < 1) { SendClientMessage(playerid, COLOR_GREY, "   You didnt even catch a Fish at that number(2) !"); return 1; }
			else if(fishid == 3 && Fishes[playerid][pWeight3] < 1) { SendClientMessage(playerid, COLOR_GREY, "   You didnt even catch a Fish at that number(3) !"); return 1; }
			else if(fishid == 4 && Fishes[playerid][pWeight4] < 1) { SendClientMessage(playerid, COLOR_GREY, "   You didnt even catch a Fish at that number(4) !"); return 1; }
			else if(fishid == 5 && Fishes[playerid][pWeight5] < 1) { SendClientMessage(playerid, COLOR_GREY, "   You didnt even catch a Fish at that number(5) !"); return 1; }
			if(Cooking[playerid][pCWeight1] == 0)
			{
				if(fishid == 1)
				{
					format(gString, sizeof(gString), "A Cooked %s", Fishes[playerid][pFish1]);
					strmid(Cooking[playerid][pCook1], gString, 0, strlen(gString), 255);
					Cooking[playerid][pCWeight1] = Fishes[playerid][pWeight1];
					Cooking[playerid][pCookID1] = Fishes[playerid][pFid1];
					format(gString, sizeof(gString), "* You've made %s, weighting %d LBS.",Cooking[playerid][pCook1],Cooking[playerid][pCWeight1]);
					SendClientMessage(playerid,COLOR_LIGHTBLUE, gString);
				}
				else if(fishid == 2)
				{
					format(gString, sizeof(gString), "A Cooked %s", Fishes[playerid][pFish2]);
					strmid(Cooking[playerid][pCook1], gString, 0, strlen(gString), 255);
					Cooking[playerid][pCWeight1] = Fishes[playerid][pWeight2];
					Cooking[playerid][pCookID1] = Fishes[playerid][pFid2];
					format(gString, sizeof(gString), "* You've made %s, weighting %d LBS.",Cooking[playerid][pCook1],Cooking[playerid][pCWeight1]);
					SendClientMessage(playerid,COLOR_LIGHTBLUE, gString);
				}
				else if(fishid == 3)
				{
					format(gString, sizeof(gString), "A Cooked %s", Fishes[playerid][pFish3]);
					strmid(Cooking[playerid][pCook1], gString, 0, strlen(gString), 255);
					Cooking[playerid][pCWeight1] = Fishes[playerid][pWeight3];
					Cooking[playerid][pCookID1] = Fishes[playerid][pFid3];
					format(gString, sizeof(gString), "* You've made %s, weighting %d LBS.",Cooking[playerid][pCook1],Cooking[playerid][pCWeight1]);
					SendClientMessage(playerid,COLOR_LIGHTBLUE, gString);
				}
				else if(fishid == 4)
				{
					format(gString, sizeof(gString), "A Cooked %s", Fishes[playerid][pFish4]);
					strmid(Cooking[playerid][pCook1], gString, 0, strlen(gString), 255);
					Cooking[playerid][pCWeight1] = Fishes[playerid][pWeight4];
					Cooking[playerid][pCookID1] = Fishes[playerid][pFid4];
					format(gString, sizeof(gString), "* You've made %s, weighting %d LBS.",Cooking[playerid][pCook1],Cooking[playerid][pCWeight1]);
					SendClientMessage(playerid,COLOR_LIGHTBLUE, gString);
				}
				else if(fishid == 5)
				{
					format(gString, sizeof(gString), "A Cooked %s", Fishes[playerid][pFish5]);
					strmid(Cooking[playerid][pCook1], gString, 0, strlen(gString), 255);
					Cooking[playerid][pCWeight1] = Fishes[playerid][pWeight5];
					Cooking[playerid][pCookID1] = Fishes[playerid][pFid5];
					format(gString, sizeof(gString), "* You've made %s, weighting %d LBS.",Cooking[playerid][pCook1],Cooking[playerid][pCWeight1]);
					SendClientMessage(playerid,COLOR_LIGHTBLUE, gString);
				}
				found = 1;
			}
			else if(Cooking[playerid][pCWeight2] == 0)
			{
				if(fishid == 1)
				{
					format(gString, sizeof(gString), "A Cooked %s", Fishes[playerid][pFish1]);
					strmid(Cooking[playerid][pCook2], gString, 0, strlen(gString), 255);
					Cooking[playerid][pCWeight2] = Fishes[playerid][pWeight1];
					Cooking[playerid][pCookID2] = Fishes[playerid][pFid1];
					format(gString, sizeof(gString), "* You've made %s, weighting %d LBS.",Cooking[playerid][pCook2],Cooking[playerid][pCWeight2]);
					SendClientMessage(playerid,COLOR_LIGHTBLUE, gString);
				}
				else if(fishid == 2)
				{
					format(gString, sizeof(gString), "A Cooked %s", Fishes[playerid][pFish2]);
					strmid(Cooking[playerid][pCook2], gString, 0, strlen(gString), 255);
					Cooking[playerid][pCWeight2] = Fishes[playerid][pWeight2];
					Cooking[playerid][pCookID2] = Fishes[playerid][pFid2];
					format(gString, sizeof(gString), "* You've made %s, weighting %d LBS.",Cooking[playerid][pCook2],Cooking[playerid][pCWeight2]);
					SendClientMessage(playerid,COLOR_LIGHTBLUE, gString);
				}
				else if(fishid == 3)
				{
					format(gString, sizeof(gString), "A Cooked %s", Fishes[playerid][pFish3]);
					strmid(Cooking[playerid][pCook2], gString, 0, strlen(gString), 255);
					Cooking[playerid][pCWeight2] = Fishes[playerid][pWeight3];
					Cooking[playerid][pCookID2] = Fishes[playerid][pFid3];
					format(gString, sizeof(gString), "* You've made %s, weighting %d LBS.",Cooking[playerid][pCook2],Cooking[playerid][pCWeight2]);
					SendClientMessage(playerid,COLOR_LIGHTBLUE, gString);
				}
				else if(fishid == 4)
				{
					format(gString, sizeof(gString), "A Cooked %s", Fishes[playerid][pFish4]);
					strmid(Cooking[playerid][pCook2], gString, 0, strlen(gString), 255);
					Cooking[playerid][pCWeight2] = Fishes[playerid][pWeight4];
					Cooking[playerid][pCookID2] = Fishes[playerid][pFid4];
					format(gString, sizeof(gString), "* You've made %s, weighting %d LBS.",Cooking[playerid][pCook2],Cooking[playerid][pCWeight2]);
					SendClientMessage(playerid,COLOR_LIGHTBLUE, gString);
				}
				else if(fishid == 5)
				{
					format(gString, sizeof(gString), "A Cooked %s", Fishes[playerid][pFish5]);
					strmid(Cooking[playerid][pCook2], gString, 0, strlen(gString), 255);
					Cooking[playerid][pCWeight2] = Fishes[playerid][pWeight5];
					Cooking[playerid][pCookID2] = Fishes[playerid][pFid5];
					format(gString, sizeof(gString), "* You've made %s, weighting %d LBS.",Cooking[playerid][pCook2],Cooking[playerid][pCWeight2]);
					SendClientMessage(playerid,COLOR_LIGHTBLUE, gString);
				}
				found = 1;
			}
			else if(Cooking[playerid][pCWeight3] == 0)
			{
				if(fishid == 1)
				{
					format(gString, sizeof(gString), "A Cooked %s", Fishes[playerid][pFish1]);
					strmid(Cooking[playerid][pCook3], gString, 0, strlen(gString), 255);
					Cooking[playerid][pCWeight3] = Fishes[playerid][pWeight1];
					Cooking[playerid][pCookID3] = Fishes[playerid][pFid1];
					format(gString, sizeof(gString), "* You've made %s, weighting %d LBS.",Cooking[playerid][pCook3],Cooking[playerid][pCWeight3]);
					SendClientMessage(playerid,COLOR_LIGHTBLUE, gString);
				}
				else if(fishid == 2)
				{
					format(gString, sizeof(gString), "A Cooked %s", Fishes[playerid][pFish2]);
					strmid(Cooking[playerid][pCook3], gString, 0, strlen(gString), 255);
					Cooking[playerid][pCWeight3] = Fishes[playerid][pWeight2];
					Cooking[playerid][pCookID3] = Fishes[playerid][pFid2];
					format(gString, sizeof(gString), "* You've made %s, weighting %d LBS.",Cooking[playerid][pCook3],Cooking[playerid][pCWeight3]);
					SendClientMessage(playerid,COLOR_LIGHTBLUE, gString);
				}
				else if(fishid == 3)
				{
					format(gString, sizeof(gString), "A Cooked %s", Fishes[playerid][pFish3]);
					strmid(Cooking[playerid][pCook3], gString, 0, strlen(gString), 255);
					Cooking[playerid][pCWeight3] = Fishes[playerid][pWeight3];
					Cooking[playerid][pCookID3] = Fishes[playerid][pFid3];
					format(gString, sizeof(gString), "* You've made %s, weighting %d LBS.",Cooking[playerid][pCook3],Cooking[playerid][pCWeight3]);
					SendClientMessage(playerid,COLOR_LIGHTBLUE, gString);
				}
				else if(fishid == 4)
				{
					format(gString, sizeof(gString), "A Cooked %s", Fishes[playerid][pFish4]);
					strmid(Cooking[playerid][pCook3], gString, 0, strlen(gString), 255);
					Cooking[playerid][pCWeight3] = Fishes[playerid][pWeight4];
					Cooking[playerid][pCookID3] = Fishes[playerid][pFid4];
					format(gString, sizeof(gString), "* You've made %s, weighting %d LBS.",Cooking[playerid][pCook3],Cooking[playerid][pCWeight3]);
					SendClientMessage(playerid,COLOR_LIGHTBLUE, gString);
				}
				else if(fishid == 5)
				{
					format(gString, sizeof(gString), "A Cooked %s", Fishes[playerid][pFish5]);
					strmid(Cooking[playerid][pCook3], gString, 0, strlen(gString), 255);
					Cooking[playerid][pCWeight3] = Fishes[playerid][pWeight5];
					Cooking[playerid][pCookID3] = Fishes[playerid][pFid5];
					format(gString, sizeof(gString), "* You've made %s, weighting %d LBS.",Cooking[playerid][pCook3],Cooking[playerid][pCWeight3]);
					SendClientMessage(playerid,COLOR_LIGHTBLUE, gString);
				}
				found = 1;
			}
			else if(Cooking[playerid][pCWeight4] == 0)
			{
				if(fishid == 1)
				{
					format(gString, sizeof(gString), "A Cooked %s", Fishes[playerid][pFish1]);
					strmid(Cooking[playerid][pCook4], gString, 0, strlen(gString), 255);
					Cooking[playerid][pCWeight4] = Fishes[playerid][pWeight1];
					Cooking[playerid][pCookID4] = Fishes[playerid][pFid1];
					format(gString, sizeof(gString), "* You've made %s, weighting %d LBS.",Cooking[playerid][pCook4],Cooking[playerid][pCWeight4]);
					SendClientMessage(playerid,COLOR_LIGHTBLUE, gString);
				}
				else if(fishid == 2)
				{
					format(gString, sizeof(gString), "A Cooked %s", Fishes[playerid][pFish2]);
					strmid(Cooking[playerid][pCook4], gString, 0, strlen(gString), 255);
					Cooking[playerid][pCWeight4] = Fishes[playerid][pWeight2];
					Cooking[playerid][pCookID4] = Fishes[playerid][pFid2];
					format(gString, sizeof(gString), "* You've made %s, weighting %d LBS.",Cooking[playerid][pCook4],Cooking[playerid][pCWeight4]);
					SendClientMessage(playerid,COLOR_LIGHTBLUE, gString);
				}
				else if(fishid == 3)
				{
					format(gString, sizeof(gString), "A Cooked %s", Fishes[playerid][pFish3]);
					strmid(Cooking[playerid][pCook4], gString, 0, strlen(gString), 255);
					Cooking[playerid][pCWeight4] = Fishes[playerid][pWeight3];
					Cooking[playerid][pCookID4] = Fishes[playerid][pFid3];
					format(gString, sizeof(gString), "* You've made %s, weighting %d LBS.",Cooking[playerid][pCook4],Cooking[playerid][pCWeight4]);
					SendClientMessage(playerid,COLOR_LIGHTBLUE, gString);
				}
				else if(fishid == 4)
				{
					format(gString, sizeof(gString), "A Cooked %s", Fishes[playerid][pFish4]);
					strmid(Cooking[playerid][pCook4], gString, 0, strlen(gString), 255);
					Cooking[playerid][pCWeight4] = Fishes[playerid][pWeight4];
					Cooking[playerid][pCookID4] = Fishes[playerid][pFid4];
					format(gString, sizeof(gString), "* You've made %s, weighting %d LBS.",Cooking[playerid][pCook4],Cooking[playerid][pCWeight4]);
					SendClientMessage(playerid,COLOR_LIGHTBLUE, gString);
				}
				else if(fishid == 5)
				{
					format(gString, sizeof(gString), "A Cooked %s", Fishes[playerid][pFish5]);
					strmid(Cooking[playerid][pCook4], gString, 0, strlen(gString), 255);
					Cooking[playerid][pCWeight4] = Fishes[playerid][pWeight5];
					Cooking[playerid][pCookID4] = Fishes[playerid][pFid5];
					format(gString, sizeof(gString), "* You've made %s, weighting %d LBS.",Cooking[playerid][pCook4],Cooking[playerid][pCWeight4]);
					SendClientMessage(playerid,COLOR_LIGHTBLUE, gString);
				}
				found = 1;
			}
			else if(Cooking[playerid][pCWeight5] == 0)
			{
				if(fishid == 1)
				{
					format(gString, sizeof(gString), "A Cooked %s", Fishes[playerid][pFish1]);
					strmid(Cooking[playerid][pCook5], gString, 0, strlen(gString), 255);
					Cooking[playerid][pCWeight5] = Fishes[playerid][pWeight1];
					Cooking[playerid][pCookID5] = Fishes[playerid][pFid1];
					format(gString, sizeof(gString), "* You've made %s, weighting %d LBS.",Cooking[playerid][pCook5],Cooking[playerid][pCWeight5]);
					SendClientMessage(playerid,COLOR_LIGHTBLUE, gString);
				}
				else if(fishid == 2)
				{
					format(gString, sizeof(gString), "A Cooked %s", Fishes[playerid][pFish2]);
					strmid(Cooking[playerid][pCook5], gString, 0, strlen(gString), 255);
					Cooking[playerid][pCWeight5] = Fishes[playerid][pWeight2];
					Cooking[playerid][pCookID5] = Fishes[playerid][pFid2];
					format(gString, sizeof(gString), "* You've made %s, weighting %d LBS.",Cooking[playerid][pCook5],Cooking[playerid][pCWeight5]);
					SendClientMessage(playerid,COLOR_LIGHTBLUE, gString);
				}
				else if(fishid == 3)
				{
					format(gString, sizeof(gString), "A Cooked %s", Fishes[playerid][pFish3]);
					strmid(Cooking[playerid][pCook5], gString, 0, strlen(gString), 255);
					Cooking[playerid][pCWeight5] = Fishes[playerid][pWeight3];
					Cooking[playerid][pCookID5] = Fishes[playerid][pFid3];
					format(gString, sizeof(gString), "* You've made %s, weighting %d LBS.",Cooking[playerid][pCook5],Cooking[playerid][pCWeight5]);
					SendClientMessage(playerid,COLOR_LIGHTBLUE, gString);
				}
				else if(fishid == 4)
				{
					format(gString, sizeof(gString), "A Cooked %s", Fishes[playerid][pFish4]);
					strmid(Cooking[playerid][pCook5], gString, 0, strlen(gString), 255);
					Cooking[playerid][pCWeight5] = Fishes[playerid][pWeight4];
					Cooking[playerid][pCookID5] = Fishes[playerid][pFid4];
					format(gString, sizeof(gString), "* You've made %s, weighting %d LBS.",Cooking[playerid][pCook5],Cooking[playerid][pCWeight5]);
					SendClientMessage(playerid,COLOR_LIGHTBLUE, gString);
				}
				else if(fishid == 5)
				{
					format(gString, sizeof(gString), "A Cooked %s", Fishes[playerid][pFish5]);
					strmid(Cooking[playerid][pCook5], gString, 0, strlen(gString), 255);
					Cooking[playerid][pCWeight5] = Fishes[playerid][pWeight5];
					Cooking[playerid][pCookID5] = Fishes[playerid][pFid5];
					format(gString, sizeof(gString), "* You've made %s, weighting %d LBS.",Cooking[playerid][pCook5],Cooking[playerid][pCWeight5]);
					SendClientMessage(playerid,COLOR_LIGHTBLUE, gString);
				}
				found = 1;
			}
			else
			{
				SendClientMessage(playerid, COLOR_GREY, "   You don't have any space in your Cooking List !");
				return 1;
			}
			if(found)
			{
				ClearFishID(playerid, fishid);
				Fishes[playerid][pLastFish] = 0;
				Fishes[playerid][pFishID] = 0;
			}
		}
		else if(strcmp(x_nr,"chicken",true) == 0)
		{
			if(PlayerToPoint(3.0,playerid,369.9786,-4.0798,1001.8589))
			{//Cluckin Bell
				if(Groceries[playerid][pChicken] != 0)
				{
					if(Cooking[playerid][pCWeight1] == 0)
					{
						format(gString, sizeof(gString), "A Cooked Chicken");
						strmid(Cooking[playerid][pCook1], gString, 0, strlen(gString), 255);
						Cooking[playerid][pCWeight1] = Groceries[playerid][pChicken];
						Cooking[playerid][pCookID1] = 30;
						Groceries[playerid][pChickens] = 0; Groceries[playerid][pChicken] = 0;
						format(gString, sizeof(gString), "* You've made %s, weighting %d LBS.",Cooking[playerid][pCook1],Cooking[playerid][pCWeight1]);
						SendClientMessage(playerid,COLOR_LIGHTBLUE, gString);
					}
					else if(Cooking[playerid][pCWeight2] == 0)
					{
						format(gString, sizeof(gString), "A Cooked Chicken");
						strmid(Cooking[playerid][pCook2], gString, 0, strlen(gString), 255);
						Cooking[playerid][pCWeight2] = Groceries[playerid][pChicken];
						Cooking[playerid][pCookID2] = 30;
						Groceries[playerid][pChickens] = 0; Groceries[playerid][pChicken] = 0;
						format(gString, sizeof(gString), "* You've made %s, weighting %d LBS.",Cooking[playerid][pCook2],Cooking[playerid][pCWeight2]);
						SendClientMessage(playerid,COLOR_LIGHTBLUE, gString);
					}
					else if(Cooking[playerid][pCWeight3] == 0)
					{
						format(gString, sizeof(gString), "A Cooked Chicken");
						strmid(Cooking[playerid][pCook3], gString, 0, strlen(gString), 255);
						Cooking[playerid][pCWeight3] = Groceries[playerid][pChicken];
						Cooking[playerid][pCookID3] = 30;
						Groceries[playerid][pChickens] = 0; Groceries[playerid][pChicken] = 0;
						format(gString, sizeof(gString), "* You've made %s, weighting %d LBS.",Cooking[playerid][pCook3],Cooking[playerid][pCWeight3]);
						SendClientMessage(playerid,COLOR_LIGHTBLUE, gString);
					}
					else if(Cooking[playerid][pCWeight4] == 0)
					{
						format(gString, sizeof(gString), "A Cooked Chicken");
						strmid(Cooking[playerid][pCook4], gString, 0, strlen(gString), 255);
						Cooking[playerid][pCWeight4] = Groceries[playerid][pChicken];
						Cooking[playerid][pCookID4] = 30;
						Groceries[playerid][pChickens] = 0; Groceries[playerid][pChicken] = 0;
						format(gString, sizeof(gString), "* You've made %s, weighting %d LBS.",Cooking[playerid][pCook4],Cooking[playerid][pCWeight4]);
						SendClientMessage(playerid,COLOR_LIGHTBLUE, gString);
					}
					else if(Cooking[playerid][pCWeight5] == 0)
					{
						format(gString, sizeof(gString), "A Cooked Chicken");
						strmid(Cooking[playerid][pCook5], gString, 0, strlen(gString), 255);
						Cooking[playerid][pCWeight5] = Groceries[playerid][pChicken];
						Cooking[playerid][pCookID5] = 30;
						Groceries[playerid][pChickens] = 0; Groceries[playerid][pChicken] = 0;
						format(gString, sizeof(gString), "* You've made %s, weighting %d LBS.",Cooking[playerid][pCook5],Cooking[playerid][pCWeight5]);
						SendClientMessage(playerid,COLOR_LIGHTBLUE, gString);
					}
					else
					{
						SendClientMessage(playerid, COLOR_GREY, "   You don't have any space in your Cooking List !");
						return 1;
					}
				}
				else
				{
					SendClientMessage(playerid, COLOR_GREY, "   You don't have any Chickens with you !");
					return 1;
				}
			}
			else
			{
				SendClientMessage(playerid, COLOR_GREY, "   You need to be at Cluckin Bell to Cook this !");
				return 1;
			}
		}
		else if(strcmp(x_nr,"hamburger",true) == 0)
		{
			if(PlayerToPoint(3.0,playerid,376.4466,-60.9574,1001.5078) || PlayerToPoint(3.0,playerid,378.1215,-57.4928,1001.5078))
			{//Burgershot
				if(Groceries[playerid][pHamburger] != 0)
				{
					if(Cooking[playerid][pCWeight1] == 0)
					{
						format(gString, sizeof(gString), "A Baken Hamburger");
						strmid(Cooking[playerid][pCook1], gString, 0, strlen(gString), 255);
						Cooking[playerid][pCWeight1] = Groceries[playerid][pHamburger];
						Cooking[playerid][pCookID1] = 30;
						Groceries[playerid][pHamburgers] = 0; Groceries[playerid][pHamburger] = 0;
						format(gString, sizeof(gString), "* You've made %s, weighting %d LBS.",Cooking[playerid][pCook1],Cooking[playerid][pCWeight1]);
						SendClientMessage(playerid,COLOR_LIGHTBLUE, gString);
					}
					else if(Cooking[playerid][pCWeight2] == 0)
					{
						format(gString, sizeof(gString), "A Baken Hamburger");
						strmid(Cooking[playerid][pCook2], gString, 0, strlen(gString), 255);
						Cooking[playerid][pCWeight2] = Groceries[playerid][pHamburger];
						Cooking[playerid][pCookID2] = 30;
						Groceries[playerid][pHamburgers] = 0; Groceries[playerid][pHamburger] = 0;
						format(gString, sizeof(gString), "* You've made %s, weighting %d LBS.",Cooking[playerid][pCook2],Cooking[playerid][pCWeight2]);
						SendClientMessage(playerid,COLOR_LIGHTBLUE, gString);
					}
					else if(Cooking[playerid][pCWeight3] == 0)
					{
						format(gString, sizeof(gString), "A Baken Hamburger");
						strmid(Cooking[playerid][pCook3], gString, 0, strlen(gString), 255);
						Cooking[playerid][pCWeight3] = Groceries[playerid][pHamburger];
						Cooking[playerid][pCookID3] = 30;
						Groceries[playerid][pHamburgers] = 0; Groceries[playerid][pHamburger] = 0;
						format(gString, sizeof(gString), "* You've made %s, weighting %d LBS.",Cooking[playerid][pCook3],Cooking[playerid][pCWeight3]);
						SendClientMessage(playerid,COLOR_LIGHTBLUE, gString);
					}
					else if(Cooking[playerid][pCWeight4] == 0)
					{
						format(gString, sizeof(gString), "A Baken Hamburger");
						strmid(Cooking[playerid][pCook4], gString, 0, strlen(gString), 255);
						Cooking[playerid][pCWeight4] = Groceries[playerid][pHamburger];
						Cooking[playerid][pCookID4] = 30;
						Groceries[playerid][pHamburgers] = 0; Groceries[playerid][pHamburger] = 0;
						format(gString, sizeof(gString), "* You've made %s, weighting %d LBS.",Cooking[playerid][pCook4],Cooking[playerid][pCWeight4]);
						SendClientMessage(playerid,COLOR_LIGHTBLUE, gString);
					}
					else if(Cooking[playerid][pCWeight5] == 0)
					{
						format(gString, sizeof(gString), "A Baken Hamburger");
						strmid(Cooking[playerid][pCook5], gString, 0, strlen(gString), 255);
						Cooking[playerid][pCWeight5] = Groceries[playerid][pHamburger];
						Cooking[playerid][pCookID5] = 30;
						Groceries[playerid][pHamburgers] = 0; Groceries[playerid][pHamburger] = 0;
						format(gString, sizeof(gString), "* You've made %s, weighting %d LBS.",Cooking[playerid][pCook5],Cooking[playerid][pCWeight5]);
						SendClientMessage(playerid,COLOR_LIGHTBLUE, gString);
					}
					else
					{
						SendClientMessage(playerid, COLOR_GREY, "   You don't have any space in your Cooking List !");
						return 1;
					}
				}
				else
				{
					SendClientMessage(playerid, COLOR_GREY, "   You don't have any Hamburgers with you !");
					return 1;
				}
			}
			else
			{
				SendClientMessage(playerid, COLOR_GREY, "   You need to be at Burger Shot to Cook this !");
				return 1;
			}
		}
		else if(strcmp(x_nr,"pizza",true) == 0)
		{
			if(PlayerToPoint(3.0,playerid,374.1185,-113.6361,1001.4922) || PlayerToPoint(3.0,playerid,377.7971,-113.7668,1001.4922))
			{//Well Stacked Pizza
				if(Groceries[playerid][pPizza] != 0)
				{
					if(Cooking[playerid][pCWeight1] == 0)
					{
						format(gString, sizeof(gString), "A Baken Pizza");
						strmid(Cooking[playerid][pCook1], gString, 0, strlen(gString), 255);
						Cooking[playerid][pCWeight1] = Groceries[playerid][pHamburger];
						Cooking[playerid][pCookID1] = 30;
						Groceries[playerid][pPizzas] = 0; Groceries[playerid][pPizza] = 0;
						format(gString, sizeof(gString), "* You've made %s, weighting %d LBS.",Cooking[playerid][pCook1],Cooking[playerid][pCWeight1]);
						SendClientMessage(playerid,COLOR_LIGHTBLUE, gString);
					}
					else if(Cooking[playerid][pCWeight2] == 0)
					{
						format(gString, sizeof(gString), "A Baken Pizza");
						strmid(Cooking[playerid][pCook2], gString, 0, strlen(gString), 255);
						Cooking[playerid][pCWeight2] = Groceries[playerid][pHamburger];
						Cooking[playerid][pCookID2] = 30;
						Groceries[playerid][pPizzas] = 0; Groceries[playerid][pPizza] = 0;
						format(gString, sizeof(gString), "* You've made %s, weighting %d LBS.",Cooking[playerid][pCook2],Cooking[playerid][pCWeight2]);
						SendClientMessage(playerid,COLOR_LIGHTBLUE, gString);
					}
					else if(Cooking[playerid][pCWeight3] == 0)
					{
						format(gString, sizeof(gString), "A Baken Pizza");
						strmid(Cooking[playerid][pCook3], gString, 0, strlen(gString), 255);
						Cooking[playerid][pCWeight3] = Groceries[playerid][pHamburger];
						Cooking[playerid][pCookID3] = 30;
						Groceries[playerid][pPizzas] = 0; Groceries[playerid][pPizza] = 0;
						format(gString, sizeof(gString), "* You've made %s, weighting %d LBS.",Cooking[playerid][pCook3],Cooking[playerid][pCWeight3]);
						SendClientMessage(playerid,COLOR_LIGHTBLUE, gString);
					}
					else if(Cooking[playerid][pCWeight4] == 0)
					{
						format(gString, sizeof(gString), "A Baken Pizza");
						strmid(Cooking[playerid][pCook4], gString, 0, strlen(gString), 255);
						Cooking[playerid][pCWeight4] = Groceries[playerid][pHamburger];
						Cooking[playerid][pCookID4] = 30;
						Groceries[playerid][pPizzas] = 0; Groceries[playerid][pPizza] = 0;
						format(gString, sizeof(gString), "* You've made %s, weighting %d LBS.",Cooking[playerid][pCook4],Cooking[playerid][pCWeight4]);
						SendClientMessage(playerid,COLOR_LIGHTBLUE, gString);
					}
					else if(Cooking[playerid][pCWeight5] == 0)
					{
						format(gString, sizeof(gString), "A Baken Pizza");
						strmid(Cooking[playerid][pCook5], gString, 0, strlen(gString), 255);
						Cooking[playerid][pCWeight5] = Groceries[playerid][pHamburger];
						Cooking[playerid][pCookID5] = 30;
						Groceries[playerid][pPizzas] = 0; Groceries[playerid][pPizza] = 0;
						format(gString, sizeof(gString), "* You've made %s, weighting %d LBS.",Cooking[playerid][pCook5],Cooking[playerid][pCWeight5]);
						SendClientMessage(playerid,COLOR_LIGHTBLUE, gString);
					}
					else
					{
						SendClientMessage(playerid, COLOR_GREY, "   You don't have any space in your Cooking List !");
						return 1;
					}
				}
				else
				{
					SendClientMessage(playerid, COLOR_GREY, "   You don't have any Pizzas with you !");
					return 1;
				}
			}
			else
			{
				SendClientMessage(playerid, COLOR_GREY, "   You need to be at Well Stacked Pizza to Cook this !");
				return 1;
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   Invalid Cooking Name !");
			return 1;
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   You are not at one of the Cooking Places (Cluckin Bell / Burger Shot / Well Stacked Pizza).");
		return 1;
	}
	return 1;
}

CMD:cooked(playerid, params[]) {
	SendClientMessage(playerid, COLOR_WHITE, "|__________________ Cooking __________________|");
	format(gString, sizeof(gString), "** (1) Made: %s.   Weight: %d.", Cooking[playerid][pCook1], Cooking[playerid][pCWeight1]);
	SendClientMessage(playerid, COLOR_GREY, gString);
	format(gString, sizeof(gString), "** (2) Made: %s.   Weight: %d.", Cooking[playerid][pCook2], Cooking[playerid][pCWeight2]);
	SendClientMessage(playerid, COLOR_GREY, gString);
	format(gString, sizeof(gString), "** (3) Made: %s.   Weight: %d.", Cooking[playerid][pCook3], Cooking[playerid][pCWeight3]);
	SendClientMessage(playerid, COLOR_GREY, gString);
	format(gString, sizeof(gString), "** (4) Made: %s.   Weight: %d.", Cooking[playerid][pCook4], Cooking[playerid][pCWeight4]);
	SendClientMessage(playerid, COLOR_GREY, gString);
	format(gString, sizeof(gString), "** (5) Made: %s.   Weight: %d.", Cooking[playerid][pCook5], Cooking[playerid][pCWeight5]);
	SendClientMessage(playerid, COLOR_GREY, gString);
	SendClientMessage(playerid, COLOR_WHITE, "|____________________________________________|");
	return 1;
}

CMD:fish(playerid, params[]) {
	if(PlayerInfo[playerid][pFishes] > 5)
	{
		SendClientMessage(playerid, COLOR_GREY, "   Caught to many fish, wait till its reduced !");
		return 1;
	}
	if(Fishes[playerid][pWeight1] > 0 && Fishes[playerid][pWeight2] > 0 && Fishes[playerid][pWeight3] > 0 && Fishes[playerid][pWeight4] > 0 && Fishes[playerid][pWeight5] > 0)
	{
		SendClientMessage(playerid, COLOR_GREY, "   You already caught 5 Fishes, sell / eat / release them first !");
		return 1;
	}
	new Veh = GetPlayerVehicleID(playerid);
	if((IsAtFishPlace(playerid)) || IsABoat(Veh))
	{
		new Caught;
		new rand;
		new fstring[MAX_PLAYER_NAME];
		new Level = PlayerInfo[playerid][pFishSkill];
		if(Level >= 0 && Level <= 50) { Caught = random(20)-7; }
		else if(Level >= 51 && Level <= 100) { Caught = random(50)-20; }
		else if(Level >= 101 && Level <= 200) { Caught = random(100)-50; }
		else if(Level >= 201 && Level <= 400) { Caught = random(160)-60; }
		else if(Level >= 401) { Caught = random(180)-70; }
		rand = random(FishNamesNumber);
		if(Caught <= 0)
		{
			SendClientMessage(playerid, COLOR_GREY, "   Line snapped !");
			return 1;
		}
		else if(rand == 0)
		{
			SendClientMessage(playerid, COLOR_GREY, "   You caught a Jacket and threw it away !");
			return 1;
		}
		else if(rand == 4)
		{
			SendClientMessage(playerid, COLOR_GREY, "   You caught a Pants and threw it away !");
			return 1;
		}
		else if(rand == 7)
		{
			SendClientMessage(playerid, COLOR_GREY, "   You caught a Can and threw it away !");
			return 1;
		}
		else if(rand == 10)
		{
			SendClientMessage(playerid, COLOR_GREY, "   You caught a pair of Shoes and threw it away !");
			return 1;
		}
		else if(rand == 13)
		{
			SendClientMessage(playerid, COLOR_GREY, "   You caught some Garbage and threw it away !");
			return 1;
		}
		else if(rand == 20)
		{
			new mrand = random(500);
			format(gString, sizeof(gString), "* You caught a Money Bag, containing $%d.", mrand);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
			GivePlayerMoney(playerid, mrand);
			return 1;
		}
		if(PlayerInfo[playerid][pFishLic] < 1)
		{
			WantedPoints[playerid] += 1;
			SetPlayerCriminal(playerid,255, "Illegal Fishing");
		}
		if(Fishes[playerid][pWeight1] == 0)
		{
			PlayerInfo[playerid][pFishes] += 1;
			PlayerInfo[playerid][pFishSkill] += 1;
			format(fstring, sizeof(fstring), "%s", FishNames[rand]);
			strmid(Fishes[playerid][pFish1], fstring, 0, strlen(fstring), 255);
			Fishes[playerid][pWeight1] = Caught;
			format(gString, sizeof(gString), "* You have caught a %s, which weights %d Lbs.", Fishes[playerid][pFish1], Caught);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
			Fishes[playerid][pLastWeight] = Caught;
			Fishes[playerid][pLastFish] = 1;
			Fishes[playerid][pFid1] = rand;
			Fishes[playerid][pFishID] = rand;
			if(Caught > PlayerInfo[playerid][pBiggestFish])
			{
				format(gString, sizeof(gString), "* Your old record of %d Lbs has been passed, your new Biggest Fish is: %d Lbs.", PlayerInfo[playerid][pBiggestFish], Caught);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
				PlayerInfo[playerid][pBiggestFish] = Caught;
			}
		}
		else if(Fishes[playerid][pWeight2] == 0)
		{
			PlayerInfo[playerid][pFishes] += 1;
			PlayerInfo[playerid][pFishSkill] += 1;
			format(fstring, sizeof(fstring), "%s", FishNames[rand]);
			strmid(Fishes[playerid][pFish2], fstring, 0, strlen(fstring), 255);
			Fishes[playerid][pWeight2] = Caught;
			format(gString, sizeof(gString), "* You have caught a %s, which weights %d Lbs.", Fishes[playerid][pFish2], Caught);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
			Fishes[playerid][pLastWeight] = Caught;
			Fishes[playerid][pLastFish] = 2;
			Fishes[playerid][pFid2] = rand;
			Fishes[playerid][pFishID] = rand;
			if(Caught > PlayerInfo[playerid][pBiggestFish])
			{
				format(gString, sizeof(gString), "* Your old record of %d Lbs has been passed, your new Biggest Fish is: %d Lbs.", PlayerInfo[playerid][pBiggestFish], Caught);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
				PlayerInfo[playerid][pBiggestFish] = Caught;
			}
		}
		else if(Fishes[playerid][pWeight3] == 0)
		{
			PlayerInfo[playerid][pFishes] += 1;
			PlayerInfo[playerid][pFishSkill] += 1;
			format(fstring, sizeof(fstring), "%s", FishNames[rand]);
			strmid(Fishes[playerid][pFish3], fstring, 0, strlen(fstring), 255);
			Fishes[playerid][pWeight3] = Caught;
			format(gString, sizeof(gString), "* You have caught a %s, which weights %d Lbs.", Fishes[playerid][pFish3], Caught);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
			Fishes[playerid][pLastWeight] = Caught;
			Fishes[playerid][pLastFish] = 3;
			Fishes[playerid][pFid3] = rand;
			Fishes[playerid][pFishID] = rand;
			if(Caught > PlayerInfo[playerid][pBiggestFish])
			{
				format(gString, sizeof(gString), "* Your old record of %d Lbs has been passed, your new Biggest Fish is: %d Lbs.", PlayerInfo[playerid][pBiggestFish], Caught);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
				PlayerInfo[playerid][pBiggestFish] = Caught;
			}
		}
		else if(Fishes[playerid][pWeight4] == 0)
		{
			PlayerInfo[playerid][pFishes] += 1;
			PlayerInfo[playerid][pFishSkill] += 1;
			format(fstring, sizeof(fstring), "%s", FishNames[rand]);
			strmid(Fishes[playerid][pFish4], fstring, 0, strlen(fstring), 255);
			Fishes[playerid][pWeight4] = Caught;
			format(gString, sizeof(gString), "* You have caught a %s, which weights %d Lbs.", Fishes[playerid][pFish4], Caught);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
			Fishes[playerid][pLastWeight] = Caught;
			Fishes[playerid][pLastFish] = 4;
			Fishes[playerid][pFid4] = rand;
			Fishes[playerid][pFishID] = rand;
			if(Caught > PlayerInfo[playerid][pBiggestFish])
			{
				format(gString, sizeof(gString), "* Your old record of %d Lbs has been passed, your new Biggest Fish is: %d Lbs.", PlayerInfo[playerid][pBiggestFish], Caught);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
				PlayerInfo[playerid][pBiggestFish] = Caught;
			}
		}
		else if(Fishes[playerid][pWeight5] == 0)
		{
			PlayerInfo[playerid][pFishes] += 1;
			PlayerInfo[playerid][pFishSkill] += 1;
			format(fstring, sizeof(fstring), "%s", FishNames[rand]);
			strmid(Fishes[playerid][pFish5], fstring, 0, strlen(fstring), 255);
			Fishes[playerid][pWeight5] = Caught;
			format(gString, sizeof(gString), "* You have caught a %s, which weights %d Lbs.", Fishes[playerid][pFish5], Caught);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
			Fishes[playerid][pLastWeight] = Caught;
			Fishes[playerid][pLastFish] = 5;
			Fishes[playerid][pFid5] = rand;
			Fishes[playerid][pFishID] = rand;
			if(Caught > PlayerInfo[playerid][pBiggestFish])
			{
				format(gString, sizeof(gString), "* Your old record of %d Lbs has been passed, your new Biggest Fish is: %d Lbs.", PlayerInfo[playerid][pBiggestFish], Caught);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
				PlayerInfo[playerid][pBiggestFish] = Caught;
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   You dont have any space for your Fish !");
			return 1;
		}
		if(PlayerInfo[playerid][pFishSkill] == 50)
		{ SendClientMessage(playerid, COLOR_YELLOW, "* Your Fishing Skill is now Level 2, you can now catch Heavier Fishes."); }
		else if(PlayerInfo[playerid][pFishSkill] == 250)
		{ SendClientMessage(playerid, COLOR_YELLOW, "* Your Fishing Skill is now Level 3, you can now catch Heavier Fishes."); }
		else if(PlayerInfo[playerid][pFishSkill] == 500)
		{ SendClientMessage(playerid, COLOR_YELLOW, "* Your Fishing Skill is now Level 4, you can now catch Heavier Fishes."); }
		else if(PlayerInfo[playerid][pFishSkill] == 1000)
		{ SendClientMessage(playerid, COLOR_YELLOW, "* Your Fishing Skill is now Level 5, you can now catch Heavier Fishes."); }
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   You are not at a Fishing Place (Big Wheel Rods) or on a Fishing Boat !");
		return 1;
	}
	return 1;
}

CMD:fishes(playerid, params[]) {
	SendClientMessage(playerid, COLOR_WHITE, "|__________________ Fishes __________________|");
	format(gString, sizeof(gString), "** (1) Fish: %s.   Weight: %d.", Fishes[playerid][pFish1], Fishes[playerid][pWeight1]);
	SendClientMessage(playerid, COLOR_GREY, gString);
	format(gString, sizeof(gString), "** (2) Fish: %s.   Weight: %d.", Fishes[playerid][pFish2], Fishes[playerid][pWeight2]);
	SendClientMessage(playerid, COLOR_GREY, gString);
	format(gString, sizeof(gString), "** (3) Fish: %s.   Weight: %d.", Fishes[playerid][pFish3], Fishes[playerid][pWeight3]);
	SendClientMessage(playerid, COLOR_GREY, gString);
	format(gString, sizeof(gString), "** (4) Fish: %s.   Weight: %d.", Fishes[playerid][pFish4], Fishes[playerid][pWeight4]);
	SendClientMessage(playerid, COLOR_GREY, gString);
	format(gString, sizeof(gString), "** (5) Fish: %s.   Weight: %d.", Fishes[playerid][pFish5], Fishes[playerid][pWeight5]);
	SendClientMessage(playerid, COLOR_GREY, gString);
	SendClientMessage(playerid, COLOR_WHITE, "|____________________________________________|");
	return 1;
}

CMD:releasefish(playerid, params[]) {
	//if(!strlen(tmp))
	{
		SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /releasefish [fish]");
		return 1;
	}
	new fishid;
	if(fishid < 1 || fishid > 5) { SendClientMessage(playerid, COLOR_GREY, "   Fish number cant be below 1 or above 5 !"); return 1; }
	else if(fishid == 1 && Fishes[playerid][pWeight1] < 1) { SendClientMessage(playerid, COLOR_GREY, "   You didnt even catch a Fish at that number(1) !"); return 1; }
	else if(fishid == 2 && Fishes[playerid][pWeight2] < 1) { SendClientMessage(playerid, COLOR_GREY, "   You didnt even catch a Fish at that number(2) !"); return 1; }
	else if(fishid == 3 && Fishes[playerid][pWeight3] < 1) { SendClientMessage(playerid, COLOR_GREY, "   You didnt even catch a Fish at that number(3) !"); return 1; }
	else if(fishid == 4 && Fishes[playerid][pWeight4] < 1) { SendClientMessage(playerid, COLOR_GREY, "   You didnt even catch a Fish at that number(4) !"); return 1; }
	else if(fishid == 5 && Fishes[playerid][pWeight5] < 1) { SendClientMessage(playerid, COLOR_GREY, "   You didnt even catch a Fish at that number(5) !"); return 1; }
	ClearFishID(playerid, fishid);
	Fishes[playerid][pLastFish] = 0;
	Fishes[playerid][pFishID] = 0;
	return 1;
}

CMD:throwback(playerid, params[]) {
	if(Fishes[playerid][pLastFish] > 0)
	{
		ClearFishID(playerid, Fishes[playerid][pLastFish]);
		Fishes[playerid][pLastFish] = 0;
		Fishes[playerid][pFishID] = 0;
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   You haven't even catched a Fish yet !");
		return 1;
	}
	return 1;
}

CMD:throwbackall(playerid, params[]) {
	if(Fishes[playerid][pWeight1] > 0 || Fishes[playerid][pWeight2] > 0 || Fishes[playerid][pWeight3] > 0 || Fishes[playerid][pWeight4] > 0 || Fishes[playerid][pWeight5] > 0)
	{
		ClearFishes(playerid);
		Fishes[playerid][pLastFish] = 0;
		Fishes[playerid][pFishID] = 0;
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   You haven't even catched a Fish yet !");
		return 1;
	}
	return 1;
}

CMD:licenses(playerid, params[]) {
	new text1[20];
	new text2[20];
	new text3[20];
	new text4[20];
	new text5[20];
	if(PlayerInfo[playerid][pCarLic]) { text1 = "Passed"; } else { text1 = "Not Passed"; }
	if(PlayerInfo[playerid][pFlyLic]) { text4 = "Passed"; } else { text4 = "Not Passed"; }
	if(PlayerInfo[playerid][pBoatLic]) { text2 = "Passed"; } else { text2 = "Not Passed"; }
	if(PlayerInfo[playerid][pFishLic]) { text3 = "Passed"; } else { text3 = "Not Passed"; }
	if(PlayerInfo[playerid][pGunLic]) { text5 = "Passed"; } else { text5 = "Not Passed"; }
	SendClientMessage(playerid, COLOR_WHITE, "|__________________ Licenses __________________|");
	format(gString, sizeof(gString), "** Drivers License: %s.", text1);
	SendClientMessage(playerid, COLOR_GREY, gString);
	format(gString, sizeof(gString), "** Flying License: %s.", text4);
	SendClientMessage(playerid, COLOR_GREY, gString);
	format(gString, sizeof(gString), "** Sailing License: %s.", text2);
	SendClientMessage(playerid, COLOR_GREY, gString);
	format(gString, sizeof(gString), "** Fishing License: %s.", text3);
	SendClientMessage(playerid, COLOR_GREY, gString);
	format(gString, sizeof(gString), "** Weapon License: %s.", text5);
	SendClientMessage(playerid, COLOR_GREY, gString);
	SendClientMessage(playerid, COLOR_WHITE, "|______________________________________________|");
	return 1;
}

CMD:showlicenses(playerid, params[]) {
	//if(!strlen(tmp))
	{
		SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /showlicenses [playerid/PartOfName]");
		return 1;
	}
	new giveplayerid;
	if(IsPlayerConnected(giveplayerid))
	{
		if(giveplayerid != INVALID_PLAYER_ID)
		{
			if (ProxDetectorS(8.0, playerid, giveplayerid))
			{
				if(giveplayerid == playerid) { SendClientMessage(playerid, COLOR_GREY, "You cannot Show Licenses to yourself, use /licenses!"); return 1; }
				new text1[20];
				new text2[20];
				new text3[20];
				new text4[20];
				new text5[20];
				if(PlayerInfo[playerid][pCarLic]) { text1 = "Passed"; } else { text1 = "Not Passed"; }
				if(PlayerInfo[playerid][pFlyLic]) { text4 = "Passed"; } else { text4 = "Not Passed"; }
				if(PlayerInfo[playerid][pBoatLic]) { text2 = "Passed"; } else { text2 = "Not Passed"; }
				if(PlayerInfo[playerid][pFishLic]) { text3 = "Passed"; } else { text3 = "Not Passed"; }
				if(PlayerInfo[playerid][pGunLic]) { text5 = "Passed"; } else { text5 = "Not Passed"; }
				format(gString, sizeof(gString), "|__________ Licenses of %s __________|", PlayerInfo[playerid][pName]);
				SendClientMessage(giveplayerid, COLOR_WHITE, gString);
				format(gString, sizeof(gString), "** Drivers License: %s.", text1);
				SendClientMessage(giveplayerid, COLOR_GREY, gString);
				format(gString, sizeof(gString), "** Flying License: %s.", text4);
				SendClientMessage(giveplayerid, COLOR_GREY, gString);
				format(gString, sizeof(gString), "** Sailing License: %s.", text2);
				SendClientMessage(giveplayerid, COLOR_GREY, gString);
				format(gString, sizeof(gString), "** Fishing License: %s.", text3);
				SendClientMessage(giveplayerid, COLOR_GREY, gString);
				format(gString, sizeof(gString), "** Weapon License: %s.", text5);
				SendClientMessage(giveplayerid, COLOR_GREY, gString);
				format(gString, sizeof(gString), "* %s has shown his Licenses to you.", PlayerInfo[playerid][pName]);
				SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
				format(gString, sizeof(gString), "* You have shown your Licenses to %s.", PlayerInfo[giveplayerid][pName]);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
			}
			else
			{
				SendClientMessage(playerid, COLOR_GREY, "   That player is not near you !");
				return 1;
			}
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   That player is Offline !");
		return 1;
	}
	return 1;
}

CMD:frisk(playerid, params[]) {
	//if(!strlen(tmp))
	{
		SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /frisk [playerid/PartOfName]");
		return 1;
	}
	new giveplayerid;
	if(IsPlayerConnected(giveplayerid))
	{
		if(giveplayerid != INVALID_PLAYER_ID)
		{
			if (ProxDetectorS(8.0, playerid, giveplayerid))
			{
				if(giveplayerid == playerid) { SendClientMessage(playerid, COLOR_GREY, "You cannot Frisk yourself!"); return 1; }
				new text1[20], text2[20], text3[20], text4[20], text5[20];
				if(PlayerInfo[giveplayerid][pDrugs] > 0) { text1 = "| Drugs."; } else { text1 = "| Empty Pocket."; }
				if(PlayerInfo[giveplayerid][pMats] > 0) { text2 = "| Materials."; } else { text2 = "| Empty Pocket."; }
				if(Fishes[giveplayerid][pWeight1] > 0 || Fishes[giveplayerid][pWeight2] > 0 || Fishes[giveplayerid][pWeight3] > 0 || Fishes[giveplayerid][pWeight4] > 0 || Fishes[giveplayerid][pWeight5] > 0) { text3 = "| Fishes."; } else { text3 = "| Empty Pocket."; }
				if(PlayerInfo[giveplayerid][pPhoneBook] > 0) { text4 = "| Phone Book."; } else { text4 = "| Empty Pocket."; }
				if(PlayerInfo[giveplayerid][pCDPlayer] > 0) { text5 = "| CD-Player."; } else { text5 = "| Empty Pocket."; }
				format(gString, sizeof(gString), "|__________ Items with %s __________|", PlayerInfo[giveplayerid][pName]);
				SendClientMessage(playerid, COLOR_WHITE, gString);
				format(gString, sizeof(gString), "%s.", text1);
				SendClientMessage(playerid, COLOR_GREY, gString);
				format(gString, sizeof(gString), "%s.", text2);
				SendClientMessage(playerid, COLOR_GREY, gString);
				format(gString, sizeof(gString), "%s.", text3);
				SendClientMessage(playerid, COLOR_GREY, gString);
				format(gString, sizeof(gString), "%s.", text4);
				SendClientMessage(playerid, COLOR_GREY, gString);
				format(gString, sizeof(gString), "%s.", text5);
				SendClientMessage(playerid, COLOR_GREY, gString);
				format(gString, sizeof(gString), "* %s has frisked %s for any illegal items.", PlayerInfo[playerid][pName] ,PlayerInfo[giveplayerid][pName]);
				ProxDetector(30.0, playerid, gString, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
			}
			else
			{
				SendClientMessage(playerid, COLOR_GREY, "   That player is not near you !");
				return 1;
			}
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   That player is Offline !");
		return 1;
	}
	return 1;
}

CMD:sellcar(playerid, params[]) {
	if(PlayerInfo[playerid][pJob] != 10)
	{
		SendClientMessage(playerid,COLOR_GREY,"   You are not a Car Dealer !");
		return 1;
	}
	if(!IsPlayerInAnyVehicle(playerid))
	{
		SendClientMessage(playerid,COLOR_GREY,"   You are not in a Car !");
		return 1;
	}
	//if(!strlen(tmp))
	{
		SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /sellcar [playerid/PartOfName] [price]");
		return 1;
	}
	new giveplayerid;
	new money;
	if(money < 1 || money > 99999) { SendClientMessage(playerid, COLOR_GREY, "   Price not below $1 or above $99999 !"); return 1; }
	if (IsPlayerConnected(giveplayerid))
	{
		if(giveplayerid != INVALID_PLAYER_ID)
		{
			if (ProxDetectorS(8.0, playerid, giveplayerid))
			{
				if(giveplayerid == playerid)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Cant sell to yourself!");
					return 1;
				}
				if(CarCalls[giveplayerid] > 0)
				{
					SendClientMessage(playerid, COLOR_GREY, "   That player has already bought a car, has to use /callcar first !");
					return 1;
				}
				format(gString, sizeof(gString), "* You offerd %s to buy your Car for $%d .", PlayerInfo[giveplayerid][pName], money);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
				format(gString, sizeof(gString), "* Car Dealer %s wants to sell you his Car for $%d, (type /accept car) to buy.", PlayerInfo[playerid][pName], money);
				SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
				CarOffer[giveplayerid] = playerid;
				CarPrice[giveplayerid] = money;
				CarID[giveplayerid] = GetPlayerVehicleID(playerid);
			}
			else
			{
				SendClientMessage(playerid, COLOR_GREY, "   That player is not near you !");
			}
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   Invalid ID/Name !");
		return 1;
	}
	return 1;
}

CMD:portable(playerid, params[]) {
	if(PlayerInfo[playerid][pMember] == 8 || PlayerInfo[playerid][pLeader] == 8)
	{
		if(ConnectedToPC[playerid] == 255)
		{
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You have shutdowned your Laptop, and Disconnected from your Agency.");
			ConnectedToPC[playerid] = 0;
			return 1;
		}
		SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You have booted up your Laptop, and Connected to your Agency.");
		SendClientMessage(playerid, COLOR_WHITE, "|___ Hitman Agency ___|");
		SendClientMessage(playerid, COLOR_YELLOW2, "|");
		SendClientMessage(playerid, COLOR_YELLOW2, "| - News");
		SendClientMessage(playerid, COLOR_YELLOW2, "| - Contracts");
		SendClientMessage(playerid, COLOR_YELLOW2, "| - Givehit");
		SendClientMessage(playerid, COLOR_YELLOW2, "| - Order");
		SendClientMessage(playerid, COLOR_YELLOW2, "| - Ranks");
		SendClientMessage(playerid, COLOR_YELLOW2, "| - Logout");
		SendClientMessage(playerid, COLOR_WHITE, "|______________|00:00|");
		ConnectedToPC[playerid] = 255;
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   You are not a Member of the Hitman Agency !");
		return 1;
	}
	return 1;
}

CMD:materials(playerid, params[]) {
	if (PlayerInfo[playerid][pJob] != 9)
	{
		SendClientMessage(playerid,COLOR_GREY,"   You are not a Arms Dealer !");
		return 1;
	}
	new x_nr[256];
	if(!strlen(x_nr)) {
		SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /materials [name]");
		SendClientMessage(playerid, COLOR_WHITE, "Available names: Get, Deliver.");
		return 1;
	}
	if(strcmp(x_nr,"get",true) == 0)
	{
		if(PlayerToPoint(3.0,playerid,597.1277,-1248.6479,18.2734))
		{
			if(MatsHolding[playerid] >= 10)
			{
				SendClientMessage(playerid, COLOR_GREY, "   You can't hold any more Materials Packages !");
				return 1;
			}
			if(!strlen(tmp)) {
				SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /materials get [ammount]");
				return 1;
			}
			new moneys;
			if(moneys < 1 || moneys > 10) { SendClientMessage(playerid, COLOR_GREY, "   Package Number can't be below 1 or higher then 10 !"); return 1; }
			new price = moneys * 100;
			if(GetPlayerMoney(playerid) > price)
			{
				format(gString, sizeof(gString), "* You bought %d Materials Packages for $%d.", moneys, price);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
				GivePlayerMoney(playerid, - price);
				MatsHolding[playerid] = moneys;
			}
			else
			{
				format(gString, sizeof(gString), "   You can't afford the $%d !", price);
				SendClientMessage(playerid, COLOR_GREY, gString);
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   You are not at the Materials Package Building in Los Santos !");
			return 1;
		}
	}
	else if(strcmp(x_nr,"deliver",true) == 0)
	{
		if(PlayerToPoint(3.0,playerid,-2119.5469,-178.5679,35.3203))
		{
			if(MatsHolding[playerid] > 0)
			{
				new payout = (50)*(MatsHolding[playerid]);
				format(gString, sizeof(gString), "* The Factory gave you %d Materials for your %d Materials Packages.", payout, MatsHolding[playerid]);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
				PlayerInfo[playerid][pMats] += payout;
				MatsHolding[playerid] = 0;
			}
			else
			{
				SendClientMessage(playerid, COLOR_GREY, "   You don't have any Materials Packages !");
				return 1;
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   You are not at the Materials Factory in San Fierro !");
			return 1;
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   Invalid Materials Name !");
		return 1;
	}
	return 1;
}

CMD:sellgun(playerid, params[]) {
	if (PlayerInfo[playerid][pJob] != 9)
	{
		SendClientMessage(playerid,COLOR_GREY,"   You are not a Arms Dealer !");
		return 1;
	}
	new x_weapon[256],weapon[MAX_PLAYERS],ammo[MAX_PLAYERS],price[MAX_PLAYERS];
	//if(!strlen(tmp))
	{
		SendClientMessage(playerid, COLOR_GRAD1, "Uzycie: /sellgun [playerid/PartOfName] [weaponname]");
		SendClientMessage(playerid, COLOR_GREY, "Weapons: flowers(25) sdpistol(100) eagle(150) mp5(200) shotgun(200)");
		SendClientMessage(playerid, COLOR_GREY, "Weapons: ak47(600) m4(600) rifle (600)");
		return 1;
	}
	new giveplayerid;
	if (IsPlayerConnected(giveplayerid))
	{
		if(giveplayerid != INVALID_PLAYER_ID)
		{
			if(!strlen(x_weapon))
			{
				SendClientMessage(playerid, COLOR_GREEN, "________________________________________________");
				SendClientMessage(playerid, COLOR_WHITE, "*** Sell Guns ***");
				SendClientMessage(playerid, COLOR_GREY, "Uzycie: /sellgun [playerid/PartOfName] [weaponname]");
				SendClientMessage(playerid, COLOR_GREY, "Weapons: flowers(25) sdpistol(100) eagle(200) mp5(200) shotgun(200)");
				SendClientMessage(playerid, COLOR_GREY, "Weapons: ak47(600) m4(600) rifle(600)");
				SendClientMessage(playerid, COLOR_GREEN, "________________________________________________");
				return 1;
			}
		}
		//if(strcmp(x_weapon,"knife",true) == 0) { if(PlayerInfo[playerid][pMats] > 99) { weapon[playerid] = 4; price[playerid] = 100; ammo[playerid] = 1; PlayerInfo[giveplayerid][pGun1] = 4; PlayerInfo[giveplayerid][pAmmo1] = 1; } else { SendClientMessage(playerid,COLOR_GREY,"   Not enough Materials for that Weapon!"); return 1; } }
		if(strcmp(x_weapon,"sdpistol",true) == 0) { if(PlayerInfo[playerid][pMats] > 99) { weapon[playerid] = 23; price[playerid] = 100; ammo[playerid] = 50; PlayerInfo[giveplayerid][pGun2] = 23; PlayerInfo[giveplayerid][pAmmo2] = 50; } else { SendClientMessage(playerid,COLOR_GREY,"   Not enough Materials for that Weapon!"); return 1; } }
		else if(strcmp(x_weapon,"flowers",true) == 0) { if(PlayerInfo[playerid][pMats] > 24) { weapon[playerid] = 14; price[playerid] = 25; ammo[playerid] = 1; PlayerInfo[giveplayerid][pGun1] = 14; PlayerInfo[giveplayerid][pAmmo1] = 1; } else { SendClientMessage(playerid,COLOR_GREY,"   Not enough Materials for that Weapon!"); return 1; } }
		else if(strcmp(x_weapon,"eagle",true) == 0) { if(PlayerInfo[playerid][pMats] > 199) { weapon[playerid] = 24; price[playerid] = 150; ammo[playerid] = 50; PlayerInfo[giveplayerid][pGun2] = 24; PlayerInfo[giveplayerid][pAmmo2] = 50; } else { SendClientMessage(playerid,COLOR_GREY,"   Not enough Materials for that Weapon!"); return 1; } }
		else if(strcmp(x_weapon,"mp5",true) == 0) {if(PlayerInfo[playerid][pMats] > 199) { weapon[playerid] = 29; price[playerid] = 200; ammo[playerid] = 200; PlayerInfo[giveplayerid][pGun2] = 29; PlayerInfo[giveplayerid][pAmmo2] = 200; } else { SendClientMessage(playerid,COLOR_GREY,"   Not enough Materials for that Weapon!"); return 1; } }
		else if(strcmp(x_weapon,"shotgun",true) == 0) {if(PlayerInfo[playerid][pMats] > 199) { weapon[playerid] = 25; price[playerid] = 200; ammo[playerid] = 50; PlayerInfo[giveplayerid][pGun2] = 25; PlayerInfo[giveplayerid][pAmmo2] = 50; } else { SendClientMessage(playerid,COLOR_GREY,"   Not enough Materials for that Weapon!"); return 1; } }
		//else if(strcmp(x_weapon,"spas12",true) == 0) { if(PlayerInfo[playerid][pMats] > 599) { weapon[playerid] = 27; price[playerid] = 600; ammo[playerid] = 50; PlayerInfo[giveplayerid][pGun2] = 27; PlayerInfo[giveplayerid][pAmmo2] = 50; } else { SendClientMessage(playerid,COLOR_GREY,"   Not enough Materials for that Weapon!"); return 1; } }
		else if(strcmp(x_weapon,"ak47",true) == 0) { if(PlayerInfo[playerid][pMats] > 599) { weapon[playerid] = 30; price[playerid] = 600; ammo[playerid] = 250; PlayerInfo[giveplayerid][pGun2] = 30; PlayerInfo[giveplayerid][pAmmo2] = 250; } else { SendClientMessage(playerid,COLOR_GREY,"   Not enough Materials for that Weapon!"); return 1; } }
		else if(strcmp(x_weapon,"m4",true) == 0) { if(PlayerInfo[playerid][pMats] > 599) { weapon[playerid] = 31; price[playerid] = 600; ammo[playerid] = 250; PlayerInfo[giveplayerid][pGun2] = 31; PlayerInfo[giveplayerid][pAmmo2] = 250; } else { SendClientMessage(playerid,COLOR_GREY,"   Not enough Materials for that Weapon!"); return 1; } }
		else if(strcmp(x_weapon,"rifle",true) == 0) { if(PlayerInfo[playerid][pMats] > 599) { weapon[playerid] = 33; price[playerid] = 600; ammo[playerid] = 50; PlayerInfo[giveplayerid][pGun2] = 33; PlayerInfo[giveplayerid][pAmmo2] = 50; } else { SendClientMessage(playerid,COLOR_GREY,"   Not enough Materials for that Weapon!"); return 1; } }
		else { SendClientMessage(playerid,COLOR_GREY,"   Invalid Weapon name!"); return 1; }
		if (ProxDetectorS(5.0, playerid, giveplayerid))
		{
			if(giveplayerid == playerid)
			{
				SendClientMessage(playerid, COLOR_GRAD1, "   You can not sell Guns to yourself!");
				return 1;
			}
			if(PlayerInfo[playerid][pMiserPerk] > 0)
			{
				new skill = 2 * PlayerInfo[playerid][pMiserPerk];
				new mats = price[playerid] / 100;
				price[playerid] -= (mats)*(skill);
			}
			ConsumingMoney[playerid] = 1;
			format(gString, sizeof(gString), "   You have given %s, a %s with %d ammo, for %d Materials.", PlayerInfo[giveplayerid][pName],x_weapon, ammo[playerid], price[playerid]);
			PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
			SendClientMessage(playerid, COLOR_GRAD1, gString);
			format(gString, sizeof(gString), "   You have recieved a %s with %d ammo from %s.", x_weapon, ammo[playerid], PlayerInfo[playerid][pName]);
			SendClientMessage(giveplayerid, COLOR_GRAD1, gString);
			PlayerPlaySound(giveplayerid, 1052, 0.0, 0.0, 0.0);
			format(gString, sizeof(gString), "* %s created a Gun from Materials, and hands it to %s.", PlayerInfo[playerid][pName] ,PlayerInfo[giveplayerid][pName]);
			ProxDetector(30.0, playerid, gString, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
			GivePlayerWeapon(giveplayerid,weapon[playerid],ammo[playerid]);
			PlayerInfo[playerid][pMats] -= price[playerid];
		}
		else
		{
			SendClientMessage(playerid, COLOR_GRAD1, "   Your too far away.");
			return 1;
		}
	}
	else
	{
		format(gString, sizeof(gString), "   %d is not an active player.", giveplayerid);
		SendClientMessage(playerid, COLOR_GRAD1, gString);
	}
	return 1;
}

CMD:get(playerid, params[]) {
	new x_job[256];

	if(!strlen(x_job)) {
		SendClientMessage(playerid, COLOR_WHITE, "|__________________ Get __________________|");
		SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /get [name]");
		SendClientMessage(playerid, COLOR_GREY, "Available names: Drugs, Fuel");
		SendClientMessage(playerid, COLOR_GREEN, "|_________________________________________|");
		return 1;
	}

	if(strcmp(x_job,"drugs",true) == 0)
	{
		if(PlayerInfo[playerid][pDrugs] > 15)
		{
			format(gString, sizeof(gString), "  You still have %d grams with you, sell them first !", PlayerInfo[playerid][pDrugs]);
			SendClientMessage(playerid, COLOR_GREY, gString);
			return 1;
		}
		new tel;
		new price;
		new ammount;
		//if(!strlen(tmp))
		{
			SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /get drugs [ammount]");
			return 1;
		}
		new level = PlayerInfo[playerid][pDrugsSkill];
		if(level >= 0 && level <= 50)
		{ tel = 200; if(ammount < 1 || ammount > 6) { SendClientMessage(playerid, COLOR_GREY, "   You cant go below 1 or above 6 at your Skill Level!"); return 1; } }
		else if(level >= 51 && level <= 100)
		{ tel = 150; if(ammount < 1 || ammount > 12) { SendClientMessage(playerid, COLOR_GREY, "   You cant go below 1 or above 12 at your Skill Level!"); return 1; } }
		else if(level >= 101 && level <= 200)
		{ tel = 100; if(ammount < 1 || ammount > 20) { SendClientMessage(playerid, COLOR_GREY, "   You cant go below 1 or above 20 at your Skill Level!"); return 1; } }
		else if(level >= 201 && level <= 400)
		{ tel = 50; if(ammount < 1 || ammount > 30) { SendClientMessage(playerid, COLOR_GREY, "   You cant go below 1 or above 30 at your Skill Level!"); return 1; } }
		else if(level >= 401)
		{ tel = 10; if(ammount < 1 || ammount > 99) { SendClientMessage(playerid, COLOR_GREY, "   You cant go below 1 or above 99 at your Skill Level!"); return 1; } }
		if (PlayerInfo[playerid][pJob] == 4 && PlayerToPoint(2.0, playerid, 323.0342,1118.5804,1083.8828))
		{
		price = ammount * tel;
			if(GetPlayerMoney(playerid) > price)
			{
				format(gString, sizeof(gString), "* You bought %d grams for $%d.", ammount, price);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
				GivePlayerMoney(playerid, -price);
				PlayerInfo[playerid][pDrugs] = ammount;
			}
			else
			{
				SendClientMessage(playerid, COLOR_GREY, "   You cant afford the Drugs !");
				return 1;
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   You are not a Drugs Dealer, or not at the Cracker House !");
			return 1;
		}
	}
	else if(strcmp(x_job,"fuel",true) == 0)
	{
		if(IsAtGasStation(playerid))
		{
			new price = 20 * SBizzInfo[3][sbEntranceCost];
			format(gString, sizeof(gString), "* You filled your Gas Can with 20% Fuel for $%d",price);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
			PlayerInfo[playerid][pFuel] = 20;
			GivePlayerMoney(playerid, - price);
			return 1;
		}
		else
		{
			SendClientMessage(playerid,COLOR_GREY,"   You're not at a Gas Station!");
			return 1;
		}
	}
	else { return 1; }
	return 1;
}

CMD:join(playerid, params[]) {
	if(PlayerInfo[playerid][pJob] == 0)
	{
		if(gTeam[playerid] == 1 || gTeam[playerid] == 2 || gTeam[playerid] == 4 || gTeam[playerid] == 11)
		{
			SendClientMessage(playerid, COLOR_GREY, "   You must be a Civilian (Not Wanted) or a Family Member to get a Job !");
			return 1;
		}
		if (GetPlayerState(playerid) == 1 && PlayerToPoint(3.0, playerid,359.5408,206.7693,1008.3828))
		{
			if(PlayerInfo[playerid][pMember] > 0 || PlayerInfo[playerid][pFMember] < 255) { SendClientMessage(playerid, COLOR_GREY, "   Families cannot take on this Job !"); return 1; }
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You are about to become a Detective, and get a 5 hour Contract.");
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You have to forfill this Contract first, if you want to Quit the job later.");
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "* If you are sure to become a Detective, type /accept job.");
			GettingJob[playerid] = 1;
		}
		else if (GetPlayerState(playerid) == 1 && PlayerToPoint(3.0, playerid,347.7374,193.7241,1014.1875))
		{
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You are about to become a Lawyer, and get a 5 hour Contract.");
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You have to forfill this Contract first, if you want to Quit the job later.");
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "* If you are sure to become a Lawyer, type /accept job.");
			GettingJob[playerid] = 2;
		}
		else if (GetPlayerState(playerid) == 1 && PlayerToPoint(3.0, playerid,1215.1304,-11.8431,1000.9219))
		{
			if(PlayerInfo[playerid][pMember] > 0 || PlayerInfo[playerid][pFMember] < 255) { SendClientMessage(playerid, COLOR_GREY, "   Families cannot take on this Job !"); return 1; }
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You are about to become a Whore, and get a 5 hour Contract.");
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You have to forfill this Contract first, if you want to Quit the job later.");
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "* If you are sure to become a Whore, type /accept job.");
			GettingJob[playerid] = 3;
		}
		else if (GetPlayerState(playerid) == 1 && PlayerToPoint(3.0, playerid,2166.3772,-1675.3829,15.0859))
		{
			if(PlayerInfo[playerid][pMember] > 0 || PlayerInfo[playerid][pFMember] < 255) { SendClientMessage(playerid, COLOR_GREY, "   Families cannot take on this Job !"); return 1; }
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You are about to become a Drugs Dealer, and get a 5 hour Contract.");
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You have to forfill this Contract first, if you want to Quit the job later.");
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "* If you are sure to become a Drugs Dealer, type /accept job.");
			GettingJob[playerid] = 4;
		}
		else if (GetPlayerState(playerid) == 1 && PlayerToPoint(3.0, playerid,1109.3318,-1796.3042,16.5938))
		{
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You are about to become a Car Jacker, and get a 5 hour Contract.");
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You have to forfill this Contract first, if you want to Quit the job later.");
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "* If you are sure to become a Car Jacker, type /accept job.");
			GettingJob[playerid] = 5;
		}
		else if (GetPlayerState(playerid) == 1 && PlayerToPoint(3.0, playerid,-1932.3859,276.2117,41.0391))
		{
			if(PlayerInfo[playerid][pMember] > 0 || PlayerInfo[playerid][pFMember] < 255) { SendClientMessage(playerid, COLOR_GREY, "   Families cannot take on this Job !"); return 1; }
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You are about to become a Car Mechanic, and get a 5 hour Contract.");
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You have to forfill this Contract first, if you want to Quit the job later.");
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "* If you are sure to become a Car Mechanic, type /accept job.");
			GettingJob[playerid] = 7;
		}
		else if (GetPlayerState(playerid) == 1 && PlayerToPoint(3.0, playerid,2226.1716,-1718.1792,13.5165))
		{
			if(PlayerInfo[playerid][pMember] > 0 || PlayerInfo[playerid][pFMember] < 255) { SendClientMessage(playerid, COLOR_GREY, "   Families cannot take on this Job !"); return 1; }
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You are about to become a Bodyguard, and get a 5 hour Contract.");
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You have to forfill this Contract first, if you want to Quit the job later.");
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "* If you are sure to become a Bodyguard, type /accept job.");
			GettingJob[playerid] = 8;
		}
		else if (GetPlayerState(playerid) == 1 && PlayerToPoint(3.0, playerid,1366.4325,-1275.2096,13.5469))
		{
			if(PlayerInfo[playerid][pMember] > 0 || PlayerInfo[playerid][pFMember] < 255) { SendClientMessage(playerid, COLOR_GREY, "   Families cannot take on this Job !"); return 1; }
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You are about to become a Arms Dealer, and get a 5 hour Contract.");
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You have to forfill this Contract first, if you want to Quit the job later.");
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "* If you are sure to become a Arms Dealer, type /accept job.");
			GettingJob[playerid] = 9;
		}
		else if (GetPlayerState(playerid) == 1 && PlayerToPoint(3.0, playerid,531.7930,-1292.4044,17.2422))
		{
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You are about to become a Car Dealer, and get a 5 hour Contract.");
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You have to forfill this Contract first, if you want to Quit the job later.");
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "* If you are sure to become a Car Dealer, type /accept job.");
			GettingJob[playerid] = 10;
		}
		else if (GetPlayerState(playerid) == 1 && PlayerToPoint(3.0, playerid,766.0804,14.5133,1000.7004))
		{
			if(PlayerInfo[playerid][pMember] > 0 || PlayerInfo[playerid][pFMember] < 255) { SendClientMessage(playerid, COLOR_GREY, "   Families cannot take on this Job !"); return 1; }
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You are about to become a Boxer, and get a 5 hour Contract.");
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You have to forfill this Contract first, if you want to Quit the job later.");
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "* If you are sure to become a Boxer, type /accept job.");
			GettingJob[playerid] = 12;
		}
		else if (GetPlayerState(playerid) == 1 && PlayerToPoint(3.0, playerid,1154.2208,-1770.8203,16.5992))
		{
			if(PlayerInfo[playerid][pMember] > 0 || PlayerInfo[playerid][pFMember] < 255) { SendClientMessage(playerid, COLOR_GREY, "   Families cannot take on this Job !"); return 1; }
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You are about to become a Bus Driver, and get a 5 hour Contract.");
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You have to forfill this Contract first, if you want to Quit the job later.");
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "* If you are sure to become a Bus Driver, type /accept job.");
			GettingJob[playerid] = 14;
		}
		else if (GetPlayerState(playerid) == 1 && PlayerToPoint(3.0, playerid,-2040.9436,456.2395,35.1719))
		{
			if(PlayerInfo[playerid][pMember] > 0 || PlayerInfo[playerid][pFMember] < 255) { SendClientMessage(playerid, COLOR_GREY, "   Families cannot take on this Job !"); return 1; }
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You are about to become a Paper Boy, and get a 5 hour Contract.");
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You have to forfill this Contract first, if you want to Quit the job later.");
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "* If you are sure to become a Paper Boy, type /accept job.");
			GettingJob[playerid] = 15;
		}
		else if (GetPlayerState(playerid) == 1 && PlayerToPoint(3.0, playerid,-77.7288,-1136.3896,1.0781))
		{
			if(PlayerInfo[playerid][pMember] > 0 || PlayerInfo[playerid][pFMember] < 255) { SendClientMessage(playerid, COLOR_GREY, "   Families cannot take on this Job !"); return 1; }
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You are about to become a Trucker, and get a 5 hour Contract.");
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You have to forfill this Contract first, if you want to Quit the job later.");
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "* If you are sure to become a Trucker, type /accept job.");
			GettingJob[playerid] = 16;
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   You are not even near a place to get a Job !");
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   You already have a Job, use /quitjob first !");
	}
	return 1;
}

CMD:fill(playerid, params[]) {
	if(IsAtGasStation(playerid))
	{
		GameTextForPlayer(playerid,"~w~~n~~n~~n~~n~~n~~n~~n~~n~~n~Re-Fueling Vehicle, please wait",2000,3);
		SetTimer("Fillup",RefuelWait,0);
		Refueling[playerid] = 1;
	}
	else
	{
		SendClientMessage(playerid,COLOR_GREY,"   You're not at a Gas Station!");
	}
	return 1;
}

CMD:fillcar(playerid, params[]) {
	if(PlayerInfo[playerid][pFuel] > 0)
	{
		if(Gas[gLastCar[playerid]] < 81)
		{
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "   You filled your car with 20 percent Fuel from your Gas Can.");
			Gas[gLastCar[playerid]] += 20;
			PlayerInfo[playerid][pFuel] = 0;
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   Your Car still got enough Fuel to drive with !");
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   You have no Fuel left in your Gas Can !");
	}
	return 1;
}

CMD:tazer(playerid, params[]) {
	if(gTeam[playerid] == 2 || IsACop(playerid))
		{
		if(IsPlayerInAnyVehicle(playerid))
		{
			SendClientMessage(playerid, COLOR_GREY, "   Cannot use this while being in the Car !");
			return 1;
		}
		new suspect = GetClosestPlayer(playerid);
		if(IsPlayerConnected(suspect))
		{
			if(PlayerCuffed[suspect] > 0)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Player already Cuffed !");
				return 1;
			}
			if(GetDistanceBetweenPlayers(playerid,suspect) < 5)
			{
				if(gTeam[suspect] == 2)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Cannot Tazer Cops / FBI / National Guard !");
					return 1;
				}
				if(IsPlayerInAnyVehicle(suspect))
				{
					SendClientMessage(playerid, COLOR_GREY, "   Suspect is in a Car, get him out first !");
					return 1;
				}
				format(gString, sizeof(gString), "* You were Tazed by %s for 8 seconds.", PlayerInfo[playerid][pName]);
				SendClientMessage(suspect, COLOR_LIGHTBLUE, gString);
				format(gString, sizeof(gString), "* You Tazed %s for 8 seconds.", PlayerInfo[suspect][pName]);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
				format(gString, sizeof(gString), "* %s shoots with his Tazer at %s, and tazed him.", PlayerInfo[playerid][pName] ,PlayerInfo[suspect][pName]);
				ProxDetector(30.0, playerid, gString, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
				GameTextForPlayer(suspect, "~r~Tazed", 2500, 3);
				TogglePlayerControllable(suspect, 0);
				PlayerCuffed[suspect] = 1;
				PlayerCuffedTime[suspect] = 8;
			}
			else
			{
				SendClientMessage(playerid, COLOR_GREY, "   No-one near you!");
				return 1;
			}
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   You are not a Cop / FBI / National Guard !");
	}
	return 1;
}

CMD:cuff(playerid, params[]) {
	if(gTeam[playerid] == 2 || IsACop(playerid))
	{
		//if(!strlen(tmp)) 
		{
			SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /cuff [Playerid/PartOfName]");
			return 1;
		}
		new giveplayerid;
		if(IsPlayerConnected(giveplayerid))
		{
			if(giveplayerid != INVALID_PLAYER_ID)
			{
				if(gTeam[giveplayerid] == 2 || IsACop(giveplayerid))
				{
					SendClientMessage(playerid, COLOR_GREY, "   You can't Cuff Cops !");
					return 1;
				}
				if(PlayerCuffed[giveplayerid] > 0)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Player already Cuffed !");
					return 1;
				}
				if (ProxDetectorS(8.0, playerid, giveplayerid))
				{
					new car = GetPlayerVehicleID(playerid);
					if(giveplayerid == playerid) { SendClientMessage(playerid, COLOR_GREY, "You cannot Cuff yourself!"); return 1; }
					if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == 2 && IsPlayerInVehicle(giveplayerid, car))
					{
						format(gString, sizeof(gString), "* You were Cuffed by %s, till uncuff.", PlayerInfo[playerid][pName]);
						SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
						format(gString, sizeof(gString), "* You Cuffed %s, till uncuff.", PlayerInfo[giveplayerid][pName]);
						SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
						format(gString, sizeof(gString), "* %s Hand Cuffs %s, so he wont go anywhere.", PlayerInfo[playerid][pName] ,PlayerInfo[giveplayerid][pName]);
						ProxDetector(30.0, playerid, gString, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
						GameTextForPlayer(giveplayerid, "~r~Cuffed", 2500, 3);
						TogglePlayerControllable(giveplayerid, 0);
						PlayerCuffed[giveplayerid] = 2;
						PlayerCuffedTime[giveplayerid] = 180;
					}
					else
					{
						SendClientMessage(playerid, COLOR_GREY, "   Player not in your Car, or your not the Driver !");
						return 1;
					}
				}
				else
				{
					SendClientMessage(playerid, COLOR_GREY, "   That player is not near you !");
					return 1;
				}
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   That player is Offline !");
			return 1;
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   You are not a Cop / FBI / National Guard !");
	}
	return 1;
}

CMD:uncuff(playerid, params[]) {
	if(gTeam[playerid] == 2)
	{
		//if(!strlen(tmp)) 
		{
			SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /uncuff [Playerid/PartOfName]");
			return 1;
		}
		new giveplayerid;
		if(IsPlayerConnected(giveplayerid))
		{
			if(giveplayerid != INVALID_PLAYER_ID)
			{
				if (ProxDetectorS(8.0, playerid, giveplayerid))
				{
					if(giveplayerid == playerid) { SendClientMessage(playerid, COLOR_GREY, "You cannot Uncuff yourself!"); return 1; }
					if(PlayerCuffed[giveplayerid])
					{
						format(gString, sizeof(gString), "* You were Uncuffed by %s.", PlayerInfo[playerid][pName]);
						SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
						format(gString, sizeof(gString), "* You Uncuffed %s.", PlayerInfo[giveplayerid][pName]);
						SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
						GameTextForPlayer(giveplayerid, "~g~Uncuffed", 2500, 3);
						TogglePlayerControllable(giveplayerid, 1);
						PlayerCuffed[giveplayerid] = 0;
					}
					else
					{
						SendClientMessage(playerid, COLOR_GREY, "   That player isn't Tied up !");
						return 1;
					}
				}
				else
				{
					SendClientMessage(playerid, COLOR_GREY, "   That player is not near you !");
					return 1;
				}
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   That player is Offline !");
			return 1;
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   You are not a Cop / FBI / National Guard !");
	}
	return 1;
}

CMD:find(playerid, params[]) {
	if(PlayerInfo[playerid][pJob] != 1)
	{
		SendClientMessage(playerid, COLOR_GREY, "   You are not a Detective !");
		return 1;
	}
	if(PlayerOnMission[playerid] > 0)
	{
		SendClientMessage(playerid, COLOR_GREY, "   On a mission right now, can't use this command !");
		return 1;
	}
	if(UsedFind[playerid] != 0 && PlayerInfo[playerid][pDetSkill] < 401)
	{
		SendClientMessage(playerid, COLOR_GREY, "   You've already searched for someone, wait 2 minutes !");
		return 1;
	}
	//if(!strlen(tmp))
	{
		SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /find [playerid/PartOfName]");
		return 1;
	}
	new giveplayerid;
	if(IsPlayerConnected(giveplayerid))
	{
		if(giveplayerid != INVALID_PLAYER_ID)
		{
			if(giveplayerid == playerid) { SendClientMessage(playerid, COLOR_GREY, "You cannot Find yourself!"); return 1; }
			new points;
			new level = PlayerInfo[playerid][pDetSkill];
			if(level >= 0 && level <= 50)
			{ points = 4; }
			else if(level >= 51 && level <= 100)
			{ points = 6; }
			else if(level >= 101 && level <= 200)
			{ points = 8; }
			else if(level >= 201 && level <= 400)
			{ points = 10; }
			else if(level >= 401)
			{ points = 12; }
			new Float:X,Float:Y,Float:Z;
			GetPlayerPos(giveplayerid, X,Y,Z);
			SetPlayerCheckpoint(playerid, X,Y,Z, 6);
			FindTime[playerid] = 1;
			FindTimePoints[playerid] = points;
			PlayerInfo[playerid][pDetSkill] ++;
			UsedFind[playerid] = 1;
			if(PlayerInfo[playerid][pDetSkill] == 50)
			{ SendClientMessage(playerid, COLOR_YELLOW, "* Your Detective Skill is now Level 2, soon you are able to find Faction Members."); }
			else if(PlayerInfo[playerid][pDetSkill] == 100)
			{ SendClientMessage(playerid, COLOR_YELLOW, "* Your Detective Skill is now Level 3, soon you are able to find Faction Members."); }
			else if(PlayerInfo[playerid][pDetSkill] == 200)
			{ SendClientMessage(playerid, COLOR_YELLOW, "* Your Detective Skill is now Level 4, you are now able to find Faction Members."); }
			else if(PlayerInfo[playerid][pDetSkill] == 400)
			{ SendClientMessage(playerid, COLOR_YELLOW, "* Your Detective Skill is now Level 5, you are now able to find Faction Members."); }
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   Invalid Name/ID !");
	}
	return 1;
}

CMD:guard(playerid, params[]) {
	if(PlayerInfo[playerid][pJob] != 8)
	{
		SendClientMessage(playerid, COLOR_GREY, "   You are not a Bodyguard!");
		return 1;
	}
//	if(!strlen(tmp))
	{
		SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /guard [playerid/PartOfName] [price]");
		return 1;
	}
	new money;
	new giveplayerid;
	if(money < 1 || money > 99999) { SendClientMessage(playerid, COLOR_GREY, "   Price not lower then 1, or above 99999!"); return 1; }
	if(IsPlayerConnected(giveplayerid))
	{
		if(giveplayerid != INVALID_PLAYER_ID)
		{
			if(ProxDetectorS(8.0, playerid, giveplayerid))
			{
				if(giveplayerid == playerid)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Cant offer protection to yourself !");
					return 1;
				}
				format(gString, sizeof(gString), "* You offerd protection to %s for $%d.", PlayerInfo[giveplayerid][pName], money);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
				format(gString, sizeof(gString), "* Bodyguard %s wants to protect you for $%d, (type /accept bodyguard) to accept.", PlayerInfo[playerid][pName], money);
				SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
				GuardOffer[giveplayerid] = playerid;
				GuardPrice[giveplayerid] = money;
			}
			else
			{
				SendClientMessage(playerid, COLOR_GREY, "   That player is not near you !");
			}
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   That player is offline!");
	}
	return 1;
}

CMD:free(playerid, params[]) {
	if(PlayerInfo[playerid][pJob] != 2)
	{
		SendClientMessage(playerid, COLOR_GREY, "   You are not a Lawyer!");
		return 1;
	}
	if(PlayerInfo[playerid][pLawSkill] >= 401)
	{
		ApprovedLawyer[playerid] = 1;
	}
	//if(!strlen(tmp))
	{
		SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /free [playerid/PartOfName]");
		return 1;
	}
	new giveplayerid;
	if(IsPlayerConnected(giveplayerid))
	{
		if(giveplayerid != INVALID_PLAYER_ID)
		{
			if(giveplayerid == playerid) { SendClientMessage(playerid, COLOR_GREY, "You cannot Free yourself!"); return 1; }
			if(PlayerInfo[giveplayerid][pJailed] == 1 && ApprovedLawyer[playerid] == 1)
			{
				format(gString, sizeof(gString), "* You freed %s out of jail.", PlayerInfo[giveplayerid][pName]);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
				format(gString, sizeof(gString), "* You were freed out of jail, by Lawyer %s.", PlayerInfo[playerid][pName]);
				SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
				ApprovedLawyer[playerid] = 0;
				WantLawyer[giveplayerid] = 0;
				CallLawyer[giveplayerid] = 0;
				JailPrice[giveplayerid] = 0;
				PlayerInfo[giveplayerid][pJailTime] = 1;
				PlayerInfo[playerid][pLawSkill] ++;
				if(PlayerInfo[playerid][pLawSkill] == 50)
				{ SendClientMessage(playerid, COLOR_YELLOW, "* Your Lawyer Skill is now Level 2, you will earn more Money and quicker Reload Time."); }
				else if(PlayerInfo[playerid][pLawSkill] == 100)
				{ SendClientMessage(playerid, COLOR_YELLOW, "* Your Lawyer Skill is now Level 3, you will earn more Money and quicker Reload Time."); }
				else if(PlayerInfo[playerid][pLawSkill] == 200)
				{ SendClientMessage(playerid, COLOR_YELLOW, "* Your Lawyer Skill is now Level 4, you will earn more Money and quicker Reload Time."); }
				else if(PlayerInfo[playerid][pLawSkill] == 400)
				{ SendClientMessage(playerid, COLOR_YELLOW, "* Your Lawyer Skill is now Level 5, you will earn more Money and quicker Reload Time."); }
			}
			else
			{
				SendClientMessage(playerid, COLOR_GRAD1, "   Player didnt need a Lawyer / Player aint Jailed !");
			}
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   That player is offline!");
	}
	return 1;
}

CMD:cancel(playerid, params[]) {
	new x_job[256];
	if(!strlen(x_job)) {
		SendClientMessage(playerid, COLOR_WHITE, "|__________________ Cancel __________________|");
		SendClientMessage(playerid, COLOR_WHITE, "Uzycie: /cancel [name]");
		SendClientMessage(playerid, COLOR_GREY, "Available names: Sex, Drugs, Repair, Lawyer, Bodyguard, Live, Refill, Car, Boxing");
		SendClientMessage(playerid, COLOR_GREY, "Available names: Taxi, Bus, Medic, Mechanic, Paper, Ticket, Witness, Marriage, Divorce");
		SendClientMessage(playerid, COLOR_WHITE, "|____________________________________________|");
		return 1;
	}
	if(strcmp(x_job,"sex",true) == 0) {SexOffer[playerid] = 999; SexPrice[playerid] = 0; }
	else if(strcmp(x_job,"drugs",true) == 0) { DrugOffer[playerid] = 999; DrugPrice[playerid] = 0; DrugGram[playerid] = 0; }
	else if(strcmp(x_job,"repair",true) == 0) {RepairOffer[playerid] = 999; RepairPrice[playerid] = 0; RepairCar[playerid] = 0; }
	else if(strcmp(x_job,"lawyer",true) == 0) { WantLawyer[playerid] = 0; CallLawyer[playerid] = 0; }
	else if(strcmp(x_job,"bodyguard",true) == 0) { GuardOffer[playerid] = 999; GuardPrice[playerid] = 0; }
	else if(strcmp(x_job,"live",true) == 0) { LiveOffer[playerid] = 999; }
	else if(strcmp(x_job,"refill",true) == 0) { RefillOffer[playerid] = 999; RefillPrice[playerid] = 0; }
	else if(strcmp(x_job,"car",true) == 0) { CarOffer[playerid] = 999; CarPrice[playerid] = 0; CarID[playerid] = 0; }
	else if(strcmp(x_job,"boxing",true) == 0) { BoxOffer[playerid] = 999; }
	else if(strcmp(x_job,"paper",true) == 0) { PaperOffer[playerid] = 999; }
	else if(strcmp(x_job,"witness",true) == 0) { MarryWitnessOffer[playerid] = 999; }
	else if(strcmp(x_job,"marriage",true) == 0) { ProposeOffer[playerid] = 999; }
	else if(strcmp(x_job,"divorce",true) == 0) { DivorceOffer[playerid] = 999; }
	else if(strcmp(x_job,"ticket",true) == 0) { TicketOffer[playerid] = 999; TicketMoney[playerid] = 0; }
	else if(strcmp(x_job,"medic",true) == 0) { if(IsPlayerConnected(MedicCall)) { if(MedicCall == playerid) { MedicCall = 999; } else { SendClientMessage(playerid, COLOR_GREY, "   You are not the current Caller !"); return 1; } } }
	else if(strcmp(x_job,"mechanic",true) == 0) { if(IsPlayerConnected(MechanicCall)) { if(MechanicCall == playerid) { MechanicCall = 999; } else { SendClientMessage(playerid, COLOR_GREY, "   You are not the current Caller !"); return 1; } } }
	else if(strcmp(x_job,"taxi",true) == 0)
	{
		if(TaxiCall < 999)
		{
			if(TransportDuty[playerid] == 1 && TaxiCallTime[playerid] > 0)
			{
				TaxiAccepted[playerid] = 999;
				GameTextForPlayer(playerid, "~w~You have~n~~r~Canceled the call", 5000, 1);
				TaxiCallTime[playerid] = 0;
				DisablePlayerCheckpoint(playerid);
				TaxiCall = 999;
			}
			else
			{
				if(IsPlayerConnected(TaxiCall)) { if(TaxiCall == playerid) { TaxiCall = 999; } }
				for(new i = 0; i < MAX_PLAYERS; i++)
				{
					if(IsPlayerConnected(i))
					{
						if(TaxiAccepted[i] < 999)
						{
							if(TaxiAccepted[i] == playerid)
							{
								TaxiAccepted[i] = 999;
								GameTextForPlayer(i, "~w~Taxi Caller~n~~r~Canceled the call", 5000, 1);
								TaxiCallTime[i] = 0;
								DisablePlayerCheckpoint(i);
							}
						}
					}
				}
			}
		}
	}
	else if(strcmp(x_job,"bus",true) == 0)
	{
		if(BusCall < 999)
		{
			if(TransportDuty[playerid] == 2 && BusCallTime[playerid] > 0)
			{
				BusAccepted[playerid] = 999;
				GameTextForPlayer(playerid, "~w~You have~n~~r~Canceled the call", 5000, 1);
				BusCallTime[playerid] = 0;
				DisablePlayerCheckpoint(playerid);
				BusCall = 999;
			}
			else
			{
				if(IsPlayerConnected(BusCall)) { if(BusCall == playerid) { BusCall = 999; } }
				for(new i = 0; i < MAX_PLAYERS; i++)
				{
					if(IsPlayerConnected(i))
					{
						if(BusAccepted[i] < 999)
						{
							if(BusAccepted[i] == playerid)
							{
								BusAccepted[i] = 999;
								GameTextForPlayer(i, "~w~Bus Caller~n~~r~Canceled the call", 5000, 1);
								BusCallTime[i] = 0;
								DisablePlayerCheckpoint(i);
							}
						}
					}
				}
			}
		}
	}
	else { return 1; }
	format(gString, sizeof(gString), "* You have canceled: %s.", x_job);
	SendClientMessage(playerid, COLOR_YELLOW, gString);
	return 1;
}

CMD:accept(playerid, params[]) {
	new x_job[256];
	if(!strlen(x_job)) {
		SendClientMessage(playerid, COLOR_WHITE, "|__________________ Accept __________________|");
		SendClientMessage(playerid, COLOR_WHITE, "Uzycie: accept [name]");
		SendClientMessage(playerid, COLOR_GREY, "Available names: Sex, Drugs, Repair, Lawyer, Bodyguard, Job, Live, Refill");
		SendClientMessage(playerid, COLOR_GREY, "Available names: Car, Taxi, Bus, Boxing, Medic, Mechanic, Paper, Ticket");
		SendClientMessage(playerid, COLOR_WHITE, "|____________________________________________|");
		return 1;
	}
	if(strcmp(x_job,"car",true) == 0)
	{
		if(CarOffer[playerid] < 999)
		{
			if(IsPlayerConnected(CarOffer[playerid]))
			{
				if(GetPlayerMoney(playerid) > CarPrice[playerid])
				{
					if(IsPlayerInVehicle(CarOffer[playerid], CarID[playerid]))
					{
						new points;
						PlayerInfo[CarOffer[playerid]][pCarSkill] ++;
						if(PlayerInfo[CarOffer[playerid]][pCarSkill] == 50)
						{ SendClientMessage(CarOffer[playerid], COLOR_YELLOW, "* Your Car Dealer Skill is now Level 2, Players that buy Cars from you can call it more often."); }
						else if(PlayerInfo[CarOffer[playerid]][pCarSkill] == 100)
						{ SendClientMessage(CarOffer[playerid], COLOR_YELLOW, "* Your Car Dealer Skill is now Level 3, Players that buy Cars from you can call it more often."); }
						else if(PlayerInfo[CarOffer[playerid]][pCarSkill] == 200)
						{ SendClientMessage(CarOffer[playerid], COLOR_YELLOW, "* Your Car Dealer Skill is now Level 4, Players that buy Cars from you can call it more often."); }
						else if(PlayerInfo[CarOffer[playerid]][pCarSkill] == 400)
						{ SendClientMessage(CarOffer[playerid], COLOR_YELLOW, "* Your Car Dealer Skill is now Level 5, Players that buy Cars from you can call it more often."); }
						new level = PlayerInfo[CarOffer[playerid]][pCarSkill];
						if(level >= 0 && level <= 50) { points = 1; }
						else if(level >= 51 && level <= 100) { points = 2; }
						else if(level >= 101 && level <= 200) { points = 3; }
						else if(level >= 201 && level <= 400) { points = 4; }
						else if(level >= 401) { points = 4; }
						format(gString, sizeof(gString), "* You bought a Car for $%d, from Car Dealer %s. (You can use /callcar %d times)",CarPrice[playerid],PlayerInfo[CarOffer[playerid]][pName],points);
						SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
						format(gString, sizeof(gString), "* You sold your Car to %s for $%d, the player can use /callcar %d times.",PlayerInfo[playerid][pName],CarPrice[playerid],points);
						SendClientMessage(CarOffer[playerid], COLOR_LIGHTBLUE, gString);
						PlayerInfo[CarOffer[playerid]][pPayCheck] += CarPrice[playerid];
						GivePlayerMoney(playerid, -CarPrice[playerid]);
						RemovePlayerFromVehicle(CarOffer[playerid]);
						CarCalls[playerid] = points;
						CarOffer[playerid] = 999;
						CarPrice[playerid] = 0;
						return 1;
					}
					else
					{
						SendClientMessage(playerid, COLOR_GREY, "   The Car Dealer is not in the offerd Car !");
						return 1;
					}
				}
				else
				{
					SendClientMessage(playerid, COLOR_GREY, "   You cant afford the Car !");
					return 1;
				}
			}
			return 1;
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   No-one offered to buy a Car !");
			return 1;
		}
	}
	else if(strcmp(x_job,"divorce",true) == 0)
	{
		if(DivorceOffer[playerid] < 999)
		{
			if(IsPlayerConnected(DivorceOffer[playerid]))
			{
				if(ProxDetectorS(10.0, playerid, DivorceOffer[playerid]))
				{
					format(gString, sizeof(gString), "* You have accepted %s's request to be his Marriage Witness.", PlayerInfo[DivorceOffer[playerid]][pName]);
					SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
					format(gString, sizeof(gString), "* %s has accepted your request to be your Marriage Witness.", PlayerInfo[playerid][pName]);
					SendClientMessage(DivorceOffer[playerid], COLOR_LIGHTBLUE, gString);
					ClearMarriage(playerid);
					ClearMarriage(DivorceOffer[playerid]);
					PlayerInfo[playerid][pPhousekey] = 255;
					PlayerInfo[playerid][pPbiskey] = 255;
					return 1;
				}
				else
				{
					SendClientMessage(playerid, COLOR_GREY, "   The player that sent you the Divorce Papers is not near you !");
					return 1;
				}
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   No-one sent you any Divorce Papers !");
			return 1;
		}
	}
	else if(strcmp(x_job,"witness",true) == 0)
	{
		if(MarryWitnessOffer[playerid] < 999)
		{
			if(IsPlayerConnected(MarryWitnessOffer[playerid]))
			{
				if(ProxDetectorS(10.0, playerid, MarryWitnessOffer[playerid]))
				{
					format(gString, sizeof(gString), "* You have accepted %s's request to be his Marriage Witness.", PlayerInfo[MarryWitnessOffer[playerid]][pName]);
					SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
					format(gString, sizeof(gString), "* %s has accepted your request to be your Marriage Witness.", PlayerInfo[playerid][pName]);
					SendClientMessage(MarryWitnessOffer[playerid], COLOR_LIGHTBLUE, gString);
					MarryWitness[MarryWitnessOffer[playerid]] = playerid;
					MarryWitnessOffer[playerid] = 999;
					return 1;
				}
				else
				{
					SendClientMessage(playerid, COLOR_GREY, "   The player that requested you to be his Marriage Witness is not near you !");
					return 1;
				}
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   No-one asked you to be his Marriage Witness !");
			return 1;
		}
	}
	else if(strcmp(x_job,"marriage",true) == 0)
	{
		if(ProposeOffer[playerid] < 999)
		{
			if(!PlayerToPoint(10.0, playerid, -1988.6638,1117.8837,54.4726))
			{
				SendClientMessage(playerid, COLOR_GREY, "   You are not at the Church in San Fierro !");
				return 1;
			}
			if(IsPlayerConnected(ProposeOffer[playerid]))
			{
				if(ProxDetectorS(10.0, playerid, ProposeOffer[playerid]))
				{
					if(MarryWitness[ProposeOffer[playerid]] == 999)
					{
						SendClientMessage(playerid, COLOR_GREY, "   The proposer doesn't have a Marriage Witness !");
						return 1;
					}
					if(IsPlayerConnected(MarryWitness[ProposeOffer[playerid]]))
					{
						if(ProxDetectorS(12.0, ProposeOffer[playerid], MarryWitness[ProposeOffer[playerid]]))
						{
							format(gString, sizeof(gString), "* You have accepted %s's request to be your Husband.", PlayerInfo[ProposeOffer[playerid]][pName]);
							SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
							format(gString, sizeof(gString), "* %s has accepted your request to be your Wife.", PlayerInfo[playerid][pName]);
							SendClientMessage(ProposeOffer[playerid], COLOR_LIGHTBLUE, gString);
							format(gString, sizeof(gString), "Priest: %s do you take %s as your lovely Husband? (type 'yes', anything else will reject the Marriage)", PlayerInfo[playerid][pName], PlayerInfo[ProposeOffer[playerid]][pName]);
							SendClientMessage(playerid, COLOR_WHITE, gString);
							MarriageCeremoney[playerid] = 1;
							ProposedTo[ProposeOffer[playerid]] = playerid;
							GotProposedBy[playerid] = ProposeOffer[playerid];
							MarryWitness[ProposeOffer[playerid]] = 999;
							ProposeOffer[playerid] = 999;
							return 1;
						}
						else
						{
							SendClientMessage(playerid, COLOR_GREY, "   The Marriage Witness is not near your proposer !");
							return 1;
						}
					}
					return 1;
				}
				else
				{
					SendClientMessage(playerid, COLOR_GREY, "   The player that proposed to you is not near you !");
					return 1;
				}
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   No-one Proposed to you !");
			return 1;
		}
	}
	else if(strcmp(x_job,"ticket",true) == 0)
	{
		if(TicketOffer[playerid] < 999)
		{
			if(IsPlayerConnected(TicketOffer[playerid]))
			{
				if (ProxDetectorS(5.0, playerid, TicketOffer[playerid]))
				{
					format(gString, sizeof(gString), "* You have paid the Ticket of $%d to Officer %s.", TicketMoney[playerid], PlayerInfo[TicketOffer[playerid]][pName]);
					SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
					format(gString, sizeof(gString), "* %s has paid your Ticket of $%d.", PlayerInfo[playerid][pName], TicketMoney[playerid]);
					SendClientMessage(TicketOffer[playerid], COLOR_LIGHTBLUE, gString);
					GivePlayerMoney(playerid, - TicketMoney[playerid]);
					GivePlayerMoney(TicketOffer[playerid], TicketMoney[playerid]);
					TicketOffer[playerid] = 999;
					TicketMoney[playerid] = 0;
					return 1;
				}
				else
				{
					SendClientMessage(playerid, COLOR_GREY, "   The Officer is not near you !");
					return 1;
				}
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   No-one offered you a Ticket !");
			return 1;
		}
	}
	else if(strcmp(x_job,"paper",true) == 0)
	{
		if(PaperOffer[playerid] < 999)
		{
			if(IsPlayerConnected(PaperOffer[playerid]))
			{
				if(BringingPaper[PaperOffer[playerid]] > 0)
				{
					if (ProxDetectorS(5.0, playerid, PaperOffer[playerid]))
					{
						format(gString, sizeof(gString), "* You have accepted a Newspaper from Paper Boy %s (use /read paper, to read).", PlayerInfo[PaperOffer[playerid]][pName]);
						SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
						format(gString, sizeof(gString), "* %s has accepted your Newspaper.", PlayerInfo[playerid][pName]);
						SendClientMessage(PaperOffer[playerid], COLOR_LIGHTBLUE, gString);
						format(gString, sizeof(gString), "%s", Paper[PaperOffer[playerid]][pTitle]);
						strmid(Paper[playerid][pTitle], gString, 0, strlen(gString), 255);
						format(gString, sizeof(gString), "%s", Paper[PaperOffer[playerid]][pMaker]);
						strmid(Paper[playerid][pMaker], gString, 0, strlen(gString), 255);
						format(gString, sizeof(gString), "%s", Paper[PaperOffer[playerid]][pLine1]);
						strmid(Paper[playerid][pLine1], gString, 0, strlen(gString), 255);
						format(gString, sizeof(gString), "%s", Paper[PaperOffer[playerid]][pLine2]);
						strmid(Paper[playerid][pLine2], gString, 0, strlen(gString), 255);
						format(gString, sizeof(gString), "%s", Paper[PaperOffer[playerid]][pLine3]);
						strmid(Paper[playerid][pLine3], gString, 0, strlen(gString), 255);
						format(gString, sizeof(gString), "%s", Paper[PaperOffer[playerid]][pLine4]);
						strmid(Paper[playerid][pLine4], gString, 0, strlen(gString), 255);
						format(gString, sizeof(gString), "%s", Paper[PaperOffer[playerid]][pLine5]);
						strmid(Paper[playerid][pLine5], gString, 0, strlen(gString), 255);
						format(gString, sizeof(gString), "%s", Paper[PaperOffer[playerid]][pLine6]);
						strmid(Paper[playerid][pLine6], gString, 0, strlen(gString), 255);
						format(gString, sizeof(gString), "%s", Paper[PaperOffer[playerid]][pLine7]);
						strmid(Paper[playerid][pLine7], gString, 0, strlen(gString), 255);
						GotPaper[playerid] = 1;
						PaperOffer[playerid] = 999;
						return 1;
					}
					else
					{
						SendClientMessage(playerid, COLOR_GREY, "   The Paper Boy is not near you !");
						return 1;
					}
				}
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   No-one offered you a Newspaper !");
			return 1;
		}
	}
	else if(strcmp(x_job,"boxing",true) == 0)
	{
		if(BoxOffer[playerid] < 999)
		{
			if(IsPlayerConnected(BoxOffer[playerid]))
			{
				new points;
				new mypoints;
				new level = PlayerInfo[BoxOffer[playerid]][pBoxSkill];
				if(level >= 0 && level <= 50) { points = 40; }
				else if(level >= 51 && level <= 100) { points = 50; }
				else if(level >= 101 && level <= 200) { points = 60; }
				else if(level >= 201 && level <= 400) { points = 70; }
				else if(level >= 401) { points = 80; }
				if(PlayerInfo[playerid][pJob] == 12)
				{
					new clevel = PlayerInfo[playerid][pBoxSkill];
					if(clevel >= 0 && clevel <= 50) { mypoints = 40; }
					else if(clevel >= 51 && clevel <= 100) { mypoints = 50; }
					else if(clevel >= 101 && clevel <= 200) { mypoints = 60; }
					else if(clevel >= 201 && clevel <= 400) { mypoints = 70; }
					else if(clevel >= 401) { mypoints = 80; }
				}
				else
				{
					mypoints = 30;
				}
				format(gString, sizeof(gString), "* You have accepted the Boxing Challenge from %s, and will fight with %d Health.",PlayerInfo[BoxOffer[playerid]][pName],mypoints);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
				format(gString, sizeof(gString), "* %s has accepted your Boxing Challenge Request, you will fight with %d Health.",PlayerInfo[playerid][pName],points);
				SendClientMessage(BoxOffer[playerid], COLOR_LIGHTBLUE, gString);
				SetPlayerHealth(playerid, mypoints);
				SetPlayerHealth(BoxOffer[playerid], points);
				SetPlayerInterior(playerid, 5); SetPlayerInterior(BoxOffer[playerid], 5);
				SetPlayerPos(playerid, 762.9852,2.4439,1001.5942); SetPlayerFacingAngle(playerid, 131.8632);
				SetPlayerPos(BoxOffer[playerid], 758.7064,-1.8038,1001.5942); SetPlayerFacingAngle(BoxOffer[playerid], 313.1165);
				TogglePlayerControllable(playerid, 0); TogglePlayerControllable(BoxOffer[playerid], 0);
				GameTextForPlayer(playerid, "~r~Waiting", 3000, 1); GameTextForPlayer(BoxOffer[playerid], "~r~Waiting", 3000, 1);
				new name[MAX_PLAYER_NAME];
				new dstring[MAX_PLAYER_NAME];
				new wstring[MAX_PLAYER_NAME];
				GetPlayerName(playerid, name, sizeof(name));
				format(dstring, sizeof(dstring), "%s", name);
				strmid(wstring, dstring, 0, strlen(dstring), 255);
				if(strcmp(Titel[TitelName] ,wstring, true ) == 0 )
				{
					format(gString, sizeof(gString), "Boxing News: Boxing Champion %s will fight VS %s, in 60 seconds (Grove Street Gym).",  PlayerInfo[playerid][pName], PlayerInfo[BoxOffer[playerid]][pName]);
					OOCOff(COLOR_WHITE,gString);
					TBoxer = playerid;
					BoxDelay = 60;
				}
				GetPlayerName(BoxOffer[playerid], name, sizeof(name));
				format(dstring, sizeof(dstring), "%s", name);
				strmid(wstring, dstring, 0, strlen(dstring), 255);
				if(strcmp(Titel[TitelName] ,wstring, true ) == 0 )
				{
					format(gString, sizeof(gString), "Boxing News: Boxing Champion %s will fight VS %s, in 60 seconds (Grove Street Gym).",  PlayerInfo[giveplayerid][pName], PlayerInfo[playerid][pName]);
					OOCOff(COLOR_WHITE,gString);
					TBoxer = BoxOffer[playerid];
					BoxDelay = 60;
				}
				BoxWaitTime[playerid] = 1; BoxWaitTime[BoxOffer[playerid]] = 1;
				if(BoxDelay < 1) { BoxDelay = 20; }
				InRing = 1;
				Boxer1 = BoxOffer[playerid];
				Boxer2 = playerid;
				PlayerBoxing[playerid] = 1;
				PlayerBoxing[BoxOffer[playerid]] = 1;
				BoxOffer[playerid] = 999;
				return 1;
			}
			return 1;
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   No-one offered you a Boxing Challenge !");
			return 1;
		}
	}
	else if(strcmp(x_job,"taxi",true) == 0)
	{
		if(TransportDuty[playerid] != 1)
		{
			SendClientMessage(playerid, COLOR_GREY, "   You are not a Taxi Driver !");
			return 1;
		}
		if(TaxiCallTime[playerid] > 0)
		{
			SendClientMessage(playerid, COLOR_GREY, "   You have already accepted a Taxi Call !");
			return 1;
		}
		if(PlayerOnMission[playerid] > 0)
		{
			SendClientMessage(playerid, COLOR_GREY, "   On a mission right now, can't use this command !");
			return 1;
		}
		if(TaxiCall < 999)
		{
			if(IsPlayerConnected(TaxiCall))
			{
				format(gString, sizeof(gString), "* You have accepted the Taxi Call from %s, you will see the marker untill you have reached it.",PlayerInfo[TaxiCall][pName]);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
				format(gString, sizeof(gString), "* Taxi Driver %s has accepted your Taxi Call please wait at your current Position.",PlayerInfo[playerid][pName]);
				SendClientMessage(TaxiCall, COLOR_LIGHTBLUE, gString);
				GameTextForPlayer(playerid, "~w~Taxi Caller~n~~r~Goto redmarker", 5000, 1);
				TaxiCallTime[playerid] = 1;
				TaxiAccepted[playerid] = TaxiCall;
				TaxiCall = 999;
				return 1;
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   No-one called for a Taxi yet !");
			return 1;
		}
	}
	else if(strcmp(x_job,"bus",true) == 0)
	{
		if(TransportDuty[playerid] != 2)
		{
			SendClientMessage(playerid, COLOR_GREY, "   You are not a Bus Driver !");
			return 1;
		}
		if(BusCallTime[playerid] > 0)
		{
			SendClientMessage(playerid, COLOR_GREY, "   You have already accepted a Bus Call !");
			return 1;
		}
		if(PlayerOnMission[playerid] > 0)
		{
			SendClientMessage(playerid, COLOR_GREY, "   On a mission right now, can't use this command !");
			return 1;
		}
		if(BusCall < 999)
		{
			if(IsPlayerConnected(BusCall))
			{
				format(gString, sizeof(gString), "* You have accepted the Bus Call from %s, you will see the marker untill you have reached it.",PlayerInfo[BusCall][pName]);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
				format(gString, sizeof(gString), "* Bus Driver %s has accepted your Bus Call please wait at your current Position.",PlayerInfo[playerid][pName]);
				SendClientMessage(BusCall, COLOR_LIGHTBLUE, gString);
				new Float:X,Float:Y,Float:Z;
				GetPlayerPos(BusCall, X, Y, Z);
				SetPlayerCheckpoint(playerid, X, Y, Z, 5);
				GameTextForPlayer(playerid, "~w~Bus Caller~n~~r~Goto redmarker", 5000, 1);
				BusCallTime[playerid] = 1;
				BusAccepted[playerid] = BusCall;
				BusCall = 999;
				return 1;
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   No-one called for a Bus yet !");
			return 1;
		}
	}
	else if(strcmp(x_job,"medic",true) == 0)
	{
		if(PlayerInfo[playerid][pMember] == 4 || PlayerInfo[playerid][pLeader] == 4)
		{
			if(MedicCallTime[playerid] > 0)
			{
				SendClientMessage(playerid, COLOR_GREY, "   You have already accepted a Medic Call !");
				return 1;
			}
			if(PlayerOnMission[playerid] > 0)
			{
				SendClientMessage(playerid, COLOR_GREY, "   On a mission right now, can't use this command !");
				return 1;
			}
			if(MedicCall < 999)
			{
				if(IsPlayerConnected(MedicCall))
				{
					format(gString, sizeof(gString), "* You have accepted the Medic Call from %s, you have 30 Seconds to get there.",PlayerInfo[MedicCall][pName]);
					SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
					SendClientMessage(playerid, COLOR_LIGHTBLUE, "* After the 30 Seconds the Red Marker will dissapear.");
					format(gString, sizeof(gString), "* Medic %s has accepted your Medic Call please wait at your current Position.",PlayerInfo[playerid][pName]);
					SendClientMessage(MedicCall, COLOR_LIGHTBLUE, gString);
					new Float:X,Float:Y,Float:Z;
					GetPlayerPos(MedicCall, X, Y, Z);
					SetPlayerCheckpoint(playerid, X, Y, Z, 5);
					GameTextForPlayer(playerid, "~w~Medic Caller~n~~r~Goto redmarker", 5000, 1);
					MedicCallTime[playerid] = 1;
					MedicCall = 999;
					return 1;
				}
			}
			else
			{
				SendClientMessage(playerid, COLOR_GREY, "   No-one called for a Medic yet !");
				return 1;
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   You are not a Medic !");
			return 1;
		}
	}
	else if(strcmp(x_job,"mechanic",true) == 0)
	{
		if(PlayerInfo[playerid][pJob] != 7)
		{
			SendClientMessage(playerid, COLOR_GREY, "   You are not a Car Mechanic !");
			return 1;
		}
		if(MechanicCallTime[playerid] > 0)
		{
			SendClientMessage(playerid, COLOR_GREY, "   You have already accepted a Mechanic Call !");
			return 1;
		}
		if(PlayerOnMission[playerid] > 0)
		{
			SendClientMessage(playerid, COLOR_GREY, "   On a mission right now, can't use this command !");
			return 1;
		}
		if(MechanicCall < 999)
		{
			if(IsPlayerConnected(MechanicCall))
			{
				format(gString, sizeof(gString), "* You have accepted the Mechanic Call from %s, you have 30 Seconds to get there.",PlayerInfo[MechanicCall][pName]);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, "* After the 30 Seconds the Red Marker will dissapear.");
				format(gString, sizeof(gString), "* Car Mechanic %s has accepted your Mechanic Call please wait at your current Position.",PlayerInfo[playerid][pName]);
				SendClientMessage(MechanicCall, COLOR_LIGHTBLUE, gString);
				new Float:X,Float:Y,Float:Z;
				GetPlayerPos(MechanicCall, X, Y, Z);
				SetPlayerCheckpoint(playerid, X, Y, Z, 5);
				GameTextForPlayer(playerid, "~w~Mechanic Caller~n~~r~Goto redmarker", 5000, 1);
				MechanicCallTime[playerid] = 1;
				MechanicCall = 999;
				return 1;
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   No-one called for a Car Mechanic yet !");
			return 1;
		}
	}
	else if(strcmp(x_job,"job",true) == 0)
	{
		if(GettingJob[playerid] > 0)
		{
			if(PlayerInfo[playerid][pMember] > 0 || PlayerInfo[playerid][pFMember] < 255)
			{
				if(GettingJob[playerid] == 2 || GettingJob[playerid] == 5 || GettingJob[playerid] == 10)
				{//Allow the 3 jobs for Family Members
				}
				else
				{
					SendClientMessage(playerid, COLOR_GREY, "   Cant get a Job, you are in a Family !");
					return 1;
				}
			}
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Now that you have confirmed you want the Job, you got a 5 hour Contract.");
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Congratulations with your new Job, type /help to see your new command.");
			PlayerInfo[playerid][pJob] = GettingJob[playerid];
			GettingJob[playerid] = 0;
			return 1;
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   You haven't even been at a Job place yet!");
			return 1;
		}
	}
	else if(strcmp(x_job,"refill",true) == 0)
	{
		if(RefillOffer[playerid] < 999)
		{
			if(IsPlayerConnected(RefillOffer[playerid]))
			{
				if(GetPlayerMoney(playerid) > RefillPrice[playerid])
				{
					new car = gLastCar[playerid];
					new fuel;
					PlayerInfo[RefillOffer[playerid]][pMechSkill] ++;
					if(PlayerInfo[RefillOffer[playerid]][pMechSkill] == 50)
					{ SendClientMessage(RefillOffer[playerid], COLOR_YELLOW, "* Your Car Mechanic Skill is now Level 2, you can add more Fuel to any Players Cars."); }
					else if(PlayerInfo[RefillOffer[playerid]][pMechSkill] == 100)
					{ SendClientMessage(RefillOffer[playerid], COLOR_YELLOW, "* Your Car Mechanic Skill is now Level 3, you can add more Fuel to any Players Cars."); }
					else if(PlayerInfo[RefillOffer[playerid]][pMechSkill] == 200)
					{ SendClientMessage(RefillOffer[playerid], COLOR_YELLOW, "* Your Car Mechanic Skill is now Level 4, you can add more Fuel to any Players Cars."); }
					else if(PlayerInfo[RefillOffer[playerid]][pMechSkill] == 400)
					{ SendClientMessage(RefillOffer[playerid], COLOR_YELLOW, "* Your Car Mechanic Skill is now Level 5, you can add more Fuel to any Players Cars."); }
					new level = PlayerInfo[RefillOffer[playerid]][pMechSkill];
					if(level >= 0 && level <= 50)
					{ fuel = 15; }
					else if(level >= 51 && level <= 100)
					{ fuel = 40; }
					else if(level >= 101 && level <= 200)
					{ fuel = 60; }
					else if(level >= 201 && level <= 400)
					{ fuel = 80; }
					else if(level >= 401)
					{ fuel = 100; }
					format(gString, sizeof(gString), "* You refilled your car with %d%, for $%d by Car Mechanic %s.",fuel,RefillPrice[playerid],PlayerInfo[RefillOffer[playerid]][pName]);
					SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
					format(gString, sizeof(gString), "* You refilled %s's car with %d%, the $%d has been added to your PayCheck.",PlayerInfo[playerid][pName],fuel,RefillPrice[playerid]);
					SendClientMessage(RefillOffer[playerid], COLOR_LIGHTBLUE, gString);
					PlayerInfo[RefillOffer[playerid]][pPayCheck] += RefillPrice[playerid];
					GivePlayerMoney(playerid, -RefillPrice[playerid]);
					if(Gas[car] < 110) { Gas[car] += fuel; }
					RefillOffer[playerid] = 999;
					RefillPrice[playerid] = 0;
					return 1;
				}
				else
				{
					SendClientMessage(playerid, COLOR_GREY, "   You cant afford the Refill !");
					return 1;
				}
			}
			return 1;
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   No-one offered to Refill your Car !");
			return 1;
		}
	}
	else if(strcmp(x_job,"live",true) == 0)
	{
		if(LiveOffer[playerid] < 999)
		{
			if(IsPlayerConnected(LiveOffer[playerid]))
			{
				if (ProxDetectorS(5.0, playerid, LiveOffer[playerid]))
				{
					SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You are frozen till the Live Conversation ends.");
					SendClientMessage(LiveOffer[playerid], COLOR_LIGHTBLUE, "* You are frozen till the Live Conversation ends (use /live again).");
					TogglePlayerControllable(playerid, 0);
					TogglePlayerControllable(LiveOffer[playerid], 0);
					TalkingLive[playerid] = LiveOffer[playerid];
					TalkingLive[LiveOffer[playerid]] = playerid;
					LiveOffer[playerid] = 999;
					return 1;
				}
				else
				{
					SendClientMessage(playerid, COLOR_GREY, "   You are to far away from the News Reporter !");
					return 1;
				}
			}
			return 1;
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   No-one gave you a Live Conversation offer !");
			return 1;
		}
	}
	else if(strcmp(x_job,"lawyer",true) == 0)
	{
		//if(!strlen(tmp))
		{
			SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /accept lawyer [playerid/PartOfName]");
			return 1;
		}
		new giveplayerid;
		if (gTeam[playerid] == 2)
		{
			if(IsPlayerConnected(giveplayerid))
			{
				if(giveplayerid != INVALID_PLAYER_ID)
				{
					if(PlayerInfo[giveplayerid][pJob] == 2)
					{
						format(gString, sizeof(gString), "* You allowed %s to free a Jailed Person.", PlayerInfo[giveplayerid][pName]);
						SendClientMessage(playerid, COLOR_LIGHTBLUE,gString);
						format(gString, sizeof(gString), "* Officer %s approved (allowed) you to free a Jailed Person. (use /free)", PlayerInfo[playerid][pName]);
						SendClientMessage(giveplayerid, COLOR_LIGHTBLUE,gString);
						ApprovedLawyer[giveplayerid] = 1;
						return 1;
					}
				}
			}
			return 1;
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "Invalid action! (You are no cop / Player aint a Lawyer / Bad ID)");
			return 1;
		}
	}
	else if(strcmp(x_job,"bodyguard",true) == 0)
	{
		if(GuardOffer[playerid] < 999)
		{
			if(GetPlayerMoney(playerid) > GuardPrice[playerid])
			{
				if(IsPlayerConnected(GuardOffer[playerid]))
				{
					format(gString, sizeof(gString), "* You accepted the Protection for $%d from Bodyguard %s.",GuardPrice[playerid],PlayerInfo[GuardOffer[playerid]][pName]);
					SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
					format(gString, sizeof(gString), "* %s accepted your Protection, and the $%d was added to your PayCheck.",PlayerInfo[playerid][pName],GuardPrice[playerid]);
					SendClientMessage(GuardOffer[playerid], COLOR_LIGHTBLUE, gString);
					PlayerInfo[GuardOffer[playerid]][pPayCheck] += GuardPrice[playerid];
					GivePlayerMoney(playerid, -GuardPrice[playerid]);
					GuardOffer[playerid] = 999;
					GuardPrice[playerid] = 0;
					return 1;
				}
				return 1;
			}
			else
			{
				SendClientMessage(playerid, COLOR_GREY, "   You can't afford the Protection !");
				return 1;
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   No-one offerd you any Protection !");
			return 1;
		}
	}
	else if(strcmp(x_job,"drugs",true) == 0)
	{
		if(DrugOffer[playerid] < 999)
		{
			if(GetPlayerMoney(playerid) > DrugPrice[playerid])
			{
				if(PlayerInfo[playerid][pDrugs] < 7)
				{
					if(IsPlayerConnected(DrugOffer[playerid]))
					{
						format(gString, sizeof(gString), "* You bought %d gram for $%d from Drug Dealer %s.",DrugGram[playerid],DrugPrice[playerid],PlayerInfo[DrugOffer[playerid]][pName]);
						SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
						format(gString, sizeof(gString), "* %s has bought your %d gram, the $%d was added to your PayCheck.",PlayerInfo[playerid][pName],DrugGram[playerid],DrugPrice[playerid]);
						SendClientMessage(DrugOffer[playerid], COLOR_LIGHTBLUE, gString);
						PlayerInfo[DrugOffer[playerid]][pPayCheck] += DrugPrice[playerid];
						PlayerInfo[DrugOffer[playerid]][pDrugsSkill] ++;
						GivePlayerMoney(playerid, -DrugPrice[playerid]);
						PlayerInfo[playerid][pDrugs] += DrugGram[playerid];
						PlayerInfo[DrugOffer[playerid]][pDrugs] -= DrugGram[playerid];
						if(PlayerInfo[DrugOffer[playerid]][pDrugsSkill] == 50)
						{ SendClientMessage(DrugOffer[playerid], COLOR_YELLOW, "* Your Drug Dealer Skill is now Level 2, you can buy more Grams and Cheaper."); }
						else if(PlayerInfo[DrugOffer[playerid]][pDrugsSkill] == 100)
						{ SendClientMessage(DrugOffer[playerid], COLOR_YELLOW, "* Your Drug Dealer Skill is now Level 3, you can buy more Grams and Cheaper."); }
						else if(PlayerInfo[DrugOffer[playerid]][pDrugsSkill] == 200)
						{ SendClientMessage(DrugOffer[playerid], COLOR_YELLOW, "* Your Drug Dealer Skill is now Level 4, you can buy more Grams and Cheaper."); }
						else if(PlayerInfo[DrugOffer[playerid]][pDrugsSkill] == 400)
						{ SendClientMessage(DrugOffer[playerid], COLOR_YELLOW, "* Your Drug Dealer Skill is now Level 5, you can buy more Grams and Cheaper."); }
						DrugOffer[playerid] = 999;
						DrugPrice[playerid] = 0;
						DrugGram[playerid] = 0;
						return 1;
					}
					return 1;
				}
				else
				{
					SendClientMessage(playerid, COLOR_GREY, "   You are fully loaded with Drugs, use them first !");
					return 1;
				}
			}
			else
			{
				SendClientMessage(playerid, COLOR_GREY, "   You can't afford those Drugs !");
				return 1;
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   No-one offerd you any Drugs !");
			return 1;
		}
	}
	else if(strcmp(x_job,"sex",true) == 0)
	{
		if(SexOffer[playerid] < 999)
		{
			if(GetPlayerMoney(playerid) > SexPrice[playerid])
			{
				if (IsPlayerConnected(SexOffer[playerid]))
				{
					new Car = GetPlayerVehicleID(playerid);
					if(IsPlayerInAnyVehicle(playerid) && IsPlayerInVehicle(SexOffer[playerid], Car))
					{
						format(gString, sizeof(gString), "* You had sex with Whore %s, for $%d.", PlayerInfo[SexOffer[playerid]][pName], SexPrice[playerid]);
						SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
						format(gString, sizeof(gString), "* %s had sex with you, the $%d was added to your PayCheck.", PlayerInfo[playerid][pName], SexPrice[playerid]);
						SendClientMessage(SexOffer[playerid], COLOR_LIGHTBLUE, gString);
						PlayerInfo[SexOffer[playerid]][pPayCheck] += SexPrice[playerid];
						GivePlayerMoney(playerid, -SexPrice[playerid]);
						PlayerInfo[SexOffer[playerid]][pSexSkill] ++;
						if(PlayerInfo[SexOffer[playerid]][pSexSkill] == 50)
						{ SendClientMessage(SexOffer[playerid], COLOR_YELLOW, "* Your Sex Skill is now Level 2, you offer better Sex (health) and less chance on STD."); }
						else if(PlayerInfo[SexOffer[playerid]][pSexSkill] == 100)
						{ SendClientMessage(SexOffer[playerid], COLOR_YELLOW, "* Your Sex Skill is now Level 3, you offer better Sex (health) and less chance on STD."); }
						else if(PlayerInfo[SexOffer[playerid]][pSexSkill] == 200)
						{ SendClientMessage(SexOffer[playerid], COLOR_YELLOW, "* Your Sex Skill is now Level 4, you offer better Sex (health) and less chance on STD."); }
						else if(PlayerInfo[SexOffer[playerid]][pSexSkill] == 400)
						{ SendClientMessage(SexOffer[playerid], COLOR_YELLOW, "* Your Sex Skill is now Level 5, you offer better Sex (health) and less chance on STD."); }
						if(STDPlayer[playerid] == 0)
						{
							if(Condom[playerid] < 1)
							{
								new Float:health;
								new level = PlayerInfo[SexOffer[playerid]][pSexSkill];
								if(level >= 0 && level <= 50)
								{
									if(GetPlayerHealth(playerid, health) < 150) {
									SetPlayerHealth(playerid, health + 30.0); }
									new rand = random(sizeof(STD1));
									STDPlayer[playerid] = STD1[rand];
									STDPlayer[SexOffer[playerid]] = STD1[rand];
									if(STD1[rand] == 0) { SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You got 30 Health + no STD while having Sex."); SendClientMessage(SexOffer[playerid], COLOR_LIGHTBLUE, "* You haven't got a STD while having Sex."); }
									else if(STD1[rand] == 1) { SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You got 30 Health + a Chlamydia because of the Sex."); SendClientMessage(SexOffer[playerid], COLOR_LIGHTBLUE, "* You got a Chlamydia because of the Sex."); }
									else if(STD1[rand] == 2) { SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You got 30 Health + a Gonorrhea because of the Sex."); SendClientMessage(SexOffer[playerid], COLOR_LIGHTBLUE, "* You got a Gonorrhea because of the Sex."); }
									else if(STD1[rand] == 3) { SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You got 30 Health + a Syphilis because of the Sex."); SendClientMessage(SexOffer[playerid], COLOR_LIGHTBLUE, "* You got a Syphilis because of the Sex."); }
								}
								else if(level >= 51 && level <= 100)
								{
									if(GetPlayerHealth(playerid, health) < 150) {
									SetPlayerHealth(playerid, health + 60.0); }
									new rand = random(sizeof(STD2));
									STDPlayer[playerid] = STD2[rand];
									STDPlayer[SexOffer[playerid]] = STD2[rand];
									if(STD2[rand] == 0) { SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You got 60 Health + no STD while having Sex."); SendClientMessage(SexOffer[playerid], COLOR_LIGHTBLUE, "* You haven't got a STD while having Sex."); }
									else if(STD2[rand] == 1) { SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You got 60 Health + a Chlamydia because of the Sex."); SendClientMessage(SexOffer[playerid], COLOR_LIGHTBLUE, "* You got a Chlamydia because of the Sex."); }
									else if(STD2[rand] == 2) { SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You got 60 Health + a Gonorrhea because of the Sex."); SendClientMessage(SexOffer[playerid], COLOR_LIGHTBLUE, "* You got a Gonorrhea because of the Sex."); }
									else if(STD2[rand] == 3) { SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You got 60 Health + a Syphilis because of the Sex."); SendClientMessage(SexOffer[playerid], COLOR_LIGHTBLUE, "* You got a Syphilis because of the Sex."); }
								}
								else if(level >= 101 && level <= 200)
								{
									if(GetPlayerHealth(playerid, health) < 150) {
									SetPlayerHealth(playerid, health + 90.0); }
									new rand = random(sizeof(STD3));
									STDPlayer[playerid] = STD3[rand];
									STDPlayer[SexOffer[playerid]] = STD3[rand];
									if(STD3[rand] == 0) { SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You got 90 Health + no STD while having Sex."); SendClientMessage(SexOffer[playerid], COLOR_LIGHTBLUE, "* You haven't got a STD while having Sex."); }
									else if(STD3[rand] == 1) { SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You got 90 Health + a Chlamydia because of the Sex."); SendClientMessage(SexOffer[playerid], COLOR_LIGHTBLUE, "* You got a Chlamydia because of the Sex."); }
									else if(STD3[rand] == 2) { SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You got 90 Health + a Gonorrhea because of the Sex."); SendClientMessage(SexOffer[playerid], COLOR_LIGHTBLUE, "* You got a Gonorrhea because of the Sex."); }
									else if(STD3[rand] == 3) { SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You got 90 Health + a Syphilis because of the Sex."); SendClientMessage(SexOffer[playerid], COLOR_LIGHTBLUE, "* You got a Syphilis because of the Sex."); }
								}
								else if(level >= 201 && level <= 400)
								{
									if(GetPlayerHealth(playerid, health) < 150) {
									SetPlayerHealth(playerid, health + 120.0); }
									new rand = random(sizeof(STD4));
									STDPlayer[playerid] = STD4[rand];
									STDPlayer[SexOffer[playerid]] = STD4[rand];
									if(STD4[rand] == 0) { SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You got 120 Health + no STD while having Sex."); SendClientMessage(SexOffer[playerid], COLOR_LIGHTBLUE, "* You haven't got a STD while having Sex."); }
									else if(STD4[rand] == 1) { SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You got 120 Health + a Chlamydia because of the Sex."); SendClientMessage(SexOffer[playerid], COLOR_LIGHTBLUE, "* You got a Chlamydia because of the Sex."); }
									else if(STD4[rand] == 2) { SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You got 120 Health + a Gonorrhea because of the Sex."); SendClientMessage(SexOffer[playerid], COLOR_LIGHTBLUE, "* You got a Gonorrhea because of the Sex."); }
									else if(STD4[rand] == 3) { SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You got 120 Health + a Syphilis because of the Sex."); SendClientMessage(SexOffer[playerid], COLOR_LIGHTBLUE, "* You got a Syphilis because of the Sex."); }
								}
								else if(level >= 401)
								{
									if(GetPlayerHealth(playerid, health) < 150) {
									SetPlayerHealth(playerid, health + 150.0); }
									SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Your Sex Skill Level is so high you gave high health and No STD.");
									SendClientMessage(SexOffer[playerid], COLOR_LIGHTBLUE, "* The Whore's Sex Skill Level is so high you got high health and No STD.");
								}
							}
							else
							{
								SendClientMessage(SexOffer[playerid], COLOR_LIGHTBLUE, "* The player used a Condom.");
								SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You used a Condom.");
								Condom[playerid] --;
							}
						}
						else
						{
							SendClientMessage(SexOffer[playerid], COLOR_LIGHTBLUE, "* That player was already infected with a STD, can't get another one.");
							return 1;
						}
						SexOffer[playerid] = 999;
						return 1;
					}
					else
					{
						SendClientMessage(playerid, COLOR_GREY, "   You or the Whore are not both in a Car !");
						return 1;
					}
				}//Connected or not
				return 1;
			}
			else
			{
				SendClientMessage(playerid, COLOR_GREY, "   You can't afford the Sex!");
				return 1;
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   You dont have any Sex offerd by a Whore !");
			return 1;
		}
	}
	else if(strcmp(x_job,"repair",true) == 0)
	{
		if(RepairOffer[playerid] < 999)
		{
			if(GetPlayerMoney(playerid) > RepairPrice[playerid])
			{
				if(IsPlayerInAnyVehicle(playerid))
				{
					if(IsPlayerConnected(RepairOffer[playerid]))
					{
						RepairCar[playerid] = GetPlayerVehicleID(playerid);
						SetVehicleHealth(RepairCar[playerid], 1000.0);
						format(gString, sizeof(gString), "* You repaired your car for $%d by Car Mechanic %s.",RepairPrice[playerid],PlayerInfo[RepairOffer[playerid]][pName]);
						SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
						format(gString, sizeof(gString), "* You fixed %s's car, the $%d has been added to your PayCheck.",PlayerInfo[playerid][pName],RepairPrice[playerid]);
						SendClientMessage(RepairOffer[playerid], COLOR_LIGHTBLUE, gString);
						PlayerInfo[RepairOffer[playerid]][pMechSkill] ++;
						if(PlayerInfo[RepairOffer[playerid]][pMechSkill] == 50)
						{ SendClientMessage(RepairOffer[playerid], COLOR_YELLOW, "* Your Car Mechanic Skill is now Level 2, you can add more Fuel to any Players Cars."); }
						else if(PlayerInfo[RepairOffer[playerid]][pMechSkill] == 100)
						{ SendClientMessage(RepairOffer[playerid], COLOR_YELLOW, "* Your Car Mechanic Skill is now Level 3, you can add more Fuel to any Players Cars."); }
						else if(PlayerInfo[RepairOffer[playerid]][pMechSkill] == 200)
						{ SendClientMessage(RepairOffer[playerid], COLOR_YELLOW, "* Your Car Mechanic Skill is now Level 4, you can add more Fuel to any Players Cars."); }
						else if(PlayerInfo[RepairOffer[playerid]][pMechSkill] == 400)
						{ SendClientMessage(RepairOffer[playerid], COLOR_YELLOW, "* Your Car Mechanic Skill is now Level 5, you can add more Fuel to any Players Cars."); }
						PlayerInfo[RepairOffer[playerid]][pPayCheck] += RepairPrice[playerid];
						GivePlayerMoney(playerid, -RepairPrice[playerid]);
						RepairOffer[playerid] = 999;
						RepairPrice[playerid] = 0;
						return 1;
					}
					return 1;
				}
				return 1;
			}
			else
			{
				SendClientMessage(playerid, COLOR_GREY, "   You can't afford the Repair !");
				return 1;
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   No-one offerd you to Repair your Car !");
			return 1;
		}
	}
	else { return 1; }
	return 1;
}

CMD:refill(playerid, params[]) {
	if(PlayerInfo[playerid][pJob] != 7)
	{
		SendClientMessage(playerid, COLOR_GREY, "   You are not a Car Mechanic!");
		return 1;
	}
	tmp = strtok(cmdtext, idx);
	if(!strlen(tmp))
	{
		SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /refill [playerid/PartOfName] [price]");
		return 1;
	}
	new playa;
	new money;
	playa = ReturnUser(tmp);
	tmp = strtok(cmdtext, idx);
	money = strval(tmp);
	if(money < 1 || money > 99999) { SendClientMessage(playerid, COLOR_GREY, "   Price not lower then 1, or above 99999!"); return 1; }
	if(IsPlayerConnected(playa))
	{
		if(playa != INVALID_PLAYER_ID)
		{
			if(ProxDetectorS(8.0, playerid, playa)&& IsPlayerInAnyVehicle(playa))
			{
				if(playa == playerid) { SendClientMessage(playerid, COLOR_GREY, "   Can't do that!"); return 1; }
				GetPlayerName(playa, PlayerInfo[giveplayerid][pName], sizeof(PlayerInfo[giveplayerid][pName]));
				GetPlayerName(playerid, PlayerInfo[playerid][pName], sizeof(PlayerInfo[playerid][pName]));
				format(gString, sizeof(gString), "* You offerd %s to refill his car for $%d .",PlayerInfo[giveplayerid][pName],money);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
				format(gString, sizeof(gString), "* Car Mechanic %s wants to refill your car for $%d, (type /accept refill) to accept.",PlayerInfo[playerid][pName],money);
				SendClientMessage(playa, COLOR_LIGHTBLUE, gString);
				RefillOffer[playa] = playerid;
				RefillPrice[playa] = money;
			}
			else
			{
				SendClientMessage(playerid, COLOR_GREY, "   That player is not near you / not in a car.");
			}
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   That player is offline.");
	}
	return 1;
}

CMD:repair(playerid, params[]) {
	if(PlayerInfo[playerid][pJob] != 7)
	{
		SendClientMessage(playerid, COLOR_GREY, "   You are not a Car Mechanic!");
		return 1;
	}
	tmp = strtok(cmdtext, idx);
	if(!strlen(tmp))
	{
		SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /repair [playerid/PartOfName] [price]");
		return 1;
	}
	new playa;
	new money;
	playa = ReturnUser(tmp);
	tmp = strtok(cmdtext, idx);
	money = strval(tmp);
	if(money < 1 || money > 99999) { SendClientMessage(playerid, COLOR_GREY, "   Price not lower then 1, or above 99999!"); return 1; }
	if(IsPlayerConnected(playa))
	{
		if(playa != INVALID_PLAYER_ID)
		{
			if(ProxDetectorS(8.0, playerid, playa)&& IsPlayerInAnyVehicle(playa))
			{
				if(playa == playerid) { SendClientMessage(playerid, COLOR_GREY, "   Can't do that!"); return 1; }
				GetPlayerName(playa, PlayerInfo[giveplayerid][pName], sizeof(PlayerInfo[giveplayerid][pName]));
				GetPlayerName(playerid, PlayerInfo[playerid][pName], sizeof(PlayerInfo[playerid][pName]));
				format(gString, sizeof(gString), "* You offerd %s to fix his car for $%d .",PlayerInfo[giveplayerid][pName],money);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
				format(gString, sizeof(gString), "* Car Mechanic %s wants to repair your car for $%d, (type /accept repair) to accept.",PlayerInfo[playerid][pName],money);
				SendClientMessage(playa, COLOR_LIGHTBLUE, gString);
				RepairOffer[playa] = playerid;
				RepairPrice[playa] = money;
			}
			else
			{
				SendClientMessage(playerid, COLOR_GREY, "   That player is not near you / not in a car.");
			}
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   That player is offline.");
	}
	return 1;
}

CMD:callcar(playerid, params[]) {
	if(CarCalls[playerid] > 0)
	{
		new Float:plocx,Float:plocy,Float:plocz;
		GetPlayerPos(playerid, plocx, plocy, plocz);
		SetVehiclePos(CarID[playerid],plocx,plocy+4, plocz);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Bought Car has arrived.");
		CarCalls[playerid] -= 1;
		format(gString, sizeof(gString), "* You can call your Bought Car for %d times more.", CarCalls[playerid]);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   Invalid action !");
	}
	return 1;
}

CMD:family(playerid, params[]) {
	if(PlayerInfo[playerid][pMuted] == 1)
	{
		SendClientMessage(playerid, TEAM_CYAN_COLOR, "You cannot speak, you have been silenced");
		return 1;
	}
	GetPlayerName(playerid, PlayerInfo[playerid][pName], sizeof(PlayerInfo[playerid][pName]));
	new length = strlen(cmdtext);
	while ((idx < length) && (cmdtext[idx] <= ' '))
	{
	idx++;
	}
	new offset = idx;
	new result[64];
	while ((idx < length) && ((idx - offset) < (sizeof(result) - 1)))
	{
	result[idx - offset] = cmdtext[idx];
	idx++;
	}
	result[idx - offset] = EOS;
	if(!strlen(result))
	{
		SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: (/f)amily [family chat]");
		return 1;
	}
	if (gTeam[playerid] >= 5 || PlayerInfo[playerid][pFMember] < 255)
	{
		new leader = PlayerInfo[playerid][pLeader];
		new member = PlayerInfo[playerid][pMember];
		if(member==5||member==6)
		{
			if(PlayerInfo[playerid][pRank] == 6) { format(gString, sizeof(gString), "** Godfather %s: %s. )) **", PlayerInfo[playerid][pName], result); }
			else if(PlayerInfo[playerid][pRank] == 5) { format(gString, sizeof(gString), "** Underboss %s: %s. )) **", PlayerInfo[playerid][pName], result); }
			else if(PlayerInfo[playerid][pRank] == 4) { format(gString, sizeof(gString), "** Capo %s: %s. ))  **", PlayerInfo[playerid][pName], result); }
			else if(PlayerInfo[playerid][pRank] == 3) { format(gString, sizeof(gString), "** Soldier %s: %s. ))  **", PlayerInfo[playerid][pName], result); }
			else if(PlayerInfo[playerid][pRank] == 2) { format(gString, sizeof(gString), "** Associate %s: %s. ))  **", PlayerInfo[playerid][pName], result); }
			else if(PlayerInfo[playerid][pRank] == 1) { format(gString, sizeof(gString), "** Outsider %s: %s. ))  **", PlayerInfo[playerid][pName], result); }
			else { format(gString, sizeof(gString), "** Outsider %s: %s. )) **", PlayerInfo[playerid][pName], result); }
			SendFamilyMessage(PlayerInfo[playerid][pMember], TEAM_AZTECAS_COLOR, gString);
		}
		else if(member==8)
		{
			if(PlayerInfo[playerid][pRank] == 6) { format(gString, sizeof(gString), "** Director %s: %s. )) **", PlayerInfo[playerid][pName], result); }
			else if(PlayerInfo[playerid][pRank] == 5) { format(gString, sizeof(gString), "** Vice-Director %s: %s. )) **", PlayerInfo[playerid][pName], result); }
			else if(PlayerInfo[playerid][pRank] == 4) { format(gString, sizeof(gString), "** Special Agent %s: %s. ))  **", PlayerInfo[playerid][pName], result); }
			else if(PlayerInfo[playerid][pRank] == 3) { format(gString, sizeof(gString), "** Agent %s: %s. ))  **", PlayerInfo[playerid][pName], result); }
			else if(PlayerInfo[playerid][pRank] == 2) { format(gString, sizeof(gString), "** Marksman %s: %s. ))  **", PlayerInfo[playerid][pName], result); }
			else if(PlayerInfo[playerid][pRank] == 1) { format(gString, sizeof(gString), "** Freelancer %s: %s. ))  **", PlayerInfo[playerid][pName], result); }
			else { format(gString, sizeof(gString), "** Freelancer %s: %s. )) **", PlayerInfo[playerid][pName], result); }
			SendFamilyMessage(PlayerInfo[playerid][pMember], TEAM_AZTECAS_COLOR, gString);
		}
		else if(member==9)
		{
			if(PlayerInfo[playerid][pRank] == 6) { format(gString, sizeof(gString), "** Network Producer %s: %s. )) **", PlayerInfo[playerid][pName], result); }
			else if(PlayerInfo[playerid][pRank] == 5) { format(gString, sizeof(gString), "** Network Editor %s: %s. )) **", PlayerInfo[playerid][pName], result); }
			else if(PlayerInfo[playerid][pRank] == 4) { format(gString, sizeof(gString), "** Network Anchor %s: %s. ))  **", PlayerInfo[playerid][pName], result); }
			else if(PlayerInfo[playerid][pRank] == 3) { format(gString, sizeof(gString), "** Local Editor %s: %s. ))  **", PlayerInfo[playerid][pName], result); }
			else if(PlayerInfo[playerid][pRank] == 2) { format(gString, sizeof(gString), "** Local Reporter %s: %s. ))  **", PlayerInfo[playerid][pName], result); }
			else if(PlayerInfo[playerid][pRank] == 1) { format(gString, sizeof(gString), "** Intern %s: %s. ))  **", PlayerInfo[playerid][pName], result); }
			else { format(gString, sizeof(gString), "** Intern %s: %s. )) **", PlayerInfo[playerid][pName], result); }
			SendFamilyMessage(PlayerInfo[playerid][pMember], TEAM_AZTECAS_COLOR, gString);
		}
		else if(member==10)
		{
			if(PlayerInfo[playerid][pRank] == 6) { format(gString, sizeof(gString), "** Taxi Company Owner %s: %s. )) **", PlayerInfo[playerid][pName], result); }
			else if(PlayerInfo[playerid][pRank] == 5) { format(gString, sizeof(gString), "** Shift Supervisor %s: %s. )) **", PlayerInfo[playerid][pName], result); }
			else if(PlayerInfo[playerid][pRank] == 4) { format(gString, sizeof(gString), "** Dispatcher %s: %s. ))  **", PlayerInfo[playerid][pName], result); }
			else if(PlayerInfo[playerid][pRank] == 3) { format(gString, sizeof(gString), "** Cabbie %s: %s. ))  **", PlayerInfo[playerid][pName], result); }
			else if(PlayerInfo[playerid][pRank] == 2) { format(gString, sizeof(gString), "** Taxi Rookie %s: %s. ))  **", PlayerInfo[playerid][pName], result); }
			else if(PlayerInfo[playerid][pRank] == 1) { format(gString, sizeof(gString), "** Trainee %s: %s. ))  **", PlayerInfo[playerid][pName], result); }
			else { format(gString, sizeof(gString), "** Trainee %s: %s. )) **", PlayerInfo[playerid][pName], result); }
			SendFamilyMessage(PlayerInfo[playerid][pMember], TEAM_AZTECAS_COLOR, gString);
		}
		else if(member==11)
		{
			if(PlayerInfo[playerid][pRank] == 6) { format(gString, sizeof(gString), "** Boss %s: %s. )) **", PlayerInfo[playerid][pName], result); }
			else if(PlayerInfo[playerid][pRank] == 5) { format(gString, sizeof(gString), "** Under Boss %s: %s. )) **", PlayerInfo[playerid][pName], result); }
			else if(PlayerInfo[playerid][pRank] == 4) { format(gString, sizeof(gString), "** Manager %s: %s. ))  **", PlayerInfo[playerid][pName], result); }
			else if(PlayerInfo[playerid][pRank] == 3) { format(gString, sizeof(gString), "** Senior Instructor %s: %s. ))  **", PlayerInfo[playerid][pName], result); }
			else if(PlayerInfo[playerid][pRank] == 2) { format(gString, sizeof(gString), "** Instructor %s: %s. ))  **", PlayerInfo[playerid][pName], result); }
			else if(PlayerInfo[playerid][pRank] == 1) { format(gString, sizeof(gString), "** Trainee %s: %s. ))  **", PlayerInfo[playerid][pName], result); }
			else { format(gString, sizeof(gString), "** Trainee %s: %s. )) **", PlayerInfo[playerid][pName], result); }
			SendFamilyMessage(PlayerInfo[playerid][pMember], TEAM_AZTECAS_COLOR, gString);
		}
		else if(leader==5||leader==6)
		{
			format(gString, sizeof(gString), "** Godfather %s: %s. )) **", PlayerInfo[playerid][pName], result);
			SendFamilyMessage(PlayerInfo[playerid][pLeader], TEAM_AZTECAS_COLOR, gString);
		}
		else if(leader==8)
		{
			format(gString, sizeof(gString), "** Director %s: %s. )) **", PlayerInfo[playerid][pName], result);
			SendFamilyMessage(PlayerInfo[playerid][pLeader], TEAM_AZTECAS_COLOR, gString);
		}
		else if(leader==9)
		{
			format(gString, sizeof(gString), "** Network Producer %s: %s. )) **", PlayerInfo[playerid][pName], result);
			SendFamilyMessage(PlayerInfo[playerid][pLeader], TEAM_AZTECAS_COLOR, gString);
		}
		else if(leader==10)
		{
			format(gString, sizeof(gString), "** Taxi Company Owner %s: %s. )) **", PlayerInfo[playerid][pName], result);
			SendFamilyMessage(PlayerInfo[playerid][pLeader], TEAM_AZTECAS_COLOR, gString);
		}
		else if(leader==11)
		{
			format(gString, sizeof(gString), "** Boss %s: %s. )) **", PlayerInfo[playerid][pName], result);
			SendFamilyMessage(PlayerInfo[playerid][pLeader], TEAM_AZTECAS_COLOR, gString);
		}
		else if(PlayerInfo[playerid][pFMember] < 255)
		{
			if(PlayerInfo[playerid][pRank] == 6) { format(gString, sizeof(gString), "** Godfather %s: %s. )) **", PlayerInfo[playerid][pName], result); }
			else if(PlayerInfo[playerid][pRank] == 5) { format(gString, sizeof(gString), "** Underboss %s: %s. )) **", PlayerInfo[playerid][pName], result); }
			else if(PlayerInfo[playerid][pRank] == 4) { format(gString, sizeof(gString), "** Capo %s: %s. ))  **", PlayerInfo[playerid][pName], result); }
			else if(PlayerInfo[playerid][pRank] == 3) { format(gString, sizeof(gString), "** Soldier %s: %s. ))  **", PlayerInfo[playerid][pName], result); }
			else if(PlayerInfo[playerid][pRank] == 2) { format(gString, sizeof(gString), "** Associate %s: %s. ))  **", PlayerInfo[playerid][pName], result); }
			else if(PlayerInfo[playerid][pRank] == 1) { format(gString, sizeof(gString), "** Outsider %s: %s. ))  **", PlayerInfo[playerid][pName], result); }
			else { format(gString, sizeof(gString), "** Outsider %s: %s. )) **", PlayerInfo[playerid][pName], result); }
			SendNewFamilyMessage(PlayerInfo[playerid][pFMember], TEAM_AZTECAS_COLOR, gString);
		}
		printf("%s", gString);
		return 1;
	}
	else
	{
		SendClientMessage(playerid, COLOR_GRAD2, "   you are not part of a Family!");
		return 1;
	}
	return 1;
}

alias:family("f")

CMD:news(playerid, params[]) {
	if(PlayerInfo[playerid][pMember] == 9 || PlayerInfo[playerid][pLeader] == 9)
	{
		new newcar = GetPlayerVehicleID(playerid);
		if(PlayerInfo[playerid][pMuted] == 1)
		{
			SendClientMessage(playerid, TEAM_CYAN_COLOR, "You cannot speak, you have been silenced");
			return 1;
		}
		if(newcar == 99 || newcar == 97 || newcar == 98)
		{
			GetPlayerName(playerid, PlayerInfo[playerid][pName], sizeof(PlayerInfo[playerid][pName]));
			new length = strlen(cmdtext);
			while ((idx < length) && (cmdtext[idx] <= ' '))
			{
			idx++;
			}
			new offset = idx;
			new result[64];
			while ((idx < length) && ((idx - offset) < (sizeof(result) - 1)))
			{
			result[idx - offset] = cmdtext[idx];
			idx++;
			}
			result[idx - offset] = EOS;
			if(!strlen(result))
			{
				SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /news [newstext]");
				return 1;
			}
			format(gString, sizeof(gString), "NR %s: %s", PlayerInfo[playerid][pName], result);
			OOCNews(COLOR_NEWS,gString);
			PlayerInfo[playerid][pNewsSkill] ++;
			if(PlayerInfo[playerid][pNewsSkill] == 50)
			{ SendClientMessage(playerid, COLOR_YELLOW, "* Your News Reporter Skill is now Level 2, soon you are able to Fly the News Chopper and talk Live."); }
			else if(PlayerInfo[playerid][pNewsSkill] == 100)
			{ SendClientMessage(playerid, COLOR_YELLOW, "* Your News Reporter Skill is now Level 3, soon you are able to Fly the News Chopper and talk Live."); }
			else if(PlayerInfo[playerid][pNewsSkill] == 200)
			{ SendClientMessage(playerid, COLOR_YELLOW, "* Your News Reporter Skill is now Level 4, you can fly the News Chopper now."); }
			else if(PlayerInfo[playerid][pNewsSkill] == 400)
			{ SendClientMessage(playerid, COLOR_YELLOW, "* Your News Reporter Skill is now Level 5, you can now talk Live with any person you want."); }
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   You are not in the News Van or Chopper !");
			return 1;
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   You are not a News Reporter !");
	}
	return 1;
}

CMD:live(playerid, params[]) {
	if(PlayerInfo[playerid][pMember] == 9 || PlayerInfo[playerid][pLeader] == 9)
	{
		if(TalkingLive[playerid] != 255)
		{
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Live Conversation ended.");
			SendClientMessage(TalkingLive[playerid], COLOR_LIGHTBLUE, "* Live Conversation ended.");
			TogglePlayerControllable(playerid, 1);
			TogglePlayerControllable(TalkingLive[playerid], 1);
			TalkingLive[TalkingLive[playerid]] = 255;
			TalkingLive[playerid] = 255;
			return 1;
		}
		if(PlayerInfo[playerid][pNewsSkill] < 400)
		{
			SendClientMessage(playerid, COLOR_GREY, "   Your News Reporter Skill is to low to talk Live with people !");
			return 1;
		}
		tmp = strtok(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, COLOR_GRAD1, "Uzycie: /live [playerid/PartOfName]");
			return 1;
		}
		//giveplayerid = strval(tmp);
		giveplayerid = ReturnUser(tmp);
		if (IsPlayerConnected(giveplayerid))
		{
			if(giveplayerid != INVALID_PLAYER_ID)
			{
				if (ProxDetectorS(5.0, playerid, giveplayerid))
				{
					if(giveplayerid == playerid) { SendClientMessage(playerid, COLOR_GREY, "You cannot Talk Live with yourself!"); return 1; }
					GetPlayerName(giveplayerid, PlayerInfo[giveplayerid][pName], sizeof(PlayerInfo[giveplayerid][pName]));
					GetPlayerName(playerid, PlayerInfo[playerid][pName], sizeof(PlayerInfo[playerid][pName]));
					format(gString, sizeof(gString), "* You offered %s to have a Live Conversation.", PlayerInfo[giveplayerid][pName]);
					SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
					format(gString, sizeof(gString), "* %s offered you to have a Live Conversation, type (/accept live) to accept.", PlayerInfo[playerid][pName]);
					SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
					LiveOffer[giveplayerid] = playerid;
				}
				else
				{
					SendClientMessage(playerid, COLOR_GREY, "   You are to far away from that player !");
					return 1;
				}
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   Invalid ID/Name !");
			return 1;
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   You are not a News Reporter !");
	}
	return 1;
}

CMD:selldrugs(playerid, params[]) {
	if(PlayerInfo[playerid][pJob] != 4)
	{
		SendClientMessage(playerid, COLOR_GREY, "   You are not a Drugs Dealer!");
		return 1;
	}
	tmp = strtok(cmdtext, idx);
	if(!strlen(tmp))
	{
		SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /selldrugs [playerid/PartOfName] [ammount] [price]");
		return 1;
	}
	new playa;
	new money;
	new needed;
	playa = ReturnUser(tmp);
	tmp = strtok(cmdtext, idx);
	if(!strlen(tmp)) { return 1; }
	needed = strval(tmp);
	if(needed < 1 || needed > 99) { SendClientMessage(playerid, COLOR_GREY, "   Grams not lower then 1, or above 99!"); return 1; }
	tmp = strtok(cmdtext, idx);
	if(!strlen(tmp)) { return 1; }
	money = strval(tmp);
	if(money < 1 || money > 99999) { SendClientMessage(playerid, COLOR_GREY, "   Price not lower then 1, or above 99999!"); return 1; }
	if(needed > PlayerInfo[playerid][pDrugs]) { SendClientMessage(playerid, COLOR_GREY, "   You dont have that much Drugs with you !"); return 1; }
	if(IsPlayerConnected(playa))
	{
		if(playa != INVALID_PLAYER_ID)
		{
			if (ProxDetectorS(8.0, playerid, playa))
			{
				if(playa == playerid)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Cant sell to yourself!");
					return 1;
				}
				GetPlayerName(playa, PlayerInfo[giveplayerid][pName], sizeof(PlayerInfo[giveplayerid][pName]));
				GetPlayerName(playerid, PlayerInfo[playerid][pName], sizeof(PlayerInfo[playerid][pName]));
				format(gString, sizeof(gString), "* You offerd %s to buy %d gram of drugs for $%d .", PlayerInfo[giveplayerid][pName], needed, money);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
				format(gString, sizeof(gString), "* Drug Dealer %s wants to sell you %d gram for $%d, (type /accept drugs) to buy.", PlayerInfo[playerid][pName], needed, money);
				SendClientMessage(playa, COLOR_LIGHTBLUE, gString);
				DrugOffer[playa] = playerid;
				DrugPrice[playa] = money;
				DrugGram[playa] = needed;
			}
			else
			{
				SendClientMessage(playerid, COLOR_GREY, "   That player is not near you !");
			}
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   That player is offline.");
	}
	return 1;
}

CMD:usedrugs(playerid, params[]) {
	   if(PlayerBoxing[playerid] > 0)
	{
		SendClientMessage(playerid, COLOR_GREY, "   Cant use Drugs while you are fighting !");
		return 1;
	}
	if(PlayerInfo[playerid][pDrugs] > 1)
	{
		PlayerStoned[playerid] += 1;
		if(PlayerStoned[playerid] >= 2) { GameTextForPlayer(playerid, "~w~You are~n~~p~Stoned", 4000, 1); }
		new Float:health;
		GetPlayerHealth(playerid, health);
		if(PlayerInfo[playerid][pDrugPerk] > 0)
		{
			new hp = 2 * PlayerInfo[playerid][pDrugPerk]; hp += 20;
			SetPlayerHealth(playerid, health + hp);
		}
		else
		{
			SetPlayerHealth(playerid, health + 20.0);
		}
		SendClientMessage(playerid, COLOR_GREY, "   2 Drug Grams used !");
		PlayerInfo[playerid][pDrugs] -= 2;
		if(STDPlayer[playerid]==1)
		{
			 STDPlayer[playerid] = 0;
			 SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You are no longer infected with a STD anymore because of the Drugs !");
		}
		else if(STDPlayer[playerid]==2)
		{
			 STDPlayer[playerid] = 1;
			 SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You lowered the STD to Chlamydia because of the Drugs !");
		}
		else if(STDPlayer[playerid]==3)
		{
			 STDPlayer[playerid] = 2;
			 SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You lowered the STD to Gonorrhea because of the Drugs !");
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   You dont have any Drug Grams left !");
	}
	return 1;
}

CMD:healme(playerid, params[]) {
	if (PlayerToPoint(3, playerid,1173.2563,-1323.3102,15.3943)||PlayerToPoint(3, playerid,2029.5945,-1404.6426,17.2512))
	{
		if(STDPlayer[playerid] > 0)
		{
			STDPlayer[playerid] = 0;
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You are no longer infected with a STD anymore because of the Hospital's help !");
			GivePlayerMoney(playerid, -1000);
			SendClientMessage(playerid, TEAM_CYAN_COLOR, "Doc: Your medical bill contained $1000,-. Have a nice day!");
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   You dont have a STD to heal !");
			return 1;
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   You are not at a Hospital !");
	}
	return 1;
}

CMD:eject(playerid, params[]) {
	new State;
	if(IsPlayerInAnyVehicle(playerid))
	{
		 State=GetPlayerState(playerid);
		if(State!=PLAYER_STATE_DRIVER)
		{
			SendClientMessage(playerid,COLOR_GREY,"   You can only eject people as the driver !");
			return 1;
		}
		tmp = strtok(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /eject [playerid/PartOfName]");
			return 1;
		}
		new playa;
		playa = ReturnUser(tmp);
		new test;
		test = GetPlayerVehicleID(playerid);
		if(IsPlayerConnected(playa))
		{
			if(playa != INVALID_PLAYER_ID)
			{
				if(playa == playerid) { SendClientMessage(playerid, COLOR_GREY, "You cannot Eject yourself!"); return 1; }
				if(IsPlayerInVehicle(playa,test))
				{
					new PName[MAX_PLAYER_NAME];
					GetPlayerName(playerid,PName,sizeof(PName));
					GetPlayerName(playa, PlayerInfo[giveplayerid][pName], sizeof(PlayerInfo[giveplayerid][pName]));
					format(gString, sizeof(gString), "* You have thrown %s out of the car!", PlayerInfo[giveplayerid][pName]);
					SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
					format(gString, sizeof(gString), "* You have been thrown out the car by %s !", PName);
					SendClientMessage(playa, COLOR_LIGHTBLUE, gString);
					RemovePlayerFromVehicle(playa);
				}
				else
				{
					SendClientMessage(playerid, COLOR_GREY, "   That player is not in your Car !");
					return 1;
				}
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, " Invalid ID/Name!");
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   You need to be in a Vehicle to use this !");
	}
	return 1;
}

CMD:sex(playerid, params[]) {
	if(PlayerInfo[playerid][pJob] == 3)
	{
		if(!IsPlayerInAnyVehicle(playerid))
		{
			SendClientMessage(playerid, COLOR_GREY, "   You can only have Sex in a Car !");
			return 1;
		}
		new Car = GetPlayerVehicleID(playerid);
		tmp = strtok(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, COLOR_GRAD1, "Uzycie: /sex [playerid/PartOfName] [price]");
			return 1;
		}
		//giveplayerid = strval(tmp);
		giveplayerid = ReturnUser(tmp);
		tmp = strtok(cmdtext, idx);
		new money;
		money = strval(tmp);
		if(money < 1 || money > 99999) { SendClientMessage(playerid, COLOR_GREY, "   Price not lower then 1, or above 99999!"); return 1; }
		if(IsPlayerConnected(giveplayerid))
		{
			if(giveplayerid != INVALID_PLAYER_ID)
			{
				if (ProxDetectorS(8.0, playerid, giveplayerid))
				{
					if(giveplayerid == playerid) { SendClientMessage(playerid, COLOR_GREY, "You cannot have Sex with yourself!"); return 1; }
					if(IsPlayerInAnyVehicle(playerid) && IsPlayerInVehicle(giveplayerid, Car))
					{
						GetPlayerName(giveplayerid, PlayerInfo[giveplayerid][pName], sizeof(PlayerInfo[giveplayerid][pName]));
						GetPlayerName(playerid, PlayerInfo[playerid][pName], sizeof(PlayerInfo[playerid][pName]));
						format(gString, sizeof(gString), "* You offerd %s to have Sex with you, for $%d.", PlayerInfo[giveplayerid][pName], money);
						SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
						format(gString, sizeof(gString), "* Whore %s has offerd you to have Sex with her, for $%d (type /accept sex) to accept.", PlayerInfo[playerid][pName], money);
						SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
						SexOffer[giveplayerid] = playerid;
						SexPrice[giveplayerid] = money;
					}
					else
					{
						SendClientMessage(playerid, COLOR_GREY, "   You or the other player must be in a Car together !");
						return 1;
					}
				}
				else
				{
					SendClientMessage(playerid, COLOR_GREY, "   That player is not near you !");
					return 1;
				}
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   That player is offline !");
			return 1;
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   You are not a Whore !");
	}
	return 1;
}

CMD:wanted(playerid, params[]) {
	if(gTeam[playerid] == 2 || IsACop(playerid))
	{
		new x;
		SendClientMessage(playerid, COLOR_GREEN, "Current Wanted Suspects:");
		for(new i=0; i < MAX_PLAYERS; i++) {
			if(IsPlayerConnected(i))
			{
				if(WantedLevel[i] > 1)
				{
					GetPlayerName(i, PlayerInfo[giveplayerid][pName], sizeof(PlayerInfo[giveplayerid][pName]));
					format(gString, sizeof(gString), "%s%s: %d", gString,PlayerInfo[giveplayerid][pName],WantedLevel[i]);
					x++;
					if(x > 3) {
						SendClientMessage(playerid, COLOR_YELLOW, gString);
						x = 0;
						format(gString, sizeof(gString), "");
					} else {
						format(gString, sizeof(gString), "%s, ", gString);
					}
				}
			}
		}
		if(x <= 3 && x > 0) {
			gString[strlen(gString)-2] = '.';
			SendClientMessage(playerid, COLOR_YELLOW, gString);
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   You're not a Cop / FBI / National Guard !");
	}
	return 1;
}

CMD:dropcar(playerid, params[]) {
	if(PlayerInfo[playerid][pJob] == 5)
	{
		if(PlayerOnMission[playerid] > 0)
		{
			SendClientMessage(playerid, COLOR_GREY, "   On a mission right now, can't use this command !");
			return 1;
		}
		if(PlayerInfo[playerid][pCarTime] == 0)
		{
			GameTextForPlayer(playerid, "~w~Car Selling ~n~~r~Drop the car at the Crane", 5000, 1);
			CP[playerid] = 1;
			SetPlayerCheckpoint(playerid, -1548.3618,123.6438,3.2966,8.0);
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   You already Dropped a car, wait till your reload time is over !");
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   You are not a Car Jacker !");
	}
	return 1;
}

CMD:quitjob(playerid, params[]) {
	if(PlayerInfo[playerid][pJob] > 0)
	{
		if(PlayerInfo[playerid][pDonateRank] > 0)
		{
			if(PlayerInfo[playerid][pContractTime] >= 2)
			{
				SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You already forfilled your 1 hour Contract, and quited your Job.");
				PlayerInfo[playerid][pJob] = 0;
				PlayerInfo[playerid][pChar] = 0;
				PlayerInfo[playerid][pContractTime] = 0;
			}
			else
			{
				new chours = 2 - PlayerInfo[playerid][pContractTime];
				format(gString, sizeof(gString), "* You still have %d hours left to forfill and end your Contract.", chours / 2);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
			}
		}
		else
		{
			if(PlayerInfo[playerid][pContractTime] >= 10)
			{
				SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You already forfilled your 5 hour Contract, and quited your Job.");
				PlayerInfo[playerid][pJob] = 0;
				PlayerInfo[playerid][pChar] = 0;
				PlayerInfo[playerid][pContractTime] = 0;
			}
			else
			{
				new chours = 10 - PlayerInfo[playerid][pContractTime];
				format(gString, sizeof(gString), "* You still have %d hours left to forfill and end your Contract.", chours / 2);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
			}
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   You don't even have a Job !");
	}
	return 1;
}

CMD:bail(playerid, params[]) {
	if(PlayerInfo[playerid][pJailed]==1)
	{
		if(JailPrice[playerid] > 0)
		{
			if(GetPlayerMoney(playerid) > JailPrice[playerid])
			{
				format(gString, sizeof(gString), "You bailed yourself out for: $%d", JailPrice[playerid]);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
				GivePlayerMoney(playerid, -JailPrice[playerid]);
				JailPrice[playerid] = 0;
				WantLawyer[playerid] = 0; CallLawyer[playerid] = 0;
				PlayerInfo[playerid][pJailTime] = 1;
			}
			else
			{
				SendClientMessage(playerid, COLOR_GRAD1, "   You can't afford the Bail Price !");
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_GRAD1, "   You don't have a Bail Price !");
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GRAD1, "   You are not in Jail !");
	}
	return 1;
}

CMD:clear(playerid, params[]) {
	new member = PlayerInfo[playerid][pMember];
	new leader = PlayerInfo[playerid][pLeader];
	new rank = PlayerInfo[playerid][pRank];
	 if(gTeam[playerid] == 2)
	{
		if (!PlayerToPoint(3.0, playerid, 253.9280,69.6094,1003.6406))
		{
			SendClientMessage(playerid, COLOR_GRAD2, "   You are to not inside the Police Station!");
			return 1;
		}
		tmp = strtok(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, COLOR_GRAD1, "Uzycie: /clear [playerid/PartOfName]");
			return 1;
		}
		giveplayerid = ReturnUser(tmp);
		if(IsPlayerConnected(giveplayerid))
		{
			if(giveplayerid != INVALID_PLAYER_ID)
			{
				if(giveplayerid == playerid) { SendClientMessage(playerid, COLOR_GREY, "You cannot Clear yourself!"); return 1; }
				GetPlayerName(giveplayerid, PlayerInfo[giveplayerid][pName], sizeof(PlayerInfo[giveplayerid][pName]));
				GetPlayerName(playerid, PlayerInfo[playerid][pName], sizeof(PlayerInfo[playerid][pName]));
				format(gString, sizeof(gString), "* You cleared the Records and Wanted Points of %s.", PlayerInfo[giveplayerid][pName]);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
				format(gString, sizeof(gString), "* Officer %s has cleared your Records and Wanted Points.", PlayerInfo[playerid][pName]);
				SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
				WantedPoints[giveplayerid] = 0;
				WantedLevel[giveplayerid] = 0;
				ClearCrime(giveplayerid);
				if(gTeam[giveplayerid]==4)
				{
					gTeam[giveplayerid] = 3;
					SetPlayerToTeamColor(giveplayerid);
				}
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   Invalid ID/Name!");
		}
	}
	else if(member == 5||member == 6||leader == 5||leader == 6)
	{
		tmp = strtok(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, COLOR_GRAD1, "Uzycie: /clear [playerid/PartOfName]");
			return 1;
		}
		giveplayerid = ReturnUser(tmp);
		if(IsPlayerConnected(giveplayerid))
		{
			if(giveplayerid != INVALID_PLAYER_ID)
			{
				if(giveplayerid == playerid) { SendClientMessage(playerid, COLOR_GREY, "You cannot Clear yourself!"); return 1; }
				if(rank < 4) { SendClientMessage(playerid, COLOR_GREY, "   You need Rank 4 to clear someone's Wanted Points + Records !"); return 1; }
				if(GetPlayerMoney(playerid) < 5000) { SendClientMessage(playerid, COLOR_GREY, "   You need $5000 to Clear your Family Member !"); return 1; }
				GetPlayerName(giveplayerid, PlayerInfo[giveplayerid][pName], sizeof(PlayerInfo[giveplayerid][pName]));
				GetPlayerName(playerid, PlayerInfo[playerid][pName], sizeof(PlayerInfo[playerid][pName]));
				if(member > 0)
				{
					if(PlayerInfo[giveplayerid][pMember] != member)
					{
						SendClientMessage(playerid, COLOR_GREY, "   That player is not in your Family !");
						return 1;
					}
					format(gString, sizeof(gString), "* You cleared the Records and Wanted Points of %s for $5000.", PlayerInfo[giveplayerid][pName]);
					SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
					format(gString, sizeof(gString), "* Family Member %s with Rank %d, has cleared your Records and Wanted Points.", PlayerInfo[playerid][pName], rank);
					SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
				}
				else if(leader > 0)
				{
					if(PlayerInfo[giveplayerid][pMember] != leader)
					{
						SendClientMessage(playerid, COLOR_GREY, "   That player is not in your Family !");
						return 1;
					}
					format(gString, sizeof(gString), "* You cleared the Records and Wanted Points of %s for $5000.", PlayerInfo[giveplayerid][pName]);
					SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
					format(gString, sizeof(gString), "* Family Leader %s, has cleared your Records and Wanted Points.", PlayerInfo[playerid][pName]);
					SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
				}
				WantedPoints[giveplayerid] = 0;
				WantedLevel[giveplayerid] = 0;
				ClearCrime(giveplayerid);
				GivePlayerMoney(playerid, - 5000);
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   Invalid ID/Name!");
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   You are not an Cop / FBI / National Guard / Family Member !");
	}
	return 1;
}

CMD:ticket(playerid, params[]) {
	if(gTeam[playerid] != 2)
	{
		SendClientMessage(playerid, COLOR_GREY, "   You are not a Cop!");
		return 1;
	}
	if(OnDuty[playerid] != 1 && PlayerInfo[playerid][pMember] == 1)
	{
		SendClientMessage(playerid, COLOR_GREY, "   You are not on Duty!");
		return 1;
	}
	tmp = strtok(cmdtext, idx);
	if(!strlen(tmp))
	{
		SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /ticket [playerid/PartOfName] [price] [reason]");
		return 1;
	}
	giveplayerid = ReturnUser(tmp);
	tmp = strtok(cmdtext, idx);
	if(!strlen(tmp))
	{
		SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /ticket [playerid/PartOfName] [price] [reason]");
		return 1;
	}
	moneys = strval(tmp);
	if(moneys < 1 || moneys > 99999) { SendClientMessage(playerid, COLOR_GREY, "   Ticket Money can't be below 1 or higher then 99999 !"); return 1; }
	if(IsPlayerConnected(giveplayerid))
	{
		if(giveplayerid != INVALID_PLAYER_ID)
		{
			if (ProxDetectorS(8.0, playerid, giveplayerid))
			{
				GetPlayerName(giveplayerid, PlayerInfo[giveplayerid][pName], sizeof(PlayerInfo[giveplayerid][pName]));
				GetPlayerName(playerid, PlayerInfo[playerid][pName], sizeof(PlayerInfo[playerid][pName]));
				new length = strlen(cmdtext);
				while ((idx < length) && (cmdtext[idx] <= ' '))
				{
				idx++;
				}
				new offset = idx;
				new result[64];
				while ((idx < length) && ((idx - offset) < (sizeof(result) - 1)))
				{
				result[idx - offset] = cmdtext[idx];
				idx++;
				}
				result[idx - offset] = EOS;
				if(!strlen(result))
				{
					SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /ticket [playerid/PartOfName] [price] [reason]");
					return 1;
				}
				format(gString, sizeof(gString), "* You gave %s a Ticket costing $%d, reason: %s", PlayerInfo[giveplayerid][pName], moneys, (result));
				SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
				format(gString, sizeof(gString), "* Officer %s has given you a Ticket costing $%d, reason: %s", PlayerInfo[playerid][pName], moneys, (result));
				SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, gString);
				SendClientMessage(giveplayerid, COLOR_LIGHTBLUE, "* Type /accept ticket, to accept it.");
				TicketOffer[giveplayerid] = playerid;
				TicketMoney[giveplayerid] = moneys;
				return 1;
			}
			else
			{
				SendClientMessage(playerid, COLOR_GREY, "   That player is not near you !");
				return 1;
			}
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   That player is Offline !");
		return 1;
	}
	return 1;
}

CMD:arrest(playerid, params[]) {
	if(gTeam[playerid] == 2  || IsACop(playerid))
	{
		if(OnDuty[playerid] != 1 && PlayerInfo[playerid][pMember] == 1)
		{
			SendClientMessage(playerid, COLOR_GREY, "   You are not on Duty!");
			return 1;
		}
		if(!PlayerToPoint(6.0, playerid, 268.3327,77.8972,1001.0391))
		{// Jail spot
			SendClientMessage(playerid, COLOR_GREY, "   You are not near the Jail, can't Arrest !");
			return 1;
		}
		tmp = strtok(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /arrest [price] [time (minutes)] [bail (0=no 1=yes)] [bailprice]");
			return 1;
		}
		moneys = strval(tmp);
		if(moneys < 1 || moneys > 99999) { SendClientMessage(playerid, COLOR_GREY, "   Jail Price can't be below $1 or above $99999 !"); return 1; }
		tmp = strtok(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /arrest [price] [time (minutes)] [bail (0=no 1=yes)] [bailprice]");
			return 1;
		}
		new time = strval(tmp);
		if(time < 1 || time > 20) { SendClientMessage(playerid, COLOR_GREY, "   Jail Time Minutes can't be below 1 or above 20 (Take the person to prison then) !"); return 1; }
		tmp = strtok(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /arrest [price] [time (minutes)] [bail (0=no 1=yes)] [bailprice]");
			return 1;
		}
		new bail = strval(tmp);
		if(bail < 0 || bail > 1) { SendClientMessage(playerid, COLOR_GREY, "   Jail Bailing can't be below 0 or above 1 !"); return 1; }
		tmp = strtok(cmdtext, idx);
		if(!strlen(tmp))
		{
			SendClientMessage(playerid, COLOR_GRAD2, "Uzycie: /arrest [price] [time (minutes)] [bail (0=no 1=yes)] [bailprice]");
			return 1;
		}
		new bailprice = strval(tmp);
		if(bailprice < 0 || bailprice > 3000000) { SendClientMessage(playerid, COLOR_GREY, "   Jail Bailing can't be below $0 or above $3000000 !"); return 1; }
		new suspect = GetClosestPlayer(playerid);
		if(IsPlayerConnected(suspect))
		{
			if(GetDistanceBetweenPlayers(playerid,suspect) < 5)
			{
				GetPlayerName(suspect, PlayerInfo[giveplayerid][pName], sizeof(PlayerInfo[giveplayerid][pName]));
				GetPlayerName(playerid, PlayerInfo[playerid][pName], sizeof(PlayerInfo[playerid][pName]));
				if(WantedLevel[suspect] < 1)
				{
					SendClientMessage(playerid, COLOR_GREY, "   Player must be at least Wanted Level 1 !");
					return 1;
				}
				format(gString, sizeof(gString), "* You arrested %s !", PlayerInfo[giveplayerid][pName]);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
				GivePlayerMoney(suspect, -moneys);
				format(gString, sizeof(gString), "arrested by %s ~n~for $%d", PlayerInfo[playerid][pName], moneys);
				GameTextForPlayer(suspect, gString, 5000, 5);
				ResetPlayerWeapons(suspect);
				if(PlayerInfo[playerid][pMember]==1||PlayerInfo[playerid][pLeader]==1)
				{
					format(gString, sizeof(gString), "<< Officer %s arrested suspect %s >>", PlayerInfo[playerid][pName], PlayerInfo[giveplayerid][pName]);
					OOCNews(COLOR_LIGHTRED, gString);
				}
				else if(PlayerInfo[playerid][pMember]==2||PlayerInfo[playerid][pLeader]==2)
				{
					format(gString, sizeof(gString), "<< FBI Agent %s arrested suspect %s >>", PlayerInfo[playerid][pName], PlayerInfo[giveplayerid][pName]);
					OOCNews(COLOR_LIGHTRED, gString);
				}
				else if(PlayerInfo[playerid][pMember]==3||PlayerInfo[playerid][pLeader]==3)
				{
					format(gString, sizeof(gString), "<< Soldier %s arrested suspect %s >>", PlayerInfo[playerid][pName], PlayerInfo[giveplayerid][pName]);
					OOCNews(COLOR_LIGHTRED, gString);
				}
				SetPlayerInterior(suspect, 6);
				SetPlayerPos(suspect,264.6288,77.5742,1001.0391);
				PlayerInfo[suspect][pJailTime] = time * 60;
				if(bail == 1)
				{
					JailPrice[suspect] = bailprice;
					format(gString, sizeof(gString), "You are jailed for %d seconds.   Bail: $%d", PlayerInfo[suspect][pJailTime], JailPrice[suspect]);
					SendClientMessage(suspect, COLOR_LIGHTBLUE, gString);
				}
				else
				{
					JailPrice[suspect] = 0;
					format(gString, sizeof(gString), "You are jailed for %d seconds.   Bail: Unable", PlayerInfo[suspect][pJailTime]);
					SendClientMessage(suspect, COLOR_LIGHTBLUE, gString);
				}
				PlayerInfo[suspect][pJailed] = 1;
				PlayerInfo[suspect][pArrested] += 1;
				SetPlayerFree(suspect,playerid, "Got Arrested");
				WantedPoints[suspect] = 0;
				WantedLevel[suspect] = 0;
				WantLawyer[suspect] = 1;
			}//distance
		}//not connected
		else
		{
			SendClientMessage(playerid, COLOR_GREY, "   No-one close enough to arrest.");
			return 1;
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_GREY, "   You are not a Cop / FBI / National Guard !");
		return 1;
	}
	return 1;
}

CMD:contract(playerid, params[]) {
	tmp = strtok(cmdtext, idx);
	if(!strlen(tmp))
	{
		SendClientMessage(playerid, COLOR_GRAD1, "Uzycie: /contract [playerid/PartOfName] [amount]");
		return 1;
	}
	giveplayerid = ReturnUser(tmp);
	tmp = strtok(cmdtext, idx);
	if(!strlen(tmp))
	{
		SendClientMessage(playerid, COLOR_GRAD1, "Uzycie: /contract [playerid/PartOfName] [amount]");
		return 1;
	}
	moneys = strval(tmp);
	if(moneys < 10000 || moneys > 100000) { SendClientMessage(playerid, COLOR_GREY, "   Contract money must be atleast $10000, and not more then $100000!"); return 1; }
	if(PlayerInfo[playerid][pLevel] < 3)
	{
		SendClientMessage(playerid, COLOR_GRAD1, "You must be level 3 to place a Contract.");
		return 1;
	}
	if (IsPlayerConnected(giveplayerid))
	{
		if(giveplayerid != INVALID_PLAYER_ID)
		{
			if(PlayerInfo[giveplayerid][pMember] == 8 && PlayerInfo[playerid][pMember] == 8)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Cannot place Contracts on your own Agency!");
				return 1;
			}
			else if(PlayerInfo[giveplayerid][pLeader] == 8 && PlayerInfo[playerid][pMember] == 8)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Cannot place Contracts on your own Agency!");
				return 1;
			}
			else if(PlayerInfo[giveplayerid][pMember] == 8||PlayerInfo[giveplayerid][pLeader] == 8)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Can't contract a Hitman !");
				return 1;
			}
			if(gTeam[giveplayerid] == 2 && moneys != 100000)
			{
				SendClientMessage(playerid, COLOR_GREY, "   Only $100000 can be placed as a Contract on Cops !");
				return 1;
			}
			if(giveplayerid == playerid) { SendClientMessage(playerid, COLOR_GREY, "You cannot Contract yourself!"); return 1; }
			GetPlayerName(giveplayerid, PlayerInfo[giveplayerid][pName], sizeof(PlayerInfo[giveplayerid][pName]));
			GetPlayerName(playerid, PlayerInfo[playerid][pName], sizeof(PlayerInfo[playerid][pName]));
			playermoney = GetPlayerMoney(playerid);
			if (moneys > 0 && playermoney >= moneys)
			{
				GivePlayerMoney(playerid, (0 - moneys));
				PlayerInfo[giveplayerid][pHeadValue]+=moneys;
				format(gString, sizeof(gString), "%s has placed a contract on %s, for $%d.",PlayerInfo[playerid][pName], PlayerInfo[giveplayerid][pName], moneys);
				SendFamilyMessage(8, COLOR_YELLOW, gString);
				format(gString, sizeof(gString), "* You placed a contract on %s, for $%d.",PlayerInfo[giveplayerid][pName], moneys);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, gString);
				PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
			}
			else
			{
				SendClientMessage(playerid, COLOR_GRAD1, "   Invalid transaction amount.");
			}
		}
	}
	else
	{
		format(gString, sizeof(gString), "   %d is not an active player.", giveplayerid);
		SendClientMessage(playerid, COLOR_GRAD1, gString);
	}
	return 1;
}