#ifndef SIMPLE_VECTOR_HPP
#define SIMPLE_VECTOR_HPP

#include <iostream>

/**
 * @brief Represents a 2D vector and provides basic linear algebra operations.
 */
class SimpleVector {
    private:
        double x;
        double y;
    public:
        /**
         * @brief Class constructor
         * @param[in] x     x-coordinate
         * @param[in] y     y-coordinate
         */
        SimpleVector(double x, double y);
        /**
         * @brief       Getter for x-coordinate
         * @return      double   x-coordinate
         */
        double getX() const;
        /**
         * @brief       Getter for y-coordinate
         * @return      double   y-coordinate
         */
        double getY() const;
        /**
         * @brief       Setter for x-coordinate
         * @param[in]   x       x-coordinate
         * @return      SimpleVector&   Reference on self
         */
        SimpleVector& setX(double x);
        /**
         * @brief       Setter for y-coordinate
         * @param[in]   y       y-coordinate
         * @return      SimpleVector&   Reference on self
         */
        SimpleVector& setY(double y);
        /**
         * @brief       Calculates length of vector
         * @return      double  length of the vector
         */
        double abs() const;
        /**
         * @brief       Addition of two vectors
         * @param[in]   vec             Vector to be added
         * @return      SimpleVector    Vector sum
         */
        SimpleVector operator+(const SimpleVector& vec) const;
        /**
         * @brief       In-place addition of another vector
         * @param[in]   vec     Vector to be added
         */
        void operator+=(const SimpleVector& vec);
        /**
         * @brief       Subtraction of two vectors
         * @param[in]   vec             Vector to be subtracted
         * @return      SimpleVector    Vector difference
         */
        SimpleVector operator-(const SimpleVector& vec) const;
        /**
         * @brief       In-place subtraction of another vector
         * @param[in]   vec     Vector to be subtracted
         */
        void operator-=(const SimpleVector& vec);
        /**
         * @brief       Scalar multiplication
         * @param[in]   scalar          Factor for multiplication
         * @return      SimpleVector    The scaled vector
         */
        SimpleVector operator*(double scalar) const;
        /**
         * @brief       In-place scalar multiplication
         * @param[in]   scalar  Factor for multiplication
         */
        void operator*=(double scalar);
        /**
         * @brief       Calculates the unit-vector
         * @return      SimpleVectro    Unit-Vector
         */
        SimpleVector getUnitVector() const;
        /**
         * @brief   Compare (==) two vectors
         * @return  bool
         */
        bool operator==(const SimpleVector& v) const {
            return (this->getX() == v.getX() && this->getY() == v.getY());
        }
        /**
         * @brief   Compare (!=) two vectors
         * @return  bool
         */
        bool operator!=(const SimpleVector& v) const {
            return (this->getX() != v.getX() || this->getY() != v.getY());
        }
        friend std::ostream& operator<<(std::ostream& os, const SimpleVector& vector) {
            os << "[" << vector.getX() << ", " << vector.getY() << "]";
            return os;
        }
};

#endif