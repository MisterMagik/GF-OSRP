/*
	Project: GodFather
	Author: MisterMagik, steeZ
	File name: textdraws.inc
	Date: 12.03.2026
	Modified: 12.03.2026
	Desc: Server tds.
*/

stock TextDrawsInit() {
	SplashScreen = TextDrawCreate(641.531494, 1.500000, "_");
	TextDrawLetterSize(SplashScreen, 0.000000, 49.396297);
	TextDrawTextSize(SplashScreen, -2.000000, 0.000000);
	TextDrawAlignment(SplashScreen, 1);
	TextDrawColor(SplashScreen, 0);
	TextDrawUseBox(SplashScreen, 1);
	TextDrawBoxColor(SplashScreen, 255);
	TextDrawSetShadow(SplashScreen, 0);
	TextDrawSetOutline(SplashScreen, 0);
	TextDrawFont(SplashScreen, 0);

	Intro[0] = TextDrawCreate(641.531494, 1.500000, "_");
	TextDrawLetterSize(Intro[0], 0.000000, 12.646296);
	TextDrawTextSize(Intro[0], -2.000000, 0.000000);
	TextDrawAlignment(Intro[0], 1);
	TextDrawColor(Intro[0], 0);
	TextDrawUseBox(Intro[0], 1);
	TextDrawBoxColor(Intro[0], 255);
	TextDrawSetShadow(Intro[0], 0);
	TextDrawSetOutline(Intro[0], 0);
	TextDrawFont(Intro[0], 0);

	Intro[1] = TextDrawCreate(641.531494, 331.083312, "_");
	TextDrawLetterSize(Intro[1], 0.000000, 12.775930);
	TextDrawTextSize(Intro[1], -2.000000, 0.000000);
	TextDrawAlignment(Intro[1], 1);
	TextDrawColor(Intro[1], 0);
	TextDrawUseBox(Intro[1], 1);
	TextDrawBoxColor(Intro[1], 255);
	TextDrawSetShadow(Intro[1], 0);
	TextDrawSetOutline(Intro[1], 0);
	TextDrawFont(Intro[1], 0);

	Intro[2] = TextDrawCreate(322.429168, 390.250213, "OLD SCHOOL ROLE PLAY");
	TextDrawLetterSize(Intro[2], 0.369414, 1.465832);
	TextDrawAlignment(Intro[2], 2);
	TextDrawColor(Intro[2], -1);
	TextDrawSetShadow(Intro[2], 0);
	TextDrawSetOutline(Intro[2], 1);
	TextDrawBackgroundColor(Intro[2], 51);
	TextDrawFont(Intro[2], 2);
	TextDrawSetProportional(Intro[2], 1);

	Intro[3] = TextDrawCreate(321.495513, 419.999969, "WWW.OSRP.PL");
	TextDrawLetterSize(Intro[3], 0.219019, 1.028332);
	TextDrawAlignment(Intro[3], 2);
	TextDrawColor(Intro[3], -1);
	TextDrawSetShadow(Intro[3], 0);
	TextDrawSetOutline(Intro[3], 1);
	TextDrawBackgroundColor(Intro[3], 51);
	TextDrawFont(Intro[3], 2);
	TextDrawSetProportional(Intro[3], 1);
}
