//Second Code

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Altino.h"
#define ST 0 // Straight
#define LGIC 1// Sharp Left
#define LOT 2 //Left
#define RGIC 3// Sharp right
#define ROT 4 // Right

#define GoSpeed 380
#define BackDelay 800
char **map;
int dx[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
int dy[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int main(void)
{
	int i, j;
	int dir = 2;
	int change = 0;
	int pile = 0;
	int set = 600;
	int x = set / 2;
	int y = set / 2;
	int temp = 0;
	int temp2 = 0;
	int temp3 = 0;
	int last, last2, last3;
	int LR;
	int count = 0;
	int isSound = 0;
	SensorData data;
	clock_t start, end;
	FILE * input;
	Open(szPort);
	Go(GoSpeed, GoSpeed);
	Steering2(5, 5);
	fopen_s(&input, "in.txt", "w");
	map = (char**)malloc(sizeof(char*)*set);
	for (i = 0; i<set; i++) {
		map[i] = (char*)malloc(sizeof(char)*set);
		memset(map[i], 0, sizeof(char)*set);
	}
	map[y][x] = 1;

	while (1) {
		start = clock();
		data = Sensor(10);
		printf("num1 %d num2 %d num3 %d  num4(right) %d num5(left) %d\n", data.IRSensor[0], data.IRSensor[1], data.IRSensor[2], data.IRSensor[3], data.IRSensor[4]);
		if (data.IRSensor[1] > 25) {
			printf("back\n");
			Go(-GoSpeed, -GoSpeed);
			delay(700);
			data = Sensor(10);
			if ((data.IRSensor[0] - data.IRSensor[2] > 200)
				|| (data.IRSensor[4] - data.IRSensor[3] > 80))
			{
				if (change == ST)
					change = ROT;
				printf("turn right 5\n");
				temp = 0;

				Go(-GoSpeed, -GoSpeed);
				Steering(1);
				delay(BackDelay);
				Go(GoSpeed, GoSpeed);
				Steering(3);
				delay(800);
				Steering2(5, 5);

			}
			else if ((data.IRSensor[2] - data.IRSensor[0] > 200)
				|| (data.IRSensor[3] - data.IRSensor[4] > 80))
			{
				if (change == ST)
					change = LOT;
				printf("turn left 5\n");
				temp = 0;

				Go(-GoSpeed, -GoSpeed);
				Steering(3);
				delay(900);
				Go(GoSpeed, GoSpeed);
				Steering(1);
				delay(800);
				Steering2(5, 5);

			}
			else if (data.IRSensor[4] - data.IRSensor[3] > 0)
			{
				if (change == ST)
					change = RGIC;
				printf("turn right \n");
				temp = 0;

				Go(-GoSpeed, -GoSpeed);
				Steering(1);
				delay(BackDelay);
				Go(GoSpeed, GoSpeed);
				Steering(3);
				delay(2100);
				Steering2(5, 5);

			}
			else if (data.IRSensor[4] - data.IRSensor[3] < 0)
			{

				if (change == ST)
					change = LGIC;
				printf("turn left \n");
				temp = 0;

				Go(-GoSpeed, -GoSpeed);
				Steering(3);
				delay(BackDelay);
				Go(GoSpeed, GoSpeed);
				Steering(1);
				delay(2100);
				Steering2(5, 5);

			}
			else if (data.IRSensor[0] - data.IRSensor[2] > 30) {
				if (change == ST)
					change = RGIC;
				printf("turn right 3\n");
				temp = 0;
				Go(-GoSpeed, -GoSpeed);
				Steering(1);
				delay(BackDelay);
				Go(GoSpeed, GoSpeed);
				Steering(3);
				delay(2100);
				Steering2(5, 5);

			}
			else if (data.IRSensor[2] - data.IRSensor[0] > 30) {
				if (change == ST)
					change = LGIC;
				printf("turn left \n");
				temp = 0;
				Go(-GoSpeed, -GoSpeed);
				Steering(3);
				delay(BackDelay);
				Go(GoSpeed, GoSpeed);
				Steering(1);
				delay(1900);
				Steering2(5, 5);
			}
			else
			{
				

				temp++;

			}

		}
		else if (data.IRSensor[1]>30 && data.IRSensor[4] - data.IRSensor[3] > 35) {

			if (change == ST)
				change = RGIC;
			printf("turn right 2\n");
			temp = 0;
			Go(-300, -300);
			Steering(1);
			delay(BackDelay);
			Go(GoSpeed, GoSpeed);
			Steering(3);
			delay(1900);
			Steering2(5, 5);

		}
		else if (data.IRSensor[1]>30 && data.IRSensor[3] - data.IRSensor[4] > 35)
		{
			if (change == ST)
				change = LGIC;
			printf("turn left \n");
			temp = 0;
			Go(-300, -300);
			Steering(3);
			delay(BackDelay);
			Go(GoSpeed, GoSpeed);
			Steering(1);
			delay(1900);
			Steering2(5, 5);
		}
		else if (data.IRSensor[4] - data.IRSensor[3]>0) {
			temp3++;
			if (change != ST&&temp3>10)
			{
				count++;
				if (change == RGIC) {
					dir += 2;
					dir %= 8;
				}
				else if (change == LGIC)
				{
					dir -= 2;
					if (dir == -1) {
						dir = 7;
					}
					else if (dir == -2) {
						dir = 6;
					}
				}
				else if (change == ROT)
				{
					dir++;
					dir %= 8;
				}
				else {
					dir--;
					if (dir == -1) {
						dir = 7;
					}
				}
				change = ST;
				temp3 = 0;
			}
			LR = (int)((data.IRSensor[4] - data.IRSensor[3])*2.5);
			if (LR > 40)
				LR = 40;
			else if (LR<15)
				LR = 15;

			Steering2(5 + LR, 5 + LR);
			delay(400);
		}
		else if (data.IRSensor[3] - data.IRSensor[4]>0) {
			temp3++;
			if (change != ST&&temp3>10)
			{
				count++;
				if (change == RGIC) {
					dir += 2;
					dir %= 8;
				}
				else if (change == LGIC)
				{
					dir -= 2;
					if (dir == -1) {
						dir = 7;
					}
					else if (dir == -2) {
						dir = 6;
					}
				}
				else if (change == ROT)
				{
					dir++;
					dir %= 8;
				}
				else {
					dir--;
					if (dir == -1) {
						dir = 7;
					}
				}
				change = ST;
				temp3 = 0;
			}
			LR = (int)((data.IRSensor[3] - data.IRSensor[4])*2.5);
			if (LR >40)
				LR = 40;
			else if (LR<10)
				LR = 15;
			Steering2(5 - LR, 5 - LR);
			delay(400);
		}
		else {
			temp3++;
			if (change != ST&&temp3>8)
			{
				count++;
				if (change == RGIC) {
					dir += 2;
					dir %= 8;
				}
				else if (change == LGIC)
				{
					dir -= 2;
					if (dir == -1) {
						dir = 7;
					}
					else if (dir == -2) {
						dir = 6;
					}
				}
				else if (change == ROT)
				{
					dir++;
					dir %= 8;
				}
				else {
					dir--;
					if (dir == -1) {
						dir = 7;
					}
				}
				change = ST;
				temp3 = 0;
			}
		}

		last = data.IRSensor[1];
		last2 = data.IRSensor[2];
		last3 = data.IRSensor[0];
		data = Sensor(10);
		end = clock();

		pile += (end - start);
		if (pile > 100) {
			int inter = pile / 100;
			//printf("pile : %d\n", inter);
			for (i = 0; i<inter; i++) {
				x += dx[dir];
				y += dy[dir];
				//printf("x %d y %d\n", x, y);
				map[y][x] = 1;
			}
			pile /= 100;
		}
		if (data.IRSensor[1] == last&&data.IRSensor[2] == last2&&data.IRSensor[0] == last3)
			temp2++;
		else
			temp2 = 0;

		if (data.IRSensor[5]>200)
			break;

		if (temp > 2) {
			printf("roll back\n");
			temp = 0;
			Go(-300, -300);
			if (data.IRSensor[3] < data.IRSensor[4])
				Steering2(-80, -80);
			else if (data.IRSensor[4] < data.IRSensor[3])
				Steering2(80, 80);
			delay(1200);

		}
		
		Go(GoSpeed, GoSpeed);
		Steering2(5, 5);
		data = Sensor(10);

	}
	Go(0, 0);
	Steering(2);
	Close();
	for (i = 0; i < set; i++) {
		for (j = 0; j < set; j++) {
			if (map[i][j] == 1)
				fprintf(input, "o");
			else
				fprintf(input, " ");
		}
		fprintf(input, "\n");
	}
	printf("count :%d\n", count);
	return 0;
}