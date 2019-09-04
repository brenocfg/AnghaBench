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
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  GList ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * g_list_prepend (int /*<<< orphan*/ *,char*) ; 
 char* g_strdup (char const*) ; 
 scalar_t__ sqlite3_column_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static gboolean
get_garbage_repo_id (sqlite3_stmt *stmt, void *vid_list)
{
    GList **ret = vid_list;
    char *repo_id;

    repo_id = g_strdup((const char *)sqlite3_column_text (stmt, 0));
    *ret = g_list_prepend (*ret, repo_id);

    return TRUE;
}