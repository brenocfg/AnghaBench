#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  ed; } ;
typedef  TYPE_1__ Mode ;
typedef  int /*<<< orphan*/  DmenuScriptEntry ;

/* Variables and functions */
 int /*<<< orphan*/ * get_script_output (TYPE_1__*,int /*<<< orphan*/ ,char*,unsigned int*) ; 

__attribute__((used)) static DmenuScriptEntry *execute_executor ( Mode *sw, char *result, unsigned int *length )
{
    DmenuScriptEntry *retv = get_script_output ( sw, sw->ed, result, length );
    return retv;
}