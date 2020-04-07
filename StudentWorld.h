#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_
#include "Actor.h"
#include "GameWorld.h"


class Studentworld :public GameWorld
{
public:
	Studentworld();
	~Studentworld();
	virtual int init();
	virtual int move();
	virtual void cleanUp();

private:
};

#endif