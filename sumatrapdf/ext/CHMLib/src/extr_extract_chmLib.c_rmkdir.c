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
 scalar_t__ dir_exists (char*) ; 
 int /*<<< orphan*/  mkdir (char*,int) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static int rmkdir(char *path)
{
    /*
     * strip off trailing components unless we can stat the directory, or we
     * have run out of components
     */

    char *i = strrchr(path, '/');

    if(path[0] == '\0'  ||  dir_exists(path))
        return 0;

    if (i != NULL)
    {
        *i = '\0';
        rmkdir(path);
        *i = '/';
        mkdir(path, 0777);
    }

#ifdef WIN32
        return 0;
#else
    if (dir_exists(path))
        return 0;
    else
        return -1;
#endif
}