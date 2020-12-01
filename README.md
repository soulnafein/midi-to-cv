** Eurorack USB MIDI to CV converter **
Use your cheap USB MIDI keyboard to control your fancy analogue synth
modules.

![Panel and PCB](https://github.com/soulnafein/midi-to-cv/blob/main/midi-to-cv-1.jpg?raw=true)

It uses a PIC24 as a MIDI host. It can work in mono mode where all the 3
CV outputs are represent the last note pressed on the keyboard, or it
can work in polyphonic mode where the notes notes pressed are passed to
the 3 CV output from the most recently pressed to the oldest.

It has one GATE (0-5V) when any note is pressed.

The CV output follow the 1v/Oct standard. Mid C is 5V. The CV can go
from 0V to 10V.

I'm a newbie electronic enthusiast, I'm even newer to the world of
synths. Use this at your own risk.

![Just Panel](https://github.com/soulnafein/midi-to-cv/blob/main/midi-to-cv-2.jpg?raw=true)
