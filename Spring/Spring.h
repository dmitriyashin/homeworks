struct Spring
{
    Vector2f position1;
    Vector2f position2;
    float length;
    float rate;
    int red;
    int green;
    int blue;

    Spring()
    {
        position1 = { 0, 0 };
        position2 = { 0, 0 };
        length = 10;
        rate = 10;
        red = 255;
        green = 255;
        blue = 0;
    }

    Spring(Vector2f position1, Vector2f position2,float length, float rate, int red, int green, int blue)
    {
        this->position1 = position1;
        this->position2 = position2;
        this->length = length;
        this->rate = rate;
        this->red = red;
        this->green = green;
        this->blue = blue;
    }

    void drawSpring(sf::RenderWindow* window)
    {
        sf::RectangleShape rectangle;
        rectangle.setSize(sf::Vector2f((position1 - position2).length(), 2));
        rectangle.setFillColor(sf::Color(red, green, blue));
        rectangle.setPosition(position1.x, position1.y);
        float angle = 0;
        if (position1.x < position2.x)
        {
            angle = Vector2f(1, 0).angle(position2 - position1);
        }
        else
        {
            angle = 180 + Vector2f(1, 0).angle(position2 - position1);
        }
        rectangle.rotate(angle);
        window->draw(rectangle);
    }

    void moveSpring(Sphere sphere1, Sphere sphere2)
    {
        position1 = sphere1.position;
        position2 = sphere2.position;
    }
};
