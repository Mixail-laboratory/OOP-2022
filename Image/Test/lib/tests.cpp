#include "gtest/gtest.h"
#include "../../Image.hpp"



void fillImage(Image &img) {
    for (int i = 0; i < img.total(); ++i) {
        img.data()[i] = i;
    }

}

TEST(RangeCtor, Default) {
    Range range;

    EXPECT_EQ(range.start(), 0);
    EXPECT_EQ(range.end(), 0);
}

TEST(RangeCtor, InvalidArgs) {
    Range range(-1, 1);

    EXPECT_EQ(range.start(), 0);
    EXPECT_EQ(range.end(), 0);
}

TEST(RangeCtor, ValidArgs) {
    Range range(5, 15);

    EXPECT_EQ(range.start(), 5);
    EXPECT_EQ(range.end(), 15);
}

TEST(RangeSize, DefaultCtor) {
    Range range;

    EXPECT_EQ(range.size(), 0);
}

TEST(RangeSize, CtorInvalidArgs) {
    Range range(-5, 5);

    EXPECT_EQ(range.size(), 0);
}

TEST(RangeSize, CtorValidArgs) {
    Range range(5, 15);

    EXPECT_EQ(range.size(), 10);
}

TEST(RangeEmpty, DefaultCtor) {
    Range range;

    EXPECT_EQ(range.empty(), true);
}

TEST(RangeEmpty, CtorInvalidArgs) {
    Range range(-5, 5);

    EXPECT_EQ(range.empty(), true);
}

TEST(RangeEmpty, CtorValidArgs) {
    Range range(5, 15);

    EXPECT_EQ(range.empty(), false);
}


TEST(RangeAll, StartAndEnd) {
    Range range = Range::all();
    EXPECT_EQ(range.start(), 0);
    EXPECT_EQ(range.end(), std::numeric_limits<int>::max());
}


TEST(ImageCtor, Default) {
    Image img;
    EXPECT_EQ(img.rows(), 0);
    EXPECT_EQ(img.cols(), 0);
    EXPECT_EQ(img.total(), 0);
    EXPECT_EQ(img.countRef(), 1);
    EXPECT_EQ(img.channels(), 0);
    EXPECT_EQ(img.data(), nullptr);
    EXPECT_TRUE(img.empty());
}

TEST(ImageCtor, InvalidRow) {
    Image img(-5, 5, 5);
    EXPECT_EQ(img.rows(), 0);
    EXPECT_EQ(img.cols(), 0);
    EXPECT_EQ(img.total(), 0);
    EXPECT_EQ(img.countRef(), 1);
    EXPECT_EQ(img.channels(), 0);
    EXPECT_EQ(img.data(), nullptr);
    EXPECT_TRUE(img.empty());
}

TEST(ImageCtor, InvalidCol) {
    Image img(5, -5, 5);
    EXPECT_EQ(img.rows(), 0);
    EXPECT_EQ(img.cols(), 0);
    EXPECT_EQ(img.total(), 0);
    EXPECT_EQ(img.countRef(), 1);
    EXPECT_EQ(img.channels(), 0);
    EXPECT_EQ(img.data(), nullptr);
    EXPECT_TRUE(img.empty());
}

TEST(ImageCtor, InvalidChannel) {
    Image img(5, 5, -5);
    EXPECT_EQ(img.rows(), 0);
    EXPECT_EQ(img.cols(), 0);
    EXPECT_EQ(img.total(), 0);
    EXPECT_EQ(img.countRef(), 1);
    EXPECT_EQ(img.channels(), 0);
    EXPECT_EQ(img.data(), nullptr);
    EXPECT_TRUE(img.empty());
}

TEST(ImageCtor, InvalidPointerArr) {
    Image img(5, 5, 5, nullptr);
    EXPECT_EQ(img.rows(), 0);
    EXPECT_EQ(img.cols(), 0);
    EXPECT_EQ(img.total(), 0);
    EXPECT_EQ(img.countRef(), 1);
    EXPECT_EQ(img.channels(), 0);
    EXPECT_EQ(img.data(), nullptr);
    EXPECT_TRUE(img.empty());
}

TEST(ImageCtor, InvalidRowRanges) {
    Image ref_image(5, 5, 5);
    Image img(ref_image, Range(-5, 5), Range(0, 5));
    EXPECT_EQ(img.rows(), 0);
    EXPECT_EQ(img.cols(), 0);
    EXPECT_EQ(img.total(), 0);
    EXPECT_EQ(img.countRef(), 1);
    EXPECT_EQ(img.channels(), 0);
    EXPECT_EQ(img.data(), nullptr);
    EXPECT_TRUE(img.empty());
}

TEST(ImageCtor, InvalidColRanges) {
    Image ref_image(5, 5, 5);
    Image img(ref_image, Range(0, 5), Range(-5, 5));
    EXPECT_EQ(img.rows(), 0);
    EXPECT_EQ(img.cols(), 0);
    EXPECT_EQ(img.total(), 0);
    EXPECT_EQ(img.countRef(), 1);
    EXPECT_EQ(img.channels(), 0);
    EXPECT_EQ(img.data(), nullptr);
    EXPECT_TRUE(img.empty());
}

