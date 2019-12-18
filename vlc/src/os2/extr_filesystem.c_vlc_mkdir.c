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
typedef  int /*<<< orphan*/  mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 char* ToLocaleDup (char const*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int mkdir (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int vlc_mkdir (const char *dirname, mode_t mode)
{
    char *locname = ToLocaleDup (dirname);
    if (unlikely(locname == NULL))
    {
        errno = ENOENT;
        return -1;
    }

    int res = mkdir (locname, mode);
    free (locname);
    return res;
}