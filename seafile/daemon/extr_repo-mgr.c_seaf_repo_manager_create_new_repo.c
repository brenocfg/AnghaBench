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
typedef  int /*<<< orphan*/  SeafRepoManager ;
typedef  int /*<<< orphan*/  SeafRepo ;

/* Variables and functions */
 int /*<<< orphan*/  g_free (char*) ; 
 char* gen_uuid () ; 
 int /*<<< orphan*/  seaf_repo_manager_add_repo (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * seaf_repo_new (char*,char const*,char const*) ; 

SeafRepo*
seaf_repo_manager_create_new_repo (SeafRepoManager *mgr,
                                   const char *name,
                                   const char *desc)
{
    SeafRepo *repo;
    char *repo_id;
    
    repo_id = gen_uuid ();
    repo = seaf_repo_new (repo_id, name, desc);
    if (!repo) {
        g_free (repo_id);
        return NULL;
    }
    g_free (repo_id);

    /* we directly create dir because it shouldn't exist */
    /* if (seaf_repo_mkdir (repo, base) < 0) { */
    /*     seaf_repo_free (repo); */
    /*     goto out; */
    /* } */

    seaf_repo_manager_add_repo (mgr, repo);
    return repo;
}