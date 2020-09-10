#include "TXLib.h"
void drawSphere(int X, int Y, int R, int r, int g, int b)
{
    int N = 100;
    int x = X ;
    int y = Y ;

    for(int i = 0; i < N;  i++)
    {
        txSetFillColor(RGB(i * r / N, i * g / N, i * b / N));
        txSetColor(RGB(i * r / N, i * g / N, i * b / N));
        txCircle(X + (X - x) * i / N, Y + (Y - y) * i / N, R - i * R / N);
    }
}
int main()
{

    txCreateWindow(800,600);

    int dx = 3 ;
    int dy = 3 ;
    int X = 200;
    int Y = 200;
    int R = 100;
    int r = 255;
    int g = 255;
    int b = 0;



    while(true)
    {
        if ( (X + R >= 800) or (X - R <= 0) )
        {
            dx = -dx;
        }
        if ( (Y + R >= 600) or (Y - R <= 0) )
        {
            dy = -dy;
        }
        X = X + dx;
        Y = Y + dy;
        txBegin();
        txSetFillColor (TX_BLACK);
        txClear();

        drawSphere(X, Y, R, r, g, b);
        txEnd();
    }

    return 0;
}
