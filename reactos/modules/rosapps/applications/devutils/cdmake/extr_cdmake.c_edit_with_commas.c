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
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */

__attribute__((used)) static char *edit_with_commas(DWORD x, BOOL pad)
{
    static char s[14];
    unsigned i = 13;
    do
    {
        if (i % 4 == 2) s[--i] = ',';
        s[--i] = (char)(x % 10 + '0');
    } while ((x/=10) != 0);
    if (pad)
    {
        while (i > 0) s[--i] = ' ';
    }
    return s + i;
}