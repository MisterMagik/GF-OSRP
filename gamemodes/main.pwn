/*
	Project: Old School Role Play
	Author: MisterMagik, steeZ
	File name: main.pwn
	Date: 12.03.2026
	Modified: 12.03.2026
	Desc: Thx for this code.
*/

// Rozmiar stosu:
#define DYNAMIC_MEMORY 131072
//
#define FOREACH_NO_VEHICLES
//
#include <a_samp>
#include <Pawn.CMD>
#include <streamer>
#include <sscanf2>
#include <YSI_Data\y_iterate>
#include <mysql>
#include <YSI\y_timers>
#include <progress>

#include "src\defines"
#include "src\enums"
#include "src\variables"
#include "src\systems\atm"
#include "src\systems\casual_jobs"
#include "src\systems\plant"
#include "src\systems\item"
#include "src\systems\vehicle"
#include "src\textdraws"
#include "src\objects"
#include "src\callbacks"
#include "src\dialogs"
#include "src\commands\player"
#include "src\funcs"
#include "src\timers"

main() {
	new callSecs = gettime();

	printf(" ");
	printf(" ");
	printf(" The Godfather: LS/SF");
	printf("_____________________");
	printf(" By: Fear & parts of Astro & steeZ & MisterMagik");
	printf(" ");

	printf("[MAIN] main (%0.1d sec)", gettime() - callSecs);
}
