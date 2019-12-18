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
struct stat {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 char* ToLocaleDup (char const*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char const*) ; 
 int lstat (char const*,struct stat*) ; 
 int stat (char const*,struct stat*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vlc_statEx (const char *filename, struct stat *buf, bool deref)
{
    const char *local_name = ToLocaleDup (filename);
    if (unlikely(local_name == NULL))
    {
        errno = ENOENT;
        return -1;
    }

    int res = deref ? stat (local_name, buf)
                    : lstat (local_name, buf);
    free (local_name);
    return res;
}