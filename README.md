# README #

**geodata** is a cross platform CLI application which cleans up car journey
geo-location data. Execute `geodata -h` for usage info (or look at `app/app.cpp`
and search for `HELP`).

### Development environment

This project contains a development docker image from which all development
and testing can be performed. Tests are implemented by use of the [catch2](catch2)
testing framework. Workflow example:

```sh
docker build . -t geodata:beta
docker run -it -v $PWD:/host --rm geodata:beta

# cd to your mounted geodata project directory
cd /host

# build release with debugging symbols
./build-debug.sh

cd into build directory (NB: test *.csv files are relative to this dir), and
execute e2e and unit - tests.

```sh
cd build
./unittest
./e2etest
```

For more info execute help to show application usage:

```sh
./geodata -h
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
