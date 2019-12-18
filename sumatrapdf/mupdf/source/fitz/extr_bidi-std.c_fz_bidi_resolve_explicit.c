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
typedef  scalar_t__ fz_bidi_level ;
typedef  int fz_bidi_chartype ;

/* Variables and functions */
 int BDI_BN ; 
 int BDI_L ; 
#define  BDI_LRE 132 
#define  BDI_LRO 131 
 int BDI_N ; 
#define  BDI_PDF 130 
 int BDI_R ; 
#define  BDI_RLE 129 
#define  BDI_RLO 128 
 scalar_t__ BIDI_LEVEL_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ greater_even (scalar_t__) ; 
 scalar_t__ greater_odd (scalar_t__) ; 

size_t fz_bidi_resolve_explicit(fz_bidi_level level, fz_bidi_chartype dir, fz_bidi_chartype *pcls, fz_bidi_level *plevel, size_t cch,
				fz_bidi_level n_nest)
{
	size_t ich;

	// always called with a valid nesting level
	// nesting levels are != embedding levels
	int nLastValid = n_nest;

	// check input values
	assert(n_nest >= 0 && level >= 0 && level <= BIDI_LEVEL_MAX);

	// process the text
	for (ich = 0; ich < cch; ich++)
	{
		fz_bidi_chartype cls = pcls[ich];
		switch (cls)
		{
		case BDI_LRO:
		case BDI_LRE:
			n_nest++;
			if (greater_even(level) <= BIDI_LEVEL_MAX)
			{
				plevel[ich] = greater_even(level);
				pcls[ich] = BDI_BN;
				ich += fz_bidi_resolve_explicit(plevel[ich], (cls == BDI_LRE ? BDI_N : BDI_L),
							&pcls[ich+1], &plevel[ich+1],
							 cch - (ich+1), n_nest);
				n_nest--;
				continue;
			}
			cls = pcls[ich] = BDI_BN;
			break;

		case BDI_RLO:
		case BDI_RLE:
			n_nest++;
			if (greater_odd(level) <= BIDI_LEVEL_MAX)
			{
				plevel[ich] = greater_odd(level);
				pcls[ich] = BDI_BN;
				ich += fz_bidi_resolve_explicit(plevel[ich], (cls == BDI_RLE ? BDI_N : BDI_R),
								&pcls[ich+1], &plevel[ich+1],
								 cch - (ich+1), n_nest);
				n_nest--;
				continue;
			}
			cls = pcls[ich] = BDI_BN;
			break;

		case BDI_PDF:
			cls = pcls[ich] = BDI_BN;
			if (n_nest)
			{
				if (nLastValid < n_nest)
				{
					n_nest--;
				}
				else
				{
					cch = ich; // break the loop, but complete body
				}
			}
			break;
		}

		// Apply the override
		if (dir != BDI_N)
		{
			cls = dir;
		}
		plevel[ich] = level;
		if (pcls[ich] != BDI_BN)
			pcls[ich] = cls;
	}

	return ich;
}