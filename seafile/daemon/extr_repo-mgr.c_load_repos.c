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
typedef  int /*<<< orphan*/  sqlite3 ;
typedef  int /*<<< orphan*/  SeafRepoManager ;

/* Variables and functions */
 int /*<<< orphan*/  load_repo_cb ; 
 int /*<<< orphan*/ * open_db (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  remove_deleted_repo ; 
 int /*<<< orphan*/  seaf_warning (char*) ; 
 scalar_t__ sqlite_foreach_selected_row (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
load_repos (SeafRepoManager *manager, const char *seaf_dir)
{
    sqlite3 *db = open_db(manager, seaf_dir);
    if (!db) return;

    char *sql;

    sql = "SELECT repo_id FROM DeletedRepo";
    if (sqlite_foreach_selected_row (db, sql, remove_deleted_repo, manager) < 0) {
        seaf_warning ("Error removing deleted repos.\n");
        return;
    }

    sql = "SELECT repo_id FROM Repo;";
    if (sqlite_foreach_selected_row (db, sql, load_repo_cb, manager) < 0) {
        seaf_warning ("Error read repo db.\n");
        return;
    }
}