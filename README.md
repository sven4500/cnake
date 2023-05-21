# cnake
Console version of the Snake video game. Written in pure C, straightforward linked list is implemented, adjustable screen size. Unit tests are implemented using gtest testing framework.

```console
+------------------------------------------------------+
|                                                      | 3
|                                                      |
|                                                      |
|                                                      |
|                                                      |
|                                  o                   |
|                                                      |
|                                                      |
|                                                      |
|                                     <.?              |
|                                                      |
|                                                      |
|                                                      |
|                                                      |
+------------------------------------------------------+
```

## Testing

Unit tests are included in this repository. Run cmake providing `GTEST_INCLUDE`, `GTEST_LIB` and `GTEST_MAIN` definitions.

```bash
mkdir build
cd build
cmake -DGTEST_INCLUDE=<path_to_gtest_headers> -DGTEST_LIB=<path_to_gtest_lib> -DGTEST_MAIN=<path_to_gtest_main> ..
```

`GTEST_INCLUDE` is location where gtest headers are stored. This directory should contain gtest folder with header files so that path to `#include <gtest/gtest.h>` is resolved.

`GTEST_LIB` points out for gtest library where all of gtest functionality is implemented.

`GTEST_MAIN` points out for gtest main library where entry point for running test is implemented. Size of this library is little. This library provides `int main` entry point to run tests.
