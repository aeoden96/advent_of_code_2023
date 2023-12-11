#include <fstream>
#include <iostream>
#include <vector>
#include <regex>
#include <cmath>

std::pair<std::string, std::string> splitString(const std::string& line) {
    std::regex re{R"([:|])"};
    const std::sregex_token_iterator first{line.begin(), line.end(), re, -1}, last;
    std::vector<std::string> tokens{first, last};

    return {tokens[1], tokens[2]};
}

auto parseNumArray(const std::string& str) {
    int number;
    std::stringstream iss( str );
    std::vector<unsigned> nums;
    while ( iss >> number ) nums.push_back( number );

    return nums;
}

int main() {
    printf("DAY 4\n");
    std::ifstream input_file("input.txt");

    int sum = 0;

    std::string line;
    while (std::getline(input_file, line)) {
        auto [winningNumsStr,myNumsStr] = splitString(line);

        // std::cout << "winning nums: " << winningNumsStr << std::endl;
        // std::cout << "my nums: " << myNumsStr << std::endl;

        auto winningNumbers = parseNumArray(winningNumsStr);
        auto myNumbers = parseNumArray(myNumsStr);

        unsigned points = 0;

        for (auto& num : myNumbers) {
            if (std::ranges::find(winningNumbers, num) != winningNumbers.end()) {
                points++;
            }
        }

        std::cout << "points: " << points << " " << pow(2, points - 1) << std::endl;


        sum += points > 0 ? (int)pow((double)2,  (double)(points - 1)): 0;


    }
    std::cout << "sum: " << sum << std::endl;
}
