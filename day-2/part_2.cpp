#include <iostream>
#include <fstream>

#define LOG(x) std::cout << x << "\n"

int main()
{
    std::ifstream file;
    file.open("day_2.txt");

    std::string line;

    int depth = 0;
    int forward = 0;
    int aim = 0;
    while (std::getline(file, line))
    {
        std::string delim = " ";

        std::string command = line.substr(0, line.find(delim));
        line.erase(0, line.find(delim) + delim.length());
        int val = stoi(line);

        if (command == "forward")
        {
            forward += val;
            depth += aim * val;
        }
        else if (command == "up")
        {
            aim -= val;
        }
        else if (command == "down")
        {
            aim += val;
        }
    }
    std::cout << depth * forward << std::endl;
    return 1;
}