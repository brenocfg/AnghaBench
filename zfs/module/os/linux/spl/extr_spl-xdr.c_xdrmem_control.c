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
struct xdr_bytesrec {scalar_t__ xc_num_avail; int /*<<< orphan*/  xc_is_last_record; } ;
typedef  int /*<<< orphan*/  bool_t ;
struct TYPE_3__ {scalar_t__ x_addr; scalar_t__ x_addr_end; } ;
typedef  TYPE_1__ XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int XDR_GET_BYTES_AVAIL ; 

__attribute__((used)) static bool_t
xdrmem_control(XDR *xdrs, int req, void *info)
{
	struct xdr_bytesrec *rec = (struct xdr_bytesrec *)info;

	if (req != XDR_GET_BYTES_AVAIL)
		return (FALSE);

	rec->xc_is_last_record = TRUE; /* always TRUE in xdrmem streams */
	rec->xc_num_avail = xdrs->x_addr_end - xdrs->x_addr;

	return (TRUE);
}