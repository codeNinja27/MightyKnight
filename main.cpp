#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

class knightType
{
public:
    struct position
    {
        position(int r = 0, int c = 0, int o = 0)
            : row(r), col(c), onwardMoves(o) {}

        int row;
        int col;
        int onwardMoves;
    };

    knightType(int dim = 8)
        : board(dim, vector<int>(dim, 0)), functionsCalled(0), boardSize(dim) {}

    bool knightTour(int startRow, int startCol)
    {
        return knightTour(startRow, startCol, 1);
    }

    void outputTour() const
    {
        cout << "  ";
        for (char c = 'A'; c < 'A' + boardSize; ++c)
        {
            cout << " " << c << " ";
        }
        cout << endl;

        for (int i = 0; i < boardSize; ++i)
        {
            cout << static_cast<char>('A' + i) << " ";
            for (int j = 0; j < boardSize; ++j)
            {
                cout << setw(2) << board[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
        cout << "Functions called: " << functionsCalled << endl;
    }

private:
    bool knightTour(int r, int c, int tourIndex)
    {
        board[r][c] = tourIndex;
        ++functionsCalled;

        if (fullBoard())
        {
            return true;
        }

        vector<position> moves = getAvailableMoves(r, c);
        sort(moves.begin(), moves.end(), ComparePositions);

        for (vector<position>::iterator it = moves.begin(); it != moves.end(); ++it)
        {
            if (knightTour(it->row, it->col, tourIndex + 1))
            {
                return true;
            }
        }

        board[r][c] = 0;
        return false;
    }

    static bool ComparePositions(const position &a, const position &b)
    {
        return a.onwardMoves < b.onwardMoves;
    }

    vector<position> getAvailableMoves(int r, int c)
    {
        static const int rowOffsets[] = {-2, -1, 1, 2, 2, 1, -1, -2};
        static const int colOffsets[] = {1, 2, 2, 1, -1, -2, -2, -1};

        vector<position> moves;

        for (size_t i = 0; i < sizeof(rowOffsets) / sizeof(rowOffsets[0]); ++i)
        {
            int newRow = r + rowOffsets[i];
            int newCol = c + colOffsets[i];

            if (isValidMove(newRow, newCol))
            {
                int onwardMoves = countOnwardMoves(newRow, newCol);
                moves.push_back(position(newRow, newCol, onwardMoves));
            }
        }

        return moves;
    }

    bool isValidMove(int r, int c)
    {
        return r >= 0 && r < boardSize && c >= 0 && c < boardSize && board[r][c] == 0;
    }

    int countOnwardMoves(int r, int c)
    {
        static const int rowOffsets[] = {-2, -1, 1, 2, 2, 1, -1, -2};
        static const int colOffsets[] = {1, 2, 2, 1, -1, -2, -2, -1};

        int count = 0;
        for (size_t i = 0; i < sizeof(rowOffsets) / sizeof(rowOffsets[0]); ++i)
        {
            int newRow = r + rowOffsets[i];
            int newCol = c + colOffsets[i];
            if (isValidMove(newRow, newCol))
            {
                ++count;
            }
        }
        return count;
    }

    bool fullBoard()
    {
        for (vector<vector<int> >::const_iterator it = board.begin(); it != board.end(); ++it)
        {
            for (vector<int>::const_iterator jt = it->begin(); jt != it->end(); ++jt)
            {
                if (*jt == 0)
                {
                    return false;
                }
            }
        }
        return true;
    }

    vector<vector<int> > board;
    int functionsCalled;
    int boardSize;
};

int main()
{
    char anotherTry;
    do {
        int dimension;
        cout << "Enter board dimension: ";
        cin >> dimension;
        cout << endl;

        int startRow, startCol;
        do{
            cout << "Please enter initial knight position that is greater than (0,0): ";
            cin >> startRow >> startCol;           
        } while (startCol <= 0 || startRow <= 0);

        cout << endl;
        --startRow; 
        --startCol; 

        knightType knight(dimension);

        if (knight.knightTour(startRow, startCol))
        {
            cout << "Knight FTW" << endl;
            cout << endl;
            knight.outputTour();
        }
        else
        {
            cout << "No solution found" << endl;
            cout << endl;
        }
        cout << endl;
        cout << "Another try? (y/n): ";
        cout << endl;
        cin >> anotherTry;
    } while (anotherTry == 'y' || anotherTry == 'Y');


    return 0;
}