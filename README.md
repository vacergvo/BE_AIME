# Smart Device Project: Nanoparticle Gas Sensor & IoT Shield
**UF "Smart Devices" – PTP Innovative Smart System (ISS)**

## 1. Project Overview
[cite_start]This project involves the design and realization of a smart device based on a custom-made tungsten trioxide ($WO_3$) nanoparticle gas sensor[cite: 17, 34]. [cite_start]The final objective is to combine this sensor with an electronic card to communicate data over a low-speed network using LoRa[cite: 17].

## 2. The Measurement Chain
### Nanoparticle Gas Sensor (AIME)
[cite_start]Developed during a training period at AIME, this sensor utilizes[cite: 3, 22]:
* [cite_start]**Synthesis**: Nanoparticles produced and deposited by dielectrophoresis[cite: 24].
* [cite_start]**Active Zone**: A sensitive layer of $WO_3$ nanoparticles integrated on aluminum interdigitated combs[cite: 57].
* [cite_start]**Target Gases**: High sensitivity to Ethanol and Ammonium[cite: 37].
* [cite_start]**Control**: Features an internal poly-silicon heating resistor and an aluminum temperature sensor[cite: 201].

### Analog Interface Circuit
[cite_start]The sensor is interfaced via a transimpedance circuit designed to measure its resistance[cite: 88, 179].
* [cite_start]**Amplification**: Utilizes an LTC1050 precision chopper amplifier[cite: 101].
* [cite_start]**Filtering**: A low-pass filter is implemented to extract useful signals before the ADC stage[cite: 89].
* [cite_start]**Simulation**: The circuit was validated using LTSpice IV[cite: 88].

> ![LTSpice Simulation](Images/testbench.jpg)

---

## 3. Hardware Design (KiCad)
[cite_start]The PCB shield was designed following specific technical constraints to ensure compatibility with an Arduino UNO[cite: 162].

### [cite_start]Design Constraints[cite: 128, 129, 131]:
* **Track Width**: 0.5 mm minimum.
* **Track Isolation**: 0.5 mm minimum.
* **Drill Sizes**: 1mm for headers/connectors; 0.8mm for passive components.

### Schematic & Routing
> ![Schematic](Images/schematic.png)

> ![PCB Layout](Images/pcb.png)

### 3D Model
> ![3D Model](Images/pcb_3d_front.png)

> ![3D Model](Images/pcb_3d_back.png)

---

## 4. Implementation & Software
* [cite_start]**Microcontroller**: Programmed for Arduino UNO / ESP32 platforms[cite: 136].
* [cite_start]**Connectivity**: Configured to send data over the The Things Network (TTN) via LoRa[cite: 161].
* [cite_start]**Version Control**: Developed collaboratively using Git and GitHub[cite: 104, 106].

## 5. Repository Structure
* `/PCB_Capteur`: Schematic and Layout design files.
* `/Software`: Arduino/ESP32 source code for data acquisition.
* `/Spice`: Simulation files for the analog interface.
* `/Images`: Screenshots and documentation assets.

## 6. Authors & Credits
* **Student**: Tom Lassalle, Sandra Benjaoui, Louis Rousset
* [cite_start]**Supervisors**: J. Grisolia, A. Biganzoli, C. Crouzet, B. Mestre[cite: 252, 253, 254].
* [cite_start]**Partners**: AIME Toulouse (Atelier Interuniversitaire de Micro-nano Électronique)[cite: 10, 25].
