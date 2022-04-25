#ifndef ROTATIONBMP_IMAGEMODIFICATOR_HPP
#define ROTATIONBMP_IMAGEMODIFICATOR_HPP

#include "BitmapPlusPlus.hpp"

enum class Degrees {
    HalphPi,
    Pi,
    ThreeQuatersPi
};

enum class MirrorDirection {
    Vertical,
    Horizontal
};

class ImageModificator final {
public:
    ImageModificator() = delete;

    static void Rotate(bmp::Bitmap &image, const Degrees degrees);

    static void Reflection(bmp::Bitmap &image, const MirrorDirection direction);

};


#endif
