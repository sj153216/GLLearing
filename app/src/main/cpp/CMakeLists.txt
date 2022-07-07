# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.10.2)

# Declares and names the project.

project("gllearning")

#find_path(GLES3_INCLUDE_DIR GLES2/gl3.h
#        HINTS ${ANDROID_NDK})

message("sj" + ${CMAKE_SOURCE_DIR})


include_directories(
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/..cpp
)


add_library( # Sets the name of the library.
        gllearning

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        native-lib.cpp
        geometric/Triangle.cpp
        util/gl_util.cpp)




find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

find_library( # Sets the name of the path variable.
        gl

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        GLESv3)


target_link_libraries( # Specifies the target library.
        gllearning
        ${gl}

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib})