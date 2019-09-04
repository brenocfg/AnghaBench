#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WORD ;
typedef  int UINT_PTR ;
struct TYPE_5__ {int palVersion; int palNumEntries; TYPE_1__* palPalEntry; } ;
struct TYPE_4__ {int /*<<< orphan*/  peFlags; scalar_t__ peBlue; scalar_t__ peGreen; scalar_t__ peRed; } ;
typedef  TYPE_2__ LOGPALETTE ;
typedef  scalar_t__ HPALETTE ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 scalar_t__ CreatePalette (TYPE_2__*) ; 
 int /*<<< orphan*/  DeleteObject (scalar_t__) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FillMemory (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ GDI_OBJECT_TYPE_PALETTE ; 
 scalar_t__ GetLastError () ; 
 int GetObject (scalar_t__,int,int /*<<< orphan*/ *) ; 
 int GetObjectA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int GetObjectW (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PC_EXPLICIT ; 
 int /*<<< orphan*/  SetLastError (scalar_t__) ; 
 int /*<<< orphan*/  ok (int,char*) ; 

void
Test_Palette(void)
{
    LOGPALETTE logpal;
    HPALETTE hPalette;
    WORD wPalette;

    FillMemory(&wPalette, sizeof(WORD), 0x77);
    logpal.palVersion = 0x0300;
    logpal.palNumEntries = 1;
    logpal.palPalEntry[0].peRed = 0;
    logpal.palPalEntry[0].peGreen = 0;
    logpal.palPalEntry[0].peBlue = 0;
    logpal.palPalEntry[0].peFlags = PC_EXPLICIT;
    hPalette = CreatePalette(&logpal);
    ok(hPalette != 0, "CreatePalette failed, skipping tests.\n");
    if (!hPalette) return;

    ok(GetObjectA((HANDLE)((UINT_PTR)hPalette & 0x0000ffff), 0, NULL) == sizeof(WORD), "\n");
    ok(GetObjectW((HANDLE)((UINT_PTR)hPalette & 0x0000ffff), 0, NULL) == sizeof(WORD), "\n");

    SetLastError(ERROR_SUCCESS);
    ok(GetObjectA((HANDLE)GDI_OBJECT_TYPE_PALETTE, 0, NULL) == sizeof(WORD), "\n");
    ok(GetObjectW((HANDLE)GDI_OBJECT_TYPE_PALETTE, 0, NULL) == sizeof(WORD), "\n");
    ok(GetObject(hPalette, sizeof(WORD), NULL) == sizeof(WORD), "\n");
    ok(GetObject(hPalette, 0, NULL) == sizeof(WORD), "\n");
    ok(GetObject(hPalette, 5, NULL) == sizeof(WORD), "\n");
    ok(GetObject(hPalette, -5, NULL) == sizeof(WORD), "\n");
    ok(GetObject(hPalette, sizeof(WORD), &wPalette) == sizeof(WORD), "\n");
    ok(GetObject(hPalette, sizeof(WORD)+2, &wPalette) == sizeof(WORD), "\n");
    ok(GetObject(hPalette, 0, &wPalette) == 0, "\n");
    ok(GetObject(hPalette, 1, &wPalette) == 0, "\n");
    ok(GetObject(hPalette, -1, &wPalette) == sizeof(WORD), "\n");
    ok(GetLastError() == ERROR_SUCCESS, "\n");
    DeleteObject(hPalette);
    ok(GetObjectW((HANDLE)GDI_OBJECT_TYPE_PALETTE, sizeof(WORD), &wPalette) == 0, "\n");
    ok(GetLastError() == ERROR_SUCCESS, "\n");

}