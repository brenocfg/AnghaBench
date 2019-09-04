#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  s ;
typedef  int /*<<< orphan*/  imlData ;
typedef  int /*<<< orphan*/  WPARAM ;
struct TYPE_9__ {int lfHeight; int lfWidth; int /*<<< orphan*/  lfFaceName; int /*<<< orphan*/  lfWeight; } ;
struct TYPE_8__ {int cx; int cy; int /*<<< orphan*/  margin; scalar_t__ himl; } ;
typedef  TYPE_1__ SIZE ;
typedef  int /*<<< orphan*/  RECT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int LONG ;
typedef  TYPE_2__ LOGFONTW ;
typedef  int /*<<< orphan*/ * HWND ;
typedef  scalar_t__ HIMAGELIST ;
typedef  int /*<<< orphan*/ * HFONT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;
typedef  TYPE_1__ BUTTON_IMAGELIST ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BCM_GETIDEALSIZE ; 
 int /*<<< orphan*/  BCM_SETIMAGELIST ; 
 int /*<<< orphan*/  BCM_SETTEXTMARGIN ; 
 int /*<<< orphan*/  BM_SETIMAGE ; 
 int BS_BITMAP ; 
 int BS_CHECKBOX ; 
 int BS_OWNERDRAW ; 
 int BS_PUSHBUTTON ; 
 int BS_USERBUTTON ; 
 int BS_VCENTER ; 
 int /*<<< orphan*/ * CreateFontIndirectW (TYPE_2__*) ; 
 int /*<<< orphan*/ * CreateWindowW (char*,char*,int,int,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FW_BOLD ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetModuleHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetTextExtentPoint32W (int /*<<< orphan*/ ,char*,int,TYPE_1__*) ; 
 int /*<<< orphan*/  IMAGE_BITMAP ; 
 scalar_t__ ImageList_LoadImage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ LoadImage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKEINTRESOURCE (int) ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ SendMessageW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetRect (int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  SetWindowTheme (int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WM_GETFONT ; 
 int /*<<< orphan*/  WM_SETFONT ; 
 int WS_CHILD ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/  ok_size (TYPE_1__,int,int) ; 
 int /*<<< orphan*/  wcscpy (int /*<<< orphan*/ ,char*) ; 

void Test_GetIdealSizeNoThemes()
{
    HWND hwnd1, hwnd2;
    BOOL ret;
    SIZE s, textent;
    HFONT font;
    HDC hdc;
    HANDLE hbmp;
    HIMAGELIST himl;
    BUTTON_IMAGELIST imlData;
    RECT rc;
    LOGFONTW lf;
    DWORD i;

    hwnd2 = CreateWindowW(L"Static", L"", 0, 0, 0, 100, 100, 0, NULL, NULL, NULL);
    ok (hwnd2 != NULL, "Expected CreateWindowW to succeed\n");

    hwnd1 = CreateWindowW(L"Button", L" ", WS_CHILD, 10, 10, 100, 100, hwnd2, NULL, NULL, NULL);
    ok (hwnd1 != NULL, "Expected CreateWindowW to succeed\n");
    SetWindowTheme(hwnd1, L"", L"");

    font = (HFONT)SendMessageW(hwnd1, WM_GETFONT, 0, 0);
    hdc = GetDC(hwnd1);
    SelectObject(hdc, font);
    GetTextExtentPoint32W(hdc, L" ", 1, &textent);

    memset(&s, 0, sizeof(s));
    ret = SendMessageW(hwnd1, BCM_GETIDEALSIZE, 0, (LPARAM)&s);
    ok (ret == TRUE, "Expected BCM_GETIDEALSIZE to succeed\n");
    ok_size(s, textent.cx + 5 + 2, 
               textent.cy + 7 + 2); /* the last +2 is the text margin */

    DestroyWindow(hwnd1);


    hwnd1 = CreateWindowW(L"Button", L" ", BS_USERBUTTON | WS_CHILD, 10, 10, 100, 100, hwnd2, NULL, NULL, NULL);
    ok (hwnd1 != NULL, "Expected CreateWindowW to succeed\n");
    SetWindowTheme(hwnd1, L"", L"");

    memset(&s, 0, sizeof(s));
    ret = SendMessageW(hwnd1, BCM_GETIDEALSIZE, 0, (LPARAM)&s);
    ok (ret == TRUE, "Expected BCM_GETIDEALSIZE to succeed\n");
    ok_size(s, textent.cx + 5 + 2, 
               textent.cy + 7 + 2); /* the last +2 is the text margin */

    DestroyWindow(hwnd1);



    hwnd1 = CreateWindowW(L"Button", L"", WS_CHILD, 10, 10, 100, 100, hwnd2, NULL, NULL, NULL);
    ok (hwnd1 != NULL, "Expected CreateWindowW to succeed\n");
    SetWindowTheme(hwnd1, L"", L"");

    s.cx = 1;
    s.cy = 1;
    ret = SendMessageW(hwnd1, BCM_GETIDEALSIZE, 0, (LPARAM)&s);
    ok (ret == TRUE, "Expected BCM_GETIDEALSIZE to succeed\n");
    ok_size(s, 100, 100);

    hbmp = LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(5), IMAGE_BITMAP, 0, 0, 0);
    ok (hbmp != 0, "Expected LoadImage to succeed\n");

    SendMessageW(hwnd1, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hbmp);

    memset(&s, 0, sizeof(s));
    ret = SendMessageW(hwnd1, BCM_GETIDEALSIZE, 0, (LPARAM)&s);
    ok (ret == TRUE, "Expected BCM_GETIDEALSIZE to succeed\n");
    ok_size(s, 100, 100);

    himl = ImageList_LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(5), 1, 1, 0, IMAGE_BITMAP, 0);
    ok (himl != 0, "Expected ImageList_LoadImage to succeed\n");

    memset(&imlData, 0, sizeof(imlData));
    imlData.himl = himl;
    ret = SendMessageW(hwnd1, BCM_SETIMAGELIST, 0, (LPARAM)&imlData);
    ok (ret == TRUE, "Expected BCM_SETIMAGELIST to fail\n"); /* This works in win10 */

    memset(&s, 0, sizeof(s));
    ret = SendMessageW(hwnd1, BCM_GETIDEALSIZE, 0, (LPARAM)&s);
    ok (ret == TRUE, "Expected BCM_GETIDEALSIZE to succeed\n");
    ok_size(s, 100, 100);

    DestroyWindow(hwnd1);





    hwnd1 = CreateWindowW(L"Button", L"",  WS_CHILD, 10, 10, 5, 5, hwnd2, NULL, NULL, NULL);
    ok (hwnd1 != NULL, "Expected CreateWindowW to succeed\n");
    SetWindowTheme(hwnd1, L"", L"");

    memset(&s, 0, sizeof(s));
    ret = SendMessageW(hwnd1, BCM_GETIDEALSIZE, 0, (LPARAM)&s);
    ok (ret == TRUE, "Expected BCM_GETIDEALSIZE to succeed\n");
    ok_size(s, 5, 5);

    DestroyWindow(hwnd1);




    hwnd1 = CreateWindowW(L"Button", L" ", BS_BITMAP | WS_CHILD, 10, 10, 100, 100, hwnd2, NULL, NULL, NULL);
    ok (hwnd1 != NULL, "Expected CreateWindowW to succeed\n");
    SetWindowTheme(hwnd1, L"", L"");

    SendMessageW(hwnd1, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hbmp);

    memset(&s, 0, sizeof(s));
    ret = SendMessageW(hwnd1, BCM_GETIDEALSIZE, 0, (LPARAM)&s);
    ok (ret == TRUE, "Expected BCM_GETIDEALSIZE to succeed\n");

    /* In xp and 2k3 the image is ignored, in vista+ its width is added to the text width */
    ok_size(s, textent.cx + 5 + 2, 
               textent.cy + 7 + 2); /* the last +2 is the text margin */

    DestroyWindow(hwnd1);



    hwnd1 = CreateWindowW(L"Button", L" ", WS_CHILD, 10, 10, 100, 100, hwnd2, NULL, NULL, NULL);
    ok (hwnd1 != NULL, "Expected CreateWindowW to succeed\n");
    SetWindowTheme(hwnd1, L"", L"");

    SetRect(&rc, 0,0,0,0);
    ret = SendMessageW(hwnd1, BCM_SETTEXTMARGIN, 0, (LPARAM)&rc);
    ok (ret == TRUE, "Expected BCM_SETTEXTMARGIN to succeed\n");

    memset(&s, 0, sizeof(s));
    ret = SendMessageW(hwnd1, BCM_GETIDEALSIZE, 0, (LPARAM)&s);
    ok (ret == TRUE, "Expected BCM_GETIDEALSIZE to succeed\n");
    ok_size(s, textent.cx + 5, 
               textent.cy + 7);

    SetRect(&rc, 50,50,50,50);
    ret = SendMessageW(hwnd1, BCM_SETTEXTMARGIN, 0, (LPARAM)&rc);
    ok (ret == TRUE, "Expected BCM_SETTEXTMARGIN to succeed\n");

    memset(&s, 0, sizeof(s));
    ret = SendMessageW(hwnd1, BCM_GETIDEALSIZE, 0, (LPARAM)&s);
    ok (ret == TRUE, "Expected BCM_GETIDEALSIZE to succeed\n");
    ok_size(s, textent.cx + 5 + 100, 
               textent.cy + 7 + 100);

    SetRect(&rc, 1,1,1,1);
    ret = SendMessageW(hwnd1, BCM_SETTEXTMARGIN, 0, (LPARAM)&rc);
    ok (ret == TRUE, "Expected BCM_SETTEXTMARGIN to succeed\n");

    ret = SendMessageW(hwnd1, BCM_SETIMAGELIST, 0, (LPARAM)&imlData);
    ok (ret == TRUE, "Expected BCM_SETIMAGELIST to fail\n");

    memset(&s, 0, sizeof(s));
    ret = SendMessageW(hwnd1, BCM_GETIDEALSIZE, 0, (LPARAM)&s);
    ok (ret == TRUE, "Expected BCM_GETIDEALSIZE to succeed\n");
    ok_size(s, textent.cx + 5 + 2 + 1, /* we get an extra pixel due to the iml */
               textent.cy + 7 + 2);

    s.cx = 1;
    s.cy = 1;
    ret = SendMessageW(hwnd1, BCM_GETIDEALSIZE, 0, (LPARAM)&s);
    ok (ret == TRUE, "Expected BCM_GETIDEALSIZE to succeed\n");
    ok_size(s, textent.cx + 5 + 2 + 1,
               textent.cy + 7 + 2);

    s.cx = 100;
    s.cy = 100;
    ret = SendMessageW(hwnd1, BCM_GETIDEALSIZE, 0, (LPARAM)&s);
    ok (ret == TRUE, "Expected BCM_GETIDEALSIZE to succeed\n");
    ok_size(s, textent.cx + 5 + 2 + 1,
               textent.cy + 7 + 2);

    SetRect(&imlData.margin, 1,1,1,1);
    ret = SendMessageW(hwnd1, BCM_SETIMAGELIST, 0, (LPARAM)&imlData);
    ok (ret == TRUE, "Expected BCM_SETIMAGELIST to fail\n");

    memset(&s, 0, sizeof(s));
    ret = SendMessageW(hwnd1, BCM_GETIDEALSIZE, 0, (LPARAM)&s);
    ok (ret == TRUE, "Expected BCM_GETIDEALSIZE to succeed\n");
    /* expected width = text width + hardcoded value + text margins + image width + image margins */
    ok_size(s, textent.cx + 5 + 2 + 1 + 2,
               textent.cy + 7 + 2);

    SetRect(&imlData.margin, 50,50,50,50);
    ret = SendMessageW(hwnd1, BCM_SETIMAGELIST, 0, (LPARAM)&imlData);
    ok (ret == TRUE, "Expected BCM_SETIMAGELIST to fail\n");

    memset(&s, 0, sizeof(s));
    ret = SendMessageW(hwnd1, BCM_GETIDEALSIZE, 0, (LPARAM)&s);
    ok (ret == TRUE, "Expected BCM_GETIDEALSIZE to succeed\n");
    /* image + its margins is so big that the height is dictated by them */
    ok_size(s, textent.cx + 5 + 2 + 1 + 100, (LONG)101);

    DestroyWindow(hwnd1);






    hwnd1 = CreateWindowW(L"Button", L"Start", BS_VCENTER | WS_CHILD, 0, 0, 0, 0, hwnd2, NULL, NULL, NULL);
    ok (hwnd1 != NULL, "Expected CreateWindowW to succeed\n");
    SetWindowTheme(hwnd1, L"", L"");

    font = (HFONT)SendMessageW(hwnd1, WM_GETFONT, 0, 0);
    hdc = GetDC(hwnd1);
    SelectObject(hdc, font);
    GetTextExtentPoint32W(hdc, L"Start", 5, &textent);

    SetRect(&rc, 0,0,0,0);
    ret = SendMessageW(hwnd1, BCM_SETTEXTMARGIN, 0, (LPARAM)&rc);
    ok (ret == TRUE, "Expected BCM_SETTEXTMARGIN to succeed\n");

    memset(&s, 0, sizeof(s));
    ret = SendMessageW(hwnd1, BCM_GETIDEALSIZE, 0, (LPARAM)&s);
    ok (ret == TRUE, "Expected BCM_GETIDEALSIZE to succeed\n");
    ok_size(s, textent.cx + 5, textent.cy + 7);

    DestroyWindow(hwnd1);




    /* Test again with some real text to see if the formula is correct */
    hwnd1 = CreateWindowW(L"Button", L"Some test text", WS_CHILD, 10, 10, 100, 100, hwnd2, NULL, NULL, NULL);
    ok (hwnd1 != NULL, "Expected CreateWindowW to succeed\n");
    SetWindowTheme(hwnd1, L"", L"");

    font = (HFONT)SendMessageW(hwnd1, WM_GETFONT, 0, 0);
    hdc = GetDC(hwnd1);
    SelectObject(hdc, font);
    GetTextExtentPoint32W(hdc, L"Some test text", 14, &textent);

    memset(&s, 0, sizeof(s));
    ret = SendMessageW(hwnd1, BCM_GETIDEALSIZE, 0, (LPARAM)&s);
    ok (ret == TRUE, "Expected BCM_GETIDEALSIZE to succeed\n");
    ok_size(s, textent.cx + 5 + 2,  /* the last +2 is the text margin */
               textent.cy + 7 + 2);

    /* The hardcoded values are independent of the margin */
    lf.lfHeight = 200;
    lf.lfWidth = 200;
    lf.lfWeight = FW_BOLD;
    wcscpy(lf.lfFaceName, L"Arial");
    font = CreateFontIndirectW(&lf);
    ok(font != NULL, "\n");
    SendMessageW(hwnd1, WM_SETFONT, (WPARAM)font, FALSE);

    SelectObject(hdc, font);
    GetTextExtentPoint32W(hdc, L"Some test text", 14, &textent);

    memset(&s, 0, sizeof(s));
    ret = SendMessageW(hwnd1, BCM_GETIDEALSIZE, 0, (LPARAM)&s);
    ok (ret == TRUE, "Expected BCM_GETIDEALSIZE to succeed\n");
    ok_size(s, textent.cx + 5 + 2,  /* the last +2 is the text margin */
               textent.cy + 7 + 2);

    DestroyWindow(hwnd1);

    for (i = BS_PUSHBUTTON; i <= BS_OWNERDRAW; i++)
    {
        if (i == BS_USERBUTTON)
            continue;

        if (i >= BS_CHECKBOX)
        {
            hwnd1 = CreateWindowW(L"Button", L" ", i|WS_CHILD, 0, 0, 72, 72, hwnd2, NULL, NULL, NULL);
            ok (hwnd1 != NULL, "Expected CreateWindowW to succeed\n");
            memset(&s, 0, sizeof(s));
            ret = SendMessageW(hwnd1, BCM_GETIDEALSIZE, 0, (LPARAM)&s);
            ok (ret == TRUE, "Expected BCM_GETIDEALSIZE to succeed\n");
            ok_size(s, 72, 72);

            SetWindowTheme(hwnd1, L"", L"");
            memset(&s, 0, sizeof(s));
            ret = SendMessageW(hwnd1, BCM_GETIDEALSIZE, 0, (LPARAM)&s);
            ok (ret == TRUE, "Expected BCM_GETIDEALSIZE to succeed\n");
            ok_size(s, 72, 72);
            DestroyWindow(hwnd1);

            hwnd1 = CreateWindowW(L"Button", L" ", i|WS_CHILD, 0, 0, 12, 12, hwnd2, NULL, NULL, NULL);
            ok (hwnd1 != NULL, "Expected CreateWindowW to succeed\n");
            memset(&s, 0, sizeof(s));
            ret = SendMessageW(hwnd1, BCM_GETIDEALSIZE, 0, (LPARAM)&s);
            ok (ret == TRUE, "Expected BCM_GETIDEALSIZE to succeed\n");
            ok_size(s, 12, 12);
            DestroyWindow(hwnd1);
        }

        hwnd1 = CreateWindowW(L"Button", L"", i|WS_CHILD, 0, 0, 72, 72, hwnd2, NULL, NULL, NULL);
        ok (hwnd1 != NULL, "Expected CreateWindowW to succeed\n");
        memset(&s, 0, sizeof(s));
        ret = SendMessageW(hwnd1, BCM_GETIDEALSIZE, 0, (LPARAM)&s);
        ok (ret == TRUE, "Expected BCM_GETIDEALSIZE to succeed\n");
        ok_size(s, 72, 72);
        DestroyWindow(hwnd1);
        
        hwnd1 = CreateWindowW(L"Button", L"", i|WS_CHILD, 0, 0, 150, 72, hwnd2, NULL, NULL, NULL);
        ok (hwnd1 != NULL, "Expected CreateWindowW to succeed\n");
        memset(&s, 0, sizeof(s));
        ret = SendMessageW(hwnd1, BCM_GETIDEALSIZE, 0, (LPARAM)&s);
        ok (ret == TRUE, "Expected BCM_GETIDEALSIZE to succeed\n");
        ok_size(s, 150, 72);
        DestroyWindow(hwnd1);
    }
    DestroyWindow(hwnd2);
}