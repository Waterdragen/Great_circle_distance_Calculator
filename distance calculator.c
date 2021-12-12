#include <stdio.h>
#include <math.h>
#include <time.h>
#define pi 3.14159265359

double radian(double deg);
double degree(double rad);
void delay(int number_of_seconds);

int main(){
	double coord[4],colatt[2],difference,angle_a=pi/2,angle_b=pi/2,dist_angle;
	char hemisphere[4]={'?','?','?','?'},yesorno='?';
	int i;
	
	for(i=0;i<4;i++){
		if(i%2==0){
			do{
				printf("Please enter #%d lattitude coordinate:\n",i/2+1);
				scanf(" %lf %[^\n]c",&coord[i],&hemisphere[i]);
			}
			while(hemisphere[i]!='n'&&hemisphere[i]!='s'||(coord[i]<0||coord[i]>180));
		}
		else{
			do{
				printf("Please enter #%d longitude coordinate:\n",i/2+1);
				scanf(" %lf %[^\n]c",&coord[i],&hemisphere[i]);
			}
			while(hemisphere[i]!='e'&&hemisphere[i]!='w'||(coord[i]<0||coord[i]>180));
		}
	}
	for(i=0;i<4;i++){
		if(i%2==0){
			if(hemisphere[i]=='s'){
				coord[i]=-1*coord[i];
			}
		}
		else if(hemisphere[i]=='w'){
			coord[i]=-1*coord[i];
		}
	}
	for(i=0;i<4;i++){
		coord[i]=coord[i]/180*pi;
	}
	colatt[0]=(pi/2-coord[0]);
	colatt[1]=(pi/2-coord[2]);
	if(coord[3]>coord[1]){
		difference=(coord[3]-coord[1]);
	}
	else{
		difference=(coord[1]-coord[3]);
	}
	
	if(difference>pi){
		difference=2*pi-difference;
	}
	
	dist_angle=acos(cos(colatt[0])*cos(colatt[1])+sin(colatt[0])*sin(colatt[1])*cos(difference));
	if(round(dist_angle*100)/100!=0){
		angle_a=asin(sin(difference)/sin(dist_angle)*sin(colatt[1]));
		angle_b=asin(sin(difference)/sin(dist_angle)*sin(colatt[0]));
	}
	printf("\nGreat circle distance = %.4lf (km)\n",6370*dist_angle);
	if((angle_a+angle_b+difference)/pi*180-180<0){
		if(colatt[0]<colatt[1]){
			angle_a=pi-angle_a;
		}
		else{
			angle_b=pi-angle_b;
		}
	}
	printf("angle a = %.4lf\n",angle_a/pi*180);
	printf("angle b = %.4lf\n",angle_b/pi*180);
	printf("angle c = %.4lf\n",difference/pi*180);
	printf("Spherical excess = %.4lf\n",(angle_a+angle_b+difference)/pi*180-180);
	
	do{
		printf("Show steps? [y/n] ");
		scanf(" %[^\n]c",&yesorno);
	}
	while(yesorno!='y'&&yesorno!='n');
	if(yesorno=='y'){
		printf("\n");
		if(hemisphere[0]!='s'){
			printf("#1 co-lattitude = 90-%.4lf = %.4lf\n",degree(coord[0]),degree(colatt[0]));
		}
		else{
			printf("#1 co-lattitude = 90-(%.4lf) = %.4lf\n",degree(coord[0]),degree(colatt[0]));
		}
		if(hemisphere[2]!='s'){
			printf("#2 co-lattitude = 90-%.4lf = %.4lf\n",degree(coord[2]),degree(colatt[1]));
		}
		else{
			printf("#2 co-lattitude = 90-(%.4lf) = %.4lf\n",degree(coord[2]),degree(colatt[1]));
		}
		if(coord[3]>coord[1]){
			if(hemisphere[1]!='w'&&hemisphere[3]!='w'){
				printf("longitude difference = %.4lf-%.4lf = %.4lf\n",degree(coord[3]),degree(coord[1]),degree(difference));
			}
			else if(hemisphere[1]=='w'&&hemisphere[3]!='w'){
				printf("longitude difference = %.4lf-(%.4lf) = %.4lf\n",degree(coord[3]),degree(coord[1]),degree(difference));
			}
			else{
				printf("longitude difference = (%.4lf)-(%.4lf) = %.4lf\n",degree(coord[3]),degree(coord[1]),degree(difference));
			}
		}
		else{
			if(hemisphere[1]!='w'&&hemisphere[3]!='w'){
				printf("longitude difference = %.4lf-%.4lf = %.4lf\n",degree(coord[1]),degree(coord[3]),degree(difference));
			}
			else if(hemisphere[1]!='w'&&hemisphere[3]=='w'){
				printf("longitude difference = %.4lf-(%.4lf) = %.4lf\n",degree(coord[1]),degree(coord[3]),degree(difference));
			}
			else{
				printf("longitude difference = (%.4lf)-(%.4lf) = %.4lf\n\n",degree(coord[1]),degree(coord[3]),degree(difference));
			}
		}
		printf("cos(c) = cos(%.4lf)cos(%.4lf)+sin(%.4lf)sin(%.4lf)cos(%.4lf)\n"
		,degree(colatt[1]),degree(colatt[0]),degree(colatt[1]),degree(colatt[0]),degree(difference));
		printf("    c = %.4lf = %.4lf rad\n",degree(dist_angle),dist_angle);
		printf("Great circle distance = 6370km x %.4lf = %.4lf km\n\n",dist_angle,6370*dist_angle);
		printf("sin(a)/sin(%.4lf)=sin(%.4lf)/sin(%.4lf)\n",degree(colatt[1]),degree(difference),degree(dist_angle));
		printf("    a = %.4lf %.4lf(rej)\n",degree(angle_a),180-degree(angle_a));
		printf("sin(b)/sin(%.4lf)=sin(%.4lf)/sin(%.4lf)\n",degree(colatt[0]),degree(difference),degree(dist_angle));
		printf("    b = %.4lf %.4lf(rej)\n",degree(angle_b),180-degree(angle_b));
		printf("Sphrical excess = %.4lf + %.4lf + %.4lf - 180 = %.4lf\n"
		,degree(angle_a),degree(angle_b),degree(difference),degree(angle_a+angle_b+difference)-180);
		delay(300);
	}
	
	return 0;
}

double radian(double deg){
	deg=deg/180*pi;
	return deg;
}
double degree(double rad){
	rad=rad/pi*180;
	return rad;
}
void delay(int number_of_seconds){
    int milli_seconds = 1000 * number_of_seconds;
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds)
        ;
}
