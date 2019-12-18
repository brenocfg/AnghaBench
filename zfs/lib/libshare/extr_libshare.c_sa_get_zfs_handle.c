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
typedef  int /*<<< orphan*/  sa_handle_t ;
typedef  TYPE_1__* sa_handle_impl_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
struct TYPE_2__ {int /*<<< orphan*/ * zfs_libhandle; } ;

/* Variables and functions */

libzfs_handle_t *
sa_get_zfs_handle(sa_handle_t handle)
{
	sa_handle_impl_t impl_handle = (sa_handle_impl_t)handle;

	if (impl_handle == NULL)
		return (NULL);

	return (impl_handle->zfs_libhandle);
}