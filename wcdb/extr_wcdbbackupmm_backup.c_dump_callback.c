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
struct TYPE_5__ {char* condition; } ;
typedef  TYPE_1__ mm_backup_tabdesc ;
struct TYPE_6__ {int flags; int writable_schema; int /*<<< orphan*/  num_tabdesc; scalar_t__ tabdesc; scalar_t__ canceled; } ;
typedef  TYPE_2__ mm_backup_ctx ;

/* Variables and functions */
 int MMBAK_FLAG_FIX_CORRUPTION ; 
 int MMBAK_FLAG_NO_CREATE_TABLE ; 
 int /*<<< orphan*/  MMBAK_TAG_SQL_ONESHOT ; 
 int SQLITE_CORRUPT ; 
 int SQLITE_OK ; 
 scalar_t__ bsearch (char const*,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compar_table_tabdesc ; 
 int dump_rows (TYPE_2__*,char const*,char const*,int) ; 
 scalar_t__ dump_write_blob (TYPE_2__*,int /*<<< orphan*/ ,char const*,...) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  sqlite3_strglob (char*,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  string_literal (char*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 

__attribute__((used)) static int
dump_callback(void *ud, int num_columns, char **values, char **columns)
{
    mm_backup_ctx *ctx = (mm_backup_ctx *) ud;
    const char *table = values[0];
    const char *type = values[1];
    const char *sql = values[2];
    int ret;

    // check exit status.
    if (ctx->canceled)
        return -1;

    // deal with system tables.
    if (!strcmp(table, "sqlite_sequence")) {
        if (dump_write_blob(ctx, MMBAK_TAG_SQL_ONESHOT,
                            string_literal("DELETE FROM sqlite_sequence;")) !=
            0)
            return -1;
    } else if (!sqlite3_strglob("sqlite_stat?", table)) {
        if (dump_write_blob(ctx, MMBAK_TAG_SQL_ONESHOT,
                            string_literal("ANALYZE sqlite_master;")))
            return -1;
    } else if (!strncmp(table, "sqlite_", 7)) {
        return 0;
    }

    // find whether in dump list.
    const char *table_condition = NULL;
    if (ctx->tabdesc) {
        const mm_backup_tabdesc *desc = (const mm_backup_tabdesc *) bsearch(
            table, ctx->tabdesc, ctx->num_tabdesc, sizeof(mm_backup_tabdesc),
            compar_table_tabdesc);
        if (!desc)
            return 0;

        table_condition = desc->condition;
    }

    if (!strncmp(sql, "CREATE VIRTUAL TABLE", 20)) {
        if (!(ctx->flags & MMBAK_FLAG_NO_CREATE_TABLE)) {
            if (!ctx->writable_schema) {
                if (dump_write_blob(
                        ctx, MMBAK_TAG_SQL_ONESHOT,
                        string_literal("PRAGMA writable_schema=ON;")))
                    return -1;
                ctx->writable_schema = 1;
            }

            char *vt_sql = sqlite3_mprintf(
                "INSERT INTO sqlite_master(type,name,tbl_name,rootpage,sql)"
                "VALUES('table','%q','%q',0,'%q');",
                table, table, sql);
            if (dump_write_blob(ctx, MMBAK_TAG_SQL_ONESHOT, vt_sql, -1))
                return -1;
            sqlite3_free(vt_sql);
        }

        return 0;
    } else if (!(ctx->flags & MMBAK_FLAG_NO_CREATE_TABLE)) {
        if (dump_write_blob(ctx, MMBAK_TAG_SQL_ONESHOT, sql, -1))
            return -1;
    }

    // for tables, dump all rows.
    if (!strcmp(type, "table")) {
        ret = dump_rows(ctx, table, table_condition, 0);
        if (ret == SQLITE_CORRUPT && !table_condition &&
            (ctx->flags & MMBAK_FLAG_FIX_CORRUPTION)) {
            ret = dump_rows(ctx, table, table_condition, 1);
            if (ret == SQLITE_CORRUPT)
                ret = SQLITE_OK;
        }
        if (ret != SQLITE_OK)
            return -1;
    }
    return 0;
}