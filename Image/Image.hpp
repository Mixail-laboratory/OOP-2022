#ifndef IMAGE_IMAGE_HPP
#define IMAGE_IMAGE_HPP

#include "Range.hpp"
#include <cstdlib>

class Image {

public:

    Image();

    Image(int rows, int cols, int channels);

    Image(int rows, int cols, int channels, unsigned char *data);

    Image(const Image &image);

    Image(const Image &image, const Range &rowRange, const Range &colRange);

    virtual ~Image();

    Image &operator=(const Image &image);

    Image operator()(const Range &rowRange, const Range &colRange) const;

    Image clone() const;

    void copyTo(Image &image) const;

    void create(int rows, int cols, int channels);

    bool empty() const;

    void release();

    Image col(int x) const;

    Image colRange(const Range &range) const;

    Image row(int y) const;

    Image rowRange(const Range &range) const;

    const unsigned char *data() const;

    unsigned char *data();

    int rows() const;

    int cols() const;

    int total() const;

    int channels() const;

    unsigned char &at(int index);

    const unsigned char &at(int index) const;

    static Image zeros(int rows, int cols, int channels);

    static Image values(int rows, int cols, int channels, unsigned char value);

    size_t countRef() const;


private:
    int Rows;
    int Cols;
    int Total;
    int Channels;
    unsigned char *Data;
    size_t *CountRef;

    void setClear();
    bool IsOwnData = false;
};


#endif
