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
    long number;
    std::stringstream iss( str );
    std::vector<long> nums;
    while ( iss >> number ) nums.push_back( number );

    return nums;
}


class Range {
public:
    Range(const long start, const long end) : start(start), end(end) {}

    long start;
    long end;
    bool isChanged = false;

    friend std::ostream& operator<<(std::ostream& os, const Range& range) {
        os << "[" << range.start << ", " << range.end << "]";
        return os;
    }


    void offset (const long offset) {
        this->isChanged = true;
        this->start += offset;
        this->end += offset;
    }
};

auto printVector(const std::vector<Range>& vec, const long index = -1) {
    std::cout << "vector: ";

    long i = 0;
    for (auto r : vec) {
        if (i == index) {
            std::cout << ">";
        }
        std::cout << r << " ";
        i++;
    }
    std::cout << std::endl;
}

bool intersect(long A_begin, long A_end, long B_begin, long B_end) {
    return A_begin <= B_end && A_end >= B_begin;
}



int main() {
    printf("DAY 5\n");
    std::ifstream input_file("input.txt");

    std::string first_line;
    std::getline(input_file, first_line);

    std::string numbers_str = first_line.substr(7, first_line.length());

    auto numbers = parseNumArray(numbers_str);

    std::vector<Range> ranges;

    for (long i = 0; i < numbers.size(); i += 2) {
        ranges.emplace_back(numbers[i], numbers[i] + numbers[i + 1] - 1);
    }

    std::vector isChanged(numbers.size(), false);

    std::string line;
    while (std::getline(input_file, line)) {

        if (line.empty()) {
            continue;
        }

        if(line.at(line.length() - 1) == ':') {
            std:: cout << line << std::endl;

            for (auto& r : ranges) {
                r.isChanged = false;
            }
            continue;
        }

        auto currentMap = parseNumArray(line);
        long destStart = currentMap[0];
        long sourceStart = currentMap[1];
        long sourceEnd = sourceStart + currentMap[2] - 1;
        long offset = (long)destStart - (long)sourceStart;

        std::cout <<  "source: [" << sourceStart << " " << sourceEnd << "]" <<  " offset: " << offset << std::endl;

        for(long k = 0;; k++) {
            if (k >= ranges.size()) {
                break;
            }

            if (ranges[k].isChanged)  continue;

            if(intersect(ranges[k].start, ranges[k].end, sourceStart, sourceEnd) ) {
                std::cout << "   intersect" << std::endl;

                if (ranges[k].start < sourceStart) {
                    auto numsBefore = Range(ranges[k].start, sourceStart - 1);
                    std::cout << "   numsBefore: " << numsBefore << std::endl;

                    ranges.emplace_back(numsBefore);

                    ranges[k].start = sourceStart;
                }

                if (ranges[k].end > sourceEnd) {
                    auto numsAfter = Range(sourceEnd + 1, ranges[k].end);
                    std::cout << ranges[k] <<  "   numsAfter: " << numsAfter << std::endl;

                    ranges.emplace_back(numsAfter);

                    ranges[k].end = sourceEnd;
                }

                std::cout << ranges[k] ;
                ranges[k].offset(offset);

            }
        }
    }

    printVector(ranges);

    auto min = ranges[0].start;
    for (auto range : ranges) {

        if (range.start < min) {
            min = range.start;
        }
    }

    std::cout << "min: " << min << std::endl;
}
