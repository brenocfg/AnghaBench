#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int zs_minor; struct TYPE_7__* zs_next; } ;
typedef  TYPE_2__ zfsdev_state_t ;
typedef  int minor_t ;
struct TYPE_8__ {TYPE_1__* f_file; } ;
typedef  TYPE_3__ file_t ;
struct TYPE_6__ {TYPE_2__* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  EBADF ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 TYPE_3__* getf (int) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 TYPE_2__* zfsdev_state_list ; 
 int /*<<< orphan*/  zfsdev_state_lock ; 

int
zfsdev_getminor(int fd, minor_t *minorp)
{
	zfsdev_state_t *zs, *fpd;
	file_t *fp;

	ASSERT(!MUTEX_HELD(&zfsdev_state_lock));
	fp = getf(fd);

	if (fp == NULL)
		return (SET_ERROR(EBADF));

	fpd = fp->f_file->private_data;
	if (fpd == NULL)
		return (SET_ERROR(EBADF));

	mutex_enter(&zfsdev_state_lock);

	for (zs = zfsdev_state_list; zs != NULL; zs = zs->zs_next) {

		if (zs->zs_minor == -1)
			continue;

		if (fpd == zs) {
			*minorp = fpd->zs_minor;
			mutex_exit(&zfsdev_state_lock);
			return (0);
		}
	}

	mutex_exit(&zfsdev_state_lock);

	return (SET_ERROR(EBADF));
}