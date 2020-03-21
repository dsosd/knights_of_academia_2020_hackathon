# the-knights

> A Pet keyboard powered by Arduino and interacted by Web

**the-knights** is a small RGB keyboard, It has an Arduino inside that talks to your computer by Serial Port and does some really cool things. Like? Pomodoro Timers! 🍅

## Index
- [Core Principles and Working](#core-principles-and-working)
    1. [Basic Idea](#basic-idea)
    2. [Deep Dive](#deep-dive)
        - [Arduino and Backend Communication](#arduino-and-backend-communication)
            - Payload Structure
            - Events
                - From Arduino
                - From Backend
        - [Backend and Frontend Communication](#backend-and-frontend-communication)
            - HTTP Methods
            - Websocket
                - Payload Structure
                - Events
                    - From Server
                    - From Frontend
        - [Function Flows](#function-flows)
            - Keybindings
            - Handling Timers
- [How to make it yourself](#how-to-make-it-yourself)
- [Contribution](#contribution)
    - [TODOs](#todos)
    - [Contributors](#contributors)
---

## Core Principles and Working

### 1. Basic Idea

The whole product is divided into 3 Main Parts

![Flowchart](/flowchart.svg)

The Arduino compatible board, here act as a keyboard. Sending keypresses and knob values to the Serial Port.

Then you have your Backend, a server running Websocket and HTTP Server both running on the same server while also listening to your serial ports. Backend manages most of the things as it helps in conveying information from the Arduino to the Frontend

The Frontend then acts as your Dashboard. You can use the Dashboard to change the configuration of your keyboard.

### 2. Deep Dive

This page contains mainly a brief of the communication, how this communication is implemented through individual libraries is mentioned in the sub folders.

#### Arduino and Backend Communication

The **Arduino and Backend** follow an event schema throughout the time they message each other. The Schema to be followed is given below.

```json
    {
        "event": "EVENT_NAME",
        "data": {...}
    }
```

The events are as follows:
- From Arduino
    1. `CONFIG`

        The Arduino on initialisation for the very first powerup writes a unique string of 8 numerical characters on the external EEPROM. This unique string acts as an id of the Board.

        This is sent in the `CONFIG` payload once the Arduino is connected to the Serial Port. Once this is sent the Backend needs to store all the details related to this specific board with this `id`. All the details include Port it is connected to, the RGB LEDs data along with Keybindings too.

        ```json
            {
                "event": "CONFIG",
                "data": {
                    "id": 12345678
                }
            }
        ```

        If connection is successfull the Server responds with a `CONNECTED` Payload

    2. `KEYSTATUS`

        This is sent periodically once the board has succesfully connected. Here `active` represents the keys currently pressed and `knob` represents the value of knob which is between 0 and 100.

        ```json
            {
                "event": "KEYSTATUS",
                "data": {
                    "active": [0, 1, 3, 5, 10],
                    "knob": 100
                }
            }
        ```

        
- From the Server
    1. `CONNECTED`

        This payload is sent once the server has recieved the `CONFIG` payload.

        ```json
            {
                "event": "CONNECTED",
                "data": {}
            }
        ```

    2. `UPDATE_LEDS`

        This payload is sent to update the rgb leds color. `leds` contain an object with keys representing the led number and value being an array of three numbers `[R, G, B]` between 0 and 255.

        ```json
            {
                "event": "UPDATE_LEDS",
                "data": {
                    "leds": {
                        0: [70, 20, 255],
                        1: [70, 54, 0],
                        ...
                        20: [100, 255, 255]
                    }
                }
            }
        ```

        The LEDs are numbered from top right to bottom left. Like so

        ```
        05 04 03 02 01
        10 09 08 07 06
        15 14 13 12 11
        20 19 18 17 16
        ```

#### Backend and Frontend Communication

The **Backend and Frontend** also communicate with the help of HTTP Methods and a Websocket.
    
The http server listens on the `localport:8080/api` and the Websocket server listens on `localport:8080`. The server also needs to host these frontend files.

- HTTP Methods

    1. `GET /api/ports`

        This route sends a JSON body with array of ports to which Arduino is connected on the Computer.

    2. `GET /api/connect`

         > Note: This route requires urlencoded parameter containing the port you want to connect to. Example, `/api/connect?port=com4`

        If successfull the route responds with the `id` of board, which we can use for identification on Websocket.

    3. `GET /api/boards/id`

        Here `id` is the Id of board that we get from `/api/connect`. Responds with a JSON Body like so

        ```json
            {
                "id": 12345678,
                "leds": {
                    0: [70, 20, 255],
                    1: [70, 54, 0],
                    ...
                    20: [100, 255, 255]
                },
                "keybindings": {
                    0: {
                        "type": "script",
                        "data": "code ~/Projects/the-knights"
                    },
                    1: {
                        "type": "keystroke",
                        "data": "E"
                    },
                    2: {
                        "type": "timer",
                        "data": ""
                    },
                    ...
                    20: {
                        "type": "keystroke",
                        "data": "Ctrl Alt Up"
                    }
                },
                "time": 45
            }
        ```

        Here `time` represents the timers time in minutes
    
- Websocket
        
    The websocket also follows an payload schema, given below

     ```json
        {
            "id": 12345678,
            "event": "EVENT_NAME",
            "data": {...}
        }
    ```

    The Events are given below

    - From Frontend

        1. `UPDATE_LEDS`

            Same as `UPDATE_LEDS` from [Arduino-Backend Communication](#arduino-and-backend-communication) but with `id` parameter.

        2. `UPDATE_KEYBINDINGS`

            Used to update keybindings.

            ```json
                {
                    "id": 12345678,
                    "event": "UPDATE_KEYBINDINGS",
                    "data": {
                        "keybindings": {
                            0: {
                                "type": "script",
                                "data": "code ~/Projects/the-knights"
                            },
                            1: {
                                "type": "keystroke",
                                "data": "E"
                            },
                            2: {
                                "type": "timer",
                                "data": "",
                            },
                            ...
                            20: {
                                "type": "keystroke",
                                "data": "Ctrl Alt Up"
                            }
                        }
                    }
                }
            ```

    - From the Server

        1. `UPDATE_TIMER`

            Used to update time of timer, Here `time` represents the timers time in minutes

            ```json
                {
                    "id": 12345678,
                    "event": "UPDATE_TIMER",
                    "data": {
                        "time": 45
                    }
                }
            ```

        2. `START_TIMER`

            Used to inform frontend the timer has started

            ```json
                "id": 12345678,
                "event": "START_TIMER",
                "data": {
                    "time": 45
                }
            ```

        3. `END_TIMER`

            Used to inform frontend the timer has stopped

            ```json
                "id": 12345678,
                "event": "END_TIMER",
                "data": {}
            ```

#### Function Flows

Here are some of the function flows

1. Keybindings
2. Handling Timers

---

## How to make it yourself

Project not yet complete. So no way to get it working

---

## Contribution

If you would like to work on this, Fork the Repository make changes and Send PRs! ❤️

### TODOs

Global todos related to the project in common

- [x] Start this README
- [ ] Complete README Function Flows
- [ ] Fix Grammar and Typo of README

### Contributors

<a href="https://github.com/SagnikPradhan/the-knights/graphs/contributors">
  <img src="https://contributors-img.web.app/image?repo=SagnikPradhan/the-knights" />
</a>