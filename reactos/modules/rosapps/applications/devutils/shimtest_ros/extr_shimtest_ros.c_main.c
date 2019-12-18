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
 int /*<<< orphan*/  test_normal_imports () ; 
 int /*<<< orphan*/  test_ordinal_imports () ; 
 int /*<<< orphan*/  xprintf (char*) ; 

int main(int argc, char* argv[])
{
    xprintf("Normal import (kernel32!GetComputerNameA)\n");
    test_normal_imports();
    xprintf("\nOrdinal import (shlwapi!#23)\n");
    test_ordinal_imports();

    return 0;
}