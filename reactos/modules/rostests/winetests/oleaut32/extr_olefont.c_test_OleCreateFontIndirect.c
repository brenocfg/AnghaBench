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
typedef  int /*<<< orphan*/  fontdesc ;
struct TYPE_4__ {int int64; } ;
struct TYPE_5__ {int cbSizeofstruct; void* fStrikethrough; void* fUnderline; void* fItalic; int /*<<< orphan*/  sCharset; int /*<<< orphan*/  sWeight; TYPE_1__ cySize; int /*<<< orphan*/  lpstrName; } ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IFont ;
typedef  scalar_t__ HRESULT ;
typedef  TYPE_2__ FONTDESC ;

/* Variables and functions */
 int /*<<< orphan*/  ANSI_CHARSET ; 
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_StdFont ; 
 scalar_t__ CoGetClassObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  EXPECT_HR (scalar_t__,scalar_t__) ; 
 void* FALSE ; 
 int /*<<< orphan*/  FW_NORMAL ; 
 int /*<<< orphan*/  IFont_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IClassFactory ; 
 int /*<<< orphan*/  IID_IFont ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 scalar_t__ IUnknown_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ OleInitialize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OleUninitialize () ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  arial_font ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ pOleCreateFontIndirect (TYPE_2__*,int /*<<< orphan*/ *,void**) ; 

__attribute__((used)) static void test_OleCreateFontIndirect(void)
{
    FONTDESC fontdesc;
    IUnknown *unk, *unk2;
    IFont *font;
    HRESULT hr;

    fontdesc.cbSizeofstruct = sizeof(fontdesc);
    fontdesc.lpstrName = arial_font;
    fontdesc.cySize.int64 = 12 * 10000; /* 12 pt */
    fontdesc.sWeight = FW_NORMAL;
    fontdesc.sCharset = ANSI_CHARSET;
    fontdesc.fItalic = FALSE;
    fontdesc.fUnderline = FALSE;
    fontdesc.fStrikethrough = FALSE;

    hr = pOleCreateFontIndirect(&fontdesc, &IID_IFont, (void**)&font);
    EXPECT_HR(hr, S_OK);
    IFont_Release(font);

    /* play with cbSizeofstruct value */
    fontdesc.cbSizeofstruct = sizeof(fontdesc)-1;
    hr = pOleCreateFontIndirect(&fontdesc, &IID_IFont, (void**)&font);
    EXPECT_HR(hr, S_OK);
    IFont_Release(font);

    fontdesc.cbSizeofstruct = sizeof(fontdesc)+1;
    hr = pOleCreateFontIndirect(&fontdesc, &IID_IFont, (void**)&font);
    EXPECT_HR(hr, S_OK);
    IFont_Release(font);

    fontdesc.cbSizeofstruct = 0;
    hr = pOleCreateFontIndirect(&fontdesc, &IID_IFont, (void**)&font);
    EXPECT_HR(hr, S_OK);
    IFont_Release(font);

    hr = OleInitialize(NULL);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = CoGetClassObject(&CLSID_StdFont, CLSCTX_INPROC_SERVER, NULL, &IID_IClassFactory, (void**)&unk);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = IUnknown_QueryInterface(unk, &IID_IUnknown, (void**)&unk2);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    IUnknown_Release(unk);
    IUnknown_Release(unk2);

    OleUninitialize();
}