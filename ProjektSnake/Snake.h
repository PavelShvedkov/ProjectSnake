#include "Array.h"

class Snake
{
public:
	Snake();
	void changeDirektion();
private:
	int length;
	Array coords;
	Array lastTurn;
	char direction;
};

