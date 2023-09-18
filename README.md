# Compiling

You can use compile.sh script. At first,
- make it executable
```bash
    $ chmod +x compile.sh
```
- then simply run it

```bash
    $ ./compile.sh
```

Or you can do it manually by this,
```bash
    $ mkdir build # creating build directory
    $ cd build 
    $ cmake .. # calling cmake
    $ make     # compile
```
