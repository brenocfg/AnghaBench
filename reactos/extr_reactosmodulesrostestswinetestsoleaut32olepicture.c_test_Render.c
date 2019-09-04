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
struct TYPE_4__ {int /*<<< orphan*/  hicon; } ;
struct TYPE_5__ {int cbSizeofstruct; TYPE_1__ icon; int /*<<< orphan*/  picType; } ;
typedef  TYPE_2__ PICTDESC ;
typedef  int OLE_YSIZE_HIMETRIC ;
typedef  int OLE_XSIZE_HIMETRIC ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int /*<<< orphan*/  IPicture ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  COLORREF ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_E_INVALIDPROPERTYVALUE ; 
 int /*<<< orphan*/  GetPixel (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ IDI_APPLICATION ; 
 int /*<<< orphan*/  IID_IPicture ; 
 int /*<<< orphan*/  IPicture_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPicture_get_Height (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  IPicture_get_Type (int /*<<< orphan*/ *,short*) ; 
 int /*<<< orphan*/  IPicture_get_Width (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  LoadIconA (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OleCreatePictureIndirect (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  PICTYPE_ICON ; 
 short PICTYPE_UNINITIALIZED ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  SetPixelV (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  create_render_dc () ; 
 int /*<<< orphan*/  delete_render_dc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,short,...) ; 
 int /*<<< orphan*/  ole_expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  picture_render (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_Render(void)
{
    IPicture *pic;
    HRESULT hres;
    short type;
    PICTDESC desc;
    OLE_XSIZE_HIMETRIC pWidth;
    OLE_YSIZE_HIMETRIC pHeight;
    COLORREF result, expected;
    HDC hdc = create_render_dc();

    /* test IPicture::Render return code on uninitialized picture */
    hres = OleCreatePictureIndirect(NULL, &IID_IPicture, TRUE, (void **)&pic);
    ok(hres == S_OK, "Failed to create a picture, hr %#x.\n", hres);
    hres = IPicture_get_Type(pic, &type);
    ok(hres == S_OK, "IPicture_get_Type does not return S_OK, but 0x%08x\n", hres);
    ok(type == PICTYPE_UNINITIALIZED, "Expected type = PICTYPE_UNINITIALIZED, got = %d\n", type);
    /* zero dimensions */
    hres = picture_render(pic, hdc, 0, 0, 0, 0, 0, 0, 0, 0, NULL);
    ole_expect(hres, CTL_E_INVALIDPROPERTYVALUE);
    hres = picture_render(pic, hdc, 0, 0, 10, 10, 0, 0, 10, 0, NULL);
    ole_expect(hres, CTL_E_INVALIDPROPERTYVALUE);
    hres = picture_render(pic, hdc, 0, 0, 10, 10, 0, 0, 0, 10, NULL);
    ole_expect(hres, CTL_E_INVALIDPROPERTYVALUE);
    hres = picture_render(pic, hdc, 0, 0, 10, 10, 0, 0, 0, 0, NULL);
    ole_expect(hres, CTL_E_INVALIDPROPERTYVALUE);
    hres = picture_render(pic, hdc, 0, 0, 0, 10, 0, 0, 10, 10, NULL);
    ole_expect(hres, CTL_E_INVALIDPROPERTYVALUE);
    hres = picture_render(pic, hdc, 0, 0, 10, 0, 0, 0, 10, 10, NULL);
    ole_expect(hres, CTL_E_INVALIDPROPERTYVALUE);
    hres = picture_render(pic, hdc, 0, 0, 0, 0, 0, 0, 10, 10, NULL);
    ole_expect(hres, CTL_E_INVALIDPROPERTYVALUE);
    /* nonzero dimensions, PICTYPE_UNINITIALIZED */
    hres = picture_render(pic, hdc, 0, 0, 10, 10, 0, 0, 10, 10, NULL);
    ole_expect(hres, S_OK);
    IPicture_Release(pic);

    desc.cbSizeofstruct = sizeof(PICTDESC);
    desc.picType = PICTYPE_ICON;
    desc.icon.hicon = LoadIconA(NULL, (LPCSTR)IDI_APPLICATION);
    if(!desc.icon.hicon){
        win_skip("LoadIcon failed. Skipping...\n");
        delete_render_dc(hdc);
        return;
    }

    hres = OleCreatePictureIndirect(&desc, &IID_IPicture, TRUE, (void **)&pic);
    ok(hres == S_OK, "Failed to create a picture, hr %#x.\n", hres);
    /* zero dimensions, PICTYPE_ICON */
    hres = picture_render(pic, hdc, 0, 0, 0, 0, 0, 0, 0, 0, NULL);
    ole_expect(hres, CTL_E_INVALIDPROPERTYVALUE);
    hres = picture_render(pic, hdc, 0, 0, 10, 10, 0, 0, 10, 0, NULL);
    ole_expect(hres, CTL_E_INVALIDPROPERTYVALUE);
    hres = picture_render(pic, hdc, 0, 0, 10, 10, 0, 0, 0, 10, NULL);
    ole_expect(hres, CTL_E_INVALIDPROPERTYVALUE);
    hres = picture_render(pic, hdc, 0, 0, 10, 10, 0, 0, 0, 0, NULL);
    ole_expect(hres, CTL_E_INVALIDPROPERTYVALUE);
    hres = picture_render(pic, hdc, 0, 0, 0, 10, 0, 0, 10, 10, NULL);
    ole_expect(hres, CTL_E_INVALIDPROPERTYVALUE);
    hres = picture_render(pic, hdc, 0, 0, 10, 0, 0, 0, 10, 10, NULL);
    ole_expect(hres, CTL_E_INVALIDPROPERTYVALUE);
    hres = picture_render(pic, hdc, 0, 0, 0, 0, 0, 0, 10, 10, NULL);
    ole_expect(hres, CTL_E_INVALIDPROPERTYVALUE);

    /* Check if target size and position is respected */
    IPicture_get_Width(pic, &pWidth);
    IPicture_get_Height(pic, &pHeight);

    SetPixelV(hdc, 0, 0, 0x00223344);
    SetPixelV(hdc, 5, 5, 0x00223344);
    SetPixelV(hdc, 10, 10, 0x00223344);
    expected = GetPixel(hdc, 0, 0);

    hres = picture_render(pic, hdc, 1, 1, 9, 9, 0, pHeight, pWidth, -pHeight, NULL);
    ole_expect(hres, S_OK);

    if(hres != S_OK) goto done;

    /* Evaluate the rendered Icon */
    result = GetPixel(hdc, 0, 0);
    ok(result == expected,
       "Color at 0,0 should be unchanged 0x%06X, but was 0x%06X\n", expected, result);
    result = GetPixel(hdc, 5, 5);
    ok(result != expected,
       "Color at 5,5 should have changed, but still was 0x%06X\n", expected);
    result = GetPixel(hdc, 10, 10);
    ok(result == expected,
       "Color at 10,10 should be unchanged 0x%06X, but was 0x%06X\n", expected, result);

done:
    IPicture_Release(pic);
    delete_render_dc(hdc);
}