TEST(ImageCtor, ValidArgs) {
    Image img(5, 5, 5);
    EXPECT_EQ(img.rows(), 5);
    EXPECT_EQ(img.cols(), 5);
    EXPECT_EQ(img.channels(), 5);
    EXPECT_EQ(img.total(), 125);
    EXPECT_EQ(img.countRef(), 1);
    EXPECT_TRUE(img.empty());
}

TEST(ImageCtor, ValidArgsWithPointer) {
    unsigned char *TestData = new unsigned char[100];

    Image img(5, 5, 5, TestData);
    EXPECT_EQ(img.rows(), 5);
    EXPECT_EQ(img.cols(), 5);
    EXPECT_EQ(img.channels(), 5);
    EXPECT_EQ(img.total(), 125);
    EXPECT_EQ(img.countRef(), 1);
    EXPECT_EQ(img.data(), TestData);
    EXPECT_FALSE(img.empty());

    delete[] TestData;
}

TEST(ImageCtor, CopyOfEmpty) {
    const Image img;
    std::vector<Image> imgs;
    for (int i = 0; i < 100; ++i) {
        imgs.push_back(img);
        ASSERT_EQ(img.countRef(), imgs.size() + 1);
    }
    imgs.clear();
    ASSERT_EQ(img.countRef(), 1);
}

TEST(ImageCtor, CopyOfValidImg) {
    unsigned char *TestData = new unsigned char[125];

    Image refimg = Image(5, 5, 5, TestData);

    fillImage(refimg);

    Image img(refimg);
    EXPECT_EQ(img.rows(), 5);
    EXPECT_EQ(img.cols(), 5);
    EXPECT_EQ(img.channels(), 5);
    EXPECT_EQ(img.total(), 125);
    EXPECT_EQ(img.countRef(), 2);
    EXPECT_EQ(img.data(), TestData);
    EXPECT_FALSE(img.empty());


    delete[] TestData;
}

TEST(ImageCtor, CopyWithRanges) {
    unsigned char *TestData = new unsigned char[125];
    Image refimg = Image(5, 5, 5, TestData);

    fillImage(refimg);

    Image img(refimg, Range().all(), Range().all());
    EXPECT_EQ(img.rows(), 5);
    EXPECT_EQ(img.cols(), 5);
    EXPECT_EQ(img.channels(), 5);
    EXPECT_EQ(img.total(), 125);
    EXPECT_EQ(img.countRef(), 2);
    EXPECT_EQ(img.data(), TestData);
    EXPECT_FALSE(img.empty());


    delete[] TestData;
}

TEST(ImageOperatorAssignment, EmptyImg) {
    const Image img;
    std::vector<Image> imgs(100);
    for (int i = 0; i < imgs.size(); ++i) {
        imgs[i] = img;
        ASSERT_EQ(img.countRef(), i + 2);
    }
    imgs.clear();
    ASSERT_EQ(img.countRef(), 1);
}

TEST(ImageOperatorAssignment, ValidImg) {
    Image img(5, 5, 5);
    img.values(5, 5, 5, 5);

    std::vector<Image> imgs(100);
    for (int i = 0; i < imgs.size(); ++i) {
        imgs[i] = img;
        ASSERT_EQ(img.countRef(), i + 2);
      }
    imgs.clear();
    ASSERT_EQ(img.countRef(), 1);
}

TEST(ImageOperatorBrackets, InvalidRowRange) {
    Image img(10, 10, 10);

    Image img2 = img(Range(-10, 10), Range(0, 10));

    EXPECT_EQ(img2.rows(), 0);
    EXPECT_EQ(img2.cols(), 0);
    EXPECT_EQ(img2.total(), 0);
    EXPECT_EQ(img2.countRef(), 1);
    EXPECT_EQ(img2.channels(), 0);
    EXPECT_EQ(img2.data(), nullptr);
    EXPECT_TRUE(img2.empty());

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
    const Image img;
    const Image clone = img.clone();
    EXPECT_EQ(img.countRef(), 2);
    EXPECT_EQ(clone.countRef(), 2);
}

TEST(ImageCopy, ValidImg) {
    const Image img(10, 10, 10);

    Image cloneimg = img.clone();


    EXPECT_TRUE(img.data() == cloneimg.data());
}

TEST(ImageCopy, RefImg) {
    const Image img(10, 10, 10);

    Image cloneimg = Image(img).clone();


    EXPECT_TRUE(img.data() == cloneimg.data());
}

