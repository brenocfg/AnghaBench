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
typedef  int /*<<< orphan*/  sqlite3 ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  SQLITE_STATIC ; 
 int /*<<< orphan*/  sqlite3_bind_blob (int /*<<< orphan*/ *,int,void const*,int,int /*<<< orphan*/ ) ; 
 int sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int sqlite3_prepare_v2 (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_step (int /*<<< orphan*/ *) ; 

int sqlite3_mm_set_cipher_key(sqlite3 *db, const void *key, int key_len)
{
    sqlite3_stmt *stmt;
    int ret =
        sqlite3_prepare_v2(db, "SELECT mm_cipher_key(?)", -1, &stmt, NULL);
    if (ret != SQLITE_OK)
        return ret;

    sqlite3_bind_blob(stmt, 1, key, key_len, SQLITE_STATIC);
    sqlite3_step(stmt);

    return sqlite3_finalize(stmt);
}