#include "gtest/gtest.h"
#include "../../Histogram.hpp"
TEST(Constructors, ConstructorStringEmpty) {
    EXPECT_NO_THROW(Histogram());

}

TEST(Construcors, ConstructorVectorEmpty) {
    std::vector<std::string> v{};
    EXPECT_NO_THROW(Histogram varname(v));
}

TEST(Construcors, ConstructorStreamEmpty) {
    const std::string s = "";
    (std::istringstream(s));
    EXPECT_NO_THROW(Histogram(iss));
}

TEST(Constructors, ConstructorRepeatString) {
    std::map<std::string, int> mp1;
    mp1["a"] = 3;
    mp1["b"] = 2;
    mp1["c"] = 3;
    mp1["z"] = 2;



    std::vector<std::string> vector = {"a", "a", "a", "b", "b", "c", "c", "c", "z", "z"};
    Histogram ht1(vector);

    EXPECT_EQ(ht1.getFrequency("a"), mp1["a"]);
    EXPECT_EQ(ht1.getFrequency("b"), mp1["b"]);
    EXPECT_EQ(ht1.getFrequency("c"), mp1["c"]);
    EXPECT_EQ(ht1.getFrequency("z"), mp1["z"]);
}


TEST(Operators, PlusNoRepeat) {
    Histogram histogram;
    histogram.addWord("0");
    histogram.addWord("1");
    histogram.addWord("0");


    Histogram histogram2;
    histogram2.addWord("0");
    histogram2.addWord("1");
    histogram2.addWord("3");

    Histogram newHist = histogram + histogram2;
    EXPECT_EQ(newHist.getFrequency("0"), 3);
    EXPECT_EQ(newHist.getFrequency("1"), 2);
    EXPECT_EQ(newHist.getFrequency("3"), 1);
}




TEST(Operators, MinusRepeat){
    Histogram histogram;
    histogram.addWord("0");
    histogram.addWord("1");
    histogram.addWord("0");


    Histogram histogram2;
    histogram2.addWord("0");
    histogram2.addWord("1");
    histogram2.addWord("3");

    Histogram newHist = histogram - histogram2;
    EXPECT_EQ(newHist.getFrequency("0"), 1);

}

TEST(Operators, Equal){
    Histogram h1({"a", "b", "c"});

    Histogram h2({"a", "b", "c"});
    ASSERT_TRUE(h1 == h2);
}

TEST(Operators, NotEqual){
    Histogram h1({"a", "2", "c"});

    Histogram h2({"a", "b", "c"});
    ASSERT_FALSE(h1 == h2);
}

