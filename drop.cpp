#include <iostream>
#include "curses.h"
#include <thread>
#include <chrono>
#include "drop.hpp"
#include <deque>

using namespace std;

Drop::Drop()
{
	this->age = 0;
	this->center.l = (rand() % LINES) + 1;
	this->center.c = (rand() % COLS) + 1;
}

void Drop::Draw()
{
	if ((this->age = 0))
	{
		mvaddch(this->center.l, this->center.c, 'o');
		refresh();
		this_thread::sleep_for(chrono::milliseconds(300));
	}
	else if ((this->age = 1))
	{
		mvaddch(this->center.l - 2, this->center.c, '-');
		mvaddstr(this->center.l, this->center.c - 1, "(  )");
		mvaddch(this->center.l + 2, this->center.c, '-');
		refresh();
		this_thread::sleep_for(chrono::milliseconds(300));
	}
	else if ((this->age = 2))
	{
		mvaddch(this->center.l - 4, this->center.c, '-');
		mvaddstr(this->center.l - 2, this->center.c - 1, "/ \\");
		mvaddstr(this->center.l, this->center.c - 3, "(   )");
		mvaddstr(this->center.l + 2, this->center.c + 1, "\\ /");
		mvaddch(this->center.l + 4, this->center.c, '-');
		refresh();
		this_thread::sleep_for(chrono::milliseconds(300));
	}
	this->age += 1;
}

bool Drop::TimeToDie()
{
	bool itsTime = false;

	if (this->age >= MAXIMUM_AGE)
	{
		itsTime = true;
	}

	return itsTime;
}

void Storm::Birth()
{
	int r = rand() % 12;
	if ((r = 0))
	{
		r += 1;
	}

	for (int i = 0; i < r; i++)
	{
		Drop d = Drop();
		drops.push_back(d);
	}
}

void Storm::Draw()
{
	for (size_t i = 0; i < drops.size(); i++)
	{
		drops.at(i).Draw();
	}
}

void Storm::Cull()
{
	while (drops.front().TimeToDie())
	{
		drops.pop_front();
	}
}