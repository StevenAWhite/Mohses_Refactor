# AMM - TCP Bridge

#### Requirements
The TCP Bridge requires the [AMM Standard Library](https://github.com/AdvancedModularManikin/amm-library) be built and available (and so requires FastRTPS and FastCDR).  In addition to the AMM library dependancies, the TCP Bridge also requires:
- tinyxml2 (`apt-get install libtinyxml2-dev`)

 

### Installation
```bash
    $ git clone https://github.com/AdvancedModularManikin/tcp-bridge
    $ mkdir tcp-bridge/build && cd tcp-bridge/build
    $ cmake ..
    $ cmake --build . --target install
```

By default on a Linux system this will install into `/usr/local/bin`

