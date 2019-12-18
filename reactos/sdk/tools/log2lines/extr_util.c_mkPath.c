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
 scalar_t__ EEXIST ; 
 int MKDIR (char*) ; 
 char PATH_CHAR ; 
 scalar_t__ errno ; 
 char* strrchr (char*,char) ; 

int
mkPath(char *path, int isDir)
{
    char *s;
    int res = 0;

    if (isDir)
    {
        res = MKDIR(path);
        if (!res || (res == -1 && errno == EEXIST))
            return 0;
    }
    // create parent dir
    if ((s = strrchr(path, PATH_CHAR)))
    {
        *s = '\0';
        res = mkPath(path, 1);
        *s = PATH_CHAR;
    }

    if (!res && isDir)
        res = MKDIR(path);

    return res;
}