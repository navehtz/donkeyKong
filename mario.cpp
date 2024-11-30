#include "mario.h"
#include "point.h"

void Mario::keyPressed(char key) {
	for (size_t i = 0; i < numKeys; i++) {
		if (std::tolower(key) == keys[i]) {
			dir = directions[i];
			return;
		}
	}
}

void Mario::move()
{
	char current_char;
	bool first_move = true;

	
	// from hereeee
	//if (first_move) { previous_char = ' '; }
	//else { previous_char = getCharPosition(p.x, p.y); } 

	if (isOnFloor())
	{
		if(dir.y == 1)
			dir.y = 0;
	}
	int newX = p.x + dir.x;
	int newY = p.y + dir.y;

	if (newX < 0 || newX > 79)
		newX = p.x;
	if (newY < 0 || newY > 24)
		newY = p.y;

	p.x = newX;
	p.y = newY;
	current_char = getCharPosition(p.x, p.y);

}

bool Mario::isOnFloor()
{
	int x = p.x;
	int y = p.y;
	char ch_below = getCharPosition(x, y + 1);
	if (ch_below == '=' || ch_below == '>' || ch_below == '<')
		return true;
	else
		return false;
}

//char Mario::theCoverLetter()
//{
//	char ch = getCharPosition(p.x, p.y);
//	/*if (ch != ' ')
//		return ch;
//	else
//		return false;*/
//}
