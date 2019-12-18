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
typedef  scalar_t__ uint_t ;
typedef  enum xdr_op { ____Placeholder_xdr_op } xdr_op ;
typedef  scalar_t__ caddr_t ;
struct TYPE_3__ {int x_op; scalar_t__ x_addr; scalar_t__ x_addr_end; int /*<<< orphan*/ * x_ops; } ;
typedef  TYPE_1__ XDR ;

/* Variables and functions */
#define  XDR_DECODE 129 
#define  XDR_ENCODE 128 
 int /*<<< orphan*/  xdrmem_decode_ops ; 
 int /*<<< orphan*/  xdrmem_encode_ops ; 

void
xdrmem_create(XDR *xdrs, const caddr_t addr, const uint_t size,
    const enum xdr_op op)
{
	switch (op) {
		case XDR_ENCODE:
			xdrs->x_ops = &xdrmem_encode_ops;
			break;
		case XDR_DECODE:
			xdrs->x_ops = &xdrmem_decode_ops;
			break;
		default:
			xdrs->x_ops = NULL; /* Let the caller know we failed */
			return;
	}

	xdrs->x_op = op;
	xdrs->x_addr = addr;
	xdrs->x_addr_end = addr + size;

	if (xdrs->x_addr_end < xdrs->x_addr) {
		xdrs->x_ops = NULL;
	}
}