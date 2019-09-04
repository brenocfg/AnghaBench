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
typedef  int /*<<< orphan*/  ll ;
typedef  int ULONGLONG ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,unsigned long,...) ; 

__attribute__((used)) static inline const char* debugstr_longlong(ULONGLONG ll)
{
    static char string[17];
    if (sizeof(ll) > sizeof(unsigned long) && ll >> 32)
        sprintf(string, "%lx%08lx", (unsigned long)(ll >> 32), (unsigned long)ll);
    else
        sprintf(string, "%lx", (unsigned long)ll);
    return string;
}