from flask import Flask, request, jsonify
from multiprocessing import Process, Value
import serial
import time
import json

plugged_in = False

while not plugged_in:
    try:
        ser = serial.Serial("COM3", 9600, timeout = 0)
        plugged_in = True
    except:
        print("!!! NOT PLUGGED IN !!!")
        time.sleep(1)

server = Flask(__name__)

#? For hosting data
@server.route('/')
def index():
    return jsonify(example_json)

def serial_loop():
    print ("Entering main server loop..")
    while True:
        #? Serial port reading
        try:
            data = dumps(ser.readline())
        except ser.SerialTimeoutExeption:
            print("Data could not be read")

if __name__ == '__main__':
    p = Process(target=serial_loop)
    p.start()  
    server.run(debug=True, use_reloader=False)
    p.join()
