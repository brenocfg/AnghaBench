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
typedef  int /*<<< orphan*/  fz_bidi_direction ;
typedef  int fz_bidi_chartype ;

/* Variables and functions */
#define  BDI_AL 131 
#define  BDI_EN 130 
#define  BDI_L 129 
#define  BDI_R 128 
 int /*<<< orphan*/  FZ_BIDI_LTR ; 
 int /*<<< orphan*/  FZ_BIDI_NEUTRAL ; 
 int /*<<< orphan*/  FZ_BIDI_RTL ; 

__attribute__((used)) static fz_bidi_direction direction_from_type(fz_bidi_chartype type)
{
	switch (type)
	{
	case BDI_L:
	case BDI_EN:
		return FZ_BIDI_LTR;

	case BDI_R:
	case BDI_AL:
		return FZ_BIDI_RTL;

	default:
		return FZ_BIDI_NEUTRAL;
	}
}