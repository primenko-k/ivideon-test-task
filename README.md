# Ivideon Test Task

Ivideon Test Task is a client/server application to test programming skills on
C++ language and Bash scripting language.

## Compiling

Prerequisites:

* g++
* boost libraries (including boost_filesystem, boost_system and boost_thread)
* qmake (to generate Makefile)

The application is Qt Creator project. So the most convenient way to build
project is from Qt Creator. But you can build project manually with

    cd $SOURCE_DIRECTORY
    qmake
    make

Installation ("make install") is not needed.
If you want to build debug version add to qmake argument 'CONFIG+=debug'.

## Usage

After the build process is completed there will be two executable files in
project directory:

* cam_server - server binary
* cam_control - bash script to provide convenient interface to server

Just execute these two files to run application.


