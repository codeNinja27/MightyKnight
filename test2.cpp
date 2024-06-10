#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <vector>

using namespace std; 

int main() {
    int boardSize;
    vector<vector<int>> board;
    cout << "Enter the dimentsions:  ";
    cin >> boardSize;


    cout << "  ";
    for (char c = 'A'; c < 'A' + boardSize; ++c)
    {
        cout << " " << c << " ";
    }
    cout << endl;
    for (int i = 0; i < boardSize; ++i)
    {
        cout << static_cast<char>('A' + i) << " ";
        board.push_back({static_cast<char>('A' + i)});
       
        for (int j = 0; j < boardSize; ++j)
        {
            board[i][j] = i * boardSize + j + 1;
            // cout << setw(2) << board[i][j] << " ";
            cout << setw(2) << "*" << " ";;
        }
        cout << endl;
    }

    return 0;
}