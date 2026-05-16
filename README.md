# 🤖 Line Follower Robot Using IR Sensors

An autonomous line-following robot designed and implemented. The robot uses a 5-channel TCRT5000 IR sensor array, an Arduino Nano microcontroller, and an L298N motor driver to detect and follow a black line on a white surface in real time.

---

## 🧠 How It Works

```
[5-Channel TCRT5000 IR Sensor Array]
               │
               ▼
        [Arduino Nano]
         (Decision Logic)
               │
               ▼
     [L298N Motor Driver]
        │            │
        ▼            ▼
  [Left N20     [Right N20
   DC Motor]     DC Motor]
        │            │
        ▼            ▼
   [Left Wheel]  [Right Wheel]
```

The IR sensors emit infrared light toward the surface:
- **Black surface** → absorbs IR → sensor reads **LOW (line detected)**
- **White surface** → reflects IR → sensor reads **HIGH (no line)**

Arduino reads all 5 sensor values every loop cycle and decides the movement command.

---

## 🌐 Sensor Logic & Movement Decisions

| Sensor State (S1–S5) | Action |
|----------------------|--------|
| S2=LOW, S3=HIGH, S4=LOW | ➡️ **Forward** — line centered |
| S1=LOW, S2=HIGH, S3=HIGH | ↙️ **Slight Left** — line drifting left |
| S3=HIGH, S4=HIGH, S5=LOW | ↘️ **Slight Right** — line drifting right |
| S1=HIGH, S2=HIGH | ⬅️ **Sharp Left** — line far left |
| S4=HIGH, S5=HIGH | ➡️ **Sharp Right** — line far right |
| All sensors LOW | 🛑 **Stop** — line lost |
| Default | ➡️ **Forward** — fallback action |

> **Note:** LOW = black line detected, HIGH = white surface

---

## 🧰 Components

| Component | Qty | Purpose |
|-----------|-----|---------|
| Arduino Nano | 1 | Main microcontroller — brain of the robot |
| TCRT5000 IR Sensor Array (5-Channel) | 1 | Line detection |
| L298N Motor Driver Module | 1 | Motor speed & direction control |
| N20 DC Gear Motor | 2 | Drive wheels |
| Lithium Rechargeable Cell 3.7V | 2 | Power supply |
| Power Switch | 1 | ON/OFF control |
| Rubber Wheels | 2 | Movement |
| Caster Wheel | 1 | Balance/support |
| Custom Chassis (SolidWorks designed) | 1 | Structural frame |
| Jumper Wires | Multiple | Connections |

---

## 📐 Pin Mapping

### Motor Driver (L298N) → Arduino Nano

| L298N Pin | Arduino Pin | Function |
|-----------|-------------|----------|
| IN1 | D9 | Left motor direction |
| IN2 | D8 | Left motor direction |
| IN3 | D7 | Right motor direction |
| IN4 | D6 | Right motor direction |
| ENA | D10 (PWM) | Left motor speed |
| ENB | D5 (PWM) | Right motor speed |

### IR Sensors → Arduino Nano

| Sensor | Arduino Pin | Position |
|--------|-------------|----------|
| S1 | A0 | Far Left |
| S2 | A1 | Center Left |
| S3 | A2 | Center |
| S4 | A3 | Center Right |
| S5 | A4 | Far Right |

---

## 💻 Source Code

The full Arduino sketch is in `/src/line_follower.ino`.

### Movement Functions Summary

| Function | Left Motor | Right Motor | When Used |
|----------|-----------|------------|-----------|
| `forward()` | Forward (full) | Forward (full) | Line centered |
| `slightLeft()` | Reverse (half) | Forward (full) | Line drifts left |
| `slightRight()` | Forward (full) | Reverse (half) | Line drifts right |
| `sharpLeft()` | Reverse (full) | Forward (full) | Line far left |
| `sharpRight()` | Forward (full) | Reverse (full) | Line far right |
| `stopMotors()` | Stop | Stop | Line lost |

---

## 📁 Repository Structure

```
line-follower-robot/
│
├── src/
│   └── line_follower.ino          ← Arduino source code
│
├── hardware/
│   ├── chassis-design/            ← SolidWorks chassis CAD design
│   ├── wiring-diagram/            ← Circuit wiring diagram
│   └── robot-photos/              ← Real robot photos
│
├── docs/
│   └── RDL_Project_Report_Line_Follower.pdf
│
├── README.md
├── TROUBLESHOOTING.md
└── LICENSE
└── .gitignore
```

---

## 🚀 Getting Started

1. **Assemble the hardware** as per the wiring diagram in `hardware/wiring-diagram/`
2. **Open** `src/line_follower.ino` in Arduino IDE
3. **Select Board:** Arduino Nano, **Processor:** ATmega328P (Old Bootloader) if needed
4. **Connect** Arduino via USB and upload the code
5. **Power** the robot via the battery pack through the power switch
6. **Place** on a track with a black line on white surface and switch ON

### Tuning Tips
- Adjust `speedMotor` value (0–255) to match your surface and motor specs
- Increase value for faster response; decrease for smoother turns
- Sensor height above ground should be 3–5 mm for optimal reading

---

## 🔗 Applications

- Industrial warehouse automation (AGVs)
- Hospital service robots
- Educational robotics platforms
- Autonomous delivery systems
- Smart factory assembly lines

---

## 📄 License

Licensed under **Creative Commons Attribution 4.0 International (CC BY 4.0)**.

See the [LICENSE](LICENSE) file for details.

---

## 👤 Authors

Muhammad Mamoon
Robotics Engineering Student

## 🙏 Acknowledgements

- Chassis designed using **SolidWorks**
