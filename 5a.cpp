#include <range/v3/all.hpp>
#include <iostream>
#include <fstream>
#include <map>

using namespace ranges;

int main()
{
    std::ifstream input{"input/5.txt"};
    auto data = getlines_view(input, ',') 
                | view::transform([](auto&& str){return std::stoi(str);})
                | view::enumerate
                | to<std::map<int,int>>;


    bool done = false;
    auto stream = data | view::values;
    auto it = begin(stream);

    const auto getInput = [](){return 1;};
    const auto putOutput = [](int output){std::cout << output << std::endl;};

    while(not done)
    {
        auto instruction = *it;
        const auto getIth = [&](int th){auto val = instruction % th; instruction /= th; return val;};
        int opcode = getIth(100);
        int argModes[] = {getIth(10), getIth(10), getIth(10)};
        const auto getArg = [&](int arg)->auto*{++it; return argModes[arg] ? &*it : &data[*it]; };
        const auto getArgs = [&](int amount){return view::ints(0, amount) | view::transform(getArg) | to<std::vector>;};
        const auto arith = [&](auto op){auto args = getArgs(3); *args[2] = op(*args[0], *args[1]);};
        switch(opcode)
        {
            case 1/*add*/:  arith(std::plus<int>{});       break;
            case 2/*mul*/:  arith(std::multiplies<int>{}); break; 
            case 3/*in*/:   *getArg(0) = getInput();       break;
            case 4/*out*/:  putOutput(*getArg(0));         break;
            case 99/*hlt*/: done = true;                   break;
        }
        ++it;
    }
}