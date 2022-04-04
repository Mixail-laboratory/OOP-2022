#include "gtest/gtest.h"
#include "../../Image.hpp"
#include <cstring>

bool isEqual(const Image &img1, const Image &img2) {
    return (std::memcmp(img1.data(), img2.data(), img1.channels() * img1.total()) == 0);
}

void fillImage(Image &img) {
    for (int i = 0; i < img.total() * img.channels(); i++) {
        img.data()[i] = i;
    }
}

TEST(ImageCol, ValidArgs) {
    Image img(10, 10, 10);
    fillImage(img);

    for (int col = 0; col < img.cols(); col++) {
        const Image roi = img.col(col);
        ASSERT_TRUE(img.countRef() == 2);
        ASSERT_TRUE(img.data() == roi.data());
        ASSERT_TRUE(img.channels() == roi.channels());
        ASSERT_TRUE(img.rows() == roi.rows());
        ASSERT_TRUE(1 == roi.cols());
        ASSERT_TRUE(isEqual({img, Range(0, img.rows()), Range(col, col + 1)},
                            roi));
    }
}


TEST(ImageColRange, ColRangeOfColRange) {
    Image img(10, 10, 10);
    fillImage(img);
    Image roi(img);
    for (int col = 0; col < img.cols(); ++col) {
        roi = roi.colRange(Range(0, img.cols() - col));
        ASSERT_TRUE(img.countRef() == 2);
        ASSERT_TRUE(img.data() == roi.data());
        ASSERT_TRUE(img.channels() == roi.channels());
        ASSERT_TRUE(img.rows() == roi.rows());
        ASSERT_TRUE(img.cols() - col == roi.cols());
        ASSERT_TRUE(isEqual({img, Range(0, img.rows()), Range(0, img.cols() - col)}, roi));
    }
}
