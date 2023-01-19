# Arduino USB-to-LCD (i2c)

Simple setup to control an LCD with HD44780 compatible controller with i2c backpack.

Raw characters are passed tgrough.


## Requirements

* Arduino Pro Mini compatible board with atmega328
* Recent Python3 version
* Python venv


## How To

```
python3 -m venv venv
. venv/bin/activate
python3 -m pip install -r requirements.txt

# Build only:
platformio run

# (Build if necessary and) upload:
platformio run --upload-port /dev/ttyUSB0 -t upload
```


## Connect on commandline

```
sudo stty -F /dev/ttyUSB0 raw -echo -hupcl 115200
echo -ne "Hello world!" > /dev/ttyUSB0

# Clear display
echo -ne "\xFE\01" > /dev/ttyUSB0

# Set backlight on
echo -ne "\xFD\01" > /dev/ttyUSB0

# Set backlight off
echo -ne "\xFD\00" > /dev/ttyUSB0
```


## Notes

* baud rate is fixed at 115200
* Implementation is one-way. No reading back from display possible.


## References / Credits

* Uses PlatformIO: https://platformio.org/
* Arduino Library to drive the display: https://github.com/duinoWitchery/hd44780
* Code based on examples of the library from above


## License

MIT

Dependencies might have different licenses!
