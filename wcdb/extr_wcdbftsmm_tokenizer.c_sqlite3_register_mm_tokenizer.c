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
typedef  int /*<<< orphan*/  sqlite3_tokenizer_module ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  sqlite3 ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  SQLITE_STATIC ; 
 int /*<<< orphan*/  mm_tokenizer_module ; 
 int /*<<< orphan*/  sqlite3_bind_blob (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const**,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_bind_text (int /*<<< orphan*/ *,int,char*,int,int /*<<< orphan*/ ) ; 
 int sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int sqlite3_prepare_v2 (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_step (int /*<<< orphan*/ *) ; 

int sqlite3_register_mm_tokenizer(sqlite3 *db)
{
    const sqlite3_tokenizer_module *module = &mm_tokenizer_module;
    sqlite3_stmt *stmt = NULL;
    int result;

    result =
        sqlite3_prepare_v2(db, "SELECT fts3_tokenizer(?, ?)", -1, &stmt, 0);
    if (result != SQLITE_OK)
        return result;

    sqlite3_bind_text(stmt, 1, "mmicu", -1, SQLITE_STATIC);
    sqlite3_bind_blob(stmt, 2, &module, sizeof(sqlite3_tokenizer_module *),
                      SQLITE_STATIC);
    sqlite3_step(stmt);

    return sqlite3_finalize(stmt);
}