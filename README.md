# STM32 Wireless RC Car 🚗📡  

A remote-controlled car powered by the **STM32 Nucleo microcontroller** and **NRF24L01 wireless transceiver**, designed for **real-time motor control** and low-latency wireless communication.  

This project combines embedded C firmware, wireless SPI communication, and H-bridge motor driving to create a fast, reliable RC system.  

---

## 🎮 System Overview  
- **Transmitter**: Joystick module connected to an STM32 board sends directional commands wirelessly via NRF24L01.  
- **Receiver**: STM32-based car interprets commands and drives DC motors using H-bridge motor drivers.  
- **Control**: Proportional joystick input → real-time motor speed & direction control.  
- **Wireless**: NRF24L01 transceiver with SPI communication for low-latency updates.  

---

## 🧠 Key Features  
- 🔁 Real-time bidirectional communication between transmitter & car  
- ⚡ PWM motor control for precise speed/direction management  
- 📡 NRF24L01 wireless module with SPI at 2.4 GHz  
- 🔋 Battery-powered car chassis with dual DC motors  
- 🛠️ Robust embedded C firmware on STM32 (HAL drivers, interrupts, GPIO)  
- 🔌 Modular hardware design for easy debugging and upgrades  

---

## 🔧 Hardware Components  

### Transmitter  
| Component        | Purpose |
|------------------|---------|
| STM32 Nucleo Board | Reads joystick values and sends commands |
| Joystick Module   | User input (X/Y axes → direction & speed) |
| NRF24L01 Module   | Wireless transmitter |

### Receiver (Car)  
| Component        | Purpose |
|------------------|---------|
| STM32 Nucleo Board | Processes wireless commands |
| NRF24L01 Module   | Wireless receiver |
| H-Bridge Driver (L298N / TB6612FNG) | Drives left/right DC motors |
| DC Motors + Wheels | Car propulsion & steering |
| LiPo / Battery Pack | Power supply |

---

## 📜 Pin Mapping (Example)  

### Transmitter  
| Signal       | STM32 Pin |
|--------------|-----------|
| Joystick X   | PA0 (ADC) |
| Joystick Y   | PA1 (ADC) |
| NRF24L01 CE  | PB0 |
| NRF24L01 CSN | PB1 |
| NRF24L01 SCK | PA5 |
| NRF24L01 MOSI| PA7 |
| NRF24L01 MISO| PA6 |

### Receiver  
| Signal          | STM32 Pin |
|-----------------|-----------|
| NRF24L01 CE     | PB0 |
| NRF24L01 CSN    | PB1 |
| Motor Driver IN1| PA8 |
| Motor Driver IN2| PA9 |
| Motor Driver IN3| PA10 |
| Motor Driver IN4| PA11 |
| PWM (Left Motor)| PB6 (TIM4_CH1) |
| PWM (Right Motor)| PB7 (TIM4_CH2) |

*(Adjust pin mapping depending on your STM32 board.)*  

---

## 🧩 Code Structure  

| File           | Description |
|----------------|-------------|
| `main.c`       | Main control loop for car or transmitter |
| `nrf24.c/h`    | NRF24L01 driver (SPI communication functions) |
| `motor.c/h`    | Motor driver functions using PWM & GPIO |
| `joystick.c/h` | Reads ADC joystick inputs on transmitter |
| `system_stm32.c` | HAL/system configuration |

---

## 🚀 Setup & Usage  

1. **Transmitter**  
   - Connect joystick module to STM32 ADC pins.  
   - Flash transmitter firmware.  
   - Power with USB or battery pack.  

2. **Receiver (Car)**  
   - Connect STM32 to NRF24L01 and motor driver.  
   - Flash receiver firmware.  
   - Power with LiPo or 3.3–5V supply (depending on motor driver).  

3. **Play!**  
   - Push joystick forward/back to control speed.  
   - Move joystick left/right to steer.  
   - Wireless communication handles control updates in real time.  

---

## 🧪 Testing Modes  
- **Motor Test**: Drive motors at fixed PWM speeds.  
- **Wireless Test**: Send/receive test packets between boards.  
- **Full Control**: Joystick → wireless → car motion.  

---

## 📹 Demo Video (Optional)  
*(Add a link or GIF of your RC car in action here!)*  

---

## 🚀 Future Improvements  
- Add **ultrasonic sensor** for obstacle avoidance.  
- Implement **closed-loop speed control** with encoders.  
- Upgrade to **Wi-Fi or Bluetooth LE** for extended range.  
- Create a **mobile app controller** (UART/Wi-Fi).  

---

## 📄 License  
MIT License — free to use and adapt for your own embedded projects.  

---

## 👤 Author  
Created by **Neil Agarwal**  
ECE Embedded Systems Track @ UT Austin  

---

> This project demonstrates how **embedded systems + wireless communication + hardware control** can bring real-time robotics to life.  
