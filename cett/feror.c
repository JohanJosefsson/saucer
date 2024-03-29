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
	// �ndra signatur!;
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

	*pPic = (me->flickerCount++/4)%2 + 2;  // / speed delay % number of changing pictures


	if(0 == me->moveCount++ % 2) { /* Delay to approriate speed */

		if(rand()%2) {
			/* random walk */
			me->x += ((rand())%3) - 1; // [-1, 0, 1]
			me->y += ((rand())%3) - 1; // [-1, 0, 1]
		} else {
			/* Follow the saucer! */
			getSaucerPos(&sx, &sy);
			if(sx < me->x)me->x--;
			if(sx > me->x)me->x++;
			if(sy < me->y)me->y--;
			if(sy > me->y)me->y++;
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
	{ 10, 10 },
	{ 11, 11 },
	{ 12, 12 }

};

struct Level monster_feror =
{
	IDB_BACKGROUND_FEROR,
	IDB_MONSTER_FEROR,
	IDB_OBSTACLE,
	Monster_new,
	Monster_delete,
	Monster_isPos,
	Monster_getPos,
	Monster_move,
    sizeof(obstacles)/sizeof(struct Obstacle),
	obstacles
};
