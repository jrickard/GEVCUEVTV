RECENT CHANGES TO GEVCU EVTV RELEASE

I've made a few changes to the EVTV official release version of the GEVCU.

1. Thanks to Paulo Almeida, we now have the cooling temperatures and outputs portion of the CONFIGURATION tab on the wireless website now working properly.  Items added:

PRECHARGE DELAY  - numeric value in milliseconds after startup when the main contactor output is switched on and the precharge relay output is switched off.

PRECHARGE RELAY - output 0 to 7 to be used to switch a precharge relay

MAIN CONTACTOR - output 0 to 7 to be used to switch main contactor relay

COOLING FAN - output 0 to 7 to be used to switch on fan on heat exchanger normally but any cooling

COOLING ON.  Reported inverter temperature in centigrade where the cooling fan output is to be turned on.

COOLING OFF  Reported inverter temperature in centigrade where cooling fan output is to be turned off.  Normally you would set this to some value below the cooling on temperature to avoid hysteresis switching or hunting about the temperature.

Note that DMOC645 undergoes a pretty serious and obvious current limit at 80C inverter temperature.

BATTERY VOLTAGE:  This is the fully charged static voltage of the battery pack.  Actually pick an integer voltage slightly BELOW the fully charged voltage of the pack - like by a volt.

Anytime the system measures a DC pack voltage HIGHER than this value, it will automatically reset a new kiloWatthour meter on the dashboard to zero.  This kwh value is retained with system starts and stops and continuosly accrues energy usage based on reported pack voltage and current.  The only way to reset it to zero is to charge the pack up above this entered voltage.

ANNUNCIATORS

Not sure what was going on here. We had a LOT of annunciators, some making some sense and others none.  But none were actually active.  I've reduced this to the following set and made them functional.

PRECHARGE RELAY - lights when precharge output is set.
MAIN CONTACTOR - lights when main contactor output is set.
READY - as reported by motorController parent object
RUNNING - as reported by motorController parent object
INVERTER OVERTEMP - lit when temperature reported by motorController parent object exceeds the COOLING ON value set in the configuration
OUT0 through OUT7 - lit when the respective output is set to on.

DASHBOARD
Again, this was in some disarray.  Most notably we had two dials for AC voltage and current.  Currently the dmoc645motorcontroller doesn't actually calculate the Direct and Quadrature voltages and currents so these dials had no input.

I rearranged the dials and converted the function of a couple of them.

THROTTLE - 0 to 100% indicates current read throttle position.

TORQUE -100 to 400 indicates current reported ACTUAL torque value from the motorController parent object.  We set this to 0.1 in configuration so it will read 0 on startup.

CURRENT - reported DC current 0 to 400 amps.  On reflection, I should probably revise this to show negative regenerative values.

RPM - 0 to 10 in thousands of rpm.

MOTOR TEMP - currently the greater of stator and rotor temperature as reported by motorController parent object. 0 to 250 centigrade.

INVERTER TEMP inverter temperature 0-120 centigrade with green as 0-70, yellow 70-80 and red over 80C.  

DC VOLTAGE 0 - 450 vdc pack voltage

KILOWATT HOURS - 0 to 30 kWh.  This one is a little complicated.  I've stollen nominalVolts use it for the fully charged voltage of the pack.  This dial is actually quite useful but ultimately destined to fail in its role.  It only works while the GEVCU is on.  I am going to store the value.  Rather than have a reset button, I'm going to automatically reset this variable to zero anytime the following applies:

1. Reported dc pack voltage EXCEEDS the value in nominalVolt AND the reported torqueActual is greater than zero.  

The theory here is if you start the vehicle and the voltage of the pack is above the value set usign the NOMV label in the serial port, we will assume the pack is fully charged and hasn't been used yet and reset the kilowatt hour counter to zero.

The exception is on negative reported torque values under the theory that we COULD momentarily spike the pack voltage during an early and strong regenerative braking event.  These will simply be ignored.

In my experience, the fully charged value, typically 3.32 to 3.34 volts on LiFEPo4 packs will dip below 3.3 volts before actually getting out of teh driveway.  It dives pretty quickly down to 3.25 and then stabilizes there moving onto the flat part of the discharge curve.  SO if you have a pack of 100 cells, it will most likely be 334 volts a few hours after charging and it may indeed be higher immediately after charging.  But in either case, it will be down to 330volts or so within the first few hundred yards. As the voltage settles below CHARGED level, the kWh meter will start to tally.

So you could probably set this effectively at 331 volts or 332 volts and it would work very well.

I intend to save the value to EEPROM and retrieve it on startup so you will actually have an accurate fuel gage allowing for multiple starts and stops of the system.  But it won't reset on a partial charge. And it won't monitor charging at all.  So it rather fails as a fully functional fuel gage.  But it's something.  If you fully charge your pack and then go drive, it will track your kilowatt hour useage fairly accurately. And the reset on a full charge is quite automatic.

POWER in kilowatts 0-150.  Simple kva multiplication of reported DC pack voltage and current and instantaneous.


NEWUSERS SOFTWARE UPGRADE PROCEDURE.

Actually there is no easy way to upgrade.  Arduino doesn't really have a binary loader.

1. Install Arduino Due 1.5.6.r2 on your machine. Make sure you have the following libraries installed:

due_can
due_rtc
due_wire
DueTimer
SPI
Wire

2. Connect cable to GEVCU USB port.

3. Open the attached GEVCU402 file in the GEVCU402 directory with Arduino.

4. On Arduino TOOLS menu under BOARD select the Arduino Due (native USB port)

5. On Arduino TOOLS menu under PORT select the serial port where GEVCU is connected.

6. On the upper left blue bar in the Arduino app, click on the compile and load button (right arrow)

7. Wait for it to finish compiling and uploading.

8.  On your laptop wireless, scan for access points and locate GEVCU.  Connect to GEVCU.

9.  In your browser, enter http://192.168.3.10/iChip

10. In the iChip configuration menu, click on UPLOAD FILES.  This is the bottom entry on the list on the left.

11. You will be prompted for a password.  Enter "secret" in the box.

12. The top most item in the list has a BROWSE button to select a file.  Click BROWSE and navigate to select /gevcu402/website/website.img

13. Click on SUBMIT once and then wait. After about five seconds, the file name should disappear.
The web page is now successfully loaded.

14. In your browser, go to http://192.168.3.10 to view the new web page for the upgraded GEVCU.

It should indicate version 4.02.



 


