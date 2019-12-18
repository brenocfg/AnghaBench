#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct gr_info_s {int scfsi; scalar_t__ part2_3_length; int big_values; scalar_t__ scalefac_compress; int block_type; int* table_select; int region1start; int region2start; void* count1table_select; void* scalefac_scale; void* preflag; void* mixed_block_flag; scalar_t__ pow2gain; scalar_t__* full_gain; } ;
struct III_sideinfo {int main_data_begin; int private_bits; TYPE_1__* ch; } ;
struct TYPE_10__ {size_t lsf; int bitreservoir; unsigned char* wordpointer; int ssize; int framesize; int gainpow2; scalar_t__ mpeg25; scalar_t__ error_protection; scalar_t__ num; int /*<<< orphan*/  to_ignore; } ;
typedef  TYPE_2__ mpg123_handle ;
struct TYPE_11__ {int* longIdx; } ;
struct TYPE_9__ {struct gr_info_s* gr; } ;

/* Variables and functions */
 scalar_t__ NOQUIET ; 
 int SINGLE_MIX ; 
 scalar_t__ VERBOSE2 ; 
 int /*<<< orphan*/  backbits (TYPE_2__*,int const) ; 
 TYPE_6__* bandInfo ; 
 int /*<<< orphan*/  debug1 (char*,scalar_t__) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,long) ; 
 void* get1bit (TYPE_2__*) ; 
 void* getbits (TYPE_2__*,int const) ; 
 int getbits_fast (TYPE_2__*,int const) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int III_get_side_info(mpg123_handle *fr, struct III_sideinfo *si,int stereo, int ms_stereo,long sfreq,int single)
{
	int ch, gr;
	int powdiff = (single == SINGLE_MIX) ? 4 : 0;

	const int tabs[2][5] = { { 2,9,5,3,4 } , { 1,8,1,2,9 } };
	const int *tab = tabs[fr->lsf];

	si->main_data_begin = getbits(fr, tab[1]);

	if(si->main_data_begin > fr->bitreservoir)
	{
		if(!fr->to_ignore && VERBOSE2) fprintf(stderr, "Note: missing %d bytes in bit reservoir for frame %li\n", (int)(si->main_data_begin - fr->bitreservoir), (long)fr->num);

		/*  overwrite main_data_begin for the really available bit reservoir */
		backbits(fr, tab[1]);
		if(fr->lsf == 0)
		{
			fr->wordpointer[0] = (unsigned char) (fr->bitreservoir >> 1);
			fr->wordpointer[1] = (unsigned char) ((fr->bitreservoir & 1) << 7);
		}
		else fr->wordpointer[0] = (unsigned char) fr->bitreservoir;

		/* zero "side-info" data for a silence-frame
		without touching audio data used as bit reservoir for following frame */
		memset(fr->wordpointer+2, 0, fr->ssize-2);

		/* reread the new bit reservoir offset */
		si->main_data_begin = getbits(fr, tab[1]);
	}

	/* Keep track of the available data bytes for the bit reservoir.
	Think: Substract the 2 crc bytes in parser already? */
	fr->bitreservoir = fr->bitreservoir + fr->framesize - fr->ssize - (fr->error_protection ? 2 : 0);
	/* Limit the reservoir to the max for MPEG 1.0 or 2.x . */
	if(fr->bitreservoir > (unsigned int) (fr->lsf == 0 ? 511 : 255))
	fr->bitreservoir = (fr->lsf == 0 ? 511 : 255);

	/* Now back into less commented territory. It's code. It works. */

	if (stereo == 1)
	si->private_bits = getbits_fast(fr, tab[2]);
	else 
	si->private_bits = getbits_fast(fr, tab[3]);

	if(!fr->lsf) for(ch=0; ch<stereo; ch++)
	{
		si->ch[ch].gr[0].scfsi = -1;
		si->ch[ch].gr[1].scfsi = getbits_fast(fr, 4);
	}

	for (gr=0; gr<tab[0]; gr++)
	for (ch=0; ch<stereo; ch++)
	{
		register struct gr_info_s *gr_info = &(si->ch[ch].gr[gr]);

		gr_info->part2_3_length = getbits(fr, 12);
		gr_info->big_values = getbits(fr, 9);
		if(gr_info->big_values > 288)
		{
			if(NOQUIET) error("big_values too large!");
			gr_info->big_values = 288;
		}
		gr_info->pow2gain = fr->gainpow2+256 - getbits_fast(fr, 8) + powdiff;
		if(ms_stereo) gr_info->pow2gain += 2;
		gr_info->scalefac_compress = getbits(fr, tab[4]);
		if(gr_info->part2_3_length == 0)
		{
			if(gr_info->scalefac_compress > 0)
				debug1( "scalefac_compress _should_ be zero instead of %i"
				,	gr_info->scalefac_compress );
			gr_info->scalefac_compress = 0;
		}

		if(get1bit(fr))
		{ /* window switch flag  */
			int i;
			gr_info->block_type       = getbits_fast(fr, 2);
			gr_info->mixed_block_flag = get1bit(fr);
			gr_info->table_select[0]  = getbits_fast(fr, 5);
			gr_info->table_select[1]  = getbits_fast(fr, 5);
			/*
				table_select[2] not needed, because there is no region2,
				but to satisfy some verification tools we set it either.
			*/
			gr_info->table_select[2] = 0;
			for(i=0;i<3;i++)
			gr_info->full_gain[i] = gr_info->pow2gain + (getbits_fast(fr, 3)<<3);

			if(gr_info->block_type == 0)
			{
				if(NOQUIET) error("Blocktype == 0 and window-switching == 1 not allowed.");
				return 1;
			}

			/* region_count/start parameters are implicit in this case. */       
			if( (!fr->lsf || (gr_info->block_type == 2)) && !fr->mpeg25)
			{
				gr_info->region1start = 36>>1;
				gr_info->region2start = 576>>1;
			}
			else
			{
				if(fr->mpeg25)
				{ 
					int r0c,r1c;
					if((gr_info->block_type == 2) && (!gr_info->mixed_block_flag) ) r0c = 5;
					else r0c = 7;

					/* r0c+1+r1c+1 == 22, always. */
					r1c = 20 - r0c;
					gr_info->region1start = bandInfo[sfreq].longIdx[r0c+1] >> 1 ;
					gr_info->region2start = bandInfo[sfreq].longIdx[r0c+1+r1c+1] >> 1; 
				}
				else
				{
					gr_info->region1start = 54>>1;
					gr_info->region2start = 576>>1; 
				} 
			}
		}
		else
		{
			int i,r0c,r1c;
			for (i=0; i<3; i++)
			gr_info->table_select[i] = getbits_fast(fr, 5);

			r0c = getbits_fast(fr, 4); /* 0 .. 15 */
			r1c = getbits_fast(fr, 3); /* 0 .. 7 */
			gr_info->region1start = bandInfo[sfreq].longIdx[r0c+1] >> 1 ;

			/* max(r0c+r1c+2) = 15+7+2 = 24 */
			if(r0c+1+r1c+1 > 22) gr_info->region2start = 576>>1;
			else gr_info->region2start = bandInfo[sfreq].longIdx[r0c+1+r1c+1] >> 1;

			gr_info->block_type = 0;
			gr_info->mixed_block_flag = 0;
		}
		if(!fr->lsf) gr_info->preflag = get1bit(fr);

		gr_info->scalefac_scale = get1bit(fr);
		gr_info->count1table_select = get1bit(fr);
	}
	return 0;
}