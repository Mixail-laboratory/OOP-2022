#ifndef IMAGE_IMAGE_HPP
#define IMAGE_IMAGE_HPP

#include "Range.hpp"
#include <cstdlib>
#include <memory>

class Image {

public:
    Image();

    Image(int rows, int cols, int channels);

    Image(int rows, int cols, int channels, unsigned char *data);

    Image(const Image &image);

    Image(const Image &image, const Range &rowRange, const Range &colRange);

    virtual ~Image();

    Image &operator=(const Image &image);

    Image operator()(const Range &rowRange, const Range &colRange);

    Image clone() const;

    void copyTo(Image &image) const;

    void create(int rows, int cols, int channels);

    [[nodiscard]] bool empty() const;

    void release();

    [[nodiscard]] Image col(int x) const;

    [[nodiscard]] Image colRange(const Range &range) const;

    Image row(int y) const;

    Image rowRange(const Range &range) const;

    [[nodiscard]] const unsigned char *data() const;

    unsigned char *data();

    [[nodiscard]] int rows() const;

    [[nodiscard]] int cols() const;

    [[nodiscard]] int total() const;

    [[nodiscard]] int channels() const;

    unsigned char &at(int index);

    [[nodiscard]] const unsigned char &at(int index) const;

    static Image zeros(int rows, int cols, int channels);

    static Image values(int rows, int cols, int channels, unsigned char value);

    [[nodiscard]] size_t countRef() const;

private:
    int Rows;
    int Cols;
    int Total;
    int Channels;
    unsigned char *Data;
    std::shared_ptr<size_t> CountRef;

    void setClear();
};


#endif //IMAGE_IMAGE_HPP
