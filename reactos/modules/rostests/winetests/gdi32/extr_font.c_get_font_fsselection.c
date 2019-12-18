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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_5__ {int otmSize; int /*<<< orphan*/  otmfsSelection; } ;
typedef  TYPE_1__ OUTLINETEXTMETRICA ;
typedef  int /*<<< orphan*/  LOGFONTA ;
typedef  int /*<<< orphan*/ * HFONT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateFontIndirectA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int GetOutlineTextMetricsA (int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static UINT get_font_fsselection(LOGFONTA *lf)
{
    OUTLINETEXTMETRICA *otm;
    HFONT hfont, hfont_old;
    DWORD ret, otm_size;
    UINT fsSelection;
    HDC hdc;

    hdc = GetDC(0);
    hfont = CreateFontIndirectA(lf);
    ok(hfont != NULL, "failed to create a font\n");

    hfont_old = SelectObject(hdc, hfont);

    otm_size = GetOutlineTextMetricsA(hdc, 0, NULL);
    otm = HeapAlloc(GetProcessHeap(), 0, otm_size);
    otm->otmSize = sizeof(*otm);
    ret = GetOutlineTextMetricsA(hdc, otm->otmSize, otm);
    ok(ret == otm->otmSize, "expected %u, got %u, error %d\n", otm->otmSize, ret, GetLastError());
    fsSelection = otm->otmfsSelection;
    HeapFree(GetProcessHeap(), 0, otm);
    SelectObject(hdc, hfont_old);
    DeleteObject(hfont);
    ReleaseDC(0, hdc);

    return fsSelection;
}