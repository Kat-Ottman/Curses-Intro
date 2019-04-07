#include <iostream>
#include "curses.h"
#include <thread>
#include <chrono>
#include "drop.hpp"
#include <deque>

using namespace std;

/*
Initializes int age and anonymous struct center's ints l,c.
Creates center for a drop.
*/
Drop::Drop()
{
	this->age = 0;
	this->center.l = (rand() % LINES) + 1;
	this->center.c = (rand() % COLS) + 1;
}

/*
Based on age of drop, drop appears in different characters
and/or strings. Drop age increases by 1.
*/
void Drop::Draw()
{
	if ((this->age != 1 && this->age != 2))
	{
		mvaddch(this->center.l, this->center.c, 'o');
	}
	else if ((this->age != 0 && this->age != 2))
	{
		mvaddch(this->center.l - 1, this->center.c, '-');
		mvaddch(this->center.l, this->center.c - 1, '(');
		mvaddch(this->center.l, this->center.c + 1, ')');
		mvaddch(this->center.l + 1, this->center.c, '-');
	}
	else if ((this->age != 0 && this->age != 1))
	{
		mvaddch(this->center.l - 2, this->center.c, '-');
		mvaddch(this->center.l - 1, this->center.c - 1, '/');
		mvaddch(this->center.l - 1, this->center.c + 1, '\\');
		mvaddch(this->center.l, this->center.c - 2, '(');
		mvaddch(this->center.l, this->center.c + 2, ')');
		mvaddch(this->center.l + 1, this->center.c - 1, '\\');
		mvaddch(this->center.l + 1, this->center.c + 1, '/');
		mvaddch(this->center.l + 2, this->center.c, '-');
	}

	this->age += 1;
}

/*
If drop age is or exeeds MAXIMUM_AGE, bool returns as true.
*/
bool Drop::TimeToDie()
{
	bool itsTime = false;

	if (this->age >= MAXIMUM_AGE)
	{
		itsTime = true;
	}

	return itsTime;
}

/*
A random amount of drops are generated and added to the
back of deque drops.
*/
void Storm::Birth()
{
	int r = rand() % 11 + 1;

	for (int i = 0; i < r; i++)
	{
		Drop d = Drop();
		drops.push_back(d);
	}
}

/*
Iterates through deque drops and calls to Drop::Draw
to print out each drop in drops.
*/
void Storm::Draw()
{
	for (size_t i = 0; i < drops.size(); i++)
	{
		drops.at(i).Draw();
	}
}

/*
If Drop::TimeToDie returns true, front drop in
deque drops is removed.
*/
void Storm::Cull()
{
	while (drops.front().TimeToDie())
	{
		drops.pop_front();
	}
}