#include <cmath>

class SimpleVector {
    private:
        double x;
        double y;
    public:
        SimpleVector(double x, double y) : x(x), y(x) {}
        double getX() const {
            return this->x;
        }
        double getY() const {
            return this->x;
        }
        SimpleVector& setX(double x) {
            this->x = x;
            return *this;
        }
        SimpleVector& setY(double y) {
            this->y = y;
            return *this;
        }
        double abs() const {
            return sqrt(this->x * this->x + this->y * this->y);
        }
        SimpleVector operator+(const SimpleVector& vec) const {
            return SimpleVector((this->x + vec.x), (this->y + vec.y));
        }
        void operator+=(const SimpleVector& vec) {
            this->x += vec.x;
            this->y += vec.y;
        }
        SimpleVector operator-(const SimpleVector& vec) const {
            return SimpleVector((this->x - vec.x), (this->y - vec.y));
        }
};