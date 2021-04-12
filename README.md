# 387_NM_Final
My Embedded System Project for ECE 387

PROJECT OUTLINE:
A "secure" storage box, using a number of security measures to be outlined below.
The absurdity of these measures will hopefully give off an over-the-top toy-like feel.

MAIN GOAL:
Create a box roughly large enough to store a phone. Due to the space required by the components, it may be larger. This box features a plethora of security measures.
Namely, it will have a servo or stepper motor (haven't decided which, but most likely servo.) holding the lid shut, only unlocked by a button pattern password.
It will also use some tamper proofing, such as:
- A tilt switch to disable the password system when the box is tilted.
  
- A vibration sensor to detect if the box is being rattled.
- Depth sensor to know if the box is submerged. 
  - what angle to place it at?
- A piezo to beep if the pattern is incorrect.
- Ultrasonic sensor to detect you approaching the box.
These measures are guaranteed. Stretch goals will add additional sensors.

This isn't a main goal, but this will likely be battery powered, due to the power demand of all the sensors.

STRETCH GOALS:

- Joystick to control the motor once the pattern is input correctly.
- Seven Segment display panel to "talk" to the user.
- Additional piezo uses, such as when any of the other safety measures are triggered
- Update the tilt switch to use interrupts to stop the system even mid-pattern.
These mainly depend on time and remaining pins after the main features are implemented.


