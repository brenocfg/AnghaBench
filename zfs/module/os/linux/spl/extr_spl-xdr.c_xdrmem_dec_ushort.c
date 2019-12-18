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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  xdrmem_dec_uint32 (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static bool_t
xdrmem_dec_ushort(XDR *xdrs, unsigned short *usp)
{
	uint32_t val;

	BUILD_BUG_ON(sizeof (unsigned short) != 2);

	if (!xdrmem_dec_uint32(xdrs, &val))
		return (FALSE);

	/*
	 * Short ints are not in the RFC, but we assume similar logic as in
	 * xdrmem_dec_char().
	 */
	if (val > 0xffff)
		return (FALSE);

	*usp = val;

	return (TRUE);
}