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
typedef  int /*<<< orphan*/  wchar_t ;
struct stat {int dummy; } ;
struct _stati64 {int dummy; } ;

/* Variables and functions */
 int _wstati64 (int /*<<< orphan*/ *,struct stat*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  static_assert (int,char*) ; 
 int /*<<< orphan*/ * widen_path (char const*) ; 

int vlc_stat (const char *filename, struct stat *buf)
{
    wchar_t *wpath = widen_path (filename);
    if (wpath == NULL)
        return -1;

    static_assert (sizeof (*buf) == sizeof (struct _stati64),
                   "Mismatched struct stat definition.");

    int ret = _wstati64 (wpath, buf);
    free (wpath);
    return ret;
}