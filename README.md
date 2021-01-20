# README #

**geodata** is a cross platform CLI application which converts written
numbers in words to digits. Execute `geodata -h` for usage info (or
look at `app/app.cpp` and search for `case HELP`).

### Development environment

This project contains a development docker image from which all development
and testing can be performed. Tests are implemented by use of the [catch2](catch2)
testing framework. Workflow example:

```sh
docker build . -t geodata:beta
docker run -it -v $HOME:/host --rm geodata:beta

# cd to your mounted geodata project directory
cd /host/<myprojects>/geodata

# build release with debugging symbols
./build-debug.sh

# execute unit tests
./build/unittest

# execute end to end tests
./build/e2etest

# execute help to show application usage
./build/geodata -h
```

### How to build a production release? ###

To build a production release for your platform you will need the following
dependencies installed on your system:

* [gcc](gcc) c++14 compatible compiler
* [cmake](cmake)

Build a production release:

```sh
cmake -DCMAKE_BUILD_TYPE=Release -check-system-vars .
```

[catch2]:https://github.com/catchorg/Catch2
[cmake]: https://cmake.org/
[gcc]: https://gcc.gnu.org/
