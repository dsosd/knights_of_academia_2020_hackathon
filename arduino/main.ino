byte rows[] = {2, 3, 4};
byte columns[] = {5, 6, 7, 8, 9};

const int rowCount = sizeof(rows)/sizeof(rows[0]);

const int columnCount = sizeof(columns)/sizeof(columns[0]);
 
byte keys[columnCount][rowCount];
 
void setup() {
    Serial.begin(9600);
 
    for(int i=0; i<rowCount; i++) {
        pinMode(rows[i], INPUT);
    }
 
    for (int i=0; i<columnCount; i++) {
        pinMode(columns[i], INPUT_PULLUP);
    }
         
}
 
void readKeys() {
    for (int i=0; i < columnCount; i++) {
        byte currentColumn = columns[i];
        pinMode(currentColumn, OUTPUT);
        digitalWrite(currentColumn, LOW);
 
        for (int j=0; j < rowCount; j++) {
            byte rowColumn = rows[j];
            pinMode(rowColumn, INPUT_PULLUP);
            keys[i][j] = digitalRead(rowColumn);
            pinMode(rowColumn, INPUT);
        }
        pinMode(currentColumn, INPUT);
    }
}
 
void loop() {
  	// The keyboard layout (topright-to-bottomleft)
  	//0504030201
    //1009080706 
    //1514131211
    readKeys();
  	int key1 = keys[4][0];
    int key2 = keys[3][0];
  	int key3 = keys[2][0];
  	int key4 = keys[1][0];
  	int key5 = keys[0][0];
  	int key6 = keys[4][1];
  	int key7 = keys[3][1];
  	int key8 = keys[2][1];
  	int key9 = keys[1][1];
  	int key10 = keys[0][1];
  	int key11 = keys[4][2];
  	int key12 = keys[3][2];
  	int key13 = keys[2][2];
  	int key14 = keys[1][2];
  	int key15 = keys[0][2];
}






