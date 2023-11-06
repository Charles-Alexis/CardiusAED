import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib import style
import numpy as np
import random
import serial
import binascii as b


#initialize serial port
ser = serial.Serial()
ser.port = 'COM3' #Arduino serial port
ser.baudrate = 115200
ser.timeout = 1
ser.open()
if ser.is_open==True:
	print("\nAll right, serial port now open. Configuration:\n")
	print(ser, "\n") #print serial parameters

# Create figure for plotting
fig = plt.figure()
ax = fig.add_subplot(1, 1, 1)
xs = [] #store trials here (n)
DataA = [] #store relative frequency here
rs = [] #for theoretical probability


def animate(i,DataA,temp):
    line=ser.readline()      #ascii
    Data = float(line[0:(len(line)-2)])
    print(Data)
    DataA.append(Data)

    ax.clear()
    ax.plot(DataA)

    # Format plot
    plt.xticks(rotation=45, ha='right')
i=0
temp = 9
##Set up plot to call animate() function periodically
ani = animation.FuncAnimation(fig, animate, fargs=(DataA,temp),interval=4)
plt.show()


'''
############################################################################################################################################################

fig, ax = plt.subplots()
x = np.arange(0, 2*np.pi, 0.01)
line, = ax.plot(x, np.sin(x))

def init():
    line.set_ydata([np.nan] * len(x))
    return line,


def animate(i):
    line.set_ydata(np.sin(x + i / 100))
    return line,


ani = animation.FuncAnimation(fig, animate, init_func=init, interval=2, blit=True, save_count=50)
plt.show()
'''







