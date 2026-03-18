/*
	Project: GodFather
	Author: MisterMagik, steeZ
	File name: enums.inc
	Date: 12.03.2026
	Modified: 12.03.2026
	Desc: Server enums.
*/

enum SavePlayerPosEnum
{
    Float:LastX,
    Float:LastY,
    Float:LastZ
};

enum pBoxingStats
{
    TitelName[128],
    TitelWins,
    TitelLoses,
};

enum cCKInfo
{
	cSendername[20],
	cGiveplayer[20],
	cUsed,
};

enum pPaperInfo
{
	PaperUsed,
	PaperMaker[20],
	PaperTitle[64],
	PaperText1[128],
	PaperText2[128],
	PaperText3[128],
	PaperText4[128],
	PaperText5[128],
	PaperText6[128],
	PaperText7[128],
	SafeSaving,
};

enum pPaper
{
	pMaker[20],
	pTitle[64],
	pLine1[128],
	pLine2[128],
	pLine3[128],
	pLine4[128],
	pLine5[128],
	pLine6[128],
	pLine7[128],
};

enum fInfo
{
	FamilyTaken,
	FamilyName[20],
	FamilyMOTD[128],
	FamilyColor[20],
	FamilyLeader[MAX_PLAYER_NAME],
	FamilyMembers,
	Float:FamilySpawn[4],
	FamilyInterior,
};

enum zInfo
{
	zOwner[64],
	zColor[20],
    Float:zMinX,
    Float:zMinY,
    Float:zMaxX,
    Float:zMaxY,
};

enum pFishing
{
	pFish1[20],
	pFish2[20],
	pFish3[20],
	pFish4[20],
	pFish5[20],
	pWeight1,
	pWeight2,
	pWeight3,
	pWeight4,
	pWeight5,
	pFid1,
	pFid2,
	pFid3,
	pFid4,
	pFid5,
	pLastFish,
	pFishID,
	pLastWeight,
};

enum pCooking
{
	pCook1[20],
	pCook2[20],
	pCook3[20],
	pCook4[20],
	pCook5[20],
	pCWeight1,
	pCWeight2,
	pCWeight3,
	pCWeight4,
	pCWeight5,
	pCookID1,
	pCookID2,
	pCookID3,
	pCookID4,
	pCookID5,
};

enum pGroceries
{
	pChickens,
	pChicken,
	pHamburgers,
	pHamburger,
	pPizzas,
	pPizza,
};

enum pSpec
{
	Float:Coords[3],
	Float:sPx,
	Float:sPy,
	Float:sPz,
	sPint,
	sLocal,
	sCam,
};

enum eCars
{
	model_id,
	Float:pos_x,
	Float:pos_y,
	Float:pos_z,
	Float:z_angle,
};

enum hNews
{
	hTaken1,
	hTaken2,
	hTaken3,
	hTaken4,
	hTaken5,
	hAdd1[128],
	hAdd2[128],
	hAdd3[128],
	hAdd4[128],
	hAdd5[128],
	hContact1[128],
	hContact2[128],
	hContact3[128],
	hContact4[128],
	hContact5[128],
};

enum pInfo
{
	pKey[128],
	pName[24],
	pLevel,
	pAdmin,
	pDonateRank,
	gPupgrade,
	pConnectTime,
	pReg,
	pSex,
	pAge,
	pOrigin,
	pCK,
	pMuted,
	pExp,
	pCash,
	pAccount,
	pCrimes,
	pKills,
	pDeaths,
	pArrested,
	pWantedDeaths,
	pPhoneBook,
	pLottoNr,
	pFishes,
	pBiggestFish,
	pJob,
	pPayCheck,
	pHeadValue,
	pJailed,
	pJailTime,
	pMats,
	pDrugs,
	pLeader,
	pMember,
	pFMember,
	pRank,
	pChar,
	pContractTime,
	pDetSkill,
	pSexSkill,
	pBoxSkill,
	pLawSkill,
	pMechSkill,
	pJackSkill,
	pCarSkill,
	pNewsSkill,
	pDrugsSkill,
	pCookSkill,
	pFishSkill,
	Float:pHealth,
	Float:pSHealth,
	pInt,
	pLocal,
	pTeam,
	pModel,
	pPnumber,
	pPhousekey,
	pPbiskey,
	Float:pPos_x,
	Float:pPos_y,
	Float:pPos_z,
	pCarLic,
	pFlyLic,
	pBoatLic,
	pFishLic,
	pGunLic,
	pGun1,
	pGun2,
	pGun3,
	pGun4,
	pAmmo1,
	pAmmo2,
	pAmmo3,
	pAmmo4,
	pCarTime,
	pPayDay,
	pPayDayHad,
	pCDPlayer,
	pWins,
	pLoses,
	pAlcoholPerk,
	pDrugPerk,
	pMiserPerk,
	pPainPerk,
	pTraderPerk,
	pTut,
	pMissionNr,
	pWarns,
	pAdjustable,
	pFuel,
	pMarried,
	pMarriedTo[128],
};

