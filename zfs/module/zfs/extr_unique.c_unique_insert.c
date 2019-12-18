#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int un_value; } ;
typedef  TYPE_1__ unique_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  avl_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  KM_SLEEP ; 
 int UNIQUE_MASK ; 
 scalar_t__ avl_find (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avl_insert (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* kmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  random_get_pseudo_bytes (void*,int) ; 
 int /*<<< orphan*/  unique_avl ; 
 int /*<<< orphan*/  unique_mtx ; 

uint64_t
unique_insert(uint64_t value)
{
	avl_index_t idx;
	unique_t *un = kmem_alloc(sizeof (unique_t), KM_SLEEP);

	un->un_value = value;

	mutex_enter(&unique_mtx);
	while (un->un_value == 0 || un->un_value & ~UNIQUE_MASK ||
	    avl_find(&unique_avl, un, &idx)) {
		mutex_exit(&unique_mtx);
		(void) random_get_pseudo_bytes((void*)&un->un_value,
		    sizeof (un->un_value));
		un->un_value &= UNIQUE_MASK;
		mutex_enter(&unique_mtx);
	}

	avl_insert(&unique_avl, un, idx);
	mutex_exit(&unique_mtx);

	return (un->un_value);
}