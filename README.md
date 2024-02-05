# libripple
The fundamental node, communication, overlay and consistency management of Ripple.

## Dependency
- libuuid: used to generate uuid
```shell
# For CentOS Stream 8 & openEuler 23.09 (x86-64)
$ dnf install libuuid-devel
# For openEuler 23.09 (RISC-V)
$ dnf install util-linux-devel
```
- sqlite: embedded database
```shell
# For CentOS Stream 8 & openEuler 23.09 (x86-64 / RISC-V)
$ dnf install sqlite-devel
```
- libuv: async I/O framework 
```shell
# For CentOS Stream 8 (requires EPEL) & openEuler 23.09 (x86-64)
$ dnf install libuv-devel
```
For openEuler 23.09 (RISC-V), you may need to build from source:
```shell
$ dnf install automake
$ dnf install libtool
$ wget https://dist.libuv.org/dist/v1.47.0/libuv-v1.47.0.tar.gz
$ tar -zxvf libuv-v1.47.0.tar.gz
$ cd libuv-v1.47.0
$ sh autogen.sh
$ ./configure
$ make
$ make check # make check cannot be run in root
$ make install
```
