#include <bits/stdc++.h>
#include "Image_class.h"
using namespace std;

// F 18  oil
int main()
{
    Image work_on("a1.png");
    Image work_on = work_on;

    for (int i = 0; i < work_on.height; i++)
    {

        for (int j = 0; j < work_on.width; j++)
        {

            for (int k = 0; k < work_on.channels; k++)
            {
                work_on(j, i, k) = 24 * (work_on(j, i, k) / 25);
            }
        }
    }

    cout << "ana 3amr gamed" << endl;
    work_on.saveImage("output.jpg");
    return 0;
}
