#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  hwndSelf; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  scalar_t__ INT ;
typedef  TYPE_1__ EDITSTATE ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  DefWindowProcW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ EDIT_CheckCombo (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ EDIT_EM_CanUndo (TYPE_1__*) ; 
 int /*<<< orphan*/  EDIT_EM_Undo (TYPE_1__*) ; 
 scalar_t__ VK_BACK ; 
 scalar_t__ VK_DOWN ; 
 scalar_t__ VK_UP ; 
 int /*<<< orphan*/  WM_SYSKEYDOWN ; 

__attribute__((used)) static LRESULT EDIT_WM_SysKeyDown(EDITSTATE *es, INT key, DWORD key_data)
{
	if ((key == VK_BACK) && (key_data & 0x2000)) {
		if (EDIT_EM_CanUndo(es))
			EDIT_EM_Undo(es);
		return 0;
	} else if (key == VK_UP || key == VK_DOWN) {
		if (EDIT_CheckCombo(es, WM_SYSKEYDOWN, key))
			return 0;
	}
	return DefWindowProcW(es->hwndSelf, WM_SYSKEYDOWN, key, key_data);
}