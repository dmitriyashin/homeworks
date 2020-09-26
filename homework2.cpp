#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

struct Vector2f
{
    float x;
    float y;
};

struct Sphere
{
    Vector2f position;
    Vector2f velocity;
    Vector2f acceleration;
    int radius;
    int red;
    int green;
    int blue;
    int m;
};

void drawSphere(sf::RenderWindow* window, Sphere sphere)
{
    int numberofCircles = 100;
    float x_centerofCircles = sphere.position.x;
    float y_centerofCircles = sphere.position.y;
    sf::CircleShape circle(0, 100);

    for (int i = 0; i < numberofCircles; i++)
    {
        circle.setRadius(sphere.radius - i * sphere.radius / numberofCircles);
        circle.setFillColor(sf::Color(i * sphere.red / numberofCircles, i * sphere.green / numberofCircles, i * sphere.blue / numberofCircles));
        circle.setPosition(sphere.position.x + (sphere.position.x - x_centerofCircles) * i / numberofCircles  - sphere.radius + sphere.radius*i/ numberofCircles, sphere.position.y + (sphere.position.y - y_centerofCircles) * i / numberofCircles - sphere.radius + sphere.radius * i / numberofCircles);
        window->draw(circle);
    }
}

void moveSphere(Sphere* sphere, int t)
{
    sphere->position.x = sphere->position.x + sphere->velocity.x * t;
    sphere->position.y = sphere->position.y + sphere->velocity.y * t;
}

void colideSphereWall(Sphere* sphere, int windowX, int windowY)
{
    if (sphere->position.x + sphere->radius > windowX)
    {
        sphere->velocity.x = -abs(sphere->velocity.x);
    }

    if (sphere->position.x - sphere->radius < 0)
    {
        sphere->velocity.x = abs(sphere->velocity.x);
    }
    if (sphere->position.y + sphere->radius > windowY)
    {
        sphere->velocity.y = -abs(sphere->velocity.y);
    }
    if (sphere->position.y - sphere->radius < 0)
    {
        sphere->velocity.y = abs(sphere->velocity.y);
    }
}

bool checkCollisionTwoSphers(Sphere sphere1, Sphere sphere2)
{
    return (pow(sphere2.position.x - sphere1.position.x, 2) + pow(sphere2.position.y - sphere1.position.y, 2) < pow(sphere1.radius + sphere2.radius, 2));
}

void collideTwoSphers(Sphere* sphere1, Sphere* sphere2)
{
    float dv1 = sphere1->velocity.x;
    float du1 = sphere1->velocity.y;
    float dv2 = sphere2->velocity.x;
    float du2 = sphere2->velocity.y;
    sphere1->velocity.x = (2 * sphere2->m * dv2 + (sphere1->m - sphere2->m) * dv1) / (sphere1->m + sphere2->m);
    sphere1->velocity.y = (2 * sphere2->m * du2 + (sphere1->m - sphere2->m) * du1) / (sphere1->m + sphere2->m);
    sphere2->velocity.x = (2 * sphere1->m * dv1 + (sphere2->m - sphere1->m) * dv2) / (sphere1->m + sphere2->m);
    sphere2->velocity.y = (2 * sphere1->m * du1 + (sphere2->m - sphere1->m) * du2) / (sphere1->m + sphere2->m);
}

void moveToCursor(Sphere* sphere, float x_cursor, float y_cursor, int t)
{
    if ((sphere->position.x == x_cursor) and (sphere->position.y == y_cursor))
    {
        sphere->velocity.x = 0;
        sphere->velocity.y = 0;
    }
    else
    {
        float l = sqrt((y_cursor - sphere->position.y) * (y_cursor - sphere->position.y) + (x_cursor - sphere->position.x) * (x_cursor - sphere->position.x));
        float sin = (y_cursor - sphere->position.y) / l;
        float cos = (x_cursor - sphere->position.x) / l;
        float v = (sqrt(sphere->velocity.x * sphere->velocity.x + sphere->velocity.y * sphere->velocity.y)) / t;
        sphere->velocity.x = cos * v;
        sphere->velocity.y = sin * v;
    }
}

void changeVelocity(Sphere* sphere, int t)
{
    sphere->velocity.x = sphere->velocity.x + sphere->acceleration.x * t;
    sphere->velocity.y = sphere->velocity.y + sphere->acceleration.y * t;
}

int main()
{
    Sphere sphere1 = { 100, 100, 5, 5,  0, 0, 50, 255, 255, 0, 1 };
    Sphere sphere2 = { 300, 300, 3, 3,  0.001, 0.001, 50, 255, 0, 0, 1 };
    Sphere sphere3 = { 500, 500, 1, 1, 0.001, 0.001, 50, 0, 255, 0, 1 };

    float x_cursor = 0;
    float y_cursor = 0;
    int t = 1;
    int windowX = 1200;
    int windowY = 1000;
    
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
            else if (event.type == sf::Event::MouseMoved)
                {
                    x_cursor = event.mouseMove.x;
                    y_cursor = event.mouseMove.y;
                }
        }

        changeVelocity(&sphere2, t);
        changeVelocity(&sphere3, t);

        moveToCursor(&sphere1, x_cursor, y_cursor, t);

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
