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
struct TYPE_5__ {int cbSizeofstruct; void* fStrikethrough; void* fUnderline; void* fItalic; scalar_t__ sCharset; int /*<<< orphan*/  sWeight; TYPE_1__ cySize; int /*<<< orphan*/  lpstrName; } ;
typedef  int /*<<< orphan*/  IFont ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_2__ FONTDESC ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_E_INVALIDPROPERTYVALUE ; 
 int /*<<< orphan*/  EXPECT_HR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_POINTER ; 
 void* FALSE ; 
 int /*<<< orphan*/  FW_NORMAL ; 
 int /*<<< orphan*/  IFont_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFont_get_Bold (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFont_get_Name (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFont_get_Size (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFont_put_Name (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IFont ; 
 int /*<<< orphan*/  MSSansSerif_font ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  pOleCreateFontIndirect (TYPE_2__*,int /*<<< orphan*/ *,void**) ; 

__attribute__((used)) static void test_returns(void)
{
    IFont *pFont;
    FONTDESC fontdesc;
    HRESULT hr;

    fontdesc.cbSizeofstruct = sizeof(fontdesc);
    fontdesc.lpstrName = MSSansSerif_font;
    fontdesc.cySize.int64 = 12 * 10000; /* 12 pt */
    fontdesc.sWeight = FW_NORMAL;
    fontdesc.sCharset = 0;
    fontdesc.fItalic = FALSE;
    fontdesc.fUnderline = FALSE;
    fontdesc.fStrikethrough = FALSE;

    hr = pOleCreateFontIndirect(&fontdesc, &IID_IFont, (void **)&pFont);
    EXPECT_HR(hr, S_OK);

    hr = IFont_put_Name(pFont, NULL);
    EXPECT_HR(hr, CTL_E_INVALIDPROPERTYVALUE);

    hr = IFont_get_Name(pFont, NULL);
    EXPECT_HR(hr, E_POINTER);

    hr = IFont_get_Size(pFont, NULL);
    EXPECT_HR(hr, E_POINTER);

    hr = IFont_get_Bold(pFont, NULL);
    EXPECT_HR(hr, E_POINTER);

    IFont_Release(pFont);
}