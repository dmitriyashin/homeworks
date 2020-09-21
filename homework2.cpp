#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

struct Sphere
{
    float x_centerofSphere;
    float y_centerofSphere;
    float vx_const;
    float vy_const;
    float vx;
    float vy;
    float ax;
    float ay;
    int radius;
    int red;
    int green;
    int blue;
    int m;
};

void drawSphere(Sphere sphere, sf::RenderWindow* window)
{
    int numberofCircles = 100;
    float x_centerofCircles = sphere.x_centerofSphere;
    float y_centerofCircles = sphere.y_centerofSphere;

    for (int i = 0; i < numberofCircles; i++)
    {
        sf::CircleShape circle(sphere.radius - i * sphere.radius / numberofCircles, 100);
        circle.setFillColor(sf::Color(i * sphere.red / numberofCircles, i * sphere.green / numberofCircles, i * sphere.blue / numberofCircles));
        circle.setPosition(sphere.x_centerofSphere + (sphere.x_centerofSphere - x_centerofCircles) * i / numberofCircles  - sphere.radius + sphere.radius*i/ numberofCircles, sphere.y_centerofSphere + (sphere.y_centerofSphere - y_centerofCircles) * i / numberofCircles - sphere.radius + sphere.radius * i / numberofCircles);
        (*window).draw(circle);
    }
}

void moveSphere(Sphere* sphere, int t)
{
    sphere->x_centerofSphere = sphere->x_centerofSphere + sphere->vx * t;
    sphere->y_centerofSphere = sphere->y_centerofSphere + sphere->vy * t;
}

void colideSphere(Sphere* sphere)
{
    if (sphere->x_centerofSphere + sphere->radius > 800)
    {
        sphere->vx = -abs(sphere->vx);
    }

    if (sphere->x_centerofSphere - sphere->radius < 0)
    {
        sphere->vx = abs(sphere->vx);
    }
    if (sphere->y_centerofSphere + sphere->radius > 600)
    {
        sphere->vy = -abs(sphere->vy);
    }
    if (sphere->y_centerofSphere - sphere->radius < 0)
    {
        sphere->vy = abs(sphere->vy);
    }
}

bool checkCollisionTwoSphers(Sphere* sphere1, Sphere* sphere2)
{
    return (pow(sphere2->x_centerofSphere - sphere1->x_centerofSphere, 2) + pow(sphere2->y_centerofSphere - sphere1->y_centerofSphere, 2) < pow(sphere1->radius + sphere2->radius, 2));
}

void collideTwoSphers(Sphere* sphere1, Sphere* sphere2)
{
    float dv1 = sphere1->vx;
    float du1 = sphere1->vy;
    float dv2 = sphere2->vx;
    float du2 = sphere2->vy;
    sphere1->vx = (2 * sphere2->m * dv2 + (sphere1->m - sphere2->m) * dv1) / (sphere1->m + sphere2->m);
    sphere1->vy = (2 * sphere2->m * du2 + (sphere1->m - sphere2->m) * du1) / (sphere1->m + sphere2->m);
    sphere2->vx = (2 * sphere1->m * dv1 + (sphere2->m - sphere1->m) * dv2) / (sphere1->m + sphere2->m);
    sphere2->vy = (2 * sphere1->m * du1 + (sphere2->m - sphere1->m) * du2) / (sphere1->m + sphere2->m);
}

void movetocursor(Sphere* sphere, float x_cursor, float y_cursor, int t)
{
    if ((sphere->x_centerofSphere == x_cursor) and (sphere->y_centerofSphere == y_cursor))
    {
        sphere->vx = 0;
        sphere->vy = 0;
    }
    else
    {
        float l = sqrt((y_cursor - sphere->y_centerofSphere) * (y_cursor - sphere->y_centerofSphere) + (x_cursor - sphere->x_centerofSphere) * (x_cursor - sphere->x_centerofSphere));
        float sin = (y_cursor - sphere->y_centerofSphere) / l;
        float cos = (x_cursor - sphere->x_centerofSphere) / l;
        float v = (sqrt(sphere->vx_const * sphere->vx_const + sphere->vy_const * sphere->vy_const)) / t;
        sphere->vx = cos * v;
        sphere->vy = sin * v;
    }
}

void accelerationofSphere(Sphere* sphere, int t)
{
    sphere->vx_const = sphere->vx_const + sphere->ax * t;
    sphere->vx_const = sphere->vy_const + sphere->ay * t;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Window");

    Sphere sphere1 = { 100, 100, 5, 5, 5, 5, 0, 0, 50, 255, 255, 0, 1 };
    Sphere sphere2 = { 300, 300, 3, 3, 3, 3, 0.001, 0.001, 50, 255, 0, 0, 1 };
    Sphere sphere3 = { 500, 500, 1, 1, 1, 1, 0.001, 0.001, 50, 0, 255, 0, 1 };

    float x_cursor = 0;
    float y_cursor = 0;
    int t = 1;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else
            {
                if (event.type == sf::Event::MouseMoved)
                {
                    x_cursor = event.mouseMove.x;
                    y_cursor = event.mouseMove.y;
                }
            }
        }

        accelerationofSphere(&sphere2, t);
        accelerationofSphere(&sphere3, t);

        

        movetocursor(&sphere1, x_cursor, y_cursor, t);

        colideSphere(&sphere1);
        colideSphere(&sphere2);
        colideSphere(&sphere3);

        if (checkCollisionTwoSphers(&sphere2, &sphere3))
        {
            collideTwoSphers(&sphere2, &sphere3);
        }

        moveSphere(&sphere1, t);
        moveSphere(&sphere2, t);
        moveSphere(&sphere3, t);

        if (checkCollisionTwoSphers(&sphere1, &sphere2))
        {
            break;
        }

        if (checkCollisionTwoSphers(&sphere1, &sphere3))
        {
            break;
        }

        window.clear();
        drawSphere(sphere1, &window);
        drawSphere(sphere2, &window);
        drawSphere(sphere3, &window);
        window.display();
    }

    return 0;
}
