
#include "stdafx.h"
#include "math.h"

#ifndef GLOBAL_DEF
#define GLOBAL_DEF
#include "GlobalDef.h"
#endif

int LeftRightPairs[NO_PAIRS] = { 6,8,10,12,19,21,23,25,27,29,31,33,35,37,39,41,
								 53,55,57,59,61,63,65,67};

int LRP_GROUP[10] = { 0,4,10,14,16,16,16,20,22,24 };

extern float  points_orig[NO_POINTS][3]; 
extern float  pts[NO_POINTS][3]; 
extern int    vertx[NO_VERTX][4];
extern float  norms[NO_POINTS][3];

float  irisd;
float  es;
float  ens;
float  mns;
float  mw;
float  au;

float eyelid_radius_left   = EYELID_RADIUS;
float eyelid_radius_right  = EYELID_RADIUS;

float  faps[NO_FAPS+1];

void GetFapUnits(void)
{
  irisd = (points_orig[213][Y]-points_orig[191][Y])/1024;

  es    = (points_orig[553][X]-points_orig[681][X])/1024;
  ens   = (points_orig[553][Y]-points_orig[86][Y])/1024;
  mns   = (points_orig[86][Y]-points_orig[60][Y])/1024;
  mw    = (points_orig[69][X]-points_orig[345][X])/1024;

  au    = 5e-4f;
}

void Open_Jaw(void)
{
	int counter;
	float dislocation_x,dislocation_y,factor_x;
	
	if(!faps[3])	return;
	
	factor_x = 4;
	
	dislocation_y = faps[3]*mns;
	dislocation_x = dislocation_y/factor_x;
	
	/* teeth down */
	
	for(counter=254;counter<=285;counter++) 
		pts[counter][Y]-=1.1*dislocation_y;
	
	for(counter=516;counter<=547;counter++) 
		pts[counter][Y]-=1.1*dislocation_y;
	
	
	/*chin*/
	
	for(counter=5;counter<=9;counter++)
		pts[counter][Y]-=dislocation_y*0.75;
	
	for(counter=10;counter<=14;counter++)
		pts[counter][Y]-=dislocation_y*0.75;
	
	pts[15][Y]-=dislocation_y;
	for(counter=16;counter<=21;counter++){
		pts[counter][X]-=dislocation_x;
		pts[counter][Y]-=dislocation_y;
	}
	pts[22][Y]-=dislocation_y;
	for(counter=23;counter<=29;counter++){
		pts[counter][X]-=dislocation_x;
		pts[counter][Y]-=dislocation_y;
	}
	pts[30][Y]-=dislocation_y;
	for(counter=31;counter<=32;counter++){
		pts[counter][X]-=dislocation_x;
		pts[counter][Y]-=dislocation_y;
	}
	pts[33][Y]-=dislocation_y;
	for(counter=34;counter<=39;counter++){
		pts[counter][X]-=dislocation_x;
		pts[counter][Y]-=dislocation_y;
	}
	pts[40][Y]-=dislocation_y;
	for(counter=41;counter<=42;counter++){
		pts[counter][X]-=dislocation_x;
		pts[counter][Y]-=dislocation_y;
	}
	
	for(counter=43;counter<=47;counter++)
		pts[counter][Y]-=dislocation_y*0.15;
	
	
	for(counter=296;counter<=299;counter++)
		pts[counter][Y]-=dislocation_y*0.75;
	
	for(counter=300;counter<=302;counter++)
		pts[counter][Y]-=dislocation_y*0.75;
	
	for(counter=303;counter<=325;counter++){
		pts[counter][X]+=dislocation_x;
		pts[counter][Y]-=dislocation_y;
	}
	
	for(counter=326;counter<=330;counter++)
		pts[counter][Y]-=dislocation_y*0.15;
}

//void Lower_Top_Midlip(void)
void Fap_51(void)	
{
	if(!faps[51])	return;

	pts[66][Y]-=faps[51]*mns;
	pts[63][Y]-=0.5*faps[51]*mns;
	pts[70][Y]-=0.5*faps[51]*mns;
}
void Fap_4(void)	
{
	if(!faps[4])	return;
	
	pts[60][Y]-=faps[4]*mns;
	pts[63][Y]-=0.5*faps[4]*mns;
}

//void Raise_Bottom_Midlip(void)
void Fap_5(void)	
{
	if(!faps[5])	return;
	
	pts[57][Y]+=faps[5]*mns;
	pts[54][Y]+=0.75*faps[5]*mns;
	pts[51][Y]+=0.25*faps[5]*mns;
}
void Fap_52(void)	
{
	if(!faps[52])	return;
	
	pts[40][Y]+=0.25*faps[52]*mns;  
	pts[48][Y]+=faps[52]*mns;
	pts[51][Y]+=0.75*faps[52]*mns;
	pts[54][Y]+=0.25*faps[52]*mns;
}

//void Stretch_Cornerlip(void)
void Fap_53(void)
{
	int counter;
	int points_ext_left[10] = { 69,43,68,65,67,64,53,50,52,49 };
	float perc_ext[10]     = { 1.0f,0.6f,0.6f,0.3f,0.5f,0.25f,0.5f,0.5f,0.4f,0.4f };

	if(!faps[53])	return;
	
	for(counter=0;counter<10;counter++)
	{
		pts[points_ext_left[counter]][X]+=perc_ext[counter]*faps[53]*mw;
		pts[points_ext_left[counter]][Z]-=0.6*perc_ext[counter]*faps[53]*mw;
	}
}
void Fap_54(void)
{
	int counter;
	int points_ext_right[10] = { 345,326,344,342,343,341,334,332,333,331 };
	float perc_ext[10]     = { 1.0f,0.6f,0.6f,0.3f,0.5f,0.25f,0.5f,0.5f,0.4f,0.4f };

	if(!faps[54])	return;
	
	for(counter=0;counter<10;counter++)
	{
		pts[points_ext_right[counter]][X]-=perc_ext[counter]*faps[54]*mw;
		pts[points_ext_right[counter]][Z]-=0.6*perc_ext[counter]*faps[54]*mw;
	}
}
void Fap_6(void)
{
	int counter;
	int points_int_left[9]	= { 286,62,65,61,64,59,56,58,55 };
	float perc_int[9]		= { 1.0f,0.6f,0.3f,0.5f,0.25,0.5f,0.5f,0.4f,0.4f };

	if(!faps[6])	return;

	for(counter=0;counter<9;counter++)
	{
		pts[points_int_left[counter]][X]+=perc_int[counter]*faps[6]*mw;
		pts[points_int_left[counter]][Z]-=0.6*perc_int[counter]*faps[6]*mw;
	}
}
void Fap_7(void)
{
	int counter;
	int points_int_right[9]	= { 548,340,342,339,341,338,336,337,335 };
	float perc_int[9]		= { 1.0f,0.6f,0.3f,0.5f,0.25,0.5f,0.5f,0.4f,0.4f };

	if(!faps[7])	return;
	
	for(counter=0;counter<9;counter++)
	{
		pts[points_int_right[counter]][X]-=perc_int[counter]*faps[7]*mw;
		pts[points_int_right[counter]][Z]-=0.6*perc_int[counter]*faps[7]*mw;
	}
}

void Thrust_Jaw(void)
{
	int counter;
	
	int points_l0[11]  = { 13,14,17,24,35,36,302,304,310,319,320 };
	int points_l1[19]  = { 15,16,22,23,30,31,32,33,34,40,41,42,
		303,309,316,317,318,324,325 };
	
	float perc[2]      = { 0.5,1.0 };
	
	float dislocation   = faps[14]*mns;
	
	if(!faps[14])	return;
	
	/* bottom teeth */
	
	for(counter=254;counter<=285;counter++) 
		pts[counter][Z]+=dislocation;
	
	for(counter=516;counter<=547;counter++) 
		pts[counter][Z]+=dislocation;
	
	/* chin */
	
	for(counter=0;counter<11;counter++)
		pts[points_l0[counter]][Z]+=perc[0]*dislocation;
	
	for(counter=0;counter<19;counter++)
		pts[points_l1[counter]][Z]+=perc[1]*dislocation;
}

