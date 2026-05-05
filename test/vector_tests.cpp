#include "test_framework.hpp"
#include "simple_vector.hpp"
#include <cmath>

// Framework variables
int passed_asserts = 0;
int failed_asserts = 0;
int passed_tests = 0;
int failed_tests = 0;
int test_number = 1;
int is_test_failed = 0;

void test_constructor_and_getters() {
    SimpleVector v1 = SimpleVector(1.0, 2.0);
    N_ASSERT(v1.getX() == 1.0);
    N_ASSERT(v1.getY() == 2.0);
    v1.setX(-1.25);
    N_ASSERT(v1.getX() == -1.25);
}

void test_vector_addition() {
    SimpleVector v1 = SimpleVector(1.0, 2.0);
    SimpleVector v2 = SimpleVector(0.5, 1.5);
    SimpleVector res = v1 + v2;
    
    N_ASSERT(res.getX() == 1.5);
    N_ASSERT(res.getY() == 3.5);
}

void test_vector_length() {
    SimpleVector v = SimpleVector(3.0, 4.0);
    N_ASSERT(v.abs() == std::hypot(3.0, 4.0));
}

void test_method_chaining() {
    SimpleVector v(0, 0);
    v.setX(10).setY(20);
    
    N_ASSERT(v.getX() == 10.0);
    N_ASSERT(v.getY() == 20.0);
}

int main() {
    TEST_HEADER;

    RUN_TEST(test_constructor_and_getters);
    RUN_TEST(test_vector_addition);
    RUN_TEST(test_vector_length);
    RUN_TEST(test_method_chaining);

    TEST_FOOTER;

    return (failed_tests == 0) ? 0 : 1;
}