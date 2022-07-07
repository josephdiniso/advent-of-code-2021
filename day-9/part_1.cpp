#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <stack>
#include <string>
#include <string_view>

#define LOG(x) std::cout << x << "\n"

/**
 Part 2 Notes:

 Recursive solution could solve this as long as all members of the basin
 are recorded, although I'd like to avoid doing any form of recursion.
 */

using Coordinate = std::tuple<int, int>;

std::vector<uint> getNeighbors(std::vector<std::vector<uint>> &heightMap,
                               int x,
                               int y)
{
    std::vector<uint> neighbors;
    if (x > 0)
    {
        neighbors.push_back(heightMap[y][x - 1]);
    }
    if (y > 0)
    {
        neighbors.push_back(heightMap[y - 1][x]);
    }
    if (x < heightMap[0].size() - 1)
    {
        neighbors.push_back(heightMap[y][x + 1]);
    }
    if (y < heightMap.size() - 1)
    {
        neighbors.push_back(heightMap[y + 1][x]);
    }
    return neighbors;
}

std::vector<Coordinate> getNeighborCoords(std::vector<std::vector<uint>> &heightMap,
                                          int x,
                                          int y)
{
    std::vector<Coordinate> neighbors;
    if (x > 0)
    {
        auto s = std::make_tuple(x - 1, y);
        neighbors.push_back(s);
    }
    if (y > 0)
    {
        auto s = std::make_tuple(x, y - 1);
        neighbors.push_back(s);
    }
    if (x < heightMap[0].size() - 1)
    {
        auto s = std::make_tuple(x + 1, y);
        neighbors.push_back(s);
    }
    if (y < heightMap.size() - 1)
    {
        auto s = std::make_tuple(x, y + 1);
        neighbors.push_back(s);
    }
    return neighbors;
}

int main(int argc, char **argv)
{
    std::ifstream file;
    file.open("day_9.txt");
    std::string line;
    std::vector<std::vector<uint>> heightMap;
    while (std::getline(file, line))
    {
        std::vector<uint> row;
        for (auto height : line)
        {
            row.push_back(height - '0');
        }
        heightMap.push_back(row);
    }
    int risk_sum = 0;
    std::vector<Coordinate> min_points;
    for (int x = 0; x < heightMap[0].size(); ++x)
    {
        for (int y = 0; y < heightMap.size(); ++y)
        {
            auto neighbors = getNeighbors(heightMap, x, y);
            bool lowest = true;
            for (auto neighbor : neighbors)
            {
                if (neighbor <= heightMap[y][x])
                {
                    lowest = false;
                    break;
                }
            }
            if (lowest)
            {
                risk_sum = risk_sum + heightMap[y][x] + 1;
                min_points.push_back(std::make_tuple(x, y));
            }
        }
    }

    std::vector<int> counts;
    for (auto point : min_points)
    {
        std::stack<Coordinate> s;
        std::set<Coordinate> alreadyUsed;
        s.push(point);
        alreadyUsed.insert(point);
        int count = 1;
        while (s.size() > 0)
        {
            auto tmp = s.top();
            s.pop();
            int base_x;
            int base_y;
            std::tie(base_x, base_y) = tmp;
            auto neighborCoords = getNeighborCoords(heightMap, base_x, base_y);
            for (auto coord : neighborCoords)
            {
                int x;
                int y;
                std::tie(x, y) = coord;
                if (heightMap[y][x] > heightMap[base_y][base_x] && heightMap[y][x] < 9)
                {
                    // If coord is not already used
                    if (alreadyUsed.find(coord) == alreadyUsed.end())
                    {
                        s.push(coord);
                        alreadyUsed.insert(coord);
                        count++;
                    }
                }
            }
        }
        counts.push_back(count);
    }
    std::sort(counts.begin(), counts.end());
    int end_index = counts.size() - 1;
    int product = 1;
    for(int i=counts.size()-1; i>counts.size()-4; --i) {
        product *= counts[i];
    }
    std::cout << "Product: " << product << "\n";
    return 1;
}