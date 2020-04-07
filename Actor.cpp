//Zhiheng Ma 
//Project#3 
// Feb 21, 2019 
#include "Actor.h"
#include "StudentWorld.h"
#include <stdlib.h>  
#include <time.h> 

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
void Penelope::dosomething()
{
	if (!alive())
		return;
	StudentWorld* d = getworld();

	if (n_infected)
	{
		infected++; 
	}

	if (infected > 500)
	{
		n_alive = false; 
		d->playSound(SOUND_PLAYER_DIE);
		return;
	}

	int key; 

	if (d->getKey(key))
	{
		if (key == KEY_PRESS_SPACE)
		{
			if (flame == 0)
				return; 
			if (flame > 0)
				flame--; 

			for (int i = 1; i < 10; i++)
			{
				if (getDirection() == left)
				{
					
					if(d->check_overloap(getX() - i * SPRITE_WIDTH, getY(), "Wall")
						|| d->check_overloap(getX() - i * SPRITE_WIDTH, getY(), "Exit"))
					{
						break;
					}
					d->fire(getX() - i * SPRITE_WIDTH, getY());
				}

				if (getDirection() == right)
				{
					
					if (d->check_overloap(getX() + i * SPRITE_WIDTH, getY(), "Wall")
						|| d->check_overloap(getX() + i * SPRITE_WIDTH, getY(), "Exit"))
						break;
					d->fire(getX() + i * SPRITE_WIDTH, getY());
				}

				if (getDirection() == up)
				{
					if (d->check_overloap(getX(), getY() + i *SPRITE_HEIGHT, "Wall")
						|| d->check_overloap(getX(),  getY() + i * SPRITE_HEIGHT, "Exit"))
						break;

					d->fire(getX(), getY() + i * SPRITE_HEIGHT);
				}

				if (getDirection() == down)
				{
					if (d->check_overloap(getX(), getY() - i * SPRITE_HEIGHT, "Wall")
						|| d->check_overloap(getX(), getY() - i * SPRITE_HEIGHT, "Exit"))
						break;

					d->fire(getX(), getY() - i * SPRITE_HEIGHT);
					
				}
			}
		}
		if (key == KEY_PRESS_ENTER)
		{
			
			if (vacc <= 0)
				return; 
			else
			{
				vacc--;
				n_infected = false;
			}
		}

		if (key == KEY_PRESS_TAB)
		{
			if (mine == 0)
				return;
			if (mine > 0)
			{
				mine--;
				d->create_landmine(getX(), getY()); 
			}
		}

		if (key == KEY_PRESS_LEFT)
		{
			setDirection(left);
			if (!d->blocking_left(getX()-4, getY(), "Wall") && !d->blocking_left(getX()-4, getY(), "Dump_Zombie")
				&& !d->blocking_left(getX()-4, getY(), "Smart_Zombie") && !d->blocking_left(getX()-4, getY(), "Citizen"))
			{
				moveTo(getX() - 4, getY());
			}
		}

		if (key == KEY_PRESS_RIGHT)
		{
			setDirection(right);
			if (!d->blocking_right(getX() + 4, getY(), "Wall") && !d->blocking_right(getX() + 4, getY(), "Dump_Zombie")
				&& !d->blocking_right(getX() + 4, getY(), "Smart_Zombie") && !d->blocking_right(getX() + 4, getY(), "Citizen"))
			{
				moveTo(getX() + 4, getY());
			}
		}

		if (key == KEY_PRESS_UP)
		{
			setDirection(up);
			if (!d->blocking_up(getX(), getY() + 4, "Wall") && !d->blocking_up(getX(), getY() + 4, "Dump_Zombie")
				&& !d->blocking_up(getX(), getY() + 4, "Smart_Zombie") && !d->blocking_up(getX(), getY() + 4, "Citizen"))
			{
				moveTo(getX(), getY() + 4);
			}
		}

		if (key == KEY_PRESS_DOWN)
		{
			setDirection(down);
			if(!d->blocking_down(getX(),getY()-4,"Wall") && !d->blocking_down(getX(), getY() - 4, "Dump_Zombie")
				&& !d->blocking_down(getX(), getY() - 4, "Smart_Zombie") &&!d->blocking_down(getX(), getY() - 4, "Citizen"))
			{
				moveTo(getX(), getY() - 4);
			}
		}
	}
}

