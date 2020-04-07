//Zhiheng Ma 
//Project#3 
// Feb 21, 2019 
#include "StudentWorld.h"
#include "GameConstants.h"
#include "Level.h"
#include "Actor.h"
#include <string>
#include <cmath>
#include<sstream>

using namespace std;


GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
}

StudentWorld::~StudentWorld()
{
	this->cleanUp();
}


//////////////////////////////////////////////////////init///////////////////////////////////////////////////////
int StudentWorld::init()
{
	finished = false; 
	
	if (level < 10)
	{
		levelFile = "level0" + to_string(level);
		levelFile += ".txt";
	}

	else
	{
		levelFile = "level" + to_string(level);
		levelFile += ".txt";
	}

	Level lev(assetPath());
	Level::LoadResult result = lev.loadLevel(levelFile);
	if (result == Level::load_fail_file_not_found || level == 99)
		return GWSTATUS_PLAYER_WON;
	else if (result == Level::load_fail_bad_format)
		cerr << "Your level was improperly formatted" << endl;

	else if (result == Level::load_success)
	{
		
		for (int i = 0; i < LEVEL_WIDTH; i++)
		{
			for (int j = 0; j < LEVEL_HEIGHT; j++)
			{
				Level::MazeEntry ge = lev.getContentsOf(i, j); 
				switch (ge) 
				{
				case Level::empty:
					break;

				case Level::smart_zombie:
				{
					Actor *a = new smart_zombie(this, i, j);
					m_actor.push_back(a);
					break;
				}

				case Level::dumb_zombie:
				{
					Actor *a = new dump_zombie(this, i, j);
					m_actor.push_back(a);
					break;
				}

				case Level::player:
				{
					m_penelope = new Penelope(this, i, j);
					m_actor.push_back(m_penelope);
					break;
				}

				case Level::exit:
				{
					Actor *a = new Exit(this, i, j);
					m_actor.push_back(a);
					break;
				}

				case Level::wall:
				{
					Actor *b = new Wall(this, i, j);
					m_actor.push_back(b);
					break;
				}

				case Level::pit:
				{
					Actor *b = new Pit(this, i, j);
					m_actor.push_back(b);
					break;
				}
				
				case Level::citizen:
				{
					Actor *d = new citizen(this, i, j); 
					m_actor.push_back(d);
					break;
				}
				
				case Level::gas_can_goodie:
				{
					Actor *e = new Gas_Can_Goodie(this, i, j);
					m_actor.push_back(e);
					break;
				}

				case Level::landmine_goodie:
				{
					Actor *f = new Landmine_Goodie(this, i, j);
					m_actor.push_back(f);
					break;
				}

				case Level::vaccine_goodie:
				{
					Actor *d = new Vaccine_Goodie(this, i, j);
					m_actor.push_back(d);
					break;
				}
				}
			}
		}

	}
    return GWSTATUS_CONTINUE_GAME;
}

//////////////////////////////////////////////////////////////move///////////////////////////////////////////////////
int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
	for (int i = 0; i < m_actor.size(); i++)
	{
		if (m_actor[i]->alive())
		{
			m_actor[i]->dosomething();
		}

		if (!(m_penelope->alive()))
		{
			decLives();
		    return GWSTATUS_PLAYER_DIED;
		}

		if (finished)
		{
			playSound(SOUND_LEVEL_FINISHED);
			level++;
			return GWSTATUS_FINISHED_LEVEL;
		}
		
	}
	remove_dead(); 
	setGameStatText(set_title());

	return GWSTATUS_CONTINUE_GAME;
   
}

//////////////////////////////////////////////////clean up/////////////////////////////////////////////////////
void StudentWorld::cleanUp()
{
	for (int i = 0; i < m_actor.size(); i++)
	{
		delete m_actor[i];
		m_actor.erase(m_actor.begin() + i);
		i--;
	}
}

/////////////////////////////////////////////////helper/////////////////////////////////////////////////////


