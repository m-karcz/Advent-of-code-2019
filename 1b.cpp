#include <range/v3/all.hpp>
#include <iostream>
#include <fstream>

using namespace ranges;

int calculateFuel(int mass)
{
    return mass / 3 - 2;
}

int calculateTotalFuel(int mass)
{
    auto fuelNeeded = calculateFuel(mass);
    return fuelNeeded > 0 ? fuelNeeded + calculateTotalFuel(fuelNeeded) : 0;
}

int main()
{
    std::ifstream input{"input/1.txt"};
    std::cout << accumulate(istream_view<int>(input) | view::transform(calculateTotalFuel), 0) << '\n';
}