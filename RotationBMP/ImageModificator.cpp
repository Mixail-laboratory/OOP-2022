#include "ImageModificator.hpp"
namespace {

    void swapPixels(bmp::Bitmap &image, bmp::Pixel (*coeffRef)(int x, int y, const bmp::Bitmap &image),
                    const bmp::Bitmap &origin) {
        for (int y = 0; y < image.Height(); y++) {
            for (int x = 0; x < image.Width(); x++) {
                image[x + y * image.Width()] = coeffRef(x, y, origin);
            }
        }
    }

}


void ImageModificator::Rotate(bmp::Bitmap &image, const Degrees degree) {
    if (image.Height() <= 0 || image.Width() <= 0) {
        return;
    }

    bmp::Bitmap newImage;

    switch (degree) {

        case Degrees::HalphPi: {
            newImage = {image.Height(), image.Width()};

            swapPixels(newImage, [](int x, int y, const bmp::Bitmap &origin) {
                return origin[x * origin.Width() + origin.Width() - y - 1];
            }, image);

            break;
        }

        case Degrees::Pi: {
            newImage = {image.Width(), image.Height()};
            swapPixels(newImage, [](int x, int y, const bmp::Bitmap &origin) {
                return origin[(origin.Width() - x - 1) + (origin.Height() - y - 1) * origin.Width()];
            }, image);
            break;
        }

        case Degrees::ThreeQuatersPi: {
            newImage = {image.Height(), image.Width()};
            swapPixels(newImage, [](int x, int y, const bmp::Bitmap &origin) {
                return origin[y + (origin.Height() - x - 1) * origin.Width()];
            }, image);
            break;
        }

    }
    image = newImage;
}


void ImageModificator::Reflection(bmp::Bitmap &image, const MirrorDirection direction) {
    if (image.Width() <= 0 || image.Height() <= 0) {
        return;
    }
    bmp::Bitmap newImage = {image.Width(), image.Height()};
    switch (direction) {
        case MirrorDirection::Horizontal: {
            swapPixels(newImage, [](int x, int y, const bmp::Bitmap &origin) {
                return origin[x + (origin.Height() - y - 1) * origin.Width()];
            }, image);
            break;
        }
        case MirrorDirection::Vertical: {
            swapPixels(newImage, [](int x, int y, const bmp::Bitmap &origin) {
                return origin[(origin.Width() - x - 1) + y * origin.Width()];
            }, image);
            break;
        }
    }
    image = newImage;
}
