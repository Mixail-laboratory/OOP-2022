#include "Image.hpp"
#include <cstring>

Image::Image() {
    setClear();
    CountRef = new size_t;
    *CountRef = 1;
}

Image::Image(int rows, int cols, int channels) {
    if (rows <= 0 || cols <= 0 || channels <= 0) {
        setClear();
        CountRef = new size_t;
        *CountRef = 1;
        return;
    }
    Rows = rows;
    Cols = cols;
    Channels = channels;
    Total = Cols * Rows * Channels;
    Data = new unsigned char[Total];
    CountRef = new size_t;
    *CountRef = 1;
}

Image::Image(int rows, int cols, int channels, unsigned char *data) {
    if (rows <= 0 || cols <= 0 || channels <= 0 || data == nullptr) {
        setClear();
        CountRef = new size_t;
        *CountRef = 1;
        return;
    }
    Rows = rows;
    Cols = cols;
    Channels = channels;
    Total = Cols * Rows * Channels;
    Data = data;
    CountRef = new size_t;
    *CountRef = 1;
}

Image::Image(const Image &image, const Range &rowRange, const Range &colRange) {
    if (rowRange.empty() || colRange.empty()) {
        setClear();
        CountRef = new size_t;
        *CountRef = 1;
        return;
    }
    Channels = image.Channels;
    if (image.Cols >= colRange.end() - 1) {
        Cols = colRange.size();
    } else if (image.Cols >= colRange.start()) {
        Cols = image.Cols - colRange.start();
    } else {
        setClear();
        CountRef = new size_t;
        *CountRef = 1;
        return;
    }

    if (image.Rows >= rowRange.end()) {
        Rows = rowRange.size();

    } else if (image.Rows >= rowRange.start()) {
        Rows = image.Rows - rowRange.start();

    } else {
        setClear();
        CountRef = new size_t;
        *CountRef = 1;
        return;
    }
    Data = image.Data;
    CountRef = image.CountRef;
    Channels = image.Channels;
    Total = Rows * Cols * Channels;
    (*CountRef)++;
}

size_t Image::countRef() const {
    if (CountRef == nullptr) {
        return 0;
    } else {
        return *CountRef;
    }
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
    image.Total = Total;
    image.Channels = Channels;
    image.CountRef = new size_t;
    *(image.CountRef) = 1;

    if (!(this->empty())) {
        image.Data = new unsigned char[image.Total];
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
    image.release();
    image.Cols = Cols;
    image.Rows = Rows;
    image.Channels = Channels;
    image.CountRef = new size_t;
    *image.CountRef = 1;
    image.Total = Total;
    image.Data = new unsigned char[Total];
    std::memcpy(image.Data, Data, Total);
}

void Image::create(int rows, int cols, int channels) {
    if (rows <= 0 || cols <= 0 || channels <= 0) {
        setClear();
        CountRef = new size_t;
        *CountRef = 1;
        return;
    }
    Rows = rows;
    Cols = cols;
    Channels = channels;
    Total = Rows * Cols * Channels;
    (*CountRef) = 1;
    Data = new unsigned char[Total];
}

unsigned char &Image::at(int index) {
    if (index > Total) {
        throw std::out_of_range("out of range");
    }
    unsigned char &pixel = Data[index];
    return pixel;
}

const unsigned char &Image::at(int index) const {
    if (index > Total) {
        throw std::out_of_range("out of range");
    }
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
    Image image(rows, cols, channels);
    image.Total = rows * cols * channels;
    image.Data = new unsigned char;
    std::memset(image.Data, value, image.Total);
    return image;
}

void Image::release() {
    if (CountRef != nullptr) {
        --(*CountRef);

        if (*CountRef <= 0) {
            delete CountRef;
            CountRef = nullptr;
        }
        setClear();
    }
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

Image Image::operator()(const Range &rowRange, const Range &colRange) const {
    return {*this, rowRange, colRange};
}

void Image::setClear() {
    Cols = 0;
    Rows = 0;
    Channels = 0;
    Total = 0;
    Data = nullptr;
}

Image &Image::operator=(const Image &image) {
    if (this == &image)
        return *this;
    release();


    Channels = image.Channels;
    Cols = image.Cols;
    Rows = image.Rows;
    Total = image.Total;
    Data = image.Data;
    CountRef = image.CountRef;
    (*CountRef)++;
    return *this;
}

Image::Image(const Image &image) {
    Cols = image.Cols;
    Rows = image.Rows;
    Total = image.Total;
    Data = image.Data;
    Channels = image.Channels;
    CountRef = image.CountRef;
    (*CountRef)++;
}

Image::~Image() {
    release();
}




