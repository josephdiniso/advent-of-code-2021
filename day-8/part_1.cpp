#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <string_view>

#define LOG(x) std::cout << x << "\n"

/**
Explanation of the problem:

The input data is many lines of two parts:

The first is signals that are activated. We need to deduce what number is being
activated simply from the signals that are activated and mismatched.

The second is the signal data to the segment displays. Using the information
from the first we need to know which numbers are being turned on.
 */

inline std::vector<std::string> splitLine(std::string s, char delim = ' ')
{
    bool adding = true;
    std::vector<std::string> vals;
    std::string val = "";
    for (auto letter : s)
    {
        if (letter == delim)
        {
            if (val.size() > 0)
            {
                vals.push_back(val);
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
        vals.push_back(val);
        val.clear();
    }
    return vals;
}

int main(int argc, char **argv)
{
    std::ifstream file;
    file.open("day_8.txt");
    std::string line;
    std::vector<std::vector<std::string>> ins;
    std::vector<std::vector<std::string>> outs;
    while (std::getline(file, line))
    {
        auto split = splitLine(line, '|');
        ins.push_back(splitLine(split[0], ' '));
        outs.push_back(splitLine(split[1], ' '));
    }
    int count = 0;
    for (int i = 0; i < ins.size(); ++i)
    {
        std::vector<std::string> s(10);
        for (int j = 0; j < ins[i].size(); ++j)
        {
            switch (ins[i][j].size())
            {
            case 2:
                s[1] = ins[i][j];
                break;
            case 3:
                s[7] = ins[i][j];
                break;
            case 4:
                s[4] = ins[i][j];
                break;
            case 7:
                s[8] = ins[i][j];
                break;
            default:
                break;
            }
        }
        break;
    }
    return 1;
}