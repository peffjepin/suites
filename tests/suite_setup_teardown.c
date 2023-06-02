#include "../suites.h"

SUITE(suite_level_setup);

int suite_setup_counter    = 0;
int suite_teardown_counter = 0;

SUITE_SETUP(suite_level_setup)
{
    suite_setup_counter += 1;
}

SUITE_TEARDOWN(suite_level_setup)
{
    suite_teardown_counter += 1;
}

TEST(suite_level_setup, "test1")
{
    ASSERT_EQUAL(1, suite_setup_counter);
    ASSERT_EQUAL(0, suite_teardown_counter);
}

TEST(suite_level_setup, "test2")
{
    ASSERT_EQUAL(1, suite_setup_counter);
    ASSERT_EQUAL(0, suite_teardown_counter);
}

SUITE(suite_level_teardown);

TEST(suite_level_teardown, "test1")
{
    ASSERT_EQUAL(1, suite_setup_counter);
    ASSERT_EQUAL(1, suite_teardown_counter);
}

TEST(suite_level_teardown, "test2")
{
    ASSERT_EQUAL(1, suite_setup_counter);
    ASSERT_EQUAL(1, suite_teardown_counter);
}
