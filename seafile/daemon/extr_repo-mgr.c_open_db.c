#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_5__ {TYPE_1__* priv; } ;
struct TYPE_4__ {int /*<<< orphan*/ * db; } ;
typedef  TYPE_2__ SeafRepoManager ;

/* Variables and functions */
 char* g_build_filename (char const*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 scalar_t__ sqlite_open_db (char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  sqlite_query_exec (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static sqlite3*
open_db (SeafRepoManager *manager, const char *seaf_dir)
{
    sqlite3 *db;
    char *db_path;

    db_path = g_build_filename (seaf_dir, "repo.db", NULL);
    if (sqlite_open_db (db_path, &db) < 0)
        return NULL;
    g_free (db_path);
    manager->priv->db = db;

    char *sql = "CREATE TABLE IF NOT EXISTS Repo (repo_id TEXT PRIMARY KEY);";
    sqlite_query_exec (db, sql);

    sql = "CREATE TABLE IF NOT EXISTS DeletedRepo (repo_id TEXT PRIMARY KEY);";
    sqlite_query_exec (db, sql);

    sql = "CREATE TABLE IF NOT EXISTS RepoBranch ("
        "repo_id TEXT PRIMARY KEY, branch_name TEXT);";
    sqlite_query_exec (db, sql);

    sql = "CREATE TABLE IF NOT EXISTS RepoLanToken ("
        "repo_id TEXT PRIMARY KEY, token TEXT);";
    sqlite_query_exec (db, sql);

    sql = "CREATE TABLE IF NOT EXISTS RepoTmpToken ("
        "repo_id TEXT, peer_id TEXT, token TEXT, timestamp INTEGER, "
        "PRIMARY KEY (repo_id, peer_id));";
    sqlite_query_exec (db, sql);

    sql = "CREATE TABLE IF NOT EXISTS RepoPasswd "
        "(repo_id TEXT PRIMARY KEY, passwd TEXT NOT NULL);";
    sqlite_query_exec (db, sql);

    sql = "CREATE TABLE IF NOT EXISTS RepoKeys "
        "(repo_id TEXT PRIMARY KEY, key TEXT NOT NULL, iv TEXT NOT NULL);";
    sqlite_query_exec (db, sql);
    
    sql = "CREATE TABLE IF NOT EXISTS RepoProperty ("
        "repo_id TEXT, key TEXT, value TEXT);";
    sqlite_query_exec (db, sql);

    sql = "CREATE INDEX IF NOT EXISTS RepoIndex ON RepoProperty (repo_id);";
    sqlite_query_exec (db, sql);

    sql = "CREATE TABLE IF NOT EXISTS MergeInfo ("
        "repo_id TEXT PRIMARY KEY, in_merge INTEGER, branch TEXT);";
    sqlite_query_exec (db, sql);

    sql = "CREATE TABLE IF NOT EXISTS CommonAncestor ("
        "repo_id TEXT PRIMARY KEY, ca_id TEXT, head_id TEXT);";
    sqlite_query_exec (db, sql);

    /* Version 1 repos will be added to this table after deletion.
     * GC will scan this table and remove the objects and blocks for the repos.
     */
    sql = "CREATE TABLE IF NOT EXISTS GarbageRepos (repo_id TEXT PRIMARY KEY);";
    sqlite_query_exec (db, sql);

    sql = "CREATE TABLE IF NOT EXISTS LockedFiles (repo_id TEXT, path TEXT, "
        "operation TEXT, old_mtime INTEGER, file_id TEXT, new_path TEXT, "
        "PRIMARY KEY (repo_id, path));";
    sqlite_query_exec (db, sql);

    sql = "CREATE TABLE IF NOT EXISTS FolderUserPerms ("
        "repo_id TEXT, path TEXT, permission TEXT);";
    sqlite_query_exec (db, sql);

    sql = "CREATE INDEX IF NOT EXISTS folder_user_perms_repo_id_idx "
        "ON FolderUserPerms (repo_id);";
    sqlite_query_exec (db, sql);

    sql = "CREATE TABLE IF NOT EXISTS FolderGroupPerms ("
        "repo_id TEXT, path TEXT, permission TEXT);";
    sqlite_query_exec (db, sql);

    sql = "CREATE INDEX IF NOT EXISTS folder_group_perms_repo_id_idx "
        "ON FolderGroupPerms (repo_id);";
    sqlite_query_exec (db, sql);

    sql = "CREATE TABLE IF NOT EXISTS FolderPermTimestamp ("
        "repo_id TEXT, timestamp INTEGER, PRIMARY KEY (repo_id));";
    sqlite_query_exec (db, sql);

    sql = "CREATE TABLE IF NOT EXISTS ServerProperty ("
        "server_url TEXT, key TEXT, value TEXT, PRIMARY KEY (server_url, key));";
    sqlite_query_exec (db, sql);

    sql = "CREATE INDEX IF NOT EXISTS ServerIndex ON ServerProperty (server_url);";
    sqlite_query_exec (db, sql);

    sql = "CREATE TABLE IF NOT EXISTS FileSyncError ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, repo_id TEXT, repo_name TEXT, "
        "path TEXT, err_id INTEGER, timestamp INTEGER);";
    sqlite_query_exec (db, sql);

    sql = "CREATE INDEX IF NOT EXISTS FileSyncErrorIndex ON FileSyncError (repo_id, path)";
    sqlite_query_exec (db, sql);

    return db;
}