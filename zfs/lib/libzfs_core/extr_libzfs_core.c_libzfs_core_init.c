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

/* Variables and functions */
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  ZFS_DEV ; 
 int errno ; 
 scalar_t__ g_fd ; 
 int /*<<< orphan*/  g_lock ; 
 scalar_t__ g_refcount ; 
 int /*<<< orphan*/  libzfs_core_debug_ioc () ; 
 scalar_t__ open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

int
libzfs_core_init(void)
{
	(void) pthread_mutex_lock(&g_lock);
	if (g_refcount == 0) {
		g_fd = open(ZFS_DEV, O_RDWR);
		if (g_fd < 0) {
			(void) pthread_mutex_unlock(&g_lock);
			return (errno);
		}
	}
	g_refcount++;

#ifdef ZFS_DEBUG
	libzfs_core_debug_ioc();
#endif
	(void) pthread_mutex_unlock(&g_lock);
	return (0);
}