#include "resource.h"
#include <assert.h>
#include "level.h"
//#include <malloc.h>
//struct Monster;
static const int apa[] = {1,1};

static const int pattern1[] = { 
	0,-1,0,1,-1,0,1,1,0,0,1,0,0,0,1,0,-1,0,0,0,1,0,0,1,-1,-1,1,1,-1,0,0,1,1,0,1,1,1,-1,1,1,0,1,1,0,1,0,1,1,0,0,-1,0,-1,0
};
static const int pattern2[] = { 
	1,1,1,0,1,0,1,-1,0,0,1,0,0,1,0,0,0,0,0,-1,0,1,1,0,1,0,1,1,1,1,0,1,1,1,0,-1,0,0,0,1,0,0,1,1,1,-1,-1,-1,1,0,0,1,1,0
};







struct Monster {
	int x;
	int y;

	int * xPattern;
	int * yPattern;
	int patternSize;
	int delayLimit;
	int delayCount;
	int patternPos;
	int dir;
};
static struct Monster monster;
static struct Monster * me = &monster;

static void Monster_new(void) {
	struct Monster * p;
//	p = malloc(sizeof(struct Monster));
	p = me;
	p->x = 10; // Left to right
	p->y = 2; // Downwards
	p->delayCount = 0;
	p->delayLimit = 3;
	p->dir = 1;
	p->xPattern = pattern1;
	p->yPattern = pattern2;
	p->patternSize = 42;//sizeof(pattern1) / sizeof(int); TODO
	assert(sizeof(pattern1) == sizeof(pattern2));
	p->patternPos = 0;
	me = p;
}
static void Monster_delete(void) {
	// ändra signatur!;
}
static void Monster_getPos(int * px, int * py) {
	*px = me->x;
	*py = me->y;
}


static void Monster_move(int * px, int * py, int * pPic) {
	int old_x;
	int old_y;
	old_x = me->x;
	old_y = me->y;

	if(++(me->delayCount) == me->delayLimit) {

		me->delayCount = 0;
		me->x += (me->xPattern[me->patternPos]) * (me->dir);
		me->y += (me->yPattern[me->patternPos]) * (me->dir);
		me->patternPos += me->dir;
		if(me->patternPos == me->patternSize) {
			me->dir = -1;
		};
		if(me->patternPos == -1) {
			me->dir = 1;
		};
	};



	if(!canGoAt(me->x, me->y)) {
		me->x = old_x;
		me->y = old_y;
	};


	*px = me->x;
	*py = me->y;

	*pPic = (me->patternPos+1)%5 + 2;
}

static int Monster_isPos(int x, int y) {
	return (x == me->x && y == me->y);
}


static struct Obstacle obstacles[] = {
	{ 20, 20 },
	{ 15, 15 }
};


struct Level monster1 =
{
	IDB_BACKGROUND,
	IDB_MONSTER,
	IDB_OBSTACLE,
	Monster_new,
	Monster_delete,
	Monster_isPos,
	Monster_getPos,
	Monster_move,
    sizeof(obstacles)/sizeof(struct Obstacle),
	obstacles
};

//struct Level * pMonster1 = &monster1;
