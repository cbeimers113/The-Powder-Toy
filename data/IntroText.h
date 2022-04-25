#pragma once
#include "Config.h"

const char *const introTextData =
	"\btCyens Toy \boVersion 5.0 \bg- \blhttps://github.com/cbeimers113/cyens-toy\n"
	"\bgBuilt on "
	"\brThe Powder Toy \boVersion " MTOS(SAVE_VERSION) "." MTOS(MINOR_VERSION) " \bg- \blhttps://powdertoy.co.uk\n"
	"\bo---------------------------------------------------------------\n"
	"\n"
	"\btCyens Toy\bg by firefreak11\n"
	"\bgSpecial thanks to Michael238 and LBPHacker\n"
	"\n"
	"\btCyens Toy \bgaims to enhance \brThe Powder Toy \bgby going deeper into science simulation.\n"
	"This mod implements phenomena from several branches of chemistry and physics\n"
	"which are feasible to simulate and fun to explore in a 2D particle simulator.\n"
	"\n"
	// TODO:
	// Update this list as features are implemented
	"\boFeatures:\n"
	"\t\bg- Time Dilation\n"
	"\t\bg- Local Gravity\n"
	"\t\bg- Compressible Gases\n"
	// "\t\bg- Organic Chemistry\n"
	// "\t\bg- Biochemistry\n"
	// "\t\bg- Digital Logic\n"
	"\n"
	"\boContributors: \bgStanislaw K Skowronek (Designed the original Powder Toy),\n"
	"\bgSimon Robertshaw, Skresanov Savely, cracker64, Catelite, Bryan Hoyle, Nathan Cousins, jacksonmj,\n"
	"\bgFelix Wallin, Lieuwe Mosch, Anthony Boot, Matthew \"me4502\", MaksProg, jacob1, mniip, LBPHacker\n"
	"\n"
#ifndef BETA
	"\bgTo use online features such as saving, you need to register at: \brhttps://powdertoy.co.uk/Register.html\n"
#else
	"\brThis is a BETA, you cannot save things publicly. If you are planning on publishing any saves, use the release version\n"
#endif
	"\n"
	"\bt" MTOS(SAVE_VERSION) "." MTOS(MINOR_VERSION) "." MTOS(BUILD_NUM) " " IDENT
#ifdef SNAPSHOT
	" SNAPSHOT " MTOS(SNAPSHOT_ID)
#elif MOD_ID > 0
	" MODVER " MTOS(SNAPSHOT_ID)
#endif
#ifdef X86
	" X86"
#endif
#ifdef X86_SSE
	" X86_SSE"
#endif
#ifdef X86_SSE2
	" X86_SSE2"
#endif
#ifdef X86_SSE3
	" X86_SSE3"
#endif
#ifdef LUACONSOLE
	" LUACONSOLE"
#endif
#ifdef GRAVFFT
	" GRAVFFT"
#endif
#ifdef REALISTIC
	" REALISTIC"
#endif
	;
