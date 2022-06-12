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

struct Monster {
	int x;
	int y;
	int cnt;
	int dx;
	int dy;
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
//#if 0
	// Update dx if time is due.
	if(0 == me->cnt%DX_CHANGE_SLOWDOWN) {
		me->dx = ((rand())%3) - 1; // [-1, 0, 1]
	};
//#endif
	// Move if time is due
	if(0 == me->cnt%X_MOVE_SLOWDOWN) {
		assert(me->dx == -1 || me->dx == 0 || me->dx == 1); // How does rand work, really?
		me->x += me->dx;
	};

	// Move in y direction
//#if 0
	if(0 == me->cnt%DY_CHANGE_SLOWDOWN)
		me->dy = rand()%3 - 1; // [-1, 0, 1]
//#endif
	if(0 == me->cnt%Y_MOVE_SLOWDOWN) {
		me->y += me->dy;
	};

	// Make monster flicker
	*pPic = ((me->cnt)/PICTURE_FLICKER_SLOWDOWN)%NOF_PICS + 2;

	// Cancel move if impossible
	if(!canGoAt(me->x, me->y)) {
		int nx, ny;
			int ndx, ndy; // new dx...
		//	do(!canGoAt(me->x, me->y)) {
		do {
			int rnd;
			ndx = me->dx;
			ndy = me->dy;
			while(ndx == me->dx && ndy == me->dy) {
				rnd = ((rand())%8);
				switch(rnd) {
				case 0:
					ndx = 0;
					ndy = +1;
					break;

				case 1:
					ndx = 0;
					ndy = -1;
					break;

				case 2:
					ndx = -1;
					ndy = 0;
					break;

				case 3:
					ndx = -1;
					ndy =  -1;
					break;

				case 4:
					ndx = -1;
					ndy = +1;
					break;

				case 5:
					ndx = +1;
					ndy = 0;
					break;

				case 6:
					ndx = +1;
					ndy = -1;
					break;

				case 7:
					ndx = +1;
					ndy = +1;
					break;

				};
			};	
			nx = me->x + ndx;
			ny = me->y +ndy;
			//nx += me->dx;/////////////////////////
			//ny += me->dy;

		} while(!canGoAt(nx,ny));
			me->dx = ndx;
			me->dy = ndy;


		me->x = nx;
		me->y = ny;


		//				me->x = old_x;
		//				me->y = old_y;

	};// canGoAt()
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


struct Level monster_generic =
{
	IDB_BACKGROUND_GENERIC,
	IDB_MONSTER_GENERIC,
	IDB_OBSTACLE,
	Monster_new,
	Monster_delete,
	Monster_isPos,
	Monster_getPos,
	Monster_move,
    sizeof(obstacles)/sizeof(struct Obstacle),
	obstacles
};

