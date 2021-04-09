//Autonomous driving_ 1st version

#include "Altino.h"
#include <stdio.h>
#define GoSpeed 380
#define BackDelay 800

void buzzer() {
	Sound(37);
	delay(100);
	Sound(0);
	delay(100);
}


int main() {

	int strCount = 0;

	SensorData data1, data2;
	//int ir0, ir1, ir2;
	Open(szPort);
	//state Car;
	Steering(2);

	while (1) {
		data1 = Sensor(1);
		Go(0, 0);
		if (data1.IRSensor[5] > 200)
			break;
	}

	Go(800, 800);

	while (1) {
		data1 = Sensor(1);
		//printf("Sensor1 : %d, Sensor2 : %d, Sensor3 : %d\nSensor4 : %d, Sensor5 : %d, Sensor6 : %d\n\n", data1.IRSensor[0], data1.IRSensor[1], data1.IRSensor[2], data1.IRSensor[3], data1.IRSensor[4], data1.IRSensor[5]);

		if (data1.CDSSensor < 120) {
			break;
		}
	}

	while (1) {
		data1 = Sensor(1);
		buzzer();

		if (data1.CDSSensor > 120) {
			break;
		}

	}

	while (1) {


		data1 = Sensor(1);
		//printf("Sensor1 : %d, Sensor2 : %d, Sensor3 : %d\nSensor4 : %d, Sensor5 : %d, Sensor6 : %d\n\n", data1.IRSensor[0], data1.IRSensor[1], data1.IRSensor[2], data1.IRSensor[3], data1.IRSensor[4], data1.IRSensor[5]);
		//printf("GyroX : %4d, GyroY : %4d, GyroZ : %4d\n", data1.IRSensor[0], data1.IRSensor[1], data1.IRSensor[2]);

		Go(350, 350);


		if (data1.IRSensor[1] > 40 || data1.IRSensor[0] > 100 || data1.IRSensor[2] > 100) {
			data1 = Sensor(1);
			if (strCount >= 3) {
				break;
			}
			data1 = Sensor(1);
			Go(0, 0);
			//delay(500);
			Go(-500, -500);
			delay(700);
			strCount++;
			printf("count : %d\n", strCount);

			data2 = Sensor(1);
			printf("Left : %d, Right : %d\n", data2.IRSensor[0], data2.IRSensor[2]);

			Steering(1);
			Go(400, 400);
			delay(1200);
			Go(0, 0);
			Steering(2);
		}


	}

	while (1) {
		data1 = Sensor(1);
		printf("Reverse : %d", data1.IRSensor[5]);
		Go(-400, -400);


		
		if (data1.IRSensor[5] > 40) {
			break;
		}

	}

	while (1) {
		Go(GoSpeed, GoSpeed);
		delay(1900);
		Steering(3);
		Go(-350, -350);
		delay(1600);
		Steering(1);
		Go(GoSpeed, GoSpeed);
		delay(1800);
		Steering(2);
		break;
	}

	while (1) {
		data1 = Sensor(1);
		Go(800, 800);
		if (data1.CDSSensor < 120) {
			char dot[3] = { 'K', 'J', 'W'};
			int count = 0;
			while (1) {
				Display(dot[count % 3]);
				delay(500);
				count++;
				if (count > 3) {
					break;
				}
			}
			break;
		}
	}

	
	while (1) {
		data1 = Sensor(1);
		Go(350, 350);
		printf("Reverse : %d\n", data1.IRSensor[5]);
	}
	Go(0, 0);
	delay(BackDelay);


	Close();

	return 0;


}

