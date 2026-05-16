# 🔧 Troubleshooting Guide
## Line Follower Robot Using IR Sensors

---

## 📋 Table of Contents

1. [Robot Doesn't Move](#1-robot-doesnt-move)
2. [Robot Moves But Doesn't Follow the Line](#2-robot-moves-but-doesnt-follow-the-line)
3. [IR Sensor Issues](#3-ir-sensor-issues)
4. [Motor & Motor Driver Issues](#4-motor--motor-driver-issues)
5. [Turning Issues](#5-turning-issues)
6. [Power & Battery Issues](#6-power--battery-issues)
7. [Arduino Upload Issues](#7-arduino-upload-issues)
8. [General Tuning Tips](#8-general-tuning-tips)

---

## 1. Robot Doesn't Move

### ❌ Robot powered ON but wheels don't spin
**Fix:**
- Check that ENA and ENB pins are receiving PWM signal — without enable pins HIGH, L298N won't drive motors
- Verify `speedMotor` is not 0 — open Serial Monitor to confirm code is running
- Make sure battery voltage is sufficient (two 3.7V cells in series = 7.4V recommended for L298N)
- Check power switch is properly toggled ON

---

### ❌ Only one motor works
**Cause:** One motor channel on L298N may be faulty or wired incorrectly.
**Fix:**
- Swap motor connections to test if the issue follows the motor or the channel
- Check IN1/IN2 vs IN3/IN4 wiring — both pairs must be correct
- Confirm ENA and ENB are both getting PWM signals

---

## 2. Robot Moves But Doesn't Follow the Line

### ❌ Robot moves in random directions
**Cause:** Sensors reading inverted values or wired to wrong pins.
**Fix:**
- Open Serial Monitor (9600 baud) and place robot on the line — center sensor (S3/A2) should read LOW
- If all sensors read opposite of expected, your sensor module may have inverted output — swap all conditions (0→1, 1→0) in the code
- Confirm sensor pin assignments: S1=A0, S2=A1, S3=A2, S4=A3, S5=A4

---

### ❌ Robot keeps going straight and ignores curves
**Cause:** Speed too high for sharp turns, or sensor response too slow.
**Fix:**
- Reduce `speedMotor` value (try 70–90 instead of 100)
- Increase speed difference between left and right motors during turns:
  ```cpp
  void slightLeft() {
    analogWrite(ENA, speedMotor / 3);  // Reduce further
    analogWrite(ENB, speedMotor);
  }
  ```

---

### ❌ Robot oscillates/wobbles on straight line
**Cause:** Speed too high or sensor sensitivity too low.
**Fix:**
- Reduce `speedMotor` to around 80
- Check sensor height above surface — optimal range is **3–5 mm**
- Widen the gap between slightLeft/slightRight thresholds

---

## 3. IR Sensor Issues

### ❌ Sensor always reads HIGH (no line detected ever)
**Cause:** Sensor too far from surface, or ambient light interference.
**Fix:**
- Lower sensor array to 3–5 mm from the surface
- Test indoors — strong sunlight or fluorescent lighting can saturate IR receivers
- Adjust the onboard potentiometer on the TCRT5000 module to set sensitivity threshold

---

### ❌ Sensor always reads LOW (line detected everywhere)
**Cause:** Sensor too close to surface or potentiometer over-tuned.
**Fix:**
- Raise sensor slightly — 5–8 mm may work better on glossy surfaces
- Turn the sensitivity potentiometer on the module counterclockwise to reduce sensitivity

---

### ❌ Only some sensors respond correctly
**Cause:** Individual sensor damaged or pin not connected.
**Fix:**
- Test each sensor pin individually using Serial Monitor:
  ```cpp
  Serial.println(digitalRead(A0));  // Test S1 in isolation
  ```
- Replace module if a specific sensor position is consistently unresponsive

---

### ❌ Line detection works on paper but not on floor
**Cause:** Surface reflectivity varies — shiny tiles reflect IR differently.
**Fix:**
- Use matte black tape on white cardboard for best contrast
- Adjust sensitivity potentiometer to match your surface
- Avoid glossy or semi-transparent surfaces

---

## 4. Motor & Motor Driver Issues

### ❌ L298N gets very hot
**Cause:** Overcurrent or motors stalled.
**Fix:**
- Add a heatsink to the L298N chip if not present
- Check that wheels spin freely without mechanical obstruction
- Reduce motor speed via `speedMotor`

---

### ❌ Motors spin backwards from expected direction
**Cause:** Motor wires connected with reversed polarity.
**Fix:**
- Swap the two wires of the affected motor at the L298N output terminal
- OR swap IN1/IN2 or IN3/IN4 logic in the code:
  ```cpp
  // Original:
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  // Reversed:
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  ```

---

### ❌ PWM speed control not working
**Cause:** Using a non-PWM pin for ENA/ENB.
**Fix:**
- Arduino Nano PWM pins are: **D3, D5, D6, D9, D10, D11**
- ENA must be on D10 and ENB on D5 — both are PWM capable ✓
- Confirm with `analogWrite()` not `digitalWrite()` for speed pins

---

## 5. Turning Issues

### ❌ Sharp turns not executing — robot just stops
**Cause:** Sensor condition for sharp turns never being triggered.
**Fix:**
- Increase track curve sharpness or slow down before the curve
- Add a `delay(50)` after sharp turn functions to let the robot complete the rotation:
  ```cpp
  void sharpLeft() {
    // ...motor code...
    delay(50);
  }
  ```

---

### ❌ Slight turns feel like sharp turns (too aggressive)
**Fix:**
- Further reduce the slower motor speed:
  ```cpp
  analogWrite(ENA, speedMotor / 3);  // Was /2, now /3
  ```
- Reduce overall `speedMotor` so turns are gentler

---

## 6. Power & Battery Issues

### ❌ Robot shuts off during sharp turns
**Cause:** Motors draw peak current during direction reversals, causing voltage drop.
**Fix:**
- Add a **100µF–470µF capacitor** across the motor power supply rails
- Ensure battery cells are fully charged (each cell should be ~3.7–4.2V)
- Use quality 18650 cells rated for at least 2A continuous discharge

---

### ❌ Arduino resets when motors start
**Cause:** Motor current spike drops supply voltage below Arduino's operating range.
**Fix:**
- Power Arduino separately from the battery's 5V output of L298N — don't use Arduino's Vin for motors
- Ensure L298N's 5V onboard regulator (if enabled) is providing stable 5V to Arduino

---

## 7. Arduino Upload Issues

### ❌ "Programmer not found" / COM port error
**Fix:**
- Select **Tools → Board → Arduino Nano**
- Try **Processor → ATmega328P (Old Bootloader)** if normal option fails
- Use a different USB cable (must be data cable, not charge-only)

---

### ❌ Code uploads but Serial Monitor shows nothing
**Fix:**
- Set baud rate to **9600** in Serial Monitor dropdown
- Press Arduino's **Reset button** after opening Serial Monitor
- Confirm `Serial.begin(9600)` is in `setup()`

---

## 8. General Tuning Tips

| Tip | Details |
|-----|---------|
| 🎚️ Start slow | Begin with `speedMotor = 80` and increase gradually |
| 📏 Sensor height | Keep IR sensors 3–5 mm above the surface |
| 🔆 Control lighting | Avoid testing under direct sunlight — use indoor diffused light |
| 🖊️ Line width | Black line should be 20–25 mm wide for optimal 5-sensor response |
| 🔋 Full battery | Always start with fully charged cells for consistent motor performance |
| 📋 Serial Monitor | Use it to debug sensor readings before placing robot on track |
| 🔄 Calibrate sensors | Adjust sensitivity potentiometers while robot is on the actual track |
| 🏁 Test track | Use matte black tape on white poster board for best contrast |

---

## 📬 Still Having Issues?

- [Arduino Nano Documentation](https://docs.arduino.cc/hardware/nano)
- [L298N Motor Driver Guide](https://lastminuteengineers.com/l298n-dc-stepper-driver-arduino-tutorial/)
- [TCRT5000 IR Sensor Guide](https://components101.com/sensors/tcrt5000-ir-sensor-module)

---

*Troubleshooting Guide — Line Follower Robot*
*Authors: Muhammad Mamoon, Ali Ahmar Awan, Asad Ali*
*Course: Robotics Design Lab - 1 — UCP Spring 2025*
