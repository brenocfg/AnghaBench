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
 int E_INVALIDARG ; 
 int ITextDocument_Range (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 int ITextRange_GetStoryLength (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  ITextRange_Release (int /*<<< orphan*/ *) ; 
 int ITextSelection_GetStoryLength (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  ITextSelection_Release (int /*<<< orphan*/ *) ; 
 int S_OK ; 
 int /*<<< orphan*/  SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  WM_SETTEXT ; 
 int /*<<< orphan*/  create_interfaces (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  release_interfaces (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_GetStoryLength(void)
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

  hr = ITextRange_GetStoryLength(range, NULL);
  ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);

  value = 0;
  hr = ITextRange_GetStoryLength(range, &value);
  ok(hr == S_OK, "got 0x%08x\n", hr);
  ok(value == 13, "got %d\n", value);

  hr = ITextSelection_GetStoryLength(selection, NULL);
  ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);

  value = 0;
  hr = ITextSelection_GetStoryLength(selection, &value);
  ok(hr == S_OK, "got 0x%08x\n", hr);
  ok(value == 13, "got %d\n", value);

  SendMessageA(hwnd, WM_SETTEXT, 0, (LPARAM)"");

  value = 0;
  hr = ITextRange_GetStoryLength(range, &value);
  ok(hr == S_OK, "got 0x%08x\n", hr);
  ok(value == 1, "got %d\n", value);

  value = 0;
  hr = ITextSelection_GetStoryLength(selection, &value);
  ok(hr == S_OK, "got 0x%08x\n", hr);
  ok(value == 1, "got %d\n", value);

  release_interfaces(&hwnd, &reOle, &doc, NULL);

  hr = ITextRange_GetStoryLength(range, NULL);
  ok(hr == CO_E_RELEASED, "got 0x%08x\n", hr);

  value = 100;
  hr = ITextRange_GetStoryLength(range, &value);
  ok(hr == CO_E_RELEASED, "got 0x%08x\n", hr);
  ok(value == 100, "got %d\n", value);

  hr = ITextSelection_GetStoryLength(selection, NULL);
  ok(hr == CO_E_RELEASED, "got 0x%08x\n", hr);

  value = 100;
  hr = ITextSelection_GetStoryLength(selection, &value);
  ok(hr == CO_E_RELEASED, "got 0x%08x\n", hr);
  ok(value == 100, "got %d\n", value);

  ITextSelection_Release(selection);
  ITextRange_Release(range);
}