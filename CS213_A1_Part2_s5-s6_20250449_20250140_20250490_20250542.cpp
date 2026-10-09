// اقسم بالله أن هذا الكود من عمل الفريق
// عمرو احمد طه شيحه         20250449    filter  (2-6)
// جابر اكرامي جابر الزغبي   20250140   filter (1-5)
// كريم محمد السيد سليمان    20250490   filter (3-7)
// محمد اشرف فتحي       20250542        filter (4-8)

#include <iostream>
#include <limits>
#include "Image_class.h"
using namespace std;

void clearStream()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool CheckExtension(string fname)
{
    int pos = fname.find_last_of('.');

    if (pos == -1)
    {
        return false;
    }

    string ext = fname.substr(pos);

    if (ext == ".jpg" || ext == ".jpeg" || ext == ".png" || ext == ".bmp" || ext == ".gif")
    {
        return true;
    }

    return false;
}
// F1
void Grayscale(Image &work_on)
{
    for (int i = 0; i < work_on.width; i++)
    {
        for (int j = 0; j < work_on.height; j++)
        {
            int mid = (work_on(i, j, 0) + work_on(i, j, 1) + work_on(i, j, 2)) / 3;

            for (int k = 0; k < work_on.channels; k++)
            {
                work_on(i, j, k) = mid;
            }
        }
    }
}
// F2
void BlackAndWhite(Image &work_on, float scl = 130)
{
    for (int i = 0; i < work_on.width; i++)
    {
        for (int j = 0; j < work_on.height; j++)
        {
            int mid = (work_on(i, j, 0) + work_on(i, j, 1) + work_on(i, j, 2)) / 3;
            mid = (mid > (scl) ? 255 : 0);

            work_on(i, j, 0) = mid;
            work_on(i, j, 1) = mid;
            work_on(i, j, 2) = mid;
        }
    }
}
// F3
Image Invert(Image &input)
{
    for (int y = 0; y < input.height; y++)
    {
        for (int x = 0; x < input.width; x++)
        {
            unsigned char R_new = 255 - input(x, y, 0);
            unsigned char G_new = 255 - input(x, y, 1);
            unsigned char B_new = 255 - input(x, y, 2);

            input(x, y, 0) = R_new;
            input(x, y, 1) = G_new;
            input(x, y, 2) = B_new;
        }
    }

    return input;
}
// F4
void AddFrame(Image &work_on)
{
    char c;
    while (true)
    {
        std::cout << "want a decorations?   (Y/N)";
        std::cin >> c;
        if (c == 'Y' || c == 'y' || c == 'N' || c == 'n')
            break;
        std::cout << "Invalid choice! Try again.\n";
        clearStream();
    }

    int size = 13;
    int w = work_on.width + size * 2;
    int h = work_on.height + size * 2;
    Image frame(w, h);

    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            if (c == 'N' || c == 'n')
            {
                if (i < size || i >= w - size || j < size || j >= h - size)
                {
                    frame(i, j, 0) = 255;
                    frame(i, j, 1) = 215;
                    frame(i, j, 2) = 0;
                }
            }
            else if (c == 'Y' || c == 'y')
            {
                if (i < size || i >= w - size || j < size || j >= h - size)
                {
                    if ((i + j) % 5 == 0 || (i + j) % 5 == 1 || (i + j) % 5 == 4)
                    {
                        frame(i, j, 0) = 0;
                        frame(i, j, 1) = 0;
                        frame(i, j, 2) = 0;
                    }
                    else
                    {
                        frame(i, j, 0) = 255;
                        frame(i, j, 1) = 215;
                        frame(i, j, 2) = 0;
                    }
                }
            }
        }
    }

    for (int i = 0; i < work_on.width; i++)
    {
        for (int j = 0; j < work_on.height; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                frame(i + size, j + size, k) = work_on(i, j, k);
            }
        }
    }

    work_on = frame;
}

