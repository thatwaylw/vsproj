#include "stdafx.h"

#include "DoFap.h"

//Extern Functions
//void KillLine(FILE *fp);
void TestforTrash(FILE *fp);
//...

float exps[6];
int   exp_table[6][NO_FAPS+1];

int   cur_visem = 0;
int   vis_table[16][NO_FAPS+1];

int viseme1, viseme2, vis_blend;
int expres1, expres2, exp_val1, exp_val2;

int PassToNumber(FILE *fp) 
{
	int c;
	
	while(c = getc(fp),(!isdigit(c)) && (c!=EOF) && (c!='-') );
	
	return ungetc(c,fp);
}


int GetInt(FILE *fp)
{
	int get;
	
	PassToNumber(fp);
	fscanf(fp,"%d", &get);
	return get;
}

void ReadExpTable()
{
	FILE * fp;
	int exp, counter;
	char trash[BUFFER_SIZE];
	
	fp = fopen("IST_expressions", "r");
	if(fp == NULL)
	{
		AfxMessageBox("Read Exp Table Error!");
		return;
	}

	for(exp=0;exp<6;exp++)
	{
		TestforTrash(fp);
		
		/*read mask */
		
		for(counter=1;counter<=NO_FAPS;counter++) 
			exp_table[exp][counter] = GetInt(fp);
		
		/* read faps */
		
		for(counter=1;counter<=NO_FAPS;counter++) {
			if(exp_table[exp][counter] == 1)
				exp_table[exp][counter] = GetInt(fp);
		}
		
		fgets(trash,BUFFER_SIZE,fp);
	}
	
	fclose (fp);
	
}

void ReadVisTable()
{
	FILE * fp;
	int vis, counter;
	char trash[BUFFER_SIZE];
	
	fp = fopen("IST_visems", "r");
	if(fp == NULL)
	{
		AfxMessageBox("Read Vis Table Error!");
		return;
	}
	
	memset(&vis_table[0], 0, sizeof(int)*(NO_FAPS+1));
	for(vis=1; vis<16; vis++)
	{
		TestforTrash(fp);
		
		/*read mask */
		
		for(counter=1;counter<=NO_FAPS;counter++) 
			vis_table[vis][counter] = GetInt(fp);
		
		/* read faps */
		
		for(counter=1;counter<=NO_FAPS;counter++) {
			if(vis_table[vis][counter] == 1)
				vis_table[vis][counter] = GetInt(fp);
		}
		
		fgets(trash,BUFFER_SIZE,fp);
	}
	
	fclose (fp);
}

void ResetFaps()
{
	int counter;

	for(counter=1;counter<=NO_FAPS;counter++)
	{
		faps[counter] = 0;
	}
}

void DoExpression()
{
	int exp, counter;

	for(exp=0;exp<6;exp++)
	{
		for(counter=1;counter<=NO_FAPS;counter++)
		{
			faps[counter] += exp_table[exp][counter]*exps[exp]/100.0f;
		}
	}
}

void DoVisem()
{
	int counter;

	if(cur_visem == 0)	return;
	else
	{
		for(counter=1;counter<=NO_FAPS;counter++)
		{
			faps[counter] += (float)(vis_table[cur_visem][counter]);
		}
		
	}
}

void ParseExpVis()
{
	int counter;

	if((int)faps[2])
	{
		if(expres1 < 0)	expres1 = 0;	if(expres2 < 0)	expres2 = 0;
		if(expres1 > 5)	expres1 = 5;	if(expres2 > 5)	expres2 = 5;
		for(counter=3;counter<=NO_FAPS;counter++)
		{
			faps[counter] += 0.5f*exp_table[expres1][counter]*exp_val1/63.0f;
			faps[counter] += 0.5f*exp_table[expres2][counter]*exp_val2/63.0f;
		}
	}
	if((int)faps[1])
	{
		if(viseme1 < 0)	viseme1 = 0;	if(viseme2 < 0)	viseme2 = 0;
		if(viseme1 >15) viseme1 = 15;	if(viseme2 >15) viseme2 = 15;
		for(counter=3;counter<=NO_FAPS;counter++)
		{
			faps[counter] += vis_table[viseme1][counter]*vis_blend/63.0f;
			faps[counter] += vis_table[viseme2][counter]*(1.0f-vis_blend/63.0f);
		}
	}
}