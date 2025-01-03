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
		Sleep(SCREEN_APPEARANCE);
	}
	std::cout << screen[MAX_Y - 1];									// Print the last row without a newline to avoid an extra blank line
}


void Board::getFilesNames()
{
    if (!std::filesystem::exists(directory)) {
        std::cerr << "Directory does not exist: " << directory << std::endl;
        return;
    }

    if (!std::filesystem::is_directory(directory)) {
        std::cerr << "Path is not a directory: " << directory << std::endl;
        return;
    }

    try {
        for (const auto& entry : std::filesystem::directory_iterator(directory)) { //compatible with C++17
            if (entry.path().extension() == ".screen") {
                files_names_vec.push_back(entry.path().filename().string());
            }
        }
        std::sort(files_names_vec.begin(), files_names_vec.end());
    }

    catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error reading directory: " << e.what() << std::endl;
    }  
}

void Board::printScreenOptions()
{
    // Add headline

    int x = 30; // MAGIC NUMBER!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    int y = 10;
    for (int i = 0; i < files_names_vec.size(); i++)
    {
        gotoxy(x, y++);
        std::cout << "(" << i << ")  " << files_names_vec[i] << std::endl;
    }
}

Board* Board::getScreenByIndex(int index)
{
    std::string screen_name = files_names_vec[index - 1]; // Array start from zero

    file.open(screen_name, std::ios::in);
    if (!file.is_open()) {
        throw std::runtime_error("Error: Could not open file " + screen_name);
    }
    if (file.good()) {
        loadFile();
        return currentBoard;
    }
    else
        throw std::runtime_error("Error: Could not work with file " + screen_name);
}

void Board::loadFile() 
{
    for (int i = 0; i < MAX_Y; i++) {
        for (int j = 0; j < MAX_X; j++) {
            char ch;
            if (file.get(ch)) {
                currentBoard[i][j] = ch;
            }
            else {
                currentBoard[i][j] = ' ';
            }
        }
    }

    file.close();
}


void Board::display() const {
    for (const auto& row : readen_board) {
        std::cout << row << std::endl;
    }
}

//const std::vector<std::string>& Board::getcurr_board() const {
//    return readen_board;
//}


/*
// פונקציה לדוגמה להצגת שמות הקבצים
void displayScreenFiles(const std::string& directory) {
    std::vector<std::string> files = getScreenFiles(directory);

    if (files.empty()) {
        std::cout << "No .screen files found in directory: " << directory << std::endl;
        return;
    }

    std::cout << "Screen files in directory:" << std::endl;
    for (const auto& file : files) {
        std::cout << "- " << file << std::endl;
    }
}

// פונקציה ראשית לדוגמה
int main() {
    std::string directory = "."; // ניתן להחליף לספרייה הרצויה
    displayScreenFiles(directory);
    return 0;
}

*/