// F5
void Flip(Image &work_on)
{
    int karar;
    while (true)
    {
        cout << "1. horizontal\n";
        cout << "2. vertical\n";
        if (cin >> karar && (karar == 1 || karar == 2))
            break;
        cout << "Invalid choice, enter 1 or 2!\n";
        clearStream();
    }

    if (karar == 1)
    {
        for (int j = work_on.width / 2; j < work_on.width; j++)
        {
            for (int i = 0; i < work_on.height; i++)
            {
                for (int k = 0; k < work_on.channels; k++)
                {
                    int temp = work_on(j, i, k);
                    work_on(j, i, k) = work_on((work_on.width - 1) - j, i, k);
                    work_on((work_on.width - 1) - j, i, k) = temp;
                }
            }
        }
    }
    else
    {
        for (int i = work_on.height / 2; i < work_on.height; i++)
        {
            for (int j = 0; j < work_on.width; j++)
            {
                for (int k = 0; k < work_on.channels; k++)
                {
                    int temp = work_on(j, i, k);
                    work_on(j, i, k) = work_on(j, (work_on.height - 1) - i, k);
                    work_on(j, (work_on.height - 1) - i, k) = temp;
                }
            }
        }
    }
}
// F6
Image Rotate(Image &work_on)
{
    Image Roty(work_on.height, work_on.width);

    for (int i = 0; i < work_on.width; ++i)
    {
        for (int j = 0; j < work_on.height; ++j)
        {
            int RX = work_on.height - 1 - j;
            int RY = i;

            for (int k = 0; k < 3; ++k)
            {
                Roty(RX, RY, k) = work_on(i, j, k);
            }
        }
    }
    return Roty;
}
// F7
Image DarkenAndLighten(Image &input, bool darken)
{
    Image output(input.width, input.height);

    for (int y = 0; y < input.height; y++)
    {
        for (int x = 0; x < input.width; x++)
        {
            unsigned char R_new;
            unsigned char G_new;
            unsigned char B_new;

            if (!darken)
            {
                R_new = input(x, y, 0) * 0.5;
                G_new = input(x, y, 1) * 0.5;
                B_new = input(x, y, 2) * 0.5;
            }
            else
            {
                R_new = (input(x, y, 0) * 1.5 > 255) ? 255 : input(x, y, 0) * 1.5;
                G_new = (input(x, y, 1) * 1.5 > 255) ? 255 : input(x, y, 1) * 1.5;
                B_new = (input(x, y, 2) * 1.5 > 255) ? 255 : input(x, y, 2) * 1.5;
            }

            output(x, y, 0) = R_new;
            output(x, y, 1) = G_new;
            output(x, y, 2) = B_new;
        }
    }

    return output;
}
// F8
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
// F9
Image Merge(Image &work_on, Image &img)
{
    int W = max(work_on.width, img.width);
    int H = max(work_on.height, img.height);

    Resize(work_on, W, H);
    Resize(img, W, H);
    Image common(W, H);

    for (int i = 0; i < W; i++)
    {
        for (int j = 0; j < H; j++)
        {
            for (int k = 0; k < 3; k++)
                common(i, j, k) = (work_on(i, j, k) + img(i, j, k)) / 2;
        }
    }
    return common;
}

// F10
Image DetectEdges(Image &work_on)
{

    BlackAndWhite(work_on);

    Image doit = work_on;
    for (int q = 1; q < work_on.width - 1; q++)
    {
        for (int e = 1; e < work_on.height - 1; e++)
        {
            for (int k = 0; k < 3; k++)
            {
                if (work_on(q - 1, e, k) == 0 && work_on(q + 1, e, k) == 0 && work_on(q, e + 1, k) == 0 && work_on(q, e - 1, k) == 0)
                {
                    doit(q, e, k) = 255;
                }
            }
        }
    }
    return doit;
}

