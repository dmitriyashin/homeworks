#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

struct Sphere
{
    float centerX;
    float centerY;
    float vX;
    float vY;
    float accelerationX;
    float accelerationY;
    int radius;
    int red;
    int green;
    int blue;
    int m;
};

void drawSphere(sf::RenderWindow* window, Sphere sphere)
{
    int numberofCircles = 100;
    float x_centerofCircles = sphere.centerX;
    float y_centerofCircles = sphere.centerY;

    for (int i = 0; i < numberofCircles; i++)
    {
        sf::CircleShape circle(sphere.radius - i * sphere.radius / numberofCircles, 100);
        circle.setFillColor(sf::Color(i * sphere.red / numberofCircles, i * sphere.green / numberofCircles, i * sphere.blue / numberofCircles));
        circle.setPosition(sphere.centerX + (sphere.centerX - x_centerofCircles) * i / numberofCircles  - sphere.radius + sphere.radius*i/ numberofCircles, sphere.centerY + (sphere.centerY - y_centerofCircles) * i / numberofCircles - sphere.radius + sphere.radius * i / numberofCircles);
        window->draw(circle);
    }
}

void moveSphere(Sphere* sphere, int t)
{
    sphere->centerX = sphere->centerX + sphere->vX * t;
    sphere->centerY = sphere->centerY + sphere->vY * t;
}

void colideSphereWall(Sphere* sphere, int windowX, int windowY)
{
    if (sphere->centerX + sphere->radius > windowX)
    {
        sphere->vX = -abs(sphere->vX);
    }

    if (sphere->centerX - sphere->radius < 0)
    {
        sphere->vX = abs(sphere->vX);
    }
    if (sphere->centerY + sphere->radius > windowY)
    {
        sphere->vY = -abs(sphere->vY);
    }
    if (sphere->centerY - sphere->radius < 0)
    {
        sphere->vY = abs(sphere->vY);
    }
}

bool checkCollisionTwoSphers(Sphere sphere1, Sphere sphere2)
{
    return (pow(sphere2.centerX - sphere1.centerX, 2) + pow(sphere2.centerY - sphere1.centerY, 2) < pow(sphere1.radius + sphere2.radius, 2));
}

void collideTwoSphers(Sphere* sphere1, Sphere* sphere2)
{
    float dv1 = sphere1->vX;
    float du1 = sphere1->vY;
    float dv2 = sphere2->vX;
    float du2 = sphere2->vY;
    sphere1->vX = (2 * sphere2->m * dv2 + (sphere1->m - sphere2->m) * dv1) / (sphere1->m + sphere2->m);
    sphere1->vY = (2 * sphere2->m * du2 + (sphere1->m - sphere2->m) * du1) / (sphere1->m + sphere2->m);
    sphere2->vX = (2 * sphere1->m * dv1 + (sphere2->m - sphere1->m) * dv2) / (sphere1->m + sphere2->m);
    sphere2->vY = (2 * sphere1->m * du1 + (sphere2->m - sphere1->m) * du2) / (sphere1->m + sphere2->m);
}

void movetocursor(Sphere* sphere, float x_cursor, float y_cursor, int t)
{
    if ((sphere->centerX == x_cursor) and (sphere->centerY == y_cursor))
    {
        sphere->vX = 0;
        sphere->vY = 0;
    }
    else
    {
        float l = sqrt((y_cursor - sphere->centerY) * (y_cursor - sphere->centerY) + (x_cursor - sphere->centerX) * (x_cursor - sphere->centerX));
        float sin = (y_cursor - sphere->centerY) / l;
        float cos = (x_cursor - sphere->centerX) / l;
        float v = (sqrt(sphere->vX * sphere->vX + sphere->vY * sphere->vY)) / t;
        sphere->vX = cos * v;
        sphere->vY = sin * v;
    }
}

void changeV(Sphere* sphere, int t)
{
    sphere->vX = sphere->vX + sphere->accelerationX * t;
    sphere->vY = sphere->vY + sphere->accelerationY * t;
}

int main()
{
    Sphere sphere1 = { 100, 100, 5, 5,  0, 0, 50, 255, 255, 0, 1 };
    Sphere sphere2 = { 300, 300, 3, 3,  0.001, 0.001, 50, 255, 0, 0, 1 };
    Sphere sphere3 = { 500, 500, 1, 1, 0.001, 0.001, 50, 0, 255, 0, 1 };

    float x_cursor = 0;
    float y_cursor = 0;
    int t = 1;
    int windowX = 800;
    int windowY = 600;
    
    sf::RenderWindow window(sf::VideoMode(windowX, windowY), "Window");

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

        changeV(&sphere2, t);
        changeV(&sphere3, t);

        movetocursor(&sphere1, x_cursor, y_cursor, t);

        colideSphereWall(&sphere1, windowX, windowY);
        colideSphereWall(&sphere2, windowX, windowY);
        colideSphereWall(&sphere3, windowX, windowY);

        if (checkCollisionTwoSphers(sphere2, sphere3))
        {
            collideTwoSphers(&sphere2, &sphere3);
        }

        moveSphere(&sphere1, t);
        moveSphere(&sphere2, t);
        moveSphere(&sphere3, t);

        if (checkCollisionTwoSphers(sphere1, sphere2))
        {
            break;
        }

        if (checkCollisionTwoSphers(sphere1, sphere3))
        {
            break;
        }

        window.clear();
        drawSphere(&window, sphere1);
        drawSphere(&window, sphere2);
        drawSphere(&window, sphere3);
        window.display();
    }

    return 0;
}
