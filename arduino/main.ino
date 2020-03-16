byte rows[] = {2, 3, 4};
byte columns[] = {5, 6, 7, 8, 9};

const int rowCount = sizeof(rows)/sizeof(rows[0]);

const int columnCount = sizeof(columns)/sizeof(columns[0]);
 
byte keys[columnCount][rowCount];
 
void setup() {
	Serial.begin(9600);

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
 
void loop() {
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
	Serial.print("{\"keysPressed\" : [");
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
	Serial.println("]}");

}






