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
 int /*<<< orphan*/  DUMP_STRING_TABLE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnitType ; 
 int /*<<< orphan*/  _UNIT_TYPE_MAX ; 
 int /*<<< orphan*/  arg_no_legend ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  unit_type ; 

__attribute__((used)) static void help_types(void) {
        if (!arg_no_legend)
                puts("Available unit types:");

        DUMP_STRING_TABLE(unit_type, UnitType, _UNIT_TYPE_MAX);
}