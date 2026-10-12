#include <iostream>
#include "Image_Class.h"
using namespace std;

void TV(Image &work_on)
{
    for (int j = 0; j < work_on.height; j++)
    {
        for (int i = 0; i < work_on.width; i++)
        {
            for (int k = 0; k < 3; k++)
            {
                if (j % 5 == 0 || j % 5 == 1)
                    work_on(i, j, k) *= 0.5;
            }
        }
    }
}

int main()
{
    Image work_on("luffy.jpg");

    TV(work_on);

    work_on.saveImage("tv.jpg");
    return 0;
}
