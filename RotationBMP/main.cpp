#include <iostream>
#include "ImageModificator.hpp"


int main() {
//    bmp::Bitmap image;
//    image.Load("example.bmp");
//    ImageModificator::Reflection(image, MirrorDirection::Horizontal);
//    image.Save("image.bmp");
    bmp::Bitmap image("lena.bmp");
    std::cout << image.Width() << " " << image.Height();
    ImageModificator::Rotate(image, Degrees::HalphPi);

    image.Save("image_90.bmp");

    bmp::Bitmap image2("lena.bmp");
    //image.Rotate(image, Degrees::HalphPi);

    ImageModificator::Rotate(image2, Degrees::Pi);
    image2.Save("lena.bmp");

    bmp::Bitmap image3("lena.bmp");
    ImageModificator::Rotate(image3, Degrees::ThreeQuatersPi);
    image3.Save("image_270.bmp");


    bmp::Bitmap image4("lena.bmp");
    ImageModificator::Reflection(image4, MirrorDirection::Vertical);
    image4.Save("image_v.bmp");


    bmp::Bitmap image5("lena.bmp");
    ImageModificator::Reflection(image5, MirrorDirection::Horizontal);
    image5.Save("image_h.bmp");
    return 0;
}
