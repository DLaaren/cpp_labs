#include <gtest/gtest.h>
#include "BigInt.h"

TEST(Constructors, DefaultConstructor) {
    BigInt a;
    EXPECT_EQ((int)a, 0);
}

TEST(Constructors, IntConstructor) {
    for (int i = 0; i < 10; i++) {
        int num = std::rand() % 1000 - 500;
        BigInt a(num);
        EXPECT_EQ((int)a, num);
    }
}

TEST(Constructors, StringConstructor) {
    for (int i = 0; i < 10; i++) {
        int num = std::rand() % 1000 - 500;
        std::stringstream ss;
        ss << num; 
        std::string str = ss.str();
        BigInt a(str);
        ss << a;
        std::string BigIntStr = ss.str();
        EXPECT_STREQ(BigIntStr, str);
    }
    ASSERT_THROW({BigInt a("-9=5l");}, BigInt::invalid_argument);
}

TEST(ArithmeticOperators, DirectAssignment) {
    for (int i = 0; i < 10; i++) {
        int num1 = std::rand() % 1000 - 500;
        int num2 = std::rand() % 1000 - 500;    
        BigInt a(num1);
        BigInt b(num2);
        a = b;
        std::stringstream ss1;
        ss1 << a;
        std::stringstream ss2;
        ss2 << b;
        std::string str1 = ss1.str();
        std::string str2 = ss2.str();
        EXPECT_STREQ(str1, str2); 
    }
}

TEST(UnaryOperators, UnaryPlus) {
    for (int i = 0; i < 2; i++) {
        int num1 = std::rand() % 1000 - 500;
        BigInt a(num1);
        std::stringstream ss1;
        ss1 << a;
        std::stringstream ss2;
        a = +a;
        ss2 << a;
        std::string str1 = ss1.str();
        std::string str2 = ss2.str();
        EXPECT_STREQ(str1, str2); 
    }
}

TEST(UnaryOperators, UnaryMinus) {
    for (int i = 0; i < 2; i++) {
        int num1 = std::rand() % 1000 - 500;
        BigInt a(num1);
        std::stringstream ss1;
        ss1 << a;
        std::stringstream ss2;
        a = -a;
        ss2 << a;
        std::string str1 = ss1.str();
        std::string str2 = ss2.str();
        EXPECT_STRNE(str1, str2); 
    }
}

TEST(UnaryOperators, Increment) {
    for (int i = 0; i < 2; i++) {
        int num1 = std::rand() % 1000 - 500;
        BigInt a(num1);
        std::stringstream ss1;
        ss1 << a;
        std::stringstream ss2;
        a = ++a;
        ss2 << a;
        std::string str1 = ss1.str();
        std::string str2 = ss2.str();
        EXPECT_STRNE(str1, str2);
        int ch = str2.back() - str1.back();
        EXPECT_EQ(ch, 1);
    }
}

TEST(UnaryOperators, Decrement) {
    for (int i = 0; i < 2; i++) {
        int num1 = std::rand() % 1000 - 500;
        BigInt a(num1);
        std::stringstream ss1;
        ss1 << a;
        std::stringstream ss2;
        a = --a;
        ss2 << a;
        std::string str1 = ss1.str();
        std::string str2 = ss2.str();
        EXPECT_STRNE(str1, str2); 
        int ch = str1.back() - str2.back();
        EXPECT_EQ(ch, 1);
    }
}

TEST(ArithmeticOperators, Addition) {
    //1
    std::stringstream ss;
    BigInt a(19);
    BigInt b(10);
    BigInt result = a + b;
    ss << result;
    std::string result_str = ss.str();
    ss.str(std::string());
    EXPECT_STREQ(result_str, "29");

    //2
    BigInt c("123456789123456789");
    BigInt d("5050505050505050");
    result = c + d;
    ss << result;
    result_str = ss.str();
    ss.str(std::string());
    EXPECT_STREQ(result_str, "128507294173961839");

    //3
    BigInt e("-105");
    BigInt f("0");
    result = e + f;
    ss << result;
    result_str = ss.str();
    ss.str(std::string());
    EXPECT_STREQ(result_str, "-105");
}

TEST(ArithmeticOperators, Substraction) {
    //1
    std::stringstream ss;
    BigInt a(19);
    BigInt b(10);
    BigInt result = a - b;
    ss << result;
    std::string result_str = ss.str();
    ss.str(std::string());
    EXPECT_STREQ(result_str, "9");

    //2
    BigInt c("123456789123456789");
    BigInt d("5050505050505050");
    result = c - d;
    ss << result;
    result_str = ss.str();
    ss.str(std::string());
    EXPECT_STREQ(result_str, "118406284072951739");

    //3
    BigInt e("0");
    BigInt f("105");
    result = e - f;
    ss << result;
    result_str = ss.str();
    ss.str(std::string());
    EXPECT_STREQ(result_str, "-105");
}

