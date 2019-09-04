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
typedef  int /*<<< orphan*/  sqlite3_tokenizer_cursor ;
typedef  int /*<<< orphan*/  sqlite3_tokenizer ;
struct TYPE_5__ {int /*<<< orphan*/  locale; } ;
typedef  TYPE_1__ mm_tokenizer_t ;
struct TYPE_6__ {int* in_offset; int ideo_start; int ideo_end; int ideo_state; int in_length; int /*<<< orphan*/  iter; int /*<<< orphan*/ * in_buffer; scalar_t__ token_count; scalar_t__ out_length; int /*<<< orphan*/ * out_buffer; } ;
typedef  TYPE_2__ mm_cursor_t ;
typedef  int int32_t ;
typedef  char UErrorCode ;
typedef  char UChar32 ;
typedef  int /*<<< orphan*/  UChar ;

/* Variables and functions */
 int ROUND4 (int) ; 
 int SQLITE_ERROR ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  U16_APPEND (int /*<<< orphan*/ *,int,int,char,int) ; 
 int /*<<< orphan*/  U8_NEXT (char const*,int,int,char) ; 
 int /*<<< orphan*/  UBRK_WORD ; 
 scalar_t__ U_FAILURE (char) ; 
 char U_ZERO_ERROR ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_2__*) ; 
 scalar_t__ sqlite3_malloc (int) ; 
 int /*<<< orphan*/  sqlite3_mm_set_last_error (char*,char) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  ubrk_first (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubrk_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*) ; 

__attribute__((used)) static int mmtok_open(sqlite3_tokenizer *pTokenizer,
                      const char *zInput,
                      int nInput,
                      sqlite3_tokenizer_cursor **ppCursor)
{
    mm_tokenizer_t *tok = (mm_tokenizer_t *) pTokenizer;
    mm_cursor_t *cur;
    int i_input;
    int i_output;

    UErrorCode status = U_ZERO_ERROR;
    int32_t dst_len;
    UChar32 c;

    //__android_log_print(ANDROID_LOG_VERBOSE, "TOKENIZER", "Begin: %s", zInput);

    if (nInput < 0)
        nInput = strlen(zInput);

    dst_len = ROUND4(nInput + 1);
    cur = (mm_cursor_t *) sqlite3_malloc(
        sizeof(mm_cursor_t) + dst_len * sizeof(UChar) // in_buffer
        + (dst_len + 1) * sizeof(int)                 // in_offset
        );
    if (!cur)
        return SQLITE_NOMEM;

    memset(cur, 0, sizeof(mm_cursor_t));
    cur->in_buffer = (UChar *) &cur[1];
    cur->in_offset = (int *) &cur->in_buffer[dst_len];
    cur->out_buffer = NULL;
    cur->out_length = 0;
    cur->token_count = 0;
    cur->ideo_start = -1;
    cur->ideo_end = -1;
    cur->ideo_state = -1;

    i_input = 0;
    i_output = 0;
    cur->in_offset[i_output] = i_input;
    for (;;) {
        if (i_input >= nInput)
            break;

        U8_NEXT(zInput, i_input, nInput, c);
        if (!c)
            break;
        if (c < 0)
            c = ' ';

        int is_error = 0;
        U16_APPEND(cur->in_buffer, i_output, dst_len, c, is_error);
        if (is_error) {
            sqlite3_free(cur);
            sqlite3_mm_set_last_error(
                "Writing UTF-16 character failed. Code point: 0x%x", c);
            return SQLITE_ERROR;
        }
        cur->in_offset[i_output] = i_input;
    }

    cur->iter =
        ubrk_open(UBRK_WORD, tok->locale, cur->in_buffer, i_output, &status);
    if (U_FAILURE(status)) {
        sqlite3_mm_set_last_error(
            "Open UBreakIterator failed. ICU error code: %d", status);
        return SQLITE_ERROR;
    }
    cur->in_length = i_output;

    ubrk_first(cur->iter);
    *ppCursor = (sqlite3_tokenizer_cursor *) cur;
    return SQLITE_OK;
}