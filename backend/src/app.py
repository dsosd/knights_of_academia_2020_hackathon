from flask import Flask, request, jsonify
from multiprocessing import Process, Value
import serial
from serial.tools import list_ports
import json
import time

# List of ports
ports = list(list_ports.comports())

# Look for the arduino port
for p in ports:
    # Print ports for debugging
    print(f"{p}. ")
    if "Arduino" in p.description:
        print(f"Arduino Port -> {p}")
        port = p

plugged_in = False

# Check if Arduino is plugged in
while not plugged_in:
    try:
        ser = serial.Serial(p, 9600, timeout = 0)
        plugged_in = True
    except:
        print("!!! NOT PLUGGED IN !!!")
        time.sleep(1)

# Create server
server = Flask(__name__)

#? For hosting data
@server.route('/')
def index():
    return data

# Serial loop for reading serial ports
def serial_loop():
    print ("Entering main server loop..")
    while True:
        #? Serial port reading
        try:
            data = dumps(ser.readline())
        except ser.SerialTimeoutExeption:
            print("Data could not be read")

# Run the server and the serial loop on a different process
if __name__ == '__main__':
    p = Process(target=serial_loop)
    p.start()  
    server.run(debug=True, use_reloader=False)
    p.join()
