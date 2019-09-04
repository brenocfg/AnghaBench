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
typedef  int LONG ;
typedef  int /*<<< orphan*/  ITextSelection ;
typedef  int /*<<< orphan*/  ITextRange ;
typedef  int /*<<< orphan*/  ITextDocument ;
typedef  int /*<<< orphan*/  IRichEditOle ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int HRESULT ;
typedef  char CHAR ;

/* Variables and functions */
 int CO_E_RELEASED ; 
 int /*<<< orphan*/  EM_SETSEL ; 
 int ITextDocument_Range (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ITextRange_Release (int /*<<< orphan*/ *) ; 
 int ITextRange_Select (int /*<<< orphan*/ *) ; 
 int ITextSelection_GetStart (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  ITextSelection_Release (int /*<<< orphan*/ *) ; 
 int ITextSelection_Select (int /*<<< orphan*/ *) ; 
 int S_OK ; 
 int /*<<< orphan*/  SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  WM_SETTEXT ; 
 int /*<<< orphan*/  create_interfaces (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  release_interfaces (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_Select(void)
{
  static const CHAR test_text1[] = "TestSomeText";
  IRichEditOle *reOle = NULL;
  ITextDocument *doc = NULL;
  ITextSelection *selection;
  ITextRange *range;
  LONG value;
  HRESULT hr;
  HWND hwnd;

  create_interfaces(&hwnd, &reOle, &doc, &selection);
  SendMessageA(hwnd, WM_SETTEXT, 0, (LPARAM)test_text1);
  SendMessageA(hwnd, EM_SETSEL, 1, 2);

  hr = ITextDocument_Range(doc, 0, 4, &range);
  ok(hr == S_OK, "got 0x%08x\n", hr);

  hr = ITextRange_Select(range);
  ok(hr == S_OK, "got 0x%08x\n", hr);

  value = 1;
  hr = ITextSelection_GetStart(selection, &value);
  ok(hr == S_OK, "got 0x%08x\n", hr);
  ok(value == 0, "got %d\n", value);

  hr = ITextRange_Select(range);
  ok(hr == S_OK, "got 0x%08x\n", hr);

  hr = ITextSelection_Select(selection);
  ok(hr == S_OK, "got 0x%08x\n", hr);

  release_interfaces(&hwnd, &reOle, &doc, NULL);

  hr = ITextRange_Select(range);
  ok(hr == CO_E_RELEASED, "got 0x%08x\n", hr);

  hr = ITextSelection_Select(selection);
  ok(hr == CO_E_RELEASED, "got 0x%08x\n", hr);

  ITextRange_Release(range);
  ITextSelection_Release(selection);
}