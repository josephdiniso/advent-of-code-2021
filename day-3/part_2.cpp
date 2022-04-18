#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <tuple>

#define LOG(x) std::cout << x << "\n";

int binary_arr_to_int(std::vector<int> arr)
{
    int val = 0;
    for (int i = arr.size() - 1; i >= 0; --i)
    {
        val += arr[i] * pow(2, arr.size() - i - 1);
    }
    return val;
}

char get_significant_frequency(std::vector<std::string> arr, int filterIndex)
{
    int total = arr.size();
    int count = 0;
    for (std::string line : arr)
    {
        if (line[filterIndex] == '1')
        {
            count++;
        }
    }
    if (count >= float(total) / 2)
    {
        return '1';
    }
    return '0';
}

using BinaryLines = std::vector<std::string>;

BinaryLines filter_lines(std::vector<std::string> arr, char filterValue, int filterIndex)
{
    std::vector<std::string> accepts;
    for (std::string line : arr)
    {
        if (line[filterIndex] == filterValue)
        {
            accepts.push_back(line);
        }
    }
    return accepts;
}

char oppositeFreq(char freq)
{
    if (freq == '1')
    {
        return '0';
    }
    else
    {
        return '1';
    }
}

int main()
{
    std::ifstream file;
    file.open("day_3.txt");

    BinaryLines lines;
    std::string line;
    while (std::getline(file, line))
    {
        lines.push_back(line);
    }

    std::vector<std::string> oxygen;
    std::vector<std::string> co2;
    for (auto item : lines)
    {
        oxygen.push_back(item);
        co2.push_back(item);
    }

    int filterIndexOxygen = 0;
    int filterIndexCo2 = 0;
    while (oxygen.size() > 1 || co2.size() > 1)
    {
        if (oxygen.size() > 1)
        {
            char freq = get_significant_frequency(oxygen, filterIndexOxygen);
            auto newOxygen = filter_lines(oxygen, freq, filterIndexOxygen);
            oxygen = newOxygen;
            filterIndexOxygen++;
        }
        if (co2.size() > 1)
        {
            char freqCo2 = oppositeFreq(get_significant_frequency(co2, filterIndexCo2));
            auto newCo2 = filter_lines(co2, freqCo2, filterIndexCo2);
            co2 = newCo2;
            filterIndexCo2++;
        }
    }
    std::vector<int> oxygenArr;
    std::vector<int> co2Arr;
    for (int i = 0; i < oxygen[0].size(); ++i)
    {
        oxygenArr.push_back(oxygen[0][i] - 48);
        co2Arr.push_back(co2[0][i] - 48);
    }
    int oxygenInt = binary_arr_to_int(oxygenArr);
    int co2Int = binary_arr_to_int(co2Arr);
    LOG(oxygenInt * co2Int);
    return 1;
}