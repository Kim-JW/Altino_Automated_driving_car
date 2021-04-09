#include "Altino.h"
#include <stdio.h>

int main()
{
	SensorData sdata;

	int count = 1;
	int sound_count = 0;
	int value = 0;
	int Display_value = 0;
	int CDS_count = 0;

	int third_value = 0;

	Open(szPort);

	Sendbuf[21] = 10;

	while (1)
	{
		sdata = Sensor(1);
		if (sdata.IRSensor[5] > 200)
		{
			break;
		}
	}

	while (1)
	{
		sdata = Sensor(1);
		printf("Illuminance value : %d\n ", sdata.CDSSensor);

		if (sdata.CDSSensor < 120 && sound_count == 0)
		{
			sound_count++;
			third_value++;

			Sound(37);
			delay(300);
			Sound(55);
			delay(300);
			Sound(67);
			//delay(300);

			//Display_value++;
			//CDS_count++;

			sdata = Sensor(1);
			//delay(100);

		}

		// If car enter tunnel, turn on LEDs.

		else if (sdata.CDSSensor < 120 && Display_value == 1)
		{
			Display('K');
			delay(900);
			Display('J');
			delay(900);
			Display('W');
			delay(900);
			//Display(' ');
			Display_value++;
		}

		else
		{
			Sound(0);
			delay(300);
			//Display(' ');
		}


		// enter T course

		/*	if (sdata.IRSensor[1] > 200 && count >= 3)
		{
		printf("Second Trigger\n");

		sdata = Sensor(1);
		Go(-400, -400);
		}

		*/

		if (sdata.IRSensor[1] > 60 && sdata.IRSensor[2] > 60 && value == 0)
		{
			if (count >= 3)
			{
				sdata = Sensor(1);
				delay(1000);
				Go(-400, -400);
				delay(3000);
				value++;
			}

			count++;
			printf("First Trigger On.\n");
			printf("count : %d\n", count);

			sdata = Sensor(1);
			delay(1000);

			Steering(3);
			Go(-350, -350);
			delay(1000);

			Steering(1);
			Go(400, 400);

			//delay(2000);
			//Steering(2);
		}

		// Last Session
		else if (sdata.IRSensor[5] > 200 && third_value >= 1)
		{

			Display_value++;

			printf("Third Trigger!\n");
			sdata = Sensor(1);
			delay(1000);

			Go(350, 350);
			delay(700);

			Steering(3);
			Go(-350, -350);
			delay(1500);

			Steering(1);
			Go(350, 350);
			delay(1700);
			Steering(2);


			//Go(300, 300);
		}

		else
		{
			Steering(2);
			Go(350, 350);
			sdata = Sensor(1);
		}

	}

	return 0;
}
