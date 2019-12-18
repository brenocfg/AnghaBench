#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  desc ;
struct TYPE_6__ {int /*<<< orphan*/ * hicon; } ;
struct TYPE_5__ {int /*<<< orphan*/  hbitmap; int /*<<< orphan*/ * hpal; } ;
struct TYPE_7__ {int cbSizeofstruct; TYPE_2__ icon; int /*<<< orphan*/  picType; TYPE_1__ bmp; } ;
typedef  TYPE_3__ PICTDESC ;
typedef  scalar_t__ OLE_YSIZE_HIMETRIC ;
typedef  scalar_t__ OLE_XSIZE_HIMETRIC ;
typedef  int /*<<< orphan*/  IPicture ;
typedef  scalar_t__ INT ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/ * HICON ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  HBITMAP ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CreateBitmap (double,double,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CreateIcon (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int,int,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DestroyIcon (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 double GetDeviceCaps (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GetSystemMetrics (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IPicture ; 
 int /*<<< orphan*/  IPicture_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IPicture_get_Height (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ IPicture_get_Width (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  LOGPIXELSX ; 
 int /*<<< orphan*/  LOGPIXELSY ; 
 scalar_t__ MulDiv (scalar_t__,int,double) ; 
 scalar_t__ OleCreatePictureIndirect (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  PICTYPE_BITMAP ; 
 int /*<<< orphan*/  PICTYPE_ICON ; 
 int /*<<< orphan*/  SM_CXICON ; 
 int /*<<< orphan*/  SM_CYICON ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_himetric(void)
{
    static const BYTE bmp_bits[1024];
    OLE_XSIZE_HIMETRIC cx;
    OLE_YSIZE_HIMETRIC cy;
    IPicture *pic;
    PICTDESC desc;
    HBITMAP bmp;
    HRESULT hr;
    HICON icon;
    HDC hdc;
    INT d;

    desc.cbSizeofstruct = sizeof(desc);
    desc.picType = PICTYPE_BITMAP;
    desc.bmp.hpal = NULL;

    hdc = CreateCompatibleDC(0);

    bmp = CreateBitmap(1.9 * GetDeviceCaps(hdc, LOGPIXELSX),
                       1.9 * GetDeviceCaps(hdc, LOGPIXELSY), 1, 1, NULL);

    desc.bmp.hbitmap = bmp;

    /* size in himetric units reported rounded up to next integer value */
    hr = OleCreatePictureIndirect(&desc, &IID_IPicture, FALSE, (void**)&pic);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    cx = 0;
    d = MulDiv((INT)(1.9 * GetDeviceCaps(hdc, LOGPIXELSX)), 2540, GetDeviceCaps(hdc, LOGPIXELSX));
    hr = IPicture_get_Width(pic, &cx);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(cx == d, "got %d, expected %d\n", cx, d);

    cy = 0;
    d = MulDiv((INT)(1.9 * GetDeviceCaps(hdc, LOGPIXELSY)), 2540, GetDeviceCaps(hdc, LOGPIXELSY));
    hr = IPicture_get_Height(pic, &cy);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(cy == d, "got %d, expected %d\n", cy, d);

    DeleteObject(bmp);
    IPicture_Release(pic);

    /* same thing with icon */
    icon = CreateIcon(NULL, GetSystemMetrics(SM_CXICON), GetSystemMetrics(SM_CYICON),
                      1, 1, bmp_bits, bmp_bits);
    ok(icon != NULL, "failed to create icon\n");

    desc.picType = PICTYPE_ICON;
    desc.icon.hicon = icon;

    hr = OleCreatePictureIndirect(&desc, &IID_IPicture, FALSE, (void**)&pic);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    cx = 0;
    d = MulDiv(GetSystemMetrics(SM_CXICON), 2540, GetDeviceCaps(hdc, LOGPIXELSX));
    hr = IPicture_get_Width(pic, &cx);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(cx == d, "got %d, expected %d\n", cx, d);

    cy = 0;
    d = MulDiv(GetSystemMetrics(SM_CYICON), 2540, GetDeviceCaps(hdc, LOGPIXELSY));
    hr = IPicture_get_Height(pic, &cy);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(cy == d, "got %d, expected %d\n", cy, d);

    IPicture_Release(pic);
    DestroyIcon(icon);

    DeleteDC(hdc);
}