//void Lower_Top_Lip_Midpoint(void)
void Fap_55(void)
{
	int counter;
	int points_ext_left[6] = { 67,68,64,65,71,72 };
	float perc_ext[6]     = { 1.0f,0.9f,0.5f,0.45f,0.5f,0.45f };
	
	if(!faps[55])	return;
	
	for(counter=0;counter<6;counter++)
	{
		pts[points_ext_left[counter]][Y]-=perc_ext[counter]*faps[55]*mns;
	}
}
void Fap_56(void)
{
	int counter;
	int points_ext_right[6] = { 343,344,341,342,346,347 };
	float perc_ext[6]     = { 1.0f,0.9f,0.5f,0.45f,0.5f,0.45f };
	
	if(!faps[56])	return;
	
	for(counter=0;counter<6;counter++)
	{
		pts[points_ext_right[counter]][Y]-=perc_ext[counter]*faps[56]*mns;
	}
}
void Fap_8(void)
{
	int counter;
	int points_int_left[4] = { 61,62,64,65 };
	float perc_int[4]     = { 1.0f,0.9f,0.5f,0.45f };
	
	if(!faps[8])	return;
	
	for(counter=0;counter<4;counter++)
	{
		pts[points_int_left[counter]][Y]-=perc_int[counter]*faps[8]*mns;
	}
}
void Fap_9(void)
{
	int counter;
	int points_int_right[4] = { 339,340,341,342 };
	float perc_int[4]     = { 1.0f,0.9f,0.5f,0.45f };
	
	if(!faps[9])	return;
	
	for(counter=0;counter<4;counter++)
	{
		pts[points_int_right[counter]][Y]-=perc_int[counter]*faps[9]*mns;
	}
}

//void Raise_Bottom_Lip_Midpoint(void)
void Fap_57(void)
{
	int counter;
	int points_ext_left[6] = { 49,50,52,53,41,42 };
	float perc_ext[6]      = { 1.0f,0.9f,1.0f,0.9f,0.25f,0.2f };
	
	if(!faps[57])	return;
	
	for(counter=0;counter<6;counter++)
	{
		pts[points_ext_left[counter]][Y]+=perc_ext[counter]*faps[57]*mns;
	}
}
void Fap_58(void)
{
	int counter;
	int points_ext_right[6] = { 331,332,333,334,324,325 };
	float perc_ext[6]       = { 1.0f,0.9f,1.0f,0.9f,0.25f,0.2f };
	
	if(!faps[58])	return;
	
	for(counter=0;counter<6;counter++)
	{
		pts[points_ext_right[counter]][Y]+=perc_ext[counter]*faps[58]*mns;
	}
}
void Fap_10(void)
{
	int counter;
	int points_int_left[4] = { 58,59,55,56 };
	float perc_int[4]      = { 1.0f,0.9f,1.0f,0.9f };
	
	if(!faps[10])	return;
	
	for(counter=0;counter<4;counter++)
	{
		pts[points_int_left[counter]][Y]+=perc_int[counter]*faps[10]*mns;
	}
}
void Fap_11(void)
{
	int counter;
	int points_int_right[4] = { 337,338,335,336 };
	float perc_int[4]         = { 1.0f,0.9f,1.0f,0.9f };
	
	if(!faps[11])	return;
	
	for(counter=0;counter<4;counter++)
	{
		pts[points_int_right[counter]][Y]+=perc_int[counter]*faps[11]*mns;
	}
}

//void Raise_Cornerlip(void)
void Fap_59(void)
{
	if(!faps[59])	return;

	pts[69][Y]+=faps[59]*mns;
	pts[43][Y]+=0.9*faps[59]*mns;
	pts[42][Y]+=0.3*faps[59]*mns;
}	
void Fap_12(void)
{
	if(!faps[12])	return;
	
	pts[286][Y]+=faps[12]*mns;
}	
void Fap_60(void)
{
	if(!faps[60])	return;
	
	pts[345][Y]+=faps[60]*mns;
	pts[326][Y]+=0.9*faps[60]*mns;
	pts[325][Y]+=0.3*faps[60]*mns;
}
void Fap_13(void)
{
	if(!faps[13])	return;
	
	pts[548][Y]+=faps[13]*mns;
}

void Shift_Jaw(void)
{
	int counter;
	
	int points_l0[11] = { 10,11,12,19,27,39,300,301,306,313,323 };
	int points_l1[16] = { 18,26,38,43,44,45,46,47,305,312,322,326,327,
		328,329,330 };  
	int points_l2[9]  = { 13,14,17,25,37,302,304,311,321 };  
	int points_l3[4]  = { 35,36,319,320 };  
	int points_l4[6]  = { 16,24,32,303,310,317 };  
	int points_l5[15] = { 15,22,23,30,31,33,34,40,41,42,309,
		316,318,324,325};  
	float perc[6]     = { 0.1f,0.2f,0.3f,0.55f,0.7f,1.0f };
	
	float dislocation  = faps[15]*mns;
	
	
	if(!faps[15])	return;
	
	/* bottom teeth */
	
	for(counter=254;counter<=285;counter++) 
		pts[counter][X]-=dislocation;
	
	for(counter=516;counter<=547;counter++) 
		pts[counter][X]-=dislocation;
	
	
	/* chin */
	
	for(counter=0;counter<11;counter++)
		pts[points_l0[counter]][X]-=perc[0]*dislocation;
	
	for(counter=0;counter<16;counter++)
		pts[points_l1[counter]][X]-=perc[1]*dislocation;
	
	for(counter=0;counter<9;counter++)
		pts[points_l2[counter]][X]-=perc[2]*dislocation;
	
	for(counter=0;counter<4;counter++)
		pts[points_l3[counter]][X]-=perc[3]*dislocation;
	
	for(counter=0;counter<6;counter++)
		pts[points_l4[counter]][X]-=perc[4]*dislocation;
	
	for(counter=0;counter<15;counter++)
		pts[points_l5[counter]][X]-=perc[5]*dislocation;
}

void Depress_Chin(void)
{
	int counter;
	
	if(!faps[18])	return;
	
	for(counter=10;counter<=39;counter++)
		pts[counter][Y]+=faps[18]*mns;
	
	for(counter=301;counter<=323;counter++)
		pts[counter][Y]+=faps[18]*mns;
	
}

//void Push_Lip(void)
void Fap_17(void)
{
	int counter;
	int points_top[15] = { 344,343,66,67,68,342,341,63,64,65,
		340,339,60,61,62 };
	float perc_top[15] = { 0.3f,0.4f,0.4f,0.4f,0.3f,0.9f,1.0f,1.0f,1.0f,0.9f,
		0.3f,0.4f,0.4f,0.4f,0.3f };
	
	if(!faps[17])	return;

	for(counter=0;counter<15;counter++) 
		pts[points_top[counter]][Z]+=perc_top[counter]*faps[17]*mns;
}
void Fap_16(void)
{
	int counter;
	int points_bottom[20] = { 338,337,57,58,59,336,335,54,55,56,
		334,333,51,52,53,332,331,48,49,50 };  
	float perc_bottom[20] = { 0.3f,0.4f,0.4f,0.4f,0.3f,0.9f,1.0f,1.0f,1.0f,0.9f,
		0.9f,1.0f,1.0f,1.0f,0.9f,0.3f,0.4f,0.4f,0.4f,0.3f };

	if(!faps[16])	return;
	
	for(counter=0;counter<20;counter++)  
		pts[points_bottom[counter]][Z]+=perc_bottom[counter]*faps[16]*mns;
}

void Close_Top_Left_Eyelid(void)
{
	int   counter,a;
	float center_x,center_y,center_z;
	float step,alfa,x,y,z;
	float dislocation_top,deslocamento,disloc_max;
	
	if(!faps[19])	return;
	
	disloc_max = pts[198][Y] - pts[191][Y];
	
	dislocation_top = pts[198][Y] - pts[213][Y] + faps[19]*irisd ;
	
	if(dislocation_top>disloc_max) dislocation_top=disloc_max;
	if(dislocation_top<0) dislocation_top=0;
	
	center_x    = points_orig[553][X];
	center_y    = points_orig[553][Y];
	center_z    = points_orig[553][Z] - 0.9*eyelid_radius_left;
	
	step = 0.4f;
	
	for(counter=202;counter<=212;counter+=5) {
		for(a=counter;a<=counter+3;a++) {
			
			deslocamento = pts[198][Y] - dislocation_top*step - center_y;      
			alfa = asin(deslocamento/eyelid_radius_left); 
			x = pts[a][X] - center_x;
			z = sqrt( (sqr(eyelid_radius_left)-sqr(x)) / (sqr(tan(alfa))*sin(alfa)+cos(alfa)) );
			y = z*tan(alfa);
			pts[a][Y] = y + center_y;
			pts[a][Z] = z + center_z;
			
		}
		step+=0.3f;
	}
	
	for(counter=202;counter<=212;counter+=5) 
		for(a=counter;a<=counter+3;a++)
			if(pts[a][Y]>pts[197+a-counter][Y]) {
				pts[a][Y] = pts[197+a-counter][Y] - 5;
				pts[a][Z] = center_z + sqrt(sqr(eyelid_radius_left) - 
					sqr(pts[a][X] - center_x) - 
					sqr(pts[a][Y] - center_y) );
			}
			
}