// F11
void Crop(Image &work_on)
{
    int width = 600;
    int height = 600;

    if (work_on.width < width)
        width = work_on.width;

    if (work_on.height < height)
        height = work_on.height;

    int x = (work_on.width - width) / 2;
    int y = (work_on.height - height) / 2;

    Image newImage(width, height);

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            for (int k = 0; k < work_on.channels; k++)
            {
                newImage(i, j, k) = work_on(x + i, y + j, k);
            }
        }
    }

    work_on = newImage;
}
// F12
void Blur(Image &work_on, int level)
{
    for (int r = 0; r < level; r++)
    {
        Image blur(work_on.width, work_on.height);
        for (int i = 5; i < work_on.width - 5; i++)
        {
            for (int j = 5; j < work_on.height - 5; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    int n1, n2, n3, n4, n5, avg;
                    n1 = work_on(i, j, k);
                    n2 = work_on(i + 5, j, k);
                    n3 = work_on(i - 5, j, k);
                    n4 = work_on(i, j + 5, k);
                    n5 = work_on(i, j - 5, k);
                    avg = (n1 + n2 + n3 + n4 + n5) / 5;
                    blur.setPixel(i, j, k, avg);
                }
            }
        }
        work_on = blur;
    }
}
// F13
void SunLight(Image &work_on)
{
    int trs;
    int Brightness = 50;
    for (int j = 0; j < work_on.width; j++)
    {
        for (int i = 0; i < work_on.height; i++)
        {
            for (int k = 0; k < work_on.channels; k++)
            {
                trs = work_on(j, i, k) + Brightness;
                trs = (trs < 255) ? trs : 255;
                if (k == 2)
                {
                    work_on(j, i, k) = (trs - 75 < 0) ? 0 : trs - 75;
                }
                else
                {
                    work_on(j, i, k) = trs;
                }
            }
        }
    }
}

// F14
void TV(Image &work_on)
{
    for (int i = 0; i < work_on.width; i++)
    {
        for (int j = 0; j < work_on.height; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                if (j % 5 == 0 || j % 5 == 1)
                    work_on(i, j, k) *= 0.6;
            }
        }
    }
}

// F15
void Purple(Image &work_on)
{
    for (int i = 0; i < work_on.width; i++)
    {
        for (int j = 0; j < work_on.height; j++)
        {
            unsigned char r = work_on(i, j, 0);
            unsigned char g = work_on(i, j, 1);
            unsigned char b = work_on(i, j, 2);

            work_on(i, j, 0) = min(255, (int)(r * 0.7 + 80));
            work_on(i, j, 1) = g * 0.5;
            work_on(i, j, 2) = min(255, (int)(b * 0.7 + 80));
        }
    }
}
// F16
void Infrared(Image &work_on)
{
    for (int i = 0; i < work_on.width; i++)
    {
        for (int j = 0; j < work_on.height; j++)
        {
            int r, g, b, n, avg_bright;
            r = work_on(i, j, 0);
            g = work_on(i, j, 1);
            b = work_on(i, j, 2);

            avg_bright = (r + g + b) / 3;
            n = 255 - avg_bright;

            work_on(i, j, 0) = 255;
            work_on(i, j, 1) = n;
            work_on(i, j, 2) = n;
        }
    }
}

// F17
Image Skewing(Image &work_on)
{
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
    return blank;
}
/////////////////////////////////////////////
// F18  Oil

