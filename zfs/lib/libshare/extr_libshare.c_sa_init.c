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
struct sa_handle_impl {int dummy; } ;
typedef  int /*<<< orphan*/ * sa_handle_t ;
typedef  TYPE_1__* sa_handle_impl_t ;
struct TYPE_5__ {int /*<<< orphan*/ * zfs_libhandle; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/ * libzfs_init () ; 
 int /*<<< orphan*/  libzfs_print_on_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_sharetab (TYPE_1__*) ; 
 int /*<<< orphan*/  update_zfs_shares (TYPE_1__*,int /*<<< orphan*/ *) ; 

sa_handle_t
sa_init(int init_service)
{
	sa_handle_impl_t impl_handle;

	impl_handle = calloc(1, sizeof (struct sa_handle_impl));

	if (impl_handle == NULL)
		return (NULL);

	impl_handle->zfs_libhandle = libzfs_init();

	if (impl_handle->zfs_libhandle != NULL) {
		libzfs_print_on_error(impl_handle->zfs_libhandle, B_TRUE);
	}

	parse_sharetab(impl_handle);
	update_zfs_shares(impl_handle, NULL);

	return ((sa_handle_t)impl_handle);
}