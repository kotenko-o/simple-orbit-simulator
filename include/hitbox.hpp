enum ShapeType {
    circle,
    rectangle
};

/**
 * @class   Basic class for all geometrical shapes
 */
class Shape {
    protected:
        ShapeType type;
    public:
        Shape() {};
        virtual ShapeType getType() = 0;
        ~Shape() {};
};

/**
 * @class   Circle shape class
 */
class Circle : public Shape {
    protected:
        ShapeType type = circle;
    public:
        using Shape::Shape;
        virtual ShapeType getType() override {
            return circle;
        }
};