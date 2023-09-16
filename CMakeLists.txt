cmake_minimum_required(VERSION 3.0.0)
project(Crave VERSION 0.1.0)

include(CTest)
enable_testing()

find_package(LibXml2 REQUIRED)
find_package(CURL REQUIRED)
include_directories(${LIBXML2_INCLUDE_DIRS})
include_directories(${CURL_INCLUDE_DIRS})



# Add your source files
add_executable(Crave Crave.cpp Crave.h)
#add_library(Test Test.cpp)

# Link against libcurl
target_link_libraries(Crave PRIVATE ${CURL_LIBRARIES} ${LIBXML2_LIBRARIES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
