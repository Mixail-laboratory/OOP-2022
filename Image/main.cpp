#include <vector>
#include "Image.hpp"
void CreateImage(Image &img) {
    for (int i = 0; i < img.total() * img.channels(); ++i) {
        img.data()[i] = i;
    }

}
int main() {
    Image img(5, 5, 5);
    CreateImage(img);

    std::vector<Image> imgs(100);
    for (int i = 0; i < imgs.size(); ++i) {
        imgs[i] = img;
    }
    imgs.clear();

    return 0;
}
