#define PICTURE_FLICKER_SLOWDOWN    50
#define INITIAL_X                   10
#define INITIAL_Y                    6
#define X_MOVE_SLOWDOWN              4
#define Y_MOVE_SLOWDOWN             20
#define DX_CHANGE_SLOWDOWN          80
#define DY_CHANGE_SLOWDOWN          80
#define NOF_PICS                     1
#define INITIAL_CNT                  7
#define BOUNCE_BACK                  0




#include <stdlib.h> /* required for randomize() and random() */
#include "resource.h"
#include <assert.h>
#include "level.h"

struct Monster {
	int x;
	int y;
	int cnt;
	int dx;
	int dy;
};
static struct Monster monster;
static struct Monster * me = &monster;





static getObstacles(struct Obstacle * obs, int num, int x1, int y1, int x2, int y2)
{
	int i;
	int x, y;
	assert(x1 < x2);
	assert(y1 < y2);
	i = 0;
	while(i < num) {
		x = x1 + rand()%(x2 - x1);
		y = y1 + rand()%(y2 - y1);
		obs[i].x = x;
		obs[i].y = y;
		i++;
	};
}

static struct Obstacle obstacles[15];

static void Monster_new(void) {
	me->x = INITIAL_X; // Left to right
	me->y = INITIAL_Y; // Downwards
	me->dx = 1;
	me->dy = 0;
	srand ( time(NULL) );
	me->cnt = INITIAL_CNT;
	getObstacles(obstacles, 15 , 4, 14, 41, 21);
}
static void Monster_delete(void) {
	// ändra signatur!;
}
static void Monster_getPos(int * px, int * py) {
	*px = me->x;
	*py = me->y;
}







static void Monster_move(int * px, int * py, int * pPic) {
	// Move if time is due
	if(0 == me->cnt%X_MOVE_SLOWDOWN) {
		me->x += me->dx;
	};

#define PPORTALGAP (8)
	/* Turn back: */
	if(3 == me->x)me->dx = 1; 
	if(MAX_X - 3== me->x)me->dx = -1;
	/* The portal */
	if(MAX_X/2 + PPORTALGAP == me->x && -1 == me->dx) {
		me->x = MAX_X/2 - PPORTALGAP; 
	};
	if(MAX_X/2 - PPORTALGAP == me->x && 1 == me->dx) {
		me->x = MAX_X/2 + PPORTALGAP; 
	};


	*pPic = ((1 == me->dx)?2:4) + me->x%2;
	*px = me->x;
	*py = me->y;
	me->cnt ++;

};

static int Monster_isPos(int x, int y) {
	return (x == me->x && y == me->y);
}

/*
static struct Obstacle obstacles[] = {
	{ 3, 9 },
	{ 11, 4 },
	{ 16,3 },
	{ 23, 8 },
	{ 23, 11 }
};
*/

struct Level monster_portalix =
{
	IDB_BACKGROUND_portalix,
	IDB_MONSTER_portalix,
	IDB_OBSTACLE,
	Monster_new,
	Monster_delete,
	Monster_isPos,
	Monster_getPos,
	Monster_move,
    sizeof(obstacles)/sizeof(struct Obstacle),
	obstacles
};

