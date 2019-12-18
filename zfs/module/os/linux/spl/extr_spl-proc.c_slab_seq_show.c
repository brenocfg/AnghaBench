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
struct seq_file {int dummy; } ;
struct TYPE_2__ {scalar_t__ skc_magic; int skc_flags; int skc_obj_size; int skc_obj_alloc; int skc_slab_size; int skc_slab_total; int /*<<< orphan*/  skc_lock; scalar_t__ skc_obj_emergency_max; scalar_t__ skc_obj_emergency; scalar_t__ skc_obj_deadlock; scalar_t__ skc_obj_max; scalar_t__ skc_obj_total; scalar_t__ skc_slab_max; scalar_t__ skc_slab_alloc; int /*<<< orphan*/  skc_name; } ;
typedef  TYPE_1__ spl_kmem_cache_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int KMC_SLAB ; 
 scalar_t__ SKC_MAGIC ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,unsigned long,...) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
slab_seq_show(struct seq_file *f, void *p)
{
	spl_kmem_cache_t *skc = p;

	ASSERT(skc->skc_magic == SKC_MAGIC);

	if (skc->skc_flags & KMC_SLAB) {
		/*
		 * This cache is backed by a generic Linux kmem cache which
		 * has its own accounting. For these caches we only track
		 * the number of active allocated objects that exist within
		 * the underlying Linux slabs. For the overall statistics of
		 * the underlying Linux cache please refer to /proc/slabinfo.
		 */
		spin_lock(&skc->skc_lock);
		seq_printf(f, "%-36s  ", skc->skc_name);
		seq_printf(f, "0x%05lx %9s %9lu %8s %8u  "
		    "%5s %5s %5s  %5s %5lu %5s  %5s %5s %5s\n",
		    (long unsigned)skc->skc_flags,
		    "-",
		    (long unsigned)(skc->skc_obj_size * skc->skc_obj_alloc),
		    "-",
		    (unsigned)skc->skc_obj_size,
		    "-", "-", "-", "-",
		    (long unsigned)skc->skc_obj_alloc,
		    "-", "-", "-", "-");
		spin_unlock(&skc->skc_lock);
		return (0);
	}

	spin_lock(&skc->skc_lock);
	seq_printf(f, "%-36s  ", skc->skc_name);
	seq_printf(f, "0x%05lx %9lu %9lu %8u %8u  "
	    "%5lu %5lu %5lu  %5lu %5lu %5lu  %5lu %5lu %5lu\n",
	    (long unsigned)skc->skc_flags,
	    (long unsigned)(skc->skc_slab_size * skc->skc_slab_total),
	    (long unsigned)(skc->skc_obj_size * skc->skc_obj_alloc),
	    (unsigned)skc->skc_slab_size,
	    (unsigned)skc->skc_obj_size,
	    (long unsigned)skc->skc_slab_total,
	    (long unsigned)skc->skc_slab_alloc,
	    (long unsigned)skc->skc_slab_max,
	    (long unsigned)skc->skc_obj_total,
	    (long unsigned)skc->skc_obj_alloc,
	    (long unsigned)skc->skc_obj_max,
	    (long unsigned)skc->skc_obj_deadlock,
	    (long unsigned)skc->skc_obj_emergency,
	    (long unsigned)skc->skc_obj_emergency_max);
	spin_unlock(&skc->skc_lock);
	return (0);
}