bool StudentWorld::blocking_down(double x, double y, string other)
{
	for (int i = 0; i < m_actor.size(); i++)
	{
		if (m_actor[i]->get_name() == other)
		{
			if (y>=m_actor[i]->getY() && y<= (m_actor[i]->getY() + SPRITE_WIDTH - 1))
			{
				if (x <= (m_actor[i]->getX() + SPRITE_WIDTH - 1) && x >= (m_actor[i]->getX() - SPRITE_WIDTH + 1))
					return true;
			}
		}
	}
	return false; 
}
bool StudentWorld::blocking_up(double x, double y, string other)
{
	for (int i = 0; i < m_actor.size(); i++)
	{
		if (m_actor[i]->get_name() == other)
		{
			if (y + SPRITE_HEIGHT - 1 <= (m_actor[i]->getY()+SPRITE_HEIGHT-1)&& y + SPRITE_HEIGHT - 1 >= (m_actor[i]->getY()))
			{
				if (x <= (m_actor[i]->getX() + SPRITE_WIDTH - 1) && x >= (m_actor[i]->getX() - SPRITE_WIDTH + 1))
					return true;
			}
		}
	}
	return false;
}
bool StudentWorld::blocking_left(double x, double y, string other)
{
	for (int i = 0; i < m_actor.size(); i++)
	{
		if (m_actor[i]->get_name() == other)
		{
			if (x >= m_actor[i]->getX() && x <= (m_actor[i]->getX() + SPRITE_WIDTH - 1))
			{
				if (y <= (m_actor[i]->getY() + SPRITE_HEIGHT - 1) && y >= (m_actor[i]->getY() - SPRITE_HEIGHT + 1))
					return true;
			}
		}
	}
	return false;
}
bool StudentWorld::blocking_right(double x, double y, string other)
{
	for (int i = 0; i < m_actor.size(); i++)
	{
		if (m_actor[i]->get_name() == other)
		{
			if (x + SPRITE_WIDTH - 1 <= (m_actor[i]->getX() + SPRITE_WIDTH - 1) && x + SPRITE_WIDTH - 1 >= (m_actor[i]->getX()))
			{
				if (y <= (m_actor[i]->getY() + SPRITE_HEIGHT - 1) && y >= (m_actor[i]->getY() - SPRITE_HEIGHT + 1))
					return true;
			}
		}
	}
	return false;
}

bool StudentWorld::check_overloap(double x1, double y1, string other) const
{
	double x2=0, y2=0;
	for (int i = 0; i < m_actor.size(); i++)
	{
		if (m_actor[i]->get_name() == other)
		{
			 x2 = m_actor[i]->getX();
			 y2 = m_actor[i]->getY();

			 double dx = x1 - x2, dy = y1 - y2;
			 if (((dx * dx) + (dy * dy)) < 100.00)
				 return true;
		}
	}
	return false; 
}

string StudentWorld::set_title()
{
    stringstream as; 
	as  <<"Score:	"<< to_string(getScore()) 
		<<"  Level: "<< to_string(getLevel())
		<< "  Lives: "<<to_string(getLives())
		<< "  Vaccines: "<< to_string(m_penelope->show_vacc())
		<< "  Flames: "<< to_string(m_penelope->show_flame())
		<< "  Mines: " << to_string(m_penelope->show_mine())
		<< "  Infected: "<< to_string(m_penelope->show_infection());
	string b =as.str();
	return b;

}

void StudentWorld::to_next()
{
	for (int i = 0; i < m_actor.size(); i++)
	{
		if (m_actor[i]->get_name() == "Citizen")
		{
			return;
		}
	}

	finished = true; 
}

void StudentWorld::kill(double x1, double y1)
{
	for (int i = 0; i < m_actor.size(); i++)
	{
		if (m_actor[i]->get_name() == "Citizen")
		{
			double x2 = m_actor[i]->getX();
			double y2 = m_actor[i]->getY();

			double dx = x1 - x2, dy = y1 - y2;
			if (((dx * dx) + (dy * dy)) < 100.00)
			{
				m_actor[i]->set_die();
				return;
			}
		}
	}
}

void StudentWorld::remove_dead()
{
	for (int i = 0; i < m_actor.size(); i++)
	{
		if (!m_actor[i]->alive())
		{
			delete m_actor[i];
			m_actor.erase(m_actor.begin() + i);
			i--;
		}
	}
}

void StudentWorld::create_vomit(double x1, double y1)
{
	Actor* a = new Vomit(this, x1, y1); 
	m_actor.push_back(a); 
}

void StudentWorld::fire(double x1, double x2)
{
	if (m_penelope->show_flame() == 0)
	{
		return;
	}
	else
	{
		playSound(SOUND_PLAYER_FIRE);
		Actor* a = new Flame(this, x1, x2);
		m_actor.push_back(a); 
	}
}

void StudentWorld::damage(double x, double y)
{
	double x2, y2;
	for (int i = 0; i < m_actor.size(); i++)
	{
			x2 = m_actor[i]->getX();
			y2 = m_actor[i]->getY();
			double dx = x - x2, dy = y - y2;
			if (((dx * dx) + (dy * dy)) < 100.00)
			{
				if (m_actor[i]->get_name() == "Vaccine_Goodie" || m_actor[i]->get_name() == "Gas_Can_Goodie" ||
					m_actor[i]->get_name() == "Landmine_Goodie"  )
				{
					m_actor[i]->set_die();
				}

				if (m_actor[i]->get_name() == "Smart_Zombie")
				{
					increaseScore(2000);
					playSound(SOUND_ZOMBIE_DIE);
					m_actor[i]->set_die();
				}

				if (m_actor[i]->get_name() == "Dump_Zombie")
				{
					int chance = rand() % +11;
					increaseScore(1000);
					playSound(SOUND_ZOMBIE_DIE);
					m_actor[i]->set_die();
					if (chance == 1)
					{
						int c = x / 16, b = y / 16;
						Actor* a = new Vaccine_Goodie(this, c, b); 
						m_actor.push_back(a);
					}
				}

				if (m_actor[i]->get_name() == "Citizen")
				{
					increaseScore(-1000);
					playSound(SOUND_CITIZEN_DIE);
					m_actor[i]->set_die();
				}

				if (m_actor[i]->get_name() == "Penelope")
				{
					playSound(SOUND_PLAYER_DIE);
					m_penelope->get_killed();
				}
			}
		
	}
}

