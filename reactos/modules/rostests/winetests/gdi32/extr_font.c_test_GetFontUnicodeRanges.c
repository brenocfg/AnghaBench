#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lf ;
struct TYPE_11__ {size_t cRanges; TYPE_1__* ranges; } ;
struct TYPE_10__ {int /*<<< orphan*/  lfFaceName; } ;
struct TYPE_9__ {int /*<<< orphan*/  cGlyphs; int /*<<< orphan*/  wcLow; } ;
typedef  TYPE_2__ LOGFONTA ;
typedef  int /*<<< orphan*/  HFONT ;
typedef  int /*<<< orphan*/ * HDC ;
typedef  TYPE_3__ GLYPHSET ;
typedef  size_t DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_3__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_font (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  lstrcpyA (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (size_t,char*) ; 
 size_t pGetFontUnicodeRanges (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  trace (char*,size_t,...) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_GetFontUnicodeRanges(void)
{
    LOGFONTA lf;
    HDC hdc;
    HFONT hfont, hfont_old;
    DWORD size;
    GLYPHSET *gs;
    DWORD i;

    if (!pGetFontUnicodeRanges)
    {
        win_skip("GetFontUnicodeRanges not available before W2K\n");
        return;
    }

    memset(&lf, 0, sizeof(lf));
    lstrcpyA(lf.lfFaceName, "Arial");
    hfont = create_font("Arial", &lf);

    hdc = GetDC(0);
    hfont_old = SelectObject(hdc, hfont);

    size = pGetFontUnicodeRanges(NULL, NULL);
    ok(!size, "GetFontUnicodeRanges succeeded unexpectedly\n");

    size = pGetFontUnicodeRanges(hdc, NULL);
    ok(size, "GetFontUnicodeRanges failed unexpectedly\n");

    gs = HeapAlloc(GetProcessHeap(), 0, size);

    size = pGetFontUnicodeRanges(hdc, gs);
    ok(size, "GetFontUnicodeRanges failed\n");

    if (0) /* Disabled to limit console spam */
        for (i = 0; i < gs->cRanges; i++)
            trace("%03d wcLow %04x cGlyphs %u\n", i, gs->ranges[i].wcLow, gs->ranges[i].cGlyphs);
    trace("found %u ranges\n", gs->cRanges);

    HeapFree(GetProcessHeap(), 0, gs);

    SelectObject(hdc, hfont_old);
    DeleteObject(hfont);
    ReleaseDC(NULL, hdc);
}