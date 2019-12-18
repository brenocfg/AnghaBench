#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  st_ctime; int /*<<< orphan*/  st_mtime; } ;
typedef  TYPE_1__ SeafStat ;

/* Variables and functions */
 scalar_t__ _fstat64 (int,TYPE_1__*) ; 
 int fstat (int,TYPE_1__*) ; 
 scalar_t__ get_utc_file_time_fd (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

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