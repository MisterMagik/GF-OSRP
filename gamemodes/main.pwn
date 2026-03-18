/*
	Project: GodFather
	Author: MisterMagik, steeZ
	File name: main.pwn
	Date: 12.03.2026
	Modified: 12.03.2026
	Desc: Thx for this code.
*/

#include <a_samp>
#include <Pawn.CMD>
#include <streamer>
#include <sscanf2>
#include <foreach>
#include <mysql>

#include "src/defines"
#include "src/dialogs"
#include "src/enums"
#include "src/variables"
#include "src/callbacks"
#include "src/funcs"

main() {
	new callSecs = gettime();

	printf(" ");
	printf(" ");
	printf(" The Godfather: LS/SF");
	printf("_____________________");
	printf(" By: Fear & parts of Astro & steeZ & MisterMagik");
	printf(" ");

	printf("[MAIN] Funkcja main zaladowana w %0.1d sek.", gettime() - callSecs);
}
