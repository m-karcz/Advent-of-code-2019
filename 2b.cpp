#include <range/v3/all.hpp>
#include <iostream>
#include <fstream>
#include <map>

using namespace ranges;

int main()
{
    std::ifstream input{"input/2.txt"};
    auto originalData = getlines_view(input, ',') 
                        | view::transform([](auto&& str){return std::stoi(str);})
                        | view::enumerate
                        | to<std::map<int,int>>;


    int op;
    int lhs;
    int rhs;

    for(auto noun : view::ints(0,100))
    {
        for(auto verb : view::ints(0,100))
        {
            auto data = originalData;

            data[1] = noun;
            data[2] = verb;

            bool done = false;

            for(auto [index, value] : data)
            {
                if(done)
                {
                    break;
                }
                switch(index % 4)
                {
                    case 0:
                    {
                        op = value;
                        if(op == 99)
                        {
                            //std::cout << data[0] << '\n';
                            if(data[0] == 19690720)
                            {
                                std::cout << 100 * noun + verb << std::endl;
                                return 0;
                            }
                            else
                            {
                                done = true;
                            }
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
    }
}