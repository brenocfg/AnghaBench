#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  symt; int /*<<< orphan*/  abbrev; } ;
typedef  TYPE_1__ dwarf2_debug_info_t ;

/* Variables and functions */
 char const* wine_dbg_sprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char* dwarf2_debug_di(const dwarf2_debug_info_t* di)
{
    return wine_dbg_sprintf("debug_info(abbrev:%p,symt:%p)",
                            di->abbrev, di->symt);
}