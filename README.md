# MoHSES Core Modules - Metapackage

This is the MoHSES Core Modules metapackage.

It includes all the modules needed to run a MoHSES simulation as well as the `tcp-bridge` and `rest-adapter` for prototyping connectivity.

## Requirments

Mohses is an open-source multiplatform library, but modules that depend on pistache are not avaliable on non nix platforms.  The following develoment tools are required to get started.

| Tool | Version | Website|
|------|---------|--------|
| CMake | >3.18  | [https://cmake.org/download/] |
| Ninja (Optional) | N/A | [https://ninja-build.org/] |
| Meson | N/A | [https://mesonbuild.com/]|

### Thirdparty Libraries

Mohses depends on several opensouce libraries which act as thirdparty dependencies.  Our build system includes a method for pulling and downloading these libraries if you must build them from source, but often installing them through yoru systems package system will be preferred. 

|  Library | Version | Source | System Preferred | Note    |
|----------|---------|--------|---------------|---------|
| openssl  |  > 3.X  | [https://github.com/openssl/openssl.git]| True | Build requires perl |  
| boost    |  > 1.8X | [https://github.com/boostorg/boost.git] | True | |  
| tinyxml2 |  > 8.1.0 | [https://github.com/leethomason/tinyxml2.git]| True |
| foonathan_memory | v0.7-3 | [https://github.com/foonathan/memory.git]| False | Use ThirdParty/Fetch |
| sqlite3 | N/A | [https://github.com/azadkuh/sqlite-amalgamation.git]| True |  
| fastcdr | v1.0.27 | [https://github.com/eProsima/Fast-CDR.git]| False |
| fastddr | v2.10.0 | [https://github.com/eProsima/Fast-DDS.git]| False |
| rapidjson  | v1.1.0  | [https://github.com/Tencent/rapidjson.git]| True | 
| xercesc | xerces-3.2.2 | [https://github.com/apache/xerces-c.git]| True |
| xsd | 4.0.1 | [https://www.codesynthesis.com/products/xsd/download.xhtml]| True |
| eigen | 3.3.9.X | [https://gitlab.com/stevenawhite/eigen.git]| True |
| biogears | master | [https://github.com/BioGearsEngine/core.git]| False |
| pistache | master | [https://github.com/pistacheio/pistache.git] | False |

## Setting up a build environment

Mohses can be built on windows and macos, but its primarly supported on debian 
base distributions.  If you need simple explanation of our build system skip to [Building Mohses]

## Ubuntu 11

### 1) Setting up the build envionment

```bash
    $ sudo apt install git build-essential ninja-build meson xsdcxx cmake-curses-gui
    $ git clone https://github.com/StevenAWhite/Mohses_Refactor Mohses
    $ mkdir -p Mohses/build

```

This will install gcc, g++, ninja, meson, and cmake.  You can build mohses against clang
using clang, but that is outside of scope these instructions.  

### 2) Option 1: Using MOHSES_FETCH_THIRDPARTY=ON 

MOHSES_FETCH_THIRDPARTY is a command line paramter which tells the MOHSES build system to fetch
and install all dependecies that are not detected. While the script can build all dependencies. 
We highly recomend you install libssl libboost libz and xsdcxx using your package management system.
When cross compiling concider that xsdcxx has two rolls the first is to run a native code generator and 
the second is to acccess cxx headers at build time. So you will need both packages or to make the native 
headers avaliable to the cross compiler sysroot via symlink or copy.  In this example we build all but the
above mentioned third party libraries and install them in the users home directory 


```bash
    $ sudo apt install libssl-dev libboost-all-dev libz-dev
    $ cmake -G Ninja -D CMAKE_INSTALL_PREFIX=/home/amm/usr/ \
                     -D MOHSES_FETCH_THIRDPARTY=ON  \
                     -B Mohses/build \
                     -S Mohses/
   $ cmake --build Mohses/build 
```
Note that the underlying Function ExternalProject_Add automatically installs packages in the value of
CMAKE_INSTALL_PREFIX so no install target needs to be called in this example check /home/amm/usr to view
the additonal dependencies. 

### 3) Option 2: Apt base dependency installs

Mohses has a very specific depency for fastddr and biogears. In this example we install all
but FastCDR/FASTDDR and BioGears using apt. Then use MOHSES_FETCH_THIRDPARTY to simplify the building of
BioGears and FastDDR.

```bash
    $ sudo apt install libssl-dev libboost-all-dev libz-dev
    $ sudo apt install libtinyxml2-dev libfoonathan-memory-dev \
                       libsqlite3-dev rapidjson-dev \
                        libxerces-c-dev libeigen3-dev
    $ cmake -G Ninja -D CMAKE_INSTALL_PREFIX=/home/amm/usr/ \
                     -D MOHSES_FETCH_THIRDPARTY=ON  \
                     -B Mohses/build \
                     -S Mohses
    $ cmake --build Mohses/build
```

If you wanted to build FastCDR, FastDDR, Pistache, BioGears yourself. You would simply set the 
CMAKE_PREFIX_PATH variable to include the INSTALL_ROOT of the installations. For example if a previous
user had placed the dependecies in `/home/amm/usr` passing `-D CMAKE_PREFIX_PATH=/home/amm/usr` to the cmake
configuration would allow it to find all the dependcies.  For cross compilation set `-D CMAKE_FIND_ROOT_PATH=/home/amm/cross-sysroot`
instead assuming /home/amm/cross-sysroot is the location of the cross-compiled dependencies. You can use `CMAKE_TOOLCHAIN_FILE` 
when `MOHSES_FETCH_THIRDPARTY=ON` to instruct CMAKE to cross compile all of the dependencies and install them in your
`CMAKE_INSTALL_PREFIX`

### 4) Building Mohses Libraries

We can reuse the previous build directory for this step, but we need to disable `MOHSES_FETCH_THIRDPARTY`.
We can also choose to install our MOHSES components in a different installation directory if we choose.
In this example we will install mohses in `/home/amm/mohses`

```bash
    $ cmake -G Ninja -D CMAKE_INSTALL_PREFIX=/home/amm/mohses/ \
                     -D MOHSES_FETCH_THIRDPARTY=OFF  \
                     -B Mohses/build \
                     -S Mohses
    $ cmake --build Mohses/build
```

## Cross Compilation

CMake makes targeting non native relatively easy. To succesfully cross compile you will need
to create a TOOLCHAIN_FILE which defines the SYSROOT location and dev tools.  For Debian based systems
we have included a toolchain file for aarch64-linux-gnu.  The following instructions give a brief
overview of cross-compiling with CMake. If you have a specific use case such as targeting Android
, iOS or embedded targets. See your devices vendor documentation for more information.

### 1) Adding aarch64 to debians MultiArch config

```bash
    $ sudo dpkg --add-architecture arm64
    $ sudo apt update
    $ sudo apt install crossbuild-essential-arm64
```

### 2) Installing third party dependencies

```bash
    $ sudo apt install  libssl-dev:arm64 libz-dev:arm64 \
                        libfoonathan-memory-dev:arm64 \ 
                        libsqlite3-dev:arm64 rapidjson-dev:arm64 \
                        libxerces-c-dev:arm64 libeigen3-dev:arm64 \
                        libtinyxml2-dev:arm64 libboost-dev:arm64 \
                        libboost-filesystem-dev:arm64 \
                        libboost-serialization-dev:arm64 \
                        libboost-program-options-dev:arm64 \
                        libboost-thread-dev:arm64 \
                        libboost-exception-dev:arm64 \
                        libboost-container-dev:arm64
   # Debian doesn't duplicate headers
   $ sudo ln -s  /usr/include/boost/ /usr/aarch64-linux-gnu/include/boost
   $ sudo ln -s  /usr/include/openssl/ /usr/aarch64-linux-gnu/include/openssl
   $ sudo ln -s  /usr/include/zlib.h  /usr/aarch64-linux-gnu/include/
   $ sudo ln -s  /usr/include/zconf.h  /usr/aarch64-linux-gnu/include/
   $ sudo ln -s /usr/include/tinyxml2.h  /usr/aarch64-linux-gnu/include/


```

### 3) Building Remaining Dependencies

```bash
    $ git clone git@github.com:StevenAWhite/Mohses_Refactor.git Mohses
    $ mkdir -p Mohses/build-aarch64-linux-gnu
    $ cmake -G Ninja -D CMAKE_INSTALL_PREFIX=/home/amm/mohses/aarch64-linux-gnu \
                     -D CMAKE_TOOLCHAIN_FILE=Mohses/cmake/toolchains/aarch64-linux-gnu.cmake
                     -D MOHSES_FETCH_THIRDPARTY=OFF  \
                     -B Mohses/build-aarch64-linux-gnu \
                     -S Mohses
    $ cmake --build Mohses/build-aarch64-linux-gnu
    $ cmake --build Mohses/build-aarch64-linux-gnu --target install
```


## Installing Mohses as an Administrator



## Running Mohses System

## Migrating from AMM 1.2.1 to Mohses 2.0
