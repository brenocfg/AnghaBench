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
typedef  int /*<<< orphan*/  sqlite3 ;
typedef  int /*<<< orphan*/  X509_STORE ;
struct TYPE_2__ {int /*<<< orphan*/  seaf_dir; } ;

/* Variables and functions */
 char* g_build_filename (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  load_certs ; 
 TYPE_1__* seaf ; 
 int /*<<< orphan*/  seaf_warning (char*) ; 
 int /*<<< orphan*/  sqlite_close_db (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite_foreach_selected_row (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite_open_db (char*,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int
load_certs_from_db (X509_STORE *store)
{
    char *cert_db_path = NULL;
    sqlite3 *db = NULL;
    char *sql;
    int ret = 0;

    cert_db_path = g_build_filename (seaf->seaf_dir, "certs.db", NULL);
    if (sqlite_open_db (cert_db_path, &db) < 0) {
        seaf_warning ("Failed to open certs.db\n");
        ret = -1;
        goto out;
    }

    sql = "SELECT cert FROM Certs;";

    if (sqlite_foreach_selected_row (db, sql, load_certs, store) < 0) {
        ret = -1;
        goto out;
    }

out:
    g_free (cert_db_path);
    if (db)
        sqlite_close_db (db);

    return ret;
}