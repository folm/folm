![Folm Logo](https://folm.io/images/logo_at_readme.png)

"Valuable secure Privacy cryptocurrency"

<a href="https://discord.gg/uDmpSHx"><img src="https://discordapp.com/api/guilds/398369914760593419/embed.png" alt="Discord server" /></a>


| [Website](https://folm.io) |[Block Explorer](https://explorer.folm.io/) |

Features
=============

* Folm Coin - Masternode
* New PHI1612 PoW/MN algorithm thanks for 216k155
* MN Reward


The Folmcore Project is a decentralized peer-to-peer banking financial platform, created under an open source license, featuring a built-in cryptocurrency, end-to-end encrypted messaging and decentralized marketplace. The decentralized network aims to provide anonymity and privacy for everyone through a simple user-friendly interface by taking care of all the advanced cryptography in the background.

## Coin Specifications

| Specification | Value |
|:-----------|:-----------|
| Total Blocks | `8,409,600` |
| Block Size | `4MB` |
| Block Time | `120s` |
| PoW Reward | `30 FLM` |
| Masternode Requirement | `5,000 FLM` |
| Masternode Reward | `15 FLM First Year` - `20 FLM Second Year` |
| Port | `53656` |
| RPC Port | `53654` |
| Masternode Port | `53656` |




| Year | PoW Reward | MN Reward |
|:-----------|:-----------|:-----------|
| 1 | `30 FLM` | `15 FLM` |
| 2 | `20 FLM` | `20 FLM` |
| 3 | `10 FLM` | `15 FLM` |
| 4 | `5 FLM` | `10 FLM` |
| 5 | `2.5 FLM` | `7.5 FLM` |



Build Folm Wallet
----------

### Building for 64-bit Windows

The first step is to install the mingw-w64 cross-compilation tool chain. Due to different Ubuntu packages for each distribution and problems with the Xenial packages the steps for each are different.

Common steps to install mingw32 cross compiler tool chain:

    sudo apt install g++-mingw-w64-x86-64
    
Ubuntu Xenial 16.04 and Windows Subsystem for Linux

    sudo apt install software-properties-common
    sudo add-apt-repository "deb http://archive.ubuntu.com/ubuntu zesty universe"
    sudo apt update
    sudo apt upgrade
    sudo update-alternatives --config x86_64-w64-mingw32-g++ # Set the default mingw32 g++ compiler option to posix.
    
Once the tool chain is installed the build steps are common:

Note that for WSL the folm Core source path MUST be somewhere in the default mount file system, for example /usr/src/folm, AND not under /mnt/d/. If this is not the case the dependency autoconf scripts will fail. This means you cannot use a directory that located directly on the host Windows file system to perform the build.

The next three steps are an example of how to acquire the source in an appropriate way.

    cd /usr/src
    sudo git clone https://github.com/folm/folm.git
    sudo chmod -R a+rw folm
    
Once the source code is ready the build steps are below.

    PATH=$(echo "$PATH" | sed -e 's/:\/mnt.*//g') # strip out problematic Windows %PATH% imported var
    cd depends
    make HOST=x86_64-w64-mingw32 -j4
    cd ..
    ./autogen.sh # not required when building from tarball
    CONFIG_SITE=$PWD/depends/x86_64-w64-mingw32/share/config.site 
    ./configure --prefix=`pwd`/depends/x86_64-w64-mingw32 --disable-tests
    make HOST=x86_64-w64-mingw32 -j4

### Build on Ubuntu

    sudo apt-get install build-essential libtool autotools-dev automake pkg-config libssl-dev libevent-dev bsdmainutils git cmake libboost-all-dev
    sudo apt-get install software-properties-common
    sudo add-apt-repository ppa:bitcoin/bitcoin
    sudo apt-get update
    sudo apt-get install libdb4.8-dev libdb4.8++-dev

    # If you want to build the Qt GUI:
    sudo apt-get install libqt5gui5 libqt5core5a libqt5dbus5 qttools5-dev qttools5-dev-tools libprotobuf-dev protobuf-compiler

    git clone https://github.com/folm/folm --recursive
    
    cd folm

    # Note autogen will prompt to install some more dependencies if needed
    ./autogen.sh
    ./configure 
    make -j4

### Build on OSX

The commands in this guide should be executed in a Terminal application.
The built-in one is located in `/Applications/Utilities/Terminal.app`.

#### Preparation

Install the OS X command line tools:

`xcode-select --install`

When the popup appears, click `Install`.

Then install [Homebrew](https://brew.sh).

#### Dependencies

    brew install cmake automake berkeley-db4 libtool boost --c++11 --without-single --without-static miniupnpc openssl pkg-config protobuf qt5 libevent imagemagick --with-librsvg

NOTE: Building with Qt4 is still supported, however, could result in a broken UI. Building with Qt5 is recommended.

#### Build Folm Core

1. Clone the folm source code and cd into `folm`

        git clone --recursive https://github.com/folm/folm.git
        cd folm

2.  Build Folm Core:

    Configure and build the headless folm binaries as well as the GUI (if Qt is found).

    You can disable the GUI build by passing `--without-gui` to configure.

        ./autogen.sh
        ./configure
        make

3.  It is recommended to build and run the unit tests:

        make check

### Run

Then you can either run the command-line daemon using `src/folmd` and `src/folm-cli`, or you can run the Qt GUI using `src/qt/folm-qt`

For in-depth description of Sparknet and how to use Folm for interacting with contracts, please see [sparknet-guide](doc/sparknet-guide.md).

License
-------

Folmcore is GPLv3 licensed.

Development Process
-------------------

The `master` branch is regularly built and tested, but is not guaranteed to be
completely stable. [Tags](https://github.com/folm/folm/tags) are created
regularly to indicate new official, stable release versions of Folm.

The contribution workflow is described in [CONTRIBUTING.md](CONTRIBUTING.md).


Testing
-------

Testing and code review is the bottleneck for development; we get more pull
requests than we can review and test on short notice. Please be patient and help out by testing
other people's pull requests, and remember this is a security-critical project where any mistake might cost people
lots of money.

### Automated Testing

Developers are strongly encouraged to write [unit tests](src/test/README.md) for new code, and to
submit new unit tests for old code. Unit tests can be compiled and run
(assuming they weren't disabled in configure) with: `make check`. Further details on running
and extending unit tests can be found in [/src/test/README.md](/src/test/README.md).

There are also [regression and integration tests](/qa) of the RPC interface, written
in Python, that are run automatically on the build server.
These tests can be run (if the [test dependencies](/qa) are installed) with: `qa/pull-tester/rpc-tests.py`

### Manual Quality Assurance (QA) Testing

Changes should be tested by somebody other than the developer who wrote the
code. This is especially important for large or high-risk changes. It is useful
to add a test plan to the pull request description if testing the changes is
not straightforward.
