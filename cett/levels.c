#include "level.h"
#include <tchar.h>

extern struct Level monster1;
extern struct Level monster2;
extern struct Level monster_sqaj;
extern struct Level monster_zqaj;
extern struct Level monster_zqx;
extern struct Level monster_spaj;
extern struct Level monster_dovolenky;
extern struct Level monster_santalenky;
extern struct Level monster_feror;
extern struct Level monster_elfrazzoo;

extern struct Level monster_lemmycopa;
extern struct Level monster_pezel;
extern struct Level monster_rosa;
//extern struct Level monster_drebylus;
extern struct Level monster_egiptas;
extern struct Level monster_rhedeg;

extern struct Level monster_nerfol;


extern struct Level monster_portalix;
extern struct Level monster_igycoopa;
extern struct Level monster_orbitalix;
extern struct Level monster_furhax;
extern struct Level monster_laddoads;

extern struct Level monster_mjau;
extern struct Level monster_siffrox;
extern struct Level monster_rhox;
extern struct Level monster_majorzero;


struct Level * levels[] =
{
#ifndef _DEBUG
	
	&monster1,
	&monster2,
	&monster_sqaj,
	&monster_zqaj,
	&monster_zqx,
	&monster_spaj,
	&monster_dovolenky,	
	&monster_santalenky,
	&monster_feror,
	&monster_elfrazzoo,
	&monster_lemmycopa,
	&monster_pezel,
	&monster_rosa,
//	&monster_drebylus,
	&monster_egiptas,
	&monster_portalix,
	&monster_rhedeg, // mer bakgrund...
	&monster_nerfol,
	&monster_igycoopa,
//	&monster_laddoads, // Alfred
	&monster_furhax,
	&monster_mjau,
	&monster_siffrox,
	&monster_rhox,
#endif
	&monster_majorzero,
	
	//	&monster_orbitalix,

0	
};


wchar_t * names[] = {

#ifndef _DEBUG
		
	_T("primus"),
	_T("deuxieme"),
	_T("sqaj"),
	_T("zqaj"),
	_T("zqx"),
	_T("spaj"),
	_T("dovolenky"),	
	_T("santalenky"),
	_T("feror"),
	_T("elfrazzoo"),
	_T("såsix"), // files: lemmycopa
	_T("pezel"),
	_T("rosa"),

//	_T("drebylus"),

	_T("egiptas"),
	_T("portalix"),

	_T("rhedeg"),

	_T("nerfol"),
	_T("donix"), // files: igycoopa
//	_T("laddoads"),
		_T("furhax"),
		_T("mjau"),
		_T("siffrox"),
_T("rhox"),
#endif
_T("major zero"),



//	_T("orbitalix"),
0


};
