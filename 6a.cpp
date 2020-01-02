#include <range/v3/all.hpp>
#include <iostream>
#include <fstream>
#include <map>
#include <tuple>

using namespace ranges;

int main()
{
    std::ifstream input{"input/6.txt"};
    std::map<std::string,std::vector<std::string>> orbits;

    for(const auto& pair : istream_view<std::string>(input))
    {
        auto pos = pair.find(")");
        auto from = pair.substr(0, pos);
        auto to = pair.substr(pos + 1);
        orbits[to];
        orbits[from].push_back(to);
    }

    std::function<int(const std::string&, int)> countOrbits = [&](const std::string& planet, int depth){
        return accumulate(orbits[planet] | view::transform([=](auto&& child){return countOrbits(child, depth+1);}), depth);
    };

    std::cout << countOrbits("COM", 0) << std::endl;
}
