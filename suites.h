#ifndef SUITES_H
#define SUITES_H

/*
 * REQUIRED COMPILER FEATURES:
 *   _Generic
 *   __attribute__((constructor))
 */

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#ifndef SUITES_DISABLE_COLORS
#define SUITES_COLOR_RESET "\x1b[0m"
#define SUITES_COLOR_GREEN "\x1b[32m"
#define SUITES_COLOR_RED "\x1b[31m"
#define SUITES_COLOR_LIGHT_RED "\x1b[91m"
#define SUITES_COLOR_YELLOW "\x1b[33m"
#else
#define SUITES_COLOR_RESET ""
#define SUITES_COLOR_GREEN ""
#define SUITES_COLOR_RED ""
#define SUITES_COLOR_LIGHT_RED ""
#define SUITES_COLOR_YELLOW ""
#endif

#ifndef SUITES_FLOAT_PRECISION
#define SUITES_FLOAT_PRECISION (0.0001)
#endif

// The number of suites the framework supports in a single invocation.
#ifndef SUITES_MAX_SUITES
#define SUITES_MAX_SUITES 1024
#endif

// The number of tests that can belong to a single suite.
#ifndef SUITES_CAPACITY
#define SUITES_CAPACITY 1024
#endif

struct suites_context {
    struct suites_suite* suite;
    struct suites_test*  test;
};

typedef void (*SuitesTestFunction)(struct suites_context);

struct suites_test {
    const char*        description;
    SuitesTestFunction function;
};

struct suites_suite {
    const char*  description;
    unsigned int failed;
    unsigned int passed;

    size_t             test_count;
    struct suites_test tests[SUITES_CAPACITY];

    void (*setup)(void);
    void (*teardown)(void);
    void (*per_test_setup)(void);
    void (*per_test_teardown)(void);
};

void _add_suite(struct suites_suite* suite);
void _add_test(struct suites_suite* suite, struct suites_test);

#define _JOIN(a, b) a##_##b
#define _JOIN_INDIRECT(a, b) _JOIN(a, b)
#define _MACRO_VAR(name) _JOIN_INDIRECT(name, __LINE__)
#define _ON_STARTUP(suite_name)                                                                    \
    __attribute__((constructor)) static void _MACRO_VAR(_JOIN(_on_startup, suite_name))(void)

