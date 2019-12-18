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
struct seq_file {scalar_t__ private; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_3__ {scalar_t__ ks_magic; scalar_t__ ks_ndata; } ;
typedef  TYPE_1__ kstat_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ KS_MAGIC ; 
 void* kstat_seq_data_addr (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static void *
kstat_seq_next(struct seq_file *f, void *p, loff_t *pos)
{
	kstat_t *ksp = (kstat_t *)f->private;
	ASSERT(ksp->ks_magic == KS_MAGIC);

	++*pos;
	if (*pos >= ksp->ks_ndata)
		return (NULL);

	return (kstat_seq_data_addr(ksp, *pos));
}