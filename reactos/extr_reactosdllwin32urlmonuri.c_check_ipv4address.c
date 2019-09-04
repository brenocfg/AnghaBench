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
typedef  char WCHAR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  check_dec_octet (char const**) ; 

__attribute__((used)) static BOOL check_ipv4address(const WCHAR **ptr, BOOL strict) {
    const WCHAR *start = *ptr;

    if(!check_dec_octet(ptr)) {
        *ptr = start;
        return FALSE;
    }

    if(**ptr != '.') {
        *ptr = start;
        return FALSE;
    }

    ++(*ptr);
    if(!check_dec_octet(ptr)) {
        *ptr = start;
        return FALSE;
    }

    if(**ptr != '.') {
        if(strict) {
            *ptr = start;
            return FALSE;
        } else
            return TRUE;
    }

    ++(*ptr);
    if(!check_dec_octet(ptr)) {
        *ptr = start;
        return FALSE;
    }

    if(**ptr != '.') {
        if(strict) {
            *ptr = start;
            return FALSE;
        } else
            return TRUE;
    }

    ++(*ptr);
    if(!check_dec_octet(ptr)) {
        *ptr = start;
        return FALSE;
    }

    /* Found a four digit ip address. */
    return TRUE;
}