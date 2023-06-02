#include "../suites.h"

SUITE(test_level_setup_teardown);

int test_setup_counter    = 0;
int test_teardown_counter = 0;

TEST_SETUP(test_level_setup_teardown)
{
    test_setup_counter += 1;
}

TEST_TEARDOWN(test_level_setup_teardown)
{
    test_teardown_counter += 1;
}

TEST(test_level_setup_teardown, "test1")
{
    ASSERT_EQUAL(1, test_setup_counter);
    ASSERT_EQUAL(0, test_teardown_counter);
}

TEST(test_level_setup_teardown, "test2")
{
    ASSERT_EQUAL(2, test_setup_counter);
    ASSERT_EQUAL(1, test_teardown_counter);
}

TEST(test_level_setup_teardown, "test3")
{
    ASSERT_EQUAL(3, test_setup_counter);
    ASSERT_EQUAL(2, test_teardown_counter);
}
