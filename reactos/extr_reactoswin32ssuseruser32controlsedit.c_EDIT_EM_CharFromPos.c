#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  hwndSelf; } ;
struct TYPE_7__ {void* y; void* x; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  TYPE_1__ POINT ;
typedef  int LRESULT ;
typedef  void* INT ;
typedef  TYPE_2__ EDITSTATE ;

/* Variables and functions */
 void* EDIT_CharFromPos (TYPE_2__*,void*,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EDIT_EM_LineFromChar (TYPE_2__*,void*) ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int MAKELONG (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PtInRect (int /*<<< orphan*/ *,TYPE_1__) ; 

__attribute__((used)) static LRESULT EDIT_EM_CharFromPos(EDITSTATE *es, INT x, INT y)
{
	POINT pt;
	RECT rc;
	INT index;

	pt.x = x;
	pt.y = y;
	GetClientRect(es->hwndSelf, &rc);
	if (!PtInRect(&rc, pt))
		return -1;

	index = EDIT_CharFromPos(es, x, y, NULL);
	return MAKELONG(index, EDIT_EM_LineFromChar(es, index));
}