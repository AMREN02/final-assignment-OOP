#include <iostream>
#include "Image_class.h"
using namespace std;
int main()
{
    // for evry 90 degree do it once
    Image image("luffy.jpg");

    Image Roty(image.height, image.width);

    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {
            int RX = image.height - 1 - j;
            int RY = i;

            for (int k = 0; k < 3; ++k)
            {
                Roty(RX, RY, k) = image(i, j, k);
            }
        }
    }
    Roty.saveImage("rrr.jpg");
    cout << "DONE ya me3alem";
}