/////////////////////////////////////////////
int main()
{
    string fname, newname, dec;
    bool flag = true, OnlyFirstTime = false, val = false;
    cout << "Enter the name of the image file & extention: \n";
    // cin >> fname;
    getline(cin, fname);

    while (!CheckExtension(fname))
    {
        cout << "Wrong image extension. Please enter a valid image file (.jpg, .jpeg, .png, .bmp): \n";
        // cin >> fname;
        getline(cin, fname);
    }

    Image backup(fname);
    Image work_on(fname);
    do
    {
        if (OnlyFirstTime && val)
        {
            string crt;
            while (true)
            {
                cout << "would you like to contenue on current image or back to old?  type(crt/old)\n";
                cin >> crt;
                if (crt == "crt" || crt == "old")
                    break;
                cout << "Invalid choice! Type 'crt' or 'old'.\n";
            }
            if (crt == "old")
            {
                work_on = backup;
            }
        }

        cout << "choose a Filter\n\n";
        cout << "0-info" << endl;
        cout << "1-Grayscale" << endl;
        cout << "2-Black and White" << endl;
        cout << "3-Invert " << endl;
        cout << "4-Adding a Frame " << endl;
        cout << "5-Flip " << endl;
        cout << "6-Rotate " << endl;
        cout << "7-Darken and Lighten " << endl;
        cout << "8-Resizing " << endl;
        cout << "9-Merge " << endl;
        cout << "10-Detect Image Edges " << endl;
        cout << "11-Crop Images " << endl;
        cout << "12-Blur Images " << endl;
        cout << "13-SunLight " << endl;
        cout << "14-TV Images " << endl;
        cout << "15-Purpling " << endl;
        cout << "16-Infrared " << endl;
        cout << "17-Skewing " << endl;
        // cout << "18-Oil painting " << endl;

        int choice;
        cin >> choice;

        if (cin.fail() || choice < 0 || choice > 18)
        {
            cout << "invalid number ,try again\n\n";
            clearStream();
            val = false;
            continue;
        }

        if (choice == 0)
        {
            int scl = 0;
            for (int i = 0; i < work_on.width; i++)
            {
                for (int j = 0; j < work_on.height; j++)
                {
                    int mid = (work_on(i, j, 0) + work_on(i, j, 1) + work_on(i, j, 2)) / 3;
                    scl += mid;
                }
            }
            cout << "You have unlocked the SECRET treasure chest\nIt`s your image infos !!!";
            cout << "width : " << work_on.width << endl;
            cout << "hieght : " << work_on.height << endl;
            cout << "brightness : " << scl << endl;
        }
        else if (choice == 1)
        {
            Grayscale(work_on);
        }
        else if (choice == 2)
        {
            BlackAndWhite(work_on);
        }
        else if (choice == 3)
        {
            work_on = Invert(work_on);
        }
        else if (choice == 4)
        {
            AddFrame(work_on);
        }
        else if (choice == 5)
        {
            Flip(work_on);
        }
        else if (choice == 6)
        {
            int num;
            while (true)
            {
                cout << "how many times to rotate? \n";
                if (cin >> num && num > 0)
                    break;
                cout << "Invalid number! Enter a positive number.\n";
                clearStream();
            }
            while (num--)
            {
                work_on = Rotate(work_on);
            }
        }
        else if (choice == 7)
        {
            int type = 0;
            while (true)
            {
                cout << "1. Darken\n";
                cout << "2. Lighten\n";
                if (cin >> type && (type == 1 || type == 2))
                    break;
                cout << "Invalid choice! Enter 1 or 2.\n";
                clearStream();
            }

            work_on = DarkenAndLighten(work_on, type - 1);
        }
        else if (choice == 8)
        {
            int W, H;
            cout << "current size " << work_on.width << " * " << work_on.height << endl;
            while (true)
            {
                cout << "enter new width and hight : \n ";
                if (cin >> W >> H && W > 0 && H > 0)
                    break;
                cout << "Invalid numbers! Enter positive integers.\n";
                clearStream();
            }
            Resize(work_on, W, H);
        }
        else if (choice == 9)
        {
            string num;
            do
            {
                cout << "enter name & ext for the image: \n";
                // cin >> num;
                getline(cin,num);
            } while (!CheckExtension(num));
            Image img(num);
            work_on = Merge(work_on, img);
        }
        else if (choice == 10)
        {
            work_on = DetectEdges(work_on);
        }
        else if (choice == 11)
        {
            Crop(work_on);
        }
        else if (choice == 12)
        {
            Blur(work_on, 1);
        }
        else if (choice == 13)
        {
            SunLight(work_on);
        }
        else if (choice == 14)
        {
            TV(work_on);
        }
        else if (choice == 15)
        {
            Purple(work_on);
        }
        else if (choice == 16)
        {
            Infrared(work_on);
        }
        else if (choice == 17)
        {
            work_on = Skewing(work_on);
        }
        // else if (choice == 18)
        // {
        //     Oil(work_on);
        // }

        val = true;
        cout << "DONE\n";
        cout << "want to save image?   type(y/n)\n";
        cin >> dec;
        if (dec[0] == 'y' || dec[0] == 'Y')
        {
            cout << "enter the file name & type which you want to save the new image in:  default(.jpg)\n";
            cout << "same name will cause an overload\n";
            // cin >> newname;
            getline(cin,newname);

            if (!CheckExtension(newname))
                newname += ".jpg";

            work_on.saveImage(newname);
        }
        
        cout << "contenue ?   type(Y/N)\n";
        cin >> dec;
        if (!dec[0] == 'y' || !dec[0] == 'Y')
            flag = false;

        OnlyFirstTime = true;

    } while (flag);

    cout << "Thanks for using our photoshop app";
    return 0;
}