void Exit::dosomething()
{
	StudentWorld* d = getworld();
	if (d->check_overloap(getX(), getY(), "Citizen"))
	{
		d->kill(getX(), getY());
		d->increaseScore(500);
		d->playSound(SOUND_CITIZEN_SAVED);
	}

	if (d->check_overloap(getX(), getY(), "Penelope"))
	{
		d->to_next();
	}
}

void Pit::dosomething()
{
	StudentWorld* d = getworld();
	if (d->check_overloap(getX(), getY(), "Penelope") || d->check_overloap(getX(), getY(), "Citizen")
		|| d->check_overloap(getX(), getY(), "Dump_Zombie") || d->check_overloap(getX(), getY(), "Smart_Zombie"))
	{
		d->damage(getX(),getY()); 
	}
}

void Flame::dosomething()
{
	ticks++;
	if (!alive())
		return;

	if (ticks == 2)
	{
		set_die();
		return;
	}

	StudentWorld* d = getworld();
	d->damage(getX(),getY()); 

}

void Vomit::dosomething()
{
	ticks++;
	if (!alive())
		return;

	if (ticks == 2)
	{
		set_die();
		return;
	}

	StudentWorld* d = getworld();

	d->infect(getX(), getY());

}

void Vaccine_Goodie::dosomething()
{
	if (!alive())
		return; 
	StudentWorld* d = getworld();
	if (d->check_overloap(getX(), getY(), "Penelope"))
	{
		d->increaseScore(50);
		set_die();
		d->playSound(SOUND_GOT_GOODIE);
		d->pick_vacc();
	}
}

void Gas_Can_Goodie::dosomething()
{
	if (!alive())
		return;
	StudentWorld* d = getworld();
	if (d->check_overloap(getX(), getY(), "Penelope"))
	{
		d->increaseScore(50);
		set_die();
		d->playSound(SOUND_GOT_GOODIE);
		d->pick_flame();
	}
}

void Landmine_Goodie::dosomething()
{
	if (!alive())
		return;
	StudentWorld* d = getworld();
	if (d->check_overloap(getX(), getY(), "Penelope"))
	{
		d->increaseScore(50);
		set_die();
		d->playSound(SOUND_GOT_GOODIE);
		d->pick_mine();
	}
}

void Landmine::dosomething()
{
	StudentWorld* d = getworld();
	if (!alive())
		return; 
	safety--; 
	if (active == false)
	{
		if (safety == 0)
			active = true; 
		return;
	}

	if (d->check_overloap(getX(), getY(), "Penelope") || d->check_overloap(getX(), getY(), "Citizen")
		|| d->check_overloap(getX(), getY(), "Dump_Zombie") || d->check_overloap(getX(), getY(), "Smart_Zombie"))
	{
		Actor::set_die();
		d->playSound(SOUND_LANDMINE_EXPLODE);
	    d->create_landmine_flame(getX(), getY());
		d->create_pit(getX(), getY());
	}
}

