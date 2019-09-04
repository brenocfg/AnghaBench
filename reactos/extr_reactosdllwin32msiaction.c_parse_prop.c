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
typedef  enum parse_state { ____Placeholder_parse_state } parse_state ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
#define  state_quote 130 
#define  state_token 129 
#define  state_whitespace 128 

__attribute__((used)) static int parse_prop( const WCHAR *str, WCHAR *value, int *quotes )
{
    enum parse_state state = state_quote;
    const WCHAR *p;
    WCHAR *out = value;
    BOOL ignore, in_quotes = FALSE;
    int count = 0, len = 0;

    for (p = str; *p; p++)
    {
        ignore = FALSE;
        switch (state)
        {
        case state_whitespace:
            switch (*p)
            {
            case ' ':
                in_quotes = TRUE;
                ignore = TRUE;
                len++;
                break;
            case '"':
                state = state_quote;
                if (in_quotes && p[1] != '\"') count--;
                else count++;
                break;
            default:
                state = state_token;
                in_quotes = TRUE;
                len++;
                break;
            }
            break;

        case state_token:
            switch (*p)
            {
            case '"':
                state = state_quote;
                if (in_quotes) count--;
                else count++;
                break;
            case ' ':
                state = state_whitespace;
                if (!count) goto done;
                in_quotes = TRUE;
                len++;
                break;
            default:
                if (count) in_quotes = TRUE;
                len++;
                break;
            }
            break;

        case state_quote:
            switch (*p)
            {
            case '"':
                if (in_quotes && p[1] != '\"') count--;
                else count++;
                break;
            case ' ':
                state = state_whitespace;
                if (!count || (count > 1 && !len)) goto done;
                in_quotes = TRUE;
                len++;
                break;
            default:
                state = state_token;
                if (count) in_quotes = TRUE;
                len++;
                break;
            }
            break;

        default: break;
        }
        if (!ignore) *out++ = *p;
        if (!count) in_quotes = FALSE;
    }

done:
    if (!len) *value = 0;
    else *out = 0;

    *quotes = count;
    return p - str;
}