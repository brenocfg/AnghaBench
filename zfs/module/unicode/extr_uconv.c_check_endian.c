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
 int EBADF ; 
 int UCONV_IN_ENDIAN_MASKS ; 
 int UCONV_IN_NAT_ENDIAN ; 
 int UCONV_OUT_ENDIAN_MASKS ; 
 int UCONV_OUT_NAT_ENDIAN ; 

__attribute__((used)) static int
check_endian(int flag, int *in, int *out)
{
	*in = flag & UCONV_IN_ENDIAN_MASKS;

	/* You cannot have both. */
	if (*in == UCONV_IN_ENDIAN_MASKS)
		return (EBADF);

	if (*in == 0)
		*in = UCONV_IN_NAT_ENDIAN;

	*out = flag & UCONV_OUT_ENDIAN_MASKS;

	/* You cannot have both. */
	if (*out == UCONV_OUT_ENDIAN_MASKS)
		return (EBADF);

	if (*out == 0)
		*out = UCONV_OUT_NAT_ENDIAN;

	return (0);
}