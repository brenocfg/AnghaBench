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
typedef  int /*<<< orphan*/  HPEN ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int ARRAYSIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CreatePen (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LineTo (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MoveToEx (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RGB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float fScale ; 
 scalar_t__ fw ; 
 scalar_t__ mw ; 
 int /*<<< orphan*/ * section_vpos ; 

void OnPaint(HDC hdc)
{
	int i;
	HPEN hp = CreatePen(0, (fScale < 1.5f) ? 2 : 3, RGB(0, 0, 0));
	SelectObject(hdc, hp);
	for (i = 0; i < ARRAYSIZE(section_vpos); i++) {
		MoveToEx(hdc, mw + 10, section_vpos[i], NULL);
		LineTo(hdc, mw + fw, section_vpos[i]);
	}
}