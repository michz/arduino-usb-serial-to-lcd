// vi:ts=4

#include <Wire.h>
#include <hd44780.h>                       // main hd44780 header
#include <hd44780ioClass/hd44780_I2Cexp.h> // i2c expander i/o class header

// LCD geometry
const int LCD_COLS = 20;
const int LCD_ROWS = 4;

hd44780_I2Cexp lcd(0x27, LCD_COLS, LCD_ROWS); // declare lcd object: auto locate & auto config expander chip

void(* resetFunc) (void) = 0; // declare reset function @ address 0

void setup()
{
    Serial.begin(115200);

    int status;
    status = lcd.begin(LCD_COLS, LCD_ROWS);
    if (status) {
        // hd44780 has a fatalError() routine that blinks an led if possible
        // begin() failed so blink error code using the onboard LED if possible
        hd44780::fatalError(status); // does not return
        Serial.println("Error!");
        Serial.println(status);
        delay(2000);
        resetFunc();
    }

    // initalization was successful, the backlight should be on now
    lcd.noCursor();
}

void loop() {
    uint8_t rxbyte;

    while (Serial.available()) {
        rxbyte = Serial.read();

        if (0xFE == rxbyte) {
            // Next byte is a command, wait for it
            while (!Serial.available()) { /* noop */ }
            rxbyte = Serial.read();
            lcd.command(rxbyte);
        } else if (0xFD == rxbyte) {
            // Next byte is a backlight command, wait for it
            while (!Serial.available()) { /* noop */ }
            rxbyte = Serial.read();

            if (rxbyte == 0) {
                lcd.noBacklight();
            } else {
                lcd.backlight();
            }
        } else {
            // This is a normal text character
            lcd.write(rxbyte);
        }
    }
}
