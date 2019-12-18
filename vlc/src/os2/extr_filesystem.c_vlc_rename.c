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
 int /*<<< orphan*/  ENOENT ; 
 char* ToLocaleDup (char const*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char const*) ; 
 int rename (char const*,char const*) ; 

int vlc_rename (const char *oldpath, const char *newpath)
{
    const char *lo = ToLocaleDup (oldpath);
    if (lo == NULL)
        goto error;

    const char *ln = ToLocaleDup (newpath);
    if (ln == NULL)
    {
        free (lo);
error:
        errno = ENOENT;
        return -1;
    }

    int ret = rename (lo, ln);
    free (lo);
    free (ln);
    return ret;
}