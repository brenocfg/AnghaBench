#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  st_mode; } ;
typedef  TYPE_1__ SeafStat ;

/* Variables and functions */
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_strdup (char const*) ; 
 scalar_t__ seaf_stat (char const*,TYPE_1__*) ; 
 int strlen (char*) ; 

int
checkdir (const char *dir)
{
    SeafStat st;

#ifdef WIN32
    /* remove trailing '\\' */
    char *path = g_strdup(dir);
    char *p = (char *)path + strlen(path) - 1;
    while (*p == '\\' || *p == '/') *p-- = '\0';
    if ((seaf_stat(dir, &st) < 0) || !S_ISDIR(st.st_mode)) {
        g_free (path);
        return -1;
    }
    g_free (path);
    return 0;
#else
    if ((seaf_stat(dir, &st) < 0) || !S_ISDIR(st.st_mode))
        return -1;
    return 0;
#endif
}