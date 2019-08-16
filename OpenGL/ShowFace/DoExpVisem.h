#ifndef GLOBAL_DEF
#define GLOBAL_DEF
#include "GlobalDef.h"
#endif

extern float exps[6];
extern int	 exp_table[6][NO_FAPS+1];
extern int   cur_visem;
extern int   vis_table[16][NO_FAPS+1];
extern int	 viseme1, viseme2, vis_blend;
extern int	 expres1, expres2, exp_val1, exp_val2;

void ReadExpTable();
void ReadVisTable();
void ResetFaps();
void DoExpression();
void DoVisem();
void ParseExpVis();
