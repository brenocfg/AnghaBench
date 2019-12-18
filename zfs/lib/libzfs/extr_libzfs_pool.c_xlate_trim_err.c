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
#define  EBUSY 133 
#define  EINVAL 132 
#define  ENODEV 131 
#define  EOPNOTSUPP 130 
#define  EROFS 129 
#define  ESRCH 128 
 int EZFS_BADDEV ; 
 int EZFS_NODEVICE ; 
 int EZFS_NO_TRIM ; 
 int EZFS_TRIMMING ; 
 int EZFS_TRIM_NOTSUP ; 

__attribute__((used)) static int
xlate_trim_err(int err)
{
	switch (err) {
	case ENODEV:
		return (EZFS_NODEVICE);
	case EINVAL:
	case EROFS:
		return (EZFS_BADDEV);
	case EBUSY:
		return (EZFS_TRIMMING);
	case ESRCH:
		return (EZFS_NO_TRIM);
	case EOPNOTSUPP:
		return (EZFS_TRIM_NOTSUP);
	}
	return (err);
}