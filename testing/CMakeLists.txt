# make exec for list testing
add_executable(TestList testlist.cpp)
add_test(NAME TestList COMMAND TestList)
target_include_directories(TestList PRIVATE ${GTEST_INCLUDE} ../src)
target_link_libraries(TestList PRIVATE ${GTEST_LIB} ${GTEST_MAIN})

# make exec for game logic testing
add_executable(TestSnake testsnake.cpp)
add_test(NAME TestSnake COMMAND TestSnake)
target_include_directories(TestSnake PRIVATE ${GTEST_INCLUDE} ../src)
target_link_libraries(TestSnake PRIVATE ${GTEST_LIB} ${GTEST_MAIN})
