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
typedef  int /*<<< orphan*/  ITextFont ;
typedef  int /*<<< orphan*/  ITextDocument ;
typedef  int /*<<< orphan*/  IRichEditOle ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int HRESULT ;
typedef  char CHAR ;

/* Variables and functions */
 int CO_E_RELEASED ; 
 int /*<<< orphan*/  EM_SETSEL ; 
 int /*<<< orphan*/  EXPECT_REF (int /*<<< orphan*/ *,int) ; 
 int E_INVALIDARG ; 
 int E_NOINTERFACE ; 
 int /*<<< orphan*/  IID_ITextSelection ; 
 int ITextRange_GetEnd (int /*<<< orphan*/ *,int*) ; 
 int ITextRange_GetFont (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int ITextRange_GetStart (int /*<<< orphan*/ *,int*) ; 
 int ITextRange_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  ITextRange_Release (int /*<<< orphan*/ *) ; 
 int ITextSelection_GetDuplicate (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ITextSelection_Release (int /*<<< orphan*/ *) ; 
 int S_OK ; 
 int /*<<< orphan*/  SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  WM_SETTEXT ; 
 int /*<<< orphan*/  create_interfaces (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int /*<<< orphan*/  release_interfaces (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_ITextSelection_GetDuplicate(void)
{
  static const CHAR test_text1[] = "TestSomeText";
  IRichEditOle *reOle = NULL;
  ITextDocument *doc = NULL;
  ITextSelection *selection, *sel2;
  ITextRange *range, *range2;
  ITextFont *font;
  LONG value;
  HRESULT hr;
  HWND hwnd;

  create_interfaces(&hwnd, &reOle, &doc, &selection);
  SendMessageA(hwnd, WM_SETTEXT, 0, (LPARAM)test_text1);
  SendMessageA(hwnd, EM_SETSEL, 1, 2);

  hr = ITextSelection_GetDuplicate(selection, NULL);
  ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);

  EXPECT_REF(selection, 2);

  hr = ITextSelection_GetDuplicate(selection, &range);
  ok(hr == S_OK, "got 0x%08x\n", hr);

  hr = ITextSelection_GetDuplicate(selection, &range2);
  ok(hr == S_OK, "got 0x%08x\n", hr);
  ok(range != range2, "got %p, %p\n", range, range2);

  EXPECT_REF(selection, 2);
  EXPECT_REF(range, 1);
  EXPECT_REF(range2, 1);

  ITextRange_Release(range2);

  value = 0;
  hr = ITextRange_GetStart(range, &value);
  ok(hr == S_OK, "got 0x%08x\n", hr);
  ok(value == 1, "got %d\n", value);

  value = 0;
  hr = ITextRange_GetEnd(range, &value);
  ok(hr == S_OK, "got 0x%08x\n", hr);
  ok(value == 2, "got %d\n", value);

  SendMessageA(hwnd, EM_SETSEL, 2, 3);

  value = 0;
  hr = ITextRange_GetStart(range, &value);
  ok(hr == S_OK, "got 0x%08x\n", hr);
  ok(value == 1, "got %d\n", value);

  value = 0;
  hr = ITextRange_GetEnd(range, &value);
  ok(hr == S_OK, "got 0x%08x\n", hr);
  ok(value == 2, "got %d\n", value);

  hr = ITextRange_QueryInterface(range, &IID_ITextSelection, (void**)&sel2);
  ok(hr == E_NOINTERFACE, "got 0x%08x\n", hr);

  release_interfaces(&hwnd, &reOle, &doc, NULL);

  hr = ITextSelection_GetDuplicate(selection, NULL);
  ok(hr == CO_E_RELEASED, "got 0x%08x\n", hr);

  hr = ITextSelection_GetDuplicate(selection, &range);
  ok(hr == CO_E_RELEASED, "got 0x%08x\n", hr);

  hr = ITextRange_GetFont(range, &font);
  ok(hr == CO_E_RELEASED, "got 0x%08x\n", hr);

  ITextSelection_Release(selection);
  ITextRange_Release(range);
}