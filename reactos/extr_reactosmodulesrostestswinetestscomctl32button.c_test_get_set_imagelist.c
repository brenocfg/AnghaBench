#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int uAlign; int /*<<< orphan*/ * himl; int /*<<< orphan*/  margin; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/ * HWND ;
typedef  int /*<<< orphan*/ * HIMAGELIST ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/ * HBITMAP ;
typedef  scalar_t__ DWORD ;
typedef  TYPE_1__ BUTTON_IMAGELIST ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BCM_GETIMAGELIST ; 
 int /*<<< orphan*/  BCM_SETIMAGELIST ; 
 scalar_t__ BS_DEFCOMMANDLINK ; 
 scalar_t__ BS_PUSHBUTTON ; 
 void* BUTTON_IMAGELIST_ALIGN_CENTER ; 
 int /*<<< orphan*/ * CreateCompatibleBitmap (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILC_COLOR ; 
 scalar_t__ IsRectEmpty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SendMessageA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/ * create_button (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ pImageList_Add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pImageList_Create (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pImageList_Destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_get_set_imagelist(void)
{
    HWND hwnd;
    HIMAGELIST himl;
    BUTTON_IMAGELIST biml = {0};
    HDC hdc;
    HBITMAP hbmp;
    INT width = 16;
    INT height = 16;
    INT index;
    DWORD type;
    BOOL ret;

    hdc = GetDC(0);
    hbmp = CreateCompatibleBitmap(hdc, width, height);
    ok(hbmp != NULL, "Expect hbmp not null\n");

    himl = pImageList_Create(width, height, ILC_COLOR, 1, 0);
    ok(himl != NULL, "Expect himl not null\n");
    index = pImageList_Add(himl, hbmp, NULL);
    ok(index == 0, "Expect index == 0\n");
    DeleteObject(hbmp);
    ReleaseDC(0, hdc);

    for (type = BS_PUSHBUTTON; type <= BS_DEFCOMMANDLINK; type++)
    {
        hwnd = create_button(type, NULL);
        ok(hwnd != NULL, "Expect hwnd not null\n");

        /* Get imagelist when imagelist is unset yet */
        ret = SendMessageA(hwnd, BCM_GETIMAGELIST, 0, (LPARAM)&biml);
        ok(ret, "Expect BCM_GETIMAGELIST return true\n");
        ok(biml.himl == 0 && IsRectEmpty(&biml.margin) && biml.uAlign == 0,
           "Expect BUTTON_IMAGELIST is empty\n");

        /* Set imagelist with himl null */
        biml.himl = 0;
        biml.uAlign = BUTTON_IMAGELIST_ALIGN_CENTER;
        ret = SendMessageA(hwnd, BCM_SETIMAGELIST, 0, (LPARAM)&biml);
        ok(ret || broken(!ret), /* xp or 2003 */
           "Expect BCM_SETIMAGELIST return true\n");

        /* Set imagelist with uAlign invalid */
        biml.himl = himl;
        biml.uAlign = -1;
        ret = SendMessageA(hwnd, BCM_SETIMAGELIST, 0, (LPARAM)&biml);
        ok(ret, "Expect BCM_SETIMAGELIST return true\n");

        /* Successful get and set imagelist */
        biml.himl = himl;
        biml.uAlign = BUTTON_IMAGELIST_ALIGN_CENTER;
        ret = SendMessageA(hwnd, BCM_SETIMAGELIST, 0, (LPARAM)&biml);
        ok(ret, "Expect BCM_SETIMAGELIST return true\n");
        ret = SendMessageA(hwnd, BCM_GETIMAGELIST, 0, (LPARAM)&biml);
        ok(ret, "Expect BCM_GETIMAGELIST return true\n");
        ok(biml.himl == himl, "Expect himl to be same\n");
        ok(biml.uAlign == BUTTON_IMAGELIST_ALIGN_CENTER, "Expect uAlign to be %x\n",
           BUTTON_IMAGELIST_ALIGN_CENTER);

        /* BCM_SETIMAGELIST null pointer handling */
        ret = SendMessageA(hwnd, BCM_SETIMAGELIST, 0, 0);
        ok(!ret, "Expect BCM_SETIMAGELIST return false\n");
        ret = SendMessageA(hwnd, BCM_GETIMAGELIST, 0, (LPARAM)&biml);
        ok(ret, "Expect BCM_GETIMAGELIST return true\n");
        ok(biml.himl == himl, "Expect himl to be same\n");

        /* BCM_GETIMAGELIST null pointer handling */
        biml.himl = himl;
        biml.uAlign = BUTTON_IMAGELIST_ALIGN_CENTER;
        ret = SendMessageA(hwnd, BCM_SETIMAGELIST, 0, (LPARAM)&biml);
        ok(ret, "Expect BCM_SETIMAGELIST return true\n");
        ret = SendMessageA(hwnd, BCM_GETIMAGELIST, 0, 0);
        ok(!ret, "Expect BCM_GETIMAGELIST return false\n");

        DestroyWindow(hwnd);
    }

    pImageList_Destroy(himl);
}