void Close_Top_Right_Eyelid(void)
{
	int counter,a;
	float center_x,center_y,center_z;
	float step,alfa,x,y,z;
	float dislocation_top,deslocamento,disloc_max;
	
	if(!faps[20])	return;
	
	disloc_max = pts[460][Y] - pts[453][Y];
	
	dislocation_top = pts[460][Y] - pts[475][Y] + faps[20]*irisd;
	
	if(dislocation_top>disloc_max) dislocation_top=disloc_max;
	if(dislocation_top<0) dislocation_top=0;
	
	
	center_x    = points_orig[681][X];
	center_y    = points_orig[681][Y];
	center_z    = points_orig[681][Z] - 0.9*eyelid_radius_right;
	
	step = 0.4f;
	
	for(counter=464;counter<=474;counter+=5) {
		for(a=counter;a<=counter+3;a++) {
			deslocamento = pts[460][Y] - dislocation_top*step - center_y;      
			alfa = asin(deslocamento/eyelid_radius_right); 
			x = pts[a][X] - center_x;
			z = sqrt((sqr(eyelid_radius_right)-sqr(x))/(sqr(tan(alfa))*sin(alfa) +
				cos(alfa)));
			y = z*tan(alfa);
			pts[a][Y] = y + center_y;
			pts[a][Z] = z + center_z;
		}
		step+=0.3f;
	}
	
	for(counter=464;counter<=474;counter+=5) 
		for(a=counter;a<=counter+3;a++)
			if(pts[a][Y]>pts[459+a-counter][Y])
			{
				pts[a][Y] = pts[459+a-counter][Y] - 5;
				pts[a][Z] = center_z + sqrt(sqr(eyelid_radius_right)
					-sqr(pts[a][X] - center_x)
					-sqr(pts[a][Y] - center_y));
			}
}

void Close_Bottom_Left_Eyelid(void)
{
	int   counter,a;
	float center_x,center_y,center_z;
	float alfa,x,y,z;
	float dislocation_bottom,deslocamento,disloc_max,disloc_min;
	
	if(!faps[21])	return;
	
	disloc_max = pts[213][Y] - pts[191][Y];
	disloc_min = pts[185][Y] - pts[191][Y];
	
	dislocation_bottom = faps[21]*irisd;
	
	if(dislocation_bottom>disloc_max) dislocation_bottom=disloc_max;
	if(dislocation_bottom<disloc_min) dislocation_bottom=disloc_min;
	
	
	center_x    = points_orig[553][X];
	center_y    = points_orig[553][Y];
	center_z    = points_orig[553][Z] - 0.9*eyelid_radius_left;
	
	deslocamento = pts[191][Y] + dislocation_bottom - center_y;
	alfa = asin(deslocamento/eyelid_radius_left);
	y	 = pts[191][Y] + dislocation_bottom;
	
	for(counter=189;counter<=193;counter++) {
		if(pts[counter][Y]<y) {
			pts[counter][Y] = y;
			x = pts[counter][X] - center_x;
			z = sqrt((sqr(eyelid_radius_left)-sqr(x))/(sqr(tan(alfa))*sin(alfa)+cos(alfa)));
			pts[counter][Z] = z + center_z;
		}
	}
	
	for(counter=189;counter<=193;counter++) 
		if(pts[counter][Y]<pts[counter-6][Y]) 
			for(a=X;a<=Z;a++)
				pts[counter][a] = pts[counter-6][a];
			
}

void Close_Bottom_Right_Eyelid(void)
{
	int   counter,a;
	float center_x,center_y,center_z;
	float alfa,x,y,z;
	float dislocation_bottom,deslocamento,disloc_max,disloc_min;
	
	if(!faps[22])	return;
	
	
	disloc_max = pts[475][Y] - pts[453][Y];
	disloc_min = pts[447][Y] - pts[453][Y];
	
	dislocation_bottom = faps[22]*irisd;
	
	if(dislocation_bottom>disloc_max) dislocation_bottom=disloc_max;
	if(dislocation_bottom<disloc_min) dislocation_bottom=disloc_min;
	
	
	center_x    = points_orig[681][X];
	center_y    = points_orig[681][Y];
	center_z    = points_orig[681][Z] - 0.9*eyelid_radius_right;
	
	deslocamento = pts[453][Y] + dislocation_bottom - center_y;
	alfa = asin(deslocamento/eyelid_radius_right);
	y    = pts[453][Y] + dislocation_bottom;
	
	for(counter=451;counter<=455;counter++) {
		if(pts[counter][Y]<y) {
			pts[counter][Y] = y;
			x = pts[counter][X] - center_x;
			z = sqrt((sqr(eyelid_radius_right)-sqr(x))/(sqr(tan(alfa))*sin(alfa)+cos(alfa)));
			pts[counter][Z] = z + center_z;
		}
	}
	
	for(counter=451;counter<=455;counter++) 
		if(pts[counter][Y]<pts[counter-6][Y]) 
			for(a=X;a<=Z;a++)
				pts[counter][a]=pts[counter-6][a];
}

void Yaw_Left_Eyeball(void)
{
	int counter;
	float d,angle_alfa,angle_beta;
	float eyex,eyez;
	
	if(!faps[23])	return;
	
	eyex = points_orig[553][X];
	eyez = points_orig[649][Z];
	
	angle_alfa = faps[23]*au;
	
	for(counter=553;counter<=680;counter++) {
		d = sqrt( sqr(pts[counter][X] - eyex) + sqr(pts[counter][Z] - eyez) );
		angle_beta = atan2((pts[counter][X] - eyex),(pts[counter][Z] - eyez));
		pts[counter][X] = eyex + d*sin(angle_alfa+angle_beta);
		pts[counter][Z] = eyez + d*cos(angle_alfa+angle_beta);
	}
	
}

void Yaw_Right_Eyeball(void)
{
	int counter;
	float d,angle_alfa,angle_beta;
	float eyex,eyez;
	
	if(!faps[24])	return;
	
	eyex = points_orig[681][X];
	eyez = points_orig[777][Z];
	
	angle_alfa = faps[24]*au;
	
	for(counter=681;counter<=808;counter++) {
		d = sqrt( sqr(pts[counter][X] - eyex) + sqr(pts[counter][Z] - eyez) );
		angle_beta = atan2((pts[counter][X] - eyex),(pts[counter][Z] - eyez));
		pts[counter][X] = eyex + d*sin(angle_alfa+angle_beta);
		pts[counter][Z] = eyez + d*cos(angle_alfa+angle_beta);
	}
	
}

void Pitch_Left_Eyeball(void)
{
	int counter;
	float d,angle_alfa,angle_beta;
	float eyey,eyez;
	
	if(!faps[25])	return;
	
	eyey = points_orig[553][Y];
	eyez = points_orig[649][Z];
	
	angle_alfa = -faps[25]*au;
	
	for(counter=553;counter<=680;counter++) {
		d = sqrt( sqr(pts[counter][Y] - eyey) + sqr(pts[counter][Z] - eyez) );
		angle_beta = atan2((pts[counter][Y] - eyey),(pts[counter][Z] - eyez));
		pts[counter][Y] = eyey + d*sin(angle_alfa+angle_beta);
		pts[counter][Z] = eyez + d*cos(angle_alfa+angle_beta);
	}
	
}

void Pitch_Right_Eyeball(void)
{
	int counter;
	float d,angle_alfa,angle_beta;
	float eyey,eyez;
	
	if(!faps[26])	return;
	
	eyey = points_orig[681][Y];
	eyez = points_orig[777][Z];
	
	angle_alfa = -faps[26]*au;
	
	for(counter=681;counter<=808;counter++) {
		d = sqrt( sqr(pts[counter][Y] - eyey) + sqr(pts[counter][Z] - eyez) );
		angle_beta = atan2((pts[counter][Y] - eyey),(pts[counter][Z] - eyez));
		pts[counter][Y] = eyey + d*sin(angle_alfa+angle_beta);
		pts[counter][Z] = eyez + d*cos(angle_alfa+angle_beta);
	}
	
}

