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
 int SEAF_PATH_MAX ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 char* g_strdup (char*) ; 
 scalar_t__ seaf_stat (char*,TYPE_1__*) ; 
 scalar_t__ seaf_util_mkdir (char*,int) ; 
 int /*<<< orphan*/  seaf_warning (char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 int strlen (char const*) ; 

char *
build_checkout_path (const char *worktree, const char *ce_name, int len)
{
    int base_len = strlen(worktree);
    int full_len;
    char path[SEAF_PATH_MAX];
    int offset;
    SeafStat st;

    if (!len) {
        seaf_warning ("entry name should not be empty.\n");
        return NULL;
    }

    snprintf (path, SEAF_PATH_MAX, "%s/", worktree);

    /* first create all leading directories. */
    full_len = base_len + len + 1;
    offset = base_len + 1;
    while (offset < full_len) {
        do {
            path[offset] = ce_name[offset-base_len-1];
            offset++;
        } while (offset < full_len && ce_name[offset-base_len-1] != '/');
        if (offset >= full_len)
            break;
        path[offset] = 0;

        if (seaf_stat (path, &st) == 0 && S_ISDIR(st.st_mode))
            continue;
        
        if (seaf_util_mkdir (path, 0777) < 0) {
            seaf_warning ("Failed to create directory %s.\n", path);
            return NULL;
        }
    }
    path[offset] = 0;

    return g_strdup(path);
}