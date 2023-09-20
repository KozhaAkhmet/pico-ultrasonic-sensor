# About

A library for Raspberry Pi Pico with filtering algorithms for the Ultrasonic Sensor(HC-S04).

# Compilation

Run the compile.sh script.
  Make it executable and run:
```bash
    $ chmod +x compile.sh
    $ ./compile.sh
```

To compile from scratch, run the following commands:
```bash
    $ mkdir build # creating build directory
    $ cd build 
    $ cmake .. # calling cmake
    $ make     # compile
```
# Visualization

For plotting I suggest to use [serialplotter](https://github.com/hyOzd/serialplot/tree/master) which is written in Qt.
Example ScreenShot:
![SerialPlotter SS](media/Screenshot%20from%202023-09-20%2015-09-41.png)
