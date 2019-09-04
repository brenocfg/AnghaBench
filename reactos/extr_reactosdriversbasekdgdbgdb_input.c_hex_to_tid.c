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
typedef  int ULONG_PTR ;
typedef  int UINT_PTR ;

/* Variables and functions */
 char hex_value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
UINT_PTR
hex_to_tid(char* buffer)
{
    ULONG_PTR ret = 0;
    char hex;
    while (*buffer)
    {
        hex = hex_value(*buffer++);
        if (hex < 0)
            return ret;
        ret <<= 4;
        ret += hex;
    }
    return ret;
}