void Thrust_Left_Eyeball(void)
{
	int counter;
	float dislocation = faps[27]*irisd;
	
	if(!faps[27])	return;
	
	for(counter=553;counter<=680;counter++) 
		pts[counter][Z]+=dislocation;
}

void Thrust_Right_Eyeball(void)
{
	int counter;
	float dislocation = faps[28]*irisd;
	
	if(!faps[28])	return;
	
	for(counter=681;counter<=808;counter++) 
		pts[counter][Z]+=dislocation;
}

void Dilate_Left_Pupil(void)
{
	int counter;
	float d,angle_alfa,dilate_radius,old_radius;
	float x_ref,y_ref;
	
	if(!faps[29])	return;
	
	old_radius = pts[569][X]-pts[553][X];
	
	dilate_radius = old_radius + faps[29]*irisd;
	
	angle_alfa = (float)PI/8;
	
	d = pts[585][X]-pts[553][X];
	
	if(dilate_radius<0.1) dilate_radius=1;
	if(dilate_radius>d) dilate_radius=d-1;
	
	x_ref=pts[553][X];
	y_ref=pts[553][Y];
	
	for(counter=569;counter<=584;counter++) {	
		pts[counter][X]=x_ref+dilate_radius*cos(angle_alfa*(counter-569));
		pts[counter][Y]=y_ref+dilate_radius*sin(angle_alfa*(counter-569));
    }
}

void Dilate_Right_Pupil(void)
{
	int counter;
	float d,angle_alfa,dilate_radius,old_radius;
	float x_ref,y_ref;
	
	if(!faps[30])	return;
	
	old_radius = fabs(pts[681][X]-pts[697][X]);
	
	dilate_radius = old_radius + faps[30]*irisd;
	
	angle_alfa = (float)PI/8;
	
	d = fabs(pts[681][X]-pts[713][X]);
	
	if(dilate_radius<0.1) dilate_radius=1;
	if(dilate_radius>d) dilate_radius=d-1;
	
	x_ref=pts[681][X];
	y_ref=pts[681][Y];
	
	for(counter=697;counter<=712;counter++) {	
		pts[counter][X]=x_ref-dilate_radius*cos(angle_alfa*(counter-697));
		pts[counter][Y]=y_ref+dilate_radius*sin(angle_alfa*(counter-697));
    }
}

void Raise_Left_Inner_Eyebrow(void)
{
	int counter;
	float dist,center_x,center_y,center_z;
	
	int dislocation = faps[31]*ens;
	
	int point[11] = { 172,173,137,138,143,144,148,
		149,150,151,155 };
	
	float perc[11] = { 0.7f,0.8f,1.0f,1.0f,1.0f,1.0f,1.0f,
		0.25f,0.6f,0.7f,0.25f };
	
	if(!faps[31])	return;
	
	for(counter=0;counter<11;counter++)
		pts[point[counter]][Y]+=perc[counter]*dislocation;
	
	//center_x=128;
	//center_y=0;
	//center_z=153;
	
	center_x    = points_orig[553][X];
	center_y    = points_orig[553][Y];
	center_z    = points_orig[553][Z] - 0.9*eyelid_radius_left;

	for(counter=0;counter<11;counter++) {
		dist=sqrt(sqr(pts[point[counter]][X] -center_x)+sqr(pts[point[counter]][Y]-center_y)
			+sqr(pts[point[counter]][Z]-center_z));
		if(dist<eyelid_radius_left)
			pts[point[counter]][Z]=center_z+sqrt(sqr(eyelid_radius_left)
			-sqr(pts[point[counter]][X]-center_x)
			-sqr(pts[point[counter]][Y]-center_y));
	}
}

void Raise_Right_Inner_Eyebrow(void)
{
	int counter;
	float dist,center_x,center_y,center_z;  
	
	int dislocation = faps[32]*ens;
	
	int point[11] = { 434,435,404,405,410,411,415,
		149,416,417,155 };
	
	float perc[11] = { 0.7f,0.8f,1.0f,1.0f,1.0f,1.0f,1.0f,
		0.25f,0.6f,0.7f,0.25f };
	
	if(!faps[32])	return;
	
	for(counter=0;counter<11;counter++)
		pts[point[counter]][Y]+=perc[counter]*dislocation;
	
	//center_x=-128;
	//center_y=0;
	//center_z=153; 

    center_x    = points_orig[681][X];
	center_y    = points_orig[681][Y];
	center_z    = points_orig[681][Z] - 0.9*eyelid_radius_right;
	
	for(counter=0;counter<11;counter++) {
		dist=sqrt(sqr(pts[point[counter]][X]-center_x)+sqr(pts[point[counter]][Y]-center_y)
			+sqr(pts[point[counter]][Z]-center_z));
		if(dist<eyelid_radius_right)
			pts[point[counter]][Z]=center_z+sqrt(sqr(eyelid_radius_right)
			-sqr(pts[point[counter]][X]-center_x)
			-sqr(pts[point[counter]][Y]-center_y));
	}
}

void Raise_Left_Middle_Eyebrow(void)
{
	int counter;
	float dist,center_x,center_y,center_z;
	
	int dislocation = faps[33]*ens;
	
	int point[7] = { 174,175,139,140,145,146,152 };
	
	float perc[7] = { 0.8f,0.8f,1.0f,1.0f,0.8f,0.8f,0.7f};
	
	if(!faps[33])	return;
	
	
	for(counter=0;counter<7;counter++)
		pts[point[counter]][Y]+=perc[counter]*dislocation;
	
	//center_x=128;
	//center_y=0;
	//center_z=153;
	
	center_x    = points_orig[553][X];
	center_y    = points_orig[553][Y];
	center_z    = points_orig[553][Z] - 0.9*eyelid_radius_left;
    
	for(counter=0;counter<7;counter++) {
		dist=sqrt(sqr(pts[point[counter]][X]-center_x)+sqr(pts[point[counter]][Y]-center_y)
			+sqr(pts[point[counter]][Z]-center_z));
		
		if(dist<eyelid_radius_left)
			pts[point[counter]][Z]=center_z+sqrt(sqr(eyelid_radius_left)
			-sqr(pts[point[counter]][X]-center_x)
			-sqr(pts[point[counter]][Y]-center_y));
	}
}

void Raise_Right_Middle_Eyebrow(void)
{
	int counter;
	float dist,center_x,center_y,center_z;
	
	int dislocation = faps[34]*ens;
	
	int point[7] = { 436,437,406,407,412,413,418 }; 
	
	float perc[7] = { 0.8f,0.8f,1.0f,1.0f,0.8f,0.8f,0.7f};
	
	if(!faps[34])	return;
	
	
	for(counter=0;counter<7;counter++)
		pts[point[counter]][Y]+=perc[counter]*dislocation;
	
	//center_x=-128;
	//center_y=0;
	//center_z=153; 

    center_x    = points_orig[681][X];
	center_y    = points_orig[681][Y];
	center_z    = points_orig[681][Z] - 0.9*eyelid_radius_right;
	
	for(counter=0;counter<7;counter++) {
		dist=sqrt(sqr(pts[point[counter]][X]-center_x)+sqr(pts[point[counter]][Y]-center_y)
			+sqr(pts[point[counter]][Z]-center_z));
		if(dist<eyelid_radius_right)
			pts[point[counter]][Z]=center_z+sqrt(sqr(eyelid_radius_right)
			-sqr(pts[point[counter]][X]-center_x)
			-sqr(pts[point[counter]][Y]-center_y));
	}
}

void Raise_Left_Outer_Eyebrow(void)
{
	int counter;
	float dist,center_x,center_y,center_z;
	
	int dislocation = faps[35]*ens;
	
	int point[4] = { 176,141,147,153 };
	
	float perc[4] = { 0.9f,1.0f,0.9f,0.9f };
	
	if(!faps[35])	return;
	
	
	for(counter=0;counter<4;counter++)
		pts[point[counter]][Y]+=perc[counter]*dislocation;
	
	//center_x=128;
	//center_y=0;
	//center_z=153;
	
	center_x    = points_orig[553][X];
	center_y    = points_orig[553][Y];
	center_z    = points_orig[553][Z] - 0.9*eyelid_radius_left;
    
	for(counter=0;counter<4;counter++) {
		dist=sqrt(sqr( pts[point[counter]][X]-center_x)+sqr(pts[point[counter]][Y]-center_y)
			+sqr(pts[point[counter]][Z]-center_z));
		if(dist<eyelid_radius_left)
			pts[point[counter]][Z]=center_z+sqrt(sqr(eyelid_radius_left)
			-sqr(pts[point[counter]][X]-center_x)
			-sqr(pts[point[counter]][Y]-center_y));
	}
}

