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
typedef  int /*<<< orphan*/  SeafStat ;

/* Variables and functions */
 int fstat (int,int /*<<< orphan*/ *) ; 

int
seaf_fstat (int fd, SeafStat *st)
{
#ifdef WIN32
    if (_fstat64 (fd, st) < 0)
        return -1;

    if (get_utc_file_time_fd (fd, &st->st_mtime, &st->st_ctime) < 0)
        return -1;

    return 0;
#else
    return fstat (fd, st);
#endif
}