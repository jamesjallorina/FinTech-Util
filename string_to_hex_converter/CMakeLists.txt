# To compile this with cmake 
# 1. Go to path=<string_to_hex_converter>
# 2. Create a build directory outside the source directory
# 3. Following are the steps to compile
#   a. mkdir build
#   b. cd build
#   c. cmake ../
#   d. make
# The final executable is in the build directory <elevator>
project(string_to_hex_converter)

add_executable(string_to_hex_converter string_to_hex_converter.c)