void dump_zombie::dosomething()
{
	step++;
	if (!alive())
		return;

	if (step == 2)
	{
		step = 0;
		return;
	}
	StudentWorld* d = getworld();
	int chance = rand() % +3;
	if (getDirection() == left)
	{
		if (d->check_overloap(getX() - SPRITE_WIDTH, getY(), "Penelope") || d->check_overloap(getX() - SPRITE_WIDTH, getY(), "Citizen"))
		{
			if (chance == 1)
			{
				d->create_vomit(getX() - SPRITE_WIDTH, getY());
				d->playSound(SOUND_ZOMBIE_VOMIT);
				return;
			}
		}
	}

	if (getDirection() == right)
	{
		if (d->check_overloap(getX() + SPRITE_WIDTH, getY(), "Penelope") || d->check_overloap(getX() + SPRITE_WIDTH, getY(), "Citizen"))
		{
			if (chance == 1)
			{
				d->create_vomit(getX() + SPRITE_WIDTH, getY());
				d->playSound(SOUND_ZOMBIE_VOMIT);
				return;
			}
		}
	}

	if (getDirection() == up)
	{
		if (d->check_overloap(getX(), getY()+SPRITE_HEIGHT, "Penelope") || d->check_overloap(getX() , getY()+SPRITE_HEIGHT, "Citizen"))
		{
			if (chance == 1)
			{
				d->create_vomit(getX(), getY() + SPRITE_HEIGHT);
				d->playSound(SOUND_ZOMBIE_VOMIT);
				return;
			}
		}
	}

	if (getDirection() == down)
	{
		if (d->check_overloap(getX(), getY() - SPRITE_HEIGHT, "Penelope") || d->check_overloap(getX(), getY() - SPRITE_HEIGHT, "Citizen"))
		{
			if (chance == 1)
			{
				d->create_vomit(getX(), getY() - SPRITE_HEIGHT);
				d->playSound(SOUND_ZOMBIE_VOMIT);
				return;
			}
		}
	}
	
	if (movement == 0)
	{
		movement = rand() % 10 +3;
		 dir = rand() % 4;
	}
	switch (dir)
	{
	case 0:
	{
		setDirection(left);
		if (!d->blocking_left(getX() - 1, getY(), "Wall") && !d->blocking_left(getX() - 1, getY(), "Dump_Zombie")
			&& !d->blocking_left(getX() - 1, getY(), "Smart_Zombie") && !d->blocking_left(getX() - 1, getY(), "Citizen")
			&& !d->blocking_left(getX() - 1, getY(), "Penelope"))
		{
			moveTo(getX() - 1, getY());
			movement--;
		}

		else
		{
			movement = 0;
		}
		break;
	}
	case 1:
	{
		setDirection(right);
		if (!d->blocking_right(getX() + 1, getY(), "Wall") && !d->blocking_right(getX() + 1, getY(), "Smart_Zombie")
			&& !d->blocking_right(getX() + 1, getY(), "Dump_Zombie") && !d->blocking_right(getX() + 1, getY(), "Citizen")
			&& !d->blocking_right(getX() + 1, getY(), "Penelope"))
		{
			moveTo(getX() + 1, getY());
			movement--;
		}

		else
		{
			movement = 0;
		}
		break;
	}

	case 2:
	{
		setDirection(up);
		if (!d->blocking_up(getX(), getY()+1, "Wall") && !d->blocking_up(getX(), getY()+1, "Smart_Zombie")
			&& !d->blocking_up(getX(), getY()+1, "Dump_Zombie") && !d->blocking_up(getX(), getY()+1, "Citizen")
			&& !d->blocking_up(getX(), getY() + 1, "Penelope"))
		{
			moveTo(getX(), getY()+1);
			movement--;
		}

		else
		{
			movement = 0;
		}
		break;
	}

	case 3:
	{
		setDirection(down);
		if (!d->blocking_down(getX(), getY()-1, "Wall") && !d->blocking_down(getX() , getY()-1, "Smart_Zombie")
			&& !d->blocking_down(getX(), getY()-1, "Dump_Zombie") && !d->blocking_down(getX(), getY()-1, "Citizen")
			&& !d->blocking_down(getX(), getY() - 1, "Penelope"))
		{
			moveTo(getX(), getY()-1);
			movement--;
		}

		else
		{
			movement = 0;
		}
		break;
	}
	}
}

