# suites.h

This is a simple header only library for testing in C.

The library requires your C compiler supports C11 `_Generic` and `__attribute__((constructor))`

## Example

See the test directory to see how the library can be used. The following commands show how to
compile and execute the example tests and what you can expect the output to look like.

Terminal output is colored, if this is not supported in your environment or undesirable add the compile
flag `-DSUITES_DISABLE_COLORS` at compile time.

```sh
>>> gcc tests/main.c -o test && ./test

tests/assert.c:17:bool failure | ASSERT( 0 (0) )
tests/assert.c:23:bool value failure | ASSERT( false_value (0) )
tests/assert.c:33:int failure | ASSERT( 0 (0) )
tests/assert.c:43:uint failure | ASSERT( 0u (0) )
tests/assert.c:58:string failure | ASSERT( ((void *)0) ((nil)) )
tests/assert.c:68:float failure | ASSERT( 0.f (0.000000) )
tests/assert.c:78:double failure | ASSERT( 0. (0.000000) )
tests/assert.c:90:int8 failure | ASSERT( value (0) )
tests/assert.c:102:int16 failure | ASSERT( value (0) )
tests/assert.c:114:int32 failure | ASSERT( value (0) )
tests/assert.c:126:int64 failure | ASSERT( value (0) )
tests/assert.c:138:uint8 failure | ASSERT( value (0) )
tests/assert.c:150:uint16 failure | ASSERT( value (0) )
tests/assert.c:162:uint32 failure | ASSERT( value (0) )
tests/assert.c:174:uint64 failure | ASSERT( value (0) )
tests/assert.c:184:expression failure | ASSERT( (1 + 2 + 3) * 0 (0) )
tests/assert_equal.c:20:bool failure | ASSERT_EQUAL( true_value (1), false_value (0) )
tests/assert_equal.c:34:int failure | ASSERT_EQUAL( expected (10), value (100) )
tests/assert_equal.c:48:uint failure | ASSERT_EQUAL( expected (10), value (109) )
tests/assert_equal.c:62:string failure | ASSERT_EQUAL( expected ("def"), value ("abc") )
tests/assert_equal.c:76:float failure | ASSERT_EQUAL( expected (2.000000), value (1.000000) )
tests/assert_equal.c:91:float failure too large | ASSERT_EQUAL( value + too_much_difference (1.000150), value (1.000000) )
tests/assert_equal.c:98:float failure too small | ASSERT_EQUAL( value - too_much_difference (0.999850), value (1.000000) )
tests/assert_equal.c:112:double failure | ASSERT_EQUAL( expected (2.000000), value (1.000000) )
tests/assert_equal.c:127:double failure too large | ASSERT_EQUAL( value + too_much_difference (1.000150), value (1.000000) )
tests/assert_equal.c:134:double failure too small | ASSERT_EQUAL( value - too_much_difference (0.999850), value (1.000000) )
tests/assert_equal.c:148:int8 failure | ASSERT_EQUAL( expected (2), value (1) )
tests/assert_equal.c:162:int16 failure | ASSERT_EQUAL( expected (2), value (1) )
tests/assert_equal.c:176:int32 failure | ASSERT_EQUAL( expected (2), value (1) )
tests/assert_equal.c:190:int64 failure | ASSERT_EQUAL( expected (2), value (1) )
tests/assert_equal.c:204:uint8 failure | ASSERT_EQUAL( expected (2), value (1) )
tests/assert_equal.c:218:uint16 failure | ASSERT_EQUAL( expected (2), value (1) )
tests/assert_equal.c:232:uint32 failure | ASSERT_EQUAL( expected (2), value (1) )
tests/assert_equal.c:246:uint64 failure | ASSERT_EQUAL( expected (2), value (1) )
tests/assert_equal.c:256:expression failure | ASSERT_EQUAL( 11 * 3 (33), 11 + 11 + 10 (32) )
tests/assert_not_equal.c:12:bool failure | ASSERT_NOT_EQUAL( true_value (1), true_value (1) )
tests/assert_not_equal.c:27:int failure | ASSERT_NOT_EQUAL( expected (10), value (10) )
tests/assert_not_equal.c:41:uint failure | ASSERT_NOT_EQUAL( expected (10), value (10) )
tests/assert_not_equal.c:55:string failure | ASSERT_NOT_EQUAL( expected ("abc"), value ("abc") )
tests/assert_not_equal.c:69:float failure | ASSERT_NOT_EQUAL( expected (1.000000), value (1.000000) )
tests/assert_not_equal.c:83:float failure within precision | ASSERT_NOT_EQUAL( value + half_precision (1.000050), value (1.000000) )
tests/assert_not_equal.c:105:double failure | ASSERT_NOT_EQUAL( expected (1.000000), value (1.000000) )
tests/assert_not_equal.c:119:double failure within precision | ASSERT_NOT_EQUAL( value + half_precision (1.000050), value (1.000000) )
tests/assert_not_equal.c:141:int8 failure | ASSERT_NOT_EQUAL( expected (1), value (1) )
tests/assert_not_equal.c:155:int16 failure | ASSERT_NOT_EQUAL( expected (1), value (1) )
tests/assert_not_equal.c:169:int32 failure | ASSERT_NOT_EQUAL( expected (1), value (1) )
tests/assert_not_equal.c:183:int64 failure | ASSERT_NOT_EQUAL( expected (1), value (1) )
tests/assert_not_equal.c:197:uint8 failure | ASSERT_NOT_EQUAL( expected (1), value (1) )
tests/assert_not_equal.c:211:uint16 failure | ASSERT_NOT_EQUAL( expected (1), value (1) )
tests/assert_not_equal.c:225:uint32 failure | ASSERT_NOT_EQUAL( expected (1), value (1) )
tests/assert_not_equal.c:239:uint64 failure | ASSERT_NOT_EQUAL( expected (1), value (1) )
tests/assert_not_equal.c:251:expression failure | ASSERT_NOT_EQUAL( 11 * 3 (33), 11 + 11 + 11 (33) )

assert_tests              | Tests run: 32  | Tests passed: 16  | Tests failed: 16 
assert_equal_tests        | Tests run: 36  | Tests passed: 17  | Tests failed: 19 
assert_not_equal_tests    | Tests run: 36  | Tests passed: 19  | Tests failed: 17 
suite_level_setup         | Tests run: 2   | Tests passed: 2   | Tests failed: 0  
suite_level_teardown      | Tests run: 2   | Tests passed: 2   | Tests failed: 0  
test_level_setup_teardown | Tests run: 3   | Tests passed: 3   | Tests failed: 0  

total                     | Tests run: 111 | Tests passed: 59  | Tests failed: 52 


# executing just one test file from the suite
>>> gcc tests/suite_setup_teardown.c -o test -DSUITES_IMPLEMENTATION && ./test

suite_level_setup    | Tests run: 2   | Tests passed: 2   | Tests failed: 0  
suite_level_teardown | Tests run: 2   | Tests passed: 2   | Tests failed: 0  

total                | Tests run: 4   | Tests passed: 4   | Tests failed: 0  
```

