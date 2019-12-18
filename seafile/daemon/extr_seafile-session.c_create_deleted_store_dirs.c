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
 scalar_t__ checkdir_with_mkdir (char const*) ; 
 char* g_build_filename (char const*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  seaf_warning (char*,char const*) ; 

__attribute__((used)) static int
create_deleted_store_dirs (const char *deleted_store)
{
    char *commits = NULL, *fs = NULL, *blocks = NULL;
    int ret = 0;

    if (checkdir_with_mkdir (deleted_store) < 0) {
        seaf_warning ("Directory %s does not exist and is unable to create\n",
                      deleted_store);
        return -1;
    }

    commits = g_build_filename (deleted_store, "commits", NULL);
    if (checkdir_with_mkdir (commits) < 0) {
        seaf_warning ("Directory %s does not exist and is unable to create\n",
                      commits);
        ret = -1;
        goto out;
    }

    fs = g_build_filename (deleted_store, "fs", NULL);
    if (checkdir_with_mkdir (fs) < 0) {
        seaf_warning ("Directory %s does not exist and is unable to create\n",
                      fs);
        ret = -1;
        goto out;
    }

    blocks = g_build_filename (deleted_store, "blocks", NULL);
    if (checkdir_with_mkdir (blocks) < 0) {
        seaf_warning ("Directory %s does not exist and is unable to create\n",
                      blocks);
        ret = -1;
        goto out;
    }

out:
    g_free (commits);
    g_free (fs);
    g_free (blocks);
    return ret;
}