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
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_8__ {int lfHeight; int /*<<< orphan*/  lfFaceName; int /*<<< orphan*/  lfQuality; int /*<<< orphan*/  lfWeight; int /*<<< orphan*/  lfClipPrecision; int /*<<< orphan*/  lfCharSet; } ;
struct TYPE_7__ {int cx; int cy; } ;
typedef  TYPE_1__ SIZE ;
typedef  int /*<<< orphan*/  RECT ;
typedef  int /*<<< orphan*/  POINT ;
typedef  TYPE_2__ LOGFONTA ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HFONT ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  ANSI_CHARSET ; 
 int /*<<< orphan*/  CLIP_DEFAULT_PRECIS ; 
 int /*<<< orphan*/  CreateWindowExA (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DEFAULT_QUALITY ; 
 int /*<<< orphan*/  DPtoLP (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_DONTCARE ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetTextExtentPoint32A (int /*<<< orphan*/ ,char*,int,TYPE_1__*) ; 
 int /*<<< orphan*/  MM_ANISOTROPIC ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetMapMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetTextCharacterExtra (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SetTextJustification (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SetViewportExtEx (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetWindowExtEx (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WS_POPUP ; 
 int /*<<< orphan*/  create_font (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  is_font_installed (char*) ; 
 int /*<<< orphan*/  lstrcpyA (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,int,int,...) ; 
 int /*<<< orphan*/  pGetGlyphIndicesA (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pGetTextExtentExPointI (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  testJustification (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_SetTextJustification(void)
{
    HDC hdc;
    RECT clientArea;
    LOGFONTA lf;
    HFONT hfont;
    HWND hwnd;
    SIZE size, expect;
    int i;
    WORD indices[2];
    static const char testText[] =
            "Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do "
            "eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut "
            "enim ad minim veniam, quis nostrud exercitation ullamco laboris "
            "nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in "
            "reprehenderit in voluptate velit esse cillum dolore eu fugiat "
            "nulla pariatur. Excepteur sint occaecat cupidatat non proident, "
            "sunt in culpa qui officia deserunt mollit anim id est laborum.";

    hwnd = CreateWindowExA(0, "static", "", WS_POPUP, 0,0, 400,400, 0, 0, 0, NULL);
    GetClientRect( hwnd, &clientArea );
    hdc = GetDC( hwnd );

    if (!is_font_installed("Times New Roman"))
    {
        skip("Times New Roman is not installed\n");
        return;
    }

    memset(&lf, 0, sizeof lf);
    lf.lfCharSet = ANSI_CHARSET;
    lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
    lf.lfWeight = FW_DONTCARE;
    lf.lfHeight = 20;
    lf.lfQuality = DEFAULT_QUALITY;
    lstrcpyA(lf.lfFaceName, "Times New Roman");
    hfont = create_font("Times New Roman", &lf);
    SelectObject(hdc, hfont);

    testJustification(hdc, testText, &clientArea);

    if (!pGetGlyphIndicesA || !pGetTextExtentExPointI) goto done;
    pGetGlyphIndicesA( hdc, "A ", 2, indices, 0 );

    SetTextJustification(hdc, 0, 0);
    GetTextExtentPoint32A(hdc, " ", 1, &expect);
    GetTextExtentPoint32A(hdc, "   ", 3, &size);
    ok( size.cx == 3 * expect.cx, "wrong size %d/%d\n", size.cx, expect.cx );
    SetTextJustification(hdc, 4, 1);
    GetTextExtentPoint32A(hdc, " ", 1, &size);
    ok( size.cx == expect.cx + 4, "wrong size %d/%d\n", size.cx, expect.cx );
    SetTextJustification(hdc, 9, 2);
    GetTextExtentPoint32A(hdc, "  ", 2, &size);
    ok( size.cx == 2 * expect.cx + 9, "wrong size %d/%d\n", size.cx, expect.cx );
    SetTextJustification(hdc, 7, 3);
    GetTextExtentPoint32A(hdc, "   ", 3, &size);
    ok( size.cx == 3 * expect.cx + 7, "wrong size %d/%d\n", size.cx, expect.cx );
    SetTextJustification(hdc, 7, 3);
    SetTextCharacterExtra(hdc, 2 );
    GetTextExtentPoint32A(hdc, "   ", 3, &size);
    ok( size.cx == 3 * (expect.cx + 2) + 7, "wrong size %d/%d\n", size.cx, expect.cx );
    SetTextJustification(hdc, 0, 0);
    SetTextCharacterExtra(hdc, 0);
    size.cx = size.cy = 1234;
    GetTextExtentPoint32A(hdc, " ", 0, &size);
    ok( size.cx == 0 && size.cy == 0, "wrong size %d,%d\n", size.cx, size.cy );
    pGetTextExtentExPointI(hdc, indices, 2, -1, NULL, NULL, &expect);
    SetTextJustification(hdc, 5, 1);
    pGetTextExtentExPointI(hdc, indices, 2, -1, NULL, NULL, &size);
    ok( size.cx == expect.cx + 5, "wrong size %d/%d\n", size.cx, expect.cx );
    SetTextJustification(hdc, 0, 0);

    SetMapMode( hdc, MM_ANISOTROPIC );
    SetWindowExtEx( hdc, 2, 2, NULL );
    GetClientRect( hwnd, &clientArea );
    DPtoLP( hdc, (POINT *)&clientArea, 2 );
    testJustification(hdc, testText, &clientArea);

    GetTextExtentPoint32A(hdc, "A", 1, &expect);
    for (i = 0; i < 10; i++)
    {
        SetTextCharacterExtra(hdc, i);
        GetTextExtentPoint32A(hdc, "A", 1, &size);
        ok( size.cx == expect.cx + i, "wrong size %d/%d+%d\n", size.cx, expect.cx, i );
    }
    SetTextCharacterExtra(hdc, 0);
    pGetTextExtentExPointI(hdc, indices, 1, -1, NULL, NULL, &expect);
    for (i = 0; i < 10; i++)
    {
        SetTextCharacterExtra(hdc, i);
        pGetTextExtentExPointI(hdc, indices, 1, -1, NULL, NULL, &size);
        ok( size.cx == expect.cx + i, "wrong size %d/%d+%d\n", size.cx, expect.cx, i );
    }
    SetTextCharacterExtra(hdc, 0);

    SetViewportExtEx( hdc, 3, 3, NULL );
    GetClientRect( hwnd, &clientArea );
    DPtoLP( hdc, (POINT *)&clientArea, 2 );
    testJustification(hdc, testText, &clientArea);

    GetTextExtentPoint32A(hdc, "A", 1, &expect);
    for (i = 0; i < 10; i++)
    {
        SetTextCharacterExtra(hdc, i);
        GetTextExtentPoint32A(hdc, "A", 1, &size);
        ok( size.cx == expect.cx + i, "wrong size %d/%d+%d\n", size.cx, expect.cx, i );
    }

done:
    DeleteObject(hfont);
    ReleaseDC(hwnd, hdc);
    DestroyWindow(hwnd);
}