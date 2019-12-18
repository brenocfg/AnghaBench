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
#define  BDI_AL 130 
#define  BDI_L 129 
#define  BDI_R 128 
 int /*<<< orphan*/  FZ_BIDI_LTR ; 
 int /*<<< orphan*/  FZ_BIDI_RTL ; 

__attribute__((used)) static fz_bidi_level base_level_from_text(fz_bidi_chartype *types, size_t len)
{
	size_t i;

	for (i = 0; i < len; i++)
	{
		switch (types[i])
		{
		/* strong left */
		case BDI_L:
			return FZ_BIDI_LTR;

		/* strong right */
		case BDI_R:
		case BDI_AL:
			return FZ_BIDI_RTL;
		}
	}
	return FZ_BIDI_LTR;
}