//BigInt.cpp
#ifndef BIG_INT
#define BIG_INT

#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <stdexcept>

class BigInt {
    private:
        //vector stores a number in reverse
        std::vector<int> digits_;

        //base_ of number        
        static const int base_ = 1'000'000'000;

        //the sign of number
        //if the number is negative then isNegative_ = true
        //otherwise isNegative_ = false
        bool isNegative_; 

        //check if string is valid
        void check_string(std::string);

        //remove redundant zeros
        void remove_leading_zeros();

        //convert BigInt to string that represents binary number
        std::string binary(BigInt) const;

        //convert from binary to BigInt
        BigInt decimal(std::string) const;

    public:
        //exceptions
        class invalid_argument : public std::exception {
            public:
                const char * what() {
                    return "invalid_argument\n";
                }
        };

        class divide_by_zero : public std::exception {
            public:
                const char * what() {
                    return "divide_by_zero\n";
                }
        };

        class out_of_bound : public std::exception {
            public:
                const char * what() {
                    return "out_of_bound\n";
                }
        };

        //default constructor
        //set up BigInt value as zero
        BigInt();

        //constructor
        //set up BigInt value as given number
        BigInt(int);

        //constructor
        //set up BigInt value as given number in string format
        //throw exception if string is invalid
        BigInt(std::string);
        
        //copy constructor
        //set up BigInt value as given BigInt value
        BigInt(const BigInt &);

        //send number to stream
        friend std::ostream & operator<<(std::ostream &, const BigInt &);

        //convert BigInt to string
        operator std::string() const;

        //returns the number of digits
        size_t size() const;

        //convert BigInt to int if BigInt is less than signed int
        operator int() const;

        //direct assignment
        //copy the given number
        BigInt & operator=(const BigInt &);

        //unary plus
        //returns the number
        BigInt operator+() const;

        // unary minus
        //changes a sign of BigInt to the opposite
        BigInt operator-() const;

        //prefix increment
        BigInt & operator++();

        //postfix increment
        const BigInt operator++(int);

        //prefix decrement
        BigInt & operator--();

        //postfix decrement
        const BigInt operator--(int);

        //addition
        friend BigInt operator+(const BigInt &, const BigInt &);
        
        //subtraction
        friend BigInt operator-(const BigInt &, const BigInt &);

        //multiplication
        friend BigInt operator*(const BigInt &, const BigInt &); 

        //division
        friend BigInt operator/(const BigInt &, const BigInt &);

        //modulo
        friend BigInt operator%(const BigInt &, const BigInt &);

        //equality comparison operator
        bool operator==(const BigInt &) const;

        //not equality comparison operator
        bool operator!=(const BigInt &) const;

        //less than comparison operator
        bool operator<(const BigInt &) const;

        //greater than comparison operator
        bool operator>(const BigInt &) const;
    
        //equality or less than comparison operator
        bool operator<=(const BigInt &) const;

        //equality or greater than comparison operator
        bool operator>=(const BigInt &) const;

        //biwise NOT
        BigInt operator~() const;

        //bitwise XOR
        friend BigInt operator^(const BigInt &, const BigInt &);
       
        //bitwise AND
        friend BigInt operator&(const BigInt &, const BigInt &);
        
        //bitwise OR
        friend BigInt operator|(const BigInt &, const BigInt &);

        //addition assignment
        BigInt & operator+=(const BigInt &);

        //multiplication assignment
        BigInt & operator*=(const BigInt &);

        //subtraction assignment 
        BigInt & operator-=(const BigInt &);

        //division assignment 
        BigInt & operator/=(const BigInt &);

        //modulo assignment 
        BigInt & operator%=(const BigInt &);

        //bitwise XOR assignment 
        BigInt & operator^=(const BigInt &);

        //bitwise AND assignment 
        BigInt & operator&=(const BigInt &);

