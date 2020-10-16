struct Vector2f
{
    float x;
    float y;

    Vector2f()
    {
        x = 0;
        y = 0;
    }

    Vector2f(float x, float y)
    {
        this->x = x;
        this->y = y;
    }

    Vector2f operator+ (Vector2f v)
    {
        return Vector2f(x + v.x, y + v.y);
    }

    Vector2f operator- (Vector2f v)
    {
        return Vector2f(x - v.x, y - v.y);
    }

    Vector2f operator* (float n)
    {
        return Vector2f(n * x, n * y);
    }

    Vector2f operator/ (float n)
    {
        return Vector2f(x / n, y / n);
    }

    float scalar(Vector2f v)
    {
        return  x * v.x + y * v.y;
    }

    float length()
    {
        return sqrt(x * x + y * y);
    }

    Vector2f normalize()
    {
        float l = this->length();
        return Vector2f(x / l, y / l);
    }

    float angle(Vector2f u)
    {
        return((atan((u.y - y) / (u.x - x))) * 180 / 3.14);
    }

}; 
