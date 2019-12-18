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
struct TYPE_3__ {int ks_raw_bufsize; int /*<<< orphan*/  ks_raw_buf; } ;
typedef  TYPE_1__ kstat_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int KSTAT_RAW_MAX ; 
 int MIN (int,int) ; 
 int /*<<< orphan*/  vmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmem_free (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
kstat_resize_raw(kstat_t *ksp)
{
	if (ksp->ks_raw_bufsize == KSTAT_RAW_MAX)
		return (ENOMEM);

	vmem_free(ksp->ks_raw_buf, ksp->ks_raw_bufsize);
	ksp->ks_raw_bufsize = MIN(ksp->ks_raw_bufsize * 2, KSTAT_RAW_MAX);
	ksp->ks_raw_buf = vmem_alloc(ksp->ks_raw_bufsize, KM_SLEEP);

	return (0);
}