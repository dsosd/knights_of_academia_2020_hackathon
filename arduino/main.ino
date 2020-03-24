#include <EEPROM.h>

#include <Adafruit_NeoPixel.h>

#include <string.h>

// Edit these to your needs
#define PIN       11
#define NUMPIXELS 15

String dataRead;
float adataRead;
bool connected = false;
int mappedknobval = 0;

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


// The pins for the rows/columns
byte rows[] = {2, 3, 4};
byte columns[] = {5, 6, 7, 8, 9};

const int rowCount = sizeof(rows)/sizeof(rows[0]);

const int columnCount = sizeof(columns)/sizeof(columns[0]);
 
byte keys[columnCount][rowCount];

void setup() {
	Serial.begin(57600);
  	pixels.begin();
 
	for(int i=0; i < rowCount; i++) {
		pinMode(rows[i], INPUT);
	}
 
	for (int i=0; i < columnCount; i++) {
		pinMode(columns[i], INPUT_PULLUP);
	}
  
}
 
void readKeys() {
	for (int i=0; i < columnCount; i++) {
		byte currentColumn = columns[i];
		pinMode(currentColumn, OUTPUT);
		digitalWrite(currentColumn, LOW);

		for (int j=0; j < rowCount; j++) {
			byte currentRow = rows[j];
			pinMode(currentRow, INPUT_PULLUP);
			keys[i][j] = digitalRead(currentRow);
			pinMode(currentRow, INPUT);
		}
		pinMode(currentColumn, INPUT);
	}
}


void sendKeys() {
  	// The keyboard layout (topright-to-bottomleft)
	//05-04-03-02-01
	//10-09-08-07-06 
	//15-14-13-12-11
  	readKeys();
  	bool first = true;
  	int keysarr[] = {keys[4][0], keys[3][0], keys[2][0], 
              		 keys[1][0], keys[0][0], keys[4][1], 
                     	 keys[3][1], keys[2][1], keys[1][1], 
                     	 keys[0][1], keys[4][2], keys[3][2],
                     	 keys[2][2], keys[1][2], keys[0][2]};
  	Serial.print("{\"event\": \"KEY_STATUS\",\"data\": {\"active\": [");
 	for (int i=0; i < 15; i++) {
		if (keysarr[i] == 0) {
		  	if (first) {
				Serial.print(i + 1);
				first = false;
		   	} else {
				Serial.print(", ");
				Serial.print(i + 1);
		   	}
		}
  	}
	// On 5V analogRead() is 1023 max. Here it gets "mapped" to 0 to 100.
  	int knobval = analogRead(A0);
  	if (knobval < 10.23) {
      		mappedknobval = 0;
    	}else {
    		mappedknobval = knobval / 10.23;
    	}
  	Serial.print("], \"knob\": ");
    	Serial.print(mappedknobval);
  	Serial.println("}}");
}

void setRgb(String rgbdata) {
	// In the environment I coded this in I couldnt use the json library, 
	// so here I'll just split and strip the strings to my needs.
  	pixels.clear();
  	char buf[rgbdata.length()];
  	rgbdata.toCharArray(buf, sizeof(buf));
  	char* token;
  	char* rest = buf;
  	int i = 1;
    	while ((token = strtok_r(rest, "[", &rest))) {
		char* token2;
		char* resttoken = token;
		while ((token2 = strtok_r(resttoken, "]", &resttoken))) {
			char* token3;
		    	char* resttoken2 = token2;
			if (i%2== 0) {
				int j = 0;
				int rgb[3];
				while ((token3 = strtok_r(resttoken2, ",", &resttoken2))) {
				    rgb[j] = atoi(token3);
				    j++;
				}
				pixels.setPixelColor((i/2)-1, pixels.Color(rgb[0], rgb[1], rgb[2]));
			}
		i++;
		}
    	}
    	pixels.show();
}

String readEEPROMID() {
    String id;
    for (int i=0;i<8;i++) {
        id += EEPROM.read(i);
    }
    return id;
}

void writeEEPROMID() {
    for (int i=0;i<8;i++) {
        EEPROM.write(i, random(10));
    }
}
  
 
void loop() {
  	if (connected) {
    	sendKeys();
    	if (Serial.available() > 0) {
        	dataRead = Serial.readString();
        	setRgb(dataRead);
    	}
    } else {
      	if (readEEPROMID() == "00000000") {
         	 writeEEPROMID();
      	}
      	Serial.print("{\"event\": \"CONFIG\",\"data\":{\"id\": ");
      	Serial.print(readEEPROMID());
      	Serial.println("}}");
      	if (Serial.available() > 0) {
        	dataRead = Serial.readString();
          	if (dataRead.indexOf("CONNECTED") > 0) {
           		 connected = true;
            }
    	}
    }
}


