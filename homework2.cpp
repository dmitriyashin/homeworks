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
        txGetColor( );
    }
}

void moveSphere(float* x_centerofSphere, float* y_centerofSphere, float vx, float vy, int t)
{
    *x_centerofSphere = *x_centerofSphere + vx * t;
    *y_centerofSphere = *y_centerofSphere + vy * t;
}

void colideSphere(float x_centerofSphere, float y_centerofSphere, int radius, float* vx, float* vy)
{
    if  (x_centerofSphere + radius > 800)
    {
        *vx = -abs(*vx);
    }

    if(x_centerofSphere - radius < 0)
    {
        *vx = abs(*vx);
    }
    if  (y_centerofSphere + radius > 600)
    {
        *vy = -abs(*vy);
    }
    if (y_centerofSphere - radius < 0)
    {
        *vy = abs(*vy);
    }
}

bool checkCollisionTwoSphers(float x1, float y1, float x2, float y2, int r1, int r2)
{
    return ((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1) < (r1 + r2) * (r1 + r2));
}

void collideTwoSphers( float* vx1, float* vx2, float* vy1, float* vy2, int m1, int m2)
{
    float dv1 = *vx1;
    float du1 = *vy1;
    float dv2 = *vx2;
    float du2 = *vy2;
    *vx1 = (2 * m2 * dv2 + (m1 - m2) * dv1) / (m1 + m2);
    *vy1 = (2 * m2 * du2 + (m1 - m2) * du1) / (m1 + m2);
    *vx2 = (2 * m1 * dv1 + (m2 - m1) * dv2) / (m1 + m2);
    *vy2 = (2 * m1 * du1 + (m2 - m1) * du2) / (m1 + m2);
}

void movetocursor(float x_centerofSphere, float y_centerofSphere,float x_cursor, float y_cursor, float* vx, float* vy, float vx_const, float vy_const, int t)
{
    if  ((x_centerofSphere == x_cursor) and (y_centerofSphere == y_cursor))
    {
        *vx = 0;
        *vy = 0;
    }
    else
    {
        float l = sqrt((y_cursor - y_centerofSphere) * (y_cursor - y_centerofSphere) + (x_cursor - x_centerofSphere) * (x_cursor - x_centerofSphere));
        float sin = (y_cursor - y_centerofSphere) / l;
        float cos = (x_cursor - x_centerofSphere) / l;
        float v = (sqrt(vx_const * vx_const + vy_const * vy_const)) / t;
        *vx = cos * v;
        *vy = sin * v;
    }
}

void accelerationofSphere(float* vx_const, float* vy_const, float ax, float ay, int t)
{
    *vx_const = *vx_const + ax * t;
    *vx_const = *vy_const + ay * t;
}

int main()
{
    txCreateWindow(800,600);

    int vx1_const = 5;
    int vy1_const = 5;
    float vx2_const = 1;
    float vy2_const = 1;
    float vx3_const = 1;
    float vy3_const = 1;
    float ax2 = 0.001;
    float ay2 = 0.001;
    float ax3 = 0.001;
    float ay3 = 0.001;
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
    float vx1 = vx1_const;
    float vy1 = vy1_const;
    float vx2 = vx2_const;
    float vy2 = vy2_const;
    float vx3 = vx3_const;
    float vy3 = vy3_const;
    float x_cursor = 0;
    float y_cursor = 0;
    int t = 1;

    while(true)
    {
        POINT positionofCursor;
        GetCursorPos(&positionofCursor);
        x_cursor = positionofCursor.x - 367;
        y_cursor = positionofCursor.y - 161;

        movetocursor(x_centerofSphere1, y_centerofSphere1, x_cursor, y_cursor, &vx1, &vy1, vx1_const, vy1_const, t);
        movetocursor(x_centerofSphere2, y_centerofSphere2, x_cursor, y_cursor, &vx2, &vy2, vx2_const, vy2_const, t);
        movetocursor(x_centerofSphere3, y_centerofSphere3, x_cursor, y_cursor, &vx3, &vy3, vx3_const, vy3_const, t);

        colideSphere(x_centerofSphere1, y_centerofSphere1, radius1, &vx1, &vy1);
        colideSphere(x_centerofSphere2, y_centerofSphere2, radius2, &vx2, &vy2);
        colideSphere(x_centerofSphere3, y_centerofSphere3, radius3, &vx3, &vy3);

        if (checkCollisionTwoSphers(x_centerofSphere2, y_centerofSphere2, x_centerofSphere3, y_centerofSphere3, radius2, radius3))
        {
            collideTwoSphers( &vx2, &vx3, &vy2, &vy3, m2, m3);
        }

        moveSphere(&x_centerofSphere1, &y_centerofSphere1, vx1, vy1, t);
        moveSphere(&x_centerofSphere2, &y_centerofSphere2, vx2, vy2, t);
        moveSphere(&x_centerofSphere3, &y_centerofSphere3, vx3, vy3, t);

        accelerationofSphere(&vx2_const, &vy2_const, ax2, ay2, t);
        accelerationofSphere(&vx3_const, &vy3_const, ax3, ay3, t);

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
