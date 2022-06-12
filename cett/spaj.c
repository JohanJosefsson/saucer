#if 0
#define PICTURE_FLICKER_SLOWDOWN    10
#define INITIAL_X                   10
#define INITIAL_Y                    2
#define X_MOVE_SLOWDOWN              5
#define Y_MOVE_SLOWDOWN             10
#define DX_CHANGE_SLOWDOWN          40
#define DY_CHANGE_SLOWDOWN          60
#define NOF_PICS                     3
#define INITIAL_CNT                  7
#define BOUNCE_BACK                  1
#endif



#define PICTURE_FLICKER_SLOWDOWN    3
#define INITIAL_X                   10
#define INITIAL_Y                    2
#define X_MOVE_SLOWDOWN              3
#define Y_MOVE_SLOWDOWN             3
#define DX_CHANGE_SLOWDOWN          6
#define DY_CHANGE_SLOWDOWN          12
#define NOF_PICS                     3
#define INITIAL_CNT                  7
#define BOUNCE_BACK                  1



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

static void Monster_new(void) {
	me->x = INITIAL_X; // Left to right
	me->y = INITIAL_Y; // Downwards
	srand ( time(NULL) );
	me->cnt = INITIAL_CNT;
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
	///////////////

	// Move in x direction.

	// Update dx if time is due.
	if(0 == me->cnt%DX_CHANGE_SLOWDOWN) {
		me->dx = ((rand())%3) - 1; // [-1, 0, 1]
	};
	// Move if time is due
	if(0 == me->cnt%X_MOVE_SLOWDOWN) {
		assert(me->dx == -1 || me->dx == 0 || me->dx == 1); // How does rand work, really?
		me->x += me->dx;
	};

	// Move in y direction

	if(0 == me->cnt%DY_CHANGE_SLOWDOWN)
		me->dy = rand()%3 - 1; // [-1, 0, 1]

	if(0 == me->cnt%Y_MOVE_SLOWDOWN) {
		me->y += me->dy;
	};

	// Make monster flicker
	*pPic = ((me->cnt)/PICTURE_FLICKER_SLOWDOWN)%NOF_PICS + 2;

	// Cancel move if impossible
	if(!canGoAt(me->x, me->y)) {
		me->x = old_x;
		me->y = old_y;
		if(BOUNCE_BACK) {
			me->dx = me->dx * (-1);
			me->dy = me->dy * (-1);
		};
	};

	*px = me->x;
	*py = me->y;
	me->cnt ++;
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


struct Level monster_spaj =
{
	IDB_BACKGROUND_SPAJ,
	IDB_MONSTER_SPAJ,
	IDB_OBSTACLE,
	Monster_new,
	Monster_delete,
	Monster_isPos,
	Monster_getPos,
	Monster_move,
    sizeof(obstacles)/sizeof(struct Obstacle),
	obstacles
};
