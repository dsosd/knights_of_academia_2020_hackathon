import copy
import flask
import json
import multiprocessing as mproc
import serial
import serial.tools.list_ports
import sys
import time

# Serial loop for reading serial port data
def serial_loop():
    print("Entering serial loop...")
    ser.open()
    while True:
        # Serial port reading
        try:
            #TODO implement actual data handling
            data = json.dumps(ser.readline())
            print(data)
        except serial.SerialTimeoutException:
            print("Data could not be read (serial timeout)")

def run_serial():
    # Look for the arduino port
    for p in serial.tools.list_ports.comports():
        # Print ports for debugging
        print(f"{p}. ")
        if "COM3" in p.description:
            print(f"Arduino Port -> {p}")
            port = p.name

        plugged_in = False
        port_num = 9600

        # Check if Arduino is plugged in
        while not plugged_in:
            try:
                #ser = serial.Serial(p, 9600, timeout = 0)
                global ser
                ser = serial.Serial(port, port_num, timeout = 0)
                plugged_in = True
            except Exception as e:
                print(e)
                print("!!! NO PLUGGED-IN ARDUINO DETECTED !!!")
                #TODO add wait for keypress prompt instead
                time.sleep(1000)
        serial_loop()

def gen_400_err():
    return "Bad request made", 400

def run_server():
    server = flask.Flask(__name__)

    port_to_id = {}
    data = {}

    # HTTP part
    @server.route("/api/ports", methods = ["GET"])
    def ports_handler():
        return json.dumps(list(port_to_id.keys()))

    @server.route("/api/connect", methods = ["GET"])
    def connect_handler():
        try:
            return json.dumps(str(port_to_id[
                flask.request.args.get("port")
            ]))
        except KeyError:
            return gen_400_err()

    @server.route("/api/board/<int:id>", methods = ["GET"])
    def board_handler(id):
        try:
            ret = copy.deepcopy(data[id])
            ret.update({"id": id})

            return json.dumps(ret)
        except KeyError:
            return gen_400_err()

    server.run(debug = True, use_reloader = False)

# Run the server and the serial loop on a different process
def main():
    proc = mproc.Process(target = run_serial)
    proc.start()
    run_server()
    proc.join()

if __name__ == "__main__":
    main()
