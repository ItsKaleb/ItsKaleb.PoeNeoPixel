# Olimex ESP32 PoE

This sketch is designed to allow for an `Olimex ESP32-PoE` board to be used as a PoE powered NeoPixel controller. 

> __Warning:__
> Per Olimex's own warnings, __DO NOT__ connect the `Olimex ESP32-PoE` to a PoE switch while connected to USB power.
> This can cause damage to the board and the connected computer.

> __Warning:__ 
> Due to power delivery constraints of the `Olimex ESP32-PoE`, current draw of the NeoPixels must be kept under 3W (600mA at 5V).
> This approximates to 10 individual NeoPixels at full power (60mA per pixel).
> 
> When measuring the current draw of a single `Jewel`, readings peaked at 160mA at full brightness white __without using the dedicated white LED__ (7 pixels).

# Hardware
* [Olimex ESP32-PoE](https://www.olimex.com/Products/IoT/ESP32/ESP32-POE/open-source-hardware)
* Suggested NeoPixel board: [Adafruit NeoPixel Jewel](https://www.adafruit.com/product/2226)

## Suggested pinout
| Olimex ESP32-PoE  | NeoPixel Jewel    |
|-------------------|-------------------|
| 5v                | 5v                |
| GND               | GND               |
| GPIO 4            | Data In           |

<a href="https://www.olimex.com/Products/IoT/ESP32/ESP32-POE/resources/ESP32-POE-GPIO.png"><img src="https://www.olimex.com/Products/IoT/ESP32/ESP32-POE/resources/ESP32-POE-GPIO.png" width="400"></a>

# Usage
1. Connect the `Olimex ESP32-PoE` board via USB to your computer.
1. Using the Arduino IDE, upload the sketch to the board.
    > Ensure the values of `NEOPIXEL_PIN`, `NEOPIXEL_NUMPIXELS` and `NEOPIXEL_TYPE` are set correctly for your NeoPixel board.
1. Open a serial console and set the baud rate to 115200.
1. Press the onboard reset button to start the sketch.
1. Wait for the sketch to initialize - you should be prompted for WiFi credentials
1. Use the CLI command `W` to set the WiFi credentials.
1. Use the CLI command `S ########` to set the pairing code for the accessory.
1. Open the Home app on your iOS device and add the accessory using the pairing code.
1. Confirm that accessory is responding as expected.

> __Note:__
> When compiling the sketch, ensure you set the partition scheme to `Minimal SPIFFS`.
> This is required to ensure the sketch has enough space for the HomeSpan library and the NeoPixel library.

## Ethernet
While the `Olimex ESP32-PoE` board is capable of using Ethernet, this sketch does not support it directly.
It is possible to connect the board via Ethernet, however there are issues in maintaining connection within the HomeSpan library.
See [issue #1058](https://github.com/HomeSpan/HomeSpan/issues/1058) for more details.

## Resetting the accessory
If you need to modify the sketch, you will usually need to reset the accessory's device ID.
1. Open the serial console and set the baud rate to 115200.
1. Use the CLI command `U` to unpair the accessory.
1. Use the CLI command `H` to reset the accessory's device ID.
1. Remove the accessory via the Home app on your iOS device and re-add it using the pairing code.