        //bitwise OR assignment
        BigInt & operator|=(const BigInt &);
};

        BigInt::BigInt() {
            this->isNegative_ = false;
            this->digits_.push_back(0);
        }

        BigInt::BigInt(int num) {
            if (num == 0) {
                BigInt();
            }
            else {
                if (num > 0) {
                    this->isNegative_ = false;
                }
                if (num < 0) {
                    this->isNegative_ = true;
                    num = -num;
                }
                do {
                    int reminder = num % BigInt::base_; 
                    this->digits_.push_back(reminder);
                    num /= BigInt::base_;
                } while (num != 0);
            }
        }

        void BigInt::check_string(std::string str) {
            std::string tmp;
            if (str[0] == '-') {
                str = str.substr(1);
            }
            for (long long int i = 0; i < str.size(); i++) {
                if (str[i] < '0' || str[i] > '9') {
                    throw BigInt::invalid_argument();
                }
            }
        }

        void BigInt::remove_leading_zeros() {
            while (this->digits_.size() > 1 && this->digits_.back() == 0) {
                this->digits_.pop_back();
            }
            if (this->digits_.size() == 1 && this->digits_[0] == 0) {
                this->isNegative_ = false;
            }
        }

        BigInt::BigInt(std::string str) {
            if (str.length() == 0) {
                BigInt();
            }
            else {
                this->check_string(str);
                if (str[0] == '-') {
                    this->isNegative_ = true;
                    str = str.substr(1);
                }
                else {
                    this->isNegative_ = false;
                }
                for (long long int i = str.size(); i > 0; i -= 9) {
                    if (i < 9)
                        this->digits_.push_back(atoi(str.substr(0, i).c_str()));
                    else
                        this->digits_.push_back(atoi(str.substr(i - 9, 9).c_str()));
                }
            }
            this->remove_leading_zeros();
        }

        BigInt::BigInt(const BigInt & big_int) {
            this->isNegative_ = big_int.isNegative_;
            this->digits_ = big_int.digits_;
        }

        std::ostream & operator<<(std::ostream & ostream, const BigInt & big_int) {
            if (big_int.digits_.empty()) {
                ostream << 0;
            }
            if (big_int.isNegative_ == true) {
                ostream << '-';
            }
            ostream << big_int.digits_.back();
            char fill = ostream.fill('0');
            for (long long int i = big_int.digits_.size() - 2; i >= 0; i--) {
                ostream << std::setw(9) << big_int.digits_[i];
                ostream.fill(fill);
            }
            return ostream;
        }

        BigInt::operator std::string() const {
            std::stringstream s;
            s << *this;
            return s.str();
        }

        size_t BigInt::size() const {
            BigInt tmp = *this;
            if (tmp == (BigInt)0) return 1;
            size_t size = 0;
            while (tmp / (BigInt)10 != (BigInt)0) {
                size++;
                tmp /= 10;
            }
            return size;
        }

        BigInt::operator int() const {
            int result = this->digits_[0];
            if (this->digits_.size() > 2) {
                throw BigInt::out_of_bound();
            }
            else if (this->digits_.size() == 2 && this->digits_[1] > 2) {
                throw BigInt::out_of_bound();
            }
            
            if (this->digits_.size() == 2) {
                result += this->digits_[1] * BigInt::base_;
            }
            if (this->isNegative_ == true) {
                result = -result;
            }
            return result;
        }

        BigInt & BigInt::operator=(const BigInt & big_int) {
            this->isNegative_ = big_int.isNegative_;
            this->digits_ = big_int.digits_;
            return *this;
        }

        BigInt BigInt::operator+() const {
            BigInt tmp(*this);
            return tmp;
        }

        BigInt BigInt::operator-() const {
            BigInt tmp(*this);
            tmp.isNegative_ = !tmp.isNegative_;
            return tmp;
        }

        BigInt & BigInt::operator++() {
            return *this = *this + (BigInt)1;
        }

        const BigInt BigInt::operator++(int) {
            BigInt tmp = *this;
            *this = *this + (BigInt)1;
            return tmp;
        }

        BigInt & BigInt::operator--() {
            return *this = *this - (BigInt)1;
        }

        const BigInt BigInt::operator--(int) {
            BigInt tmp = *this;
            *this = *this - (BigInt)1;
            return tmp;
        }

        BigInt operator+(const BigInt & first, const BigInt & second) {
            //(-a) + (b) --> (b) - (a)
            if (first.isNegative_ == true && second.isNegative_ == false) {
                return second - (-first);
            }
            //a + (-b) --> a - (b)
            else if (second.isNegative_ == true && first.isNegative_ == false) {
                return first - (-second);
            }
            else {
                BigInt result;
                long long int min_size, max_size;
                BigInt mmax;
                if (first > second) {
                    min_size = second.digits_.size(), max_size = first.digits_.size();
                    mmax = first;
                }
                else {
                    max_size = second.digits_.size(), min_size = first.digits_.size();
                    mmax = second;
                }
                result = mmax;
                int reminder = 0;
                for (long long int i = 0; i < std::min(first.digits_.size(), second.digits_.size()); i++) {
                    long long int add_result = first.digits_[i] + second.digits_[i];
                    if ((add_result + reminder) >= BigInt::base_) {
                        result.digits_[i] = (add_result + reminder) % BigInt::base_;
                        reminder = (add_result + reminder) / BigInt::base_;
                    }
                    else {
                        result.digits_[i] = add_result + reminder;
                        reminder = 0;
                    }
                }
                if (first.isNegative_ == true && second.isNegative_ == true) {
                    result.isNegative_ = true;
                }
                else if (first.isNegative_ == false && second.isNegative_ == false) {
                    result.isNegative_ = false;
                }
                return result;
            }
        }

        BigInt operator-(const BigInt & first, const BigInt & second) {
            //(-a) - (b) --> -(a + b)
            if (first.isNegative_ == true && second.isNegative_ == false) {
                return (-((-first) + second));
            }
            //(a) - (-b) --> (a) + (b)
            else if (second.isNegative_ == true && first.isNegative_ == false) {
                return (first + (-second));
            }
            //(a) - (b) && b > a --> -(b - a)
            else if (first < second) {
                return (-(second - first));
            }
            else {
                BigInt result;
                long long int min_size, max_size;
                BigInt mmax, mmin;
                if (first > second) {
                    min_size = second.digits_.size(), max_size = first.digits_.size();
                    mmax = first;
                    mmin = second;
                }
                else {
                    max_size = second.digits_.size(), min_size = first.digits_.size();
                    mmax = second;
                    mmin = first;
                }
                result = mmax;
                int borrowed_num = 0;
                for (long long int i = 0; i < min_size || borrowed_num != 0; i++) {
                    result.digits_[i] -= borrowed_num + (i < min_size ? mmin.digits_[i] : 0);
                    borrowed_num = result.digits_[i] < 0;
                    if (borrowed_num != 0) result.digits_[i] += BigInt::base_;
                }
                result.remove_leading_zeros();
                return result;
            }
        }
        
        BigInt operator*(const BigInt & first, const BigInt & second) {
            BigInt result;
            if (first == result || second == result) {
                return result;
            }
            long long int min_size, max_size;
            BigInt mmax, mmin;
            if (first >= second) {
                min_size = second.digits_.size();
                max_size = first.digits_.size();
                mmax = first;
                mmin = second;
            }
            else if (second > first) {
                max_size = second.digits_.size();
                min_size = first.digits_.size();
                mmax = second;
                mmin = first;
            }
            result.digits_.resize(first.digits_.size() + second.digits_.size());
            for (long long int j = 0; j < min_size; j++) {
                int carry = 0;
                for (long long int i = 0; i < max_size || carry != 0; i++) {
                    long long int res = static_cast<long long int>(mmax.digits_[i]) *
                    static_cast<long long int>(mmin.digits_[j]) + carry;
                    int reminder = res % BigInt::base_;
                    carry = res / BigInt::base_;
                    result.digits_[i + j] += reminder;
                }
            }
            if (first.isNegative_ == second.isNegative_) {
                result.isNegative_ = false;
            }
            else if (first.isNegative_ != second.isNegative_) {
                result.isNegative_ = true;
            }
            result.remove_leading_zeros();
            return result;
        }

        BigInt operator/(const BigInt & first, const BigInt & second) {
           BigInt result;
            if (second == result) {
                throw BigInt::divide_by_zero();
            }    
            if (first < second && first.isNegative_ == second.isNegative_) {
                return result;
            }
            if (second == (BigInt)1) {
                return first;
            }
            if (second == (BigInt)-1) {
                return -first;
            }

            long long int size = first.digits_.size() - 1;
            BigInt chunck = first.digits_[size];
            for ( ; size >= 0; ) {
                while (chunck < second) {
                    auto begin = chunck.digits_.begin();
                    int num = first.digits_[--size];
                    chunck.digits_.insert(begin, num);
                }
                while (chunck >= second) {
                    chunck -= second;
                    result += 1;
                }
                if (size == 0) break;
            }
            if (first.isNegative_ == second.isNegative_) {
                result.isNegative_ = false; 
            }
            else {
                result.isNegative_ = true;
            }
            return result;
        }

        BigInt operator%(const BigInt & first, const BigInt & second) {
            BigInt result = first - (first/second) * second;
            if (result.isNegative_ == true) {
                result += second;
            }
            return result;
        }

        bool BigInt::operator==(const BigInt & big_int) const {
            if (this->isNegative_ != big_int.isNegative_) {
                return false;
            }
            if (this->digits_ == big_int.digits_) return true;
            else return false;
        }

        bool BigInt::operator!=(const BigInt & big_int) const {
            return !(*this == big_int);
        }

        bool BigInt::operator<(const BigInt & big_int) const {
            if (*this == big_int) {
                return false;
            }
            if (this->isNegative_ == true && big_int.isNegative_ == false) {
                return true;
            }
            else if (this->isNegative_ == false && big_int.isNegative_ == true) {
                return false;
            }
            if ((this->digits_.size() < big_int.digits_.size()) && (this->isNegative_ == big_int.isNegative_)) {
                return true;
            }
            else if ((this->digits_.size() > big_int.digits_.size()) && (this->isNegative_ == big_int.isNegative_)) {
                return false;
            }
            else if ((this->digits_.size() == big_int.digits_.size()) && (this->isNegative_ == big_int.isNegative_)){
                for (long long int i = this->digits_.size() - 1; i >= 0; i--) {
                    if (this->digits_[i] > big_int.digits_[i]) {
                        return false;
                    }
                }
            }
            return true;
        }

        bool BigInt::operator>(const BigInt & big_int) const {
            return (big_int < *this);
        }

        bool BigInt::operator<=(const BigInt & big_int) const {
            return (*this < big_int || *this == big_int);
        }

        bool BigInt::operator>=(const BigInt & big_int) const {
            return (big_int <= *this);
        }

        std::string BigInt::binary(BigInt big_int) const {
            std::string bin;
            BigInt tmp(big_int);
            tmp.isNegative_ = false;
            BigInt zero;
            while (tmp > zero) {
                int modulo = tmp % (BigInt)2;
                bin.insert(bin.begin(), modulo + '0');
                tmp /= (BigInt)2;
            }
            bin.insert(bin.begin(), '0'); //sign bit
            if (big_int.isNegative_ == true) {
                for (long long int i = 0; i < bin.size(); i++) {
                    bin[i] = (bin[i] == '0' ? '1' : '0');
                }
                auto bit = bin.end() - 1;
                while (*bit == '1') { //adding 1 bit to the end
                    *bit = '0';
                    if (bit == bin.begin()) {
                        bin.insert(bin.begin(), '1'); //sign bit
                        return bin;
                    }
                    bit--;
                }
                *bit = '1'; 
            }
            return bin;
        }

        BigInt BigInt::decimal(std::string bin) const {
            BigInt result;
            long long int place = 1;
            for (auto bit = bin.end() - 1; bit > bin.begin(); bit--) {
                if (*bit == '1') {
                    result += (BigInt)place;
                }
                place *= 2;
            }
            if (*(bin.begin()) == '0') {
                result.isNegative_ = false;
            }
            else {
                result.isNegative_ = true;
            }
            return result;
        }

        BigInt BigInt::operator~() const {
            std::string bin = binary(*this);
            for (auto bit = bin.end() - 1; bit >= bin.begin(); bit--) {
                *bit = ((*bit) == '0' ? '1' : '0');
            }
            BigInt result = decimal(bin);
            return result;
        }

        BigInt operator^(const BigInt & first, const BigInt & second) {
            std::string bin1 = first.binary(first);
            std::string bin2 = second.binary(second);
            std::string result_str;
            std::string mmax, mmin;
            if (bin1.size() >= bin2.size()) {
                mmax = bin1, mmin = bin2;
            }
            else if (bin1.size() < bin2.size()) {
                mmax = bin2, mmin = bin1;
            }
            if (mmin.size() < mmax.size()) {
                char sign = mmin[0];
                mmin.pop_back();
                while (mmin.size() < mmax.size() - 1) {
                    mmin.insert(mmin.begin(), '0');
                }
                mmin.insert(mmin.begin(), sign);
            }
            for (long long int i = mmin.size() - 1; i > 0 ; i--) {
                if (mmax[i] != mmin[i]) {
                    result_str.insert(result_str.begin(), '1');
                }
                else if (mmax[i] == mmin[i]) {
                    result_str.insert(result_str.begin(), '0');
                }
            }
            //define sign
            if (mmax[0] != mmin[0]) {
                result_str.insert(result_str.begin(), '1');
            }
            else {
                result_str.insert(result_str.begin(), '0');
            }
            BigInt result = result.decimal(result_str);
            return result;
        }
       
        BigInt operator&(const BigInt & first, const BigInt & second) {
            std::string bin1 = first.binary(first);
            std::string bin2 = second.binary(second);
            std::string result_str;
            std::string mmax, mmin;
            if (bin1.size() >= bin2.size()) {
                mmax = bin1, mmin = bin2;
            }
            else if (bin1.size() < bin2.size()) {
                mmax = bin2, mmin = bin1;
            }
            if (mmin.size() < mmax.size()) {
                char sign = mmin[0];
                mmin.pop_back();
                while (mmin.size() < mmax.size() - 1) {
                    mmin.insert(mmin.begin(), '0');
                }
                mmin.insert(mmin.begin(), sign);
            }
            for (long long int i = mmin.size() - 1; i > 0 ; i--) {
                if (mmax[i] == '1' && mmin[i] == '1') {
                    result_str.insert(result_str.begin(), '1');
                }
                else {
                    result_str.insert(result_str.begin(), '0');
                }
            }
            //define sign
            if (mmax[0] == '1' && mmin[0] == '1') {
                result_str.insert(result_str.begin(), '1');
            }
            else {
                result_str.insert(result_str.begin(), '0');
            }
            BigInt result = result.decimal(result_str);
            return result;
        }
        
        BigInt operator|(const BigInt & first, const BigInt & second) {
            std::string bin1 = first.binary(first);
            std::string bin2 = second.binary(second);
            std::string result_str;
            std::string mmax, mmin;
            if (bin1.size() >= bin2.size()) {
                mmax = bin1, mmin = bin2;
            }
            else if (bin1.size() < bin2.size()) {
                mmax = bin2, mmin = bin1;
            }
            if (mmin.size() < mmax.size()) {
                char sign = mmin[0];
                mmin.pop_back();
                while (mmin.size() < mmax.size() - 1) {
                    mmin.insert(mmin.begin(), '0');
                }
                mmin.insert(mmin.begin(), sign);
            }
            std::cout << mmax << std::endl << mmin << std::endl;
            for (long long int i = mmin.size() - 1; i > 0 ; i--) {
                if (mmax[i] == '0' && mmin[i] == '0') {
                    result_str.insert(result_str.begin(), '0');
                }
                else {
                    result_str.insert(result_str.begin(), '1');
                }
            }
            //define sign
            if (mmax[0] == '0' && mmin[0] == '0') {
                result_str.insert(result_str.begin(), '0');
            }
            else {
                result_str.insert(result_str.begin(), '1');
            }
            std::cout << result_str << std::endl;
            BigInt result = result.decimal(result_str);
            return result;
        }

        BigInt & BigInt::operator+=(const BigInt & big_int) {
            return *this = *this + big_int;
        }

        BigInt & BigInt::operator*=(const BigInt & big_int) {
            return *this = *this * big_int;
        }

        BigInt & BigInt::operator-=(const BigInt & big_int) {
            return *this = *this - big_int;
        }

        BigInt & BigInt::operator/=(const BigInt & big_int) {
            return *this = *this / big_int;
        }

        BigInt & BigInt::operator%=(const BigInt & big_int) {
            return *this = *this % big_int;
        }

        BigInt & BigInt::operator^=(const BigInt & big_int) {
            return *this = *this ^ big_int;
        }
        BigInt & BigInt::operator&=(const BigInt & big_int) {
            return *this = *this & big_int;
        }
        BigInt & BigInt::operator|=(const BigInt & big_int) {
            return *this = *this | big_int;
        }
#endif
