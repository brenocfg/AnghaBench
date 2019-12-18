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
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 scalar_t__ const UCONV_BOM_NORMAL ; 
 scalar_t__ const UCONV_BOM_SWAPPED ; 
 int UCONV_IN_NAT_ENDIAN ; 
 int UCONV_IN_REV_ENDIAN ; 

__attribute__((used)) static boolean_t
check_bom16(const uint16_t *u16s, size_t u16l, int *in)
{
	if (u16l > 0) {
		if (*u16s == UCONV_BOM_NORMAL) {
			*in = UCONV_IN_NAT_ENDIAN;
			return (B_TRUE);
		}
		if (*u16s == UCONV_BOM_SWAPPED) {
			*in = UCONV_IN_REV_ENDIAN;
			return (B_TRUE);
		}
	}

	return (B_FALSE);
}