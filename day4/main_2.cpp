#include <fstream>
#include <iostream>
#include <vector>
#include <regex>
#include <cmath>
#include <numeric>

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

    typedef std::tuple<unsigned, unsigned, unsigned> Card;

    std::vector<Card> cards;

    std::string line;
    int i = 1;
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

        cards.emplace_back(i++, points,1);


    }

    for (auto [index, points, count] : cards) {

        std::cout << "index: " << index << " points: " << points << " count: " << count << std::endl;

        for (unsigned k = index; k < index + points; k++) {
            std::get<2>(cards[k]) += count;
        }

    }
    unsigned sum = std::accumulate(cards.begin(), cards.end(), 0, [](const unsigned acc, const Card& card) {
        return acc + std::get<2>(card);
    });

    std::cout << "sum: " << sum << std::endl;


}
