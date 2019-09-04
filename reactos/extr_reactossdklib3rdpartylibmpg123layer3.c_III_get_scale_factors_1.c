#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct gr_info_s {size_t scalefac_compress; scalar_t__ part2_3_length; int block_type; int scfsi; scalar_t__ mixed_block_flag; } ;
typedef  int /*<<< orphan*/  mpg123_handle ;

/* Variables and functions */
 void* getbits_fast (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int III_get_scale_factors_1(mpg123_handle *fr, int *scf,struct gr_info_s *gr_info,int ch,int gr)
{
	const unsigned char slen[2][16] =
	{
		{0, 0, 0, 0, 3, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4},
		{0, 1, 2, 3, 0, 1, 2, 3, 1, 2, 3, 1, 2, 3, 2, 3}
	};
	int numbits;
	int num0 = slen[0][gr_info->scalefac_compress];
	int num1 = slen[1][gr_info->scalefac_compress];

	if(gr_info->part2_3_length == 0)
	{
		int i;
		for(i=0;i<39;i++)
			*scf++ = 0;
		return 0;
	}

	if(gr_info->block_type == 2)
	{
		int i=18;
		numbits = (num0 + num1) * 18;

		if(gr_info->mixed_block_flag)
		{
			for (i=8;i;i--)
			*scf++ = getbits_fast(fr, num0);

			i = 9;
			numbits -= num0; /* num0 * 17 + num1 * 18 */
		}

		for(;i;i--) *scf++ = getbits_fast(fr, num0);

		for(i = 18; i; i--) *scf++ = getbits_fast(fr, num1);

		*scf++ = 0; *scf++ = 0; *scf++ = 0; /* short[13][0..2] = 0 */
	}
	else
	{
		int i;
		int scfsi = gr_info->scfsi;

		if(scfsi < 0)
		{ /* scfsi < 0 => granule == 0 */
			for(i=11;i;i--) *scf++ = getbits_fast(fr, num0);

			for(i=10;i;i--) *scf++ = getbits_fast(fr, num1);

			numbits = (num0 + num1) * 10 + num0;
			*scf++ = 0;
		}
		else
		{
			numbits = 0;
			if(!(scfsi & 0x8))
			{
				for (i=0;i<6;i++) *scf++ = getbits_fast(fr, num0);

				numbits += num0 * 6;
			}
			else scf += 6; 

			if(!(scfsi & 0x4))
			{
				for (i=0;i<5;i++) *scf++ = getbits_fast(fr, num0);

				numbits += num0 * 5;
			}
			else scf += 5;

			if(!(scfsi & 0x2))
			{
				for(i=0;i<5;i++) *scf++ = getbits_fast(fr, num1);

				numbits += num1 * 5;
			}
			else scf += 5;

			if(!(scfsi & 0x1))
			{
				for (i=0;i<5;i++) *scf++ = getbits_fast(fr, num1);

				numbits += num1 * 5;
			}
			else scf += 5;

			*scf++ = 0;  /* no l[21] in original sources */
		}
	}
	return numbits;
}