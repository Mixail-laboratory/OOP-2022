#include "gtest/gtest.h"
#include "../../Image.hpp"
#include <cstring>

bool isEqual(const Image &img1, const Range &rangeRow, const Range &rangeCol, const Image &roi) {
    for (int rowIdx = 0; rowIdx < rangeRow.size(); ++rowIdx) {

        const auto srcRow = img1.row(rowIdx + rangeRow.start());
        const auto dstRow = roi.row(rowIdx);

        for (int colIdx = 0; colIdx < rangeCol.size(); ++colIdx) {
            const auto srcCol = srcRow.col(colIdx + rangeCol.start());
            const auto dstCol = dstRow.col(colIdx);

            if (srcCol.at(0) != dstCol.at(0))
                return false;
        }
    }

    return true;
}

void fillImage(Image &img) {
    for (int i = 0; i < img.total() * img.channels(); ++i) {
        img.data()[i] = i;
    }
}

TEST(RangeCtor, InvalidArgs) {
    Range range(-2, -10);

    EXPECT_EQ(range.start(), 0);
    EXPECT_EQ(range.end(), 0);
}

TEST(RangeSize, DefaultCtor) {
    Range range;

    EXPECT_EQ(range.size(), 0);
}

TEST(RangeSize, CtorInvalidArgs) {
    Range range(-10, -3);

    EXPECT_EQ(range.size(), 0);
}

TEST(RangeSize, ValidArgs) {
    Range range(1, 101);
    EXPECT_EQ(range.size(), 100);
}

TEST(RangeEmpty, DefaultCtor) {
    Range range;
    EXPECT_EQ(range.empty(), true);
}

TEST(RangeEmpty, InvalidArgs) {
    Range range(-5, 5);

    EXPECT_EQ(range.empty(), true);
}

TEST(RangeEmpty, CtorValidArgs) {
    Range range(5, 15);

    EXPECT_EQ(range.empty(), false);
}

TEST(ImageCtor, InvalidArgs) {
    Image image(-1, 0, -3);
    EXPECT_EQ(image.rows(), 0);
    EXPECT_EQ(image.cols(), 0);
    EXPECT_EQ(image.total(), 0);
    EXPECT_EQ(image.countRef(), 1);
    EXPECT_EQ(image.channels(), 0);
    EXPECT_EQ(image.data(), nullptr);
    EXPECT_TRUE(image.empty());
}


TEST(ImageCtor, InvalidData) {
    Image image(10, 10, 5, nullptr);
    EXPECT_EQ(image.rows(), 0);
    EXPECT_EQ(image.cols(), 0);
    EXPECT_EQ(image.total(), 0);
    EXPECT_EQ(image.countRef(), 1);
    EXPECT_EQ(image.channels(), 0);
    EXPECT_EQ(image.data(), nullptr);
}

TEST(ImageCtor, InvalidRanges) {
    Image image_1(3, 4, 5);
    Image image_2(image_1, Range(-5, 5), Range(-10, 5));
    EXPECT_EQ(image_2.rows(), 0);
    EXPECT_EQ(image_2.cols(), 0);
    EXPECT_EQ(image_2.total(), 0);
    EXPECT_EQ(image_2.countRef(), 1);
    EXPECT_EQ(image_2.channels(), 0);
    EXPECT_EQ(image_2.data(), nullptr);
}


TEST(ImageCtor, ValidACtor) {
    Image image(1, 2, 5);
    EXPECT_EQ(image.rows(), 1);
    EXPECT_EQ(image.cols(), 2);
    EXPECT_EQ(image.channels(), 5);
    EXPECT_EQ(image.total(), 2);
}

TEST(ImageCtor, ValidDataAndArgs) {
    unsigned char *TestData = new unsigned char[10];

    Image image(1, 2, 5, TestData);
    EXPECT_EQ(image.rows(), 1);
    EXPECT_EQ(image.cols(), 2);
    EXPECT_EQ(image.channels(), 5);

    EXPECT_EQ(image.total(), 2);
    EXPECT_EQ(image.countRef(), 1);
    EXPECT_EQ(image.data(), TestData);
    EXPECT_FALSE(image.empty());
    delete[] TestData;
}

TEST(ImageCtor, RangesCase) {
    std::shared_ptr<unsigned char> TestData(new unsigned char[10]);
    Image image_1 = Image(1, 2, 5, TestData.get());


    Image image(image_1, Range().all(), Range().all());
    EXPECT_EQ(image.rows(), 1);
    EXPECT_EQ(image.cols(), 2);
    EXPECT_EQ(image.channels(), 5);
    EXPECT_EQ(image.total(), 2);
    EXPECT_EQ(image.countRef(), 2);
    EXPECT_EQ(image.data(), TestData.get());
    EXPECT_FALSE(image.empty());

    EXPECT_EQ(std::memcmp(image.data(), image_1.data(), image.channels() * image.total()), 0);


}

