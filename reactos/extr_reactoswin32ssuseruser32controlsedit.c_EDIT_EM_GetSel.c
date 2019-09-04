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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_3__ {int /*<<< orphan*/  selection_end; int /*<<< orphan*/  selection_start; } ;
typedef  int /*<<< orphan*/ * PUINT ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_1__ EDITSTATE ;

/* Variables and functions */
 int /*<<< orphan*/  MAKELONG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ORDER_UINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static LRESULT EDIT_EM_GetSel(const EDITSTATE *es, PUINT start, PUINT end)
{
	UINT s = es->selection_start;
	UINT e = es->selection_end;

	ORDER_UINT(s, e);
	if (start)
		*start = s;
	if (end)
		*end = e;
	return MAKELONG(s, e);
}