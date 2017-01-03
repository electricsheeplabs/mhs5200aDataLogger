#!/usr/bin/gnuplot

#get variables from environment
windowSize = system("echo $FOO")
path = system("echo $name")

#set x11 window to not be raised dammit
set term x11 1 noraise
set title "MHS5200A Frequency Logger"
plot "< tail -".windowSize." ".path using 0:1 with lines title "Freq in Hz vs Time in seconds"
pause 1
reread
