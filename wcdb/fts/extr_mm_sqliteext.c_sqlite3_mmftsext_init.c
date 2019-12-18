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
typedef  int /*<<< orphan*/  sqlite3_api_routines ;
typedef  int /*<<< orphan*/  sqlite3 ;

/* Variables and functions */
 int SQLITE_ERROR ; 
 int /*<<< orphan*/  SQLITE_EXTENSION_INIT2 (int /*<<< orphan*/  const*) ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  g_default_key ; 
 scalar_t__ init_icucompat () ; 
 char* sqlite3_errmsg (int /*<<< orphan*/ *) ; 
 char* sqlite3_mprintf (char*,...) ; 
 int sqlite3_register_mm_cipher (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sqlite3_register_mm_tokenizer (int /*<<< orphan*/ *) ; 
 int sqlite3_register_mm_utils (int /*<<< orphan*/ *) ; 

int sqlite3_mmftsext_init(sqlite3 *db,
							char **pzErrMsg,
							const sqlite3_api_routines *pApi)
{
    int rc;
    const char *errmsg;
    SQLITE_EXTENSION_INIT2(pApi);

    // Load and initialize ICU library.
    if (init_icucompat() != 0) {
        *pzErrMsg = sqlite3_mprintf("failed to load ICU library.");
        return SQLITE_ERROR;
    }

    // Register tokenizer.
    rc = sqlite3_register_mm_tokenizer(db);
    if (rc != SQLITE_OK)
        goto bail;

    // Register text cipher.
    rc = sqlite3_register_mm_cipher(db, g_default_key);
    if (rc != SQLITE_OK)
        goto bail;

    // Register utility functions.
    rc = sqlite3_register_mm_utils(db);
    if (rc != SQLITE_OK)
        goto bail;

    *pzErrMsg = NULL;
    return SQLITE_OK;

bail:
    errmsg = sqlite3_errmsg(db);
    if (!errmsg)
        errmsg = "";
    *pzErrMsg = sqlite3_mprintf(
        "Failed to register SQLite functions: %s, ErrCode: %d", errmsg, rc);
    return rc;
}