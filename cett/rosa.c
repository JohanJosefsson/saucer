#define PICTURE_FLICKER_SLOWDOWN    50
#define INITIAL_X                   10
#define INITIAL_Y                    2
#define X_MOVE_SLOWDOWN             20
#define Y_MOVE_SLOWDOWN             20
#define DX_CHANGE_SLOWDOWN          80
#define DY_CHANGE_SLOWDOWN          80
#define NOF_PICS                     3
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

static struct Obstacle obstacles[30];

static void Monster_new(void) {
	struct Monster * p;
	p = me;
	p->x = 10; // Left to right
	p->y = 2; // Downwards
	p->flickerCount = 0;
	p->moveCount = 0;
	me = p;
	getObstacles(obstacles, 30 , 4, 4, 41, 21);

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

	/* The saucers position  */
	int sx;
	int sy;

	old_x = me->x;
	old_y = me->y;

	*pPic = (me->flickerCount++/4)%NOF_PICS + 2;  // / speed delay % number of changing pictures


	/* Follow the saucer! */
	if(0 == me->moveCount++ % 5) { /* Delay to approriate speed */
		getSaucerPos(&sx, &sy);
		if(sx < me->x)me->x--;
		if(sx > me->x)me->x++;
		if(sy < me->y)me->y--;
		if(sy > me->y)me->y++;
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

/*
static struct Obstacle obstacles[] = {
	{ 3, 9 },
	{ 11, 4 },
	{ 16,3 },
	{ 23, 8 },
	{ 23, 11 }
};
*/

struct Level monster_rosa =
{
	IDB_BACKGROUND_rosa,
	IDB_MONSTER_rosa,
	IDB_OBSTACLE,
	Monster_new,
	Monster_delete,
	Monster_isPos,
	Monster_getPos,
	Monster_move,
    sizeof(obstacles)/sizeof(struct Obstacle),
	obstacles
};

