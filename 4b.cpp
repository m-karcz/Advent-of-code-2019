#include <range/v3/all.hpp>
#include <iostream>
#include <boost/container/flat_map.hpp>

using namespace ranges;

bool hasDouble(const std::string& str)
{
    boost::container::flat_map<char,uint8_t> digits;
    digits.reserve(6);
    for(auto digit : str)
    {
        digits[digit]++;
    }
    return contains(digits | view::values, 2);
}

int main()
{
    std::cout << distance(view::ints(372304,847060)
                          | view::transform([](int i){return std::to_string(i);})
                          | view::cache1
                          | view::filter(is_sorted)
                          | view::filter(hasDouble)) << std::endl;

}