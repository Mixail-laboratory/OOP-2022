#include "gtest/gtest.h"
#include "../../Number.hpp"
#include "../../StreamIO.hpp"

TEST(Parser, invalid_input) {
    std::stringstream sstream;
    sstream.str("Some_trash\n");
    sstream.str("more_trash");
    EXPECT_ANY_THROW(StreamIO::getInputData(sstream));
}

TEST(Parser, invalid_format) {
    std::stringstream sstream;
    sstream.str("10 \"5\"");
    sstream.str("10 \"5\"");
    sstream.str("2");
    EXPECT_ANY_THROW(StreamIO::getInputData(sstream));
}

TEST(Parser, invalid_base) {
    std::stringstream sstream;
    sstream.str("40: \"5\"\n10: \"5\"\n2");
    EXPECT_ANY_THROW(StreamIO::getInputData(sstream));
}

TEST(Parser, invalid_digit) {
    std::stringstream sstream;
    sstream.str("40: \"\"\n10: \"5\"\n2");
    EXPECT_ANY_THROW(StreamIO::getInputData(sstream));
}

TEST(Adder, lazy_test) {
    std::stringstream sstream;
    sstream.str("16: \"FF\"\n36: \"HELLO\"\n2");
    InputData inputData = StreamIO::getInputData(sstream);
    sstream.clear();
    StreamIO::writeNumber(sstream, Number::plus(inputData.numberA,
                                                inputData.numberB, inputData.returnBase));
    EXPECT_EQ(sstream.str(), "2: \"1101111100001011011011011\"");
}

TEST(Adder, base_2){
    std::stringstream sstream;
    sstream.str("36: \"WORLD\"\n36: \"HELLO\"\n2");
    InputData inputData = StreamIO::getInputData(sstream);
    sstream.clear();
    std::stringstream stringstream;
    StreamIO::writeNumber(stringstream, Number::plus(inputData.numberA,
                                                     inputData.numberB, inputData.returnBase));
    EXPECT_EQ(stringstream.str(), "2: \"101000000111101011110001101\"");
}


TEST(Adder, base_8){
    std::stringstream sstream;
    sstream.str("36: \"WORLD\"\n36: \"HELLO\"\n8");
    InputData inputData = StreamIO::getInputData(sstream);
    sstream.clear();
    std::stringstream stringstream;
    StreamIO::writeNumber(stringstream, Number::plus(inputData.numberA,
                                                     inputData.numberB, inputData.returnBase));
    EXPECT_EQ(stringstream.str(), "8: \"500753615\"");
}



TEST(Adder, base_10){
    std::stringstream sstream;
    sstream.str("36: \"WORLD\"\n36: \"HELLO\"\n10");
    InputData inputData = StreamIO::getInputData(sstream);
    sstream.clear();
    std::stringstream stringstream;
    StreamIO::writeNumber(stringstream, Number::plus(inputData.numberA,
                                                     inputData.numberB, inputData.returnBase));
    EXPECT_EQ(stringstream.str(), "10: \"84137869\"");
}


TEST(Adder, base_16){
    std::stringstream sstream;
    sstream.str("36: \"WORLD\"\n36: \"HELLO\"\n16");
    InputData inputData = StreamIO::getInputData(sstream);
    sstream.clear();
    std::stringstream stringstream;
    StreamIO::writeNumber(stringstream, Number::plus(inputData.numberA,
                                                     inputData.numberB, inputData.returnBase));
    EXPECT_EQ(stringstream.str(), "16: \"503D78D\"");
}


TEST(Adder, base_36){
    std::stringstream sstream;
    sstream.str("36: \"WORLD\"\n36: \"HELLO\"\n36");
    InputData inputData = StreamIO::getInputData(sstream);
    sstream.clear();
    std::stringstream stringstream;
    StreamIO::writeNumber(stringstream, Number::plus(inputData.numberA,
                                                     inputData.numberB, inputData.returnBase));
    EXPECT_EQ(stringstream.str(), "36: \"1E3D71\"");
}
