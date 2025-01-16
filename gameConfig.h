#pragma once

// Class representing configuration settings and constants for the game
class GameConfig
{
public:
    // Constants representing movement directions
    static constexpr int UP = -1;       // Move up
    static constexpr int DOWN = 1;     // Move down
    static constexpr int RIGHT = 1;    // Move right
    static constexpr int LEFT = -1;    // Move left
    static constexpr int STAY = 0;     // No movement

    // Constants representing game states and configurations
    static constexpr int DEAD_MARIO = 0;       // State representing Mario is dead
    static constexpr int FULL_LIVES = 3;       // Initial number of lives for Mario
    static constexpr int EXPLOSION_RADIUS = 2; // Radius of an explosion of a barrel
    static constexpr int MAX_BARRELS = 5;      // Number of barrels in the container
    static constexpr int POSSIBLE_INPUT = 3;   // Number of possible inputs for controls in one loop game

    // Constants for screen-related timings (in milliseconds)
    static constexpr int SCREEN_TIME = 150 / POSSIBLE_INPUT;    // Sleep between the game's loops based on input
    static constexpr int SCREEN_PAUSE_GAME = 50;                // Pause duration when the game is paused
    static constexpr int SCREEN_WIN = 2000;                     // Time to display the win screen
    static constexpr int SCREEN_EXIT = 2000;                    // Time to display the exit screen
    static constexpr int SCREEN_FLASH_MARIO = 200;              // Flash duration for Mario's appearance

    // File and game element configurations
    static constexpr int FILE_NAME_LENGTH = 6; // Length of the file name's start template

    // Characters representing game elements in the console
    static constexpr char WALL = 'Q';        // Character for wall
    static constexpr char FLOOR = '=';       // Character for floor
    static constexpr char FLOOR_LEFT = '<';  // Character for floor (left edge)
    static constexpr char FLOOR_RIGHT = '>'; // Character for floor (right edge)
    static constexpr char LADDER = 'H';      // Character for ladder
    static constexpr char MARIO = '@';       // Character for Mario
    static constexpr char PRINCESS = '$';    // Character for the Pauline
    static constexpr char GORRILA = '&';     // Character for the Donkey Kong
    static constexpr char SPACE = ' ';       // Character for empty space
    static constexpr char HAMMER = 'p';      // Character for hammer
    static constexpr char BARREL = 'O';      // Character for barrel
    static constexpr char GHOST = 'x';       // Character for ghost
    static constexpr char LEGEND = 'L';      // Character for legend or key point

    // Scoring system constants
    static constexpr int KILL_GHOST = 100;   // Score for killing a ghost
    static constexpr int KILL_BARREL = 80;   // Score for destroying a barrel
    static constexpr int END_LEVEL = 1000;   // Score for completing a level

    // Position constants for printing elements on the screen
    static constexpr int POS_X_PRINT_SCREEN = 30; // X-coordinate for print position
    static constexpr int POS_Y_PRINT_SCREEN = 10; // Y-coordinate for print position

    // Struct representing a position with x and y coordinates
    struct Position {
        int x, y;
    };

    // Struct representing a movement direction
    struct Direction {
        int x, y;
    };
   
    // Move the cursor to the specified (x, y) position in the console
    static void gotoxy(int x, int y);

    // Show or hide the console cursor based on the given flag
    static void ShowConsoleCursor(bool showFlag);

    // Clear the console screen
    static void clrscr() { system("cls"); }

};
