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
struct mmio_rb_tree {int dummy; } ;
struct mem_range {scalar_t__ base; scalar_t__ size; } ;
struct mmio_rb_range {scalar_t__ mr_end; scalar_t__ mr_base; struct mem_range mr_param; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  free (struct mmio_rb_range*) ; 
 struct mmio_rb_range* malloc (int) ; 
 int mmio_rb_add (struct mmio_rb_tree*,struct mmio_rb_range*) ; 
 scalar_t__ mmio_rb_lookup (struct mmio_rb_tree*,scalar_t__,struct mmio_rb_range**) ; 
 int /*<<< orphan*/  mmio_rwlock ; 
 int /*<<< orphan*/  pthread_rwlock_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_rwlock_wrlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
register_mem_int(struct mmio_rb_tree *rbt, struct mem_range *memp)
{
	struct mmio_rb_range *entry, *mrp;
	int		err;

	err = 0;

	mrp = malloc(sizeof(struct mmio_rb_range));
	
	if (mrp != NULL) {
		mrp->mr_param = *memp;
		mrp->mr_base = memp->base;
		mrp->mr_end = memp->base + memp->size - 1;
		pthread_rwlock_wrlock(&mmio_rwlock);
		if (mmio_rb_lookup(rbt, memp->base, &entry) != 0)
			err = mmio_rb_add(rbt, mrp);
		pthread_rwlock_unlock(&mmio_rwlock);
		if (err)
			free(mrp);
	} else
		err = ENOMEM;

	return (err);
}