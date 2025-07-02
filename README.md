# Exponential Pump Control 

## Description

This project controls a INOFLUID pump using an exponential voltage curve over time.  
It runs on an **Industruino** and outputs a 0–10V signal via the Indio module to dynamically regulate the pump flow rate.

The system allows:
- **Start/reset control** via physical buttons (A and B)
- **Exponential ramp** over 1 minute (configurable)
- **Live voltage display** on a UC1701 LCD screen

Designed for experimental setups requiring precise and dynamic flow control.

## Hardware Requirements

- Industruino with Indio module  
- UC1701-compatible LCD display  
- INOFLUID pump (or compatible 0–10V-controlled device)  
- Two push buttons (Start and Reset)  

## How It Works

- Press **Start** (Button A): Begins an exponential voltage increase from 0 to 10V over 1 minute.
- Press **Reset** (Button B): Resets the voltage output to 0V.
- The voltage is updated every 100 ms and displayed in real-time.

## License

This project is licensed under the MIT License.  
See the code comments for full license terms.

![](graph.png)
