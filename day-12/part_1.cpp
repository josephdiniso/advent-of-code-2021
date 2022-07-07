#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

#define LOG(x) std::cout << x << "\n"

/**
 * This code works but I would prefer to use an iterative solution over
 * using a recursive one. Perhaps some usage of a stack to process each scenario
 * would be a way to do this but for now I'm going to leave it.
 */



int getPaths(std::string currentVal,
             std::map<std::string, std::vector<std::string>> pathMap,
             std::vector<std::string> placesTaken,
             bool noDouble)
{
    if (currentVal == "end")
    {
        return 1;
    }
    placesTaken.push_back(currentVal);
    std::vector<std::string> outputs;
    try
    {
        // Gets all connections between components
        outputs = pathMap.at(currentVal);
    }
    catch (std::out_of_range)
    {
        return 0;
    }

    int sumVal = 0;
    for (auto output : outputs)
    {
        // If not visited or the next place is capital letters and the next
        // place is not start
        int count = std::count(placesTaken.begin(), placesTaken.end(), output);
        if (isupper(output[0]) || (count == 0 || (count == 1 && noDouble && output != "start" && output != "end")))
        {
            bool noDoubleCopy = noDouble;
            if (!isupper(output[0]) && count == 1)
            {
                noDoubleCopy = false;
            }
            sumVal += getPaths(output, pathMap, placesTaken, noDoubleCopy);
        }
    }
    return sumVal;
}

std::vector<std::string> splitLine(std::string line, char delim = '-')
{
    std::vector<std::string> out;
    std::string part = "";
    for (auto letter : line)
    {
        if (letter == delim)
        {
            out.push_back(part);
            part = "";
        }
        else
        {
            part += letter;
        }
    }
    out.push_back(part);
    return out;
}

void append_value(std::map<std::string, std::vector<std::string>> &mapping, std::string key, std::string value)
{
    if (mapping.find(key) != mapping.end())
    {
        mapping[key].push_back(value);
    }
    else
    {
        std::vector<std::string> newVal = {value};
        mapping[key] = newVal;
    }
}

void print_map(std::map<std::string, std::vector<std::string>> &mapping)
{
    std::map<std::string, std::vector<std::string>>::iterator it;

    for (it = mapping.begin(); it != mapping.end(); it++)
    {
        std::cout << "Key: " << it->first << "\n";
        for (auto item : it->second)
        {
            std::cout << item << ", ";
        }
        std::cout << "\n";
    }
}

int main(int argc, char **argv)
{
    std::ifstream file;
    auto file_name = "day_12.txt";
    file.open(file_name);
    if (file.fail())
    {
        std::cout << "File " << file_name << " not accessible\n";
        return 0;
    }
    std::string line;
    // Populates board with text input
    std::map<std::string, std::vector<std::string>> mapping;
    while (std::getline(file, line))
    {
        auto split = splitLine(line, '-');
        append_value(mapping, split[0], split[1]);
        append_value(mapping, split[1], split[0]);
    }
    std::vector<std::string> placesTaken = {};
    auto val = getPaths("start", mapping, placesTaken, true);
    std::cout << val << "\n";
    return 1;
}