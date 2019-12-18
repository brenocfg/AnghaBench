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
typedef  int /*<<< orphan*/  gint64 ;

/* Variables and functions */
 int /*<<< orphan*/  _lseeki64 (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lseek (int,int /*<<< orphan*/ ,int) ; 

gint64
seaf_util_lseek (int fd, gint64 offset, int whence)
{
#ifdef WIN32
    return _lseeki64 (fd, offset, whence);
#else
    return lseek (fd, offset, whence);
#endif
}