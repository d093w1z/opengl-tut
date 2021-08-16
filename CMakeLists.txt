cmake_minimum_required(VERSION 3.0.0)
project(libmygraph VERSION 0.1.0)

set(SOURCE_FILES "src")

# include(CTest)
enable_testing()

add_library(libmygraph SHARED ${SOURCE_FILES}/libmygraph.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
include(CPack)

set(CMAKE_CXX_STANDARD 11)
set(OpenGL_GL_PREFERENCE "GLVND")

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchCOntent_MakeAvailable(googletest)
find_package(glfw3 3.3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
enable_testing()

add_executable(
    lib-test
    ${SOURCE_FILES}/test.cpp
)
add_executable(
    main
    ${SOURCE_FILES}/main.cpp
    ${SOURCE_FILES}/renderer
    ${SOURCE_FILES}/indexBuffer
    ${SOURCE_FILES}/bufferLayout
    ${SOURCE_FILES}/vertexBuffer
    ${SOURCE_FILES}/vertexArray
)

target_link_libraries(
    lib-test
    gtest_main
    libmygraph
)
target_link_libraries(
    main
    glfw
    GLEW
    OpenGL::GL
    libmygraph
)
include(GoogleTest)
gtest_discover_tests(lib-test)