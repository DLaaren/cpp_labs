#pragma once
#include <fstream> 
#include <string>
#include <tuple>
#include <iostream>
#include <sstream>

template<typename ...Args> 
class CSVparser {
    private:
        std::ifstream &input_;
        std::streampos fileStart_;

    public:
        CSVparser(std::ifstream &input) : input_(input), lastTuple_(false) {
            fileStart_ = input_.tellg();
            currentPos_ = fileStart_;
        }

        class Tuple {
            private:
                CSVParser &CSVparser_;
                std::tuple<Args...> tuple_;
                bool lastTuple_;
                std::streampos currentPos_;

            public:
                Tuple(CSVParser &CSVparser, bool isLastTuple)
                : CSVparser_{CSVparser}, lastTuple_(isLastTuple), currentPos_(CVSparser.fileStart_) {
                    if (isLastTuple) return;
                    readTuple();
                }

                void readTuple() {
                    if (CSVparcer_.input_.eof() ) {
                        CSVparser_.input_.seekg(currentPos_);

                        std::string currentLine;
                        std::getline(CSVparser_.input_, currentLine, "\n");

                        currentPos_ = CSVparser_.input.tellg();
                        std::istringstream lineParser {currentLine};
                        
                        if (!lineParser.eof()) {
                            Args data;
                            lineParser >> data;
                            std::make_tuple(data);
                        }
                    }
                }

                /* void printTuple(std::ostream &ostream, cosnt Tuple &tuple) {
                    ostream << 
                } */

                bool operator!=(const Tuple &other) const {
                    return lastTuple_  != other.lastTuple_;
                }

                Tuple& operator++() {
                    readTuple();
                    return *this;
                }

                std::tuple<Args...> operator*() const {
                    return Tuple;
                }

                ~Tuple = default;
        };

        Tuple begin() {
            input_.seekg(fileStart_);
            return Tuple{*this, false};
        }

        Tuple end() {
            return Tuple{*this, true};
        }
};

template<typename ...Args> 
std::ostream& operator<<(std::ostream &ostream, const std::tuple<Args...> &tuple) {
    size_t sizeTuple = std::tuple_size<decltype(tuple)>::value;
    for (size_t i = 0; i < sizeTuple; i++) {
        ostream << std::get<i>(tuple);
        if (i != sizeTuple - 1) {
            ostream << ",";
        }
    }
}