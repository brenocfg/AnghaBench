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
typedef  int /*<<< orphan*/  stat_t ;

/* Variables and functions */
 int _stat64 (char const*,int /*<<< orphan*/ *) ; 
 int stat (char const*,int /*<<< orphan*/ *) ; 

int UTIL_fileExist(const char* filename)
{
    stat_t statbuf;
#if defined(_MSC_VER)
    int const stat_error = _stat64(filename, &statbuf);
#else
    int const stat_error = stat(filename, &statbuf);
#endif
    return !stat_error;
}