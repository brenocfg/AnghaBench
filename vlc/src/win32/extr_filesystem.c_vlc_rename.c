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

/* Variables and functions */
 scalar_t__ EACCES ; 
 scalar_t__ EEXIST ; 
 scalar_t__ _wremove (int /*<<< orphan*/ *) ; 
 scalar_t__ _wrename (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * widen_path (char const*) ; 

int vlc_rename (const char *oldpath, const char *newpath)
{
    int ret = -1;

    wchar_t *wold = widen_path (oldpath), *wnew = widen_path (newpath);
    if (wold == NULL || wnew == NULL)
        goto out;

    if (_wrename (wold, wnew) && (errno == EACCES || errno == EEXIST))
    {   /* Windows does not allow atomic file replacement */
        if (_wremove (wnew))
        {
            errno = EACCES; /* restore errno */
            goto out;
        }
        if (_wrename (wold, wnew))
            goto out;
    }
    ret = 0;
out:
    free (wnew);
    free (wold);
    return ret;
}