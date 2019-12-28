#include <range/v3/all.hpp>
#include <iostream>
#include <fstream>

using namespace ranges;

int main()
{
    std::ifstream input{"input/1.txt"};
    std::cout << accumulate(istream_view<int>(input) | view::transform([](auto i){return i / 3 - 2;}), 0) << '\n';
}