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
typedef  char uint32_t ;
typedef  int fz_bidi_chartype ;

/* Variables and functions */
#define  BDI_AL 135 
#define  BDI_EN 134 
#define  BDI_L 133 
#define  BDI_LRE 132 
 int BDI_PDF ; 
#define  BDI_R 131 
#define  BDI_RLE 130 
 int FALSE ; 
#define  FZ_BIDI_LTR 129 
#define  FZ_BIDI_RTL 128 
 int TRUE ; 
 int direction_from_type (int) ; 

__attribute__((used)) static void
classify_quoted_blocks(const uint32_t *text,
		fz_bidi_chartype *types,
		size_t len)
{
	size_t i;
	int inQuote = FALSE;
	int pdfNeeded = FALSE;
	int ltrFound = FALSE;
	int rtlFound = FALSE;

	/* Only do anything special here if there is mixed content
	 * (LTR *and* RTL) in the text.
	 */
	for (i = 0; i < len; i++)
	{
		switch (direction_from_type(types[i]))
		{
		case FZ_BIDI_LTR:
			ltrFound = TRUE;
			break;

		case FZ_BIDI_RTL:
			rtlFound = TRUE;
			break;

		default:
			break;
		}
	}

	/* Only make any changes if *both* LTR and RTL characters exist
	 * in this text.
	 */
	if (!ltrFound || !rtlFound)
	{
		return;
	}

	for (i = 0; i < len; i++)
	{
		if (text[i]=='"')
		{
			/* If we're already in a quote then terminate it,
			 * else start a new block.
			 */
			if (inQuote)
			{
				inQuote = FALSE;
				if (pdfNeeded)
				{
					pdfNeeded = FALSE;
					types[i] = BDI_PDF;
				}
			}
			else
			{
				size_t j;
				int done = FALSE;

				inQuote = TRUE;

				/* Find the first strong right or left type and
				 * use that to determine whether we should classify
				 * the quote as LRE or RLE. Or neither, if we
				 * hit another quote before any strongly-directional
				 * character.
				 */
				for (j = i + 1; !done && (j < len) && text[j] != '"'; ++j)
				{
					switch(types[j])
					{
					case BDI_RLE:
					case BDI_LRE:
						done = TRUE;
						break;

					case BDI_L:
					case BDI_EN:
						types[i] = BDI_LRE;
						pdfNeeded = TRUE;
						done = TRUE;
						break;

					case BDI_R:
					case BDI_AL:
						types[i] = BDI_RLE;
						pdfNeeded = TRUE;
						done = TRUE;
						break;

					default:
						break;
					}
				}
			}
		}
	}
}