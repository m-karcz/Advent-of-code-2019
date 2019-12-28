#include <range/v3/all.hpp>
#include <iostream>
#include <fstream>
#include <map>

using namespace ranges;

int main()
{
    std::ifstream input{"input/2.txt"};
    auto data = getlines_view(input, ',') 
                | view::transform([](auto&& str){return std::stoi(str);})
                | view::enumerate
                | to<std::map<int,int>>;

    data[1] = 12;
    data[2] = 2;

    int op;
    int lhs;
    int rhs;

    for(auto [index, value] : data)
    {
        switch(index % 4)
        {
            case 0:
            {
                op = value;
                if(op == 99)
                {
                    std::cout << data[0] << '\n';
                    return 0;
                }
                break;
            }
            case 1: lhs = value; break;
            case 2: rhs = value; break;
            case 3:
            {
                switch(op)
                {
                    case 1: data[value] = data[lhs] + data[rhs]; break;
                    case 2: data[value] = data[lhs] * data[rhs]; break;
                }
            }
        }
    }
}