#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include <boost/multiprecision/cpp_int.hpp>

#define LOG(x) std::cout << x << "\n"

using namespace boost::multiprecision;

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

std::vector<int128_t> processDay(std::vector<int128_t> arr)
{
    auto births = arr[0];
    arr.erase(arr.begin());
    arr.push_back(births);
    arr[6] += births;
    return arr;
}

int main(int argc, char **argv)
{
    int days = 256;
    if (argc == 1)
    {
        std::cout << "No number of days selected, defaulting to " << days << "\n";
    }
    else if (argc == 2)
    {
        std::size_t pos;
        std::string arg = argv[1];
        days = std::stoi(arg, &pos);
        if (pos < arg.size())
        {
            std::cout << "Invalid Argument\n";
            return 0;
        }
        std::cout << "Using " << days << "days\n";
    }
    std::vector<int128_t> arr(9);
    for (int i = 0; i < arr.size(); ++i)
    {
        arr[i] = 0;
    }

    std::ifstream file;
    file.open("day_6.txt");
    std::string line;
    std::getline(file, line);
    auto items = splitLine(line, ',');
    for (auto item : items)
    {
        arr[item]++;
    }

    for (int i = 0; i < days; ++i)
    {
        arr = processDay(arr);
        std::cout << "DAY: " << i + 1 << "\n";
        for (auto item : arr)
        {
            std::cout << item << ", ";
        }
        std::cout << "\n";
    }

    int128_t sum = 0;
    std::cout << "COUNTING: \n";
    for (auto item : arr)
    {
        sum += item;
    }

    std::cout << "Sum: " << sum << "\n";

    return 1;
}