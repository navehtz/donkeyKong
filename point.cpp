#include "point.h"
#include "general.h"

// Erase the character by redrawing the previous character
void Point::erase() const {															
	gotoxy(x, y);
	if (colors_on && previous_char == LADDER)													
		setConsoleColor(BLUE);
	else if (colors_on && (previous_char == FLOOR || previous_char == FLOOR_LEFT || previous_char == FLOOR_RIGHT))
		setConsoleColor(RED);

	cout << previous_char;
	setConsoleColor(DEFULT);       // Return consol's color to defult

}


