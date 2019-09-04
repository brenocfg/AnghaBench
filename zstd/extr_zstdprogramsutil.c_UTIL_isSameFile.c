#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ st_dev; scalar_t__ st_ino; } ;
typedef  TYPE_1__ stat_t ;

/* Variables and functions */
 scalar_t__ UTIL_getFileStat (char const*,TYPE_1__*) ; 

int UTIL_isSameFile(const char* file1, const char* file2)
{
#if defined(_MSC_VER)
    /* note : Visual does not support file identification by inode.
     *        The following work-around is limited to detecting exact name repetition only,
     *        aka `filename` is considered different from `subdir/../filename` */
    return !strcmp(file1, file2);
#else
    stat_t file1Stat;
    stat_t file2Stat;
    return UTIL_getFileStat(file1, &file1Stat)
        && UTIL_getFileStat(file2, &file2Stat)
        && (file1Stat.st_dev == file2Stat.st_dev)
        && (file1Stat.st_ino == file2Stat.st_ino);
#endif
}