void Raise_Right_Outer_Eyebrow(void)
{
	int counter;
	float dist,center_x,center_y,center_z;  
	
	int dislocation = faps[36]*ens;
	
	int point[4] = { 438,408,414,419 };
	
	float perc[4] = { 0.9f,1.0f,0.9f,0.9f };
	
	if(!faps[36])	return;
	
	for(counter=0;counter<4;counter++)
		pts[point[counter]][Y]+=perc[counter]*dislocation;
	
	//center_x=-128;
	//center_y=0;
	//center_z=153; 

    center_x    = points_orig[681][X];
	center_y    = points_orig[681][Y];
	center_z    = points_orig[681][Z] - 0.9*eyelid_radius_right;
    
	for(counter=0;counter<4;counter++) {
		dist=sqrt(sqr(pts[point[counter]][X]-center_x)+sqr(pts[point[counter]][Y]-center_y)
			+sqr(pts[point[counter]][Z]-center_z));
		if(dist<eyelid_radius_right)
			pts[point[counter]][Z]=center_z+sqrt(sqr(eyelid_radius_right)
			-sqr(pts[point[counter]][X]-center_x)
			-sqr(pts[point[counter]][Y]-center_y));
	}
}

void Squeeze_Left_Eyebrow(void)
{
	int counter;
	float dist,center_x,center_y,center_z;  
	
	int dislocation = faps[37]*es;
	
	int point[20] = { 172,173,174,175,176,137,138,139,140,141,
		143,144,145,146,147,148,150,151,152,153 };
	
	float perc[20] = { 0.8f,0.8f,0.7f,0.6f,0.5f,0.9f,0.9f,0.8f,0.7f,0.6f,
		1.0f,1.0f,0.8f,0.7f,0.6f,0.7f,0.7f,0.7f,0.6f,0.5f };
	
	
	if(!faps[37])	return;
	
	for(counter=0;counter<20;counter++)
		pts[point[counter]][X]-=perc[counter]*dislocation;
	
	center_x=128;
	center_y=0;
	center_z=153; 
	
	for(counter=0;counter<20;counter++) {
		dist=sqrt(sqr(pts[point[counter]][X] -center_x)+sqr(pts[point[counter]][Y]-center_y)
			+sqr(pts[point[counter]][Z]-center_z));
		if(dist<eyelid_radius_left)
			pts[point[counter]][Z]=center_z+sqrt(sqr(eyelid_radius_left)
			-sqr(pts[point[counter]][X]-center_x)
			-sqr(pts[point[counter]][Y]-center_y));
	}
}

void Squeeze_Right_Eyebrow(void)
{
	int counter;
	float dist,center_x,center_y,center_z;  
	
	int dislocation = faps[38]*es;
	
	int point[20] = { 434,435,436,437,438,404,405,406,407,408,
		410,411,412,413,414,415,416,417,418,419 };
	
	float perc[20] = { 0.8f,0.8f,0.7f,0.6f,0.5f,0.9f,0.9f,0.8f,0.7f,0.6f,
		1.0f,1.0f,0.8f,0.7f,0.6f,0.7f,0.7f,0.7f,0.6f,0.5f };
	
	
	if(!faps[38])	return;
	
	for(counter=0;counter<20;counter++)
		pts[point[counter]][X]+=perc[counter]*dislocation;
	
	center_x=-128;
	center_y=0;
	center_z=153; 
	
	for(counter=0;counter<20;counter++) {
		dist=sqrt(sqr(pts[point[counter]][X] -center_x)+sqr(pts[point[counter]][Y]-center_y)
			+sqr(pts[point[counter]][Z]-center_z));
		if(dist<eyelid_radius_right)
			pts[point[counter]][Z]=center_z+sqrt(sqr(eyelid_radius_right)
			-sqr(pts[point[counter]][X]-center_x)
			-sqr(pts[point[counter]][Y]-center_y));
	}
}

void Puff_Left_Cheek(void)
{
	int counter;
	int points_1[12] = { 44,45,46,94,95,101,102,112,
		113,118,119,131 };
	
	int points_2[3]  = { 111,130,132 };
	
	float dislocation = faps[39]*es;

	if(!faps[39])	return;	

	for(counter=0;counter<12;counter++)
	{
		pts[points_1[counter]][X]+=0.5*dislocation;
		pts[points_1[counter]][Z]-=0.3*dislocation;
	}
	
	
	for(counter=0;counter<3;counter++)
	{
		pts[points_2[counter]][X]+=0.25*dislocation;
		pts[points_2[counter]][Z]-=0.15*dislocation;
	}
}

void Puff_Right_Cheek(void)
{
	int counter;
	int Points_1[12] = { 327,328,329,364,365,370,371,380,
		381,386,387,398 };
	
	int Points_2[3]  = { 379,397,399 };
	
	float dislocation = faps[40]*es;
	
	if(!faps[40])	return;	

	for(counter=0;counter<12;counter++)
	{
		pts[Points_1[counter]][X]-=0.5*dislocation;
		pts[Points_1[counter]][Z]-=0.3*dislocation;
	}
	
	
	for(counter=0;counter<3;counter++)
	{
		pts[Points_2[counter]][X]-=0.25*dislocation;
		pts[Points_2[counter]][Z]-=0.15*dislocation;
	}
}

void Lift_Left_Cheek(void)
{
	int counter;
	int points_1[12] = { 44,45,46,94,95,101,102,112,
		113,118,119,131 };
	
	int points_2[3]  = { 111,130,132 };
	
	float dislocation = faps[41]*ens;
	
	if(!faps[41])	return;	
	
	
	for(counter=0;counter<12;counter++)
		pts[points_1[counter]][Y]+=dislocation;
	
	
	for(counter=0;counter<3;counter++)
		pts[points_2[counter]][Y]+=0.5*dislocation;
}

void Lift_Right_Cheek(void)
{
	int counter;
	int Points_1[12] = { 327,328,329,364,365,370,371,380,
		381,386,387,398 };
	
	int Points_2[3]  = { 379,397,399 };
	
	float dislocation = faps[42]*ens;
	
	if(!faps[42])	return;
	
	
	for(counter=0;counter<12;counter++)
		pts[Points_1[counter]][Y]+=dislocation;
	
	for(counter=0;counter<3;counter++)
		pts[Points_2[counter]][Y]+=0.5*dislocation;
}

