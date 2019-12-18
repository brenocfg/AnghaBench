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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* LIBDIR ; 
 scalar_t__ config_GetLibDir ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 int sscanf (char*,char*,void**,void**) ; 
 char* strchr (char*,char) ; 
 char* strdup (char*) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static char *config_GetLibDirRaw(void)
{
    char *path = NULL;
    /* Find the path to libvlc (i.e. ourselves) */
    FILE *maps = fopen ("/proc/self/maps", "rte");
    if (maps == NULL)
        goto error;

    char *line = NULL;
    size_t linelen = 0;
    uintptr_t needle = (uintptr_t)config_GetLibDir;

    for (;;)
    {
        ssize_t len = getline (&line, &linelen, maps);
        if (len == -1)
            break;

        void *start, *end;
        if (sscanf (line, "%p-%p", &start, &end) < 2)
            continue;
        /* This mapping contains the address of this function. */
        if (needle < (uintptr_t)start || (uintptr_t)end <= needle)
            continue;

        char *dir = strchr (line, '/');
        if (dir == NULL)
            continue;

        char *file = strrchr (line, '/');
        if (end == NULL)
            continue;
        *file = '\0';

        path = strdup(dir);
        break;
    }

    free (line);
    fclose (maps);
error:
    if (path == NULL)
        path = strdup(LIBDIR);
    return path;
}