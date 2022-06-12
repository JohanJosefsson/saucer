#define PICTURE_FLICKER_SLOWDOWN    50
#define INITIAL_X                   10
#define INITIAL_Y                    2
#define X_MOVE_SLOWDOWN             20
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



struct Portal {
	int x;
	int y;
};
struct Portal portals[] =
{
	{ 15, 2 },
	{ 34, 5 },
	{ 34,18 },
};


struct Monster {
	int x;
	int y;
	int cnt;
	int dx;
	int dy;
	int portal;
	struct Portal * portals;
	int inhibitCnt;
	int flickerCount;
	int moveCount;
};
static struct Monster monster;
static struct Monster * me = &monster;




/*
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

static struct Obstacle obstacles[70];
*/
static void Monster_new(void) {
	me->x = INITIAL_X; // Left to right
	me->y = INITIAL_Y; // Downwards
	me->dx = 1;
	me->dy = 1;
	srand ( time(NULL) );
	me->cnt = INITIAL_CNT;
//	getObstacles(obstacles, 70 , 4, 4, 41, 21);
	me->portal = rand()%3;
	me->portals = portals;
	me->inhibitCnt = 10;
	me->flickerCount = 0;
	me->moveCount = 0;
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

	int i;

	old_x = me->x;
	old_y = me->y;

	*pPic = (me->flickerCount++/4)%4 + 2;  // / speed delay % number of changing pictures

	/* Teleportation */
	if(0 != me->inhibitCnt--) {
		for(i = 0; i < 3; i++) {
			if(me->x == me->portals[me->portal].x && me->y == me->portals[me->portal].y) {
				/* We have entered a portal */
				int t; /* Which portal to go to */
				t = (me->portal + rand()%2 + 1)%3;
				me->x = me->portals[t].x;
				me->y = me->portals[t].y;
				me->portal = (t + rand()%2 + 1)%3;
				me->inhibitCnt = 10;
			};
		};
	};

	/* Go to a (tele)portal */
	if(0 == me->moveCount++ % 3) { /* Delay to approriate speed */
		if(0 != rand()%4) { /* Proportion systematic/random */
			/* systematic part */
			int tx, ty;
			tx = me->portals[me->portal].x;
			ty = me->portals[me->portal].y;
			if(tx < me->x)me->x--;
			if(tx > me->x)me->x++;
			if(ty < me->y)me->y--;
			if(ty > me->y)me->y++;
		} else {
			/* Random element */
			me->x += (rand()%3 - 1);
			me->x += (rand()%3 - 1);
		};
	};

	/* Cancel impossible move */
	if(!canGoAt(me->x, me->y)) {
		me->x = old_x;
		me->y = old_y;
	};

	*px = me->x;
	*py = me->y;
}

int apa;

static int Monster_isPos(int x, int y) {
	return (x == me->x && y == me->y);
}

/*
static struct Obstacle obstacles[] = {
	{ 15, 2 },
	{ 34, 5 },
	{ 34,18 },
};
*/

struct Level monster_nerfol =
{
	IDB_BACKGROUND_nerfol,
	IDB_MONSTER_nerfol,
	IDB_OBSTACLE,
	Monster_new,
	Monster_delete,
	Monster_isPos,
	Monster_getPos,
	Monster_move,
    0,//sizeof(obstacles)/sizeof(struct Obstacle),
	0,//obstacles
};

