#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

typedef std::vector<std::vector<std::string>> Matrix;
typedef std::vector<std::string> MatrixRow;

bool isNumber(const std::string& s)
{
    return !s.empty() && std::ranges::find_if(s.begin(),
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

bool isSpecialChar(const std::string& s) {
    return s != "." && !isNumber(s);
}

auto tranformToVector(std::ifstream& input_file) {
    input_file.clear();
    input_file.seekg(0, std::ios::beg);
    Matrix input;

    char character;
    input.emplace_back();

    while (input_file.get(character)) {
        if (character == '\n') {
            input.emplace_back();
        } else {
            input.back().emplace_back(1, character);
        }
    }

    return input;
}

auto printMatrix(const Matrix& matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {

            std::cout <<  '[' <<matrix[i][j] << ']';
        }

        std::cout << std::endl;
    }
}

std::string getNumAtIndex(const MatrixRow& line, const int i) {

    int startInd = i;
    int endInd = i;

    for (int j = i; j >= 0; j--) {
        if (isNumber(line[j])) {
            startInd = j;
        } else {
            break;
        }
    }

    for (int j = i; j < line.size(); j++) {
        if (isNumber(line[j])) {
            endInd = j;
        } else {
            break;
        }
    }

    std::string numStr;
    for (int j = startInd; j <= endInd; j++) {
        numStr += line[j];
    }

    return numStr;
}

int jump(const MatrixRow& row, const int j) {
    int jumpAmount = 0;
    for (int k = j; k < row.size(); k++) {
        if (isNumber(row[k])) {
            jumpAmount++;
        } else {
            break;
        }
    }

    return jumpAmount;
}

auto isSpecialMatrixChar(const Matrix& matrix, const int i, const int j) {
    try {
        return isSpecialChar(matrix.at(i).at(j));
    } catch (const std::out_of_range&) {
        return false;
    }
}

bool checkForSpecialChar(const Matrix& matrix, const int i, const int j) {
    const std::vector<std::pair<int, int>> directions = {
        {0, 1},
        {0, -1},
        {1, 0},
        {-1, 0},
        {1, 1},
        {1, -1},
        {-1, 1},
        {-1, -1}
    };

    return std::ranges::any_of(directions, [&](const auto& direction) {
      return isSpecialMatrixChar(matrix, i + direction.first, j + direction.second);
    });
}

auto getSoroundingNumbers(const Matrix& matrix, const int i, const int j) {
    const std::vector<std::pair<int, int>> directions = {
        {0, 1},
        {0, -1},
        {1, 0},
        {-1, 0},
        {1, 1},
        {1, -1},
        {-1, 1},
        {-1, -1}
    };

    std::vector<std::string> soroundingNumbers;

    for (const auto& direction : directions) {
        try {
            if (isNumber(matrix.at(i + direction.first).at(j + direction.second))) {
                soroundingNumbers.emplace_back(matrix.at(i + direction.first).at(j + direction.second));
            }
        } catch (const std::out_of_range&) {
            continue;
        }
    }

    return soroundingNumbers;
}


int main() {
    printf("DAY 3\n");
    std::ifstream input_file("input.txt");

    int sum = 0;
    auto matrix = tranformToVector(input_file);
    auto matrix2 = tranformToVector(input_file);


    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            if (isNumber(matrix[i][j])){
                const std::string wholeNum = getNumAtIndex(matrix[i], j);

                matrix2[i][j] = wholeNum;
            }
        }
    }

    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            if (matrix2[i][j] == "*") {
                auto soroundingNumbers = getSoroundingNumbers(matrix2, i, j);
                std::sort(soroundingNumbers.begin(), soroundingNumbers.end());
                soroundingNumbers.erase(std::unique(soroundingNumbers.begin(), soroundingNumbers.end()), soroundingNumbers.end());

                if (soroundingNumbers.size() != 2) {
                    matrix2[i][j] = ".";
                } else {
                    sum += (std::stoi(soroundingNumbers[0]) * std::stoi(soroundingNumbers[1]));
                }

            } else if (!isNumber(matrix2[i][j]) && matrix2[i][j] != ".") {
                matrix2[i][j] = ".";
            }
        }
    }

    printMatrix(matrix2);

    std::cout << "Sum: " << sum << std::endl;
}