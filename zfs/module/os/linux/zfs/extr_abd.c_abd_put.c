#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int abd_flags; int /*<<< orphan*/  abd_children; int /*<<< orphan*/  abd_size; TYPE_1__* abd_parent; } ;
typedef  TYPE_2__ abd_t ;
struct TYPE_7__ {int /*<<< orphan*/  abd_children; } ;

/* Variables and functions */
 int ABD_FLAG_OWNER ; 
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  abd_free_struct (TYPE_2__*) ; 
 int /*<<< orphan*/  abd_verify (TYPE_2__*) ; 
 int /*<<< orphan*/  zfs_refcount_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_refcount_remove_many (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 

void
abd_put(abd_t *abd)
{
	abd_verify(abd);
	ASSERT(!(abd->abd_flags & ABD_FLAG_OWNER));

	if (abd->abd_parent != NULL) {
		(void) zfs_refcount_remove_many(&abd->abd_parent->abd_children,
		    abd->abd_size, abd);
	}

	zfs_refcount_destroy(&abd->abd_children);
	abd_free_struct(abd);
}