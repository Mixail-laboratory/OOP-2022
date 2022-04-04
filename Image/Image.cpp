#include "Image.hpp"
#include <cstring>

Image::Image() {
    setClear();
    CountRef = new size_t;
    *CountRef = 1;
}

Image::Image(int rows, int cols, int channels): Image() {
    if (rows <= 0 || cols <= 0 || channels <= 0) {
        return;
    }
    Rows = rows;
    Cols = cols;
    Channels = channels;
    Total = Cols * Rows;
    Data = new unsigned char[Total * Channels];
    IsOwnData = true;
    CountRef = new size_t;
    *CountRef = 1;
}

Image::Image(int rows, int cols, int channels, unsigned char *data){
    if (rows <= 0 || cols <= 0 || channels <= 0 || data == nullptr) {
        setClear();
        CountRef = new size_t;
        *CountRef = 1;
        return;
    }
    Rows = rows;
    Cols = cols;
    Channels = channels;
    Total = Cols * Rows;
    Data = data;
    CountRef = new size_t;
    *CountRef = 1;
}

Image::Image(const Image &image, const Range &rowRange, const Range &colRange): Image() {
    if (rowRange.empty() || colRange.empty()) { //same thing
        setClear();
        CountRef = new size_t;
        *CountRef = 1;
        return;
    }
    Channels = image.Channels;
    if (image.Cols >= colRange.end()) {
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
    Total = Rows * Cols;
    IsOwnData = false;
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
    //Image image(Rows, Cols, Channels, nullptr);
    Image image;
    copyTo(image);
    /*
    image.Cols = Cols;
    image.Rows = Rows;
    image.Total = Total;
    image.Channels = Channels;
*/
    if (!(empty())) {
        image.Data = new unsigned char[image.Total * image.Channels];
        image.IsOwnData = true;
        std::memcpy(image.Data, Data, Total * Channels);
    } /*else {
        image.Data = nullptr;
    }
*/
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
    *image.CountRef = 1;
    image.Total = Total;
    image.Data = new unsigned char[Total * Channels];
    image.IsOwnData = true;
    std::memcpy(image.Data, Data, Total * Channels);
}

void Image::create(int rows, int cols, int channels) {
    release();
    if (rows <= 0 || cols <= 0 || channels <= 0) {
        setClear();
        *CountRef = 1;
        return;
    }
    Rows = rows;
    Cols = cols;
    Channels = channels;
    Total = Rows * Cols;
    (*CountRef) = 1;
    Data = new unsigned char[Total * Channels];
    IsOwnData = true;
}

unsigned char &Image::at(int index) {
    return Data[index];
}

const unsigned char &Image::at(int index) const {
    return Data[index];
}

bool Image::empty() const {
    return (Data == nullptr);
}

Image Image::zeros(int rows, int cols, int channels) {
    return values(rows, cols, channels, 0);
}

Image Image::values(int rows, int cols, int channels, unsigned char value) {
    Image image(rows, cols, channels);
    image.IsOwnData = true;
    std::memset(image.Data, value, image.Total * image.Channels);
    return image;
}

void Image::release() {
    if (CountRef != nullptr) {
        --(*CountRef);

        if (*CountRef <= 0) {
            if (IsOwnData) {
                delete[] Data;
                Data = nullptr;
            }
            delete CountRef;
            CountRef = nullptr;
        }
        setClear();
        CountRef = new size_t;
        *CountRef = 1;
    }
}

Image Image::col(int x) const {
    if (x >= Cols) {
        return Image();
    }

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
    if (y >= Rows) {
        return Image();
    }

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
    if (this == &image) {
        return *this;
    }
    release();
    if (IsOwnData){
        delete[] Data;
    }
    delete CountRef;

    Channels = image.Channels;
    Cols = image.Cols;
    Rows = image.Rows;
    Total = image.Total;
    Data = image.Data;
    CountRef = image.CountRef;
    IsOwnData = image.IsOwnData;
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
    IsOwnData = image.IsOwnData;
    (*CountRef)++;
}

Image::~Image() {
    release();
    delete CountRef;
}




