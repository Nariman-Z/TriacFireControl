# TriacFireControl
A microcontroller-based TRIAC firing angle control system with zero-crossing detection and voltage monitoring for precise power regulation.

<!--horizontal divider(gradiant)-->
<img src="https://user-images.githubusercontent.com/73097560/115834477-dbab4500-a447-11eb-908a-139a6edaec5c.gif">

<!--Repo Banner-->
<img height=350 alt="Repo Banner - TRIAC Firing Angle Control" src="https://capsule-render.vercel.app/api?type=waving&color=0:6E9EAB,100:23395B&height=300&section=header&text=TRIAC%20Firing%20Angle%20Control&fontSize=50&fontColor=ffffff&animation=fadeIn&fontAlignY=38&desc=Precise%20Control%20of%20AC%20Voltage&descAlignY=60&descAlign=50"></img>

<!--Title-->
<p align="center">
  <b>TRIAC Firing Angle Control</b>
  <br> <small> <i>- A precise TRIAC-based AC voltage control system using zero-cross detection and real-time monitoring -</i> </small> <br>
</p>  

---

<!--Body-->
## **Introduction**

This project focuses on developing a microcontroller-based system for **TRIAC firing angle control** to regulate AC voltage.  
Using real-time zero-crossing detection and calculated delay control, this system adjusts the firing angle to maintain precise control over the output voltage.  
Designed with an intuitive LCD interface and adaptive voltage regulation, this project serves as a robust tool for applications like dimming, power regulation, and heating control.


## **Hardware Overview**

The hardware implementation includes:  
- **Microcontroller (ESP32 or Arduino)**: Central to processing zero-crossing signals, calculating firing delays, and managing the TRIAC trigger mechanism.  
- **Zero-Cross Detection Circuit (H11AA1 or 4N25)**: Converts AC signals to a clean digital pulse to precisely determine zero-crossing points.
- **TRIAC and Optocoupler (MOC3021)**: Ensures safe and isolated control of the high-voltage AC circuit.  
- **Voltage Sensor (ZMPT101B)**: Continuously monitors the AC voltage for adaptive control.    
- **LCD Display (I2C, 16x2)**: Provides real-time information on frequency, firing angle, and voltage.  


## **Software Overview**

The software, written in C++, integrates the following key features:  
1. **Frequency Measurement**: Accurately measures the frequency of the AC input using interrupt-driven zero-cross detection.  
2. **Firing Angle Calculation**: Dynamically adjusts the firing angle based on measured voltage, frequency, and user-defined parameters.  
3. **Triac Trigger Generation**: Precisely generates firing pulses with calculated delays for optimal AC power regulation.
4. **Adaptive Voltage Control**: Monitors real-time voltage using ZMPT101B and recalibrates firing angle to maintain the desired output.  
5. **LCD Display**: Continuously updates and displays critical data, including voltage, frequency, and firing delay.

- **for the [ZMPT101B.h](https://github.com/Abdurraziq/ZMPT101B-arduino) library please refer to this link.**


## **Project Goals**

- **Precise Voltage Control**: Develop a reliable system for regulating AC voltage using TRIAC firing angle control.  
- **Dynamic Frequency Adaptation**: Ensure compatibility with 50 Hz and 60 Hz AC mains frequencies.  
- **Embedded System Design**: Implement efficient interrupt-driven software for real-time voltage and frequency monitoring.  
- **Interactive Display**: Provide real-time feedback through an intuitive LCD interface.  
- **Safe High-Voltage Operation**: Incorporate optocouplers and isolation circuits for user and system safety.  


## **Conclusion**

This project combines robust hardware with efficient software to deliver a precise and adaptive TRIAC-based voltage control system.  
It offers a comprehensive learning experience for microcontroller programming, high-voltage control, and real-time monitoring.  
With applications spanning from home automation to industrial power regulation, this system provides a versatile platform for further enhancements.


## **License**

This project is licensed under the MIT License - see the [LICENSE.md](https://github.com/Nariman-Z/TriacFireControl/blob/main/LICENSE) file for details.

---

<!--Footer-->
### Made with ♥️ by: [Nariman_Z](https://github.com/Nariman-Z) ###
See also: [My Website](https://nariman-z.github.io/)

<!--horizontal divider(gradiant)-->
<img src="https://user-images.githubusercontent.com/73097560/115834477-dbab4500-a447-11eb-908a-139a6edaec5c.gif">

<div>
  <p> Last Edited on: November 23, 2024 </p>
  <!--profile visit count-->
    <a href="https://visitcount.itsvg.in">
    <img src="https://visitcount.itsvg.in/api?id=Nariman-Z&label=Total%20Profile%20Views&color=6E9EAB&icon=8&pretty=true" />
  </a>
</div>
