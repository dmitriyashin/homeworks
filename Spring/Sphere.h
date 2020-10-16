struct Sphere
{
public:

    Vector2f position;
    Vector2f velocity;
    Vector2f acceleration;
    int radius;
    int red;
    int green;
    int blue;
    int m;

    Sphere()
    {
        position = { 0, 0 };
        velocity = { 0, 0 };
        acceleration = { 0, 0 };
        radius = 0;
        red = 0;
        green = 0;
        blue = 0;
        m = 0;
    }

    Sphere(Vector2f position, Vector2f velocity, Vector2f acceleration, int radius, int red, int green, int blue, int m)
    {
        this->position = position;
        this->velocity = velocity;
        this->acceleration = acceleration;
        this->radius = radius;
        this->red = red;
        this->green = green;
        this->blue = blue;
        this->m = m;
    }


    void drawSphere(sf::RenderWindow* window)
    {
        int numberofCircles = 100;
        float x_centerofCircles = position.x;
        float y_centerofCircles = position.y;
        sf::CircleShape circle(0, 30);

        for (int i = 0; i < numberofCircles; i++)
        {
            circle.setRadius(radius - i * radius / numberofCircles);
            circle.setFillColor(sf::Color(i * red / numberofCircles, i * green / numberofCircles, i * blue / numberofCircles));
            circle.setPosition(position.x + (position.x - x_centerofCircles) * i / numberofCircles - radius + radius * i / numberofCircles, position.y + (position.y - y_centerofCircles) * i / numberofCircles - radius + radius * i / numberofCircles);
            window->draw(circle);
        }
    }

    void moveSphere(float t)
    {
        position = position + velocity * t;
    }

    void collideSphereWall(int windowX, int windowY, int t)
    {
        if (position.x + radius + velocity.x * t > windowX)
        {
            velocity.x = -abs(velocity.x);
            position.x = position.x + 2 * (windowX - position.x) - 2 * radius;
        }

        if (position.x + velocity.x * t - radius < 0)
        {
            velocity.x = abs(velocity.x);
            position.x = -position.x + 2 * radius;
        }
        if (position.y + radius + velocity.y * t > windowY)
        {
            velocity.y = -abs(velocity.y);
            position.y = position.y + 2 * (windowY - position.y) - 2 * radius;
        }
        if (position.y + velocity.y * t - radius < 0)
        {
            velocity.y = abs(velocity.y);
            position.y = -position.y + 2 * radius;
        }
    }

    bool checkCollisionTwoSphers(Sphere sphere2)
    {
        return (pow(sphere2.position.x - position.x, 2) + pow(sphere2.position.y - position.y, 2) < pow(radius + sphere2.radius, 2));
    }

    void collideTwoSphers(Sphere* sphere2, int t, int windowX, int windowY)
    {
        float dv1 = velocity.x;
        float du1 = velocity.y;
        float dv2 = sphere2->velocity.x;
        float du2 = sphere2->velocity.y;

        float x1 = position.x;
        float y1 = position.y;
        float x2 = sphere2->position.x;
        float y2 = sphere2->position.y;

        float dist = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
        position.x =position.x + (radius + sphere2->radius - dist) * (x1 - x2) / (2 * dist);
        position.y = position.y + (radius + sphere2->radius - dist) * (y1 - y2) / (2 * dist);
        sphere2->position.x = sphere2->position.x + (radius + sphere2->radius - dist) * (x2 - x1) / (2 * dist);
        sphere2->position.y = sphere2->position.y + (radius + sphere2->radius - dist) * (y2 - y1) / (2 * dist);

        if ((x1 + radius + velocity.x * t > windowX) or (x1 + velocity.x * t - radius < 0))
        {
            sphere2->position.x = sphere2->position.x + (radius + sphere2->radius - dist) * (x2 - x1) / dist;
        }

        if ((x2 + sphere2->radius + sphere2->velocity.x * t > windowX) or (x2 + velocity.x * t - radius < 0))
        {
            position.x = position.x + (radius + sphere2->radius - dist) * (x1 - x2) / dist;
            sphere2->position.x = x2;
        }
        if ((y1 + radius + velocity.y * t > windowY) or (y1 + velocity.y * t - radius < 0))
        {
            sphere2->position.y = sphere2->position.y + (radius + sphere2->radius - dist) * (y2 - y1) / dist;
        }

        if ((y2 + sphere2->radius + sphere2->velocity.y * t > windowY) or (y2 + velocity.y * t - radius < 0))
        {
            position.y = position.y + (radius + sphere2->radius - dist) * (y1 - y2) / dist;
            sphere2->position.y = y2;
        }

        velocity.x = (2 * sphere2->m * dv2 + (m - sphere2->m) * dv1) / (m + sphere2->m);
        velocity.y = (2 * sphere2->m * du2 + (m - sphere2->m) * du1) / (m + sphere2->m);
        sphere2->velocity.x = (2 * m * dv1 + (sphere2->m - m) * dv2) / (m + sphere2->m);
        sphere2->velocity.y = (2 * m * du1 + (sphere2->m - m) * du2) / (m + sphere2->m);

        assert(dist);
    }

    void changeVelocity(float t)
    {
        velocity = velocity + acceleration * t;
    }
};
