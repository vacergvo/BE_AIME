# Smart Device Project: Nanoparticle Gas Sensor & IoT Shield
**UF "Smart Devices" – PTP Innovative Smart System (ISS)**

## 1. Project Overview
This project involves the design and realization of a smart device based on a custom-made tungsten trioxide ($WO_3$) nanoparticle gas sensor[cite: 17, 34]. [cite_start]The final objective is to combine this sensor with an electronic card to communicate data over a low-speed network using LoRa.

## 2. The Measurement Chain
### Nanoparticle Gas Sensor (AIME)
Developed during a training period at AIME, this sensor utilizes:
* **Synthesis**: Nanoparticles produced and deposited by dielectrophoresis.
* **Active Zone**: A sensitive layer of $WO_3$ nanoparticles integrated on aluminum interdigitated combs.
* **Target Gases**: High sensitivity to Ethanol and Ammonium.
* **Control**: Features an internal poly-silicon heating resistor and an aluminum temperature sensor.

### Analog Interface Circuit
The sensor is interfaced via a transimpedance circuit designed to measure its resistance.
* **Amplification**: Utilizes an LTC1050 precision chopper amplifier.
* **Filtering**: A low-pass filter is implemented to extract useful signals before the ADC stage.
* **Simulation**: The circuit was validated using LTSpice IV.

![LTSpice Simulation](Images/testbench.jpg)

---

## 3. Hardware Design (KiCad)
The PCB shield was designed following specific technical constraints to ensure compatibility with an Arduino UNO.

### Design Constraints:
* **Track Width**: 0.5 mm minimum.
* **Track Isolation**: 0.5 mm minimum.
* **Drill Sizes**: 1mm for headers/connectors; 0.8mm for passive components.

### Schematic & Routing
![Schematic](Images/schematic.png)
![PCB Layout](Images/pcb.png)

### 3D Model
![3D Model](Images/pcb_3d_front.png)

> ![3D Model](Images/pcb_3d_back.png)

---

## 4. Implementation & Software
* **Microcontroller**: Programmed for Arduino UNO / ESP32 platforms.
* **Connectivity**: Configured to send data over the The Things Network (TTN) via LoRa.
* **Version Control**: Developed collaboratively using Git and GitHub.

## 5. Repository Structure
* `/PCB_Capteur`: Schematic and Layout design files.
* `/Software`: Arduino/ESP32 source code for data acquisition.
* `/Spice`: Simulation files for the analog interface.
* `/Images`: Screenshots and documentation assets.

## 6. Authors & Credits
* **Student**: Tom Lassalle, Sandra Benjaoui, Louis Rousset
* **Supervisors**: J. Grisolia, A. Biganzoli, C. Crouzet, B. Mestre.
* **Partners**: AIME Toulouse (Atelier Interuniversitaire de Micro-nano Électronique).
