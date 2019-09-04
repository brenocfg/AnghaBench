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
struct TYPE_3__ {scalar_t__ scheme_type; scalar_t__ has_implicit_scheme; } ;
typedef  TYPE_1__ parse_data ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ URL_SCHEME_FILE ; 
 scalar_t__ URL_SCHEME_MAILTO ; 
 scalar_t__ URL_SCHEME_WILDCARD ; 
 scalar_t__ check_hierarchical (char const**) ; 
 scalar_t__ is_hierarchical_scheme (scalar_t__) ; 

__attribute__((used)) static inline BOOL is_hierarchical_uri(const WCHAR **ptr, const parse_data *data) {
    const WCHAR *start = *ptr;

    if(data->scheme_type == URL_SCHEME_WILDCARD)
        return TRUE;
    else if(data->scheme_type == URL_SCHEME_FILE && data->has_implicit_scheme)
        return TRUE;
    else if(is_hierarchical_scheme(data->scheme_type) && (*ptr)[0] == '\\' && (*ptr)[1] == '\\') {
        *ptr += 2;
        return TRUE;
    } else if(data->scheme_type != URL_SCHEME_MAILTO && check_hierarchical(ptr))
        return TRUE;

    *ptr = start;
    return FALSE;
}