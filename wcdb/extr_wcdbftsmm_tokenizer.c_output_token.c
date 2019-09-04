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
struct TYPE_3__ {char* out_buffer; int out_length; int* in_offset; int /*<<< orphan*/  token_count; int /*<<< orphan*/ * in_buffer; } ;
typedef  TYPE_1__ mm_cursor_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  buf2 ;
typedef  int /*<<< orphan*/  buf1 ;
typedef  int /*<<< orphan*/  UErrorCode ;
typedef  int /*<<< orphan*/  UChar ;

/* Variables and functions */
 int MINIMAL_OUT_BUFFER_LENGTH ; 
 int SQLITE_ERROR ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  UNORM_NFKD ; 
 scalar_t__ U_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  U_FOLD_CASE_DEFAULT ; 
 int /*<<< orphan*/  U_ZERO_ERROR ; 
 int /*<<< orphan*/  free (char*) ; 
 char* generate_token_printable_code (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sqlite3_malloc (int) ; 
 int /*<<< orphan*/  sqlite3_mm_set_last_error (char*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ sqlite3_realloc (char*,int) ; 
 int u_strFoldCase (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u_strToUTF8 (char*,int,int*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int unorm_normalize (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int output_token(mm_cursor_t *cur,
                        int32_t start,
                        int32_t end,
                        const char **ppToken,
                        int *pnBytes,
                        int *piStartOffset,
                        int *piEndOffset,
                        int *piPosition)
{
    UChar buf1[256];
    UChar buf2[256];
    UErrorCode status = U_ZERO_ERROR;
    int32_t result;
    int32_t length;

    length = end - start;
    if (length > 256)
        length = 256;
    result = unorm_normalize(cur->in_buffer + start, length, UNORM_NFKD, 0,
                             buf1, sizeof(buf1) / sizeof(UChar), &status);
    // currently, only try fixed length buffer, failed if overflowed.
    if (U_FAILURE(status) || result > sizeof(buf1) / sizeof(UChar)) {
        char *seq =
            generate_token_printable_code(cur->in_buffer + start, length);
        sqlite3_mm_set_last_error(
            "Normalize token failed. ICU status: %d, input: %s", status, seq);
        free(seq);
        return SQLITE_ERROR;
    }

    length = result;
    result = u_strFoldCase(buf2, sizeof(buf2) / sizeof(UChar), buf1, length,
                           U_FOLD_CASE_DEFAULT, &status);
    // currently, only try fixed length buffer, failed if overflowed.
    if (U_FAILURE(status) || result > sizeof(buf2) / sizeof(UChar)) {
        char *seq = generate_token_printable_code(buf1, length);
        sqlite3_mm_set_last_error(
            "FoldCase token failed. ICU status: %d, input: %s", status, seq);
        free(seq);
        return SQLITE_ERROR;
    }

    if (cur->out_buffer == NULL) {
        cur->out_buffer =
            (char *) sqlite3_malloc(MINIMAL_OUT_BUFFER_LENGTH * sizeof(char));
        if (!cur->out_buffer)
            return SQLITE_NOMEM;
        cur->out_length = MINIMAL_OUT_BUFFER_LENGTH;
    }

    length = result;
    u_strToUTF8(cur->out_buffer, cur->out_length, &result, buf2, length,
                &status);
    if (result > cur->out_length) {
        char *b =
            (char *) sqlite3_realloc(cur->out_buffer, result * sizeof(char));
        if (!b)
            return SQLITE_NOMEM;

        cur->out_buffer = b;
        cur->out_length = result;

        status = U_ZERO_ERROR;
        u_strToUTF8(cur->out_buffer, cur->out_length, &result, buf2, length,
                    &status);
    }
    if (U_FAILURE(status) || result > cur->out_length) {
        char *seq = generate_token_printable_code(buf2, length);
        sqlite3_mm_set_last_error(
            "Transform token to UTF-8 failed. ICU status: %d, input: %s",
            status, seq);
        free(seq);
        return SQLITE_ERROR;
    }

    *ppToken = cur->out_buffer;
    *pnBytes = result;
    *piStartOffset = cur->in_offset[start];
    *piEndOffset = cur->in_offset[end];
    *piPosition = cur->token_count++;

    return SQLITE_OK;
}