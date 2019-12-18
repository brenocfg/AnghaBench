#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  json_t ;
typedef  int /*<<< orphan*/  gchar ;
struct TYPE_6__ {int enc_version; int /*<<< orphan*/  repo_id; scalar_t__ server_url; scalar_t__ is_readonly; scalar_t__ repo_salt; int /*<<< orphan*/ * repo_version; scalar_t__ random_key; scalar_t__ passwd; int /*<<< orphan*/  email; int /*<<< orphan*/  peer_port; int /*<<< orphan*/  peer_addr; int /*<<< orphan*/  worktree; int /*<<< orphan*/  peer_id; int /*<<< orphan*/  token; int /*<<< orphan*/  repo_name; } ;
struct TYPE_5__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ SeafCloneManager ;
typedef  TYPE_2__ CloneTask ;

/* Variables and functions */
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_dumps (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_integer (scalar_t__) ; 
 int /*<<< orphan*/ * json_object () ; 
 int /*<<< orphan*/  json_object_set_new (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_string (scalar_t__) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,int /*<<< orphan*/ ,int,...) ; 
 scalar_t__ sqlite_query_exec (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
save_task_to_db (SeafCloneManager *mgr, CloneTask *task)
{
    char *sql;

    if (task->passwd)
        sql = sqlite3_mprintf ("REPLACE INTO CloneTasks VALUES "
            "('%q', '%q', '%q', '%q', '%q', '%q', '%q', '%q', '%q')",
                                task->repo_id, task->repo_name,
                                task->token, task->peer_id,
                                task->worktree, task->passwd,
                                task->peer_addr, task->peer_port, task->email);
    else
        sql = sqlite3_mprintf ("REPLACE INTO CloneTasks VALUES "
            "('%q', '%q', '%q', '%q', '%q', NULL, '%q', '%q', '%q')",
                                task->repo_id, task->repo_name,
                                task->token, task->peer_id,
                                task->worktree, task->peer_addr,
                                task->peer_port, task->email);

    if (sqlite_query_exec (mgr->db, sql) < 0) {
        sqlite3_free (sql);
        return -1;
    }
    sqlite3_free (sql);

    if (task->passwd && task->enc_version >= 2 && task->random_key) {
        sql = sqlite3_mprintf ("REPLACE INTO CloneEncInfo VALUES "
                               "('%q', %d, '%q')",
                               task->repo_id, task->enc_version, task->random_key);
        if (sqlite_query_exec (mgr->db, sql) < 0) {
            sqlite3_free (sql);
            return -1;
        }
        sqlite3_free (sql);
    }

    sql = sqlite3_mprintf ("REPLACE INTO CloneVersionInfo VALUES "
                           "('%q', %d)",
                           task->repo_id, task->repo_version);
    if (sqlite_query_exec (mgr->db, sql) < 0) {
        sqlite3_free (sql);
        return -1;
    }
    sqlite3_free (sql);

    if (task->is_readonly || task->server_url || task->repo_salt) {
        /* need to store more info */
        json_t *object = NULL;
        gchar *info = NULL;

        object = json_object ();
        json_object_set_new (object, "is_readonly", json_integer (task->is_readonly));
        if (task->server_url)
            json_object_set_new (object, "server_url", json_string(task->server_url));
    
        info = json_dumps (object, 0);
        json_decref (object);
        sql = sqlite3_mprintf ("REPLACE INTO CloneTasksMoreInfo VALUES "
                           "('%q', '%q')", task->repo_id, info);
        if (sqlite_query_exec (mgr->db, sql) < 0) {
            sqlite3_free (sql);
            g_free (info);
            return -1;
        }
        sqlite3_free (sql);
        g_free (info);
    }

    return 0;
}