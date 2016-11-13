#include<stdio.h>
#include<deque>
#include<iostream>
#include<thread>
#include"zero.h"
using namespace std;
#define Map_h 15
#define Map_w 30
int Map[Map_h][Map_w];

int Keyboard;
struct point
{
	int x, y;
	point(int _x = 0, int _y = 0)
	{
		x = _x;
		y = _y;
	}
};
class snake
{
public:
	deque<point> body; // body[0] = head point
	point dir, newScore;
	int score;
	bool addBody, gameOVER;
	// new body -> last body moved, insert new body
	snake()
	{
		body.push_back(point(Map_w / 2, Map_h / 2));
		dir.x = 1;
		dir.y = 0;
		addBody = false;
		gameOVER = false;
		score = 0;
	}
	void spawnScore()
	{
		do
		{
			newScore.x = random() % Map_w;
			newScore.y = random() % Map_h;
		} while (isBody(newScore.x, newScore.y));
	}
	void move()
	{
		if (addBody)
		{
			addBody = false;
			body.push_back(body.back());
		}
		for (int i = body.size() - 1; i>0; i--)
		{
			body[i] = body[i - 1];
		}
		body[0].x += dir.x;
		body[0].y += dir.y;
		if (body[0].x == newScore.x && body[0].y == newScore.y)
		{
			addBody = true;
			score += 100*body.size();
			spawnScore();
		}
		else if (0 > body[0].x || body[0].x >= Map_w || 0 > body[0].y || body[0].y >= Map_h) gameOVER = true;
		else
		{
			for (int i = 1; i < body.size(); i++)
			{
				if (body[i].x==body[0].x && body[i].y==body[0].y)
				{
					gameOVER = true;
					break;
				}
			}
		}
	}
	inline bool isBody(int x, int y)
	{
		for (int i = 0; i<body.size(); i++)
		{
			if (body[i].x == x && body[i].y == y) return true;
		}
		return false;
	}
}Snake;

void drawMap()
{
	pointmove(0,0);
	printf("## Score : %d\n", Snake.score);
	printf("M");
	for (int i = 0; i<Map_w; i++) printf("-");
	printf("M\n");
	for (int i = 0; i<Map_h; i++)
	{
		printf("|");
		for (int j = 0; j<Map_w; j++)
		{
			// Map
			if (Snake.isBody(j, i))
			{
				textcolor(14);
				printf("A");
				textcolor(-1);
			}
			else if (Snake.newScore.x == j && Snake.newScore.y == i)
			{
				textcolor(12);
				printf("N");
				textcolor(-1);
			}
			else printf(" ");
		}
		printf("|\n");
	}
	printf("M");
	for (int i = 0; i<Map_w; i++) printf("-");
	printf("M\n");
}
void keyListener()
{
	while (true)
	{
		if (Snake.gameOVER) break;
		Keyboard = getch();
		switch (Keyboard)
		{
		case 72:
			// Up
			if(Snake.dir.x!=0 && Snake.dir.y!=1)
			{
				Snake.dir.x = 0;
				Snake.dir.y = -1;
			}
			break;
		case 80:
			// Down
			if(Snake.dir.x!=0 && Snake.dir.y!=-1)
			{
				Snake.dir.x = 0;
				Snake.dir.y = 1;
			}
			break;
		case 75:
			// Left
			if(Snake.dir.x!=1 && Snake.dir.y!=0)
			{
				Snake.dir.x = -1;
				Snake.dir.y = 0;
			}
			break;
		case 77:
			// Right
			if(Snake.dir.x!=-1 && Snake.dir.y!=0)
			{
				Snake.dir.x = 1;
				Snake.dir.y = 0;
			}
			break;
		}
	}
}
int main()
{
	thread T_keyListener(keyListener);
	Snake.spawnScore();
	while (!Snake.gameOVER)
	{
		drawMap();
		Snake.move();
		if (Snake.gameOVER)
		{
			cls();
			printf("Game OvEr!!!\n\n");
			pause();
		}
		sleep(200);
	}
	T_keyListener.join();
	return 0;
}
