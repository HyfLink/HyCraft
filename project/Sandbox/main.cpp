#include "HyJson/Json.hpp"
#include <iostream>
#include <sstream>

int main(void)
{
    using namespace hy::json;

    Json j = {
        {"A", 1},
        {"B", 2},
        {"C", nullptr},
        {"D", true},
        {"E", false},
        {"F", "Hello"},
        {"G", {{"What", 2}, {"When", 3}, {"Hew", nullptr}}},
        {"H", "World"},
    };

    j["X"] = JArray(10);
    j["Y"] = JArray(10);
    j["Z"] = JArray(10);
    j["Z"][2] = JArray(10);
    j["X"][0] = 1;
    j["X"][1] = 1;
    j["X"][2] = 2;
    j["X"][3] = nullptr;
    j["X"][9] = true;
    j["X"][8] = {{"AB", true}, {"CD", false}};
 
    std::cout << j << std::endl;

    return 0;
}