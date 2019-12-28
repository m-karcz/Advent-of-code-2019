#include <range/v3/all.hpp>
#include <iostream>

using namespace ranges;

bool hasDouble(const std::string& str)
{
    return adjacent_find(str) != end(str);
}

int main()
{
    std::cout << distance(view::ints(372304,847060)
                          | view::transform([](int i){return std::to_string(i);})
                          | view::cache1
                          | view::filter(is_sorted)
                          | view::filter(hasDouble)) << std::endl;

}