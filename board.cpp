#include <cstring> //for memcpy
#include <iostream>

#include "Board.h"

// This function resets the board to its original state
void Board::reset() {
	for (int i = 0; i < GameConfig::BOARD_HEIGHT; i++) {
		memcpy(currentBoard[i], originalBoard[i], GameConfig::BOARD_WIDTH + 1);
	}
}

// This function prints the input board to the screen
void Board::printScreen(const char screen[][GameConfig::BOARD_WIDTH + 1]) const 
{
    GameConfig::clrscr();														// Clears the console screen before printing the new board

	for (int i = 0; i < GameConfig::BOARD_HEIGHT - 1; i++) {
		std::cout << screen[i] << '\n';
	}
	std::cout << screen[GameConfig::BOARD_HEIGHT - 1];									// Print the last row without a newline to avoid an extra blank line
}

// Function made by the lecturer and chatGPT 
void Board::getAllBoardFileNames(std::vector<std::string>& vec_to_fill) const {
    if (!std::filesystem::exists(directory)) {
        std::cout << "Directory does not exist: " << directory << std::endl;
        return;
    }

    if (!std::filesystem::is_directory(directory)) {
        std::cout << "Path is not a directory: " << directory << std::endl;
        return;
    }
    try {
        for (const auto& entry : std::filesystem::directory_iterator(std::filesystem::current_path())) {
            auto filenameStr = entry.path().filename().string();
            if (filenameStr.substr(0, GameConfig::FILE_NAME_LENGTH) == "dkong_" && entry.path().extension() == ".screen") {
                vec_to_fill.push_back(filenameStr);
            }
        }
        std::sort(vec_to_fill.begin(), vec_to_fill.end());
    }
    catch (const std::filesystem::filesystem_error& e) {
        std::cout << "Filesystem error: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Error reading directory: " << e.what() << std::endl;
    }
}

bool Board::load(const std::string& filename) {
    readen_mario = readen_princess = readen_gorilla = readen_legend = readen_hammer = 0;

    std::ifstream screen_file(filename);                // Open file
    if (!screen_file) {                                 // Check if opened correctly
        return handleReadFileErrors(screen_file);
    }
    start_pos_and_type_ghosts_vec.clear();
    int curr_row = 0;
    int curr_col = 0;
    char c;
    while (!screen_file.get(c).eof() && curr_row < GameConfig::BOARD_HEIGHT) {
        if (c == '\n') {
            if (curr_col < GameConfig::BOARD_WIDTH) {
                // add spaces for missing cols
                #pragma warning(suppress : 4996) // to allow strcpy
                strcpy(originalBoard[curr_row] + curr_col, std::string(GameConfig::BOARD_WIDTH - curr_col, GameConfig::SPACE).c_str());
            }
            ++curr_row;
            curr_col = 0;
            continue;
        }
        if (curr_col < GameConfig::BOARD_WIDTH) {                           
            switch (c)
            {
            case GameConfig::MARIO:
                manageChar(c, readen_mario, start_pos_mario, curr_col, curr_row);
                break;
            case GameConfig::GORRILA:
                manageChar(c, readen_gorilla, start_pos_gorilla, curr_col, curr_row);
                break;
            case GameConfig::PRINCESS:
                manageChar(c, readen_princess, start_pos_princess, curr_col, curr_row);
                break;
            case GameConfig::REGULAR_GHOST:
                start_pos_and_type_ghosts_vec.push_back({ GameConfig::REGULAR_GHOST, { curr_col, curr_row } });
                break;
            case GameConfig::SPECIAL_GHOST:
                start_pos_and_type_ghosts_vec.push_back({ GameConfig::SPECIAL_GHOST, { curr_col, curr_row } });
                break;
            case GameConfig::HAMMER:
                manageChar(c, readen_hammer, start_pos_hammer, curr_col, curr_row);
                break;
            case GameConfig::LEGEND:
                readen_legend++;
                legend.pos_L = { curr_col, curr_row };
                setPositionsInLegend();
                break;
            default:
                if (c != GameConfig::FLOOR && c != GameConfig::FLOOR_LEFT && c != GameConfig::FLOOR_RIGHT && c != GameConfig::LADDER && c != GameConfig::WALL)
                    c = GameConfig::SPACE;
                break;
            }
            originalBoard[curr_row][curr_col++] = c;
        }
    }
    screen_file.close();

    return handleUnvalidFile(filename, curr_row);
}

