#pragma once

class Board {
	static constexpr int MAX_X = 80;
	static constexpr int MAX_Y = 25;
	const char* originalBoard[MAX_Y] = {
		// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		  "                                                                                ", // 0
		  "                                     $                                          ", // 1
		  "                        ===============================                         ", // 2
		  "                        H            &               H                          ", // 3
		  "                        H      =============         H                          ", // 4
		  "                        H                            H                          ", // 5
		  "                        H                            H                          ", // 6
		  "          <<<<<<<<<<<<<<<<<<<<<<<        >>>>>>>>>>>>>>>>>>>>                   ", // 7
		  "            H                                 H                                 ", // 8
		  "            H                                 H                                 ", // 9
		  "            H                                 H           H                     ", // 10
		  "            H                                 H           H                     ", // 11
		  "         >==================            <<<<<<<<<<<<<<<<<<<<<<<<<<<             ", // 12
		  "                       H                                        H               ", // 13
		  "                       H                                        H               ", // 14
		  "                ============<         >===========================<             ", // 15
		  "                  H                               H            H                ", // 16
		  "                  H                               H            H                ", // 17
		  "                  H                               H            H                ", // 18
		  "       =======>================                  =================	           ", // 19
		  "          H                                                H                    ", // 20
		  "          H                                                H                    ", // 21
		  "          H                H              H                H                    ", // 22
		  "          H    =           H              H                H                    ", // 23
		  "================================================================================"  // 24
	};
public:
	char currentBoard[MAX_Y][MAX_X + 1]; // +1 for null terminator
	void reset();
	void print() const;
	char getCharPosition(int x, int y) const { return currentBoard[y][x]; }
	void updateBoard(int x, int y, char newChar) { currentBoard[y][x] = newChar; }
};



/*
		// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		  "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 0
		  "Q                                                                              Q", // 1
		  "Q                                                                              Q", // 2
		  "Q                            =====================                             Q", // 3
		  "Q                                                                              Q", // 4
		  "Q                                                                              Q", // 5
		  "Q                                                                              Q", // 6
		  "Q                                                                              Q", // 7
		  "Q                                                                              Q", // 8
		  "Q                                                                              Q", // 9
		  "Q                                                                              Q", // 10
		  "Q                                                                              Q", // 11
		  "Q                                                                              Q", // 12
		  "Q                                                                              Q", // 13
		  "Q                                                                              Q", // 14
		  "Q                                                                              Q", // 15
		  "Q                                                                              Q", // 16
		  "Q                                                                              Q", // 17
		  "Q                                                                              Q", // 18
		  "Q                                                                              Q", // 19
		  "Q                                                                              Q", // 20
		  "Q      ==================================================================      Q", // 21
		  "Q                                                                              Q", // 22
		  "Q                                                                              Q", // 23
		  "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ"  // 24
*/