#define SUITE(name)                                                                                \
    static struct suites_suite _MACRO_VAR(_JOIN(suite, name)) = {.description = #name};            \
    _ON_STARTUP(name)                                                                              \
    {                                                                                              \
        _add_suite(&_MACRO_VAR(_JOIN(suite, name)));                                               \
    }                                                                                              \
    static struct suites_suite* name = &_MACRO_VAR(_JOIN(suite, name))

#define SUITE_SETUP(suite)                                                                         \
    static void _MACRO_VAR(_JOIN(setup, suite))(void);                                             \
    _ON_STARTUP(suite)                                                                             \
    {                                                                                              \
        suite->setup = _MACRO_VAR(_JOIN(setup, suite));                                            \
    }                                                                                              \
    static void _MACRO_VAR(_JOIN(setup, suite))(void)

#define SUITE_TEARDOWN(suite)                                                                      \
    static void _MACRO_VAR(_JOIN(teardown, suite))(void);                                          \
    _ON_STARTUP(suite)                                                                             \
    {                                                                                              \
        suite->teardown = _MACRO_VAR(_JOIN(teardown, suite));                                      \
    }                                                                                              \
    static void _MACRO_VAR(_JOIN(teardown, suite))(void)

#define TEST_SETUP(suite)                                                                          \
    static void _MACRO_VAR(_JOIN(test_setup, suite))(void);                                        \
    _ON_STARTUP(suite)                                                                             \
    {                                                                                              \
        suite->per_test_setup = _MACRO_VAR(_JOIN(test_setup, suite));                              \
    }                                                                                              \
    static void _MACRO_VAR(_JOIN(test_setup, suite))(void)

#define TEST_TEARDOWN(suite)                                                                       \
    static void _MACRO_VAR(_JOIN(test_teardown, suite))(void);                                     \
    _ON_STARTUP(suite)                                                                             \
    {                                                                                              \
        suite->per_test_teardown = _MACRO_VAR(_JOIN(test_teardown, suite));                        \
    }                                                                                              \
    static void _MACRO_VAR(_JOIN(test_teardown, suite))(void)

#define TEST(suite, test_description)                                                              \
    static void _MACRO_VAR(_JOIN(test_function, suite))(struct suites_context);                    \
    _ON_STARTUP(suite)                                                                             \
    {                                                                                              \
        _add_test(                                                                                 \
            suite,                                                                                 \
            (struct suites_test){                                                                  \
                .function    = _MACRO_VAR(_JOIN(test_function, suite)),                            \
                .description = test_description,                                                   \
            }                                                                                      \
        );                                                                                         \
    }                                                                                              \
    static void _MACRO_VAR(_JOIN(test_function, suite))(struct suites_context _ctx_)

struct suites_assert_info {
    const char* expected_str;
    const char* actual_str;
    const char* file;
    int         line;
    const char* testname;
};

#define DEFINE_ASSERT_EQUAL_FN(type, name)                                                         \
    bool name(type expected, type actual, struct suites_assert_info)

#define DEFINE_ASSERT_NOT_EQUAL_FN(type, name)                                                     \
    bool name(type expected, type actual, struct suites_assert_info)

#define DEFINE_ASSERT_FN(type, name) bool name(type value, struct suites_assert_info)

DEFINE_ASSERT_FN(long long, _assert_int);
DEFINE_ASSERT_FN(unsigned long long, _assert_uint);
DEFINE_ASSERT_FN(double, _assert_float);
DEFINE_ASSERT_FN(char, _assert_char);
DEFINE_ASSERT_FN(const char*, _assert_string);
DEFINE_ASSERT_FN(const void*, _assert_pointer);
DEFINE_ASSERT_FN(bool, _assert_bool);

DEFINE_ASSERT_EQUAL_FN(long long, _assert_equal_int);
DEFINE_ASSERT_EQUAL_FN(unsigned long long, _assert_equal_uint);
DEFINE_ASSERT_EQUAL_FN(double, _assert_equal_float);
DEFINE_ASSERT_EQUAL_FN(char, _assert_equal_char);
DEFINE_ASSERT_EQUAL_FN(const char*, _assert_equal_string);
DEFINE_ASSERT_EQUAL_FN(const void*, _assert_equal_pointer);
DEFINE_ASSERT_EQUAL_FN(bool, _assert_equal_bool);

DEFINE_ASSERT_NOT_EQUAL_FN(long long, _assert_not_equal_int);
DEFINE_ASSERT_NOT_EQUAL_FN(unsigned long long, _assert_not_equal_uint);
DEFINE_ASSERT_NOT_EQUAL_FN(double, _assert_not_equal_float);
DEFINE_ASSERT_NOT_EQUAL_FN(char, _assert_not_equal_char);
DEFINE_ASSERT_NOT_EQUAL_FN(const char*, _assert_not_equal_string);
DEFINE_ASSERT_NOT_EQUAL_FN(const void*, _assert_not_equal_pointer);
DEFINE_ASSERT_NOT_EQUAL_FN(bool, _assert_not_equal_bool);

#define _ASSERT_EQUAL(expected, actual)                                                            \
    _Generic((expected),                                                                           \
        int: _assert_equal_int,                                                                    \
        float: _assert_equal_float,                                                                \
        double: _assert_equal_float,                                                               \
        char: _assert_equal_char,                                                                  \
        unsigned char: _assert_equal_uint,                                                         \
        signed char: _assert_equal_int,                                                            \
        unsigned int: _assert_equal_uint,                                                          \
        long: _assert_equal_int,                                                                   \
        unsigned long: _assert_equal_uint,                                                         \
        short: _assert_equal_int,                                                                  \
        unsigned short: _assert_equal_uint,                                                        \
        const char*: _assert_equal_string,                                                         \
        char*: _assert_equal_string,                                                               \
        bool: _assert_equal_bool,                                                                  \
        default: _assert_equal_pointer                                                             \
    )(                                                                                             \
        expected,                                                                                  \
        actual,                                                                                    \
        (struct suites_assert_info){                                                                 \
            .expected_str = #expected,                                                             \
            .actual_str = #actual,                                                                 \
            .file = __FILE__,                                                                      \
            .line = __LINE__,                                                                      \
            .testname = _ctx_.test->description,                                                   \
        }                                                                                          \
      )

#define _ASSERT_NOT_EQUAL(expected, actual)                                                        \
    _Generic((expected),                                                                           \
        int: _assert_not_equal_int,                                                                \
        float: _assert_not_equal_float,                                                            \
        double: _assert_not_equal_float,                                                           \
        char: _assert_not_equal_char,                                                              \
        unsigned char: _assert_not_equal_uint,                                                     \
        signed char: _assert_not_equal_int,                                                        \
        unsigned int: _assert_not_equal_uint,                                                      \
        long: _assert_not_equal_int,                                                               \
        unsigned long: _assert_not_equal_uint,                                                     \
        short: _assert_not_equal_int,                                                              \
        unsigned short: _assert_not_equal_uint,                                                    \
        long long: _assert_not_equal_int,                                                          \
        unsigned long long: _assert_not_equal_uint,                                                \
        const char*: _assert_not_equal_string,                                                     \
        char*: _assert_not_equal_string,                                                           \
        bool: _assert_not_equal_bool,                                                              \
        default: _assert_not_equal_pointer                                                         \
    )(                                                                                             \
        expected,                                                                                  \
        actual,                                                                                    \
        (struct suites_assert_info){                                                                 \
            .expected_str = #expected,                                                             \
            .actual_str = #actual,                                                                 \
            .file = __FILE__,                                                                      \
            .line = __LINE__,                                                                      \
            .testname = _ctx_.test->description,                                                   \
        }                                                                                          \
      )

#define _ASSERT(expression)                                                                        \
    _Generic((expression),                                                                         \
        int: _assert_int,                                                                          \
        float: _assert_float,                                                                      \
        double: _assert_float,                                                                     \
        char: _assert_char,                                                                        \
        unsigned char: _assert_uint,                                                               \
        signed char: _assert_int,                                                                  \
        unsigned int: _assert_uint,                                                                \
        long: _assert_int,                                                                         \
        unsigned long: _assert_uint,                                                               \
        short: _assert_int,                                                                        \
        unsigned short: _assert_uint,                                                              \
        long long: _assert_int,                                                                    \
        unsigned long long: _assert_uint,                                                          \
        const char*: _assert_string,                                                               \
        char*: _assert_string,                                                                     \
        bool: _assert_bool,                                                                        \
        default: _assert_pointer                                                                   \
    )(                                                                                             \
        (expression),                                                                              \
        (struct suites_assert_info){                                                                 \
            .actual_str = #expression,                                                             \
            .file = __FILE__,                                                                      \
            .line = __LINE__,                                                                      \
            .testname = _ctx_.test->description,                                                   \
        }                                                                                          \
      )

#define ASSERT_EQUAL(expected, actual)                                                             \
    do {                                                                                           \
        if (!_ASSERT_EQUAL(expected, actual)) {                                                    \
            _ctx_.suite->failed++;                                                                 \
            return;                                                                                \
        }                                                                                          \
    } while (0)

#define ASSERT_NOT_EQUAL(expected, actual)                                                         \
    do {                                                                                           \
        if (!_ASSERT_NOT_EQUAL(expected, actual)) {                                                \
            _ctx_.suite->failed++;                                                                 \
            return;                                                                                \
        }                                                                                          \
    } while (0)

#define ASSERT(expression)                                                                         \
    do {                                                                                           \
        if (!_ASSERT(expression)) {                                                                \
            _ctx_.suite->failed++;                                                                 \
            return;                                                                                \
        }                                                                                          \
    } while (0)

#ifdef SUITES_IMPLEMENTATION

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ASSERT_LOCATION_FMT "%s:%i:" SUITES_COLOR_YELLOW "%s" SUITES_COLOR_RESET
#define ASSERT_LOCATION_ARGS(info) info.file, info.line, info.testname

#define PRINT_ASSERT_EQUAL_FAILURE(expected, actual, info, fmtspec)                                \
    printf(                                                                                        \
        ASSERT_LOCATION_FMT " | ASSERT_EQUAL( %s (%s" fmtspec "%s), %s (%s" fmtspec "%s) )\n",     \
        ASSERT_LOCATION_ARGS(info),                                                                \
        info.expected_str,                                                                         \
        SUITES_COLOR_LIGHT_RED,                                                                    \
        (expected),                                                                                \
        SUITES_COLOR_RESET,                                                                        \
        info.actual_str,                                                                           \
        SUITES_COLOR_LIGHT_RED,                                                                    \
        (actual),                                                                                  \
        SUITES_COLOR_RESET                                                                         \
    )

#define PRIMITIVE_ASSERT_EQUAL_IMPLEMENTATION(printf_fmt_specifier)                                \
    if (expected != actual) {                                                                      \
        PRINT_ASSERT_EQUAL_FAILURE(expected, actual, info, printf_fmt_specifier);                  \
        return false;                                                                              \
    }                                                                                              \
    return true

#define PRINT_ASSERT_NOT_EQUAL_FAILURE(expected, actual, info, fmtspec)                            \
    printf(                                                                                        \
        ASSERT_LOCATION_FMT " | ASSERT_NOT_EQUAL( %s (%s" fmtspec "%s), %s (%s" fmtspec "%s) )\n", \
        ASSERT_LOCATION_ARGS(info),                                                                \
        info.expected_str,                                                                         \
        SUITES_COLOR_LIGHT_RED,                                                                    \
        (expected),                                                                                \
        SUITES_COLOR_RESET,                                                                        \
        info.actual_str,                                                                           \
        SUITES_COLOR_LIGHT_RED,                                                                    \
        (actual),                                                                                  \
        SUITES_COLOR_RESET                                                                         \
    )

#define PRIMITIVE_ASSERT_NOT_EQUAL_IMPLEMENTATION(printf_fmt_specifier)                            \
    if (expected == actual) {                                                                      \
        PRINT_ASSERT_NOT_EQUAL_FAILURE(expected, actual, info, printf_fmt_specifier);              \
        return false;                                                                              \
    }                                                                                              \
    return true

#define PRINT_ASSERT_FAILURE(value, info, fmtspec)                                                 \
    printf(                                                                                        \
        ASSERT_LOCATION_FMT " | ASSERT( %s (%s" fmtspec "%s) )\n",                                 \
        ASSERT_LOCATION_ARGS(info),                                                                \
        info.actual_str,                                                                           \
        SUITES_COLOR_LIGHT_RED,                                                                    \
        (value),                                                                                   \
        SUITES_COLOR_RESET                                                                         \
    )

#define PRIMITIVE_ASSERT_IMPLEMENTATION(printf_fmt_specifier)                                      \
    if (!value) {                                                                                  \
        PRINT_ASSERT_FAILURE(value, info, printf_fmt_specifier);                                   \
        return false;                                                                              \
    }                                                                                              \
    return true

bool
_assert_bool(bool value, struct suites_assert_info info)
{
    PRIMITIVE_ASSERT_IMPLEMENTATION("%i");
}

bool
_assert_int(long long value, struct suites_assert_info info)
{
    PRIMITIVE_ASSERT_IMPLEMENTATION("%lli");
}

bool
_assert_uint(unsigned long long value, struct suites_assert_info info)
{
    PRIMITIVE_ASSERT_IMPLEMENTATION("%llu");
}

bool
_assert_float(double value, struct suites_assert_info info)
{
    PRIMITIVE_ASSERT_IMPLEMENTATION("%f");
}

bool
_assert_char(char value, struct suites_assert_info info)
{
    PRIMITIVE_ASSERT_IMPLEMENTATION("%c");
}

bool
_assert_string(const char* value, struct suites_assert_info info)
{
    PRIMITIVE_ASSERT_IMPLEMENTATION("%s");
}

bool
_assert_pointer(const void* value, struct suites_assert_info info)
{
    PRIMITIVE_ASSERT_IMPLEMENTATION("%p");
}

bool
_assert_equal_bool(bool expected, bool actual, struct suites_assert_info info)
{
    PRIMITIVE_ASSERT_EQUAL_IMPLEMENTATION("%i");
}

bool
_assert_equal_int(long long expected, long long actual, struct suites_assert_info info)
{
    PRIMITIVE_ASSERT_EQUAL_IMPLEMENTATION("%lli");
}

bool
_assert_equal_float(double expected, double actual, struct suites_assert_info info)
{
    static const double PRECISION  = 0.0001;
    double              difference = expected - actual;
    if (difference < 0) difference *= -1;
    if (difference > PRECISION) {
        PRINT_ASSERT_EQUAL_FAILURE(expected, actual, info, "%f");
        return false;
    }
    return true;
}

bool
_assert_equal_string(const char* expected, const char* actual, struct suites_assert_info info)
{
    if (expected == NULL && actual == NULL) return true;
    if (expected == NULL || actual == NULL) return false;
    if (strcmp(expected, actual) != 0) {
        PRINT_ASSERT_EQUAL_FAILURE(expected, actual, info, "\"%s\"");
        return false;
    }
    return true;
}

bool
_assert_equal_char(char expected, char actual, struct suites_assert_info info)
{
    PRIMITIVE_ASSERT_EQUAL_IMPLEMENTATION("\'%c\'");
}

bool
_assert_equal_uint(
    unsigned long long expected, unsigned long long actual, struct suites_assert_info info
)
{
    PRIMITIVE_ASSERT_EQUAL_IMPLEMENTATION("%llu");
}

bool
_assert_equal_pointer(const void* expected, const void* actual, struct suites_assert_info info)
{
    PRIMITIVE_ASSERT_EQUAL_IMPLEMENTATION("%p");
}

bool
_assert_not_equal_bool(bool expected, bool actual, struct suites_assert_info info)
{
    PRIMITIVE_ASSERT_NOT_EQUAL_IMPLEMENTATION("%i");
}

bool
_assert_not_equal_float(double expected, double actual, struct suites_assert_info info)
{
    static const double PRECISION  = 0.0001;
    double              difference = expected - actual;
    if (difference < 0) difference *= -1;
    if (difference < PRECISION) {
        PRINT_ASSERT_NOT_EQUAL_FAILURE(expected, actual, info, "%f");
        return false;
    }
    return true;
}

bool
_assert_not_equal_string(const char* expected, const char* actual, struct suites_assert_info info)
{
    if (expected == NULL && actual == NULL) return true;
    if (expected == NULL || actual == NULL || strcmp(expected, actual) == 0) {
        PRINT_ASSERT_NOT_EQUAL_FAILURE(expected, actual, info, "\"%s\"");
        return false;
    }
    return true;
}

bool
_assert_not_equal_char(char expected, char actual, struct suites_assert_info info)
{
    PRIMITIVE_ASSERT_NOT_EQUAL_IMPLEMENTATION("\'%c\'");
}

bool
_assert_not_equal_uint(
    unsigned long long expected, unsigned long long actual, struct suites_assert_info info
)
{
    PRIMITIVE_ASSERT_NOT_EQUAL_IMPLEMENTATION("%llu");
}

bool
_assert_not_equal_int(long long expected, long long actual, struct suites_assert_info info)
{
    PRIMITIVE_ASSERT_NOT_EQUAL_IMPLEMENTATION("%lli");
}

bool
_assert_not_equal_pointer(const void* expected, const void* actual, struct suites_assert_info info)
{
    PRIMITIVE_ASSERT_NOT_EQUAL_IMPLEMENTATION("%p");
}

struct suites_suite* _internal_suites_array[SUITES_MAX_SUITES] = {0};
size_t               _internal_suites_array_count              = 0;
static size_t        _longest_suite_name                       = 1;

void
_add_suite(struct suites_suite* suite)
{
    if (_internal_suites_array_count >= SUITES_MAX_SUITES) {
        fprintf(
            stderr,
            "ERROR: too many test suites defined (`#define SUITES_MAX_SUITES N` "
            "before importing suites.h to increase maximum to `N`)\n"
        );
        exit(1);
    }
    size_t namelen      = strlen(suite->description);
    _longest_suite_name = (_longest_suite_name > namelen) ? _longest_suite_name : namelen;
    _internal_suites_array[_internal_suites_array_count++] = suite;
}

void
_add_test(struct suites_suite* suite, struct suites_test test)
{
    if (suite->test_count == SUITES_CAPACITY) {
        fprintf(
            stderr,
            "ERROR: too many tests (%zu) in suite %s (`#define SUITES_CAPACITY N`"
            "before importing suites.h to increase maximum to `N`)\n",
            suite->test_count,
            suite->description
        );
        exit(1);
    }
    suite->tests[suite->test_count++] = test;
}

void
print_test_suite_results(struct suites_suite* suite)
{
    printf(
        "%-*s | Tests run: %s%-3zu%s | Tests passed: %s%-3u%s | Tests failed: "
        "%s%-3u%s\n",
        (int)_longest_suite_name,
        suite->description,
        SUITES_COLOR_YELLOW,
        suite->test_count,
        SUITES_COLOR_RESET,
        SUITES_COLOR_GREEN,
        suite->passed,
        SUITES_COLOR_RESET,
        SUITES_COLOR_RED,
        suite->failed,
        SUITES_COLOR_RESET
    );
}

static void
run_suite(struct suites_suite* suite)
{
    if (suite->setup != NULL) {
        suite->setup();
    }

    for (size_t i = 0; i < suite->test_count; i++) {
        struct suites_test test   = suite->tests[i];
        const unsigned int failed = suite->failed;
        if (suite->per_test_setup != NULL) suite->per_test_setup();
        test.function((struct suites_context){
            .suite = suite,
            .test  = &test,
        });
        if (suite->per_test_teardown != NULL) suite->per_test_teardown();
        if (failed == suite->failed) suite->passed++;
    }

    if (suite->teardown != NULL) {
        suite->teardown();
    }
}

int
main(void)
{
    struct suites_suite accumulative = {.description = "total"};
    for (size_t i = 0; i < _internal_suites_array_count; i++) {
        struct suites_suite* suite = _internal_suites_array[i];
        run_suite(suite);

        accumulative.test_count += suite->test_count;
        accumulative.failed += suite->failed;
        accumulative.passed += suite->passed;
    }
    printf("\n");
    for (size_t i = 0; i < _internal_suites_array_count; i++) {
        struct suites_suite* suite = _internal_suites_array[i];
        print_test_suite_results(suite);
    }
    if (_internal_suites_array_count > 1) {
        printf("\n");
        print_test_suite_results(&accumulative);
    }
    return accumulative.failed ? EXIT_FAILURE : EXIT_SUCCESS;
}

#endif  // SUITES_IMPLEMENTATION

#endif  // SUITES_H

/*
==============================================================================
OPTION 1 (MIT)
==============================================================================

Copyright (c) 2023, Jeffrey Pepin.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.


==============================================================================
OPTION 2 (Public Domain)
==============================================================================

This is free and unencumbered software released into the public domain.
Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
software, either in source code form or as a compiled binary, for any purpose,
commercial or non-commercial, and by any means.
In jurisdictions that recognize copyright laws, the author or authors of this
software dedicate any and all copyright interest in the software to the public
domain. We make this dedication for the benefit of the public at large and to
the detriment of our heirs and successors. We intend this dedication to be an
overt act of relinquishment in perpetuity of all present and future rights to
this software under copyright law.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