enum hInfo
{
	Float:hEntrancex,
	Float:hEntrancey,
	Float:hEntrancez,
	Float:hExitx,
	Float:hExity,
	Float:hExitz,
	hHealthx,
	hHealthy,
	hHealthz,
	hArmourx,
	hArmoury,
	hArmourz,
	hOwner[MAX_PLAYER_NAME],
	hDiscription[MAX_PLAYER_NAME],
	hValue,
	hHel,
	hArm,
	hInt,
	hLock,
	hOwned,
	hRooms,
	hRent,
	hRentabil,
	hTakings,
	hVec,
	hVcol1,
	hVcol2,
	hDate,
	hLevel,
};

enum bInfo
{
    bOwned,
	bOwner[64],
	bMessage[128],
	bExtortion[MAX_PLAYER_NAME],
	Float:bEntranceX,
	Float:bEntranceY,
	Float:bEntranceZ,
	Float:bExitX,
	Float:bExitY,
	Float:bExitZ,
	bLevelNeeded,
	bBuyPrice,
	bEntranceCost,
	bTill,
	bLocked,
	bInterior,
	bProducts,
	bMaxProducts,
	bPriceProd,
};

enum sbInfo
{
	sbOwned,
	sbOwner[64],
	sbMessage[128],
	sbExtortion[MAX_PLAYER_NAME],
	Float:sbEntranceX,
	Float:sbEntranceY,
	Float:sbEntranceZ,
	sbLevelNeeded,
	sbBuyPrice,
	sbEntranceCost,
	sbTill,
	sbLocked,
	sbInterior,
	sbProducts,
	sbMaxProducts,
	sbPriceProd,
};

enum pHaul
{
	pCapasity,
	pLoad,
};

enum pCrime
{
	pBplayer[32],
	pAccusing[32],
	pAccusedof[32],
	pVictim[32],
};

enum mInfo
{
    mTitle[128],
    mText1[128],
    mText2[128],
    mText3[128],
    mText4[128],
    mText5[128],
    mText6[128],
    mText7[128],
    mText8[128],
    mText9[128],
    mText10[128],
    mText11[128],
    mText12[128],
    mText13[128],
    mText14[128],
    mText15[128],
    mText16[128],
    mText17[128],
    mText18[128],
    mGText1[128],
    mGText2[128],
    mGText3[128],
    mGText4[128],
    mGText5[128],
    mGText6[128],
	Float:mCP1[3],
	Float:mCP2[3],
	Float:mCP3[3],
	Float:mCP4[3],
	Float:mCP5[3],
	Float:mCP6[3],
	mReward,
	mToggle,
};

enum kInfo
{
    kTitle[128],
    kMaker[MAX_PLAYER_NAME],
    kText1[128],
    kText2[128],
    kText3[128],
    kText4[128],
    kText5[128],
    kText6[128],
    kText7[128],
    kText8[128],
    kText9[128],
    kText10[128],
    kText11[128],
    kText12[128],
    kText13[128],
    kText14[128],
    kText15[128],
    kText16[128],
    kText17[128],
    kText18[128],
    kGText1[128],
    kGText2[128],
    kGText3[128],
    kGText4[128],
    kGText5[128],
    kGText6[128],
	Float:kCP1[3],
	Float:kCP2[3],
	Float:kCP3[3],
	Float:kCP4[3],
	Float:kCP5[3],
	Float:kCP6[3],
	kNumber,
	kReward,
	kToggle,
};

enum iInfo
{
	iAdmin[128],
	iMOTD[128],
	iPassword[128],
	iNeedPass,
	iLock,
	iPlayers,
};