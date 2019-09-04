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
struct define {int /*<<< orphan*/  name; scalar_t__ value; struct define* next; } ;

/* Variables and functions */
 struct define* cmdline_defines ; 
 int /*<<< orphan*/  pp_del_define (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void del_cmdline_defines(void)
{
    struct define *def;

    for (def = cmdline_defines; def; def = def->next)
    {
        if (def->value) pp_del_define( def->name );
    }
}