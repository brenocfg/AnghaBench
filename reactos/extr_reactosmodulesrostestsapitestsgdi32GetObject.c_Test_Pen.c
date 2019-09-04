#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ lopnStyle; } ;
typedef  TYPE_1__ LOGPEN ;
typedef  scalar_t__ HPEN ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  BITMAP ;

/* Variables and functions */
 scalar_t__ CreatePen (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (scalar_t__) ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  FillMemory (TYPE_1__*,int,int) ; 
 scalar_t__ GDI_OBJECT_TYPE_PEN ; 
 scalar_t__ GetLastError () ; 
 int GetObject (scalar_t__,int,TYPE_1__*) ; 
 int GetObjectA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ GetObjectW (int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 scalar_t__ PS_SOLID ; 
 int /*<<< orphan*/  RGB (int,int,int) ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

void
Test_Pen(void)
{
    LOGPEN logpen;
    HPEN hPen;

    FillMemory(&logpen, sizeof(LOGPEN), 0x77);
    hPen = CreatePen(PS_SOLID, 3, RGB(4,5,6));
    ok(hPen != 0, "CreatePen failed, skipping tests.\n");
    if (!hPen) return;
    SetLastError(ERROR_SUCCESS);
    ok(GetObjectA((HANDLE)GDI_OBJECT_TYPE_PEN, 0, NULL) == sizeof(LOGPEN), "\n");
    ok(GetObjectW((HANDLE)GDI_OBJECT_TYPE_PEN, 0, NULL) == sizeof(LOGPEN), "\n");
    ok(GetObject(hPen, sizeof(BITMAP), NULL) == sizeof(LOGPEN), "\n");
    ok(GetObject(hPen, 0, NULL) == sizeof(LOGPEN), "\n");
    ok(GetObject(hPen, 5, NULL) == sizeof(LOGPEN), "\n");
    ok(GetObject(hPen, -5, NULL) == sizeof(LOGPEN), "\n");
    ok(GetObject(hPen, sizeof(LOGPEN), &logpen) == sizeof(LOGPEN), "\n");
    ok(GetObject(hPen, sizeof(LOGPEN)-1, &logpen) == 0, "\n");
    ok(GetObject(hPen, sizeof(LOGPEN)+2, &logpen) == sizeof(LOGPEN), "\n");
    ok(GetObject(hPen, 0, &logpen) == 0, "\n");
    ok(GetObject(hPen, -5, &logpen) == sizeof(LOGPEN), "\n");
    //ok(GetLastError() == ERROR_SUCCESS, "\n"); fails on win7

    /* test if the fields are filled correctly */
    ok(logpen.lopnStyle == PS_SOLID, "\n");

    ok(GetObjectW((HANDLE)GDI_OBJECT_TYPE_PEN, sizeof(LOGPEN), &logpen) == 0, "\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER, "expected ERROR_INVALID_PARAMETER, got %ld\n", GetLastError());

    DeleteObject(hPen);
}