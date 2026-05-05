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
 * @brief       Calculates length of vector
 * @return      double          length of the vector
 */
double abs() const {
    return std::hypot(this->x, this->y);
}
/**
 * @brief       Addition of two vectors
 * @param[in]   vec             Vector to be added
 * @return      SimpleVector    Vector sum
 */
SimpleVector operator+(const SimpleVector& vec) const {
    return SimpleVector((this->x + vec.x), (this->y + vec.y));
}
/**
 * @brief       In-place addition of another vector
 * @param[in]   vec     Vector to be added
 */
void operator+=(const SimpleVector& vec) {
    this->x += vec.x;
    this->y += vec.y;
}
/**
 * @brief       Subtraction of two vectors
 * @param[in]   vec             Vector to be subtracted
 * @return      SimpleVector    Vector difference
 */
SimpleVector operator-(const SimpleVector& vec) const {
    return SimpleVector((this->x - vec.x), (this->y - vec.y));
}
/**
 * @brief       In-place subtraction of another vector
 * @param[in]   vec     Vector to be subtracted
 */
void operator-=(const SimpleVector& vec) {
    this->x -= vec.x;
    this->y -= vec.y;
}
/**
 * @brief       Scalar multiplication
 * @param[in]   scalar          Factor for multiplication
 * @return      SimpleVector    The scaled vector
 */
SimpleVector operator*(double scalar) const {
    return SimpleVector((this->x * scalar), (this->y * scalar));
}
/**
 * @brief       In-place scalar multiplication
 * @param[in]   scalar  Factor for multiplication
 */
void operator*=(double scalar) {
    this->x *= scalar;
    this->y *= scalar;
}
