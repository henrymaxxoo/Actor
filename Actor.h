//Zhiheng Ma 
//Project#3 
// Feb 21, 2019 
#ifndef ACTOR_H_
#define ACTOR_H_
#include <iostream>
#include "GraphObject.h"
class StudentWorld; 
using namespace std;
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Actor : public GraphObject
{
public: 
	Actor(StudentWorld* world, int imageID, int startX, int startY,Direction dir)
		:GraphObject(imageID, startX, startY, dir)
	{
		sw = world;
	};

	virtual ~Actor() {};
	virtual void dosomething() = 0;
	virtual string get_name() = 0;
	virtual void get_infect() = 0;
	virtual bool alive() { return n_alive; }
	void set_die() { n_alive = false;  }
	StudentWorld* getworld() { return sw; }

private:
	StudentWorld* sw; 
	bool n_alive=true; 
};

class Penelope : public Actor
{
public: 
	Penelope( StudentWorld* world, int level_x, int level_y)
		: Actor(world, IID_PLAYER, SPRITE_WIDTH *level_x, SPRITE_HEIGHT * level_y, right)
	{};
	virtual void dosomething();
	virtual string get_name() { return "Penelope"; }
	virtual ~Penelope() {};
	void get_killed() { n_alive = false; }
   virtual void get_infect() { n_infected = true; }
	virtual bool alive() { return n_alive; }
	int show_infection() { return infected; }
	int show_vacc() { return vacc; }
	int show_flame() { return flame; }
	int show_mine() { return mine; }

	void add_vacc() { vacc++; }
	void add_flame() { flame += 5; }
	void add_mine() { mine += 2; }

private:
	bool n_alive = true, n_infected =false;
	int infected = 0, flame =0,vacc =0, mine =0; 
};

class Wall : public Actor
{
public:
	Wall(StudentWorld* world, int level_x, int level_y )
		: Actor(world, IID_WALL, SPRITE_WIDTH *level_x, SPRITE_HEIGHT * level_y, right)
	{};
	virtual string get_name() { return "Wall"; }
	virtual void dosomething() {};
	virtual void get_infect() {}
	virtual ~Wall() {};
private:
};

class Exit : public Actor
{
public:
	Exit(StudentWorld* world, int level_x, int level_y)
		: Actor(world, IID_EXIT, SPRITE_WIDTH *level_x, SPRITE_HEIGHT * level_y, right)
	{};
	virtual string get_name() { return "Exit"; }
	virtual void dosomething();
	virtual void get_infect() {}
private:
};

class Pit : public Actor
{
public:
	Pit(StudentWorld* world, int level_x, int level_y)
		: Actor(world, IID_PIT, SPRITE_WIDTH *level_x, SPRITE_HEIGHT * level_y, right)
	{};
	virtual string get_name() { return "Pit"; }
	virtual void dosomething();
	virtual void get_infect() {}
private:
};

class Flame : public Actor
{
public:
	Flame(StudentWorld* world, double level_x, double level_y)
		: Actor(world, IID_FLAME, level_x,  level_y, right)
	{}
	virtual string get_name() { return "Flame"; }
	virtual void dosomething();
	virtual void get_infect() {}
private:
	int ticks = 0;
};

class Vomit : public Actor
{
public:
	Vomit(StudentWorld* world, double level_x, double level_y)
		: Actor(world, IID_VOMIT, level_x,  level_y, right)
	{};
	virtual string get_name() { return "Vomit"; }
	virtual void dosomething();
	virtual void get_infect() {}
private:
	int ticks = 0;
};

class Vaccine_Goodie : public Actor
{
public:
	Vaccine_Goodie(StudentWorld* world, int level_x, int level_y)
		: Actor(world, IID_VACCINE_GOODIE, SPRITE_WIDTH *level_x, SPRITE_HEIGHT * level_y, right)
	{}
	virtual string get_name() { return "Vaccine_Goodie"; }
	virtual void dosomething();
	virtual void get_infect() {}
private:
};

class Gas_Can_Goodie : public Actor
{
public:
	Gas_Can_Goodie(StudentWorld* world, int level_x, int level_y)
		: Actor(world, IID_GAS_CAN_GOODIE, SPRITE_WIDTH *level_x, SPRITE_HEIGHT * level_y, right)
	{}
	virtual string get_name() { return "Gas_Can_Goodie"; }
	virtual void dosomething();
	virtual void get_infect() {}
private:
};

class Landmine_Goodie : public Actor
{
public:
	Landmine_Goodie(StudentWorld* world, int level_x, int level_y)
		: Actor(world, IID_LANDMINE_GOODIE, SPRITE_WIDTH *level_x, SPRITE_HEIGHT * level_y, right)
	{}
	virtual string get_name() { return "Landmine_Goodie"; }
	virtual void dosomething();
	virtual void get_infect() {}
private:
};

class Landmine : public Actor
{
public:
	Landmine(StudentWorld* world, double level_x, double level_y)
		: Actor(world, IID_LANDMINE, level_x, level_y, right)
	{};
	virtual string get_name() { return "Landmine"; }
	virtual void dosomething();
	virtual void get_infect() {}
private:
	int safety = 30; 
	bool active = false; 
};

class Zombie : public Actor
{
public:
	Zombie(StudentWorld* world, int level_x, int level_y)
		: Actor(world, IID_ZOMBIE, SPRITE_WIDTH *level_x, SPRITE_HEIGHT * level_y, right)
	{}
	virtual string get_name() = 0;
	virtual void dosomething()=0;
	virtual void get_infect() = 0;
private:

};

class smart_zombie : public Zombie
{
public:
	smart_zombie(StudentWorld* world, int level_x, int level_y)
		:Zombie(world, level_x, level_y)
	{};
	virtual string get_name() { return "Smart_Zombie"; }
	virtual void dosomething();
	virtual void get_infect() {}
private:
	int step = 0;
	int movement = 0, dir = 0;
};

class dump_zombie : public Zombie
{
public:
	dump_zombie(StudentWorld* world, int level_x, int level_y)
		:Zombie(world, level_x, level_y)
	{};
	virtual string get_name() { return "Dump_Zombie"; }
	virtual void dosomething();
	virtual void get_infect() {}
private:
	int step = 0; 
	int movement = 0, dir=0;
};

class citizen : public Actor
{
public:
	citizen(StudentWorld* world, int level_x, int level_y)
		: Actor(world, IID_CITIZEN, SPRITE_WIDTH *level_x, SPRITE_HEIGHT * level_y, right)
	{};
	virtual string get_name() { return "Citizen"; }
	virtual void dosomething();
	virtual void get_infect() { c_infected = true; }
private:
	bool c_alive = true, c_infected = false;
	int c_infection = 0, step=0;
};
#endif // ACTOR_H_
