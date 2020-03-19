from flask import Flask, request, jsonify
from multiprocessing import Process, Value
import serial
import time
import json


#ser = serial.Serial("COM3", 9600, timeout = 0)

server = Flask(__name__)

example_json = [
    {
        "leds": {
            0: [255, 255, 255]
            }
    }
]

#? For hosting data
@server.route('/')
def index():
    return jsonify(example_json)

def serial_loop():
    while True:
        print ("Main server loop running")
        time.sleep(1)

if __name__ == '__main__':
    p = Process(target=serial_loop)
    p.start()  
    server.run(debug=True, use_reloader=False)
    p.join()

#? Serial port reading
# Hashed out as serial ports not configured yet
#try:
    #data = dumps(ser.readline())
#except ser.SerialTimeoutExeption:
    #print("Data could not be read")
    #time.sleep(1)
