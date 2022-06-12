// x : [0, 41]
// y : [0, 23]
#define MAX_X (41)
#define MAX_Y (23)


/* Saucer start position */
//	p->x = 10; // Left to right
//	p->y = 22; // Downwards
#define SAUCER_START_X (10)
#define SAUCER_START_Y (22)


struct Obstacle {
	int x;
	int y;
};


struct Level {
	int background;
	int monster;
	int obstacle;
    void (*monsterConstructor)(void);
    void (*monsterDestructor)(void);

	int (*Monster_isPos)(int x, int y);
	void (*Monster_getPos)(int * px, int * py);
	void (*Monster_move)(int * px, int * py, int * pPic);
	int nofObstacles;
	struct Obstacle * obstacles;
};


int canGoAt(int x, int y);
//void directionToSaucer(int * px, int * py);

void getSaucerPos(int * px, int * py);
// ...

// To coompensate for bad design/ new opportunities...
void setNofObstacles(int nofObstacles);