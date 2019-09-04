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
typedef  int WCHAR ;
typedef  int ULONGLONG ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int UINT_MAX ; 
 scalar_t__ is_num (int const) ; 

__attribute__((used)) static BOOL check_implicit_ipv4(const WCHAR **ptr, UINT *val) {
    const WCHAR *start = *ptr;
    ULONGLONG ret = 0;
    *val = 0;

    while(is_num(**ptr)) {
        ret = ret*10 + (**ptr - '0');

        if(ret > UINT_MAX) {
            *ptr = start;
            return FALSE;
        }
        ++(*ptr);
    }

    if(*ptr == start)
        return FALSE;

    *val = ret;
    return TRUE;
}