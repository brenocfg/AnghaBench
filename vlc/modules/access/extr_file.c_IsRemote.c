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
struct statvfs {int f_flag; } ;
struct statfs {scalar_t__ f_type; } ;

/* Variables and functions */
#define  AFS_SUPER_MAGIC 132 
#define  CODA_SUPER_MAGIC 131 
 int MNT_LOCAL ; 
#define  NCP_SUPER_MAGIC 130 
#define  NFS_SUPER_MAGIC 129 
#define  SMB_SUPER_MAGIC 128 
 scalar_t__ fstatfs (int,struct statfs*) ; 
 scalar_t__ fstatvfs (int,struct statvfs*) ; 

__attribute__((used)) static bool IsRemote (int fd)
{
#if defined (HAVE_FSTATVFS) && defined (MNT_LOCAL)
    struct statvfs stf;

    if (fstatvfs (fd, &stf))
        return false;
    /* fstatvfs() is in POSIX, but MNT_LOCAL is not */
    return !(stf.f_flag & MNT_LOCAL);

#elif defined (HAVE_LINUX_MAGIC_H)
    struct statfs stf;

    if (fstatfs (fd, &stf))
        return false;

    switch ((unsigned long)stf.f_type)
    {
        case AFS_SUPER_MAGIC:
        case CODA_SUPER_MAGIC:
        case NCP_SUPER_MAGIC:
        case NFS_SUPER_MAGIC:
        case SMB_SUPER_MAGIC:
        case 0xFF534D42 /*CIFS_MAGIC_NUMBER*/:
            return true;
    }
    return false;

#else
    (void)fd;
    return false;

#endif
}