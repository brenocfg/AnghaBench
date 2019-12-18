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
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_5__ {int lbStyle; int lbColor; } ;
typedef  TYPE_1__ LOGBRUSH ;
typedef  scalar_t__ HBRUSH ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 scalar_t__ CreateSolidBrush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (scalar_t__) ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FillMemory (TYPE_1__*,int,int) ; 
 scalar_t__ GDI_OBJECT_TYPE_BRUSH ; 
 scalar_t__ GetLastError () ; 
 int GetObject (scalar_t__,int,TYPE_1__*) ; 
 int GetObjectA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ GetObjectW (int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 int /*<<< orphan*/  RGB (int,int,int) ; 
 int /*<<< orphan*/  SetLastError (scalar_t__) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

void
Test_Brush(void)
{
    LOGBRUSH logbrush;
    HBRUSH hBrush;

    FillMemory(&logbrush, sizeof(LOGBRUSH), 0x77);
    hBrush = CreateSolidBrush(RGB(1,2,3));
    ok(hBrush != 0, "CreateSolidBrush failed, skipping tests.\n");
    if (!hBrush) return;

    SetLastError(ERROR_SUCCESS);
    ok(GetObjectA((HANDLE)GDI_OBJECT_TYPE_BRUSH, 0, NULL) == sizeof(LOGBRUSH), "\n");
    ok(GetObjectW((HANDLE)GDI_OBJECT_TYPE_BRUSH, 0, NULL) == sizeof(LOGBRUSH), "\n");
    ok(GetObject(hBrush, sizeof(WORD), NULL) == sizeof(LOGBRUSH), "\n");
    ok(GetObject(hBrush, 0, NULL) == sizeof(LOGBRUSH), "\n");
    ok(GetObject(hBrush, 5, NULL) == sizeof(LOGBRUSH), "\n");
    ok(GetObject(hBrush, -5, NULL) == sizeof(LOGBRUSH), "\n");

    //ok(GetObject(hBrush, 0, &logbrush) == 0, "\n"); fails on win7
    ok(logbrush.lbStyle == 0x77777777, "\n");
    ok(GetObject(hBrush, 5, &logbrush) == sizeof(LOGBRUSH), "\n");
    ok(logbrush.lbStyle == 0, "\n");
    ok(logbrush.lbColor == 0x77777701, "\n");

    ok(GetObject(hBrush, sizeof(LOGBRUSH), &logbrush) == sizeof(LOGBRUSH), "\n");
    ok(GetObject(hBrush, sizeof(LOGBRUSH) - 1, &logbrush) == sizeof(LOGBRUSH), "\n");
    ok(GetObject(hBrush, 1, &logbrush) == sizeof(LOGBRUSH), "\n");
    ok(GetObject(hBrush, sizeof(LOGBRUSH)+2, &logbrush) == sizeof(LOGBRUSH), "\n");
    ok(GetObject(hBrush, -1, &logbrush) == sizeof(LOGBRUSH), "\n");
    // TODO: test all members

    ok(GetLastError() == ERROR_SUCCESS, "\n");
    DeleteObject(hBrush);

    ok(GetObjectW((HANDLE)GDI_OBJECT_TYPE_BRUSH, sizeof(LOGBRUSH), &logbrush) == 0, "\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER, "expected ERROR_INVALID_PARAMETER, got %ld\n", GetLastError());
}