#include <cmath>

class SimpleVector {
    private:
        double x;
        double y;
    public:
        SimpleVector(double x, double y) : x(x), y(y) {}
        double getX() const {
            return this->x;
        }
        double getY() const {
            return this->y;
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
            return std::hypot(this->x, this->y);
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
        void operator-=(const SimpleVector& vec) {
            this->x -= vec.x;
            this->y -= vec.y;
        }
        SimpleVector operator*(double scalar) const {
            return SimpleVector((this->x * scalar), (this->y * scalar));
        }
        void operator*=(double scalar) {
            this->x *= scalar;
            this->y *= scalar;
        }
};