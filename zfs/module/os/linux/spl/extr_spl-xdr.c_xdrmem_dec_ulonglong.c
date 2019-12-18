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
typedef  int u_longlong_t ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  xdrmem_dec_uint32 (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static bool_t
xdrmem_dec_ulonglong(XDR *xdrs, u_longlong_t *ullp)
{
	uint32_t low, high;

	BUILD_BUG_ON(sizeof (u_longlong_t) != 8);

	if (!xdrmem_dec_uint32(xdrs, &high))
		return (FALSE);
	if (!xdrmem_dec_uint32(xdrs, &low))
		return (FALSE);

	*ullp = ((u_longlong_t)high << 32) | low;

	return (TRUE);
}