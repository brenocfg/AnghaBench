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
 char* FromWide (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * _wgetcwd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

char *vlc_getcwd (void)
{
#if VLC_WINSTORE_APP
    return NULL;
#else
    wchar_t *wdir = _wgetcwd (NULL, 0);
    if (wdir == NULL)
        return NULL;

    char *dir = FromWide (wdir);
    free (wdir);
    return dir;
#endif
}