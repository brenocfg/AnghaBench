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

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,unsigned char const) ; 

__attribute__((used)) static
char*
dbg_print_physaddr(const unsigned char* addr, unsigned long addr_len)
{
    static char buffer[24];

    char* dest = buffer;
    *dest = '\0';

    while (addr_len--)
    {
        dest += sprintf(dest, "%02x", *addr);
        addr++;
        if (addr_len)
            *dest++ = ':';
    }

    return buffer;
}