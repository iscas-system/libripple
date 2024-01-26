# libripple
The fundamental node, communication, overlay and consistency management of Ripple.

## Dependency
- libuuid: used to generate uuid
```shell
dnf install libuuid-devel
```
- sqlite: embedded database
```shell
dnf install sqlite-devel
```
- libuv: async I/O framework 
```shell
# requires EPEL
dnf install libuv-devel
```