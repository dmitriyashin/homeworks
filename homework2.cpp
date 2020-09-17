#include "TXLib.h"
#include "math.h"
#include "windows.h"

void drawSphere(float x_centerofSphere, float y_centerofSphere, int radius, int red, int green, int blue)
{
    int numberofCircles = 100;
    float x_centerofCircles = x_centerofSphere ;
    float y_centerofCircles = y_centerofSphere ;

    for(int i = 0; i < numberofCircles;  i++)
    {
        txSetFillColor(RGB(i * red / numberofCircles, i * green / numberofCircles, i * blue / numberofCircles));
        txSetColor(RGB(i * red / numberofCircles, i * green / numberofCircles, i * blue / numberofCircles));
        txCircle(x_centerofSphere + (x_centerofSphere - x_centerofCircles) * i / numberofCircles, y_centerofSphere + (y_centerofSphere - y_centerofCircles) * i / numberofCircles, radius - i * radius / numberofCircles);
    }
}

void moveSphere(float* x_centerofSphere, float* y_centerofSphere, float dx, float dy)
{
    *x_centerofSphere = *x_centerofSphere + dx;
    *y_centerofSphere = *y_centerofSphere + dy;
}

void colideSphere(float x_centerofSphere, float y_centerofSphere, int radius, float* dx, float* dy)
{
    if  (x_centerofSphere + radius > 800)
    {
        *dx = -abs(*dx);
    }

    if(x_centerofSphere - radius < 0)
    {
        *dx = abs(*dx);
    }
    if  (y_centerofSphere + radius > 600)
    {
        *dy = -abs(*dy);
    }
    if (y_centerofSphere - radius < 0)
    {
        *dy = abs(*dy);
    }
}

bool checkCollisionTwoSphers(float x1, float y1, float x2, float y2, int r1, int r2)
{
    if ((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1) < (r1 + r2)  * (r1 + r2))
    {
        return(true);
    }
    else
    {
        return(false);
    }
}

void collideTwoSphers( float* dx1, float* dx2, float* dy1, float* dy2, int m1, int m2)
{
    float dv1 = *dx1;
    float du1 = *dy1;
    float dv2 = *dx2;
    float du2 = *dy2;
    *dx1 = (2 * m2 * dv2 + (m1 - m2) * dv1) / (m1 + m2);
    *dy1 = (2 * m2 * du2 + (m1 - m2) * du1) / (m1 + m2);
    *dx2 = (2 * m1 * dv1 + (m2 - m1) * dv2) / (m1 + m2);
    *dy2 = (2 * m1 * du1 + (m2 - m1) * du2) / (m1 + m2);
}

void movetopoint(float x_centerofSphere, float y_centerofSphere,float x_point, float y_point, float* dx, float* dy, float dx_const, float dy_const)
{
    if  ((x_centerofSphere == x_point) and (y_centerofSphere == y_point))
    {
        *dx = 0;
        *dy = 0;
    }
    else
    {
        float l = sqrt((y_point - y_centerofSphere) * (y_point - y_centerofSphere) + (x_point - x_centerofSphere) * (x_point - x_centerofSphere));
        float sin = (y_point - y_centerofSphere) / l;
        float cos = (x_point - x_centerofSphere) / l;
        float v = sqrt(dx_const * dx_const + dy_const * dy_const);
        *dx = cos * v;
        *dy = sin * v;
    }
}

void accelerationofSphere(float* dx_const, float* dy_const, float dx_acceleration, float dy_acceleration)
{
    *dx_const = *dx_const + dx_acceleration;
    *dy_const = *dy_const + dy_acceleration;
}

int main()
{
    txCreateWindow(800,600);

    int dx1_const = 5;
    int dy1_const = 5;
    float dx2_const = 1;
    float dy2_const = 1;
    float dx3_const = 1;
    float dy3_const = 1;
    float dx2_acceleration = 0.001;
    float dy2_acceleration = 0.001;
    float dx3_acceleration = 0.001;
    float dy3_acceleration = 0.001;
    float x_centerofSphere1 = 100;
    float y_centerofSphere1 = 100;
    float x_centerofSphere2 = 500;
    float y_centerofSphere2 = 500;
    float x_centerofSphere3 = 300;
    float y_centerofSphere3 = 300;
    int radius1 = 50;
    int radius2 = 50;
    int radius3 = 50;
    int red1 = 255;
    int green1 = 255;
    int blue1 = 0;
    int red2 = 255;
    int green2 = 0;
    int blue2 = 0;
    int red3 = 0;
    int green3 = 255;
    int blue3 = 0;
    int m1 = 1;
    int m2 = 1;
    int m3 = 1;
    float dx1 = dx1_const;
    float dy1 = dy1_const;
    float dx2 = dx2_const;
    float dy2 = dy2_const;
    float dx3 = dx3_const;
    float dy3 = dy3_const;
    float x_point = 0;
    float y_point = 0;

    while(true)
    {
        POINT positionofCursor;
        GetCursorPos(&positionofCursor);
        x_point = positionofCursor.x - 367;
        y_point = positionofCursor.y - 161;

        movetopoint(x_centerofSphere1, y_centerofSphere1, x_point, y_point, &dx1, &dy1, dx1_const, dy1_const);
        movetopoint(x_centerofSphere2, y_centerofSphere2, x_point, y_point, &dx2, &dy2, dx2_const, dy2_const);
        movetopoint(x_centerofSphere3, y_centerofSphere3, x_point, y_point, &dx3, &dy3, dx3_const, dy3_const);

        colideSphere(x_centerofSphere1, y_centerofSphere1, radius1, &dx1, &dy1);
        colideSphere(x_centerofSphere2, y_centerofSphere2, radius2, &dx2, &dy2);
        colideSphere(x_centerofSphere3, y_centerofSphere3, radius3, &dx3, &dy3);

        if (checkCollisionTwoSphers(x_centerofSphere2, y_centerofSphere2, x_centerofSphere3, y_centerofSphere3, radius2, radius3))
        {
            collideTwoSphers( &dx2, &dx3, &dy2, &dy3, m2, m3);
        }

        moveSphere(&x_centerofSphere1, &y_centerofSphere1, dx1, dy1);
        moveSphere(&x_centerofSphere2, &y_centerofSphere2, dx2, dy2);
        moveSphere(&x_centerofSphere3, &y_centerofSphere3, dx3, dy3);

        accelerationofSphere(&dx2_const, &dy2_const, dx2_acceleration, dy2_acceleration);
        accelerationofSphere(&dx3_const, &dy3_const, dx3_acceleration, dy3_acceleration);



        if (checkCollisionTwoSphers(x_centerofSphere1, y_centerofSphere1, x_centerofSphere3, y_centerofSphere3, radius1, radius3))
            {
                break;
            }

            if (checkCollisionTwoSphers(x_centerofSphere1, y_centerofSphere1, x_centerofSphere2, y_centerofSphere2, radius1, radius2))
            {
                break;
            }

        txBegin();
        txSetFillColor (TX_BLACK);
        txClear();
        drawSphere(x_centerofSphere1, y_centerofSphere1, radius1, red1, green1, blue1);
        drawSphere(x_centerofSphere2, y_centerofSphere2, radius2, red2, green2, blue2);
        drawSphere(x_centerofSphere3, y_centerofSphere3, radius3, red3, green3, blue3);
        txEnd();
    }

    return 0;
}
