struct Spring
{
    Sphere* sphere1;
    Sphere* sphere2;
    float length;
    float rate;
    int red;
    int green;
    int blue;

    void draw(sf::RenderWindow* window)
    {
        sf::RectangleShape rectangle;
        rectangle.setSize(sf::Vector2f((sphere1->position - sphere2->position).length(), 2));
        rectangle.setFillColor(sf::Color(red, green, blue));
        rectangle.setPosition(sphere1->position.x, sphere1->position.y);
        float angle = 0;
        if (sphere1->position.x < sphere2->position.x)
        {
            angle = Vector2f(1, 0).angle(sphere2->position - sphere1->position);
        }
        else
        {
            angle = 180 + Vector2f(1, 0).angle(sphere2->position - sphere1->position);
        }
        rectangle.rotate(angle);
        window->draw(rectangle);
    }
};

