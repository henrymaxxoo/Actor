//Zhiheng Ma 
//Project#3 
// Feb 21, 2019 
#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_
#include <iostream>
#include "GameWorld.h"
#include <string>
#include <vector>
#include"Actor.h"

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp
class Actor;
class Wall;
class Penelope;
class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetPath);
	virtual ~StudentWorld();
    virtual int init();
    virtual int move();
    virtual void cleanUp();
	
	//accessor 
	void pick_vacc() { m_penelope->add_vacc(); }
	void pick_flame() { m_penelope->add_flame(); }
	void pick_mine() { m_penelope->add_mine(); }

	//helper
	std::string set_title();
	
	bool blocking_down(double x, double y, std::string other);
	bool blocking_up(double x, double y, std::string other);
	bool blocking_left(double x, double y, std::string other);
	bool blocking_right(double x, double y, std::string other);
	void remove_dead();
	bool check_overloap(double x1, double y1, std::string other) const;
	void to_next();
	void kill(double x1, double y1);
	void create_vomit(double x1, double y1);
	void create_landmine(double x1, double y1);
	void create_pit(double x1, double y1);
	void create_landmine_flame(double x1, double y1);
	void create_zombie(double x1, double x2);
	void fire(double x1, double x2);
	void damage(double x, double y);
	void infect(double x, double y);
	int Cloest_person(double x, double y);
	double cloest(double x1, double y1, string who);
	//return direction, x1,y1,who input, distance x,y output 
	int dirction_cloest(double x1, double y1, string who);
	
	
	
private:
	bool finished; 
	int level = 1;
	std::vector <Actor*> m_actor;
	Penelope* m_penelope;
	std::string levelFile;

};

#endif // STUDENTWORLD_H_
