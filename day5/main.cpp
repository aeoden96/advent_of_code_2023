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
    unsigned number;
    std::stringstream iss( str );
    std::vector<unsigned> nums;
    while ( iss >> number ) nums.push_back( number );

    return nums;
}

int main() {
    printf("DAY 5\n");
    std::ifstream input_file("input.txt");

    int sum = 0;

    std::string first_line;
    std::getline(input_file, first_line);

    std::string numbers_str = first_line.substr(7, first_line.length());

    auto numbers = parseNumArray(numbers_str);

    std::cout << numbers.size() << std::endl;

    std::vector<bool> isChanged(numbers.size(), false);

    std::string line;
    while (std::getline(input_file, line)) {

        if (line.empty()) {
            continue;
        }

        if(line.at(line.length() - 1) == ':') {
            std:: cout << line << std::endl;
            //reset isChanged
            isChanged = std::vector<bool>(numbers.size(), false);
            continue;
        }

        auto currentMap = parseNumArray(line);

        std::cout << "currentMap: " << currentMap.size() << std::endl;

        unsigned destStart = currentMap[0];
        unsigned sourceStart = currentMap[1];
        unsigned range = currentMap[2];

        std::cout << "destStart: " << destStart << " sourceStart: " << sourceStart << " range: " << range << std::endl;


        unsigned sourceEnd = sourceStart + range - 1;
        int offset = (int)destStart - (int)sourceStart;

        for (int i = 0; i < numbers.size(); i++) {
            auto num = numbers[i];

            if (num >= sourceStart && num <= sourceEnd && !isChanged[i]) {
                numbers[i] = num + offset;
                std::cout << "num: " << num << " -> " << numbers[i] << std::endl;
                isChanged[i] = true;
            }
        }

    }

    int min = numbers[0];
    for (auto num : numbers) {
        std::cout << num << std::endl;

        if (num < min) {
            min = num;
        }
    }

    std::cout << "min: " << min << std::endl;
}
