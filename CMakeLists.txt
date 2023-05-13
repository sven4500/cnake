cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(cnake VERSION 1.0)

# add the executable
add_executable(cnake src/cnake.c)

# check if gtest paths are known
if(GTEST_INCLUDE AND GTEST_LIB AND GTEST_MAIN)
  # this internally invokes enable_testing() and sets BUILD_TESTING on
  message("Testing enabled")
  include(CTest)
endif()

# include tests if testing BUILD_TESTING is on
if(BUILD_TESTING)
  # add testing subdir
  add_subdirectory(testing)
endif()
