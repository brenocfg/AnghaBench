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

/* Variables and functions */
#define  UCDN_BIDI_CLASS_AL 141 
#define  UCDN_BIDI_CLASS_AN 140 
#define  UCDN_BIDI_CLASS_B 139 
#define  UCDN_BIDI_CLASS_BN 138 
#define  UCDN_BIDI_CLASS_CS 137 
#define  UCDN_BIDI_CLASS_EN 136 
#define  UCDN_BIDI_CLASS_ES 135 
#define  UCDN_BIDI_CLASS_ET 134 
#define  UCDN_BIDI_CLASS_L 133 
#define  UCDN_BIDI_CLASS_NSM 132 
#define  UCDN_BIDI_CLASS_ON 131 
#define  UCDN_BIDI_CLASS_R 130 
#define  UCDN_BIDI_CLASS_S 129 
#define  UCDN_BIDI_CLASS_WS 128 

__attribute__((used)) static int
direction_from_bidi_class(int bidiclass, int curdir)
{
	switch (bidiclass)
	{
	/* strong */
	case UCDN_BIDI_CLASS_L: return 1;
	case UCDN_BIDI_CLASS_R: return -1;
	case UCDN_BIDI_CLASS_AL: return -1;

	/* weak */
	case UCDN_BIDI_CLASS_EN:
	case UCDN_BIDI_CLASS_ES:
	case UCDN_BIDI_CLASS_ET:
	case UCDN_BIDI_CLASS_AN:
	case UCDN_BIDI_CLASS_CS:
	case UCDN_BIDI_CLASS_NSM:
	case UCDN_BIDI_CLASS_BN:
		return curdir;

	/* neutral */
	case UCDN_BIDI_CLASS_B:
	case UCDN_BIDI_CLASS_S:
	case UCDN_BIDI_CLASS_WS:
	case UCDN_BIDI_CLASS_ON:
		return curdir;

	/* embedding, override, pop ... we don't support them */
	default:
		return 0;
	}
}