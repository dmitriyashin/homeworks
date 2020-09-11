#include "TXLib.h"

void drawSphere(int x_centerofSphere, int y_centerofSphere, int radius, int red, int green, int blue)
{
    int numberofCircles = 100;
    int x_centerofCircles = x_centerofSphere ;
    int y_centerofCircles = y_centerofSphere ;

    for(int i = 0; i < numberofCircles;  i++)
    {
        txSetFillColor(RGB(i * red / numberofCircles, i * green / numberofCircles, i * blue / numberofCircles));
        txSetColor(RGB(i * red / numberofCircles, i * green / numberofCircles, i * blue / numberofCircles));
        txCircle(x_centerofSphere + (x_centerofSphere - x_centerofCircles) * i / numberofCircles, y_centerofSphere + (y_centerofSphere - y_centerofCircles) * i / numberofCircles, radius - i * radius / numberofCircles);
    }
}
int main()
{
    txCreateWindow(800,600);

    int dx = 3 ;
    int dy = 3 ;
    int x_centerofSphere = 200;
    int y_centerofSphere = 200;
    int radius = 100;
    int red = 255;
    int green = 255;
    int blue = 0;

    while(true)
    {
        if ( (x_centerofSphere + radius >= 800) or (x_centerofSphere - radius <= 0) )
        {
            dx = -dx;
        }
        if ( (y_centerofSphere + radius >= 600) or (y_centerofSphere - radius <= 0) )
        {
            dy = -dy;
        }

        x_centerofSphere = x_centerofSphere + dx;
        y_centerofSphere = y_centerofSphere + dy;
        txBegin();
        txSetFillColor (TX_BLACK);
        txClear();
        drawSphere(x_centerofSphere, y_centerofSphere, radius, red, green, blue);
        txEnd();
    }

    return 0;
}
