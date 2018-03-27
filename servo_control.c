#pragma config(Sensor, S1, TIR, sensorI2CCustom)

ubyte pan_left = 0x01; // command to pan left 
ubyte pan_right = 0x02; // command to pan camera right 

void sendCommand(ubyte command){
	ubyte msgSize = 0x04;
	ubyte deviceAddress = 0x14; //0x0A on Arduino
	ubyte regAddress = 0x01;

	ubyte i2cMsg[7];//create empty msge on stack
	i2cMsg[0] = msgSize;
	i2cMsg[1] = deviceAddress;
	i2cMsg[2] = regAddress;
  i2cMsg[3] = command;

  i2cMsg[4] = 0x00;
  i2cMsg[5] = 0x00;
  i2cMsg[6] = 0x00;

  sendI2CMsg(S1, &i2cMsg[0], 0x00);
  //wait1Msec(20);
}

void arduinoControl(){
		if(nNxtButtonPressed == kLeftButton){
			sendCommand(pan_left);
			wait1Msec(50);
		}	
		else if(nNxtButtonPressed == kRightButton){
			sendCommand(pan_right);
			wait1Msec(50);
		}	
}		

task main(){
	while(true){
		arduinoControl();
	}
}
