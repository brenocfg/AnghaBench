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
struct kiocb {int ki_flags; } ;

/* Variables and functions */
 int FAPPEND ; 
 int FDIRECT ; 
 int FDSYNC ; 
 int FSYNC ; 
 int IOCB_APPEND ; 
 int IOCB_DIRECT ; 
 int IOCB_DSYNC ; 
 int IOCB_SYNC ; 

__attribute__((used)) static inline int
zfs_io_flags(struct kiocb *kiocb)
{
	int flags = 0;

#if defined(IOCB_DSYNC)
	if (kiocb->ki_flags & IOCB_DSYNC)
		flags |= FDSYNC;
#endif
#if defined(IOCB_SYNC)
	if (kiocb->ki_flags & IOCB_SYNC)
		flags |= FSYNC;
#endif
#if defined(IOCB_APPEND)
	if (kiocb->ki_flags & IOCB_APPEND)
		flags |= FAPPEND;
#endif
#if defined(IOCB_DIRECT)
	if (kiocb->ki_flags & IOCB_DIRECT)
		flags |= FDIRECT;
#endif
	return (flags);
}