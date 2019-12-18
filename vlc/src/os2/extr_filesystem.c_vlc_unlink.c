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
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int unlink (char const*) ; 

int vlc_unlink (const char *filename)
{
    const char *local_name = ToLocaleDup (filename);
    if (unlikely(local_name == NULL))
    {
        errno = ENOENT;
        return -1;
    }

    int ret = unlink (local_name);
    free (local_name);
    return ret;
}