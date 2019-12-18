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
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 char* ToLocaleDup (char const*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char const*) ; 
 int /*<<< orphan*/ * opendir (char const*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

DIR *vlc_opendir (const char *dirname)
{
    const char *locname = ToLocaleDup (dirname);
    if (unlikely(locname == NULL))
    {
        errno = ENOENT;
        return NULL;
    }

    DIR *dir = opendir (locname);

    free (locname);

    return dir;
}