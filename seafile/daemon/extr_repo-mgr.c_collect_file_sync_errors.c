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
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  gint64 ;
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  SeafileFileSyncError ;
typedef  int /*<<< orphan*/  GList ;

/* Variables and functions */
 int /*<<< orphan*/  SEAFILE_TYPE_FILE_SYNC_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * g_list_prepend (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_object_new (int /*<<< orphan*/ ,char*,int,char*,char const*,char*,char const*,char*,char const*,char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sqlite3_column_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_column_int64 (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sqlite3_column_text (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static gboolean
collect_file_sync_errors (sqlite3_stmt *stmt, void *data)
{
    GList **pret = data;
    const char *repo_id, *repo_name, *path;
    int id, err_id;
    gint64 timestamp;
    SeafileFileSyncError *error;

    id = sqlite3_column_int (stmt, 0);
    repo_id = (const char *)sqlite3_column_text (stmt, 1);
    repo_name = (const char *)sqlite3_column_text (stmt, 2);
    path = (const char *)sqlite3_column_text (stmt, 3);
    err_id = sqlite3_column_int (stmt, 4);
    timestamp = sqlite3_column_int64 (stmt, 5);

    error = g_object_new (SEAFILE_TYPE_FILE_SYNC_ERROR,
                          "id", id,
                          "repo_id", repo_id,
                          "repo_name", repo_name,
                          "path", path,
                          "err_id", err_id,
                          "timestamp", timestamp,
                          NULL);
    *pret = g_list_prepend (*pret, error);

    return TRUE;
}