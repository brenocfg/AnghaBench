#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int nvs_op; int /*<<< orphan*/ * nvs_private; } ;
typedef  TYPE_1__ nvstream_t ;
struct TYPE_6__ {int /*<<< orphan*/  nvl_nvflag; int /*<<< orphan*/  nvl_version; } ;
typedef  TYPE_2__ nvlist_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
#define  NVS_OP_DECODE 130 
#define  NVS_OP_ENCODE 129 
#define  NVS_OP_GETSIZE 128 
 int /*<<< orphan*/  xdr_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_u_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nvs_xdr_nvlist(nvstream_t *nvs, nvlist_t *nvl, size_t *size)
{
	switch (nvs->nvs_op) {
	case NVS_OP_ENCODE:
	case NVS_OP_DECODE: {
		XDR 	*xdr = nvs->nvs_private;

		if (!xdr_int(xdr, &nvl->nvl_version) ||
		    !xdr_u_int(xdr, &nvl->nvl_nvflag))
			return (EFAULT);
		break;
	}
	case NVS_OP_GETSIZE: {
		/*
		 * 2 * 4 for nvl_version + nvl_nvflag
		 * and 8 for end of the entire list
		 */
		*size += 2 * 4 + 8;
		break;
	}
	default:
		return (EINVAL);
	}
	return (0);
}