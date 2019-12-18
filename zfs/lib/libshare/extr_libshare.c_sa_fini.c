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
typedef  TYPE_1__* sa_share_impl_t ;
typedef  int /*<<< orphan*/  sa_handle_t ;
typedef  TYPE_2__* sa_handle_impl_t ;
struct TYPE_8__ {TYPE_1__* shares; int /*<<< orphan*/ * zfs_libhandle; } ;
struct TYPE_7__ {struct TYPE_7__* next; int /*<<< orphan*/ * dataset; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  free_share (TYPE_1__*) ; 
 int /*<<< orphan*/  libzfs_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sa_disable_share (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_sharetab (TYPE_2__*) ; 

void
sa_fini(sa_handle_t handle)
{
	sa_handle_impl_t impl_handle = (sa_handle_impl_t)handle;
	sa_share_impl_t impl_share, next;
	sa_share_impl_t *pcurr;

	if (impl_handle == NULL)
		return;

	/*
	 * clean up shares which don't have a non-NULL dataset property,
	 * which means they're in sharetab but we couldn't find their
	 * ZFS dataset.
	 */
	pcurr = &(impl_handle->shares);
	impl_share = *pcurr;
	while (impl_share != NULL) {
		next = impl_share->next;

		if (impl_share->dataset == NULL) {
			/* remove item from the linked list */
			*pcurr = next;

			sa_disable_share(impl_share, NULL);

			free_share(impl_share);
		} else {
			pcurr = &(impl_share->next);
		}

		impl_share = next;
	}

	update_sharetab(impl_handle);

	if (impl_handle->zfs_libhandle != NULL)
		libzfs_fini(impl_handle->zfs_libhandle);

	impl_share = impl_handle->shares;
	while (impl_share != NULL) {
		next = impl_share->next;
		free_share(impl_share);
		impl_share = next;
	}

	free(impl_handle);
}