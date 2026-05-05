#include <cmath>
#include "simple_vector.hpp"

/**
 * Class constructor
 */
SimpleVector::SimpleVector(double x, double y) : x(x), y(y) {}

/**
 * Getter methods
 */
double SimpleVector::getX() const {
    return this->x;
}

double SimpleVector::getY() const {
    return this->y;
}

/**
 * Setter methods
 */
SimpleVector& SimpleVector::setX(double x) {
    this->x = x;
    return *this;
}

SimpleVector& SimpleVector::setY(double y) {
    this->y = y;
    return *this;
}

/**
 * Math. logic
 */
double SimpleVector::abs() const {
    return std::hypot(this->x, this->y);
}

/**
 * Operator
 */
SimpleVector SimpleVector::operator+(const SimpleVector& vec) const {
    return SimpleVector((this->x + vec.x), (this->y + vec.y));
}

void SimpleVector::operator+=(const SimpleVector& vec) {
    this->x += vec.x;
    this->y += vec.y;
}

SimpleVector SimpleVector::operator-(const SimpleVector& vec) const {
    return SimpleVector((this->x - vec.x), (this->y - vec.y));
}

void SimpleVector::operator-=(const SimpleVector& vec) {
    this->x -= vec.x;
    this->y -= vec.y;
}

SimpleVector SimpleVector::operator*(double scalar) const {
    return SimpleVector((this->x * scalar), (this->y * scalar));
}

void SimpleVector::operator*=(double scalar) {
    this->x *= scalar;
    this->y *= scalar;
}
