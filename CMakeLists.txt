cmake_minimum_required(VERSION 3.17)
project(image_processor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(MY_PROJECT_FILES
        image.cpp
        image.h
        fileformat.h
        bmp.cpp
        bmp.h
        filter.h
        linearfilter.h
        linearfilter.cpp
        grayscale.h
        grayscale.cpp
        crop.h
        crop.cpp
        negative.h
        negative.cpp
        sharpening.h
        edgedetection.cpp
        edgedetection.h
        gaussianblur.h
        canny.h
        canny.cpp)

add_executable(image_processor
        image_processor.cpp
        ${MY_PROJECT_FILES})

enable_testing()

include(FetchContent)

FetchContent_Declare(googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG e2239ee6043f73722e7aa812a459f54a28552929
        )

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(test_image_processor test/test.cpp  ${MY_PROJECT_FILES})

target_link_libraries(test_image_processor PUBLIC gtest_main)
target_include_directories(test_image_processor PUBLIC .)

include(GoogleTest)

gtest_discover_tests(test_image_processor)