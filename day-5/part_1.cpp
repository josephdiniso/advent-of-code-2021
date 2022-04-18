#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#define LOG(x) std::cout << x << "\n"

inline std::vector<int> splitLine(std::string s, char delim = ' ')
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

inline std::vector<std::string> getCoords(std::string line)
{
    std::vector<std::string> words;
    std::string tmp = "";
    for (auto letter : line)
    {
        if (letter == ' ')
        {
            if (tmp != "->")
            {
                words.push_back(tmp);
            }
            tmp.clear();
        }
        else
        {
            tmp += letter;
        }
    }
    if (tmp != "->")
    {
        words.push_back(tmp);
    }
    tmp.clear();
    return words;
}

std::vector<std::vector<int>> makeTable(int maxX, int maxY)
{
    std::vector<std::vector<int>> out;
    for (int i = 0; i <= maxY; ++i)
    {
        std::vector<int> tmp(maxX);
        out.push_back(tmp);
    }
    return out;
}

int main()
{
    std::ifstream file;
    file.open("day_5.txt");
    std::string line;
    int maxX = 0;
    int maxY = 0;
    std::vector<std::vector<int>> first;
    std::vector<std::vector<int>> second;
    while (std::getline(file, line))
    {
        auto words = getCoords(line);
        auto c1 = splitLine(words[0], ',');
        if (c1[0] > maxX)
        {
            maxX = c1[0];
        }
        if (c1[1] > maxY)
        {
            maxY = c1[1];
        }
        auto c2 = splitLine(words[1], ',');
        if (c2[0] > maxX)
        {
            maxX = c2[0];
        }
        if (c2[1] > maxY)
        {
            maxY = c2[1];
        }
        first.push_back(c1);
        second.push_back(c2);
    }
    auto table = makeTable(maxX, maxY);
    for (int i = 0; i < first.size(); ++i)
    {
        // If a vertical line (i.e. x coord is the same)
        if (first[i][0] == second[i][0])
        {
            // Start at lower y coordinate
            int minVal = std::min(first[i][1], second[i][1]);
            // End at higher y coordinate
            int maxVal = std::max(first[i][1], second[i][1]);
            for (int j = minVal; j <= maxVal; ++j)
            {
                table[j][first[i][0]] += 1;
            }
        }
        // If a horizontal line (i.e. y coord is the same)
        else if (first[i][1] == second[i][1])
        {
            // Start at lower x coordinate
            int minVal = std::min(first[i][0], second[i][0]);
            // End at higher x coordinate
            int maxVal = std::max(first[i][0], second[i][0]);
            for (int j = minVal; j <= maxVal; ++j)
            {
                table[first[i][1]][j] += 1;
            }
        }
        // For part 1, comment out the inside of this because diagonals should
        // not count
        else
        {
            int dirX = 1;
            int dirY = 1;
            // If going left
            if (first[i][0] > second[i][0])
            {
                dirX = -1;
            }
            // If going up
            if (first[i][1] > second[i][1])
            {
                dirY = -1;
            }
            std::cout << first[i][0] << "," << first[i][1] << " -> " << second[i][0] << "," << second[i][1] << "\n";
            for (int j = 0; j <= abs(first[i][0] - second[i][0]); ++j)
            {
                int newY = first[i][1] + j * dirY;
                int newX = first[i][0] + j * dirX;
                table[newY][newX] += 1;
            }
        }
    }
    int counter = 0;
    for (auto row : table)
    {
        for (auto item : row)
        {
            if (item >= 2)
            {
                counter++;
            }
        }
    }
    LOG(counter);
}