void Board::manageChar(char& ch, bool& already_readen_char, GameConfig::Position& pos, int curr_col, int curr_row)
{
    if (!already_readen_char) {
        pos = { curr_col, curr_row };
        already_readen_char = true;
    }
    else
        ch = GameConfig::SPACE;
}

bool Board::handleReadFileErrors(const std::ifstream& _file)
{
    GameConfig::clrscr();														// Clears the console screen before printing the new board
    if (_file.eof()) {
        std::cout << "End of file reached." << std::endl;
    }
    else if (_file.fail()) {
        std::cout << "Read error (failbit)." << std::endl;
    }
    else if (_file.bad()) {
        std::cout << "Critical error (badbit)." << std::endl;
    }
    else {
        std::cout << "Unknown error." << std::endl;
    }
    std::cout << "Returning to menu" << std::endl;
    Sleep(GameConfig::SCREEN_EXIT);
    return false;
}

bool Board::handleUnvalidFile(const std::string& filename, int rows_number) const
{
    int count_errors = 0;
    GameConfig::clrscr();
    if (rows_number < GameConfig::BOARD_HEIGHT)     // The board's rows isn't match the norma
    {
        std::cout << filename << ": Not enough rows" << std::endl;
        std::cout << "the valid rows in the screen should be : " << GameConfig::BOARD_HEIGHT << std::endl;
        count_errors++;
    }
    if (!readen_mario)
    {
        std::cout << filename << ": no mario in file" << std::endl;
        count_errors++;
    }
    if (!readen_princess)
    {
        std::cout << filename << ": no princess in file" << std::endl;
        count_errors++;
    }
    if (!readen_gorilla) 
    {
        std::cout << filename << ": no gorilla in file" << std::endl;
        count_errors++;
    }
    if (readen_legend < 1)
    {
        std::cout << filename << ": no legend in file" << std::endl;
        count_errors++;
    }
    else if (readen_legend > 1)
    {
        std::cout << filename << ": too many legends in file" << std::endl;
        count_errors++;
    }

    if (count_errors > 0)
    {
        std::cout << std::endl;
        std::cout << "loading next screen ..." << std::endl;
        Sleep(GameConfig::SCREEN_EXIT * 2);

        return false;
    }
    else
        return true;
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
    GameConfig::gotoxy(legend.pos_score_in_legend.x, legend.pos_score_in_legend.y);
    std::cout << legend.str_score << legend.score;

    GameConfig::gotoxy(legend.pos_life_in_legend.x, legend.pos_life_in_legend.y);
    std::cout << legend.str_life << legend.life;

    GameConfig::gotoxy(legend.pos_hammer_in_legend.x, legend.pos_hammer_in_legend.y);
    std::cout << legend.str_hammer << legend.hammer;
}

void Board::printEndLevelScore() const
{
    GameConfig::gotoxy(GameConfig::WIN_SCORE_POS_X, GameConfig::WIN_SCORE_POS_Y);
    std::cout << "Your score: " << legend.score << " !";
}

void Board::setLegend(int score, int life, char hammer)
{
    setScoreLegend(score);
    setLifeLegend(life);
    setHammerLegend(hammer);
}


void Board::printScreenOptions(const std::vector<std::string>& vec_to_fill) const
{
    GameConfig::clrscr();
    int y = GameConfig::POS_Y_PRINT_SCREEN;

    printScreen(chooseBoard_screen);

    for (int i = 0; i < vec_to_fill.size(); i++)
    {
        GameConfig::gotoxy(GameConfig::POS_X_PRINT_SCREEN, y++);
        std::cout << "(" << i + 1 << ")  " << vec_to_fill[i] << std::endl;
    }
}



