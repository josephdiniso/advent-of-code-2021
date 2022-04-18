#include <iostream>
#include <fstream>
#include <limits.h>
#include <vector>

/**
 * Advent of code day 1 part 2. 
 * Uses an algorithm of O(n) runtime and O(3)=O(1) space complexity.
 */

int convert_str_to_int(std::string line)
{
    try
    {
        return stoi(line);
    }
    catch (std::invalid_argument)
    {
    }
    return 0;
}

int main()
{
    std::ifstream file;
    file.open("day_1.txt");

    std::string line;
    int prev = INT_MAX;
    int counter = 0;

    int sumVal = 0;
    int index = 0;
    std::vector<int> history;
    while (std::getline(file, line))
    {
        int lineVal = convert_str_to_int(line);

        if (index >= 3)
        {
            int nextVal = sumVal - history[0] + lineVal;
            if (sumVal < nextVal)
            {
                counter++;
            }
            sumVal = nextVal;
        }
        history.push_back(lineVal);
        std::cout << "SHOWING ELEMENTS: " << '\n';
        for (int element : history)
        {
            std::cout << element << "\n";
        }
        if (history.size() > 3)
        {
            history.erase(history.begin());
        }
        sumVal += lineVal;

        index++;
    }
    std::cout << counter;

    return 0;
}
