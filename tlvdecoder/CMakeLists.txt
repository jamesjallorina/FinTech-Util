# To compile this with cmake 
# 1. Go to path=<tlvdecoder>
# 2. Create a build directory outside the source directory
# 3. Following are the steps to compile
#	a. mkdir build
#	b. cd build
#	c. cmake ../tlvdecoder
#	d. make
# The final executable is in the build directory <tlvdecoder>
project(tlvdecoder)

add_executable(tlvdecoder tlvdecoder.cxx)
