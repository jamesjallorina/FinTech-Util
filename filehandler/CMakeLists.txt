# To compile this with cmake 
# 1. Go to path=<filehandler>
# 2. Create a build directory outside the source directory
# 3. Following are the steps to compile
#	a. mkdir build
#	b. cd build
#	c. cmake ../filehandler
#	d. make
# The final executable is in the build directory <elevator>
project(filehandler)

add_executable(filehandler filehandler.cxx)
