This module can control a 12v signal on a time delay. Originally intended for the "horn scare" at Fresno Fright Nights. It takes an input (anywhere from 5v to 24v) to trigger the output.

The output turns on when triggered and stays on according to the potentiometer (knob) labeled on time.
After that it turns off for the duration based on the off time knob. It ignores further inputs during this time.
After the off time has elapsed, it resets itself.

The idea is that when someone walks close to a car we have placed as a prop, it honks the horn immediately, jump scaring them. If a group of several people walk past, you dont want the horn to keep going off for each person. They would have seen the first person get honked, and so would be expecting it. Further honks would just be annoying. So it ignores further triggers until the off time delay has been reached.

The gerber file is meant to be sent to board houses so they can make the board. The epro file is for easyedya.com, my preferred board editor. The c++ code is for arduino, and runs on the attiny85 chip the board uses.
