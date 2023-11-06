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
C1A = [] #store relative frequency here
C2A = [] #store relative frequency here
C3A = [] #store relative frequency here
C4A = [] #store relative frequency here
rs = [] #for theoretical probability

"""
while True:
    line=ser.readline()      #ascii
    line_as_list = str(line[0:2],'utf-8')
    if line_as_list == 'C2':
        res = float(line[3:(len(line)-2)])
        print(res)

"""

def animate(i,DataA,C1A,C2A,C3A,C4A):
    flag1 = False
    flag2 = False
    flag3 = False
    flag4 = False
    flag5 = False
    i = 0
    #Aquire and parse data from serial port
    while flag1 == False or flag2 == False or flag3 == False or flag4 == False or flag5 == False:
        line=ser.readline()      #ascii
        i=i+1
        
        line_as_list = str(line[0:2],'utf-8')
        if line_as_list == 'D0':
            Data = float(line[3:(len(line)-2)]) 
            flag1 = True
            
        if line_as_list == 'C1':
            C1 = float(line[3:(len(line)-2)])
            flag2 = True
            
        if line_as_list == 'C2':
            C2 = float(line[3:(len(line)-2)])
            flag3 = True
            
        if line_as_list == 'C3':
            C3 = float(line[3:(len(line)-2)])
            flag4 = True
            
        if line_as_list == 'C4':
            C4 = float(line[3:(len(line)-2)])
            flag5 = True
        else:
            i = 0.0
            
       
	
	# Add x and y to lists
    
    
    DataA.append(Data)
    C1A.append(C1)
    C2A.append(C2)
    C3A.append(C3)
    C4A.append(C4)

    # Limit x and y lists to 20000 items
    DataA = DataA[-20000:]
    C1A = C1A[-20000:]
    C2A = C2A[-20000:]
    C3A = C3A[-20000:]
    C4A = C4A[-20000:]

    # Draw x and y lists
    ax.clear()
    ax.plot(DataA,label = 'Data')
    ax.plot(C1A,label = 'MAX/2')
    ax.plot(C2A,label = 'MEAN')
    ax.plot(C3A,label = 'MEAN-MD')
    ax.plot(C4A,label = 'MEAN+MD')
    plt.legend()

    # Format plot
    plt.xticks(rotation=45, ha='right')

##Set up plot to call animate() function periodically
ani = animation.FuncAnimation(fig, animate, fargs=(DataA,C1A,C2A,C3A,C4A),interval=10)
plt.show()