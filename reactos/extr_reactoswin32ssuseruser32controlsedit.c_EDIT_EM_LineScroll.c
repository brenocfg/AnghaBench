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
struct TYPE_4__ {int style; int /*<<< orphan*/  char_width; } ;
typedef  int /*<<< orphan*/  INT ;
typedef  TYPE_1__ EDITSTATE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EDIT_EM_LineScroll_internal (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ES_MULTILINE ; 
 int /*<<< orphan*/  FALSE ; 

__attribute__((used)) static BOOL EDIT_EM_LineScroll(EDITSTATE *es, INT dx, INT dy)
{
	if (!(es->style & ES_MULTILINE))
		return FALSE;

	dx *= es->char_width;
	return EDIT_EM_LineScroll_internal(es, dx, dy);
}