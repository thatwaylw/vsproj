#define CODERANGE 94
#define ASCIIRANGE 96

BYTE ASCIILib[ASCIIRANGE][16];
BYTE HZLib[CODERANGE][CODERANGE][32];

float hzSize = 0.5f;
float hzXpos=0.0f, hzYpos=0.0f;
float hzItalic = 0.0f;

void LoadASCIILib(char * fname)
{
	FILE * fp;
	fp = fopen(fname, "rb");
	if(fp == NULL)
		return;

	int i, b;
	
	for(i=0; i<ASCIIRANGE; i++)
		for(b=0; b<16; b++)
			ASCIILib[i][b] = fgetc(fp);
			
	fclose(fp);
}

void ShowASCII(char * str)
{
	int i, j, m;
	BYTE mask, word;
	float x, y;
	
	i = 0;
	glBegin(GL_QUADS);
	while(str[i] != '\0')
	{
		for(j=0; j<16; j++)
		{
			mask = 0x80;
			word = ASCIILib[str[i]-32][j];
			for(m=0; m<8; m++)
			{
				if(word & mask)
				{
					x = ((15-j)*hzItalic + 8*i + m) * hzSize + hzXpos;
					y = (15-j) * hzSize + hzYpos;

					glVertex3f(x,			y,			0.0f);
					glVertex3f(x+hzSize,	y,			0.0f);
					glVertex3f(x+hzSize,	y+hzSize,	0.0f);
					glVertex3f(x,			y+hzSize,	0.0f);
				}
				mask >>= 1;
			}
		}
		i ++;
	}
	glEnd();
//	hzXpos += i*8*hzSize;
}

void LoadHZLib(char * fname)
{
	FILE * fp;
	fp = fopen(fname, "rb");
	if(fp == NULL)
		return;

	int i, j, b;
	
	for(i=0; i<CODERANGE; i++)
		for(j=0; j<CODERANGE; j++)
			for(b=0; b<32; b++)
				HZLib[i][j][b] = fgetc(fp);
			
	fclose(fp);
}

void ShowHZ(char * str)
{
	int i, j, k, m;
	BYTE mask, word;
	unsigned char qm, wm;
	float x, y;
	
	i = 0;
	glBegin(GL_QUADS);
	while(str[i] != '\0')
	{
		for(j=0; j<16; j++)
		{
			for(k=0; k<2; k++)
			{
				mask = 0x80;
				qm = str[i];
				wm = str[i+1];
				word = HZLib[qm-161][wm-161][2*j + k];
				for(m=0; m<8; m++)
				{
					if(word & mask)
					{
//						glVertex3f((17*(i-s)+k*8+m)*hzSize, (-j)*hzSize, 0.0f);
						
						x = ((15-j)*hzItalic + (i+k)*8 + m) * hzSize + hzXpos;
						y = (15-j) * hzSize + hzYpos;

						glVertex3f(x,			y,			0.0f);
						glVertex3f(x+hzSize,	y,			0.0f);
						glVertex3f(x+hzSize,	y+hzSize,	0.0f);
						glVertex3f(x,			y+hzSize,	0.0f);
					}
					mask >>= 1;
				}
			}
		}
		i += 2;
	}		
	glEnd();				
//	hzXpos += i*8*hzSize;
}

void LoadTextLib(char * path)
{
	int i;
	i = strlen(path);
	char * fname = new char[i+10];
	
	strcpy(fname, path);
	strcat(fname, "ASCII16");
	LoadASCIILib(fname);

	fname[i] = '\0';
	strcat(fname, "HZK16");
	LoadHZLib(fname);

	delete fname;
}

void ShowText(char * str)
{
	int i=0, j;
	char tmp[101];
	int Pre_Xpos, Pre_Ypos;
	Pre_Xpos = hzXpos;
	Pre_Ypos = hzYpos;

	while(str[i] != '\0')
	{
		if(str[i] == '\n')
		{
			hzYpos += 16*hzSize;
			hzXpos = Pre_Xpos;
			i ++;
		}
		else if(str[i] == '\t')
		{
			hzXpos += 64*hzSize;
			i ++;
		}
		
		j = 0;
		while(str[i]>0 && str[i]!='\n' && str[i]!='\t')
		{
			tmp[j++] = str[i++];
			if(j >= 100)	break;
		}
		tmp[j] = '\0';
		ShowASCII(tmp);
		hzXpos += j*8*hzSize;

		j = 0;
		while(str[i] < 0)
		{
			tmp[j++] = str[i++];
			tmp[j++] = str[i++];
			if(j >= 100)	break;
		}
		tmp[j] = '\0';
		ShowHZ(tmp);
		hzXpos += j*8*hzSize;
	}
	hzXpos = Pre_Xpos;
	hzYpos = Pre_Ypos;
}
