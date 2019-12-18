#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ ddr_type; } ;
struct diffarg {int da_err; int* da_offp; TYPE_1__ da_ddr; int /*<<< orphan*/  da_vp; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CRED () ; 
 scalar_t__ DDR_NONE ; 
 int /*<<< orphan*/  FAPPEND ; 
 int /*<<< orphan*/  RLIM64_INFINITY ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  UIO_WRITE ; 
 int vn_rdwr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
write_record(struct diffarg *da)
{
	ssize_t resid; /* have to get resid to get detailed errno */

	if (da->da_ddr.ddr_type == DDR_NONE) {
		da->da_err = 0;
		return (0);
	}

	da->da_err = vn_rdwr(UIO_WRITE, da->da_vp, (caddr_t)&da->da_ddr,
	    sizeof (da->da_ddr), 0, UIO_SYSSPACE, FAPPEND,
	    RLIM64_INFINITY, CRED(), &resid);
	*da->da_offp += sizeof (da->da_ddr);
	return (da->da_err);
}