TEST(ImageCtor, ValidCopy) {
    std::shared_ptr<unsigned char> TestData(new unsigned char[10]);
    std::memset(TestData.get(), 5, 10);
    Image image_1 = Image(1, 2, 5, TestData.get());
    Image image(image_1);
    EXPECT_EQ(image.rows(), 1);
    EXPECT_EQ(image.cols(), 2);
    EXPECT_EQ(image.channels(), 5);
    EXPECT_EQ(image.total(), 2);
    EXPECT_EQ(image.countRef(), 2);
    EXPECT_EQ(image.data(), TestData.get());
    EXPECT_FALSE(image.empty());

    EXPECT_EQ(std::memcmp(image.data(), image_1.data(), image.channels() * image.total()), 0);
}


TEST(ImageOperatorBrackets, InvalidRowRange) {
    Image image(10, 10, 10);

    Image image_2 = image(Range(-10, 10), Range(0, 10));

    EXPECT_EQ(image_2.rows(), 0);
    EXPECT_EQ(image_2.cols(), 0);
    EXPECT_EQ(image_2.total(), 0);
    EXPECT_EQ(image_2.countRef(), 1);
    EXPECT_EQ(image_2.channels(), 0);
    EXPECT_EQ(image_2.data(), nullptr);
    EXPECT_TRUE(image_2.empty());

}

TEST(ImageOperatorBrackets, InvalidColRange) {
    Image img(10, 10, 10);

    Image img2 = img(Range(0, 10), Range(-10, 10));

    EXPECT_EQ(img2.rows(), 0);
    EXPECT_EQ(img2.cols(), 0);
    EXPECT_EQ(img2.total(), 0);
    EXPECT_EQ(img2.countRef(), 1);
    EXPECT_EQ(img2.channels(), 0);
    EXPECT_EQ(img2.data(), nullptr);
    EXPECT_TRUE(img2.empty());
}


TEST(ImageCopy, EmptyImg) {
    const Image image;
    const Image cloneImage = image.clone();
    EXPECT_EQ(image.countRef(), 1);
    EXPECT_EQ(cloneImage.countRef(), 1);
}

TEST(ImageCopy, ValidImg) {
    const Image image(5, 5, 5);

    Image cloneimage = image.clone();

    EXPECT_EQ(std::memcmp(image.data(), cloneimage.data(), image.total() * image.channels()), 0);
    EXPECT_FALSE(image.data() == cloneimage.data());
}


TEST(ImageCopyTo, EmptyImg) {
    const Image image;
    Image clone;
    image.copyTo(clone);
    EXPECT_EQ(image.countRef(), 1);
    EXPECT_EQ(clone.countRef(), 1);
}

TEST(ImageCopyTo, ValidImgs) {
    std::unique_ptr<unsigned char> Data(new unsigned char[125]);
    Image image(5, 5, 5, Data.get());

    Image clone;
    image.copyTo(clone);
    EXPECT_EQ(image.countRef(), 1);
    EXPECT_EQ(clone.countRef(), 1);

    EXPECT_EQ(std::memcmp(image.data(), clone.data(), image.total() * image.channels()), 0);
}

TEST(ImageCopyTo, This) {
    Image image(10, 10, 10);
    std::memset(image.data(), 5, image.channels() * image.total());

    Image copy = image(Range(5, 10), Range(5, 10));
    copy.copyTo(copy);

    EXPECT_EQ(image.countRef(), 2);
    EXPECT_EQ(image.data(), copy.data());
    EXPECT_EQ(copy.countRef(), 2);
    EXPECT_EQ(std::memcmp(image.data(), copy.data(), image.total() * image.channels()), 0);
}

TEST(ImageCreate, InvalidRow) {
    for (int row = -5; row <= 0; ++row) {
        Image img(10, 10, 10);
        img.create(row, 1, 1);
        EXPECT_EQ(img.channels(), 0);
        EXPECT_EQ(img.rows(), 0);
        EXPECT_EQ(img.cols(), 0);
        ASSERT_EQ(img.total(), 0);
    }
}

TEST(ImageCreate, InvalidCol) {
    for (int col = -5; col <= 0; ++col) {
        Image img(10, 10, 10);
        img.create(1, col, 1);
        EXPECT_EQ(img.channels(), 0);
        EXPECT_EQ(img.rows(), 0);
        EXPECT_EQ(img.cols(), 0);
        ASSERT_EQ(img.total(), 0);
    }
}

