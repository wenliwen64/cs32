///*
#include "Game.h"

int main()
{
	// Create a game
	// Use this instead to create a mini-game:   Game g(3, 4, 2);
	Game g(7, 8, 25);

	// Play the game
	g.play();
}
//*/
/*
#include "Game.h"
#include "Game.h"
#include "Arena.h"
#include "Arena.h"
#include "History.h"
#include "History.h"
#include "Player.h"
#include "Player.h"
#include "Robot.h"
#include "Robot.h"
#include "globals.h"
#include "globals.h"
int main()
{}
*/
/*
#include "History.h"
int main()
{
	History h(2, 2);
	h.record(1, 1);
	h.display();
}
*/
/*
#include "Robot.h"
int main()
{
	Robot r(nullptr, 1, 1);
}
*/
/*
#include "Player.h"
int main()
{
	Player p(nullptr, 1, 1);
}
*/
/*
#include "Arena.h"
int main()
{
	Arena a(10, 18);
	a.addPlayer(2, 2);
}
*/
/*
#include "Arena.h"
#include "Player.h"
int main()
{
	Arena a(10, 20);
	Player p(&a, 2, 3);
}
*/
/*
#include "Player.h"
#include "Arena.h"
int main()
{
	Arena a(10, 20);
	Player p(&a, 2, 3);
}
*/
/*
#include "Arena.h"
#include "History.h"
#include "Player.h"
#include "globals.h"
int main()
{
	Arena a(4, 4);
	a.addPlayer(2, 4);
	a.addRobot(3, 2);
	a.addRobot(2, 3);
	a.addRobot(1, 4);
	a.player()->moveOrAttack(LEFT);
	a.player()->moveOrAttack(UP);
	a.player()->moveOrAttack(LEFT);
	a.player()->moveOrAttack(LEFT);
	a.player()->moveOrAttack(DOWN);
	a.player()->moveOrAttack(DOWN);
	a.player()->moveOrAttack(LEFT);
	a.player()->moveOrAttack(UP);
	a.player()->moveOrAttack(UP);
	a.player()->moveOrAttack(UP);
	a.history().display();
}
*/
/*
#include "Player.h"
#include "Arena.h"
int main()
{
	Arena a(10, 20);
	Player p(&a, 2, 3);
	Robot r(&a, 1, 1);
}
*/
/*
#include "globals.h"
#include "Robot.h"
#include "Player.h"
int main()
{
	Arena a(10, 10);
}
*/
/*
#include "History.h"
int main()
{
	History h;
}
*/
