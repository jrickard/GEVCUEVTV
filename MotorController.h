/*
 * MotorController.h
  *
 * Parent class for all motor controllers.
 *
 Copyright (c) 2013 Collin Kidder, Michael Neuweiler, Charles Galpin

 Permission is hereby granted, free of charge, to any person obtaining
 a copy of this software and associated documentation files (the
 "Software"), to deal in the Software without restriction, including
 without limitation the rights to use, copy, modify, merge, publish,
 distribute, sublicense, and/or sell copies of the Software, and to
 permit persons to whom the Software is furnished to do so, subject to
 the following conditions:

 The above copyright notice and this permission notice shall be included
 in all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

 */

#ifndef MOTORCTRL_H_
#define MOTORCTRL_H_

#include <Arduino.h>
#include "config.h"
#include "Device.h"
#include "Throttle.h"
#include "DeviceManager.h"
#include "sys_io.h"
#include "EEPROMAnything.h"




#define MOTORCTL_INPUT_DRIVE_EN    3
#define MOTORCTL_INPUT_FORWARD     4
#define MOTORCTL_INPUT_REVERSE     5
#define MOTORCTL_INPUT_LIMP        6

class MotorControllerConfiguration : public DeviceConfiguration {
public:
	uint16_t speedMax; // in rpm
	uint16_t torqueMax;	// maximum torque in 0.1 Nm
	uint16_t torqueSlewRate; // for torque mode only: slew rate of torque value, 0=disabled, in 0.1Nm/sec
	uint16_t speedSlewRate; //  for speed mode only: slew rate of speed value, 0=disabled, in rpm/sec
	uint16_t reversePercent;

	uint16_t kilowattHrs; //capacitance of motor controller input in uf
	uint16_t prechargeR; //resistance of precharge resistor in tenths of ohm
	uint16_t nominalVolt; //nominal pack voltage in tenths of a volt
	uint8_t prechargeRelay; //# of output to use for this relay or 255 if there is no relay
	uint8_t mainContactorRelay; //# of output to use for this relay or 255 if there isno relay
        uint8_t coolFan; //# of output to use external cooling fan
        uint8_t coolOn; // Temperature at which external cooling is switched on
        uint8_t coolOff; //Temperature at which exterinal cooling is switched off

};

class MotorController: public Device {

public:
    enum GearSwitch {
        GS_NEUTRAL,
        GS_FORWARD,
        GS_REVERSE,
        GS_FAULT
    };

	enum PowerMode {
		modeTorque,
		modeSpeed
	};

    MotorController();
	DeviceType getType();
    void setup();
    void handleTick();
	uint32_t getTickInterval();

	void loadConfiguration();
	void saveConfiguration();

	void coolingcheck();
        void setStatusBits();
	bool isReady();
	bool isRunning();
	bool isFaulted();
	bool isWarning();

	void setPowerMode(PowerMode mode);
	PowerMode getPowerMode();
	int16_t getThrottle();
        int8_t getCoolFan();
        int8_t getCoolOn();
        int8_t getCoolOff();
        int16_t getselectedGear();
         int16_t getprechargeR();
         int16_t getnominalVolt();
      
        int8_t getprechargeRelay();
        int8_t getmainContactorRelay();
        
      	int16_t getSpeedRequested();
	int16_t getSpeedActual();
	int16_t getTorqueRequested();
	int16_t getTorqueActual();
	int16_t getTorqueAvailable();

	uint16_t getDcVoltage();
	int16_t getDcCurrent();
	uint32_t getkiloWattHours();
	int16_t getMechanicalPower();
	int16_t getTemperatureMotor();
	int16_t getTemperatureInverter();
	int16_t getTemperatureSystem();

	uint32_t getStatusBitfield1();
	uint32_t getStatusBitfield2();
	uint32_t getStatusBitfield3();
	uint32_t getStatusBitfield4();
        uint32_t statusBitfield1; // bitfield variable for use of the specific implementation
	uint32_t statusBitfield2;
	uint32_t statusBitfield3;
	uint32_t statusBitfield4;
        uint32_t efficiency;
	GearSwitch getGearSwitch();
enum Gears {
		NEUTRAL = 0,
		DRIVE = 1,
		REVERSE = 2,
		ERROR = 3
	};
Gears selectedGear;
	

protected:
	bool ready; // indicates if the controller is ready to enable the power stage
	bool running; // indicates if the power stage of the inverter is operative
	bool faulted; // indicates a error condition is present in the controller
	bool warning; // indicates a warning condition is present in the controller
	bool coolflag;

	PowerMode powerMode;
	int16_t throttleRequested; // -1000 to 1000 (per mille of throttle level)
	int16_t speedRequested; // in rpm
	int16_t speedActual; // in rpm
	int16_t torqueRequested; // in 0.1 Nm
	int16_t torqueActual; // in 0.1 Nm
	int16_t torqueAvailable; // the maximum available torque in 0.1Nm

    GearSwitch gearSwitch;

	uint16_t dcVoltage; // DC voltage in 0.1 Volts
	int16_t dcCurrent; // DC current in 0.1 Amps
	uint32_t kiloWattHours; // AC current in 0.1 Amps
	int16_t mechanicalPower; // mechanical power of the motor 0.1 kW
	int16_t temperatureMotor; // temperature of motor in 0.1 degree C
	int16_t temperatureInverter; // temperature of inverter power stage in 0.1 degree C
	int16_t temperatureSystem; // temperature of controller in 0.1 degree C

	
        uint16_t nominalVolts; //nominal pack voltage in tenths of a volt


	uint16_t prechargeTime; //time in ms that precharge should last
	uint32_t milliStamp; //how long we have precharged so far
	
        bool donePrecharge; //already completed the precharge cycle?
        bool prelay; //already completed the precharge cycle?
	uint32_t skipcounter;
};

#endif
