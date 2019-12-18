#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int LPARAM ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  ITextSelection ;
typedef  int /*<<< orphan*/  ITextRange ;
typedef  int /*<<< orphan*/  ITextFont ;
typedef  int /*<<< orphan*/  ITextDocument ;
typedef  int /*<<< orphan*/  IRichEditOle ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ HRESULT ;
typedef  char CHAR ;

/* Variables and functions */
 scalar_t__ CO_E_RELEASED ; 
 int /*<<< orphan*/  EM_SETSEL ; 
 int /*<<< orphan*/  EXPECT_REF (int /*<<< orphan*/ *,int) ; 
 scalar_t__ E_INVALIDARG ; 
 scalar_t__ ITextDocument_Range (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ **) ; 
 scalar_t__ ITextFont_GetItalic (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  ITextFont_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ ITextFont_SetItalic (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ ITextRange_GetFont (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ITextRange_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ ITextRange_SetFont (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITextSelection_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ ITextSelection_SetFont (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  WM_SETTEXT ; 
 int /*<<< orphan*/  create_interfaces (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  release_interfaces (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ tomFalse ; 
 scalar_t__ tomTrue ; 

__attribute__((used)) static void test_SetFont(void)
{
  static const CHAR test_text1[] = "TestSomeText";
  IRichEditOle *reOle = NULL;
  ITextDocument *doc = NULL;
  ITextSelection *selection;
  ITextRange *range, *range2;
  ITextFont *font, *font2;
  LONG value;
  HRESULT hr;
  HWND hwnd;

  create_interfaces(&hwnd, &reOle, &doc, &selection);
  SendMessageA(hwnd, WM_SETTEXT, 0, (LPARAM)test_text1);
  SendMessageA(hwnd, EM_SETSEL, 1, 2);

  hr = ITextDocument_Range(doc, 0, 4, &range);
  ok(hr == S_OK, "got 0x%08x\n", hr);

  hr = ITextDocument_Range(doc, 5, 2, &range2);
  ok(hr == S_OK, "got 0x%08x\n", hr);

  EXPECT_REF(range, 1);
  hr = ITextRange_GetFont(range, &font);
  ok(hr == S_OK, "got 0x%08x\n", hr);
  EXPECT_REF(range, 2);

  EXPECT_REF(range2, 1);
  hr = ITextRange_GetFont(range2, &font2);
  ok(hr == S_OK, "got 0x%08x\n", hr);
  EXPECT_REF(range2, 2);

  hr = ITextRange_SetFont(range, NULL);
  ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);

  /* setting same font, no-op */
  EXPECT_REF(range, 2);
  hr = ITextRange_SetFont(range, font);
  ok(hr == S_OK, "got 0x%08x\n", hr);
  EXPECT_REF(range, 2);

  EXPECT_REF(range2, 2);
  EXPECT_REF(range, 2);
  hr = ITextRange_SetFont(range, font2);
  ok(hr == S_OK, "got 0x%08x\n", hr);
  EXPECT_REF(range2, 2);
  EXPECT_REF(range, 2);

  /* originally range 0-4 is non-italic */
  value = tomTrue;
  hr = ITextFont_GetItalic(font, &value);
  ok(hr == S_OK, "got 0x%08x\n", hr);
  ok(value == tomFalse, "got %d\n", value);

  /* set range 5-2 to italic, then set this font to range 0-4 */
  hr = ITextFont_SetItalic(font2, tomTrue);
  ok(hr == S_OK, "got 0x%08x\n", hr);

  hr = ITextRange_SetFont(range, font2);
  ok(hr == S_OK, "got 0x%08x\n", hr);

  value = tomFalse;
  hr = ITextFont_GetItalic(font, &value);
  ok(hr == S_OK, "got 0x%08x\n", hr);
  ok(value == tomTrue, "got %d\n", value);

  release_interfaces(&hwnd, &reOle, &doc, NULL);

  hr = ITextRange_SetFont(range, NULL);
  ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);

  hr = ITextRange_SetFont(range, font);
  ok(hr == CO_E_RELEASED, "got 0x%08x\n", hr);

  hr = ITextSelection_SetFont(selection, NULL);
  ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);

  hr = ITextSelection_SetFont(selection, font);
  ok(hr == CO_E_RELEASED, "got 0x%08x\n", hr);

  ITextFont_Release(font);
  ITextFont_Release(font2);
  ITextRange_Release(range);
  ITextRange_Release(range2);
  ITextSelection_Release(selection);
}