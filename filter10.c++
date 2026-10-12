#include <iostream>
#include "Image_Class.h"
using namespace std;
// F10 edges
void DetectEdges(Image &work_on)
{
    // do back & white
    // BlackWhite(work_on);
    Image doit = work_on;

    for (int q = 1; q < work_on.width - 1; q++)
    {
        for (int e = 1; e < work_on.height - 1; e++)
        {
            for (int k = 0; k < 3; k++)
            {
                if (work_on(q - 1, e, k) == 0 && work_on(q + 1, e, k) == 0 &&
                    work_on(q, e + 1, k) == 0 && work_on(q, e - 1, k) == 0)
                {
                    doit(q, e, k) = 255;
                }
            }
        }
    }
    work_on = doit;
}

int main()
{
    Image work_on("luffy.jpg");

    DetectEdges(work_on);

    work_on.saveImage("n.jpg");
    return 0;
}
