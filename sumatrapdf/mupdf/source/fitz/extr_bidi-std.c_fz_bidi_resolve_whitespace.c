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
typedef  int /*<<< orphan*/  fz_bidi_level ;
typedef  int fz_bidi_chartype ;

/* Variables and functions */
#define  BDI_B 136 
#define  BDI_BN 135 
#define  BDI_LRE 134 
#define  BDI_LRO 133 
#define  BDI_PDF 132 
#define  BDI_RLE 131 
#define  BDI_RLO 130 
#define  BDI_S 129 
#define  BDI_WS 128 
 int /*<<< orphan*/  set_deferred_level_run (int /*<<< orphan*/ *,size_t,size_t,int /*<<< orphan*/ ) ; 

void fz_bidi_resolve_whitespace(fz_bidi_level baselevel, const fz_bidi_chartype *pcls, fz_bidi_level *plevel,
				size_t cch)
{
	size_t cchrun = 0;
	fz_bidi_level oldlevel = baselevel;
	size_t ich;

	for (ich = 0; ich < cch; ich++)
	{
		switch(pcls[ich])
		{
		default:
			cchrun = 0; // any other character breaks the run
			break;
		case BDI_WS:
			cchrun++;
			break;

		case BDI_RLE:
		case BDI_LRE:
		case BDI_LRO:
		case BDI_RLO:
		case BDI_PDF:
		case BDI_BN:
			plevel[ich] = oldlevel;
			cchrun++;
			break;

		case BDI_S:
		case BDI_B:
			// reset levels for WS before eot
			set_deferred_level_run(plevel, cchrun, ich, baselevel);
			cchrun = 0;
			plevel[ich] = baselevel;
			break;
		}
		oldlevel = plevel[ich];
	}
	// reset level before eot
	set_deferred_level_run(plevel, cchrun, ich, baselevel);
}