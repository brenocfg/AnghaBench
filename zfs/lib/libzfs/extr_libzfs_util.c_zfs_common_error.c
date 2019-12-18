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
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;

/* Variables and functions */
#define  EACCES 133 
#define  ECANCELED 132 
#define  EFAULT 131 
#define  EINTR 130 
#define  EIO 129 
#define  EPERM 128 
 int /*<<< orphan*/  EZFS_FAULT ; 
 int /*<<< orphan*/  EZFS_INTR ; 
 int /*<<< orphan*/  EZFS_IO ; 
 int /*<<< orphan*/  EZFS_NODELEGATION ; 
 int /*<<< orphan*/  EZFS_PERM ; 
 int /*<<< orphan*/  zfs_verror (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zfs_common_error(libzfs_handle_t *hdl, int error, const char *fmt,
    va_list ap)
{
	switch (error) {
	case EPERM:
	case EACCES:
		zfs_verror(hdl, EZFS_PERM, fmt, ap);
		return (-1);

	case ECANCELED:
		zfs_verror(hdl, EZFS_NODELEGATION, fmt, ap);
		return (-1);

	case EIO:
		zfs_verror(hdl, EZFS_IO, fmt, ap);
		return (-1);

	case EFAULT:
		zfs_verror(hdl, EZFS_FAULT, fmt, ap);
		return (-1);

	case EINTR:
		zfs_verror(hdl, EZFS_INTR, fmt, ap);
		return (-1);
	}

	return (0);
}