void Shift_Tongue_Tip(void)
{
	int counter;
	float t_angle,d_lado,dz;
	int outer_point,middle_point;
	float f1,f2;
	
	
	if(!faps[43])	return;	
	
	f1 = 0.5f;
	f2 = 0.4f;
	
	outer_point = 1013;
	middle_point = 979;
	
	d_lado = faps[43]*mw;
	
	/* upside tongue */
	
	dz=pts[1006][Z]-pts[outer_point][Z];
	pts[1006][Z]=pts[outer_point][Z]+sqrt(fabs(sqr(dz)-sqr(d_lado)));
	pts[1006][X]+=d_lado;
	t_angle=d_lado/dz;
	
	for(counter=1007;counter<=1010;counter++) 
    {
		dz=pts[counter][Z]-pts[outer_point][Z];
		pts[counter][Z]=pts[outer_point][Z]+sqrt(fabs(sqr(dz)-sqr(d_lado)));
		pts[counter][X]+=dz*t_angle;
    }    
	pts[1010][X]-=(pts[1010][X]-pts[1011][X])*f1; 
	pts[1011][X]+=(pts[1010][X]-pts[1011][X])*f2; 
	
	
	for(counter=1015;counter<=1018;counter++) {
		dz=pts[counter][Z]-pts[outer_point][Z];
		pts[counter][Z]=pts[outer_point][Z]+sqrt(fabs(sqr(dz)-sqr(d_lado)));
		pts[counter][X]+=dz*t_angle;
	}  
	pts[1018][X]-=(pts[1018][X]-pts[1019][X])*f1; 
	pts[1019][X]+=(pts[1018][X]-pts[1019][X])*f2; 
	
	for(counter=1023;counter<=1026;counter++)  {
		dz=pts[counter][Z]-pts[outer_point][Z];
		pts[counter][Z]=pts[outer_point][Z]+sqrt(fabs(sqr(dz)-sqr(d_lado)));
		pts[counter][X]+=dz*t_angle;
	}  
	pts[1026][X]-=(pts[1026][X]-pts[1027][X])*f1; 
	pts[1027][X]+=(pts[1026][X]-pts[1027][X])*f2; 
	
	/* inside tongue */
	
	dz=pts[972][Z]-pts[middle_point][Z];
	pts[972][Z]=pts[middle_point][Z]+sqrt(fabs(sqr(dz)-sqr(d_lado)));
	pts[972][X]+=d_lado;
	t_angle=d_lado/dz;
	
	for(counter=973;counter<=976;counter++)  {
		dz=pts[counter][Z]-pts[middle_point][Z];
		pts[counter][Z]=pts[middle_point][Z]+sqrt(fabs(sqr(dz)-sqr(d_lado)));
		pts[counter][X]+=dz*t_angle;
	}  
	pts[976][X]-=(pts[976][X]-pts[977][X])*f1; 
	pts[977][X]+=(pts[976][X]-pts[977][X])*f2; 
	
	for(counter=981;counter<=984;counter++)  {
		dz=pts[counter][Z]-pts[middle_point][Z];
		pts[counter][Z]=pts[middle_point][Z]+sqrt(fabs(sqr(dz)-sqr(d_lado)));
		pts[counter][X]+=dz*t_angle;
	}  
	pts[984][X]-=(pts[984][X]-pts[985][X])*f1; 
	pts[985][X]+=(pts[984][X]-pts[985][X])*f2; 
	
	/* downside tongue */
	
	dz=pts[989][Z]-pts[outer_point][Z];
	pts[989][Z]=pts[outer_point][Z]+sqrt(fabs(sqr(dz)-sqr(d_lado)));
	pts[989][X]+=d_lado;
	t_angle=d_lado/dz;  
	
	for(counter=990;counter<=993;counter++)  {
		dz=pts[counter][Z]-pts[outer_point][Z];
		pts[counter][Z]=pts[outer_point][Z]+sqrt(fabs(sqr(dz)-sqr(d_lado)));
		pts[counter][X]+=dz*t_angle;
	}  
	pts[993][X]-=(pts[993][X]-pts[994][X])*f1; 
	pts[994][X]+=(pts[993][X]-pts[994][X])*f2; 
	
	
	for(counter=998;counter<=1001;counter++)  {
		dz=pts[counter][Z]-pts[outer_point][Z];
		pts[counter][Z]=pts[outer_point][Z]+sqrt(fabs(sqr(dz)-sqr(d_lado)));
		pts[counter][X]+=dz*t_angle;
	} 
	pts[1001][X]-=(pts[1001][X]-pts[1002][X])*f1; 
	pts[1002][X]+=(pts[1001][X]-pts[1002][X])*f2; 
	
	for(counter=1031;counter<=1034;counter++)  {
		dz=pts[counter][Z]-pts[outer_point][Z];
		pts[counter][Z]=pts[outer_point][Z]+sqrt(fabs(sqr(dz)-sqr(d_lado)));
		pts[counter][X]+=dz*t_angle;
	} 
	pts[1034][X]-=(pts[1034][X]-pts[1035][X])*f1; 
	pts[1035][X]+=(pts[1034][X]-pts[1035][X])*f2;  
}

void Raise_Tongue_Tip(void)
{
	int counter;
	float t_angle,d_inclina,dz;
	int outer_point,middle_point;

	if(!faps[44])	return;

	outer_point = 1013;
	middle_point = 979;
	
	d_inclina = faps[44]*mns;
	
	
	/* upside tongue */
	
	dz=pts[1006][Z]-pts[outer_point][Z];
	pts[1006][Z]=pts[outer_point][Z]+sqrt(fabs(sqr(dz)-sqr(d_inclina)));
	pts[1006][Y]+=d_inclina;
	t_angle=d_inclina/dz;
	
	for(counter=1007;counter<=1010;counter++) 
    {
		dz=pts[counter][Z]-pts[outer_point][Z];
		pts[counter][Z]=pts[outer_point][Z]+sqrt(fabs(sqr(dz)-sqr(d_inclina)));
		pts[counter][Y]+=dz*t_angle;
    }    
	pts[1010][Y]-=(pts[1010][Y]-pts[1011][Y])*2/3;
	pts[1011][Y]+=(pts[1010][Y]-pts[1011][Y])*1/3;
	
	
	for(counter=1015;counter<=1018;counter++) {
		dz=pts[counter][Z]-pts[outer_point][Z];
		pts[counter][Z]=pts[outer_point][Z]+sqrt(fabs(sqr(dz)-sqr(d_inclina)));
		pts[counter][Y]+=dz*t_angle;
	}  
	pts[1018][Y]-=(pts[1018][Y]-pts[1019][Y])*2/3;
	pts[1019][Y]+=(pts[1018][Y]-pts[1019][Y])*1/3;
	
	for(counter=1023;counter<=1026;counter++)  {
		dz=pts[counter][Z]-pts[outer_point][Z];
		pts[counter][Z]=pts[outer_point][Z]+sqrt(fabs(sqr(dz)-sqr(d_inclina)));
		pts[counter][Y]+=dz*t_angle;
	}  
	pts[1026][Y]-=(pts[1026][Y]-pts[1027][Y])*2/3;
	pts[1027][Y]+=(pts[1026][Y]-pts[1027][Y])*1/3;
	
	/* inside tongue */
	
	dz=pts[972][Z]-pts[middle_point][Z];
	pts[972][Z]=pts[middle_point][Z]+sqrt(fabs(sqr(dz)-sqr(d_inclina)));
	pts[972][Y]+=d_inclina;
	t_angle=d_inclina/dz;
	
	for(counter=973;counter<=976;counter++)  {
		dz=pts[counter][Z]-pts[middle_point][Z];
		pts[counter][Z]=pts[middle_point][Z]+sqrt(fabs(sqr(dz)-sqr(d_inclina)));
		pts[counter][Y]+=dz*t_angle;
	}  
	pts[976][Y]-=(pts[976][Y]-pts[977][Y])*2/3;
	pts[977][Y]+=(pts[976][Y]-pts[977][Y])*1/3;
	
	for(counter=981;counter<=984;counter++)  {
		dz=pts[counter][Z]-pts[middle_point][Z];
		pts[counter][Z]=pts[middle_point][Z]+sqrt(fabs(sqr(dz)-sqr(d_inclina)));
		pts[counter][Y]+=dz*t_angle;
	}  
	pts[984][Y]-=(pts[984][Y]-pts[985][Y])*2/3;
	pts[985][Y]+=(pts[984][Y]-pts[985][Y])*1/3;
	
	/* downside tongue */
	
	dz=pts[989][Z]-pts[outer_point][Z];
	pts[989][Z]=pts[outer_point][Z]+sqrt(fabs(sqr(dz)-sqr(d_inclina)));
	pts[989][Y]+=d_inclina;
	t_angle=d_inclina/dz;  
	
	for(counter=990;counter<=993;counter++)  {
		dz=pts[counter][Z]-pts[outer_point][Z];
		pts[counter][Z]=pts[outer_point][Z]+sqrt(fabs(sqr(dz)-sqr(d_inclina)));
		pts[counter][Y]+=dz*t_angle;
	}  
	pts[993][Y]-=(pts[993][Y]-pts[994][Y])*2/3;
	pts[994][Y]+=(pts[993][Y]-pts[994][Y])*1/3;
	
	
	for(counter=998;counter<=1001;counter++)  {
		dz=pts[counter][Z]-pts[outer_point][Z];
		pts[counter][Z]=pts[outer_point][Z]+sqrt(fabs(sqr(dz)-sqr(d_inclina)));
		pts[counter][Y]+=dz*t_angle;
	} 
	pts[1001][Y]-=(pts[1001][Y]-pts[1002][Y])*2/3;
	pts[1002][Y]+=(pts[1001][Y]-pts[1002][Y])*1/3;
	
	for(counter=1031;counter<=1034;counter++)  {
		dz=pts[counter][Z]-pts[outer_point][Z];
		pts[counter][Z]=pts[outer_point][Z]+sqrt(fabs(sqr(dz)-sqr(d_inclina)));
		pts[counter][Y]+=dz*t_angle;
	} 
	pts[1034][Y]-=(pts[1034][Y]-pts[1035][Y])*1/3;
	pts[1035][Y]+=(pts[1034][Y]-pts[1035][Y])*1/4;
}

