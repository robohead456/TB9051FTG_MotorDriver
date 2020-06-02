/**
 * @file TB9051FTG_MotorDriver.h
 * @brief Class for controling a TB9051FTG Motor Driver
 * @author Michael Sidler
 */

#include "TB9051FTG_MotorDriver.h"

/**
 * @brief Constructor for TB9051FTG_MotorDriver controller
 * @param pin_EN Enable pin
 * @param pin_PWM1 Forward PWM pin
 * @param pin_PWM2 Reverse PWM pin
 * @param pin_FB Analog current feedback pin
 * @param Vin Motor supply voltage
 * @param deadzone Deadzone where voltage won't move motor
 */
TB9051FTG_MotorDriver::TB9051FTG_MotorDriver(uint32_t pin_EN, uint32_t pin_PWM1, uint32_t pin_PWM2, uint32_t pin_FB, float Vin, float deadzone) {
    this->pin_EN = pin_EN;
    this->pin_PWM1 = pin_PWM1;
    this->pin_PWM2 = pin_PWM2;
    this->pin_FB = pin_FB;
    this->Vin = Vin;
    this->deadzone = deadzone;

    pinMode(pin_EN, OUTPUT);
    pinMode(pin_PWM1, OUTPUT);
    pinMode(pin_PWM2, OUTPUT);

    this->lastVoltage = 0.0f;
    disable();

}

/**
 * @brief Sets voltage applied to motor
 * @param voltage Voltage to apply
 * 
 * Note: will enable motor if it is disabled
 */
void TB9051FTG_MotorDriver::setVoltage(float voltage) {

    lastVoltage = voltage;

    if(fabsf(voltage) <= deadzone) {
        analogWrite(pin_PWM1, 0);
        analogWrite(pin_PWM2, 0);
        return;
    }

    float dutyCycle = fabsf(voltage / this->Vin);

    if(dutyCycle > 1.0f) dutyCycle = 1.0f;
    if(dutyCycle < 0.0f) dutyCycle = 0.0f;

    if(voltage > 0.0f) {
        analogWrite(pin_PWM1, dutyCycle * 4095.0f);
        analogWrite(pin_PWM2, 0);
    }
    else {
        analogWrite(pin_PWM2, dutyCycle * 4095.0f);
        analogWrite(pin_PWM1, 0);
    }

    digitalWrite(pin_EN, HIGH);
}

/**
 * @brief Enable motor output
 */
void TB9051FTG_MotorDriver::enable() {
    setVoltage(lastVoltage);
    digitalWrite(pin_EN, HIGH);
}

/**
 * @brief Disable motor output
 */
void TB9051FTG_MotorDriver::disable() {
    digitalWrite(pin_EN, LOW);
    analogWrite(pin_PWM1, 0);
    analogWrite(pin_PWM2, 0);
}

/**
 * @brief Read current from the motor
 * @return current in Amps
 */
float TB9051FTG_MotorDriver::readCurrent() {
    return (analogRead(A1) / 4096.0f * 3300.0f / MV_PER_A);
}

/**
 * @brief Read last applied voltage to motor
 * @return last applied voltage
 */
float TB9051FTG_MotorDriver::getLastVoltage() {
    return lastVoltage;
}