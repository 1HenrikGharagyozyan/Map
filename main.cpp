#include <iostream>
#include "Map.h"

int main() 
{
    std::cout << std::boolalpha;

    Map<int, std::string> m;

    // insert / operator[]
    m[1] = "one";
    m[2] = "two";
    m.insert({ 3, "three" });

    // insert_or_assign
    m.insert_or_assign(2, "TWO");

    // try_emplace
    m.try_emplace(4, "four");

    // emplace
    m.emplace(std::make_pair(5, "five"));

    // at / operator[]
    std::cout << "m.at(1): " << m.at(1) << "\n";
    std::cout << "m[2]: " << m[2] << "\n";

    // contains / count
    std::cout << "Contains key 3? " << m.contains(3) << "\n";

    // find
    auto it = m.find(4);
    if (it != m.end())
        std::cout << "Found key 4: " << it->second << "\n";

    // erase
    m.erase(1);
    std::cout << "After erase(1), contains(1): " << m.contains(1) << "\n";

    // lower_bound / upper_bound
    auto lb = m.lower_bound(3);
    auto ub = m.upper_bound(3);
    if (lb != m.end()) std::cout << "lower_bound(3): " << lb->first << "\n";
    if (ub != m.end()) std::cout << "upper_bound(3): " << ub->first << "\n";

    // extract
    auto extracted = m.extract(3);
    std::cout << "Extracted key 3: " << extracted.second << "\n";

    // merge
    Map<int, std::string> other;
    other[6] = "six";
    m.merge(other);
    std::cout << "After merge: contains 6? " << m.contains(6) << "\n";

    // swap
    Map<int, std::string> temp;
    temp[100] = "hundred";
    swap(m, temp);
    std::cout << "After swap, temp contains key 2? " << temp.contains(2) << "\n";

    // iteration + structured bindings
    std::cout << "\nFinal Map content:\n";
    for (auto& [k, v] : temp) 
        std::cout << k << ": " << v << "\n";

    // comparisons
    Map<int, std::string> a{ {1, "x"}, {2, "y"} };
    Map<int, std::string> b{ {1, "x"}, {2, "y"} };
    std::cout << "a == b? " << (a == b) << "\n";
    std::cout << "a < b? " << (a < b) << "\n";
}
