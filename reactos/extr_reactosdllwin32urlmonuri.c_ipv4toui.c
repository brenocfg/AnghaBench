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
typedef  int UINT ;
typedef  int DWORD ;

/* Variables and functions */

__attribute__((used)) static UINT ipv4toui(const WCHAR *ip, DWORD len) {
    UINT ret = 0;
    DWORD comp_value = 0;
    const WCHAR *ptr;

    for(ptr = ip; ptr < ip+len; ++ptr) {
        if(*ptr == '.') {
            ret <<= 8;
            ret += comp_value;
            comp_value = 0;
        } else
            comp_value = comp_value*10 + (*ptr-'0');
    }

    ret <<= 8;
    ret += comp_value;

    return ret;
}