TEST(ImageCopyTo, EmptyImg) {
    const Image img;
    Image clone;
    img.copyTo(clone);
    EXPECT_EQ(img.countRef(), 2);
    EXPECT_EQ(clone.countRef(), 2);
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

TEST(ImageEmpty, EmptyImage) {
    Image img;
    EXPECT_TRUE(img.empty());
}

TEST(ImageEmpty, NotEmptyImage) {
    Image img(5, 5, 5);
    EXPECT_TRUE(img.empty());
}

TEST(ImageRelease, InvalidRow) {
    Image img(-2, 2, 2);
    EXPECT_EQ(img.countRef(), 1);

    img.release();

    EXPECT_EQ(img.countRef(), 1);

    EXPECT_EQ(img.countRef(), 1);
    EXPECT_EQ(img.channels(), 0);
    EXPECT_EQ(img.rows(), 0);
    EXPECT_EQ(img.cols(), 0);
    EXPECT_EQ(img.total(), 0);
}

TEST(ImageRelease, InvalidCol) {
    Image img(2, -2, 2);
    EXPECT_EQ(img.countRef(), 1);

    img.release();

    EXPECT_EQ(img.countRef(), 1);

    EXPECT_EQ(img.countRef(), 1);
    EXPECT_EQ(img.channels(), 0);
    EXPECT_EQ(img.rows(), 0);
    EXPECT_EQ(img.cols(), 0);
    EXPECT_EQ(img.total(), 0);
}


TEST(ImageRelease, InvalidChannel) {
    Image img(2, 2, -2);
    EXPECT_EQ(img.countRef(), 1);

    img.release();

    EXPECT_EQ(img.countRef(), 1);

    EXPECT_EQ(img.countRef(), 1);
    EXPECT_EQ(img.channels(), 0);
    EXPECT_EQ(img.rows(), 0);
    EXPECT_EQ(img.cols(), 0);
    EXPECT_EQ(img.total(), 0);
}

TEST(ImageRelease, InvalidPointerArr) {
    Image img(2, 2, 2, nullptr);
    EXPECT_EQ(img.countRef(), 1);

    img.release();

    EXPECT_EQ(img.countRef(), 1);

    EXPECT_EQ(img.countRef(), 1);
    EXPECT_EQ(img.channels(), 0);
    EXPECT_EQ(img.rows(), 0);
    EXPECT_EQ(img.cols(), 0);
    EXPECT_EQ(img.total(), 0);
}

TEST(ImageRelease, InvalidRowRanges) {
    Image img(10, 10, 10);
    fillImage(img);

    Image partimg = img(Range(-5, 5), Range(0, 5));

    EXPECT_EQ(img.countRef(), 1);
    EXPECT_EQ(partimg.countRef(), 1);

    img.release();

    EXPECT_EQ(img.countRef(), 1);
    EXPECT_EQ(partimg.countRef(), 1);


    EXPECT_EQ(img.countRef(), 1);
    EXPECT_EQ(img.channels(), 0);
    EXPECT_EQ(img.rows(), 0);
    EXPECT_EQ(img.cols(), 0);
    EXPECT_EQ(img.total(), 0);
}

TEST(ImageRelease, InvalidColRanges) {
    Image img(10, 10, 10);
    fillImage(img);

    Image partimg = img(Range(0, 5), Range(-5, 5));

    EXPECT_EQ(img.countRef(), 1);
    EXPECT_EQ(partimg.countRef(), 1);

    img.release();

    EXPECT_EQ(img.countRef(), 1);
    EXPECT_EQ(partimg.countRef(), 1);


    EXPECT_EQ(img.countRef(), 1);
    EXPECT_EQ(img.channels(), 0);
    EXPECT_EQ(img.rows(), 0);
    EXPECT_EQ(img.cols(), 0);
    EXPECT_EQ(img.total(), 0);
}

TEST(ImageRelease, ValidCopy) {
    const Image img(2, 2, 2);
    Image copy = img;
    EXPECT_EQ(copy.countRef(), 2);
    EXPECT_EQ(img.countRef(), 2);

    copy.release();

    EXPECT_EQ(img.countRef(), 1);

    EXPECT_EQ(copy.countRef(), 1);
    EXPECT_EQ(copy.channels(), 0);
    EXPECT_EQ(copy.rows(), 0);
    EXPECT_EQ(copy.cols(), 0);
    EXPECT_EQ(copy.total(), 0);
}

TEST(ImageRelease, ValidArgs) {
    for (int cols = 1; cols < 10; ++cols) {
        for (int rows = 1; rows < 10; ++rows) {
            for (int ch = 1; ch < 10; ++ch) {
                Image img(rows, cols, ch);
                img.release();
                EXPECT_EQ(img.channels(), 0);
                EXPECT_EQ(img.rows(), 0);
                EXPECT_EQ(img.cols(), 0);
                ASSERT_EQ(img.total(), 0);
            }
        }
    }
}

TEST(ImageRelease, ValidArgsWithPointer) {
    for (int cols = 1; cols < 10; ++cols) {
        for (int rows = 1; rows < 10; ++rows) {
            for (int ch = 1; ch < 10; ++ch) {
                unsigned char ptr[1];
                Image img(rows, cols, ch, ptr);
                img.release();
                EXPECT_EQ(img.channels(), 0);
                EXPECT_EQ(img.rows(), 0);
                EXPECT_EQ(img.cols(), 0);
                ASSERT_EQ(img.total(), 0);
            }
        }
    }
}