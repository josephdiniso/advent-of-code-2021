#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <math.h>
#include <stack>
#include <string>
#include <string_view>

#define LOG(x) std::cout << x << "\n"

bool valid_close(char start, char end)
{
    if ((start == '(' && end == ')') ||
        (start == '<' && end == '>') ||
        (start == '[' && end == ']') ||
        (start == '{' && end == '}'))
    {
        return true;
    }
    return false;
}
int main(int argc, char **argv)
{
    std::ifstream file;
    file.open("day_10.txt");
    std::string line;

    int illegal_count = 0;
    std::vector<long long int> scores;
    while (std::getline(file, line))
    {
        std::stack<char> s;
        bool valid_string = true;
        for (auto letter : line)
        {
            if (letter == '(' || letter == '<' || letter == '[' || letter == '{')
            {
                s.push(letter);
            }
            else
            {
                char top = s.top();
                s.pop();
                if (!valid_close(top, letter))
                {
                    if (letter == ')')
                    {
                        illegal_count += 3;
                    }
                    else if (letter == ']')
                    {
                        illegal_count += 57;
                    }
                    else if (letter == '}')
                    {
                        illegal_count += 1197;
                    }
                    else if (letter == '>')
                    {
                        illegal_count += 25137;
                    }
                    valid_string = false;
                    break;
                }
            }
        }
        if (valid_string)
        {
            long long int line_score = 0;
            while(s.size() > 0) {
                auto tmp = s.top();
                s.pop();
                line_score *= 5;
                if (tmp == '(') {
                    line_score += 1;
                }
                else if(tmp == '[') {
                    line_score += 2;
                }
                else if(tmp == '{') {
                    line_score += 3;
                }
                else if(tmp == '<') {
                    line_score += 4;
                }
            }
            scores.push_back(line_score);
        }
    }
    std::sort(scores.begin(), scores.end());
    std::cout << "Score: " << scores[round(scores.size() / 2)] << "\n";
    std::cout << "Count: " << illegal_count << "\n";
}