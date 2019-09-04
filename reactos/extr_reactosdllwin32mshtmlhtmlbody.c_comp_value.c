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

/* Variables and functions */
 scalar_t__ isdigitW (int) ; 

__attribute__((used)) static int comp_value(const WCHAR *ptr, int dpc)
{
    int ret = 0;
    WCHAR ch;

    if(dpc > 2)
        dpc = 2;

    while(dpc--) {
        if(!*ptr)
            ret *= 16;
        else if(isdigitW(ch = *ptr++))
            ret = ret*16 + (ch-'0');
        else if('a' <= ch && ch <= 'f')
            ret = ret*16 + (ch-'a') + 10;
        else if('A' <= ch && ch <= 'F')
            ret = ret*16 + (ch-'A') + 10;
        else
            ret *= 16;
    }

    return ret;
}