void StudentWorld::infect(double x, double y)
{
	if (check_overloap(x,y,"Penelope"))
	m_penelope->get_infect(); 

	double x2 = 0, y2 = 0;
	for (int i = 0; i < m_actor.size(); i++)
	{
		if (m_actor[i]->get_name() == "Citizen")
		{
			x2 = m_actor[i]->getX();
			y2 = m_actor[i]->getY();

			double dx = x - x2, dy = y - y2;
			if (((dx * dx) + (dy * dy)) < 100.00)
				m_actor[i]->get_infect(); 
		}
	}
}

void StudentWorld::create_landmine(double x, double y)
{

	Actor* a = new Landmine (this, x, y);
	m_actor.push_back(a);
}

void StudentWorld::create_pit(double x1, double y1)
{
	int e = x1 / 16;
	int b = y1 / 16;
	Actor* a = new Pit(this, e, b);
	m_actor.push_back(a);
}

void StudentWorld::create_landmine_flame(double x1, double y1)
{
	Actor* a = new Flame(this, x1-16, y1);
	Actor* b = new Flame(this, x1+16, y1);
	Actor* c = new Flame(this, x1, y1-16);
	Actor* d = new Flame(this, x1, y1+16);
	Actor* e = new Flame(this, x1+16, y1+16);
	Actor* f = new Flame(this, x1-16, y1-16);
	Actor* g = new Flame(this, x1+16, y1-16);
	Actor* h = new Flame(this, x1-16, y1+16);
	Actor* j = new Flame(this, x1, y1);
	m_actor.push_back(a);
	m_actor.push_back(b);
	m_actor.push_back(c);
	m_actor.push_back(d);
	m_actor.push_back(e);
	m_actor.push_back(f);
	m_actor.push_back(g);
	m_actor.push_back(h);
	m_actor.push_back(j);
}

int StudentWorld::Cloest_person(double x, double y)
{
	// return 0 left, 1 right, 2 up, 3 down, 4 is random
	//result is the piex 
	double min = 6400,x2,y2,dx,dy,d;
	int location=4;

	for (int i = 0; i < m_actor.size(); i++)
	{
		if (m_actor[i]->get_name() == "Citizen" || m_actor[i]->get_name() == "Penelope")
		{
			x2 = m_actor[i]->getX();
			y2 = m_actor[i]->getY();
			dx = x - x2;
			dy = y - y2;
			d = (dx*dx) + (dy*dy);
			if ( d<= min)
			{
				min = d;

				if (dx > 0)
					location = 0;
				else if (dx < 0)
					location = 1;
				else if (dy < 0)
					location = 2;
				else if (dy > 0)
					location = 3;
				else
					location = rand() % 3 + 2;
			}
		}
	}
	if (location == 4)
	{
		location = rand() % +4;
	}
	return location;
}

void StudentWorld::create_zombie(double x1, double x2)
{
	int a = x1 / 16, b = x2 / 16, c=rand()%+11; 

	if (c <= 7)
	{
		Actor* k = new dump_zombie(this, a, b); 
		m_actor.push_back(k);
		return;
	}

	else
	{
		Actor* l = new smart_zombie(this, a, b);
		m_actor.push_back(l);
		return;
	}
}

double StudentWorld::cloest(double x1, double y1, string who)
{
	double min = 256*256, x2=0, y2=0, dx, dy, d;
	int location = 0;

	for (int i = 0; i < m_actor.size(); i++)
	{
		if (m_actor[i]->get_name() == who)
		{
			x2 = m_actor[i]->getX();
			y2 = m_actor[i]->getY();
			dx = x1 - x2;
			dy = y1 - y2;
			d = (dx*dx) + (dy*dy);
			if (d <= min)
			{	
				min = d;
			}
		}
	}
	return sqrt(min);
}

int StudentWorld::dirction_cloest(double x1, double y1, string who)
{
	double x2, y2, dx, dy;
	for (int i = 0; i < m_actor.size(); i++)
	{
		if (m_actor[i]->get_name() == who)
		{
			x2 = m_actor[i]->getX();
			y2 = m_actor[i]->getY();
			dx = x1 - x2;
			dy = y1 - y2;

			if (dx > 0)
				return 0;
			else if (dx < 0)
				return 1;
			else if (dy < 0)
				return 2;
			else if (dy > 0)
				return 3;
		}
	}
}