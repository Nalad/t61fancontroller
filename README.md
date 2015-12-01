# t61fancontroller

T61FanController is a program which will automatically switch the fan in our
T61 under Linux.

### Requirements

- thinkpad-acpi in your kernel
- fan_control=1 module parameter for thinkpad-acpi

### Compilation

    make

### Usage

    usage: main arg1 arg2 arg3

    arguments:
        arg1        interval beetwen checks of temperature when fan is off
        arg2        interval beetwen checks of temperature when fan is on
        arg3        level of temperature at which fan will turn on

### Author

- Alan Drozd

### Notes

[How to control fan speed](http://www.thinkwiki.org/wiki/How_to_control_fan_speed)
