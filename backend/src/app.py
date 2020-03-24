import copy
import flask
from flask import jsonify
import flask_socketio as flask_sio
import json
import multiprocessing as mproc
import serial
import serial.tools.list_ports
import sys
import time

ser = serial.Serial()
data = {}

def run_serial():
    global ser

    port = ""
    # Look for the arduino port
    for p in serial.tools.list_ports.comports():
        # Print ports for debugging
        print(f"{p}. ")
        desired_port = 'COM3'
        if desired_port in p.description:
            print(f"Arduino Port -> {p}")
            port = desired_port
            #port_num = 9600

    # Check if Arduino is plugged in
    while True:
        try:
            ser.port = port
            ser.baudrate = 9600
            ser.timeout = 0
            break
        except Exception as e:
            print(e)
            print("!!! NO PLUGGED-IN ARDUINO DETECTED !!!")
            #TODO add wait for keypress prompt instead
            time.sleep(1000)
    serial_loop()

# Serial loop for reading serial port data
def serial_loop():
    global ser
    global data
    print(f"Entering serial loop...")
    ser.open()
    ser.flush()
    first_time = True
    while True:
        # Serial port reading
        try:
            #TODO implement actual data handling
            if data != {} or first_time == True:
                data = ser.readline()
                data = json.loads(json.dumps(data.decode("utf-8")))
                first_time = False
                print(data)
            time.sleep(1)
        except serial.SerialTimeoutException:
            print("Data could not be read (serial timeout)")
    ser.close()

def gen_400_err():
    return "Bad request made", 400

def run_server():
    port = 8080

    http_server = flask.Flask(__name__)
    ws_server = flask_sio.SocketIO(http_server)

    port_to_id = {}
    data = {}
    timer = {}

    # HTTP part
    @http_server.route("/api/ports", methods = ["GET"])
    def ports_handler():
        return json.dumps(list(port_to_id.keys()))

    @http_server.route("/api/connect", methods = ["GET"])
    def connect_handler():
        try:
            return json.dumps(str(port_to_id[
                flask.request.args.get("port")
            ]))
        except KeyError:
            return gen_400_err()

    @http_server.route("/api/board/<int:id>", methods = ["GET"])
    def board_handler(id):
        try:
            ret = copy.deepcopy(data[id])
            ret.update({"id": id})

            return json.dumps(ret)
        except KeyError:
            return gen_400_err()

    # adds each relevant client, the frontend and the
    # arduino part of the backend, to their appropriate rooms
    @ws_server.on("message")
    def add_to_room(room_name):
        # valid room names are "frontend" and "arduino"
        # not checked here, but necessary for replies/broadcasts
        flask_sio.join(room_name)

    def frontend_ws_handler(payload):
        json_data = json.loads(payload)

        id = json_data["id"]
        if id not in data.keys():
            return {"error": "Id is not valid"}
        event = json_data["event"]

        if event == "UPDATE_LEDS":
            data[id]["leds"].update(json_data["data"])
            # update the leds on the arduino side
            ret = {
                "event": "UPDATE_LEDS",
                "data": {
                    "leds": data[id]["leds"]
                }
            }
            return data[id], "arduino"
        elif event == "UPDATE_KEYBINDINGS":
            data[id]["keybindings"].update(json_data["data"])
            return {}
        else:
            return {"error": "Event is not valid"}

    #TODO implement websocket support to arduino part of backend. simplifies design
    def arduino_ws_handler(payload):
        pass

    #TODO timer functions need more specification. what triggers a timer start/end/update??
    def on_timer_start():
        pass

    def on_timer_end():
        pass

    #NOTE unknown rate of updates
    def on_timer_update():
        pass

    # manages all inbound json payloads
    @ws_server.on("json")
    def json_handler(payload):
        room = flask.session.get("room")

        def reply(data, room = room):
            flask_sio.emit("json", data, room = room, include_self = false)

        if room == "frontend":
            ret = frontend_ws_handler(payload)
            if len(ret):
                reply(ret)
        elif room == "arduino":
            ret = arduino_ws_handler(payload)
            if len(ret):
                reply(ret)
        else:
            reply({"error": "Room is not valid"})

    # ws_server.run(...) starts the http server as well. comment is for debugging purposes
    #http_server.run(port = port, debug = True, use_reloader = False)
    ws_server.run(app = http_server, port = port, debug = True, use_reloader = False)

# Run the http/ws server and the serial port interface on different processes
def main():
    proc = mproc.Process(target = run_serial)
    proc.start()
    run_server()
    proc.join()

if __name__ == "__main__":
    main()
