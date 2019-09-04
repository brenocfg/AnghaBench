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
struct parser {char const* start; char* token; int token_len; } ;
typedef  char WCHAR ;

/* Variables and functions */
 int MAX_FIELD_LEN ; 

__attribute__((used)) static int push_token( struct parser *parser, const WCHAR *pos )
{
    int len = pos - parser->start;
    const WCHAR *src = parser->start;
    WCHAR *dst = parser->token + parser->token_len;

    if (len > MAX_FIELD_LEN - parser->token_len) len = MAX_FIELD_LEN - parser->token_len;

    parser->token_len += len;
    for ( ; len > 0; len--, dst++, src++) *dst = *src ? *src : ' ';
    *dst = 0;
    parser->start = pos;
    return 0;
}