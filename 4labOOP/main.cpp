#include "CSVparser.h"

int main() {
    std::ifstream file("test.csv");
    if (file.fail()) {
        std::cout << "The file could not be opened\n" << std::endl;
        return 0;
    }

    CSVparser<int, double, std::string> CSVparser(file);
    for (auto tuple : CSVparser) {
        std::cout << tuple << std::endl;
    }

    file.close();
    return 0;
}