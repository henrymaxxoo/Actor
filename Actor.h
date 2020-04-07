#ifndef ACTOR_H_
#define ACTOR_H_
#include "StudentWorld.h"
#include"GraphObject.h"
/*
Penelope
? Dumb zombies
? Smart zombies
? Landmines
? Pits
? Flames
? Vomit
? Vaccine Goodies
? Gas can Goodies
? Landmine Goodies
? Walls
? Exits*/
class Actor:public GraphObject 
{
public:
	Actor();
	~Actor();
};


class Penelope: public Actor
{

};

class zombies : public Actor
{

};

class dumb_zombies : public zombies
{

};

class smart_zombies : public zombies
{

};

class Landmines : public Actor
{

};

class Pits : public Actor
{

};

class Flames : public Actor
{

};

class Vomit : public Actor
{

};

class Goodie: public Actor
{

};

class Vaccine_Goodies : public Goodie
{

};

class Gas_can_Goodies : public Goodie
{

};

class Landmine_Goodies : public Goodie
{

};

class Walls : public Actor
{

};

class Exits : public Actor
{

};

class citizens : public Actor
{

};

#endif