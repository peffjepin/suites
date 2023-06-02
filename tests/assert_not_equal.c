#include "../suites.h"

#include <stdbool.h>
#include <stdint.h>

SUITE(assert_not_equal_tests);

TEST(assert_not_equal_tests, "bool failure")
{
    bool true_value  = true;
    bool false_value = false;
    ASSERT_NOT_EQUAL(true_value, true_value);
    ASSERT_NOT_EQUAL(false_value, false_value);
}

TEST(assert_not_equal_tests, "bool success")
{
    bool true_value  = true;
    bool false_value = false;
    ASSERT_NOT_EQUAL(true_value, false_value);
}

TEST(assert_not_equal_tests, "int failure")
{
    int value    = 10;
    int expected = 10;
    ASSERT_NOT_EQUAL(expected, value);
}

TEST(assert_not_equal_tests, "int success")
{
    int value    = 100;
    int expected = 10;
    ASSERT_NOT_EQUAL(expected, value);
}

TEST(assert_not_equal_tests, "uint failure")
{
    unsigned int value    = 10;
    unsigned int expected = 10;
    ASSERT_NOT_EQUAL(expected, value);
}

TEST(assert_not_equal_tests, "uint success")
{
    unsigned int value    = 109;
    unsigned int expected = 10;
    ASSERT_NOT_EQUAL(expected, value);
}

TEST(assert_not_equal_tests, "string failure")
{
    const char* value    = "abc";
    const char* expected = "abc";
    ASSERT_NOT_EQUAL(expected, value);
}

TEST(assert_not_equal_tests, "string success")
{
    const char* value    = "abc";
    const char* expected = "def";
    ASSERT_NOT_EQUAL(expected, value);
}

TEST(assert_not_equal_tests, "float failure")
{
    float value    = 1.f;
    float expected = 1.f;
    ASSERT_NOT_EQUAL(expected, value);
}

TEST(assert_not_equal_tests, "float success")
{
    float value    = 1.f;
    float expected = 2.f;
    ASSERT_NOT_EQUAL(expected, value);
}

TEST(assert_not_equal_tests, "float failure within precision")
{
    float value          = 1.f;
    float half_precision = SUITES_FLOAT_PRECISION / 2.f;
    ASSERT_NOT_EQUAL(value + half_precision, value);
    ASSERT_NOT_EQUAL(value - half_precision, value);
}

TEST(assert_not_equal_tests, "float success too large")
{
    float value               = 1.f;
    float too_much_difference = SUITES_FLOAT_PRECISION * 1.5f;
    ASSERT_NOT_EQUAL(value + too_much_difference, value);
}

TEST(assert_not_equal_tests, "float success too small")
{
    float value               = 1.f;
    float too_much_difference = SUITES_FLOAT_PRECISION * 1.5f;
    ASSERT_NOT_EQUAL(value - too_much_difference, value);
}

TEST(assert_not_equal_tests, "double failure")
{
    double value    = 1.f;
    double expected = 1.f;
    ASSERT_NOT_EQUAL(expected, value);
}

TEST(assert_not_equal_tests, "double success")
{
    double value    = 1.f;
    double expected = 2.f;
    ASSERT_NOT_EQUAL(expected, value);
}

TEST(assert_not_equal_tests, "double failure within precision")
{
    double value          = 1.f;
    double half_precision = SUITES_FLOAT_PRECISION / 2.f;
    ASSERT_NOT_EQUAL(value + half_precision, value);
    ASSERT_NOT_EQUAL(value - half_precision, value);
}

TEST(assert_not_equal_tests, "double success too large")
{
    double value               = 1.f;
    double too_much_difference = SUITES_FLOAT_PRECISION * 1.5f;
    ASSERT_NOT_EQUAL(value + too_much_difference, value);
}

TEST(assert_not_equal_tests, "double success too small")
{
    double value               = 1.f;
    double too_much_difference = SUITES_FLOAT_PRECISION * 1.5f;
    ASSERT_NOT_EQUAL(value - too_much_difference, value);
}

TEST(assert_not_equal_tests, "int8 failure")
{
    int8_t value    = 1;
    int8_t expected = 1;
    ASSERT_NOT_EQUAL(expected, value);
}

TEST(assert_not_equal_tests, "int8 success")
{
    int8_t value    = 1;
    int8_t expected = 2;
    ASSERT_NOT_EQUAL(expected, value);
}

TEST(assert_not_equal_tests, "int16 failure")
{
    int16_t value    = 1;
    int16_t expected = 1;
    ASSERT_NOT_EQUAL(expected, value);
}

TEST(assert_not_equal_tests, "int16 success")
{
    int16_t value    = 1;
    int16_t expected = 2;
    ASSERT_NOT_EQUAL(expected, value);
}

TEST(assert_not_equal_tests, "int32 failure")
{
    int32_t value    = 1;
    int32_t expected = 1;
    ASSERT_NOT_EQUAL(expected, value);
}

TEST(assert_not_equal_tests, "int32 success")
{
    int32_t value    = 1;
    int32_t expected = 2;
    ASSERT_NOT_EQUAL(expected, value);
}

TEST(assert_not_equal_tests, "int64 failure")
{
    int64_t value    = 1;
    int64_t expected = 1;
    ASSERT_NOT_EQUAL(expected, value);
}

TEST(assert_not_equal_tests, "int64 success")
{
    int64_t value    = 1;
    int64_t expected = 2;
    ASSERT_NOT_EQUAL(expected, value);
}

TEST(assert_not_equal_tests, "uint8 failure")
{
    uint8_t value    = 1;
    uint8_t expected = 1;
    ASSERT_NOT_EQUAL(expected, value);
}

TEST(assert_not_equal_tests, "uint8 success")
{
    uint8_t value    = 1;
    uint8_t expected = 2;
    ASSERT_NOT_EQUAL(expected, value);
}

TEST(assert_not_equal_tests, "uint16 failure")
{
    uint16_t value    = 1;
    uint16_t expected = 1;
    ASSERT_NOT_EQUAL(expected, value);
}

TEST(assert_not_equal_tests, "uint16 success")
{
    uint16_t value    = 1;
    uint16_t expected = 2;
    ASSERT_NOT_EQUAL(expected, value);
}

TEST(assert_not_equal_tests, "uint32 failure")
{
    uint32_t value    = 1;
    uint32_t expected = 1;
    ASSERT_NOT_EQUAL(expected, value);
}

TEST(assert_not_equal_tests, "uint32 success")
{
    uint32_t value    = 1;
    uint32_t expected = 2;
    ASSERT_NOT_EQUAL(expected, value);
}

TEST(assert_not_equal_tests, "uint64 failure")
{
    uint64_t value    = 1;
    uint64_t expected = 1;
    ASSERT_NOT_EQUAL(expected, value);
}

TEST(assert_not_equal_tests, "uint64 success")
{
    uint64_t value    = 1;
    uint64_t expected = 2;
    ASSERT_NOT_EQUAL(expected, value);
}

TEST(assert_not_equal_tests, "expression failure")
{
    ASSERT_NOT_EQUAL(11 * 3, 11 + 11 + 11);
}

TEST(assert_not_equal_tests, "expression success")
{
    ASSERT_NOT_EQUAL(11 * 3, 11 + 11 + 10);
}
