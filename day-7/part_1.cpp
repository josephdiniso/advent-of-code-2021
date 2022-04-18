#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <math.h>

#define LOG(x) std::cout << x << "\n"

/**
 * Uses O(n^2) solution, this could almost definitely be improved to a linear
 * solution.
 */


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

int crab_distance(int crab_1, int crab_2)
{
    int diff = abs(crab_1 - crab_2);
    int dist = 0;
    for (int i = 1; i < diff+1; ++i)
    {
        dist += i;
    }
    return dist;
}

int main(int argc, char **argv)
{
    std::ifstream file;
    file.open("day_7.txt");
    std::string line;
    std::getline(file, line);
    auto items = splitLine(line, ',');

    std::sort(items.begin(), items.end());

    auto i0 = std::min_element(items.begin(), items.end());
    auto i1 = std::max_element(items.begin(), items.end());

    int64_t lowest_dist = INT64_MAX;
    int lowest_spot = 0;
    for (int i = *i0; i < *i1; ++i)
    {
        int sum_of_dist = 0;
        for (auto item : items)
        {
            sum_of_dist += crab_distance(item, i);
        }
        if (sum_of_dist < lowest_dist)
        {
            lowest_dist = sum_of_dist;
            lowest_spot = i;
        }
    }
    std::cout << lowest_dist << std::endl;

    return 1;
}