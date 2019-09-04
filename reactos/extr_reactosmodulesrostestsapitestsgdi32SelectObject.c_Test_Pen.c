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
typedef  scalar_t__ HPEN ;

/* Variables and functions */
 scalar_t__ GDI_HANDLE_GET_TYPE (scalar_t__) ; 
 scalar_t__ GDI_OBJECT_TYPE_BRUSH ; 
 int /*<<< orphan*/  GRAY_BRUSH ; 
 scalar_t__ GetStockObject (int /*<<< orphan*/ ) ; 
 scalar_t__ SelectObject (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  WHITE_BRUSH ; 
 int /*<<< orphan*/  hdc1 ; 
 int /*<<< orphan*/  ok (int,char*) ; 

__attribute__((used)) static void
Test_Pen()
{
    HPEN hpen, hpenOld;

	/* Test PEN */
	hpen = GetStockObject(GRAY_BRUSH);
	hpenOld = SelectObject(hdc1, hpen);
	ok(hpenOld == GetStockObject(WHITE_BRUSH), "Got wrong pen.\n");
//	RTEST(pDc_Attr->hbrush == hpen);
	ok(GDI_HANDLE_GET_TYPE(hpenOld) == GDI_OBJECT_TYPE_BRUSH, "wrong type.\n");
	SelectObject(hdc1, hpenOld);
}