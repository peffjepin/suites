#include "../suites.h"

#include <stdbool.h>
#include <stdint.h>

SUITE(assert_tests);

TEST(assert_tests, "bool success")
{
    bool true_value = true;
    ASSERT(true);
    ASSERT(true_value);
}

TEST(assert_tests, "bool failure")
{
    ASSERT(false);
}

TEST(assert_tests, "bool value failure")
{
    bool false_value = false;
    ASSERT(false_value);
}

TEST(assert_tests, "int success")
{
    ASSERT(1);
}

TEST(assert_tests, "int failure")
{
    ASSERT(0);
}

TEST(assert_tests, "uint success")
{
    ASSERT(1u);
}

TEST(assert_tests, "uint failure")
{
    ASSERT(0u);
}

TEST(assert_tests, "string success")
{
    ASSERT("abc");
}

TEST(assert_tests, "string success empty")
{
    ASSERT("");
}

TEST(assert_tests, "string failure")
{
    ASSERT(NULL);
}

TEST(assert_tests, "float success")
{
    ASSERT(0.5f);
}

TEST(assert_tests, "float failure")
{
    ASSERT(0.f);
}

TEST(assert_tests, "double success")
{
    ASSERT(0.5);
}

TEST(assert_tests, "double failure")
{
    ASSERT(0.);
}

TEST(assert_tests, "int8 success")
{
    int8_t value = 1;
    ASSERT(value);
}

TEST(assert_tests, "int8 failure")
{
    int8_t value = 0;
    ASSERT(value);
}

TEST(assert_tests, "int16 success")
{
    int16_t value = 1;
    ASSERT(value);
}

TEST(assert_tests, "int16 failure")
{
    int16_t value = 0;
    ASSERT(value);
}

TEST(assert_tests, "int32 success")
{
    int32_t value = 1;
    ASSERT(value);
}

TEST(assert_tests, "int32 failure")
{
    int32_t value = 0;
    ASSERT(value);
}

TEST(assert_tests, "int64 success")
{
    int64_t value = 1;
    ASSERT(value);
}

TEST(assert_tests, "int64 failure")
{
    int64_t value = 0;
    ASSERT(value);
}

TEST(assert_tests, "uint8 success")
{
    uint8_t value = 1;
    ASSERT(value);
}

TEST(assert_tests, "uint8 failure")
{
    uint8_t value = 0;
    ASSERT(value);
}

TEST(assert_tests, "uint16 success")
{
    uint16_t value = 1;
    ASSERT(value);
}

TEST(assert_tests, "uint16 failure")
{
    uint16_t value = 0;
    ASSERT(value);
}

TEST(assert_tests, "uint32 success")
{
    uint32_t value = 1;
    ASSERT(value);
}

TEST(assert_tests, "uint32 failure")
{
    uint32_t value = 0;
    ASSERT(value);
}

TEST(assert_tests, "uint64 success")
{
    uint64_t value = 1;
    ASSERT(value);
}

TEST(assert_tests, "uint64 failure")
{
    uint64_t value = 0;
    ASSERT(value);
}

TEST(assert_tests, "expression success")
{
    ASSERT(0 + 3 - 2);
}

TEST(assert_tests, "expression failure")
{
    ASSERT((1 + 2 + 3) * 0);
}
