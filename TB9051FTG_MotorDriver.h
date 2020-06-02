/**
 * @file TB9051FTG_MotorDriver.h
 * @brief Class for controling a TB9051FTG Motor Driver
 * @author Michael Sidler
 */

/* 
 * This class is designed to work with a TB9051FTG breakout from Pololu
 *   https://www.pololu.com/product/2997
 * 
 * The wiring is as follows: 
 *   VM   = 
 *   GND  = MOTOR GROUND AND DIGITAL GROUND
 *   VCC  = 3.3/5V DIGITAL POWER
 *   OCC  = 
 *   EN   = pin_EN
 *   ENB  = TIED LOW WITH JUMPER
 *   PWM2 = pin_PWM1
 *   PWM1 = pin_PWM1
 *   OCM  = pin_FB
 *   DIAG = (*Diagnostic not implemented yet*)
 * 
 */

#pragma once

#include <Arduino.h>
#include "Motor.h"

class TB9051FTG_MotorDriver : public Motor{
    public:
        TB9051FTG_MotorDriver(uint32_t pin_EN, uint32_t pin_PWM1, uint32_t pin_PWM2, uint32_t pin_FB, float Vin, float deadzone);

        virtual void setVoltage(float voltage) final;
        virtual void enable() final;
        virtual void disable() final;
        virtual float readCurrent() final;
        virtual float getLastVoltage() final;

    private:
        const float MV_PER_A = 500.0f;
        float Vin;
        float deadzone;
        float lastVoltage;
        uint32_t pin_EN;
        uint32_t pin_PWM1;
        uint32_t pin_PWM2;
        uint32_t pin_FB;
        
};