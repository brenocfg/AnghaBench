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
struct stat {scalar_t__ st_dev; scalar_t__ st_ino; } ;

/* Variables and functions */
 scalar_t__ ERANGE ; 
 char* ToLocaleDup (char const*) ; 
 int /*<<< orphan*/  _PC_PATH_MAX ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * getcwd (char*,size_t) ; 
 char* getenv (char*) ; 
 char* malloc (size_t) ; 
 long pathconf (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ stat (char const*,struct stat*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

char *vlc_getcwd (void)
{
    /* Try $PWD */
    const char *pwd = getenv ("PWD");
    if (pwd != NULL)
    {
        struct stat s1, s2;
        /* Make sure $PWD is correct */
        if (stat (pwd, &s1) == 0 && stat (".", &s2) == 0
         && s1.st_dev == s2.st_dev && s1.st_ino == s2.st_ino)
            return ToLocaleDup (pwd);
    }

    /* Otherwise iterate getcwd() until the buffer is big enough */
    long path_max = pathconf (".", _PC_PATH_MAX);
    size_t size = (path_max == -1 || path_max > 4096) ? 4096 : path_max;

    for (;; size *= 2)
    {
        char *buf = malloc (size);
        if (unlikely(buf == NULL))
            break;

        if (getcwd (buf, size) != NULL)
        {
            char *ret = ToLocaleDup (buf);
            free (buf);
            return ret; /* success */
        }
        free (buf);

        if (errno != ERANGE)
            break;
    }
    return NULL;
}