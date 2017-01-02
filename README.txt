Made by Nick Crescimanno
an Electric Sheep Labs production
1/1/17

**This code is open source: do with it what you want. 

DISCLAIMER: This is my first ever terminal based program (bash/shell script) and the first time I have made a README for code. I am not a programmer, though that is clear to anyone who looks at the c program or shell script in this folder :D. In any case, please don't judge too hard! I would love to have experienced serial/USB/C/shell programmers provide input as to how to make this project better. Feel free to make a branch too! Finally, feel free to message me directly at electricsheeplabs@gmail.com if you have pressing comments/questions. Thanks!

This folder contains a not-so-good excuse for a piece of USB communication software that talks to an MHS2000A signal generator/frequency counter. It retails online (at the time of me typing this) for around 50$ and doesn't have much good software written for it. There is a project at https://github.com/wd5gnr/mhs5200a that enables the user to make and upload arbitrary waveforms to the device (which has 16 spots in storage for such waveforms!). But, I also wanted to log the input frequency of the device and use it more as a data logger/frequency counter, and thus this abomination was born.

This program uses gnuplot, the only additional item you will need on a Linux machine to run this (unless you don't have a c compiler, which you do indeed need). Next, simply download and unzip the project folder, compile the c program to
an executable called mhsPlotter (in the folder directory in the terminal type "gcc mhsPlotter.c -o mhsPlotter"), give permission to the shell script (something like "chmod 755 plotter.sh"), plug in the device, and execute the shell script with super user permission ("sudo ./plotter.sh").

NOTE: there was plenty of hard coding going on during the making of this project, and one real bad one is the USB device. If your program doesn't run because it says it cannot find device ttyUSB0, try opening up the c program and change the 0 to
a 1, 2, etc until it recognizes the device, and don’t forget to recompile!...(I have no idea if that will actually work but its the best I got until I find out how to detect the correct device...).

When running, you will be prompted for a file name (with no file extension!!, just a name...) and a window. The window takes integer value entries for the duration (in seconds) you would like to view the signal over (the graph will pan and auto scale within that window). Let me know through push request or email what needs fixed. 

ANOTHER NOTE: I used countless pieces of example code online to hack this clunker together, and will try to populate the bottom of this readme
with some links to those pages (if not for acknowledging the people I ripped offa). 
