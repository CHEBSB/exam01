import matplotlib.pyplot as plt
import numpy as np
import serial
import time

Fs = 2000.0;  # sampling rate
Ts = 1.0/Fs; # sampling interval
t = np.arange(0,1,1/128) # time vector; create Fs samples between 0 and 1.0 sec.
y = np.arange(0,1,1/128) # signal vector; create Fs samples

n = len(y) # length of the signal
k = np.arange(n)
T = n/Fs
frq = k/T # a vector of frequencies; two sides frequency range
frq = frq[range(int(n/2))] # one side frequency range

serdev = '/dev/ttyACM0'
s = serial.Serial(serdev)
for x in range(0, 127):
    line=s.readline() # Read an echo string from K66F terminated with '\n'
    # print line
    y[x] = float(line)


fig, ax = plt.subplots(1, 1)
ax.plot(t,y)
ax.set_xlabel('Time')
ax.set_ylabel('Amplitude')
plt.show()
s.close()