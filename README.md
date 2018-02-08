# Calibrator
This is a Calibrator to calibrate your camera with opencv. It can work on Linux OS.

In order to calibrate your camera conveniently, a class will be useful and extensible.

# Directories
/src                  : main source code(modifiable)

/build                : .makefile files after cmake command

/bin                  : executable files after make command and .xml file

/bin/mynteye_images   : calibrated images captured by your camera

/cmake                : cmake files needed by CMakeLists.txt

/include              : Calibrator.h and Calibrator.cpp

/lib                  : library files after cmake, generally empty

/mynteye_lib          : mynteye packages containing its .so files

/mynteye_include      : mynteye packages containing its .h files

# File
CMakeLists.txt: modifiable to adapt your own camera with opencv libraries and mynteye camera module libraries
                (because the author uses mynteye to expriment)
                
# Software Environment

Linux + openCV 3.0+ + cmake + gcc

But it is also applicable for VS under windows after proper settings.

# Hardware Requirements

mynteye camera module

Or you need to modify CMakeLists.txt and main source code with your own preference, and it is not hard.

# Firstly Use

1. Open directory "build" in Terminal under Linux

2. In Terminal: $ cmake ../                  and you will find some files created in directory "build"

3. In Terminal: $ make                       and you will find some files created in directory "bin"

4. In Terminal: $ cd ../bin                  you now command in directory "bin"

5. In Terminal: $ ./mynteye_camera_calib     execute mynteye_camera_calib.o

6. Operate with hints printed in Terminal window, and you will got camera calibrated parameters.

Good Luck! If you have any questions, please leave your messages.

