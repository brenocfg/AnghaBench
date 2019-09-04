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
 int /*<<< orphan*/  DbgP (char*,...) ; 
#define  IOCTL_NFS41_ADDCONN 135 
#define  IOCTL_NFS41_DELCONN 134 
#define  IOCTL_NFS41_GETSTATE 133 
#define  IOCTL_NFS41_INVALCACHE 132 
#define  IOCTL_NFS41_READ 131 
#define  IOCTL_NFS41_START 130 
#define  IOCTL_NFS41_STOP 129 
#define  IOCTL_NFS41_WRITE 128 

void print_fs_ioctl(int on, int op)
{
    if(!on) return;
    switch(op) {
        case IOCTL_NFS41_INVALCACHE:
            DbgP("IOCTL_NFS41_INVALCACHE\n");
            break;
        case IOCTL_NFS41_READ:
            DbgP("IOCTL_NFS41_UPCALL\n");
            break;
        case IOCTL_NFS41_WRITE:
            DbgP("IOCTL_NFS41_DOWNCALL\n");
            break;
        case IOCTL_NFS41_ADDCONN:
            DbgP("IOCTL_NFS41_ADDCONN\n");
            break;
        case IOCTL_NFS41_DELCONN:
            DbgP("IOCTL_NFS41_DELCONN\n");
            break;
        case IOCTL_NFS41_GETSTATE:
            DbgP("IOCTL_NFS41_GETSTATE\n");
            break;
        case IOCTL_NFS41_START:
            DbgP("IOCTL_NFS41_START\n");
            break;
        case IOCTL_NFS41_STOP:
            DbgP("IOCTL_NFS41_STOP\n");
            break;
        default:
            DbgP("UNKNOWN FS IOCTL %d\n", op);
    };
}