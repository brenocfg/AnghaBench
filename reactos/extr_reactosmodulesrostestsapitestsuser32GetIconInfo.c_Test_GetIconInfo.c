#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bitmap ;
struct TYPE_7__ {scalar_t__ bmType; int bmWidth; int bmHeight; int bmWidthBytes; int bmPlanes; int bmBitsPixel; int /*<<< orphan*/ * bmBits; } ;
struct TYPE_6__ {scalar_t__ fIcon; int xHotspot; int yHotspot; int /*<<< orphan*/ * hbmColor; int /*<<< orphan*/ * hbmMask; } ;
typedef  TYPE_1__ ICONINFO ;
typedef  scalar_t__ HICON ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;
typedef  TYPE_2__ BITMAP ;

/* Variables and functions */
 void* CreateBitmap (int,int,int,int,int /*<<< orphan*/ *) ; 
 void* CreateCompatibleBitmap (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ CreateIconIndirect (TYPE_1__*) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 
 int DestroyIcon (scalar_t__) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int GetIconInfo (scalar_t__,TYPE_1__*) ; 
 int GetObject (int /*<<< orphan*/ *,int,TYPE_2__*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

void
Test_GetIconInfo(BOOL fIcon, DWORD screen_bpp)
{
    HICON hicon;
    ICONINFO iconinfo, iconinfo2;
    BITMAP bitmap;

    iconinfo.fIcon = fIcon;
    iconinfo.xHotspot = 0;
    iconinfo.yHotspot = 0;
    iconinfo.hbmMask = NULL;
    iconinfo.hbmColor = NULL;

    hicon = CreateIconIndirect(&iconinfo);
    ok(hicon == 0, "should fail\n");

    iconinfo.hbmMask = CreateBitmap(8, 16, 1, 1, NULL);
    hicon = CreateIconIndirect(&iconinfo);
    ok(hicon != 0, "should not fail\n");

    ok(GetIconInfo(hicon, &iconinfo2), "\n");
    ok(iconinfo2.fIcon == iconinfo.fIcon, "\n");
    if (fIcon)
    {
        ok(iconinfo2.xHotspot == 4, "%ld\n", iconinfo2.xHotspot);
        ok(iconinfo2.yHotspot == 4, "%ld\n", iconinfo2.yHotspot);
    }
    else
    {
        ok(iconinfo2.xHotspot == 0, "%ld\n", iconinfo2.xHotspot);
        ok(iconinfo2.yHotspot == 0, "%ld\n", iconinfo2.yHotspot);
    }
    ok(iconinfo2.hbmMask != NULL, "\n");
    ok(iconinfo2.hbmMask != iconinfo.hbmMask, "\n");
    ok(iconinfo2.hbmColor == NULL, "\n");
    DeleteObject(iconinfo2.hbmMask);

    ok(GetIconInfo(hicon, &iconinfo2), "\n");
    ok(iconinfo2.fIcon == iconinfo.fIcon, "\n");
    if (fIcon)
    {
        ok(iconinfo2.xHotspot == 4, "%ld\n", iconinfo2.xHotspot);
        ok(iconinfo2.yHotspot == 4, "%ld\n", iconinfo2.yHotspot);
    }
    else
    {
        ok(iconinfo2.xHotspot == 0, "%ld\n", iconinfo2.xHotspot);
        ok(iconinfo2.yHotspot == 0, "%ld\n", iconinfo2.yHotspot);
    }
    ok(iconinfo2.hbmMask != NULL, "\n");
    ok(iconinfo2.hbmMask != iconinfo.hbmMask, "\n");
    ok(iconinfo2.hbmColor == NULL, "\n");
    DeleteObject(iconinfo2.hbmMask);
    ok(DestroyIcon(hicon), "\n");

    iconinfo.hbmColor = CreateBitmap(2, 2, 1, 1, NULL);
    hicon = CreateIconIndirect(&iconinfo);
    ok(hicon != 0, "should not fail\n");

    ok(GetIconInfo(hicon, &iconinfo2), "\n");
    ok(iconinfo2.fIcon == iconinfo.fIcon, "\n");
    if (fIcon)
    {
        ok(iconinfo2.xHotspot == 4, "%ld\n", iconinfo2.xHotspot);
        ok(iconinfo2.yHotspot == 8, "%ld\n", iconinfo2.yHotspot);
    }
    else
    {
        ok(iconinfo2.xHotspot == 0, "%ld\n", iconinfo2.xHotspot);
        ok(iconinfo2.yHotspot == 0, "%ld\n", iconinfo2.yHotspot);
    }
    ok(iconinfo2.hbmMask != NULL, "\n");
    ok(iconinfo2.hbmMask != iconinfo.hbmMask, "\n");
    ok(iconinfo2.hbmColor != NULL, "\n");
    ok(iconinfo2.hbmColor != iconinfo.hbmColor, "\n");

    ok(GetObject(iconinfo2.hbmMask, sizeof(bitmap), &bitmap), "GetObject failed\n");
    ok(bitmap.bmType == 0, "\n");
    ok(bitmap.bmWidth == 8, "\n");
    ok(bitmap.bmHeight == 16, "\n");
    ok(bitmap.bmWidthBytes == 2, "\n");
    ok(bitmap.bmPlanes == 1, "\n");
    ok(bitmap.bmBitsPixel == 1, "\n");
    ok(bitmap.bmBits == NULL, "\n");

    ok(GetObject(iconinfo2.hbmColor, sizeof(bitmap), &bitmap), "GetObject failed\n");
    ok(bitmap.bmType == 0, "\n");
    ok(bitmap.bmWidth == 8, "\n");
    ok(bitmap.bmHeight == 16, "\n");
    ok(bitmap.bmWidthBytes == 8 * bitmap.bmBitsPixel / 8, "\n");
    ok(bitmap.bmPlanes == 1, "\n");
    ok(bitmap.bmBitsPixel == screen_bpp, "%d\n", bitmap.bmBitsPixel);
    ok(bitmap.bmBits == NULL, "\n");
    DeleteObject(iconinfo2.hbmMask);
    DeleteObject(iconinfo2.hbmColor);
    ok(DestroyIcon(hicon), "\n");

    DeleteObject(iconinfo.hbmMask);
    iconinfo.hbmMask = NULL;
    hicon = CreateIconIndirect(&iconinfo);
    ok(hicon == 0, "should fail\n");

    DeleteObject(iconinfo.hbmColor);
    iconinfo.hbmColor = CreateCompatibleBitmap(GetDC(0), 16, 16);
    hicon = CreateIconIndirect(&iconinfo);
    ok(hicon == 0, "should fail\n");

    iconinfo.hbmMask = CreateCompatibleBitmap(GetDC(0), 8, 16);
    hicon = CreateIconIndirect(&iconinfo);
    ok(hicon != 0, "should not fail\n");

    ok(GetIconInfo(hicon, &iconinfo2), "\n");

    ok(GetObject(iconinfo2.hbmMask, sizeof(bitmap), &bitmap), "GetObject failed\n");
    ok(bitmap.bmType == 0, "\n");
    ok(bitmap.bmWidth == 8, "%ld\n", bitmap.bmWidth);
    ok(bitmap.bmHeight == 16, "%ld\n", bitmap.bmHeight);
    ok(bitmap.bmWidthBytes == 2, "%ld\n", bitmap.bmWidthBytes);
    ok(bitmap.bmPlanes == 1, "%d\n", bitmap.bmPlanes);
    ok(bitmap.bmBitsPixel == 1, "%d\n", bitmap.bmBitsPixel);
    ok(bitmap.bmBits == NULL, "\n");

    ok(GetObject(iconinfo2.hbmColor, sizeof(bitmap), &bitmap), "GetObject failed\n");
    ok(bitmap.bmType == 0, "\n");
    ok(bitmap.bmWidth == 8, "%ld\n", bitmap.bmWidth);
    ok(bitmap.bmHeight == 16, "%ld\n", bitmap.bmHeight);
    ok(bitmap.bmWidthBytes == screen_bpp, "%ld\n", bitmap.bmWidthBytes);
    ok(bitmap.bmPlanes == 1, "%d\n", bitmap.bmPlanes);
    ok(bitmap.bmBitsPixel == screen_bpp, "%d\n", bitmap.bmBitsPixel);
    ok(bitmap.bmBits == NULL, "\n");
    DeleteObject(iconinfo2.hbmMask);
    DeleteObject(iconinfo2.hbmColor);
    ok(DestroyIcon(hicon), "\n");
}