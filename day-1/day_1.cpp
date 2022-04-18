#include <iostream>
#include <fstream>
#include <limits.h>

int main()
{
	std::ifstream file;
	file.open("day_1.txt");

	std::string line;
	int prev = INT_MAX;
	int counter = 0;
	while (std::getline(file, line))
	{
		try
		{
			if (stoi(line) > prev)
			{
				counter++;
			}
		} catch (std::invalid_argument) {

		}
		prev = stoi(line);
	}
	std::cout << counter << "\n";

	return 0;
}
