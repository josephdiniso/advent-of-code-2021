#include <iostream>
#include <fstream>
#include <math.h>

#define LOG(x) std::cout << x << "\n";

int binary_arr_to_int(int *arr, int len)
{
    int val = 0;
    for (int i = len-1; i >= 0; --i)
    {
        val += arr[i] * pow(2, len - i - 1);
    }
    return val;
}

int get_frequency_counts(std::ifstream & file, int * counts, int lineWidth) {
    std::string line;
    int numLines = 0;
    while (std::getline(file, line))
    {
        for (int i = 0; i < lineWidth; ++i)
        {
            if (line[i] == '1')
            {
                counts[i]++;
            }
        }
        numLines++;
    }
    return numLines;
}

int main()
{
    std::ifstream file;
    file.open("day_3.txt");
    int LINE_WIDTH = 12;

    int counts[LINE_WIDTH] = {0};
    int numLines = get_frequency_counts(file, counts, LINE_WIDTH);
    
    int gamma[LINE_WIDTH];
    int epsilon[LINE_WIDTH];
    for (int i = 0; i < LINE_WIDTH; ++i)
    {
        if (counts[i] > numLines / 2)
        {
            gamma[i] = 1;
            epsilon[i] = 0;
        }
        else
        {
            gamma[i] = 0;
            epsilon[i] = 1;
        }
    }

    int gammaVal = binary_arr_to_int(gamma, LINE_WIDTH);
    int epsilonVal = binary_arr_to_int(epsilon, LINE_WIDTH);
    std::cout << gammaVal * epsilonVal << "\n";

    return 1;
}