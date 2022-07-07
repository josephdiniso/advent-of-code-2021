#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>

#define LOG(x) std::cout << x << "\n"

using Array = std::vector<std::vector<int>>;

void print_arr(const Array &arr)
{
    for (auto row : arr)
    {
        for (auto item : row)
        {
            if(item == 1) {
                std::cout << "▓";
            }
            else {
                std::cout << " ";
            }
        }
        std::cout << "\n";
    }
}

std::vector<int> split_line(std::string line)
{
    std::vector<int> split;
    std::string word = "";
    for (auto letter : line)
    {
        if (letter == ',')
        {
            try
            {
                split.push_back(std::stoi(word));
                word = "";
            }
            catch (std::invalid_argument)
            {
                return split;
            }
        }
        else
        {
            word += letter;
        }
    }
    try
    {
        split.push_back(std::stoi(word));
    }
    catch (std::invalid_argument)
    {
    }
    return split;
}

std::tuple<int, int> split_coord(std::string line)
{
    int dir = -1;
    if (line[11] == 'x')
    {
        dir = 0;
    }
    else
    {
        dir = 1;
    }

    std::string num;
    for (int i = 13; i < line.size(); ++i)
    {
        num += line[i];
    }
    int val;
    try
    {
        val = std::stoi(num);
    }
    catch (std::invalid_argument)
    {
        throw std::invalid_argument("Invalid input");
    }
    return std::make_tuple(dir, val);
}

/**
 * Make a new array of size `width` and `height`
 *
 * */
Array make_shape(int width, int height)
{
    Array arr;
    for (int i = 0; i < height; ++i)
    {
        std::vector<int> line;
        for (int j = 0; j < width; ++j)
        {
            line.push_back(0);
        }
        arr.push_back(line);
    }
    return arr;
}

/**
 * Takes an array and performs a center symmetrical fold.
 * */
Array fold_array(const Array &arr, int axis, int coord)
{
    // If folding along x-axis
    Array new_arr;
    if (axis == 0)
    {
        new_arr = make_shape(arr[0].size() / 2, arr.size());
        for (int x = 0; x < arr[0].size() / 2; ++x)
        {
            for (int y = 0; y < arr.size(); ++y)
            {
                new_arr[y][x] = arr[y][x] | arr[y][arr[0].size() - x - 1];
            }
        }
    }
    // If folding along y-axis
    else
    {
        new_arr = make_shape(arr[0].size(), arr.size() / 2);
        for (int x = 0; x < arr[0].size(); ++x)
        {
            for (int y = 0; y < arr.size() / 2; ++y)
            {
                new_arr[y][x] = arr[y][x] | arr[arr.size() - y - 1][x];
            }
        }
    }
    return new_arr;
}

int count_visible_dots(Array arr)
{
    int count = 0;
    for (auto row : arr)
    {
        for (auto item : row)
        {
            if (item == 1)
            {
                count++;
            }
        }
    }
    return count;
}

int main(int argc, char **argv)
{
    std::ifstream file;
    auto file_name = "day_13.txt";
    file.open(file_name);
    if (file.fail())
    {
        std::cout << "File " << file_name << " not accessible\n";
        return 0;
    }
    Array arr;

    std::vector<std::tuple<int, int>> coords;

    std::string line;
    int max_width = 0;
    int max_height = 0;
    bool folding = false;
    std::vector<std::tuple<int, int>> folds;
    while (std::getline(file, line))
    {
        if (line[0] == '\n')
        {
            folding = true;
        }
        if (!folding)
        {
            std::vector<int> split = split_line(line);
            if (split.size() != 2)
            {
                folding = true;
                continue;
            }
            // Add check for argument size being 2
            coords.push_back(std::make_tuple(split[0], split[1]));
            if (split[0] > max_width)
            {
                max_width = split[0];
            }
            if (split[1] > max_height)
            {
                max_height = split[1];
            }
        }
        else
        {
            auto ret = split_coord(line);
            folds.push_back(ret);
            // int axis, coord;
            // std::tie(axis, coord) = ret;
            // std::cout << "Axis: " << axis << ", " << coord << "\n";
        }
    }
    // Populates array
    arr = make_shape(max_width + 1, max_height + 1);
    for (auto item : coords)
    {
        int x, y;
        std::tie(x, y) = item;
        arr[y][x] = 1;
    }
    Array new_arr = arr;
    for (auto fold : folds)
    {
        int dir, coord;
        std::tie(dir, coord) = fold;
        new_arr = fold_array(new_arr, dir, coord);
        // int count = count_visible_dots(new_arr);
        // std::cout << count << "\n";
    }
    // std::cout << new_arr.size();
    print_arr(new_arr);
}