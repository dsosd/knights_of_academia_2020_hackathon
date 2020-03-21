from flask import Flask, request, jsonify
import json
from multiprocessing import Process, Value
import serial
from serial.tools import list_ports
import sys
import time

def serial():
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
    port_num = 9600

    # Check if Arduino is plugged in
    while not plugged_in:
        try:
            #ser = serial.Serial(p, 9600, timeout = 0)
            ser = serial.Serial(port, port_num, timeout = 0)
            plugged_in = True
        except:
            print("!!! NOT PLUGGED IN !!!")
            #TODO add wait for keypress prompt instead
            time.sleep(1)

    serial_loop()

# Create server
server = Flask(__name__)

#? For hosting data
@server.route('/')
def index():
    return data

# Serial loop for reading serial ports
def serial_loop():
    print("Entering serial loop...")
    while True:
        #? Serial port reading
        try:
            data = dumps(ser.readline())
        except serial.SerialTimeoutExeption:
            print("Data could not be read (serial timeout)")

# Run the server and the serial loop on a different process
def main()
    proc = Process(target = serial)
    proc.start()
    server.run(debug = True, use_reloader = False)
    proc.join()

if __name__ == "__main__":
    main()