TEST(ArithmeticOperators, Multiplication) {
    //1
    std::stringstream ss;
    BigInt a(19);
    BigInt b(10);
    BigInt result = a * b;
    ss << result;
    std::string result_str = ss.str();
    ss.str(std::string());
    EXPECT_STREQ(result_str, "190");

    //2
    BigInt c("123456789123456789");
    BigInt d("5050505050505050");
    result = c * d;
    ss << result;
    result_str = ss.str();
    ss.str(std::string());
    EXPECT_STREQ(result_str, "623519136987155437648086301284450");

    //3
    BigInt e("0");
    BigInt f("105");
    result = e * f;
    ss << result;
    result_str = ss.str();
    ss.str(std::string());
    EXPECT_STREQ(result_str, "0");
}

TEST(ArithmeticOperators, Division) {
    //1
    std::stringstream ss;
    BigInt a(19);
    BigInt b(10);
    BigInt result = a / b;
    ss << result;
    std::string result_str = ss.str();
    ss.str(std::string());
    EXPECT_STREQ(result_str, "1");

    //2
    BigInt c("123456789123456789");
    BigInt d("5050505050505050");
    result = c / d;
    ss << result;
    result_str = ss.str();
    ss.str(std::string());
    EXPECT_STREQ(result_str, "2");

    //3
    BigInt e("0");
    BigInt f("105");
    result = e / f;
    ss << result;
    result_str = ss.str();
    ss.str(std::string());
    EXPECT_STREQ(result_str, "0");
}

TEST(ArithmeticOperators, Modulo) {
    //1
    std::stringstream ss;
    BigInt a(19);
    BigInt b(10);
    BigInt result = a % b;
    ss << result;
    std::string result_str = ss.str();
    ss.str(std::string());
    EXPECT_STREQ(result_str, "9");

    //2
    BigInt c("123456789123456789");
    BigInt d("5050505050505050");
    result = c % d;
    ss << result;
    result_str = ss.str();
    ss.str(std::string());
    EXPECT_STREQ(result_str, "113355779022446689");

    //3
    BigInt e("0");
    BigInt f("105");
    result = e % f;
    ss << result;
    result_str = ss.str();
    ss.str(std::string());
    EXPECT_STREQ(result_str, "0");
}

TEST(BoolOperators, Equality) {
    //1
    BigInt a(19);
    BigInt b(10);
    bool result = (a == b);
    EXPECT_STREQ(result, false);

    //2
    BigInt c("123456789123456789");
    BigInt d("123456789123456789");
    result = (c == d);
    EXPECT_STREQ(result, true);
}

TEST(BoolOperators, NotEquality) {
    //1
    BigInt a(19);
    BigInt b(10);
    bool result = (a != b);
    EXPECT_STREQ(result, true);

    //2
    BigInt c("123456789123456789");
    BigInt d("123456789123456789");
    result = (c != d);
    EXPECT_STREQ(result, false);
}

TEST(BoolOperators, LessThan) {
    //1
    BigInt a(19);
    BigInt b(10);
    bool result = (b < a);
    EXPECT_STREQ(result, true);

    //2
    BigInt c("123456789123456789");
    BigInt d("123456789123456789");
    result = (c < d);
    EXPECT_STREQ(result, false);
}

TEST(BoolOperators, GreaterThan) {
    //1
    BigInt a(19);
    BigInt b(10);
    bool result = (a > b);
    EXPECT_STREQ(result, true);

    //2
    BigInt c("123456789123456789");
    BigInt d("123456789123456789");
    result = (c > d);
    EXPECT_STREQ(result, false);
}

TEST(BoolOperators, EqualityOrLessThan) {
    //1
    BigInt a(19);
    BigInt b(10);
    bool result = (b <= a);
    EXPECT_STREQ(result, true);

    //2
    BigInt c("123456789123456789");
    BigInt d("123456789123456789");
    result = (c <= d);
    EXPECT_STREQ(result, true);
}

TEST(BoolOperators, EqualityOrGreaterThan) {
    //1
    BigInt a(19);
    BigInt b(10);
    bool result = (a >= b);
    EXPECT_STREQ(result, true);

    //2
    BigInt c("123456789123456789");
    BigInt d("123456789123456789");
    result = (c >= d);
    EXPECT_STREQ(result, true);
}

TEST(BitwiseOperators, NOT) {
    //1
    std::stringstream ss;
    BigInt a(123);
    BigInt result = ~a;
    ss << result;
    std::string result_str = ss.str();
    ss.str(std::string());
    EXPECT_STREQ(result_str, "-4");

    //2
    BigInt b(123456789123456789);
    result = ~b;
    ss << result;
    result_str = ss.str();
    ss.str(std::string());
    EXPECT_STREQ(result_str, "1395630319");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}