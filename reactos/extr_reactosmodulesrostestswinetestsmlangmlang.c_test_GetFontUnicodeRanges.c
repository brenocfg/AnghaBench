#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lf ;
typedef  int /*<<< orphan*/  UNICODERANGE ;
typedef  int UINT ;
struct TYPE_4__ {int /*<<< orphan*/  lfFaceName; } ;
typedef  TYPE_1__ LOGFONTA ;
typedef  int /*<<< orphan*/  IMLangFontLink2 ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  HFONT ;
typedef  int /*<<< orphan*/ * HDC ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateFontIndirectA (TYPE_1__*) ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 scalar_t__ E_FAIL ; 
 scalar_t__ E_INVALIDARG ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ IMLangFontLink2_GetFontUnicodeRanges (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrcpyA (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_GetFontUnicodeRanges(IMLangFontLink2 *font_link)
{
    HRESULT hr;
    UINT count;
    HFONT hfont, old_hfont;
    LOGFONTA lf;
    HDC hdc;
    UNICODERANGE *ur;

    hdc = CreateCompatibleDC(0);
    memset(&lf, 0, sizeof(lf));
    lstrcpyA(lf.lfFaceName, "Arial");
    hfont = CreateFontIndirectA(&lf);
    old_hfont = SelectObject(hdc, hfont);

    count = 0;
    hr = IMLangFontLink2_GetFontUnicodeRanges(font_link, NULL, &count, NULL);
    ok(hr == E_FAIL, "expected E_FAIL, got 0x%08x\n", hr);

    hr = IMLangFontLink2_GetFontUnicodeRanges(font_link, hdc, NULL, NULL);
    ok(hr == E_INVALIDARG, "expected E_FAIL, got 0x%08x\n", hr);

    count = 0;
    hr = IMLangFontLink2_GetFontUnicodeRanges(font_link, hdc, &count, NULL);
    ok(hr == S_OK, "expected S_OK, got 0x%08x\n", hr);
    ok(count, "expected count > 0\n");

    ur = HeapAlloc(GetProcessHeap(), 0, sizeof(*ur) * count);

    hr = IMLangFontLink2_GetFontUnicodeRanges(font_link, hdc, &count, ur);
    ok(hr == S_OK, "expected S_OK, got 0x%08x\n", hr);

    count--;
    hr = IMLangFontLink2_GetFontUnicodeRanges(font_link, hdc, &count, ur);
    ok(hr == S_OK, "expected S_OK, got 0x%08x\n", hr);

    HeapFree(GetProcessHeap(), 0, ur);

    SelectObject(hdc, old_hfont);
    DeleteObject(hfont);
    DeleteDC(hdc);
}