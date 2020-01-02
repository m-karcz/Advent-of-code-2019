#include <range/v3/all.hpp>
#include <iostream>
#include <fstream>
#include <map>
#include <tuple>
#include <list>
#include <optional>

using namespace ranges;

std::map<std::string,std::vector<std::string>> orbits;

extern const char YOU[] = "YOU";
extern const char SAN[] = "SAN";

template<const char* ToBeFound>
std::optional<std::list<std::string>> findPathTo(const std::string& planet = "COM")
{
    if(planet == ToBeFound)
    {
        return {{planet}};
    }
    for(auto child : orbits[planet])
    {
        if(auto path = findPathTo<ToBeFound>(child))
        {
            path->push_front(planet);
            return path;
        }
    }
    return std::nullopt;
}

int main()
{
    std::ifstream input{"input/6.txt"};

    for(const auto& pair : istream_view<std::string>(input))
    {
        auto pos = pair.find(")");
        auto from = pair.substr(0, pos);
        auto to = pair.substr(pos + 1);
        orbits[to];
        orbits[from].push_back(to);
    }

    if(auto pathToYou = findPathTo<YOU>())
    {
        if(auto pathToSan = findPathTo<SAN>())
        {
            auto [toYou, toSan] = mismatch(*pathToYou, *pathToSan);
            std::cout << distance(toYou, pathToYou->end()) + distance(toSan, pathToSan->end()) - 2 << std::endl;
        }
    }
}
