cmake_minimum_required(VERSION 3.30)
project(mongo_tut CXX)


find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBMONGOCXX REQUIRED libmongocxx)
pkg_check_modules(LIBBSONCXX REQUIRED libbsoncxx)


add_executable(mongo_tut src/quickstart.cpp)

target_include_directories(mongo_tut PRIVATE ${LIBMONGOCXX_INCLUDE_DIRS} ${LIBBSONCXX_INCLUDE_DIRS})
target_link_libraries(mongo_tut ${LIBMONGOCXX_LIBRARIES} ${LIBBSONCXX_LIBRARIES})