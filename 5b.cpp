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
    auto instructionPointer = 0;

    const auto getInput = [](){return 5;};
    const auto putOutput = [](int output){std::cout << output << '\n';};

    while(not done)
    {
        auto instruction = data[instructionPointer];
        const auto getIth = [&](int th){auto val = instruction % th; instruction /= th; return val;};
        int opcode = getIth(100);
        int argModes[] = {getIth(10), getIth(10), getIth(10)};
        const auto getArg = [&](int arg)->auto*{++instructionPointer; return argModes[arg] ? &data[instructionPointer] : &data[data[instructionPointer]]; };
        const auto getArgs = [&](int amount){return view::ints(0, amount) | view::transform(getArg) | to<std::vector>;};
        const auto arith = [&](auto op){auto args = getArgs(3); *args[2] = op(*args[0], *args[1]);};
        const auto jumpIf = [&](bool value){auto args = getArgs(2); if(!!*args[0] == value){instructionPointer = *args[1] - 1;}};
        switch(opcode)
        {
            case 1/*add*/:      arith(std::plus<int>{});       break;
            case 2/*mul*/:      arith(std::multiplies<int>{}); break; 
            case 3/*in*/:       *getArg(0) = getInput();       break;
            case 4/*out*/:      putOutput(*getArg(0));         break;
            case 5/*je true*/:  jumpIf(true);                  break;
            case 6/*je false*/: jumpIf(false);                 break;
            case 7/*lt*/:       arith(std::less<int>{});       break;
            case 8/*eq*/:       arith(std::equal_to<int>{});   break;
            case 99/*hlt*/:     done = true;                   break;
        }
        ++instructionPointer;
    }
}