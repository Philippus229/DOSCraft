#include<graphics.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<bios.h>
#include<dos.h>

#define ARROW_LEFT 0x4B
#define ARROW_RIGHT 0x4D
#define ARROW_UP 0x48
#define ARROW_DOWN 0x50

const char KEY_W = 'w';
const char KEY_S = 's';
const char KEY_A = 'a';
const char KEY_D = 'd';

const double PI = 3.14159265;
const int height = 480;
const int width = 640;
const int nob = 1;
double blockMap[1][3] = {{0,0,2}};
double camPos[3] = {0,0,0};
double camRot[2] = {0,0};

double my_sin(double x) {
	return sin((x*PI)/180);
}

double my_cos(double x) {
	return cos((x*PI)/180);
}

int initDone = 0;

int main() {
	int gd=DETECT, gm, errorcode;
	initgraph(&gd,&gm,"c:\\turboc3\\bgi");
	errorcode = graphresult();
	if (errorcode != grOk) {
		printf("Graphics error: %s\n", grapherrormsg(errorcode));
		printf("Press any key to halt:");
		getch();
		exit(1);
	}
	while(1) {
		int key;
		//char key;
		if(initDone == 1) {
			key = bioskey(0);
			//key = getch();
			if((key & 0x00FF) > 0) {
				key = key & 0x00FF;
			} else {
				key = (key & 0xFF00) >> 8;
			}
		} else {
			initDone = 1;
		}
		if(key == KEY_W) {
			camPos[0] += (my_sin(camRot[1])*0.05);
			camPos[2] += (my_cos(camRot[1])*0.05);
		}
		if(key == KEY_S) {
			camPos[0] -= (my_sin(camRot[1])*0.05);
			camPos[2] -= (my_cos(camRot[1])*0.05);
		}
		if(key == ARROW_LEFT) {
			camRot[1] -= 1;
		}
		if(key == ARROW_RIGHT) {
			camRot[1] += 1;
		}
		if(key == ARROW_UP) {
			camRot[0] += 1;
		}
		if(key == ARROW_DOWN) {
			camRot[0] -= 1;
		}
		if(camRot[1] > 360) {
			camRot[1] -= 360;
		} else if(camRot[1] < 0) {
			camRot[1] += 360;
		}
		if(camRot[0] > 360) {
			camRot[0] -= 360;
		} else if(camRot[0] < 0) {
			camRot[0] += 360;
		}
		cleardevice();
		for(int i = 0; i < nob; i++) {
			double block_tmp[3] = {blockMap[i][0],blockMap[i][1],blockMap[i][2]};
			double p0[3] = {block_tmp[0]-0.5,block_tmp[1]+0.5,block_tmp[2]-0.5};
			double p1[3] = {block_tmp[0]-0.5,block_tmp[1]-0.5,block_tmp[2]-0.5};
			double p2[3] = {block_tmp[0]+0.5,block_tmp[1]+0.5,block_tmp[2]-0.5};
			double p3[3] = {block_tmp[0]+0.5,block_tmp[1]-0.5,block_tmp[2]-0.5};
			double p4[3] = {block_tmp[0]+0.5,block_tmp[1]+0.5,block_tmp[2]+0.5};
			double p5[3] = {block_tmp[0]+0.5,block_tmp[1]-0.5,block_tmp[2]+0.5};
			double p6[3] = {block_tmp[0]-0.5,block_tmp[1]+0.5,block_tmp[2]+0.5};
			double p7[3] = {block_tmp[0]-0.5,block_tmp[1]-0.5,block_tmp[2]+0.5};
			for(int i2 = 0; i2 < 9; i2++) {
				double pTmp[3] = {0,0,0};
				if (i2 == 0) {
					pTmp[0] = p0[0];
					pTmp[1] = p0[1];
					pTmp[2] = p0[2];
				} else if (i2 == 1) {
					pTmp[0] = p1[0];
					pTmp[1] = p1[1];
					pTmp[2] = p1[2];
				} else if (i2 == 2) {
					pTmp[0] = p2[0];
					pTmp[1] = p2[1];
					pTmp[2] = p2[2];
				} else if (i2 == 3) {
					pTmp[0] = p3[0];
					pTmp[1] = p3[1];
					pTmp[2] = p3[2];
				} else if (i2 == 4) {
					pTmp[0] = p4[0];
					pTmp[1] = p4[1];
					pTmp[2] = p4[2];
				} else if (i2 == 5) {
					pTmp[0] = p5[0];
					pTmp[1] = p5[1];
					pTmp[2] = p5[2];
				} else if (i2 == 6) {
					pTmp[0] = p6[0];
					pTmp[1] = p6[1];
					pTmp[2] = p6[2];
				} else if (i2 == 7) {
					pTmp[0] = p7[0];
					pTmp[1] = p7[1];
					pTmp[2] = p7[2];
				} else if (i2 == 8) {
					pTmp[0] = block_tmp[0];
					pTmp[1] = block_tmp[1];
					pTmp[2] = block_tmp[2];
				}
				double blockPosXRTC = ((my_cos(camRot[1])*(pTmp[0]-camPos[0]))-(my_sin(camRot[1])*(pTmp[2]-camPos[2])));
				double blockPosZRTC = ((my_cos(camRot[1])*(pTmp[2]-camPos[2]))+(my_sin(camRot[1])*(pTmp[0]-camPos[0])));
				double blockPosYRTC = -((my_cos(camRot[0])*(pTmp[1]-camPos[1]))-(my_sin(camRot[0])*blockPosZRTC));
				blockPosZRTC = ((my_cos(camRot[0])*blockPosZRTC)+(my_sin(camRot[0])*(pTmp[1]-camPos[1])));
				if (i2 == 0) {
					p0[0] = blockPosXRTC;
					p0[1] = blockPosYRTC;
					p0[2] = blockPosZRTC;
				} else if (i2 == 1) {
					p1[0] = blockPosXRTC;
					p1[1] = blockPosYRTC;
					p1[2] = blockPosZRTC;
				} else if (i2 == 2) {
					p2[0] = blockPosXRTC;
					p2[1] = blockPosYRTC;
					p2[2] = blockPosZRTC;
				} else if (i2 == 3) {
					p3[0] = blockPosXRTC;
					p3[1] = blockPosYRTC;
					p3[2] = blockPosZRTC;
				} else if (i2 == 4) {
					p4[0] = blockPosXRTC;
					p4[1] = blockPosYRTC;
					p4[2] = blockPosZRTC;
				} else if (i2 == 5) {
					p5[0] = blockPosXRTC;
					p5[1] = blockPosYRTC;
					p5[2] = blockPosZRTC;
				} else if (i2 == 6) {
					p6[0] = blockPosXRTC;
					p6[1] = blockPosYRTC;
					p6[2] = blockPosZRTC;
				} else if (i2 == 7) {
					p7[0] = blockPosXRTC;
					p7[1] = blockPosYRTC;
					p7[2] = blockPosZRTC;
				} else if (i2 == 8) {
					block_tmp[0] = blockPosXRTC;
					block_tmp[1] = blockPosYRTC;
					block_tmp[2] = blockPosZRTC;
				}
			}
			if(block_tmp[0]/block_tmp[2] > -1.25 && block_tmp[0]/block_tmp[2] < 1.25 && block_tmp[1]/block_tmp[2] > -1 && block_tmp[1]/block_tmp[2] < 1) {
				double p00[2] = {(width/2)+((p0[0]/p0[2])*(height/2)), (height/2)+((p0[1]/p0[2])*(height/2))};
				double p01[2] = {(width/2)+((p1[0]/p1[2])*(height/2)), (height/2)+((p1[1]/p1[2])*(height/2))};
				double p02[2] = {(width/2)+((p2[0]/p2[2])*(height/2)), (height/2)+((p2[1]/p2[2])*(height/2))};
				double p03[2] = {(width/2)+((p3[0]/p3[2])*(height/2)), (height/2)+((p3[1]/p3[2])*(height/2))};
				double p04[2] = {(width/2)+((p4[0]/p4[2])*(height/2)), (height/2)+((p4[1]/p4[2])*(height/2))};
				double p05[2] = {(width/2)+((p5[0]/p5[2])*(height/2)), (height/2)+((p5[1]/p5[2])*(height/2))};
				double p06[2] = {(width/2)+((p6[0]/p6[2])*(height/2)), (height/2)+((p6[1]/p6[2])*(height/2))};
				double p07[2] = {(width/2)+((p7[0]/p7[2])*(height/2)), (height/2)+((p7[1]/p7[2])*(height/2))};
				setcolor(WHITE);
				line(p00[0], p00[1], p02[0], p02[1]);
				line(p02[0], p02[1], p03[0], p03[1]);
				line(p01[0], p01[1], p03[0], p03[1]);
				line(p02[0], p02[1], p04[0], p04[1]);
				line(p04[0], p04[1], p05[0], p05[1]);
				line(p03[0], p03[1], p05[0], p05[1]);
				line(p04[0], p04[1], p06[0], p06[1]);
				line(p06[0], p06[1], p07[0], p07[1]);
				line(p05[0], p05[1], p07[0], p07[1]);
				line(p06[0], p06[1], p00[0], p00[1]);
				line(p00[0], p00[1], p01[0], p01[1]);
				line(p07[0], p07[1], p01[0], p01[1]);
			}
		}
	}
	closegraph();
	return(0);
}