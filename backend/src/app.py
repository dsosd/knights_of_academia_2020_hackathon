import copy
import flask
import flask_socketio as flask_sio
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
    # arduino part of the backend to their appropriate rooms
    @ws_server.on("message")
    def add_to_room(room_name):
        # valid room names are "frontend" and "arduino"
        flask_sio.join(room_name)

    def frontend_ws_handler(payload):
        json_data = json.loads(payload)

        id = json_data["id"]
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

    #TODO timer functions need more specification. what triggers a timer??
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
            emit("json", data, room = room, include_self = false)

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
