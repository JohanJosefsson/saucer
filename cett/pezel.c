#define PICTURE_FLICKER_SLOWDOWN    30
#define INITIAL_X                   MAX_X / 2
#define INITIAL_Y                    0
#define X_MOVE_SLOWDOWN             4
#define Y_MOVE_SLOWDOWN             4
#define DX_CHANGE_SLOWDOWN          80
#define DY_CHANGE_SLOWDOWN          80
#define NOF_PICS                     7
#define INITIAL_CNT                  7
#define BOUNCE_BACK                  1




#include <stdlib.h> /* required for randomize() and random() */
#include "resource.h"
#include <assert.h>
#include "level.h"

////////////////////////////////////////////////////////////////////////////
// maze.h

#define UPPER_SPACE (5)
	
#define X (MAX_X + 1)
#define Y (MAX_Y + 1 - UPPER_SPACE)
/* saucer starts at (22, 10) */

//void get_maze(int the_maze[X][Y]);


//////////////////////////////////////////
// maze.c

//#include "maze.h"
#include <assert.h>
#include <stdlib.h>
#include <time.h>

typedef struct { int x; int y;} Point;

typedef enum { L, F, R } Direction;
typedef enum { N = R + 1, E, S, W } Course;
#define assert_course(c) assert(c >= N && c <= W)
#define assert_direction(d) assert(d >= L && d <= R)

static Point step(Point p, Course c)
{
	Point ret;
	assert_course(c);
	switch(c) {
	case N:
		ret.x = p.x;
		ret.y = p.y - 1;
		break;
	case E:
		ret.x = p.x + 1;
		ret.y = p.y;
		break;
	case S:
		ret.x = p.x;
		ret.y = p.y + 1;
		break;
	case W:
		ret.x = p.x - 1;
		ret.y = p.y;
		break;
	default:
		assert(0);
	};
	return ret;
}

static Course change(Course c, Direction d)
{
	Course r;
	assert_course(c);
	assert_direction(d);
	switch(d) {
	case L:
		switch(c) {
		case N:
			r = W;
			break;
		case E:
			r = N;
			break;
		case S:
			r = E;
			break;
		case W:
			r = S;
			break;
		default:
			assert(0);
		};
		break;
		
	case F:
		r = c;
		break;
	case R:
		switch(c) {
		case N:
			r = E;
			break;
		case E:
			r = S;
			break;
		case S:
			r = W;
			break;
		case W:
			r = N;
			break;
		default:
			assert(0);
		};
		break;
	default:
		assert(0);
	};
	return r;
}

static int * g;
static void set(Point p)
{
	static cnt = 1;
	*(g + Y*p.x + p.y) = cnt++;
}

static Point point(int x, int y)
{
	Point r;
	r.x = x;
	r.y = y;
	return r;
}

static  int is_set(Point p)
{
	return !!(*(g + Y*p.x + p.y));
}

static int can_go(Point p, Course c) {
	Direction d;
	assert_course(c);
	if(p.x < 0 || p.x >= X) return 0;
	if(p.y < 0 || p.y >= Y) return 0;

	for(d = L; d <= R; d++) {
		if(is_set(step(p, change(c, d)))) {
			return 0;
		};
	};
	return 1;
}


struct Die {
	int left;
	int forward;
	int right;
};

static int die_get(struct Die * p, Direction * pd)
{
	while(!p->left || !p->forward || !p->right) {
		int r = rand()%3;
		if(r == L && p->left == 0) {
			p->left = 1;
			*pd = L;
			assert_direction(*pd);
			return 1;
		};

		if(r == F && p->forward == 0) {
			p->forward = 1;
			*pd = F;
			return 1;
		};

		if(r == R && p->right == 0) {
			p->right = 1;
			*pd = R;
			return 1;
		};
	};
	return 0;
}


static void die_reset(struct Die * p)
{
	p->left = 0;
	p->forward = 0;
	p->right = 0;
}

static void get_path(Point cur, Course course, int (*my_can_go)(Point p, Course c) )
{
	Point next;
	Course new_course;
	int i;
	struct Die die;
	Direction dir;

	assert_course(course);

	set(cur);
	die_reset(&die);
	for(i = 0;; i++) {
		if(die_get(&die, &dir)) {
			new_course = change(course, dir);
			next = step(cur, new_course);
			if(can_go(next, new_course) &&  (my_can_go == 0  || (my_can_go != 0 && (*my_can_go)(next, new_course)))   ) {
				cur = next;
				course = new_course;
				set(cur);
				die_reset(&die);
			};
		} else {
			break;
		};
	};


}

