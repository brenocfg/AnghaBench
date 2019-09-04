#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lf ;
typedef  int /*<<< orphan*/  dtp ;
typedef  char WCHAR ;
struct TYPE_19__ {int lfHeight; int cbSize; int uiLengthDrawn; int iLeftMargin; int iRightMargin; int iTabLength; int /*<<< orphan*/  lfFaceName; int /*<<< orphan*/  lfQuality; int /*<<< orphan*/  lfWeight; int /*<<< orphan*/  lfClipPrecision; int /*<<< orphan*/  lfCharSet; } ;
struct TYPE_18__ {int member_2; scalar_t__ bottom; int right; int left; int top; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ RECT ;
typedef  TYPE_2__ LOGFONTA ;
typedef  int INT ;
typedef  scalar_t__ HWND ;
typedef  scalar_t__ HFONT ;
typedef  scalar_t__ HDC ;
typedef  TYPE_2__ DRAWTEXTPARAMS ;
typedef  char CHAR ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ANSI_CHARSET ; 
 int /*<<< orphan*/  CLIP_DEFAULT_PRECIS ; 
 scalar_t__ CreateFontIndirectA (TYPE_2__*) ; 
 scalar_t__ CreateWindowExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DEFAULT_QUALITY ; 
 int DT_CALCRECT ; 
 int DT_EDITCONTROL ; 
 int DT_EXPANDTABS ; 
 int DT_EXTERNALLEADING ; 
 int DT_LEFT ; 
 int DT_NOCLIP ; 
 int DT_NOPREFIX ; 
 int DT_SINGLELINE ; 
 int DT_TABSTOP ; 
 int DT_WORDBREAK ; 
 int DeleteObject (scalar_t__) ; 
 int DestroyWindow (scalar_t__) ; 
 int DrawTextA (scalar_t__,char*,int,TYPE_1__*,int) ; 
 int DrawTextExA (scalar_t__,char*,int,TYPE_1__*,int,TYPE_2__*) ; 
 int DrawTextExW (scalar_t__,char*,int,TYPE_1__*,int,TYPE_2__*) ; 
 int DrawTextW (scalar_t__,char*,int,TYPE_1__*,int) ; 
 int EMPTY (TYPE_1__) ; 
 int ERROR_CALL_NOT_IMPLEMENTED ; 
 int FALSE ; 
 int /*<<< orphan*/  FW_DONTCARE ; 
 scalar_t__ GetDC (scalar_t__) ; 
 int /*<<< orphan*/  GetDeviceCaps (scalar_t__,int /*<<< orphan*/ ) ; 
 int GetLastError () ; 
 int /*<<< orphan*/  IsRectEmpty (TYPE_1__*) ; 
 int /*<<< orphan*/  LOGPIXELSY ; 
 int /*<<< orphan*/  MM_HIENGLISH ; 
 int /*<<< orphan*/  MM_TEXT ; 
 scalar_t__ MODIFIED (TYPE_1__) ; 
 int MulDiv (int,int /*<<< orphan*/ ,int) ; 
 int ReleaseDC (scalar_t__,scalar_t__) ; 
 scalar_t__ SelectObject (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetMapMode (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetRect (TYPE_1__*,int,int,int,int) ; 
 int /*<<< orphan*/  SetRectEmpty (TYPE_1__*) ; 
 int TRUE ; 
 int /*<<< orphan*/  WS_POPUP ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  lstrcpyA (int /*<<< orphan*/ ,char*) ; 
 int lstrlenA (char*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  trace (char*,scalar_t__) ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 int wine_dbgstr_rect (TYPE_1__*) ; 

__attribute__((used)) static void test_DrawTextCalcRect(void)
{
    HWND hwnd;
    HDC hdc;
    HFONT hFont, hOldFont;
    LOGFONTA lf;
    static CHAR text[] = "Example text for testing DrawText in "
      "MM_HIENGLISH mode";
    static WCHAR textW[] = {'W','i','d','e',' ','c','h','a','r',' ',
        's','t','r','i','n','g','\0'};
    static CHAR emptystring[] = "";
    static WCHAR emptystringW[] = { 0 };
    static CHAR wordbreak_text[] = "line1 line2";
    static WCHAR wordbreak_textW[] = {'l','i','n','e','1',' ','l','i','n','e','2',0};
    static char tabstring[] = "one\ttwo";
    INT textlen, textheight, heightcheck;
    RECT rect = { 0, 0, 100, 0 }, rect2;
    BOOL ret;
    DRAWTEXTPARAMS dtp;
    BOOL conform_xp = TRUE;

    /* Initialization */
    hwnd = CreateWindowExA(0, "static", NULL, WS_POPUP,
                           0, 0, 200, 200, 0, 0, 0, NULL);
    ok(hwnd != 0, "CreateWindowExA error %u\n", GetLastError());
    hdc = GetDC(hwnd);
    ok(hdc != 0, "GetDC error %u\n", GetLastError());
    trace("hdc %p\n", hdc);
    textlen = lstrlenA(text);

    /* LOGFONT initialization */
    memset(&lf, 0, sizeof(lf));
    lf.lfCharSet = ANSI_CHARSET;
    lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
    lf.lfWeight = FW_DONTCARE;
    lf.lfHeight = 0; /* mapping mode dependent */
    lf.lfQuality = DEFAULT_QUALITY;
    lstrcpyA(lf.lfFaceName, "Arial");

    /* DrawText in MM_HIENGLISH with DT_CALCRECT */
    SetMapMode(hdc, MM_HIENGLISH);
    lf.lfHeight = 100 * 9 / 72; /* 9 point */
    hFont = CreateFontIndirectA(&lf);
    ok(hFont != 0, "CreateFontIndirectA error %u\n",
       GetLastError());
    hOldFont = SelectObject(hdc, hFont);

    textheight = DrawTextA(hdc, text, textlen, &rect, DT_CALCRECT |
       DT_EXTERNALLEADING | DT_WORDBREAK | DT_NOCLIP | DT_LEFT |
       DT_NOPREFIX);
    ok( textheight, "DrawTextA error %u\n", GetLastError());

    trace("MM_HIENGLISH rect.bottom %d\n", rect.bottom);
    ok(rect.bottom < 0, "In MM_HIENGLISH, DrawText with "
       "DT_CALCRECT should return a negative rectangle bottom. "
       "(bot=%d)\n", rect.bottom);

    SelectObject(hdc, hOldFont);
    ret = DeleteObject(hFont);
    ok( ret, "DeleteObject error %u\n", GetLastError());


    /* DrawText in MM_TEXT with DT_CALCRECT */
    SetMapMode(hdc, MM_TEXT);
    lf.lfHeight = -MulDiv(9, GetDeviceCaps(hdc,
       LOGPIXELSY), 72); /* 9 point */
    hFont = CreateFontIndirectA(&lf);
    ok(hFont != 0, "CreateFontIndirectA error %u\n",
       GetLastError());
    hOldFont = SelectObject(hdc, hFont);

    textheight = DrawTextA(hdc, text, textlen, &rect, DT_CALCRECT |
       DT_EXTERNALLEADING | DT_WORDBREAK | DT_NOCLIP | DT_LEFT |
       DT_NOPREFIX);
    ok( textheight, "DrawTextA error %u\n", GetLastError());

    trace("MM_TEXT rect.bottom %d\n", rect.bottom);
    ok(rect.bottom > 0, "In MM_TEXT, DrawText with DT_CALCRECT "
       "should return a positive rectangle bottom. (bot=%d)\n",
       rect.bottom);

    /* empty or null text should in some cases calc an empty rectangle */

    SetRect( &rect, 10,10, 100, 100);
    heightcheck = textheight = DrawTextExA(hdc, text, 0, &rect, DT_CALCRECT, NULL );
    ok(!IsRectEmpty(&rect) && !MODIFIED(rect),
        "rectangle should NOT be empty and NOT modified got %s\n", wine_dbgstr_rect(&rect));
    ok(textheight==0,"Got textheight from DrawTextExA\n");

    SetRect( &rect, 10,10, 100, 100);
    textheight = DrawTextA(hdc, text, 0, &rect, DT_CALCRECT);
    ok(!IsRectEmpty(&rect) && !MODIFIED(rect),
        "rectangle should NOT be empty and NOT modified got %s\n", wine_dbgstr_rect(&rect));
    if (conform_xp)
        ok(textheight==0,"Got textheight from DrawTextA\n");
    ok(textheight == heightcheck,"DrawTextEx and DrawText differ in return\n");

    SetRect( &rect, 10,10, 100, 100);
    SetLastError( 0);
    heightcheck = textheight = DrawTextExA(hdc, emptystring, -1, &rect, DT_CALCRECT, NULL );
    ok(EMPTY(rect), "rectangle should be empty got %s\n", wine_dbgstr_rect(&rect));
    ok(textheight!=0,"Failed to get textheight from DrawTextExA\n");

    SetRect( &rect, 10,10, 100, 100);
    textheight = DrawTextA(hdc, emptystring, -1, &rect, DT_CALCRECT);
    ok(EMPTY(rect), "rectangle should be empty got %s\n", wine_dbgstr_rect(&rect));
    ok(textheight!=0,"Failed to get textheight from DrawTextA\n");
    ok(textheight == heightcheck,"DrawTextEx and DrawText differ in return\n");

    SetRect( &rect, 10,10, 100, 100);
    SetLastError( 0);
    heightcheck = textheight = DrawTextExA(hdc, NULL, -1, &rect, DT_CALCRECT, NULL );
    ok(EMPTY(rect), "rectangle should be empty got %s\n", wine_dbgstr_rect(&rect));
    if (!textheight) /* Windows NT 4 */
    {
        if (conform_xp)
            win_skip("XP conformity failed, skipping XP tests. Probably winNT\n");
        conform_xp = FALSE;
    }
    else
        ok(textheight!=0,"Failed to get textheight from DrawTextExA\n");

    SetRect( &rect, 10,10, 100, 100);
    textheight = DrawTextA(hdc, NULL, -1, &rect, DT_CALCRECT);
    ok(EMPTY(rect), "rectangle should be empty got %s\n", wine_dbgstr_rect(&rect));
    if (conform_xp)
        ok(textheight!=0,"Failed to get textheight from DrawTextA\n");
    ok(textheight == heightcheck,"DrawTextEx and DrawText differ in return\n");

    SetRect( &rect, 10,10, 100, 100);
    heightcheck = textheight = DrawTextExA(hdc, NULL, 0, &rect, DT_CALCRECT, NULL );
    ok(!IsRectEmpty(&rect) && !MODIFIED(rect),
        "rectangle should NOT be empty and NOT modified got %s\n", wine_dbgstr_rect(&rect));
    if (conform_xp)
        ok(textheight==0,"Got textheight from DrawTextExA\n");

    SetRect( &rect, 10,10, 100, 100);
    textheight = DrawTextA(hdc, NULL, 0, &rect, DT_CALCRECT);
    ok(!IsRectEmpty(&rect) && !MODIFIED(rect),
        "rectangle should NOT be empty and NOT modified got %s\n", wine_dbgstr_rect(&rect));
    if (conform_xp)
        ok(textheight==0,"Got textheight from DrawTextA\n");
    ok(textheight == heightcheck,"DrawTextEx and DrawText differ in return\n");

    /* DT_SINGLELINE tests */

    SetRect( &rect, 10,10, 100, 100);
    heightcheck = textheight = DrawTextExA(hdc, text, 0, &rect, DT_CALCRECT|DT_SINGLELINE, NULL );
    ok(!IsRectEmpty(&rect) && !MODIFIED(rect),
        "rectangle should NOT be empty and NOT modified got %s\n", wine_dbgstr_rect(&rect));
    if (conform_xp)
        ok(textheight==0,"Got textheight from DrawTextExA\n");

    SetRect( &rect, 10,10, 100, 100);
    textheight = DrawTextA(hdc, text, 0, &rect, DT_CALCRECT|DT_SINGLELINE);
    ok(!IsRectEmpty(&rect) && !MODIFIED(rect),
        "rectangle should NOT be empty and NOT modified got %s\n", wine_dbgstr_rect(&rect));
    if (conform_xp)
        ok(textheight==0,"Got textheight from DrawTextA\n");
    ok(textheight == heightcheck,"DrawTextEx and DrawText differ in return\n");

    SetRect( &rect, 10,10, 100, 100);
    SetLastError( 0);
    heightcheck = textheight = DrawTextExA(hdc, emptystring, -1, &rect, DT_CALCRECT|DT_SINGLELINE, NULL );
    ok(!EMPTY(rect) && MODIFIED(rect), "rectangle should be modified got %s\n",
       wine_dbgstr_rect(&rect));
    ok(textheight!=0,"Failed to get textheight from DrawTextExA\n");

    SetRect( &rect, 10,10, 100, 100);
    textheight = DrawTextA(hdc, emptystring, -1, &rect, DT_CALCRECT|DT_SINGLELINE);
    ok(!EMPTY(rect) && MODIFIED (rect), "rectangle should be modified got %s\n",
       wine_dbgstr_rect(&rect));
    ok(textheight!=0,"Failed to get textheight from DrawTextA\n");
    ok(textheight == heightcheck,"DrawTextEx and DrawText differ in return\n");

    SetRect( &rect, 10,10, 100, 100);
    SetLastError( 0);
    heightcheck = textheight = DrawTextExA(hdc, NULL, -1, &rect, DT_CALCRECT|DT_SINGLELINE, NULL );
    ok(!EMPTY(rect) && MODIFIED(rect), "rectangle should be modified got %s\n",
       wine_dbgstr_rect(&rect));
    if (conform_xp)
        ok(textheight!=0,"Failed to get textheight from DrawTextExA\n");

    SetRect( &rect, 10,10, 100, 100);
    textheight = DrawTextA(hdc, NULL, -1, &rect, DT_CALCRECT|DT_SINGLELINE);
    ok(!EMPTY(rect) && MODIFIED(rect), "rectangle should be modified got %s\n",
       wine_dbgstr_rect(&rect));
    if (conform_xp)
        ok(textheight!=0,"Failed to get textheight from DrawTextA\n");
    ok(textheight == heightcheck,"DrawTextEx and DrawText differ in return\n");

    SetRect( &rect, 10,10, 100, 100);
    heightcheck = textheight = DrawTextExA(hdc, NULL, 0, &rect, DT_CALCRECT|DT_SINGLELINE, NULL );
    ok(!IsRectEmpty(&rect) && !MODIFIED(rect),
        "rectangle should NOT be empty and NOT modified got %s\n", wine_dbgstr_rect(&rect));
    if (conform_xp)
        ok(textheight==0,"Got textheight from DrawTextExA\n");

    SetRect( &rect, 10,10, 100, 100);
    textheight = DrawTextA(hdc, NULL, 0, &rect, DT_CALCRECT|DT_SINGLELINE);
    ok(!IsRectEmpty(&rect) && !MODIFIED(rect),
        "rectangle should NOT be empty and NOT modified got %s\n", wine_dbgstr_rect(&rect));
    if (conform_xp)
        ok(textheight==0,"Got textheight from DrawTextA\n");
    ok(textheight == heightcheck,"DrawTextEx and DrawText differ in return\n");

    /* further tests with  0 count, NULL and empty strings */
    heightcheck = textheight = DrawTextA(hdc, text, 0, &rect, 0);
    if (conform_xp)
        ok(textheight==0,"Got textheight from DrawTextA\n");
    textheight = DrawTextExA(hdc, text, 0, &rect, 0, NULL );
    if (conform_xp)
        ok(textheight==0,"Got textheight from DrawTextExA\n");
    ok(textheight == heightcheck,"DrawTextEx and DrawText differ in return\n");
    heightcheck = textheight = DrawTextA(hdc, emptystring, 0, &rect, 0);
    if (conform_xp)
        ok(textheight==0,"Got textheight from DrawTextA\n");
    textheight = DrawTextExA(hdc, emptystring, 0, &rect, 0, NULL );
    if (conform_xp)
        ok(textheight==0,"Got textheight from DrawTextExA\n");
    ok(textheight == heightcheck,"DrawTextEx and DrawText differ in return\n");
    heightcheck = textheight = DrawTextA(hdc, NULL, 0, &rect, 0);
    if (conform_xp)
        ok(textheight==0,"Got textheight from DrawTextA\n");
    textheight = DrawTextExA(hdc, NULL, 0, &rect, 0, NULL );
    if (conform_xp)
        ok(textheight==0,"Got textheight from DrawTextExA\n");
    ok(textheight == heightcheck,"DrawTextEx and DrawText differ in return\n");
    heightcheck = textheight = DrawTextA(hdc, emptystring, -1, &rect, 0);
    ok(textheight!=0,"Failed to get textheight from DrawTextA\n");
    textheight = DrawTextExA(hdc, emptystring, -1, &rect, 0, NULL );
    ok(textheight!=0,"Failed to get textheight from DrawTextExA\n");
    ok(textheight == heightcheck,"DrawTextEx and DrawText differ in return\n");
    heightcheck = textheight = DrawTextA(hdc, NULL, -1, &rect, 0);
    if (conform_xp)
        ok(textheight!=0,"Failed to get textheight from DrawTextA\n");
    textheight = DrawTextExA(hdc, NULL, -1, &rect, 0, NULL );
    if (conform_xp)
        ok(textheight!=0,"Failed to get textheight from DrawTextExA\n");
    ok(textheight == heightcheck,"DrawTextEx and DrawText differ in return\n");
    heightcheck = textheight = DrawTextA(hdc, NULL, 10, &rect, 0);
    ok(textheight==0,"Got textheight from DrawTextA\n");
    textheight = DrawTextExA(hdc, NULL, 10, &rect, 0, NULL );
    ok(textheight==0,"Got textheight from DrawTextA\n");
    ok(textheight == heightcheck,"DrawTextEx and DrawText differ in return\n");


    /* invalid dtp size test */
    dtp.cbSize = -1; /* Invalid */
    dtp.uiLengthDrawn = 1337;
    textheight = DrawTextExA(hdc, text, 0, &rect, 0, &dtp);
    ok(textheight==0,"Got textheight from DrawTextExA\n");
    ok(dtp.uiLengthDrawn==1337, "invalid dtp.uiLengthDrawn = %i\n",dtp.uiLengthDrawn);
    dtp.uiLengthDrawn = 1337;
    textheight = DrawTextExA(hdc, emptystring, 0, &rect, 0, &dtp);
    ok(textheight==0,"Got textheight from DrawTextExA\n");
    ok(dtp.uiLengthDrawn==1337, "invalid dtp.uiLengthDrawn = %i\n",dtp.uiLengthDrawn);
    dtp.uiLengthDrawn = 1337;
    textheight = DrawTextExA(hdc, NULL, 0, &rect, 0, &dtp);
    ok(textheight==0,"Got textheight from DrawTextExA\n");
    ok(dtp.uiLengthDrawn==1337, "invalid dtp.uiLengthDrawn = %i\n",dtp.uiLengthDrawn);
    dtp.uiLengthDrawn = 1337;
    textheight = DrawTextExA(hdc, emptystring, -1, &rect, 0, &dtp);
    ok(textheight==0,"Got textheight from DrawTextExA\n");
    ok(dtp.uiLengthDrawn==1337, "invalid dtp.uiLengthDrawn = %i\n",dtp.uiLengthDrawn);
    dtp.uiLengthDrawn = 1337;
    textheight = DrawTextExA(hdc, NULL, -1, &rect, 0, &dtp);
    ok(textheight==0,"Got textheight from DrawTextExA\n");
    ok(dtp.uiLengthDrawn==1337, "invalid dtp.uiLengthDrawn = %i\n",dtp.uiLengthDrawn);

    /* Margin calculations */
    dtp.cbSize = sizeof(dtp);
    dtp.iLeftMargin = 0;
    dtp.iRightMargin = 0;
    SetRectEmpty(&rect);
    DrawTextExA(hdc, text, -1, &rect, DT_CALCRECT, &dtp);
    textlen = rect.right; /* Width without margin */
    dtp.iLeftMargin = 8;
    SetRectEmpty(&rect);
    DrawTextExA(hdc, text, -1, &rect, DT_CALCRECT, &dtp);
    ok(rect.right==dtp.iLeftMargin+textlen  ,"Incorrect left margin calculated  rc(%d,%d)\n", rect.left, rect.right);
    dtp.iLeftMargin = 0;
    dtp.iRightMargin = 8;
    SetRectEmpty(&rect);
    DrawTextExA(hdc, text, -1, &rect, DT_CALCRECT, &dtp);
    ok(rect.right==dtp.iRightMargin+textlen  ,"Incorrect right margin calculated rc(%d,%d)\n", rect.left, rect.right);

    /* Wide char versions */
    SetRect( &rect, 10,10, 100, 100);
    SetLastError( 0);
    heightcheck = textheight = DrawTextExW(hdc, textW, 0, &rect, DT_CALCRECT, NULL );
    if( GetLastError() != ERROR_CALL_NOT_IMPLEMENTED) {
        ok(!IsRectEmpty(&rect) && !MODIFIED(rect),
            "rectangle should NOT be empty and NOT modified got %s\n", wine_dbgstr_rect(&rect));
        ok(textheight!=0,"Failed to get textheight from DrawTextExW\n");

        SetRect( &rect, 10,10, 100, 100);
        textheight = DrawTextW(hdc, textW, 0, &rect, DT_CALCRECT);
        ok(!IsRectEmpty(&rect) && !MODIFIED(rect),
            "rectangle should NOT be empty and NOT modified got %s\n", wine_dbgstr_rect(&rect));
        ok(textheight!=0,"Failed to get textheight from DrawTextW\n");
        ok(textheight == heightcheck,"DrawTextEx and DrawText differ in return\n");

        SetRect( &rect, 10,10, 100, 100);
        heightcheck = textheight = DrawTextExW(hdc, emptystringW, -1, &rect, DT_CALCRECT, NULL );
        ok(EMPTY(rect), "rectangle should be empty got %s\n", wine_dbgstr_rect(&rect));
        ok(textheight!=0,"Failed to get textheight from DrawTextExW\n");

        SetRect( &rect, 10,10, 100, 100);
        textheight = DrawTextW(hdc, emptystringW, -1, &rect, DT_CALCRECT);
        ok(EMPTY(rect), "rectangle should be empty got %s\n", wine_dbgstr_rect(&rect));
        ok(textheight!=0,"Failed to get textheight from DrawTextW\n");
        ok(textheight == heightcheck,"DrawTextEx and DrawText differ in return\n");

        SetRect( &rect, 10,10, 100, 100);
        heightcheck = textheight = DrawTextExW(hdc, NULL, 0, &rect, DT_CALCRECT, NULL );
        ok(!IsRectEmpty(&rect) && !MODIFIED(rect),
            "rectangle should NOT be empty and NOT modified got %s\n", wine_dbgstr_rect(&rect));
        if (textheight) /* windows 2000 */
        {
            if (conform_xp)
                win_skip("XP conformity failed, skipping XP tests. Probably win 2000\n");
            conform_xp = FALSE;
        }
        else
            ok(textheight==0,"Got textheight from DrawTextExW\n");

        SetRect( &rect, 10,10, 100, 100);
        textheight = DrawTextW(hdc, NULL, 0, &rect, DT_CALCRECT);
        ok(!IsRectEmpty(&rect) && !MODIFIED(rect),
            "rectangle should NOT be empty and NOT modified got %s\n", wine_dbgstr_rect(&rect));
        if (conform_xp)
            ok(textheight==0,"Got textheight from DrawTextW\n");
        ok(textheight == heightcheck,"DrawTextEx and DrawText differ in return\n");

        if (conform_xp) {
            /* Crashes on NT4 */
            SetRect( &rect, 10,10, 100, 100);
            heightcheck = textheight = DrawTextExW(hdc, NULL, -1, &rect, DT_CALCRECT, NULL );
            ok(!IsRectEmpty(&rect) && !MODIFIED(rect),
                "rectangle should NOT be empty and NOT modified got %s\n", wine_dbgstr_rect(&rect));
            ok(textheight==0,"Got textheight from DrawTextExW\n");

            SetRect( &rect, 10,10, 100, 100);
            textheight = DrawTextW(hdc, NULL, -1, &rect, DT_CALCRECT);
            ok(!IsRectEmpty(&rect) && !MODIFIED(rect),
                "rectangle should NOT be empty and NOT modified got %s\n", wine_dbgstr_rect(&rect));
            ok(textheight==0,"Got textheight from DrawTextW\n");
            ok(textheight == heightcheck,"DrawTextEx and DrawText differ in return\n");
        }


        /* DT_SINGLELINE tests */

        heightcheck = textheight = DrawTextExW(hdc, textW, 0, &rect, DT_CALCRECT|DT_SINGLELINE, NULL );
        ok(!IsRectEmpty(&rect) && !MODIFIED(rect),
            "rectangle should NOT be empty and NOT modified got %s\n", wine_dbgstr_rect(&rect));
        ok(textheight!=0,"Failed to get textheight from DrawTextExW\n");

        SetRect( &rect, 10,10, 100, 100);
        textheight = DrawTextW(hdc, textW, 0, &rect, DT_CALCRECT|DT_SINGLELINE);
        ok(!IsRectEmpty(&rect) && !MODIFIED(rect),
            "rectangle should NOT be empty and NOT modified got %s\n", wine_dbgstr_rect(&rect));
        ok(textheight!=0,"Failed to get textheight from DrawTextW\n");
        ok(textheight == heightcheck,"DrawTextEx and DrawText differ in return\n");

        SetRect( &rect, 10,10, 100, 100);
        heightcheck = textheight = DrawTextExW(hdc, emptystringW, -1, &rect, DT_CALCRECT|DT_SINGLELINE, NULL );
        ok(!EMPTY(rect) && MODIFIED(rect), "rectangle should be modified got %s\n",
           wine_dbgstr_rect(&rect));
        ok(textheight!=0,"Failed to get textheight from DrawTextExW\n");

        SetRect( &rect, 10,10, 100, 100);
        textheight = DrawTextW(hdc, emptystringW, -1, &rect, DT_CALCRECT|DT_SINGLELINE);
        ok(!EMPTY(rect) && MODIFIED(rect), "rectangle should be modified got %s\n",
           wine_dbgstr_rect(&rect));
        ok(textheight!=0,"Failed to get textheight from DrawTextW\n");
        ok(textheight == heightcheck,"DrawTextEx and DrawText differ in return\n");

        if (conform_xp) {
            /* Crashes on NT4 */
            SetRect( &rect, 10,10, 100, 100);
            heightcheck = textheight = DrawTextExW(hdc, NULL, -1, &rect, DT_CALCRECT|DT_SINGLELINE, NULL );
            ok(!IsRectEmpty(&rect) && !MODIFIED(rect),
                "rectangle should NOT be empty and NOT modified got %s\n", wine_dbgstr_rect(&rect));
            ok(textheight==0,"Got textheight from DrawTextExW\n");

            SetRect( &rect, 10,10, 100, 100);
            textheight = DrawTextW(hdc, NULL, -1, &rect, DT_CALCRECT|DT_SINGLELINE);
            ok(!IsRectEmpty(&rect) && !MODIFIED(rect),
                "rectangle should NOT be empty and NOT modified got %s\n", wine_dbgstr_rect(&rect));
            ok(textheight==0,"Got textheight from DrawTextW\n");
            ok(textheight == heightcheck,"DrawTextEx and DrawText differ in return\n");
        }

        SetRect( &rect, 10,10, 100, 100);
        heightcheck = textheight = DrawTextExW(hdc, NULL, 0, &rect, DT_CALCRECT|DT_SINGLELINE, NULL );
        ok(!IsRectEmpty(&rect) && !MODIFIED(rect),
            "rectangle should NOT be empty and NOT modified got %s\n", wine_dbgstr_rect(&rect));
        if (conform_xp)
            ok(textheight==0,"Got textheight from DrawTextExW\n");

        SetRect( &rect, 10,10, 100, 100);
        textheight = DrawTextW(hdc, NULL, 0, &rect, DT_CALCRECT|DT_SINGLELINE);
        ok(!IsRectEmpty(&rect) && !MODIFIED(rect),
            "rectangle should NOT be empty and NOT modified got %s\n", wine_dbgstr_rect(&rect));
        if (conform_xp)
            ok(textheight==0,"Got textheight from DrawTextW\n");
        ok(textheight == heightcheck,"DrawTextEx and DrawText differ in return\n");

        /* further tests with NULL and empty strings */
        heightcheck = textheight = DrawTextW(hdc, textW, 0, &rect, 0);
        ok(textheight!=0,"Failed to get textheight from DrawTextW\n");
        textheight = DrawTextExW(hdc, textW, 0, &rect, 0, NULL );
        ok(textheight!=0,"Failed to get textheight from DrawTextExW\n");
        ok(textheight == heightcheck,"DrawTextEx and DrawText differ in return\n");
        heightcheck = textheight = DrawTextW(hdc, emptystringW, 0, &rect, 0);
        ok(textheight!=0,"Failed to get textheight from DrawTextW\n");
        textheight = DrawTextExW(hdc, emptystringW, 0, &rect, 0, NULL );
        ok(textheight!=0,"Failed to get textheight from DrawTextExW\n");
        ok(textheight == heightcheck,"DrawTextEx and DrawText differ in return\n");
        heightcheck = textheight = DrawTextW(hdc, NULL, 0, &rect, 0);
        if (conform_xp)
            ok(textheight==0,"Got textheight from DrawTextW\n");
        textheight = DrawTextExW(hdc, NULL, 0, &rect, 0, NULL );
        if (conform_xp)
            ok(textheight==0,"Got textheight from DrawTextExW\n");
        ok(textheight == heightcheck,"DrawTextEx and DrawText differ in return\n");
        heightcheck = textheight = DrawTextW(hdc, emptystringW, -1, &rect, 0);
        ok(textheight!=0,"Failed to get textheight from DrawTextW\n");
        textheight = DrawTextExW(hdc, emptystringW, -1, &rect, 0, NULL );
        ok(textheight!=0,"Failed to get textheight from DrawTextExW\n");
        ok(textheight == heightcheck,"DrawTextEx and DrawText differ in return\n");
        if (conform_xp) {
            /* Crashes on NT4 */
            heightcheck = textheight = DrawTextW(hdc, NULL, -1, &rect, 0);
            ok(textheight==0,"Got textheight from DrawTextW\n");
            textheight = DrawTextExW(hdc, NULL, -1, &rect, 0, NULL );
            ok(textheight==0,"Got textheight from DrawTextExW\n");
            ok(textheight == heightcheck,"DrawTextEx and DrawText differ in return\n");
            heightcheck = textheight = DrawTextW(hdc, NULL, 10, &rect, 0);
            ok(textheight==0,"Got textheight from DrawTextW\n");
            textheight = DrawTextExW(hdc, NULL, 10, &rect, 0, NULL );
            ok(textheight==0,"Got textheight from DrawTextW\n");
            ok(textheight == heightcheck,"DrawTextEx and DrawText differ in return\n");
        }

        dtp.cbSize = -1; /* Invalid */
        dtp.uiLengthDrawn = 1337;
        textheight = DrawTextExW(hdc, textW, 0, &rect, 0, &dtp);
        ok(textheight!=0,"Failed to get textheight from DrawTextExW\n");
        ok(dtp.uiLengthDrawn==1337, "invalid dtp.uiLengthDrawn = %i\n",dtp.uiLengthDrawn);
        dtp.uiLengthDrawn = 1337;
        textheight = DrawTextExW(hdc, emptystringW, 0, &rect, 0, &dtp);
        if (conform_xp)
            ok(textheight==0,"Got textheight from DrawTextExW\n");
        ok(dtp.uiLengthDrawn==1337, "invalid dtp.uiLengthDrawn = %i\n",dtp.uiLengthDrawn);
        dtp.uiLengthDrawn = 1337;
        textheight = DrawTextExW(hdc, NULL, 0, &rect, 0, &dtp);
        if (conform_xp)
            ok(textheight==0,"Got textheight from DrawTextExW\n");
        ok(dtp.uiLengthDrawn==1337, "invalid dtp.uiLengthDrawn = %i\n",dtp.uiLengthDrawn);
        dtp.uiLengthDrawn = 1337;
        textheight = DrawTextExW(hdc, emptystringW, -1, &rect, 0, &dtp);
        ok(textheight==0,"Got textheight from DrawTextExW\n");
        ok(dtp.uiLengthDrawn==1337, "invalid dtp.uiLengthDrawn = %i\n",dtp.uiLengthDrawn);
        if (conform_xp) {
            /* Crashes on NT4 */
            dtp.uiLengthDrawn = 1337;
            textheight = DrawTextExW(hdc, NULL, -1, &rect, 0, &dtp);
            ok(textheight==0,"Got textheight from DrawTextExW\n");
            ok(dtp.uiLengthDrawn==1337, "invalid dtp.uiLengthDrawn = %i\n",dtp.uiLengthDrawn);
        }
    }

    /* More test cases from bug 12226 */
    SetRectEmpty(&rect);
    textheight = DrawTextA(hdc, emptystring, -1, &rect, DT_CALCRECT | DT_LEFT | DT_SINGLELINE);
    ok(textheight, "DrawTextA error %u\n", GetLastError());
    ok(0 == rect.left, "expected 0, got %d\n", rect.left);
    ok(0 == rect.right, "expected 0, got %d\n", rect.right);
    ok(0 == rect.top, "expected 0, got %d\n", rect.top);
    ok(rect.bottom, "rect.bottom should not be 0\n");

    SetRectEmpty(&rect);
    textheight = DrawTextW(hdc, emptystringW, -1, &rect, DT_CALCRECT | DT_LEFT | DT_SINGLELINE);
    if (!textheight && GetLastError() == ERROR_CALL_NOT_IMPLEMENTED)
    {
        win_skip( "DrawTextW not implemented\n" );
    }
    else
    {
        ok(textheight, "DrawTextW error %u\n", GetLastError());
        ok(0 == rect.left, "expected 0, got %d\n", rect.left);
        ok(0 == rect.right, "expected 0, got %d\n", rect.right);
        ok(0 == rect.top, "expected 0, got %d\n", rect.top);
        ok(rect.bottom, "rect.bottom should not be 0\n");
    }

    SetRect(&rect, 0, 0, 1, 1);
    heightcheck = DrawTextA(hdc, wordbreak_text, -1, &rect, DT_CALCRECT);
    SetRect(&rect, 0, 0, 1, 1);
    textheight = DrawTextA(hdc, wordbreak_text, -1, &rect, DT_CALCRECT | DT_WORDBREAK);
    ok(textheight == heightcheck * 2, "Got unexpected textheight %d, expected %d.\n",
       textheight, heightcheck * 2);
    SetRect(&rect, 0, 0, 1, 1);
    textheight = DrawTextA(hdc, wordbreak_text, -1, &rect, DT_CALCRECT | DT_WORDBREAK | DT_EDITCONTROL);
    ok(textheight >= heightcheck * 6, "Got unexpected textheight %d, expected at least %d.\n",
       textheight, heightcheck * 6);

    SetRect(&rect, 0, 0, 1, 1);
    heightcheck = DrawTextW(hdc, wordbreak_textW, -1, &rect, DT_CALCRECT);
    SetRect(&rect, 0, 0, 1, 1);
    textheight = DrawTextW(hdc, wordbreak_textW, -1, &rect, DT_CALCRECT | DT_WORDBREAK);
    ok(textheight == heightcheck * 2, "Got unexpected textheight %d, expected %d.\n",
       textheight, heightcheck * 2);
    SetRect(&rect, 0, 0, 1, 1);
    textheight = DrawTextW(hdc, wordbreak_textW, -1, &rect, DT_CALCRECT | DT_WORDBREAK | DT_EDITCONTROL);
    ok(textheight >= heightcheck * 6, "Got unexpected textheight %d, expected at least %d.\n",
       textheight, heightcheck * 6);

    /* DT_TABSTOP | DT_EXPANDTABS tests */
    SetRect( &rect, 0,0, 10, 10);
    textheight = DrawTextA(hdc, tabstring, -1, &rect, DT_TABSTOP | DT_EXPANDTABS );
    ok(textheight >= heightcheck, "Got unexpected textheight %d\n", textheight);

    SetRect( &rect, 0,0, 10, 10);
    memset(&dtp, 0, sizeof(dtp));
    dtp.cbSize = sizeof(dtp);
    textheight = DrawTextExA(hdc, tabstring, -1, &rect, DT_CALCRECT, &dtp);
    ok(textheight >= heightcheck, "Got unexpected textheight %d\n", textheight);
    ok(dtp.iTabLength == 0, "invalid dtp.iTabLength = %i\n",dtp.iTabLength);

    SetRect( &rect2, 0,0, 10, 10);
    memset(&dtp, 0, sizeof(dtp));
    dtp.cbSize = sizeof(dtp);
    textheight = DrawTextExA(hdc, tabstring, -1, &rect2, DT_CALCRECT | DT_TABSTOP | DT_EXPANDTABS, &dtp);
    ok(textheight >= heightcheck, "Got unexpected textheight %d\n", textheight);
    ok(dtp.iTabLength == 0, "invalid dtp.iTabLength = %i\n",dtp.iTabLength);
    ok(rect.left == rect2.left && rect.right != rect2.right && rect.top == rect2.top && rect.bottom == rect2.bottom,
       "incorrect rect %s rect2 %s\n", wine_dbgstr_rect(&rect), wine_dbgstr_rect(&rect2));

    SetRect( &rect, 0,0, 10, 10);
    memset(&dtp, 0, sizeof(dtp));
    dtp.cbSize = sizeof(dtp);
    dtp.iTabLength = 8;
    textheight = DrawTextExA(hdc, tabstring, -1, &rect, DT_CALCRECT | DT_TABSTOP | DT_EXPANDTABS, &dtp);
    ok(textheight >= heightcheck, "Got unexpected textheight %d\n", textheight);
    ok(dtp.iTabLength == 8, "invalid dtp.iTabLength = %i\n",dtp.iTabLength);
    ok(rect.left == rect2.left, "unexpected value %d, got %d\n", rect.left, rect2.left);
    /* XP, 2003 appear to not give the same values. */
    ok(rect.right == rect2.right || broken(rect.right > rect2.right), "unexpected value %d, got %d\n",rect.right, rect2.right);
    ok(rect.top == rect2.top, "unexpected value %d, got %d\n", rect.top, rect2.top);
    ok(rect.bottom == rect2.bottom , "unexpected value %d, got %d\n", rect.bottom, rect2.bottom);


    SelectObject(hdc, hOldFont);
    ret = DeleteObject(hFont);
    ok( ret, "DeleteObject error %u\n", GetLastError());

    /* Clean up */
    ret = ReleaseDC(hwnd, hdc);
    ok( ret, "ReleaseDC error %u\n", GetLastError());
    ret = DestroyWindow(hwnd);
    ok( ret, "DestroyWindow error %u\n", GetLastError());
}