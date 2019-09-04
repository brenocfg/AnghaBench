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
 char G_DIR_SEPARATOR ; 
 int SEAF_PATH_MAX ; 
 int checkdir_with_mkdir (char const*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int strlen (char const*) ; 

int
objstore_mkdir (const char *base)
{
    int ret;
    int i, j, len;
    static const char hex[] = "0123456789abcdef";
    char subdir[SEAF_PATH_MAX];

    if ( (ret = checkdir_with_mkdir(base)) < 0)
        return ret;

    len = strlen(base);
    memcpy(subdir, base, len);
    subdir[len] = G_DIR_SEPARATOR;
    subdir[len+3] = '\0';

    for (i = 0; i < 16; i++) {
        subdir[len+1] = hex[i];
        for (j = 0; j < 16; j++) {
            subdir[len+2] = hex[j];
            if ( (ret = checkdir_with_mkdir(subdir)) < 0)
                return ret;
        }
    }
    return 0;
}