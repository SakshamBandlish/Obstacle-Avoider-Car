# 🤖 Autonomous Obstacle-Avoiding Robot (Tinkercad & Physical Build Guide)

An autonomous, self-directing 2WD robot built using an Arduino UNO, an L293D/L298N motor driver, and an ultrasonic distance sensor. The robot mimics basic robotic navigation mapping logic—constantly scanning its environment, detecting spatial boundaries within 20cm, alerting via an active audio buzzer, reversing, and pivoting to recalculate a clear pathway.

---

## 📌 Project Overview
* **Difficulty:** ⭐⭐☆☆☆
* **Duration:** 7 Days (Structured learning path)
* **Core Application:** Autonomous navigation, embedded logic flow, sensor-actuator integration.

### ✨ Key Features
* 🚗 **Autonomous Navigation:** Drives forward dynamically without human intervention.
* 📏 **Real-Time Spatial Scanning:** Constantly samples distance boundaries 24/7.
* 🛑 **Collision Mitigation:** Instantly halts operations if an obstacle enters the 20cm hazard threshold.
* 🔔 **Acoustic Feedback:** Emits a distinct dual-tone audio frequency upon detection.
* 🔄 **Dynamic Path Correction:** Reverses and executes directional pivotal turns to discover non-blocked vectors.

---

## 🛒 System Architecture & Components



### 1. Hardware Deep Dive
* **Microcontroller:** Arduino UNO (ATmega328P architecture running at 16 MHz internal clock speed).
* **Motor Driver Module:** L293D Push-Pull Four-Channel Driver IC / L298N Dual H-Bridge Module. Handles high-current inductive loads (up to 2A peak per channel) to drive the chassis gearboxes without back-powering or damaging the MCU's fragile I/O pins.
* **Proximity Sensor:** 3-Pin / 4-Pin Ultrasonic Transceiver (utilizing speed-of-sound calculations based on ultrasonic wave flight time variables).
* **Actuators:** Dual 3V-6V DC Hobby Gear Motors paired with rubber traction wheels and an omnidirectional passive front caster wheel.
* **Audio Feedback:** 5V Active Piezo Buzzer.

### 2. High-Level Logic Map

```mermaid
graph TD
    A[Power On / Init System] --> B[Measure Distance via Ping Sensor]
    B --> C{Distance < 20cm?}
    C -- No --> D[Drive Forward] --> B
    C -- Yes --> E[Halt Motors]
    E --> F[Sound Buzzer Alert]
    F --> G[Execute Reverse Vector]
    G --> H[Pivot Right]
    H --> I{Is Path Clear Now?}
    I -- Yes --> D
    I -- No --> J[Pivot Left] --> D
