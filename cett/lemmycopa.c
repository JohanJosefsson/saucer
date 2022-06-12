#define PICTURE_FLICKER_SLOWDOWN    50
#define INITIAL_X                   MAX_X
#define INITIAL_Y                    MAX_Y
#define X_MOVE_SLOWDOWN             2
#define Y_MOVE_SLOWDOWN             2
#define DX_CHANGE_SLOWDOWN          80
#define DY_CHANGE_SLOWDOWN          80
#define NOF_PICS                     1
#define INITIAL_CNT                  7
#define BOUNCE_BACK                  0

/* Wait time out */
#define WAIT_TO (10)


#include <stdlib.h> /* required for randomize() and random() */
#include "resource.h"
#include <assert.h>
#include "level.h"


enum State { WAITING, GOING_H, GOING_V }; /* horizontally/vertically */

struct Monster {
	int x;
	int y;
	int cnt;
	enum State state;
	int wait_cnt;
	int saucer_x;
	int saucer_y;
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
	me->cnt = INITIAL_CNT;
	me->state = WAITING;
	me->wait_cnt = WAIT_TO;
//	getObstacles(obstacles, 70 , 4, 4, 41, 21);
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

    switch(me->state) {
	case WAITING:
		if(!me->wait_cnt--) {
			getSaucerPos(&me->saucer_x, &me->saucer_y);
			me->state = rand()%2?GOING_H:GOING_V;
		};
		break;
		
	case GOING_H:
//varför inte ?		if(!me->cnt%X_MOVE_SLOWDOWN) {
				if(0 == me->cnt%X_MOVE_SLOWDOWN) {
			if(me->saucer_x < me->x)me->x--;
			if(me->saucer_x > me->x)me->x++;
			if(me->saucer_x == me->x) {
				me->state = WAITING;    // Wait here
				me->wait_cnt = WAIT_TO; //
			};
		};
		break;

	case GOING_V:
		if(0 == me->cnt%Y_MOVE_SLOWDOWN) {
			if(me->saucer_y < me->y)me->y--;
			if(me->saucer_y > me->y)me->y++;
			if(me->saucer_y == me->y) {
				me->state = WAITING;    // Wait here
				me->wait_cnt = WAIT_TO; //
			};
		}
		break;

	default:
		assert(0);
	};

	// Make monster flicker
	*pPic = ((me->cnt)/PICTURE_FLICKER_SLOWDOWN)%NOF_PICS + 2;

	// Cancel move if impossible
	if(!canGoAt(me->x, me->y)) {
		me->state = WAITING;    // Wait here
		me->wait_cnt = WAIT_TO; //
		me->x = old_x;
 		me->y = old_y;
	};
	*px = me->x;
	*py = me->y;
	me->cnt ++;

};

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


struct Level monster_lemmycopa =
{
	IDB_BACKGROUND_lemmycopa,
	IDB_MONSTER_lemmycopa,
	IDB_OBSTACLE,
	Monster_new,
	Monster_delete,
	Monster_isPos,
	Monster_getPos,
	Monster_move,
    sizeof(obstacles)/sizeof(struct Obstacle),
	obstacles
};

