#define HintsOn			TRUE

BYTE HZs[32*1000];
float hzSize = 0.88f;
float hzXpos, hzYpos;
int   hzFrom = -1, hzTo = -1;
float hzRed, hzGreen, hzBlue;

void PreShowHZ(BYTE * pb, char * str);
void ShowHZ(BYTE * hzk, int s, int e);
void ShowHints(int s, int e);
	
void CTaiQiuView::DrawScene()
{
	......
	if(HintsOn && hzFrom >= 0)
	{
		glColor3f(hzRed, hzGreen, hzBlue);
		ShowHZ(HZs, hzFrom, hzTo);
	}
	......
}

void CTaiQiuView::OnTimer(UINT nIDEvent)
{
	......
	else if(nIDEvent == 4)
	{
		if(hzSize <= 0.3f)
		{
			KillTimer(4);
			hzFrom = -1;
		}

		hzSize -= 0.02f;
		hzYpos += 2.0f;
		hzXpos = -hzSize*17*(hzTo-hzFrom)/2;
		hzRed -= 0.02f;
		hzGreen -= 0.01f;
		hzBlue += 0.02f;
		
		DrawScene();

	}
	CView::OnTimer(nIDEvent);
}

void CTaiQiuView::PreShowHZ(BYTE * pb, char * str)
{
	int i, j, n;
	unsigned long idx;
	unsigned char qm, wm;
	FILE * fp;

	fp = fopen("hzk16", "rb");
	if(fp == NULL)	return;

	n = 0;
	while(str[n] != '\0')
	{
		qm = str[n++];
		wm = str[n++];
		idx = 94*(qm-161) + wm-161;

		fseek(fp, 32*idx, SEEK_SET);
		j = 0;
		for(i=0; i<16; i++)
		{
			pb[j++] = fgetc(fp);
			pb[j++] = fgetc(fp);
		}
		pb += 32;
	}

	fclose(fp);
}

void CTaiQiuView::ShowHZ(BYTE * hzk, int s, int e)
{
	int i, j, k, m;
	BYTE mask, word;
//	glEnable(GL_LINE_STIPPLE);
//	glBegin(GL_POINTS);
	glBegin(GL_QUADS);
	for(i=s; i<e; i++)
	{
//		glBitmap(16, 16, 0.0, 0.0, 17.0, 0.0, &hzk[i*64]);
		for(j=0; j<16; j++)
		{
			for(k=0; k<2; k++)
			{
				mask = 0x80;
				word = hzk[i*32 + 2*j + k];
				for(m=0; m<8; m++)
				{
					if(word & mask)
					{
//						glVertex3f((17*(i-s)+k*8+m)*hzSize, (-j)*hzSize, 0.0f);
						
						glVertex3f((17*(i-s)+k*8+m)*hzSize+hzXpos,		(16-j)*hzSize+hzYpos, 0.0f);
						glVertex3f((17*(i-s)+k*8+m+1)*hzSize+hzXpos,	(16-j)*hzSize+hzYpos, 0.0f);
						glVertex3f((17*(i-s)+k*8+m+1)*hzSize+hzXpos,	(15-j)*hzSize+hzYpos,  0.0f);
						glVertex3f((17*(i-s)+k*8+m)*hzSize+hzXpos,		(15-j)*hzSize+hzYpos,  0.0f);

					}
					mask >>= 1;
				}
			}
/*			glLineStipple(1, hzk[i*32 + 2*j]);
			glBegin(GL_LINES);
				glVertex3f(17*(i-s)+0.0f, 0.0f-j, 0.0f);
				glVertex3f(17*(i-s)+8.0f, 0.0f-j, 0.0f);
			glEnd();
			glLineStipple(1, hzk[i*32 + 2*j+1]);
			glBegin(GL_LINES);
				glVertex3f(17*(i-s)+8.0f, 0.0f-j, 0.0f);
				glVertex3f(17*(i-s)+16.0f,0.0f-j, 0.0f);
			glEnd();
*/
		}
	}
	glEnd();
//	glDisable(GL_LINE_STIPPLE);
//	glBitmap(0, 0, 0.0, 0.0, -17.0*(e-s+1), 0.0, NULL);
}

void CTaiQiuView::ShowHints(int s, int e)
{
	if(!HintsOn)	return;

	hzFrom = s;
	hzTo   = e;
	hzSize = 1.2f; 
	hzXpos = -hzSize*17*(e-s)/2;
	hzYpos = -hzSize*20;
	hzRed = 1.0f;
	hzGreen = 1.0f;
	hzBlue = 0.0f;

	DrawScene();

	SetTimer(4, 40, NULL);
}
