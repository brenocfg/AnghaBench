#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_5__ {int ref_count; int /*<<< orphan*/  key; int /*<<< orphan*/  cnv; } ;
typedef  TYPE_1__ mm_cipher_context_t ;
typedef  int /*<<< orphan*/  UErrorCode ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_ANY ; 
 int SQLITE_ERROR ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  UCNV_IBM ; 
 int /*<<< orphan*/  U_ZERO_ERROR ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char const*,int) ; 
 int /*<<< orphan*/  mm_cipher_key_func ; 
 int /*<<< orphan*/  mm_func_destroy ; 
 int /*<<< orphan*/  mmdec_func ; 
 int /*<<< orphan*/  mmenc_func ; 
 int sqlite3_create_function_v2 (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_1__*) ; 
 TYPE_1__* sqlite3_malloc (int) ; 
 int /*<<< orphan*/  ucnv_openCCSID (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int sqlite3_register_mm_cipher(sqlite3 *db, const unsigned char *key)
{
    UErrorCode status = U_ZERO_ERROR;
    int sqlite_err;
    mm_cipher_context_t *ctx;

    // XXX: if we failed to load ICU functions, just skip initializing.
    if (!ucnv_openCCSID)
        return SQLITE_OK;

    ctx = sqlite3_malloc(sizeof(mm_cipher_context_t));
    if (!ctx)
        return SQLITE_NOMEM;

    sqlite_err = SQLITE_ERROR;
    // open converter using CCSID instead of converter name to hide "BOCU-1" string.
    ctx->cnv = ucnv_openCCSID(1214, UCNV_IBM, &status);
    if (!ctx->cnv)
        goto error;

    memcpy(ctx->key, key, 16);
    ctx->ref_count = 3;

    sqlite_err =
        sqlite3_create_function_v2(db, "mmenc", 1, SQLITE_ANY, ctx, mmenc_func,
                                   NULL, NULL, mm_func_destroy);
    if (sqlite_err != SQLITE_OK)
        goto error;

    sqlite_err =
        sqlite3_create_function_v2(db, "mmdec", 1, SQLITE_ANY, ctx, mmdec_func,
                                   NULL, NULL, mm_func_destroy);
    if (sqlite_err != SQLITE_OK)
        goto error;

    sqlite_err = sqlite3_create_function_v2(db, "mm_cipher_key", 1, SQLITE_ANY,
                                            ctx, mm_cipher_key_func, NULL, NULL,
                                            mm_func_destroy);
    if (sqlite_err != SQLITE_OK)
        goto error;

    return SQLITE_OK;

error:
    if (ctx)
        sqlite3_free(ctx);
    return sqlite_err;
}