void smart_zombie::dosomething()
{
	step++;
	if (!alive())
		return;

	if (step == 2)
	{
		step = 0;
		return;
	}
	StudentWorld* d = getworld();
	int chance = rand() % +3;
	if (getDirection() == left)
	{
		if (d->check_overloap(getX() - SPRITE_WIDTH, getY(), "Penelope") || d->check_overloap(getX() - SPRITE_WIDTH, getY(), "Citizen"))
		{
			if (chance == 1)
			{
				d->create_vomit(getX() - SPRITE_WIDTH, getY());
				d->playSound(SOUND_ZOMBIE_VOMIT);
				return;
			}
		}
	}

	if (getDirection() == right)
	{
		if (d->check_overloap(getX() + SPRITE_WIDTH, getY(), "Penelope") || d->check_overloap(getX() + SPRITE_WIDTH, getY(), "Citizen"))
		{
			if (chance == 1)
			{
				d->create_vomit(getX() + SPRITE_WIDTH, getY());
				d->playSound(SOUND_ZOMBIE_VOMIT);
				return;
			}
		}
	}

	if (getDirection() == up)
	{
		if (d->check_overloap(getX(), getY() + SPRITE_HEIGHT, "Penelope") || d->check_overloap(getX(), getY() + SPRITE_HEIGHT, "Citizen"))
		{
			if (chance == 1)
			{
				d->create_vomit(getX(), getY() + SPRITE_HEIGHT);
				d->playSound(SOUND_ZOMBIE_VOMIT);
				return;
			}
		}
	}

	if (getDirection() == down)
	{
		if (d->check_overloap(getX(), getY() - SPRITE_HEIGHT, "Penelope") || d->check_overloap(getX(), getY() - SPRITE_HEIGHT, "Citizen"))
		{
			if (chance == 1)
			{
				d->create_vomit(getX(), getY() - SPRITE_HEIGHT);
				d->playSound(SOUND_ZOMBIE_VOMIT);
				return;
			}
		}
	}

	if (movement == 0)
	{
		movement = rand() % 10 + 3;
	}
	
	dir = d->Cloest_person(getX(), getY());
	
	switch (dir)
	{
	case 0:
	{
		setDirection(left);
		if (!d->blocking_left(getX() - 1, getY(), "Wall") && !d->blocking_left(getX() - 1, getY(), "Dump_Zombie")
			&& !d->blocking_left(getX() - 1, getY(), "Smart_Zombie") && !d->blocking_left(getX() - 1, getY(), "Citizen")
			&& !d->blocking_left(getX() - 1, getY(), "Penelope"))
		{
			moveTo(getX() - 1, getY());
			movement--;
		}

		else
		{
			movement = 0;
		}
		break;
	}
	case 1:
	{
		setDirection(right);
		if (!d->blocking_right(getX() + 1, getY(), "Wall") && !d->blocking_right(getX() + 1, getY(), "Smart_Zombie")
			&& !d->blocking_right(getX() + 1, getY(), "Dump_Zombie") && !d->blocking_right(getX() + 1, getY(), "Citizen")
			&& !d->blocking_right(getX() + 1, getY(), "Penelope"))
		{
			moveTo(getX() + 1, getY());
			movement--;
		}

		else
		{
			movement = 0;
		}
		break;
	}

	case 2:
	{
		setDirection(up);
		if (!d->blocking_up(getX(), getY() + 1, "Wall") && !d->blocking_up(getX(), getY() + 1, "Smart_Zombie")
			&& !d->blocking_up(getX(), getY() + 1, "Dump_Zombie") && !d->blocking_up(getX(), getY() + 1, "Citizen")
			&& !d->blocking_up(getX(), getY()+1, "Penelope"))
		{
			moveTo(getX(), getY() + 1);
			movement--;
		}

		else
		{
			movement = 0;
		}
		break;
	}

	case 3:
	{
		setDirection(down);
		if (!d->blocking_down(getX(), getY() - 1, "Wall") && !d->blocking_down(getX(), getY() - 1, "Smart_Zombie")
			&& !d->blocking_down(getX(), getY() - 1, "Dump_Zombie") && !d->blocking_down(getX(), getY() - 1, "Citizen")
			&& !d->blocking_down(getX() , getY()-1, "Penelope"))
		{
			moveTo(getX(), getY() - 1);
			movement--;
		}

		else
		{
			movement = 0;
		}
		break;
	}
	}
}
	
