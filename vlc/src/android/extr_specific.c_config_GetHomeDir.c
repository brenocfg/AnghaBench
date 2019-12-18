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
 int asprintf (char**,char*,char*,char const*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 char* strdup (char const*) ; 
 int vlc_mkdir (char*,int) ; 

__attribute__((used)) static char *config_GetHomeDir(const char *psz_dir, const char *psz_default_dir)
{
    char *psz_home = getenv("HOME");
    if (psz_home == NULL)
        goto fallback;

    if (psz_dir == NULL)
        return strdup(psz_home);

    char *psz_fullpath;
    if (asprintf(&psz_fullpath, "%s/%s", psz_home, psz_dir) == -1)
        goto fallback;
    if (vlc_mkdir(psz_fullpath, 0700) == -1 && errno != EEXIST)
    {
        free(psz_fullpath);
        goto fallback;
    }
    return psz_fullpath;

fallback:
    return psz_default_dir != NULL ? strdup(psz_default_dir) : NULL;
}