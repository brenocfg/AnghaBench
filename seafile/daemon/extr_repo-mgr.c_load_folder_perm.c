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
typedef  int /*<<< orphan*/  FolderPerm ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * folder_perm_new (char const*,char const*) ; 
 int /*<<< orphan*/ * g_list_prepend (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_column_text (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static gboolean
load_folder_perm (sqlite3_stmt *stmt, void *data)
{
    GList **p_perms = data;
    const char *path, *permission;

    path = (const char *)sqlite3_column_text (stmt, 0);
    permission = (const char *)sqlite3_column_text (stmt, 1);

    FolderPerm *perm = folder_perm_new (path, permission);
    *p_perms = g_list_prepend (*p_perms, perm);

    return TRUE;
}