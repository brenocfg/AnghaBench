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
struct TYPE_3__ {char const* scheme; int scheme_len; } ;
typedef  TYPE_1__ parse_data ;
typedef  char WCHAR ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int ALLOW_NULL_TERM_SCHEME ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  is_alpha (char const) ; 
 int /*<<< orphan*/  is_num (char const) ; 

__attribute__((used)) static BOOL parse_scheme_name(const WCHAR **ptr, parse_data *data, DWORD extras) {
    const WCHAR *start = *ptr;

    data->scheme = NULL;
    data->scheme_len = 0;

    while(**ptr) {
        if(**ptr == '*' && *ptr == start) {
            /* Might have found a wildcard scheme. If it is the next
             * char has to be a ':' for it to be a valid URI
             */
            ++(*ptr);
            break;
        } else if(!is_num(**ptr) && !is_alpha(**ptr) && **ptr != '+' &&
           **ptr != '-' && **ptr != '.')
            break;

        (*ptr)++;
    }

    if(*ptr == start)
        return FALSE;

    /* Schemes must end with a ':' */
    if(**ptr != ':' && !((extras & ALLOW_NULL_TERM_SCHEME) && !**ptr)) {
        *ptr = start;
        return FALSE;
    }

    data->scheme = start;
    data->scheme_len = *ptr - start;

    ++(*ptr);
    return TRUE;
}