void Thrust_Tongue_Tip(void)
{
	int counter;
	float dislocation;
	
	if(!faps[45])	return;
	
	dislocation = faps[45]*mw;
	
	
	/* upside tongue */
	for(counter=1006;counter<=1010;counter++) 
		pts[counter][Z]+=dislocation;
	pts[1011][Z]+=(dislocation-dislocation/3);
	
	
	for(counter=1015;counter<=1018;counter++) 
		pts[counter][Z]+=dislocation;
	pts[1019][Z]+=(dislocation-dislocation/3);
	
	for(counter=1023;counter<=1026;counter++) 
		pts[counter][Z]+=dislocation;
	pts[1027][Z]+=(dislocation-dislocation/3);
	
	/* inside tongue */
	for(counter=972;counter<=976;counter++) 
		pts[counter][Z]+=dislocation;
	pts[977][Z]+=(dislocation-dislocation/3);
	
	
	for(counter=981;counter<=984;counter++) 
		pts[counter][Z]+=dislocation;
	pts[985][Z]+=(dislocation-dislocation/3);
	
	
	/* downside tongue */
	for(counter=989;counter<=993;counter++) 
		pts[counter][Z]+=dislocation;
	pts[994][Z]+=(dislocation-dislocation/3);
	
	
	for(counter=998;counter<=1001;counter++) 
		pts[counter][Z]+=dislocation;
	pts[1002][Z]+=(dislocation-dislocation/3);
	
	for(counter=1031;counter<=1034;counter++) 
		pts[counter][Z]+=dislocation;
	pts[1035][Z]+=(dislocation-dislocation/3);
}

void Raise_Tongue(void)
{
	int counter;
	float dislocation;
	
	if(!faps[46])	return;
	
	dislocation = faps[46]*mns;
	
	for(counter=972;counter<=1038;counter++) {
		pts[counter][Y]+=dislocation;
	}  
}

void Tongue_Roll(void)
{
	int counter;
	float d,angle,angle_back;
	
	if(!faps[47])	return;
	
	angle = faps[47]*au;	
	
	if(angle != 0){
		
		/* upside tongue */
		
		for(counter=1007;counter<=1010;counter++) 
		{
			d=pts[counter][X];
			pts[counter][X]-=(d-d*cos(angle));
			pts[counter][Y]+=d*sin(angle);
		}
		
		angle_back=angle*2/3;
		d=pts[1011][X];
		pts[1011][X]-=(d-d*cos(angle_back));
		pts[1011][Y]+=d*sin(angle_back);
		
		
		for(counter=1015;counter<=1018;counter++)
		{
			d=pts[counter][X];
			pts[counter][X]-=(d-d*cos(angle));
			pts[counter][Y]-=d*sin(angle);
		}
		
		angle_back=angle*2/3;
		d=pts[1019][X];
		pts[1019][X]-=(d-d*cos(angle_back));
		pts[1019][Y]-=d*sin(angle_back);
		
		
		pts[1006][Y]+=(pts[1007][Y]-pts[1006][Y])/2;
		for(counter=1023;counter<=1027;counter++)
			pts[counter][Y]=pts[1006][Y];
		
		
		/* inside tongue */
		
		for(counter=973;counter<=976;counter++)
		{
			d=pts[counter][X];
			pts[counter][X]-=(d-d*cos(angle));
			pts[counter][Y]+=d*sin(angle);
		} 
		
		angle_back=angle*2/3;
		d=pts[977][X];    
		pts[977][X]-=(d-d*cos(angle_back));
		pts[977][Y]+=d*sin(angle_back);
		
		for(counter=981;counter<=984;counter++)
		{
			d=pts[counter][X];
			pts[counter][X]-=(d-d*cos(angle));
			pts[counter][Y]-=d*sin(angle);
		}
		
		angle_back=angle*2/3;
		d=pts[985][X];
		pts[985][X]-=(d-d*cos(angle_back));
		pts[985][Y]-=d*sin(angle_back);
		
		pts[972][Y]+=(pts[973][Y]-pts[972][Y])/2;
		
		/* downside tongue */
		
		for(counter=990;counter<=993;counter++)
		{
			d=pts[counter][X];
			pts[counter][X]-=(d-d*cos(angle));
			pts[counter][Y]+=d*sin(angle);
		}
		
		angle_back=angle*2/3;
		d=pts[994][X];
		pts[994][X]-=(d-d*cos(angle_back));
		pts[994][Y]+=d*sin(angle_back);
		
		for(counter=998;counter<=1001;counter++)
		{
			d=pts[counter][X];
			pts[counter][X]-=(d-d*cos(angle));
			pts[counter][Y]-=d*sin(angle);
		}
		
		angle_back=angle*2/3;
		d=pts[1002][X]; 
		pts[1002][X]-=(d-d*cos(angle_back));
		pts[1002][Y]-=d*sin(angle_back);  
		
		pts[989][Y]=pts[1006][Y]-17;
		
		for(counter=1031;counter<=1035;counter++)
			pts[counter][Y]=pts[989][Y]-2;
	}
}

void Head_Pitch(void)
{
	int counter;
	float d,angle_alfa,angle_beta;
	float heady,headz;
	
	
	if(!faps[48])	return;
	
	heady = points_orig[826][Y];
	headz = points_orig[826][Z];
	
	angle_alfa = faps[48]*au;
	
	for(counter=0;counter<NO_POINTS;counter++) {
		d = sqrt( sqr(pts[counter][Y] - heady) + sqr(pts[counter][Z] - headz) );
		angle_beta = atan2((pts[counter][Y] - heady),(pts[counter][Z] - headz));
		pts[counter][Y] = heady + d*sin(angle_alfa+angle_beta);
		pts[counter][Z] = headz + d*cos(angle_alfa+angle_beta);
	}
	
}

void Head_Roll(void)
{
	int counter;
	float d,angle_alfa,angle_beta;
	float headx,headz;
	
	if(!faps[49])	return;
	
	headx = points_orig[826][X];
	headz = points_orig[826][Z];
	
	angle_alfa = faps[49]*au;
	
	for(counter=0;counter<NO_POINTS;counter++) {
		d = sqrt( sqr(pts[counter][X] - headx) + sqr(pts[counter][Z] - headz) );
		angle_beta = atan2((pts[counter][X] - headx),(pts[counter][Z] - headz));
		pts[counter][X] = headx + d*sin(angle_alfa+angle_beta);
		pts[counter][Z] = headz + d*cos(angle_alfa+angle_beta);
	}
	
}

void Head_Yaw(void)
{
	int counter;
	float d,angle_alfa,angle_beta;
	float headx,heady;
	
	if(!faps[50])	return;
	
	headx = points_orig[826][X];
	heady = points_orig[826][Y];
	
	angle_alfa = faps[50]*au;
	
	for(counter=0;counter<NO_POINTS;counter++) {
		d = sqrt( sqr(pts[counter][X] - headx) + sqr(pts[counter][Y] - heady) );
		angle_beta = atan2((pts[counter][X] - headx),(pts[counter][Y] - heady));
		pts[counter][X] = headx + d*sin(angle_alfa+angle_beta);
		pts[counter][Y] = heady + d*cos(angle_alfa+angle_beta);
	}
	
}

void Stretch_Left_Nose(void)
{
	int counter;
	float dislocation_x;
	
	if(!faps[61])	return;
	
	dislocation_x = faps[61]*ens;
	
	for(counter=73;counter<=78;counter++)  
		pts[counter][X]+=dislocation_x*0.9;
	for(counter=80;counter<=85;counter++)  
		pts[counter][X]+=dislocation_x*0.9;
	for(counter=90;counter<=93;counter++)  
		pts[counter][X]+=dislocation_x;
	for(counter=97;counter<=99;counter++)  
		pts[counter][X]+=dislocation_x*0.7;
	pts[100][X]+=dislocation_x;
	for(counter=108;counter<=110;counter++)
		pts[counter][X]+=dislocation_x*0.5;
}

void Stretch_Right_Nose(void)
{
	int counter;
	float dislocation_x;
	
	
	if(!faps[62])	return;
	
	dislocation_x = faps[62]*ens;
	
	for(counter=348;counter<=353;counter++)  
		pts[counter][X]-=dislocation_x*0.9;
	for(counter=354;counter<=359;counter++)  
		pts[counter][X]-=dislocation_x*0.9;
	for(counter=360;counter<=363;counter++)  
		pts[counter][X]-=dislocation_x;
	for(counter=366;counter<=368;counter++)  
		pts[counter][X]-=dislocation_x*0.7;
	pts[369][X]-=dislocation_x;
	for(counter=376;counter<=378;counter++)
		pts[counter][X]-=dislocation_x*0.5;
}