void citizen::dosomething()
{
	if (!alive())
		return;

	StudentWorld* d = getworld();

	if (c_infected)
	{
		c_infection++;
	}

	if (c_infection > 500)
	{
		c_infection = 0;
		c_infected = false; 
		set_die(); 
		d->playSound(SOUND_ZOMBIE_BORN);
		d->increaseScore(-1000);
		d->create_zombie(getX(), getY());
		return;
	}

	step++;

	if (step == 2)
	{
		step = 0;
		return;
	}

	double  dist_p, dist_z1, dist_z2, dist_z = 0;
	int direction;

	dist_z1 = d->cloest(getX(), getY(), "Dump_Zombie");
	dist_z2 = d->cloest(getX(), getY(), "Smart_Zombie");
	dist_p = d->cloest(getX(), getY(), "Penelope");

	if (dist_z1 < dist_z2)
		dist_z = dist_z1;
	else
		dist_z = dist_z2;

	if (dist_p < dist_z || dist_z == 0)
	{
		if (dist_p <= 80)
		{
			direction = d->dirction_cloest(getX(), getY(), "Penelope");

			switch (direction)
			{
			case 0:
			{
				setDirection(left);
				if (!d->blocking_left(getX() - 2, getY(), "Wall") && !d->blocking_left(getX() - 2, getY(), "Dump_Zombie")
					&& !d->blocking_left(getX() - 2, getY(), "Smart_Zombie") && !d->blocking_left(getX() - 2, getY(), "Citizen")
					&& !d->blocking_left(getX() - 2, getY(), "Penelope"))
				{
					moveTo(getX() - 2, getY());
				}
				break;
			}
			case 1:
			{
				setDirection(right);
				if (!d->blocking_right(getX() + 2, getY(), "Wall") && !d->blocking_right(getX() + 2, getY(), "Smart_Zombie")
					&& !d->blocking_right(getX() + 2, getY(), "Dump_Zombie") && !d->blocking_right(getX() + 2, getY(), "Citizen")
					&& !d->blocking_right(getX() - 2, getY(), "Penelope"))
				{
					moveTo(getX() + 2, getY());
				}
				break;
			}
			case 2:
			{
				setDirection(up);
				if (!d->blocking_up(getX(), getY() + 2, "Wall") && !d->blocking_up(getX(), getY() + 2, "Smart_Zombie")
					&& !d->blocking_up(getX(), getY() + 2, "Dump_Zombie") && !d->blocking_up(getX(), getY() + 2, "Citizen")
					&& !d->blocking_up(getX() - 2, getY(), "Penelope"))
				{
					moveTo(getX(), getY() + 2);
				}
				break;
			}

			case 3:
			{
				setDirection(down);
				if (!d->blocking_down(getX(), getY() - 2, "Wall") && !d->blocking_down(getX(), getY() - 2, "Smart_Zombie")
					&& !d->blocking_down(getX(), getY() - 2, "Dump_Zombie") && !d->blocking_down(getX(), getY() - 2, "Citizen")
					&& !d->blocking_down(getX() - 2, getY(), "Penelope"))
				{
					moveTo(getX(), getY() - 2);
				}
				break;
			}

			return;
			}
		}
	}
	else if (dist_z<dist_p)
	{ 
		if (dist_z <= 80)
		{
			if (dist_z1 < dist_z2)
				direction = d->dirction_cloest(getX(), getY(), "Dump_Zombie");

			else
				direction = d->dirction_cloest(getX(), getY(), "Smart_Zombie");

			switch (direction)
			{
			case 1:
			{
				setDirection(left);
				if (!d->blocking_left(getX() - 2, getY(), "Wall") && !d->blocking_left(getX() - 2, getY(), "Dump_Zombie")
					&& !d->blocking_left(getX() - 2, getY(), "Smart_Zombie") && !d->blocking_left(getX() - 2, getY(), "Citizen")
					&& !d->blocking_left(getX() - 2, getY(), "Penelope"))
				{
					moveTo(getX() - 2, getY());
				}
				break;
			}
			case 0:
			{
				setDirection(right);
				if (!d->blocking_right(getX() + 2, getY(), "Wall") && !d->blocking_right(getX() + 2, getY(), "Smart_Zombie")
					&& !d->blocking_right(getX() + 2, getY(), "Dump_Zombie") && !d->blocking_right(getX() + 2, getY(), "Citizen")
					&& !d->blocking_right(getX() - 2, getY(), "Penelope"))
				{
					moveTo(getX() + 2, getY());
				}
				break;
			}
			case 3:
			{
				setDirection(up);
				if (!d->blocking_up(getX(), getY() + 2, "Wall") && !d->blocking_up(getX(), getY() + 2, "Smart_Zombie")
					&& !d->blocking_up(getX(), getY() + 2, "Dump_Zombie") && !d->blocking_up(getX(), getY() + 2, "Citizen")
					&& !d->blocking_up(getX() - 2, getY(), "Penelope"))
				{
					moveTo(getX(), getY() + 2);
				}
				break;
			}

			case 2:
			{
				setDirection(down);
				if (!d->blocking_down(getX(), getY() - 2, "Wall") && !d->blocking_down(getX(), getY() - 2, "Smart_Zombie")
					&& !d->blocking_down(getX(), getY() - 2, "Dump_Zombie") && !d->blocking_down(getX(), getY() - 2, "Citizen")
					&& !d->blocking_down(getX() - 2, getY(), "Penelope"))
				{
					moveTo(getX(), getY() - 2);
				}
				break;
			}

			return;
			}
		}
	}
}
	
	

