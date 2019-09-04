#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  seaf_dir; } ;
typedef  int /*<<< orphan*/  SeafRepoManager ;

/* Variables and functions */
 char* g_build_filename (int /*<<< orphan*/ ,char*,char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  g_rename (char*,char*) ; 
 char* gen_deleted_store_path (char const*,char const*) ; 
 TYPE_1__* seaf ; 

void
seaf_repo_manager_move_repo_store (SeafRepoManager *mgr,
                                   const char *type,
                                   const char *repo_id)
{
    char *src = NULL;
    char *dst = NULL;

    src = g_build_filename (seaf->seaf_dir, "storage", type, repo_id, NULL);
    dst = gen_deleted_store_path (type, repo_id);
    if (dst) {
        g_rename (src, dst);
    }
    g_free (src);
    g_free (dst);
}