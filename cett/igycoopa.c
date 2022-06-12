#define PICTURE_FLICKER_SLOWDOWN    50
#define INITIAL_X                   15
#define INITIAL_Y                   10
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

struct Monster {
	int x;
	int y;
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
	struct Monster * p;
	p = me;
	p->x = 10; // Left to right
	p->y = 2; // Downwards
	p->flickerCount = 0;
	p->moveCount = 0;
	me = p;
}
static void Monster_delete(void) {
	// ändra signatur!;
}
static void Monster_getPos(int * px, int * py) {
	*px = me->x;
	*py = me->y;
}





int distance(int x1, int y1, int x2, int y2)
{
	int distx, disty, ret;
	distx = (x2 > x1)?(x2-x1):(x1- x2);
	disty = (y2 > y1)?(y2-y1):(y1- y2);
	assert(distx >= 0);
	assert(disty >= 0);
	ret = (distx > disty)?distx:disty;
	assert(ret >= 0);
	return ret;
}

static void Monster_move(int * px, int * py, int * pPic) {
	int old_x;
	int old_y;

	/* The saucers position  */
	int sx;
	int sy;

	old_x = me->x;
	old_y = me->y;

	*pPic = (me->flickerCount++/4)%2 + 2;  // / speed delay % number of changing pictures

	getSaucerPos(&sx, &sy);
	if(me->y < MAX_Y && (0 == me->x || MAX_X == me->x)) {
		me->y++;
	} else if(0 == me->y) {
		me->x < sx?me->x--:me->x++;
	} else if(0 == me->moveCount++ % 2) { /* Delay to approriate speed */
			if(!rand()%3 || distance(me->x, me->y, sx, sy) > 7) {
			/* random walk */
			me->x += ((rand())%3) - 1; // [-1, 0, 1]
			me->y += ((rand())%3) - 1; // [-1, 0, 1]
		} else {
			/* Follow or flee from the saucer! */
			if(sy < me->y) {
				/* attack */ 
				if(sx < me->x)me->x--;
				if(sx > me->x)me->x++;
				if(sy < me->y)me->y--;
				if(sy > me->y)me->y++;
			} else {
				/* flee */
				if(sx < me->x)me->x--;
				if(sx > me->x)me->x++;
				if(sy < me->y)me->y++;
				if(sy > me->y)me->y--;
			};
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

static int Monster_isPos(int x, int y) {
	return (x == me->x && y == me->y);
}


static struct Obstacle obstacles[] = {
	{ 3, 9 },
	{ 11, 4 },
	{ 16,3 },
	{ 23, 8 },
	{ 23, 11 }
};


struct Level monster_igycoopa =
{
	IDB_BACKGROUND_igycoopa,
	IDB_MONSTER_igycoopa,
	IDB_OBSTACLE,
	Monster_new,
	Monster_delete,
	Monster_isPos,
	Monster_getPos,
	Monster_move,
    sizeof(obstacles)/sizeof(struct Obstacle),
	obstacles
};

