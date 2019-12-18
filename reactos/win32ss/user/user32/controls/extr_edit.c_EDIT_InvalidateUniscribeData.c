#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * ssa; TYPE_1__* first_line_def; } ;
struct TYPE_5__ {struct TYPE_5__* next; } ;
typedef  TYPE_1__ LINEDEF ;
typedef  TYPE_2__ EDITSTATE ;

/* Variables and functions */
 int /*<<< orphan*/  EDIT_InvalidateUniscribeData_linedef (TYPE_1__*) ; 
 int /*<<< orphan*/  ScriptStringFree (int /*<<< orphan*/ **) ; 

__attribute__((used)) static inline void EDIT_InvalidateUniscribeData(EDITSTATE *es)
{
	LINEDEF *line_def = es->first_line_def;
	while (line_def)
	{
		EDIT_InvalidateUniscribeData_linedef(line_def);
		line_def = line_def->next;
	}
	if (es->ssa)
	{
		ScriptStringFree(&es->ssa);
		es->ssa = NULL;
	}
}