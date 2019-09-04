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
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  EDITSTATE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EDIT_EM_PosFromChar (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ HIWORD (int /*<<< orphan*/ ) ; 
 scalar_t__ LOWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetCaretPos (short,short) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,short,short) ; 

__attribute__((used)) static void EDIT_SetCaretPos(EDITSTATE *es, INT pos,
			     BOOL after_wrap)
{
	LRESULT res = EDIT_EM_PosFromChar(es, pos, after_wrap);
	TRACE("%d - %dx%d\n", pos, (short)LOWORD(res), (short)HIWORD(res));
	SetCaretPos((short)LOWORD(res), (short)HIWORD(res));
}