TEST(ImageCreate, InvalidChannel) {
    for (int channel = -5; channel <= 0; ++channel) {
        Image img(10, 10, 10);
        img.create(1, 1, channel);
        EXPECT_EQ(img.channels(), 0);
        EXPECT_EQ(img.rows(), 0);
        EXPECT_EQ(img.cols(), 0);
        ASSERT_EQ(img.total(), 0);
    }
}

TEST(ImageCreate, ValidArgs) {
    for (int channel = -5; channel <= 0; ++channel) {
        Image img(10, 10, 10);
        img.create(1, 1, channel);
        EXPECT_EQ(img.channels(), 0);
        EXPECT_EQ(img.rows(), 0);
        EXPECT_EQ(img.cols(), 0);
        ASSERT_EQ(img.total(), 0);
    }
}


TEST(ImageEmpty, FalseEmpty) {
    Image image(1, 2, 3);
    EXPECT_FALSE(image.empty());
}

TEST(ImageRelease, InvalidArgs) {
    Image image(-2, 0, -100);
    image.release();
    EXPECT_EQ(image.countRef(), 1);
    EXPECT_EQ(image.channels(), 0);
    EXPECT_EQ(image.rows(), 0);
    EXPECT_EQ(image.cols(), 0);
    EXPECT_EQ(image.total(), 0);
}

TEST(ImageRelease, InvalidData) {
    Image image(5, 5, 5, nullptr);
    image.release();
    EXPECT_EQ(image.countRef(), 1);
    EXPECT_EQ(image.channels(), 0);
    EXPECT_EQ(image.rows(), 0);
    EXPECT_EQ(image.cols(), 0);
    EXPECT_EQ(image.total(), 0);
}

TEST(ImageRelease, InvalidRanges) {
    Image image(10, 10, 10);
    std::memset(image.data(), 5, image.channels() * image.total());

    Image partimg = image(Range(-5, 3), Range(0, -100));

    EXPECT_EQ(image.countRef(), 1);
    EXPECT_EQ(partimg.countRef(), 1);

    image.release();
    EXPECT_EQ(image.countRef(), 1);
    EXPECT_EQ(partimg.countRef(), 1);
    EXPECT_EQ(image.channels(), 0);
    EXPECT_EQ(image.rows(), 0);
    EXPECT_EQ(image.cols(), 0);
    EXPECT_EQ(image.total(), 0);
}

TEST(ImageRelease, ValidCopy) {
    const Image image(5, 5, 5);
    Image copy = image;
    EXPECT_EQ(copy.countRef(), 2);
    EXPECT_EQ(image.countRef(), 2);

    copy.release();

    EXPECT_EQ(image.countRef(), 1);

    EXPECT_EQ(copy.countRef(), 1);
    EXPECT_EQ(copy.channels(), 0);
    EXPECT_EQ(copy.rows(), 0);
    EXPECT_EQ(copy.cols(), 0);
    EXPECT_EQ(copy.total(), 0);
}

TEST(ImageZeroes, ZeroesCreateImage) {
    const Image image = Image::zeros(5, 5, 5);
    std::unique_ptr<unsigned char> TestData(new unsigned char[125]);
    std::memset(TestData.get(), 0, 125);

    EXPECT_EQ(std::memcmp(image.data(), TestData.get(), 125), 0);
}

TEST(ImageCol, EmptyImg) {
    Image image;
    Image emptyimg;
    Image colImg = image.col(0);

    EXPECT_TRUE(colImg.data() == emptyimg.data());
}

TEST(ImageCol, InvalidArg) {
    Image image(5, 5, 5);
    EXPECT_TRUE(image.col(image.cols()).empty());
}


TEST(ImageColRange, EmptyImg) {
    Image image;
    Image emptyimg;

    EXPECT_EQ(image.data(), emptyimg.data());
}

TEST(ImageColRange, RangeAll) {
    Image image(5, 5, 5);
    Image emptyimg;
    Image imageCol = image.colRange(Range().all());

    EXPECT_EQ(std::memcmp(imageCol.data(), image.data(), imageCol.total() * imageCol.channels()), 0);
}


TEST(ImageRow, EmptyImg) {
    Image image;
    Image emptyimg;

    EXPECT_TRUE(image.row(0).data() == emptyimg.data());
}

TEST(ImageRow, InvalidArg) {
    Image img(10, 10, 10);
    Image emptyimg;

    EXPECT_TRUE(img.row(10).empty());
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
        ASSERT_TRUE(isEqual(img, Range(0, img.rows()), Range(col, col + 1),
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
        ASSERT_TRUE(isEqual(img, Range(0, img.rows()), Range(0, img.cols() - col), roi));
    }
}
