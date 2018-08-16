//Serial Variables
char inBuff[5] = {};
struct Data {
								float vTot = 0;
								float vHigh = 0;
								float vLow = 0;
								float current = 0;
								float tempOne = 0;
								float tempTwo = 0;
								int rpm = 0;
								int throttle = 0;
								int brake = 0;
								float speed = 0;
								float distance = 0;
								float gearRatio = 0;
} data;


void setup(){
								Serial.begin(115200);
}

void loop() {
								receiveSerial(); //call every loop
}

void receiveSerial(){
								if(Serial.available()) {
																buffPush(Serial.read());
																if(inBuff[4] == '}') { // Latest char is the end of a packet
																								if(inBuff[0] =='{') { // First char of packet is in expected location - we should have data between them
																																float value = dataDecode(inBuff[2],inBuff[3]);
																																assignValue(inBuff[1], value);
																								}
																}
								}
}

void buffPush(char in){
								//hard coded for buffer length of 5
								for(int i = 0; i < 4; i++) { //leave last value untouched, hence -1
																//Shifts the array left
																inBuff[i] = inBuff[i+1];
								}
								//Add new value to end
								inBuff[4] = in;
}

float dataDecode(char b1, char b2){
								float val = 0;
								//First calculate the value in b1 and b2
								//Check for 0
								if( b1 == 0xFF && b2 = 0xFF) {
																val = 0;
								} else if (b1 > 127) { // check flag for integer
																val = ((int)b1 - 128)*100 + (int)b2;
																Serial.print("integer value decoded as: ");
																Serial.println(val);
								} else{ //value is a float
																val = (float)((int)b1 + ((int)b2/100));
																Serial.print("Float value decoded as: ");
																Serial.println(val);
								}

								return val;
}

void assignValue(char id, float val){
								switch (id) {
								case 's':
																data.speed = val;
																break;
								case 'm':
																data.rpm = val;
																break;
								case 'i':
																data.current = val;
																break;
								case 'v':
																data.vTot = val;
																break;
								case 'w':
																data.vLow = val;
																data.vHigh = data.vTot-val;
																break;
								case 't':
																data.throttle = val;
																break;
								case 'a':
																data.tempOne = val;
																break;
								case 'b':
																data.tempTwo = val;
																break;
								case 'r':
																data.gearRatio = val;
																break;
								case 'B':
																data.brake = val;
																break;
								default:
																break;
								}
}