static void clear_maze(void) {
	int i;
	for(i = 0;i < X*Y; i++) {
		g[i] = 0;
	};
}

/* Application part: */

/* My can go... */
struct {
	int y;
	int x0;
	int xsize;
} my_can_go_data;


static int my_can_go(Point p, Course c) {
	assert_course(c);
	if(p.y == Y/2 && (p.x > X/4 && p.x < X - X/4)) return 0;
	return 1;
}

static
void get_maze(int pa[X][Y])
{
	int i;
	srand((unsigned int)time(0));
	g = (int*)&pa[0];
	clear_maze();
	while(!is_set(point(X/2,0))) {
		clear_maze();
//		get_path(point(17, 10 /* X/2,Y-1 */), N, my_can_go);


		//set(point(0,0));
		//set(point(X-1,Y-1));
		//set(point(10,17));
		//return;

//				get_path(point(10, 17 /* X/2,Y-1 */), N, my_can_go);
		get_path(point(SAUCER_START_X, SAUCER_START_Y - UPPER_SPACE /* X/2,Y-1 */), N, my_can_go);
	};
	for(i = 0;i < 2; i++) {
		int x, y;
		Course c;
		c = rand()%(W - N + 1) + N;
		for(x = 0;x < X; x++) {
			for(y = 0;y < Y;y++) {
				if(is_set(point(x,y))) {
					get_path(point(x,y), c, 0);
				};
			};
		};
	};
}












/////////////////////////////////////
// The ordinary monster:
struct Monster {
	int x;
	int y;
	int cnt;
	int dx;
	int dy;
};
static struct Monster monster;
static struct Monster * me = &monster;

// BEGIN ostacles thing
//
/* Global variables */
static int the_maze[X][Y];
static struct Obstacle obstacles[(MAX_X + 1) * (MAX_Y + 1)];
static nofobs = 0; /* Number of obstacles */
static void reset_obstacles(void)
{
	nofobs = 0;
}
static void set_obstacle(int x, int y) {
	obstacles[nofobs].x = x;
	obstacles[nofobs].y = y;
	assert(nofobs < sizeof(obstacles)/sizeof(struct Obstacle));
	nofobs++;
};

static get_obstacles(void)
{

	int i, j;
//	static char buf[X + 1];
	get_maze(the_maze);
	for(i = 0; i < Y; i++) {
		for(j = 0; j < X; j++) {
			//buf[j] = the_maze[j][i]?' ':'O';
			if(!the_maze[j][i])set_obstacle(j, i + UPPER_SPACE);
		};
//		buf[X] = '\0';
//		printf("|%s|\n", buf);
	};
	for(i = 0; i < MAX_X + 1;i++) {
		if(X/2 != i)set_obstacle(i, UPPER_SPACE - 1);
	};
}
static int get_nof_obstacles(void)
{
	return nofobs;
}
//
//// END obstacles thing

static void Monster_new(void) {
	me->x = INITIAL_X; // Left to right
	me->y = INITIAL_Y; // Downwards
	me->dx = 1;
	me->dy = 1;
	srand ( time(NULL) );
	me->cnt = INITIAL_CNT;
	reset_obstacles();
	get_obstacles();
	setNofObstacles(get_nof_obstacles());
//	monster_pezel.nofObstacles = get_nof_obstacles();


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
	if(0 == me->cnt%X_MOVE_SLOWDOWN) {
		me->x += me->dx;
		if(me->x + me->dx < 0 || me->x + me->dx > MAX_X) me->dx *= -1;
	};
	if(0 == me->cnt%Y_MOVE_SLOWDOWN) {
		me->y += me->dy;
		if(me->y + me->dy < 0 || me->y + me->dy == UPPER_SPACE - 1) me->dy *= -1;// Jag fattar inte själv varför men det verkar funka...
	};

	// Make monster flicker
	*pPic = ((me->cnt)/PICTURE_FLICKER_SLOWDOWN)%NOF_PICS + 2;


		//				me->x = old_x;
		//				me->y = old_y;

//	};// canGoAt()
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


struct Level monster_pezel =
{
	IDB_BACKGROUND_pezel,
	IDB_MONSTER_pezel,
	IDB_OBSTACLE,
	Monster_new,
	Monster_delete,
	Monster_isPos,
	Monster_getPos,
	Monster_move,
    sizeof(obstacles)/sizeof(struct Obstacle),
	obstacles
};

