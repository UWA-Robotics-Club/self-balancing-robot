---
layout: default
title: Arduino Microcontrollers
nav_order: 2
#parent: ..
#has_children: ...
---

# Arduino Microcontrollers
{: .no_toc }

<details open markdown="block">
  <summary>
    Table of contents
  </summary>
  {: .text-delta }
1. TOC
{:toc}
</details>

## The Arduino Nano
The Arduino Nano is a small, low-cost microcontroller board using the ATmega328P microcontroller chip. The board includes 14 digital input/output pins (6 provide PWM output) and 8 analog inputs. It has a clock speed of 16 MHz, a recommended input voltage of 7-12V, an operating voltage (logic level) of 5V and 40mA DC current per I/O pin. The board also comes with a USB interface for easy programming and communication. The Arduino Nano can be programmed using the Arduino Software (IDE), which is an open-source software platform for programming Arduino microcontrollers.


### Pinout Diagram
![Pinout diagram](http://127.0.0.1:4000/assets/arduino_microcontrollers/Arduino-nano-pinout.png)

## Arduino Integrated Environment (IDE)
The Arduino Integrated Environment or Arduino Software (IDE) is an open-source platform containing a text editor for writing code, a message area, a text console, a tool bar with buttons for common functions and a series of menus. It allows us to write programs for an Arduino board and easily upload it.

{: .highlight }
> For more information on the Arduino IDE, click <a href="https://docs.arduino.cc/learn/starting-guide/the-arduino-software-ide" target="_blank">here</a>!


### Installation
To install the Arduino IDE 2.0:
1. Click <a href="https://www.arduino.cc/en/software#future-version-of-the-arduino-ide" and target="_blank">here</a> to access the download page for Arduino IDE 2.0.  
![Download page](http://127.0.0.1:4000/assets/arduino_microcontrollers/download_1.png)
2. Click the "Just Download" button to download for free.
![Just download](http://127.0.0.1:4000/assets/arduino_microcontrollers/download_2.png)
3. Run the client and follow the prompts to finish installing.
![Just download](http://127.0.0.1:4000/assets/arduino_microcontrollers/download_3.png)

### Uploading Programs
To upload an Arduino program onto the Nano (using the Arduino IDE):
1. Connect the Arduino Nano to your device using a USB cable.
2. Choose the correct COM port and Arduino board.
![COM port and board](http://127.0.0.1:4000/assets/arduino_microcontrollers/upload_program_1.png)
![COM port and board](http://127.0.0.1:4000/assets/arduino_microcontrollers/upload_program_2.png)
3. Click on the upload button to upload your program onto the Arduino board. This will also verify that your syntax is correct.
![Upload button](http://127.0.0.1:4000/assets/arduino_microcontrollers/upload_program_3.png)

{: .highlight }
> Tip: If your code fails to upload try changing the bootloader to the old bootloader 
![Upload button](http://127.0.0.1:4000/assets/arduino_microcontrollers/upload_program_4.png)

For easier debugging, "Show verbose output" during compile and upload. This allows you to see any errors that occur while compiling and uploading.
![File to Preferences](http://127.0.0.1:4000/assets/arduino_microcontrollers/ide_tips_1.png)
![Show verbose output](http://127.0.0.1:4000/assets/arduino_microcontrollers/ide_tips_2.png)

### Features
The Arduino IDE provides a 'Serial Monitor' where we can easily print messages such as the output from a sensor. If your message contains only numerical values, you can also use the 'Serial Plotter' to graph those values.
![Serial monitor and plotter](http://127.0.0.1:4000/assets/arduino_microcontrollers/features_1.png)

The Arduino IDE also features a debugger which allows you to set breakpoints and track the values of your variables while your program is running.
![Debugger](http://127.0.0.1:4000/assets/arduino_microcontrollers/features_2.png)


## Arduino Code
Upon startup, the Arduino IDE will create a new sketch (programs written using Arduino software) with the basic structure of a sketch already in place. This basic structure includes two main functions: setup() and loop().
![structure](http://127.0.0.1:4000/assets/arduino_microcontrollers/structure.png)

### Setup() and Loop()
The special function `setup()` is run once at the start of every program. 
In this function, we often:
- Initialise variables
- Setup modes for digital I/O pins
- Setup up communication (e.g. using `Serial.begin()`)

This is then followed by the special function `loop()` which is repeated for an indefinite amount of time. In `loop()` we will write the main program, which is this case will be the control loop for the self-balancing robot.

### Syntax
Other than its special functions, Arduino software follows C/C++ syntax including:
- the use of semicolons at the end of each statement
- curly brackets to organise functions
- return type before the function name
- variable type before its name
- etc.

To import libraries, we can also use the keyword `#include` followed by the name of the library.

### Commonly-Used Functions
Some functions that you may need during this project include:
- `pinMode(pin, mode)`: configures the specified pin to behave either as input or output.
- `digitalWrite(pin, value)`: write a HIGH or LOW to a digital pin.
- `digitalRead(pin)`: returns the value of a specified digital pin, either HIGH or LOW.
- `analogWrite(pin, value)`: writes an analog (PWM wave) to a pin. The value must be an integer from 0 to 255.
- `analogRead(pin)`: reads the value from the specified analog pin. For the Nano, the analog input pins are A0 to A7.
- `delay(ms)`: pauses the program for the specified amount of time (in milliseconds).
- `Serial.begin(speed)`: sets the data rate in bits per second (baud) for serial data transmission.
- `Serial.print(val)`: prints data to the serial port as human-readable ASCII text.
- `Serial.println(val)`: prints data to the serial port as human-readable ASCII text followed by a carriage return character (ASCII 13, or '\r') and a newline character (ASCII 10, or '\n'). 

{: .highlight }
> For a more comprehensive list of in-built Arduino functions, click <a href="https://www.arduino.cc/reference/en/" target="_blank">here</a>!
