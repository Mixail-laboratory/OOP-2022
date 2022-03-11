#include "Image.hpp"
#include <cstring>

Image::Image() {
    setClear();
}

Image::Image(int rows, int cols, int channels) {
    if (rows <= 0 || cols <= 0 || channels <= 0) {
        setClear();
        return;
    }
    Rows = rows;
    Cols = cols;
    Channels = channels;
    Total = Cols * Rows * Channels;
    Data = nullptr;
    CountRef.reset(new size_t);
}

Image::Image(int rows, int cols, int channels, unsigned char *data) {
    if (rows <= 0 || cols <= 0 || channels <= 0 || data == nullptr) {
        setClear();
        return;
    }
    Rows = rows;
    Cols = cols;
    Channels = channels;
    Total = Cols * Rows * Channels;
    Data = data;
    CountRef.reset(new size_t);
}

Image::Image(const Image &image, const Range &rowRange, const Range &colRange) {
    if (rowRange.empty() || colRange.empty()) {
        setClear();
        return;
    }
    Channels = image.Channels;
    if (image.Cols >= colRange.end() - 1) {
        Cols = colRange.size();
    } else if (image.Cols >= colRange.start()) {
        Cols = image.Cols - colRange.start();
    } else {
        setClear();
        return;
    }

    if (image.Rows >= rowRange.end()) {
        Rows = rowRange.size();

    } else if (image.Rows >= rowRange.start()) {
        Rows = image.Rows - rowRange.start();

    } else {
        setClear();
        return;
    }
    Data = image.Data;
    CountRef = image.CountRef;
    Channels = image.Channels;
    Total = Rows * Cols * Channels;
}

size_t Image::countRef() const {
    return CountRef.use_count();
}

int Image::rows() const {
    return Rows;
}

int Image::cols() const {
    return Cols;
}

int Image::total() const {
    return Total;
}

int Image::channels() const {
    return Channels;
}

const unsigned char *Image::data() const {
    return Data;
}

unsigned char *Image::data() {
    return Data;
}

Image Image::clone() const {
    Image image;
    image.Cols = Cols;
    image.Rows = Rows;
    image.Channels = Channels;
    image.CountRef = CountRef;
    image.Total = Total;
    if (!(this->empty())) {
        image.Data = new unsigned char[Total];
        memcpy(image.Data, Data, Total);
    } else {
        image.Data = nullptr;
    }

    return image;
}

void Image::copyTo(Image &image) const {
    if (this == &image) {
        return;
    }
    image.Cols = Cols;
    image.Rows = Rows;
    image.Channels = Channels;
    image.CountRef = CountRef;
    image.Total = Total;
    delete image.Data;
    image.Data = new unsigned char;
    std::memcpy(image.Data, Data, Total);
}

void Image::create(int rows, int cols, int channels) {
    if (rows <= 0 || cols <= 0 || channels <= 0){
        setClear();
        return;
    }
    Rows = rows;
    Cols = cols;
    Channels = channels;
}

unsigned char &Image::at(int index) {
    unsigned char &pixel = Data[index];
    return pixel;
}

const unsigned char &Image::at(int index) const {
    const unsigned char &pixel = Data[index];
    return pixel;
}

bool Image::empty() const {
    return (Data == nullptr);
}

Image Image::zeros(int rows, int cols, int channels) {
    return values(rows, cols, channels, 0);
}

Image Image::values(int rows, int cols, int channels, unsigned char value) {
    Image image;
    image.Rows = rows;
    image.Cols = cols;
    image.Channels = channels;
    image.Total = rows * cols * channels;
    image.Data = new unsigned char;
    std::memset(image.Data, value, image.Total);
    return image;
}

void Image::release() {
    CountRef.reset();
}

Image Image::col(int x) const {
    return {*this, Range::all(), Range(x, x + 1)};
}

Image Image::colRange(const Range &range) const {
    if (range.empty()) {
        return Image();
    } else {
        return {*this, Range::all(), range};
    }
}

Image Image::row(int y) const {
    return {*this, Range(y, y + 1), Range::all()};
}

Image Image::rowRange(const Range &range) const {
    if (range.empty()) {
        return Image();
    } else {
        return {*this, range, Range::all()};
    }
}

Image Image::operator()(const Range &rowRange, const Range &colRange) {
    return {*this, rowRange, colRange};
}

void Image::setClear() {
    Cols = 0;
    Rows = 0;
    Channels = 0;
    Total = 0;
    Data = nullptr;
    CountRef.reset(new size_t);
}

Image &Image::operator=(const Image &image) = default;

Image::Image(const Image &image) = default;

Image::~Image() = default;