void Raise_Nose(void)
{
    int counter;
    float dislocation_y;
    
	
	if(!faps[63])	return;
	
    dislocation_y = faps[63]*ens;
	
    if(dislocation_y>0) {
		for(counter=79;counter<=81;counter++)        
			pts[counter][Y]+=dislocation_y*0.7;    
		for(counter=89;counter<=91;counter++)        
			pts[counter][Y]+=dislocation_y;    
		for(counter=96;counter<=98;counter++)       
			pts[counter][Y]+=dislocation_y*0.7;
		for(counter=354;counter<=355;counter++)        
			pts[counter][Y]+=dislocation_y*0.7;    
		for(counter=360;counter<=361;counter++) 
			pts[counter][Y]+=dislocation_y;    
		for(counter=366;counter<=367;counter++)        
			pts[counter][Y]+=dislocation_y*0.7;
    }
    if(dislocation_y<0) {
		
		for(counter=79;counter<=81;counter++)        
			pts[counter][Y]+=dislocation_y;    
		for(counter=89;counter<=91;counter++) 
			pts[counter][Y]+=dislocation_y*0.8;    	    
		for(counter=96;counter<=98;counter++) 
			pts[counter][Y]+=dislocation_y*0.7;
		
		for(counter=354;counter<=355;counter++)        
			pts[counter][Y]+=dislocation_y*0.8;    
		for(counter=360;counter<=361;counter++) 
			pts[counter][Y]+=dislocation_y;    	
		for(counter=366;counter<=367;counter++) 
			pts[counter][Y]+=dislocation_y*0.7;	        
    }
}

void Bend_Nose(void)
{
    int counter;
    float dislocation_x;
    
	if(!faps[64])	return;
	
    dislocation_x = faps[64]*ens;
	
    if(dislocation_x!=0) {
		for(counter=79;counter<=81;counter++)        
			pts[counter][X]+=dislocation_x*0.9;    
		for(counter=89;counter<=91;counter++)        
			pts[counter][X]+=dislocation_x;    
		for(counter=96;counter<=98;counter++)       
			pts[counter][X]+=dislocation_x*0.6;
		
		for(counter=354;counter<=355;counter++)        
			pts[counter][X]+=dislocation_x*0.9;    
		for(counter=360;counter<=361;counter++) 
			pts[counter][X]+=dislocation_x;    
		for(counter=366;counter<=367;counter++)        
			pts[counter][X]+=dislocation_x*0.6;
    }
}

void Raise_Left_Ear(void)
{
	int counter;
	int points_head[7] = { 122,116,105,844,845,846,106 };
	
	float dislocation     = faps[65]*ens;
	
	if(!faps[65])	return;
	for(counter=936;counter<=953;counter++)
		pts[counter][Y]+=dislocation;
	
	for(counter=0;counter<7;counter++)  
		pts[points_head[counter]][Y]+=dislocation;
}

void Raise_Right_Ear(void)
{
	int counter;
	int points_head[7] = { 390,384,374,917,918,919,375 };
	
	float dislocation     = faps[66]*ens;
	
	if(!faps[66])	return;
	
	for(counter=954;counter<=971;counter++)
		pts[counter][Y]+=dislocation;
	
	for(counter=0;counter<7;counter++)  
		pts[points_head[counter]][Y]+=dislocation;
}

void Pull_Left_Ear(void)
{
	int counter;
	int points_head[7] = { 122,116,105,844,845,846,106 };
	float dislocation = faps[67]*ens;
	
	if(!faps[67])	return;
	
	
	for(counter=936;counter<=953;counter++)
		pts[counter][Z]+=dislocation;
	
	for(counter=0;counter<7;counter++)  
		pts[points_head[counter]][Z]+=dislocation;
}

void Pull_Right_Ear(void)
{
	int counter;
	int points_head[7] = { 390,384,374,917,918,919,375 };
	
	float dislocation = faps[68]*ens;
	
	if(!faps[68])	return;
	
	
	for(counter=954;counter<=971;counter++)
		pts[counter][Z]+=dislocation;
	
	for(counter=0;counter<7;counter++)  
		pts[points_head[counter]][Z]+=dislocation;
}

void FAP_Interpolation(void)
{
	int counter,i;
	int fap_mask[NO_FAPS+1];
	for(counter=1;counter<=NO_FAPS;counter++)
	{
		if((int)faps[counter]!=0)
			fap_mask[counter] = 1;
		else
			fap_mask[counter] = 0;
	}
	
	/* left-right interpolation */
	for(counter=1;counter<GROUP_MASK_SIZE;counter++)
	{
		for(i=LRP_GROUP[counter-1];i<LRP_GROUP[counter];i++)
		{
			if(!fap_mask[LeftRightPairs[i]])// &&  ((int)faps[LeftRightPairs[i]]==0))
				faps[LeftRightPairs[i]] = faps[LeftRightPairs[i]+1];
			
			if(!fap_mask[LeftRightPairs[i]+1])// && ((int)faps[LeftRightPairs[i]+1]==0))
				faps[LeftRightPairs[i]+1] = faps[LeftRightPairs[i]];
		}
	}
	
	/* lips interpolation */
	
	for(counter=51;counter<=60;counter++)
	{
		if( (fap_mask[counter] == 0) && ((int)faps[counter-47]!=0) )
			faps[counter] = faps[counter-47];
	}
	
	for(counter=4;counter<=13;counter++)
	{
		if( (fap_mask[counter] == 0) && ((int)faps[counter+47]!=0) )
			faps[counter] = faps[counter+47];
	}
	
	if(fap_mask[3]) faps[44] = -1*faps[3];		
}

void DoFaps()
{
	Depress_Chin();									//fap 18
	Open_Jaw();										//fap 3
	Shift_Jaw();									//fap 15
	Thrust_Jaw();									//fap 14
	Fap_51();	Fap_4();							//void Lower_Top_Midlip(void)
	Fap_5();	Fap_52();							//void Raise_Bottom_Midlip(void)
	Fap_53();	Fap_54();	Fap_6();	Fap_7();	//void Stretch_Cornerlip(void)
	Fap_55();	Fap_56();	Fap_8();	Fap_9();	//void Lower_Top_Lip_Midpoint(void)
	Fap_57();	Fap_58();	Fap_10();	Fap_11();	//void Raise_Bottom_Lip_Midpoint(void)
	Fap_59();	Fap_12();	Fap_60();	Fap_13();	//void Raise_Cornerlip(void)
	Fap_17();	Fap_16();							//void Push_Lip(void)
	Close_Top_Left_Eyelid();						//fap 19
	Close_Top_Right_Eyelid();						//fap 20
	Close_Bottom_Left_Eyelid();						//fap 21
	Close_Bottom_Right_Eyelid();					//fap 22
	Yaw_Left_Eyeball();								//fap 23
	Yaw_Right_Eyeball();							//fap 24
	Pitch_Left_Eyeball();							//fap 25
	Pitch_Right_Eyeball();							//fap 26
	Thrust_Left_Eyeball();							//fap 27
	Thrust_Right_Eyeball();							//fap 28
	Dilate_Left_Pupil();							//fap 29
	Dilate_Right_Pupil();							//fap 30
	Raise_Left_Inner_Eyebrow();						//fap 31
	Raise_Right_Inner_Eyebrow();					//fap 32
	Raise_Left_Middle_Eyebrow();					//fap 33
	Raise_Right_Middle_Eyebrow();					//fap 34
	Raise_Left_Outer_Eyebrow();						//fap 35
	Raise_Right_Outer_Eyebrow();					//fap 36
	Squeeze_Left_Eyebrow();							//fap 37
	Squeeze_Right_Eyebrow();						//fap 38
	Puff_Left_Cheek();								//fap 39
	Puff_Right_Cheek();								//fap 40
	Lift_Left_Cheek();								//fap 41
	Lift_Right_Cheek();								//fap 42
	Shift_Tongue_Tip();								//fap 43
	Raise_Tongue_Tip();								//fap 44
	Thrust_Tongue_Tip();							//fap 45
	Raise_Tongue();									//fap 46
	Tongue_Roll();									//fap 47
	Head_Pitch();									//fap 48
	Head_Roll();									//fap 49
	Head_Yaw();										//fap 50
	Stretch_Left_Nose();							//fap 61
	Stretch_Right_Nose();							//fap 62
	Raise_Nose();									//fap 63
	Bend_Nose();									//fap 64
	Raise_Left_Ear();								//fap 65
	Raise_Right_Ear();								//fap 66
	Pull_Left_Ear();								//fap 67
	Pull_Right_Ear();								//fap 68
		
}