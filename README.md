# Parking-sensor-esp32

## Bill of Materials
The project needs an esp32 (ESP32-WROOM-32),  HW-508 passive buzzer, a HC-SR04 ultrasonic sensor, 3 LEDs (green, yellow, red), 3 resistors, breadboard and jumper wires.
No soldering needed.


## Wiring
Passive Buzzer:     - -> GND
                    + -> Pin 4

Green LED:          Anode -> Resisitor -> Pin 21
                    Cathode -> GND

Yellow LED:         Anode -> Resisitor -> Pin 22
                    Cathode -> GND

Red LED:            Anode -> Resisitor -> Pin 23
                    Cathode -> GND

Ultrasonic sensor:  Vcc -> VIN
                    Trig -> Pin 18
                    Echo -> Pin 19
                    Gnd -> Gnd


## Dependencies
No library needed

## User guide
The ultrasonic sensor detects an object in range 2cm - 17cm.
Based on the distance, the buzzer will beep (faster when closer) and the LEDs light up accordingly.

## Code features
Non blocking buzzer logic
0.5 cm transition zones between states for smoother detection

## Installation

### Prerequisites
1. Download and install the [Arduino IDE](https://www.arduino.cc/en/software).
2. Install the ESP32 board package in the Arduino IDE (follow [Espressif's official guide](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html) if you haven't done this before).

### Setup Steps
1. **Clone the repository:**
   ```bash
   git clone (https://github.com/SzekelyK05/Parking-sensor-esp32.git)

(Or download the repository as a ZIP file and extract it).
2. Open the sketch: Open the src/main.ino file in the Arduino IDE.

Configure your board:

Go to Tools > Board and select ESP32 Dev Module (or your specific ESP32 variant).

Go to Tools > Port and select the USB port your ESP32 is connected to.

Flash the firmware: Click the Upload button to compile and push the code to your board.