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
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_2__ {int /*<<< orphan*/  err_id; void* path; void* repo_id; } ;
typedef  TYPE_1__ FileErrorAux ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 void* g_strdup (char const*) ; 
 int /*<<< orphan*/  sqlite3_column_int (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sqlite3_column_text (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static gboolean
get_last_file_sync_error (sqlite3_stmt *stmt, void *data)
{
    FileErrorAux *aux = data;

    aux->repo_id = g_strdup((const char *)sqlite3_column_text (stmt, 0));
    aux->path = g_strdup((const char *)sqlite3_column_text (stmt, 1));
    aux->err_id = sqlite3_column_int (stmt, 2);

    return FALSE;
}