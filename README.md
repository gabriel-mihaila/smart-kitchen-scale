# smart-kitchen-scale
Smart kitchen scale is a digital system for measuring the weights using the technology behind an Arduino UNO board.
## Use and functionalities
The system thus presented is very easy to use and has a multitude of functionalities:
- In order to run the system, it must be connected to a device (eg. a laptop) located in
voltage, the connection being made via a USB cable;
- Once the system is connected to the laptop, it is waiting for the bluetooth connection to be able to be
start the scale using a command on the phone (if you type the word "Start" in
the serial terminal of the Bluetooth system, it will transmit the information to the PC and will
start the calibration stage). In the meantime, until the system is activated by the so-called
"Magic word", the name of the scale will be displayed on the LCD: "Digital Weight Measuring
1.0 ”;
- During the calibration stage, the measured values ​​on the scale will be displayed in the Serial Monitor
(about 0g at first). Then a standard weight will be placed (in my case, a battery
weighing 60g) to check that the calibration factor is set correctly, and
the values ​​displayed in Serial Monitor are satisfactory. Otherwise, it may change
the calibration factor with 10 units, typing in the Serial Monitor the character ‘+’ or ‘a’ to
increases by 10 units, respectively ‘-’ or ‘z’ to decrease by 10 units;
- After the calibration step has been completed, you can start the system and display it on the LCD
the weight of the objects on the scale in real time, the ‘s’ character will be typed in the Serial Monitor.
From now on, the scale could function normally, placing various objects on it
to be able to determine their exact weight.
## Other features
- The scale has two displays: a standard one in grams which is displayed by default,
as well as a display in kilograms. The transition from grams to kilograms and vice versa is done
pressing the first button on the right of the plate with the 4 buttons (K1). It will execute
an interruption that will automatically convert the unit displayed on the LCD;
- Also, if we want to change the reference after which we weigh the objects (for example
we put an object on the scale and we want to put another object that we want to find out
the exact weight without moving the first object) there is also a button that resets it
reference, placing the scale on 0g;
- If the scale detects a considerable weight (for example, I set it to 2 kg), it will
sends a warning message on the phone that the weight on the scale has exceeded 2 kg.
## System screenshots
![Calibration phase](https://i.pinimg.com/564x/8b/e6/6e/8be66e452d4f269a5cf6e25fc5bd7d70.jpg#gh-dark-mode-only)
![Calibration phase](https://i.pinimg.com/564x/9a/76/08/9a76083675c88e651004e105c621ca34.jpg#gh-dark-mode-only)
![Calibration phase](https://i.pinimg.com/564x/d4/99/5a/d4995a5e98926b829abf37768e92109e.jpg#gh-dark-mode-only)
## Used components
- 1x Arduino UNO board
- 1x weight sensor
- 2x wooden boards
- 1x LCD I2C 16x2 (green color)
- 1x HX711 module for weight sensor
- 1x Bluetooth hc-05 module 
- 1x 4 buttons board
- 1x USB cable
- father-father and mother-father 


