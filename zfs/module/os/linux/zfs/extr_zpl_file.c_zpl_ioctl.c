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
struct file {int dummy; } ;

/* Variables and functions */
 long ENOTTY ; 
#define  FS_IOC_GETFLAGS 131 
#define  FS_IOC_SETFLAGS 130 
#define  ZFS_IOC_FSGETXATTR 129 
#define  ZFS_IOC_FSSETXATTR 128 
 long zpl_ioctl_getflags (struct file*,void*) ; 
 long zpl_ioctl_getxattr (struct file*,void*) ; 
 long zpl_ioctl_setflags (struct file*,void*) ; 
 long zpl_ioctl_setxattr (struct file*,void*) ; 

__attribute__((used)) static long
zpl_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	switch (cmd) {
	case FS_IOC_GETFLAGS:
		return (zpl_ioctl_getflags(filp, (void *)arg));
	case FS_IOC_SETFLAGS:
		return (zpl_ioctl_setflags(filp, (void *)arg));
	case ZFS_IOC_FSGETXATTR:
		return (zpl_ioctl_getxattr(filp, (void *)arg));
	case ZFS_IOC_FSSETXATTR:
		return (zpl_ioctl_setxattr(filp, (void *)arg));
	default:
		return (-ENOTTY);
	}
}