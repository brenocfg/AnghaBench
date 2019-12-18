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
typedef  int /*<<< orphan*/  ITextDocument ;
typedef  int /*<<< orphan*/  IRichEditOle ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ HRESULT ;
typedef  char CHAR ;

/* Variables and functions */
 scalar_t__ CO_E_RELEASED ; 
 int /*<<< orphan*/  EM_SETSEL ; 
 scalar_t__ ITextDocument_Range (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ **) ; 
 scalar_t__ ITextRange_InRange (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  ITextRange_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ ITextSelection_InRange (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  ITextSelection_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_FALSE ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  WM_SETTEXT ; 
 int /*<<< orphan*/  create_interfaces (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  release_interfaces (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ tomFalse ; 
 scalar_t__ tomTrue ; 

__attribute__((used)) static void test_InRange(void)
{
  static const CHAR test_text1[] = "TestSomeText";
  ITextRange *range, *range2, *range3;
  IRichEditOle *reOle = NULL;
  ITextDocument *doc = NULL;
  ITextSelection *selection;
  LONG value;
  HRESULT hr;
  HWND hwnd;

  create_interfaces(&hwnd, &reOle, &doc, &selection);
  SendMessageA(hwnd, WM_SETTEXT, 0, (LPARAM)test_text1);
  SendMessageA(hwnd, EM_SETSEL, 1, 2);

  hr = ITextDocument_Range(doc, 0, 4, &range);
  ok(hr == S_OK, "got 0x%08x\n", hr);

  hr = ITextDocument_Range(doc, 0, 4, &range2);
  ok(hr == S_OK, "got 0x%08x\n", hr);

  /* matches selection */
  hr = ITextDocument_Range(doc, 1, 2, &range3);
  ok(hr == S_OK, "got 0x%08x\n", hr);

  hr = ITextRange_InRange(range, NULL, NULL);
  ok(hr == S_FALSE, "got 0x%08x\n", hr);

  value = tomTrue;
  hr = ITextRange_InRange(range, NULL, &value);
  ok(hr == S_FALSE, "got 0x%08x\n", hr);
  ok(value == tomFalse, "got %d\n", value);

  hr = ITextRange_InRange(range, range2, NULL);
  ok(hr == S_OK, "got 0x%08x\n", hr);

  value = tomFalse;
  hr = ITextRange_InRange(range, range2, &value);
  ok(hr == S_OK, "got 0x%08x\n", hr);
  ok(value == tomTrue, "got %d\n", value);

  /* selection */
  hr = ITextSelection_InRange(selection, NULL, NULL);
  ok(hr == S_FALSE, "got 0x%08x\n", hr);

  value = tomTrue;
  hr = ITextSelection_InRange(selection, NULL, &value);
  ok(hr == S_FALSE, "got 0x%08x\n", hr);
  ok(value == tomFalse, "got %d\n", value);

  hr = ITextSelection_InRange(selection, range2, NULL);
  ok(hr == S_FALSE, "got 0x%08x\n", hr);

  value = tomTrue;
  hr = ITextSelection_InRange(selection, range2, &value);
  ok(hr == S_FALSE, "got 0x%08x\n", hr);
  ok(value == tomFalse, "got %d\n", value);

  value = tomTrue;
  hr = ITextSelection_InRange(selection, range3, &value);
  ok(hr == S_FALSE, "got 0x%08x\n", hr);
  ok(value == tomFalse, "got %d\n", value);

  /* seems to work on ITextSelection ranges only */
  value = tomFalse;
  hr = ITextSelection_InRange(selection, (ITextRange*)selection, &value);
  ok(hr == S_OK, "got 0x%08x\n", hr);
  ok(value == tomTrue, "got %d\n", value);

  release_interfaces(&hwnd, &reOle, &doc, NULL);

  hr = ITextRange_InRange(range, NULL, NULL);
  ok(hr == CO_E_RELEASED, "got 0x%08x\n", hr);

  value = tomTrue;
  hr = ITextRange_InRange(range, NULL, &value);
  ok(hr == CO_E_RELEASED, "got 0x%08x\n", hr);
  ok(value == tomFalse, "got %d\n", value);

  hr = ITextRange_InRange(range, range2, NULL);
  ok(hr == CO_E_RELEASED, "got 0x%08x\n", hr);

  value = tomTrue;
  hr = ITextRange_InRange(range, range2, &value);
  ok(hr == CO_E_RELEASED, "got 0x%08x\n", hr);
  ok(value == tomFalse, "got %d\n", value);

  /* selection */
  hr = ITextSelection_InRange(selection, NULL, NULL);
  ok(hr == CO_E_RELEASED, "got 0x%08x\n", hr);

  value = tomTrue;
  hr = ITextSelection_InRange(selection, NULL, &value);
  ok(hr == CO_E_RELEASED, "got 0x%08x\n", hr);
  ok(value == tomFalse, "got %d\n", value);

  hr = ITextSelection_InRange(selection, range2, NULL);
  ok(hr == CO_E_RELEASED, "got 0x%08x\n", hr);

  value = tomTrue;
  hr = ITextSelection_InRange(selection, range2, &value);
  ok(hr == CO_E_RELEASED, "got 0x%08x\n", hr);
  ok(value == tomFalse, "got %d\n", value);

  ITextRange_Release(range);
  ITextRange_Release(range2);
  ITextRange_Release(range3);
  ITextSelection_Release(selection);
}