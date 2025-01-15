#include <cstring> //for memcpy
#include <iostream>

#include "Board.h"

// This function resets the board to its original state
void Board::reset() {
	for (int i = 0; i < MAX_Y; i++) {
		memcpy(currentBoard[i], originalBoard[i], MAX_X + 1);
	}
}

// This function prints the input board to the screen
void Board::printScreen(const char screen[][MAX_X + 1]) const 
{
	clrscr();														// Clears the console screen before printing the new board

	for (int i = 0; i < MAX_Y - 1; i++) {
		std::cout << screen[i] << '\n';
		//Sleep(SCREEN_APPEARANCE);
	}
	std::cout << screen[MAX_Y - 1];									// Print the last row without a newline to avoid an extra blank line
}




// Function made by the lecturer and chatGPT 
void Board::getAllBoardFileNames(std::vector<std::string>& vec_to_fill) const {
    if (!std::filesystem::exists(directory)) {
        std::cerr << "Directory does not exist: " << directory << std::endl;
        return;
    }

    if (!std::filesystem::is_directory(directory)) {
        std::cerr << "Path is not a directory: " << directory << std::endl;
        return;
    }
    try {
        for (const auto& entry : std::filesystem::directory_iterator(std::filesystem::current_path())) {
            auto filenameStr = entry.path().filename().string();
            if (filenameStr.substr(0, 6) == "dkong_" && entry.path().extension() == ".screen") { //maybe magic number 6
                vec_to_fill.push_back(filenameStr);
            }
        }
        std::sort(vec_to_fill.begin(), vec_to_fill.end());
    }
    catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error reading directory: " << e.what() << std::endl;
    }
}

bool Board::load(const std::string& filename) {
    std::ifstream screen_file(filename);                // Open file
    if (!screen_file) {                                 // Check if opened correctly
        handleErrors(screen_file);
        return false;
    }
    start_pos_ghosts_vec.clear();
    int curr_row = 0;
    int curr_col = 0;
    char c;
    while (!screen_file.get(c).eof() && curr_row < MAX_Y) {
        if (c == '\n') {
            if (curr_col < MAX_X) {
                // add spaces for missing cols
                #pragma warning(suppress : 4996) // to allow strcpy
                strcpy(originalBoard[curr_row] + curr_col, std::string(MAX_X - curr_col - 1, ' ').c_str());
            }
            ++curr_row;
            curr_col = 0;
            continue;
        }
        if (curr_col < MAX_X) {                           
            switch (c)
            {
            case '@':
                start_pos_mario = { curr_col, curr_row };
                break;
            case '&':
                start_pos_gorilla = { curr_col, curr_row };
                break;
            case '$':
                start_pos_pauline = { curr_col, curr_row };
                break;
            //case 'p':
            //   start_pos_hammer = { curr_col, curr_row };
            //    break;
            case 'x':
                start_pos_ghosts_vec.push_back({ curr_col, curr_row });
                break;
            case 'L':
                legend.pos_L = { curr_col, curr_row };
                setPositionsInLegend();
                break;
            }
            originalBoard[curr_row][curr_col++] = c;
        }
    }
    screen_file.close();
    return true;
}


void Board::handleErrors(const std::ifstream& _file) {

    clrscr();														// Clears the console screen before printing the new board
    if (_file.eof()) {
        std::cerr << "End of file reached." << std::endl;
    }
    else if (_file.fail()) {
        std::cerr << "Read error (failbit)." << std::endl;
    }
    else if (_file.bad()) {
        std::cerr << "Critical error (badbit)." << std::endl;
    }
    else {
        std::cerr << "Unknown error." << std::endl;
    }
    std::cout << "Returning to menu" << std::endl;
    Sleep(500);
}

void Board::setPositionsInLegend()
{
    int x = legend.pos_L.x;
    int y = legend.pos_L.y;
    legend.pos_score_in_legend = { x, y };
    legend.pos_life_in_legend = { x, y + 1 };
    legend.pos_hammer_in_legend = { x, y + 2 };
}

void Board::printLegend() const
{
    gotoxy(legend.pos_score_in_legend.x, legend.pos_score_in_legend.y);
    std::cout << legend.str_score << legend.score;

    gotoxy(legend.pos_life_in_legend.x, legend.pos_life_in_legend.y);
    std::cout << legend.str_life << legend.life;

    gotoxy(legend.pos_hammer_in_legend.x, legend.pos_hammer_in_legend.y);
    std::cout << legend.str_hammer << legend.hammer;
}

void Board::setLegend(int score, int life, char hammer)
{
    setScoreLegend(score);
    setLifeLegend(life);
    setHammerLegend(hammer);
}


void Board::printScreenOptions(std::vector<std::string>& vec_to_fill) const
{
    clrscr();
    // Add headline - ascii art

    printScreen(chooseBoard_screen);

    int x = 30; // MAGIC NUMBER!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    int y = 10;
    for (int i = 0; i < vec_to_fill.size(); i++)
    {
        gotoxy(x, y++);
        std::cout << "(" << i + 1 << ")  " << vec_to_fill[i] << std::endl;
    }
}



