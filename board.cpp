#include <vector>
#include <variant>
#include <iostream>
#include <string>



int main(int argc, char const *argv[])
{
    std::vector<std::variant<int, float, std::string>> vectorName;

    vectorName.emplace_back(1);
    vectorName.emplace_back(3.5);
    vectorName.emplace_back("hugo");

    for (auto& v : vectorName) {
        std::cout << v << "\n";
    }

    return 0;
}
