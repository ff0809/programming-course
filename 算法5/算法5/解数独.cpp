//#include<iostream>
//#include<vector>
//using namespace std;
//
//bool isvalid(vector<vector<char>>&board,char num,int row,int col) {
//	for (int i = 0; i < 9; i++) {
//		if (board[i][col] == num)return false;
//	}
//	for (int j = 0; j < 9; j++) {
//		if (board[row][j] == num)return false;
//	}
//	int boxrow = (row / 3) * 3; int boxcol = (col / 3) * 3;
//	for (int i = boxrow; i < boxrow + 3; i++) {
//		for (int j = boxcol; j < boxcol + 3; j++) {
//			if (board[i][j] == num)return false;
//		}
//	}
//	return true;
//}
//
//bool backtrack(vector<vector<char>>&board) {
//	for (int i = 0; i < 9; i++) {
//		for (int j = 0; j < 9; j++) {
//			if (board[i][j] == '.') {
//				for (char num = '1'; num <= '9';num++) {
//					if (isvalid(board, num, i, j)) {
//						board[i][j] = num;
//						if (backtrack(board))return true;
//						board[i][j] = '.';
//					}
//				}
//				return false;
//			}
//		}
//	}
//	return true;
//}
//
//void printBoard(vector<vector<char>>& board) {
//	for (int i = 0; i < 9; i++) {
//		for (int j = 0; j < 9; j++) {
//			cout << board[i][j] << " ";
//		}
//		cout << endl;
//	}
//}
//
//void game(vector<vector<char>>&board) {
//	backtrack(board);
//}
//
//int main()
//{
//	vector<vector<char>> board = {
//		{'5','3','.','.','7','.','.','.','.'},
//		{'6','.','.','1','9','5','.','.','.'},
//		{'.','9','8','.','.','.','.','6','.'},
//		{'8','.','.','.','6','.','.','.','3'},
//		{'4','.','.','8','.','3','.','.','1'},
//		{'7','.','.','.','2','.','.','.','6'},
//		{'.','6','.','.','.','.','2','8','.'},
//		{'.','.','.','4','1','9','.','.','5'},
//		{'.','.','.','.','8','.','.','7','9'}
//	};
//
//	game(board);       
//	printBoard(board);
//	return 0;
//}