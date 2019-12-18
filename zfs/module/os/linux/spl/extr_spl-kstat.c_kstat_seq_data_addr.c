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
typedef  int loff_t ;
typedef  int /*<<< orphan*/  kstat_timer_t ;
struct TYPE_5__ {void* (* addr ) (TYPE_2__*,int) ;} ;
struct TYPE_6__ {int ks_type; int ks_data; TYPE_1__ ks_raw_ops; } ;
typedef  TYPE_2__ kstat_t ;
typedef  int /*<<< orphan*/  kstat_named_t ;
typedef  int /*<<< orphan*/  kstat_io_t ;
typedef  int /*<<< orphan*/  kstat_intr_t ;

/* Variables and functions */
#define  KSTAT_TYPE_INTR 132 
#define  KSTAT_TYPE_IO 131 
#define  KSTAT_TYPE_NAMED 130 
#define  KSTAT_TYPE_RAW 129 
#define  KSTAT_TYPE_TIMER 128 
 int /*<<< orphan*/  PANIC (char*,int) ; 
 void* stub1 (TYPE_2__*,int) ; 

__attribute__((used)) static void *
kstat_seq_data_addr(kstat_t *ksp, loff_t n)
{
	void *rc = NULL;

	switch (ksp->ks_type) {
		case KSTAT_TYPE_RAW:
			if (ksp->ks_raw_ops.addr)
				rc = ksp->ks_raw_ops.addr(ksp, n);
			else
				rc = ksp->ks_data;
			break;
		case KSTAT_TYPE_NAMED:
			rc = ksp->ks_data + n * sizeof (kstat_named_t);
			break;
		case KSTAT_TYPE_INTR:
			rc = ksp->ks_data + n * sizeof (kstat_intr_t);
			break;
		case KSTAT_TYPE_IO:
			rc = ksp->ks_data + n * sizeof (kstat_io_t);
			break;
		case KSTAT_TYPE_TIMER:
			rc = ksp->ks_data + n * sizeof (kstat_timer_t);
			break;
		default:
			PANIC("Undefined kstat type %d\n", ksp->ks_type);
	}

	return (rc);
}