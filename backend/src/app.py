import flask
from flask import Flask, request, jsonify
import json
from multiprocessing import Process, Value
import serial
import serial.tools.list_ports
import sys
import time

# Serial loop for reading serial port data
def serial_loop():
    print("Entering serial loop...")
    while True:
        # why is there a question mark??
        #? Serial port reading
        try:
            data = dumps(ser.readline())
        except serial.SerialTimeoutExeption:
            print("Data could not be read (serial timeout)")

def run_serial():
    # Look for the arduino port
    for p in serial.tools.list_ports.comports():
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

def run_server():
    # Create server
    server = Flask(__name__)

    # why is there a question mark??
    #? For hosting data
    @server.route("/api/<endpoint>", methods = ["GET", "POST"])
    def req_handler(endpoint):
        return "{} request received!".format(flask.request.method)

    server.run(debug = True, use_reloader = False)

# Run the server and the serial loop on a different process
def main():
    proc = Process(target = run_serial)
    proc.start()
    run_server()
    proc.join()

if __name__ == "__main__":
    main()
