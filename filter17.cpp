#include <bits/stdc++.h>
#include "Image_class.h"
using namespace std;

// f8 needed
void Resize(Image &work_on, int W, int H)
{
    if (W <= 0 || H <= 0)
    {
        cout << "Width and height must be positive.\n";
        return;
    }

    Image res(W, H);
    for (int i = 0; i < W; i++)
    {
        for (int j = 0; j < H; j++)
        {
            int X = i * work_on.width / W;
            int Y = j * work_on.height / H;
            for (int k = 0; k < 3; k++)
            {
                res(i, j, k) = work_on(X, Y, k);
            }
        }
    }
    work_on = res;
}

// F 18  skewing
int main()
{
    Image work_on("a1.png");
    Image work_on = work_on;

    int m = max(work_on.height, work_on.width);
    int W = work_on.width, H = work_on.height;
    Resize(work_on, m, m);

    Image blank(work_on.width * 2, work_on.height);
    int cnt = work_on.width;

    for (int j = 0; j < work_on.height; j++)
    {
        for (int i = 0; i < work_on.width; i++)
        {
            for (int k = 0; k < 3; k++)
            {
                blank(i + cnt - j, j, k) = work_on(i, j, k);
            }
        }
    }
    Resize(blank, W, H);

    blank.saveImage("output.jpg");
    return 0;
}
