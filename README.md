# kellerkompanie-rename-addons

Little C++ based CLI tool that renames all addon files to lowercase on linux servers.

## Building from source

```bash
mkdir cmake-build
cmake -DCMAKE_BUILD_TYPE=Release -B cmake-build
cmake --build cmake-build --target all -- -j 8
```

## Install

```bash
cp cmake-build/kekorename /usr/bin/
chmod +x /usr/bin/kekorename
```