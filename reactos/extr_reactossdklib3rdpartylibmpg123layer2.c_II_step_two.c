#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct al_table {int bits; int d; } ;
typedef  int /*<<< orphan*/  real ;
struct TYPE_4__ {int stereo; int II_sblimit; int jsbound; int down_sample_sblimit; int /*<<< orphan*/ ** muls; struct al_table* alloc; } ;
typedef  TYPE_1__ mpg123_handle ;

/* Variables and functions */
 int /*<<< orphan*/  DOUBLE_TO_REAL (double) ; 
 int /*<<< orphan*/  DOUBLE_TO_REAL_15 (int) ; 
 int /*<<< orphan*/  REAL_MUL_SCALE_LAYER12 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REAL_SCALE_LAYER12 (int /*<<< orphan*/ ) ; 
 int SBLIMIT ; 
 scalar_t__ getbits (TYPE_1__*,int) ; 
 int const* grp_3tab ; 
 int const* grp_5tab ; 
 int const* grp_9tab ; 

__attribute__((used)) static void II_step_two(unsigned int *bit_alloc,real fraction[2][4][SBLIMIT],int *scale,mpg123_handle *fr,int x1)
{
	int i,j,k,ba;
	int stereo = fr->stereo;
	int sblimit = fr->II_sblimit;
	int jsbound = fr->jsbound;
	const struct al_table *alloc2,*alloc1 = fr->alloc;
	unsigned int *bita=bit_alloc;
	int d1,step;

	for(i=0;i<jsbound;i++,alloc1+=(1<<step))
	{
		step = alloc1->bits;
		for(j=0;j<stereo;j++)
		{
			if( (ba=*bita++) ) 
			{
				k=(alloc2 = alloc1+ba)->bits;
				if( (d1=alloc2->d) < 0) 
				{
					real cm=fr->muls[k][scale[x1]];
					fraction[j][0][i] = REAL_MUL_SCALE_LAYER12(DOUBLE_TO_REAL_15((int)getbits(fr, k) + d1), cm);
					fraction[j][1][i] = REAL_MUL_SCALE_LAYER12(DOUBLE_TO_REAL_15((int)getbits(fr, k) + d1), cm);
					fraction[j][2][i] = REAL_MUL_SCALE_LAYER12(DOUBLE_TO_REAL_15((int)getbits(fr, k) + d1), cm);
				}        
				else 
				{
					const int *table[] = { 0,0,0,grp_3tab,0,grp_5tab,0,0,0,grp_9tab };
					unsigned int idx,*tab,m=scale[x1];
					idx = (unsigned int) getbits(fr, k);
					tab = (unsigned int *) (table[d1] + idx + idx + idx);
					fraction[j][0][i] = REAL_SCALE_LAYER12(fr->muls[*tab++][m]);
					fraction[j][1][i] = REAL_SCALE_LAYER12(fr->muls[*tab++][m]);
					fraction[j][2][i] = REAL_SCALE_LAYER12(fr->muls[*tab][m]);  
				}
				scale+=3;
			}
			else
			fraction[j][0][i] = fraction[j][1][i] = fraction[j][2][i] = DOUBLE_TO_REAL(0.0);
		}
	}

	for(i=jsbound;i<sblimit;i++,alloc1+=(1<<step))
	{
		step = alloc1->bits;
		bita++;	/* channel 1 and channel 2 bitalloc are the same */
		if( (ba=*bita++) )
		{
			k=(alloc2 = alloc1+ba)->bits;
			if( (d1=alloc2->d) < 0)
			{
				real cm;
				cm=fr->muls[k][scale[x1+3]];
				fraction[0][0][i] = DOUBLE_TO_REAL_15((int)getbits(fr, k) + d1);
				fraction[0][1][i] = DOUBLE_TO_REAL_15((int)getbits(fr, k) + d1);
				fraction[0][2][i] = DOUBLE_TO_REAL_15((int)getbits(fr, k) + d1);
				fraction[1][0][i] = REAL_MUL_SCALE_LAYER12(fraction[0][0][i], cm);
				fraction[1][1][i] = REAL_MUL_SCALE_LAYER12(fraction[0][1][i], cm);
				fraction[1][2][i] = REAL_MUL_SCALE_LAYER12(fraction[0][2][i], cm);
				cm=fr->muls[k][scale[x1]];
				fraction[0][0][i] = REAL_MUL_SCALE_LAYER12(fraction[0][0][i], cm);
				fraction[0][1][i] = REAL_MUL_SCALE_LAYER12(fraction[0][1][i], cm);
				fraction[0][2][i] = REAL_MUL_SCALE_LAYER12(fraction[0][2][i], cm);
			}
			else
			{
				const int *table[] = { 0,0,0,grp_3tab,0,grp_5tab,0,0,0,grp_9tab };
				unsigned int idx,*tab,m1,m2;
				m1 = scale[x1]; m2 = scale[x1+3];
				idx = (unsigned int) getbits(fr, k);
				tab = (unsigned int *) (table[d1] + idx + idx + idx);
				fraction[0][0][i] = REAL_SCALE_LAYER12(fr->muls[*tab][m1]); fraction[1][0][i] = REAL_SCALE_LAYER12(fr->muls[*tab++][m2]);
				fraction[0][1][i] = REAL_SCALE_LAYER12(fr->muls[*tab][m1]); fraction[1][1][i] = REAL_SCALE_LAYER12(fr->muls[*tab++][m2]);
				fraction[0][2][i] = REAL_SCALE_LAYER12(fr->muls[*tab][m1]); fraction[1][2][i] = REAL_SCALE_LAYER12(fr->muls[*tab][m2]);
			}
			scale+=6;
		}
		else
		{
			fraction[0][0][i] = fraction[0][1][i] = fraction[0][2][i] =
			fraction[1][0][i] = fraction[1][1][i] = fraction[1][2][i] = DOUBLE_TO_REAL(0.0);
		}
/*
	Historic comment...
	should we use individual scalefac for channel 2 or
	is the current way the right one , where we just copy channel 1 to
	channel 2 ?? 
	The current 'strange' thing is, that we throw away the scalefac
	values for the second channel ...!!
	-> changed .. now we use the scalefac values of channel one !! 
*/
	}

	if(sblimit > (fr->down_sample_sblimit) )
	sblimit = fr->down_sample_sblimit;

	for(i=sblimit;i<SBLIMIT;i++)
	for (j=0;j<stereo;j++)
	fraction[j][0][i] = fraction[j][1][i] = fraction[j][2][i] = DOUBLE_TO_REAL(0.0);
}