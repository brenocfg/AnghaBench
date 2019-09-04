#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  src_buf ;
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;
struct TYPE_3__ {int /*<<< orphan*/  cnv; } ;
typedef  TYPE_1__ mm_cipher_context_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  scalar_t__ UErrorCode ;
typedef  char UChar ;

/* Variables and functions */
 int SQLITE_BLOB ; 
 int /*<<< orphan*/  SQLITE_ERROR ; 
 int /*<<< orphan*/  SQLITE_MISUSE ; 
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 scalar_t__ U_BUFFER_OVERFLOW_ERROR ; 
 scalar_t__ U_FAILURE (scalar_t__) ; 
 scalar_t__ U_STRING_NOT_TERMINATED_WARNING ; 
 scalar_t__ U_ZERO_ERROR ; 
 int /*<<< orphan*/  do_rc4 (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 scalar_t__ sqlite3_malloc (int) ; 
 int /*<<< orphan*/  sqlite3_mm_set_last_error (char*) ; 
 int /*<<< orphan*/  sqlite3_result_error_code (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_text16 (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_value (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_user_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_value_blob (int /*<<< orphan*/ *) ; 
 int sqlite3_value_bytes (int /*<<< orphan*/ *) ; 
 int sqlite3_value_type (int /*<<< orphan*/ *) ; 
 int ucnv_toUChars (int /*<<< orphan*/ ,char*,int,char*,int,scalar_t__*) ; 

__attribute__((used)) static void mmdec_func(sqlite3_context *db, int argc, sqlite3_value **argv)
{
    mm_cipher_context_t *ctx;
    char src_buf[1024];
    char *src = src_buf;
    int32_t src_len;
    UChar buf[512];
    UChar *dst = buf;
    int32_t dst_len;
    UErrorCode status = U_ZERO_ERROR;
    int arg_type;

    // only accept 1 argument.
    if (argc != 1)
        goto error_misuse;

    arg_type = sqlite3_value_type(argv[0]);

    // for data types other than BLOB, just return them.
    if (arg_type != SQLITE_BLOB) {
        sqlite3_result_value(db, argv[0]);
        return;
    }

    ctx = (mm_cipher_context_t *) sqlite3_user_data(db);
    src_len = sqlite3_value_bytes(argv[0]);
    if (src_len > sizeof(src_buf)) {
        src = (char *) sqlite3_malloc(src_len);
        if (!src)
            goto error_error;
    }
    memcpy(src, sqlite3_value_blob(argv[0]), src_len);

    // decrypt transformed BOCU-1 string.
    do_rc4(ctx, src, src_len);

    // transform input string from BOCU-1 encoding.
    // try stack buffer first, if it doesn't fit, malloc a new buffer.
    dst_len = ucnv_toUChars(ctx->cnv, dst, sizeof(buf), src, src_len, &status);
    if (status == U_BUFFER_OVERFLOW_ERROR) {
        status = U_ZERO_ERROR;
        dst = (UChar *) sqlite3_malloc(dst_len * sizeof(UChar));
        dst_len = ucnv_toUChars(ctx->cnv, dst, dst_len, src, src_len, &status);
    }
    if (U_FAILURE(status) && status != U_STRING_NOT_TERMINATED_WARNING) {
        sqlite3_mm_set_last_error(
            "Failed transforming text from internal encoding.");
        goto error_error;
    }

    // return
    sqlite3_result_text16(db, dst, dst_len * sizeof(UChar), SQLITE_TRANSIENT);
    if (src != src_buf)
        sqlite3_free(src);
    if (dst != buf)
        sqlite3_free(dst);
    return;

error_error:
    if (src != src_buf)
        sqlite3_free(src);
    if (dst != buf)
        sqlite3_free(dst);
    sqlite3_result_error_code(db, SQLITE_ERROR);
    return;

error_misuse:
    if (src != src_buf)
        sqlite3_free(src);
    if (dst != buf)
        sqlite3_free(dst);
    sqlite3_result_error_code(db, SQLITE_MISUSE);
    return;
}