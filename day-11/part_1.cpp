#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
#include <tuple>

#define LOG(x) std::cout << x << "\n"

using Row = std::vector<int>;
using Coord = std::tuple<int, int>;
/**
 * Increments all elements of the board by 1
 */
std::vector<Row> incrementBoard(std::vector<Row> board)
{
    for (int y = 0; y < board.size(); ++y)
    {
        for (int x = 0; x < board[0].size(); ++x)
        {
            board[y][x]++;
        }
    }
    return board;
}

std::tuple<std::vector<Row>, bool> checkFlashes(std::vector<Row> board, std::set<Coord> &coords)
{
    bool changes = false;
    for (int y = 0; y < board.size(); ++y)
    {
        for (int x = 0; x < board[0].size(); ++x)
        {
            // If element is not present
            if (board[y][x] > 9 &&
                coords.find(std::make_tuple(x, y)) == coords.end())
            {
                coords.insert(std::make_tuple(x, y));
                changes = true;
                for (int i = std::max(0, x - 1); i <= std::min((int)board[0].size()-1, x + 1); ++i)
                {
                    for (int j = std::max(0, y - 1); j <= std::min((int)board.size()-1, y + 1); ++j)
                    {
                        if (coords.find(std::make_tuple(i, j)) == coords.end())
                        {
                            board[j][i] += 1;
                        }
                    }
                }
            }
        }
    }
    return std::make_tuple(board, changes);
}

std::vector<Row> removeOvers(std::vector<Row> board) {
    for (int y = 0; y < board.size(); ++y)
    {
        for (int x = 0; x < board[0].size(); ++x)
        {
            if(board[y][x] > 9) {
                board[y][x] = 0;
            }
        }
    }
    return board;
}

bool allFlashing(std::vector<Row> board) {
    for(auto row:board) {
        for(auto item:row) {
            if(item != 0) {
                return false;
            }
        }
    }
    return true;
}

int main(int argc, char **argv)
{
    std::ifstream file;
    auto file_name = "day_11.txt";
    file.open(file_name);
    if (file.fail())
    {
        std::cout << "File " << file_name << " not accessible\n";
        return 0;
    }
    std::string line;
    std::vector<Row> board;
    // Populates board with text input
    while (std::getline(file, line))
    {
        Row row;
        for (auto item : line)
        {
            row.push_back(item - '0');
        }
        board.push_back(row);
    }
    
    long long int total_flashes = 0;
    int iters = 1;
    while(true)
    {
        board = incrementBoard(board);
        std::set<Coord> coords;
        bool changes = true;
        do
        {
            auto ret = checkFlashes(board, coords);
            std::tie(board, changes) = ret;
        } while(changes);
        board = removeOvers(board);
        std::cout << "Iteration: " << iters << "\n";
        for(auto row:board) {
            for(auto item:row) {
                std::cout << item;
            }
            std::cout << "\n";
        }

        total_flashes += coords.size();

        if(allFlashing(board)) {
            break;
        }
        iters++;
    }
    std::cout << "Final iteration: " << iters << "\n";
    std::cout << "Total flashes: " << total_flashes << "\n";

    return 1;
}