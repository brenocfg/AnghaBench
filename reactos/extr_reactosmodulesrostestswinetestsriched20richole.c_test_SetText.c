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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  ITextRange ;
typedef  int /*<<< orphan*/  ITextDocument ;
typedef  int /*<<< orphan*/  IRichEditOle ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int HRESULT ;
typedef  char CHAR ;
typedef  int /*<<< orphan*/ * BSTR ;

/* Variables and functions */
 int CO_E_RELEASED ; 
 int ITextDocument_Range (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 int ITextRange_GetEnd (int /*<<< orphan*/ *,int*) ; 
 int ITextRange_GetStart (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  ITextRange_Release (int /*<<< orphan*/ *) ; 
 int ITextRange_SetText (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int S_OK ; 
 int /*<<< orphan*/  SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SysAllocString (char const*) ; 
 int /*<<< orphan*/ * SysAllocStringLen (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WM_SETTEXT ; 
 int /*<<< orphan*/  create_interfaces (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  release_interfaces (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_SetText(void)
{
  static const CHAR test_text1[] = "TestSomeText";
  static const WCHAR textW[] = {'a','b','c','d','e','f','g','h','i',0};
  IRichEditOle *reOle = NULL;
  ITextDocument *doc = NULL;
  ITextRange *range, *range2;
  LONG value;
  HRESULT hr;
  HWND hwnd;
  BSTR str;

  create_interfaces(&hwnd, &reOle, &doc, NULL);
  SendMessageA(hwnd, WM_SETTEXT, 0, (LPARAM)test_text1);

  hr = ITextDocument_Range(doc, 0, 4, &range);
  ok(hr == S_OK, "got 0x%08x\n", hr);

  hr = ITextDocument_Range(doc, 0, 4, &range2);
  ok(hr == S_OK, "got 0x%08x\n", hr);

  value = 1;
  hr = ITextRange_GetStart(range2, &value);
  ok(hr == S_OK, "got 0x%08x\n", hr);
  ok(value == 0, "got %d\n", value);

  value = 0;
  hr = ITextRange_GetEnd(range2, &value);
  ok(hr == S_OK, "got 0x%08x\n", hr);
  ok(value == 4, "got %d\n", value);

  hr = ITextRange_SetText(range, NULL);
  ok(hr == S_OK, "got 0x%08x\n", hr);

  value = 1;
  hr = ITextRange_GetEnd(range2, &value);
  ok(hr == S_OK, "got 0x%08x\n", hr);
  ok(value == 0, "got %d\n", value);

  str = SysAllocString(textW);
  hr = ITextRange_SetText(range, str);
  ok(hr == S_OK, "got 0x%08x\n", hr);
  SysFreeString(str);

  value = 1;
  hr = ITextRange_GetStart(range, &value);
  ok(hr == S_OK, "got 0x%08x\n", hr);
  ok(value == 0, "got %d\n", value);

  value = 0;
  hr = ITextRange_GetEnd(range, &value);
  ok(hr == S_OK, "got 0x%08x\n", hr);
  ok(value == 9, "got %d\n", value);

  value = 1;
  hr = ITextRange_GetStart(range2, &value);
  ok(hr == S_OK, "got 0x%08x\n", hr);
  ok(value == 0, "got %d\n", value);

  value = 0;
  hr = ITextRange_GetEnd(range2, &value);
  ok(hr == S_OK, "got 0x%08x\n", hr);
  ok(value == 0, "got %d\n", value);

  str = SysAllocStringLen(NULL, 0);
  hr = ITextRange_SetText(range, str);
  ok(hr == S_OK, "got 0x%08x\n", hr);
  value = 1;
  hr = ITextRange_GetEnd(range, &value);
  ok(hr == S_OK, "got 0x%08x\n", hr);
  ok(value == 0, "got %d\n", value);
  SysFreeString(str);

  ITextRange_Release(range2);
  release_interfaces(&hwnd, &reOle, &doc, NULL);

  hr = ITextRange_SetText(range, NULL);
  ok(hr == CO_E_RELEASED, "got 0x%08x\n", hr);

  str = SysAllocStringLen(NULL, 0);
  hr = ITextRange_SetText(range, str);
  ok(hr == CO_E_RELEASED, "got 0x%08x\n", hr);
  SysFreeString(str);

  ITextRange_Release(range);
}