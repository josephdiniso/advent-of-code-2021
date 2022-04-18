#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#define LOG(x) std::cout << x << std::endl;

using Board = std::vector<std::vector<int>>;

std::vector<int> splitLine(std::string s, char delim = ' ')
{
    bool adding = true;
    std::vector<int> vals;
    std::string val = "";
    for (auto letter : s)
    {
        if (letter == delim)
        {
            if (val.size() > 0)
            {
                vals.push_back(std::stoi(val));
                val.clear();
            }
        }
        if (letter != delim)
        {
            val += letter;
        }
    }
    if (val.size() > 0)
    {
        vals.push_back(std::stoi(val));
        val.clear();
    }
    return vals;
}

std::vector<Board> processBoards(std::ifstream &file)
{
    std::vector<Board> boards;
    Board board;

    std::string line;
    while (std::getline(file, line))
    {
        if (line == "" || line == "\n")
        {
            if (board.size() > 0)
            {
                boards.push_back(board);
                board.clear();
            }
        }
        else
        {
            board.push_back(splitLine(line));
        }
    }
    if (board.size() > 0)
    {
        boards.push_back(board);
        board.clear();
    }

    return boards;
}

using BoardBool = std::vector<std::vector<bool>>;

/**
 * @brief Make a vector of vectors of bools to represent each board.
 *
 * @param size
 * @return std::vector<BoardBool>
 */
std::vector<BoardBool> getBoardBools(int size)
{
    std::vector<BoardBool> boardBools;
    for (int i = 0; i < size; ++i)
    {
        BoardBool board;
        for (int j = 0; j < 5; ++j)
        {
            std::vector<bool> row(5, false);
            board.push_back(row);
        }
        boardBools.push_back(board);
    }
    return boardBools;
}

std::vector<int> checkWinner(std::vector<BoardBool> &boardBools, std::vector<int> &alreadyWon)
{
    std::vector<int> winners;
    for (int i = 0; i < boardBools.size(); ++i)
    {
        if (std::find(alreadyWon.begin(), alreadyWon.end(), i) != alreadyWon.end())
        {
            continue;
        }
        bool foundRow = false;
        for (int j = 0; j < 5; ++j)
        {
            bool goodRow = true;
            for (int k = 0; k < 5; ++k)
            {
                if (!boardBools[i][j][k])
                {
                    goodRow = false;
                    break;
                }
            }
            if (goodRow)
            {
                foundRow = true;
                winners.push_back(i);
                break;
            }
        }
        if (foundRow)
        {
            continue;
        }
        for (int j = 0; j < 5; ++j)
        {
            bool goodCol = true;
            for (int k = 0; k < 5; ++k)
            {
                if (!boardBools[i][k][j])
                {
                    goodCol = false;
                    break;
                }
            }
            if (goodCol)
            {
                winners.push_back(i);
                break;
            }
        }
    }
    return winners;
}

int getScore(BoardBool &boardBool,
             Board &board, int justCalled)
{
    int sumVal = 0;

    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            if (!boardBool[i][j])
            {
                sumVal += board[i][j];
            }
        }
    }
    return sumVal * justCalled;
}

void processResults(std::vector<BoardBool> &boardBools,
                    std::vector<Board> &boards,
                    std::vector<int> numbersCalled)
{
    std::vector<int> alreadyWon;
    for (auto number : numbersCalled)
    {
        // Check each board in each location for valid number
        for (int i = 0; i < boards.size(); ++i)
        {
            for (int j = 0; j < 5; ++j)
            {
                for (int k = 0; k < 5; ++k)
                {
                    if (boards[i][j][k] == number)
                    {
                        boardBools[i][j][k] = true;
                    }
                }
            }
        }
        std::vector<int> res = checkWinner(boardBools, alreadyWon);
        if (res.size() > 0)
        {
            for (int winner : res)
            {
                alreadyWon.push_back(winner);
                LOG(getScore(boardBools[winner], boards[winner], number));
            }
        }
    }
}

int main()
{
    std::ifstream file;
    file.open("day_4.txt");

    std::string numbersCalledLine;
    std::getline(file, numbersCalledLine);
    std::vector<int> numbersCalled = splitLine(numbersCalledLine, ',');
    std::vector<Board> boards = processBoards(file);

    std::vector<BoardBool> boardBools = getBoardBools(boards.size());
    processResults(boardBools, boards, numbersCalled);
}