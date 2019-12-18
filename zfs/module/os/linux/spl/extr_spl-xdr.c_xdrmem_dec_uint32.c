#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  bool_t ;
struct TYPE_3__ {scalar_t__ x_addr; scalar_t__ x_addr_end; } ;
typedef  TYPE_1__ XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool_t
xdrmem_dec_uint32(XDR *xdrs, uint32_t *val)
{
	if (xdrs->x_addr + sizeof (uint32_t) > xdrs->x_addr_end)
		return (FALSE);

	*val = be32_to_cpu(*((uint32_t *)xdrs->x_addr));

	xdrs->x_addr += sizeof (uint32_t);

	return (TRUE);
}