#include <bits/stdc++.h>
#include "Image_class.h"
using namespace std;

void BW(Image &imgg, int scl = 130)
{
    for (int i = 0; i < imgg.width; i++)
    {
        for (int j = 0; j < imgg.height; j++)
        {
            int mid = (imgg(i, j, 0) + imgg(i, j, 1) + imgg(i, j, 2)) / 3;
            mid = (mid > (scl) ? 255 : 0);

            imgg(i, j, 0) = mid;
            imgg(i, j, 1) = mid;
            imgg(i, j, 2) = mid;
        }
    }
}

int main()
{
    Image imgg("luffy.jpg");

    BW(imgg);

    imgg.saveImage("n.jpg");
    return 0;
}

