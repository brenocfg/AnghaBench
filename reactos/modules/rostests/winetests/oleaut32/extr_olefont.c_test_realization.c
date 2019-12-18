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
struct TYPE_5__ {int cbSizeofstruct; int /*<<< orphan*/  lpstrName; void* fStrikethrough; void* fUnderline; void* fItalic; scalar_t__ sCharset; int /*<<< orphan*/  sWeight; TYPE_1__ cySize; } ;
typedef  scalar_t__ SHORT ;
typedef  int /*<<< orphan*/  IFont ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_2__ FONTDESC ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 scalar_t__ ANSI_CHARSET ; 
 int /*<<< orphan*/  EXPECT_HR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* FALSE ; 
 int /*<<< orphan*/  FW_NORMAL ; 
 int /*<<< orphan*/  IFont_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFont_get_Charset (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  IFont_get_Name (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFont_put_Name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IFont ; 
 scalar_t__ SYMBOL_CHARSET ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  SysAllocString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arial_font ; 
 int /*<<< orphan*/  lstrcmpiW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  marlett_font ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  pOleCreateFontIndirect (TYPE_2__*,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ wine_dbgstr_w (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_realization(void)
{
    IFont *font;
    FONTDESC fontdesc;
    HRESULT hr;
    BSTR name;
    SHORT cs;

    /* Try to create a symbol only font (marlett) with charset
       set to ANSI.  This will result in another, ANSI, font
       being selected */
    fontdesc.cbSizeofstruct = sizeof(fontdesc);
    fontdesc.lpstrName = marlett_font;
    fontdesc.cySize.int64 = 12 * 10000; /* 12 pt */
    fontdesc.sWeight = FW_NORMAL;
    fontdesc.sCharset = ANSI_CHARSET;
    fontdesc.fItalic = FALSE;
    fontdesc.fUnderline = FALSE;
    fontdesc.fStrikethrough = FALSE;

    hr = pOleCreateFontIndirect(&fontdesc, &IID_IFont, (void **)&font);
    EXPECT_HR(hr, S_OK);

    hr = IFont_get_Charset(font, &cs);
    EXPECT_HR(hr, S_OK);
    ok(cs == ANSI_CHARSET, "got charset %d\n", cs);

    IFont_Release(font);

    /* Now create an ANSI font and change the name to marlett */

    fontdesc.lpstrName = arial_font;

    hr = pOleCreateFontIndirect(&fontdesc, &IID_IFont, (void **)&font);
    EXPECT_HR(hr, S_OK);

    hr = IFont_get_Charset(font, &cs);
    EXPECT_HR(hr, S_OK);
    ok(cs == ANSI_CHARSET, "got charset %d\n", cs);

    name = SysAllocString(marlett_font);
    hr = IFont_put_Name(font, name);
    EXPECT_HR(hr, S_OK);
    SysFreeString(name);

    hr = IFont_get_Name(font, &name);
    EXPECT_HR(hr, S_OK);
    ok(!lstrcmpiW(name, marlett_font), "got name %s\n", wine_dbgstr_w(name));
    SysFreeString(name);

    hr = IFont_get_Charset(font, &cs);
    EXPECT_HR(hr, S_OK);
    ok(cs == SYMBOL_CHARSET, "got charset %d\n", cs);

    IFont_Release(font);
}