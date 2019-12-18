#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* z_sb; } ;
typedef  TYPE_2__ zfsvfs_t ;
struct TYPE_4__ {int /*<<< orphan*/  s_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESRCH ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc_not_zero (int /*<<< orphan*/ *) ; 

int
zfs_vfs_ref(zfsvfs_t **zfvp)
{
	if (*zfvp == NULL || (*zfvp)->z_sb == NULL ||
	    !atomic_inc_not_zero(&((*zfvp)->z_sb->s_active))) {
		return (SET_ERROR(ESRCH));
	}
	return (0);
}