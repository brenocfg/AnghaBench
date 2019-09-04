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
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  ITextSelection ;
typedef  int /*<<< orphan*/  ITextRange ;
typedef  int /*<<< orphan*/  ITextPara ;
typedef  int /*<<< orphan*/  ITextDocument ;
typedef  int /*<<< orphan*/  IRichEditOle ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  char CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  CO_E_RELEASED ; 
 int /*<<< orphan*/  EXPECT_REF (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  E_INVALIDARG ; 
 int /*<<< orphan*/  ITextDocument_Range (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ITextPara_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITextRange_GetPara (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ITextRange_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITextSelection_GetPara (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ITextSelection_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_SETTEXT ; 
 int /*<<< orphan*/  create_interfaces (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  release_interfaces (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_GetPara(void)
{
  static const CHAR test_text1[] = "TestSomeText";
  IRichEditOle *reOle = NULL;
  ITextDocument *doc = NULL;
  ITextSelection *selection;
  ITextRange *range = NULL;
  ITextPara *para, *para2;
  HRESULT hr;
  HWND hwnd;

  create_interfaces(&hwnd, &reOle, &doc, &selection);
  SendMessageA(hwnd, WM_SETTEXT, 0, (LPARAM)test_text1);

  EXPECT_REF(reOle, 3);
  EXPECT_REF(doc, 3);

  hr = ITextDocument_Range(doc, 0, 4, &range);
  ok(hr == S_OK, "got 0x%08x\n", hr);

  EXPECT_REF(reOle, 3);
  EXPECT_REF(doc, 3);
  EXPECT_REF(range, 1);

  hr = ITextRange_GetPara(range, NULL);
  ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);

  hr = ITextRange_GetPara(range, &para);
  ok(hr == S_OK, "got 0x%08x\n", hr);

  EXPECT_REF(reOle, 3);
  EXPECT_REF(doc, 3);
  EXPECT_REF(range, 2);
  EXPECT_REF(para, 1);

  hr = ITextRange_GetPara(range, &para2);
  ok(hr == S_OK, "got 0x%08x\n", hr);
  ok(para != para2, "got %p, %p\n", para, para2);

  EXPECT_REF(reOle, 3);
  EXPECT_REF(doc, 3);
  EXPECT_REF(range, 3);
  EXPECT_REF(para, 1);
  EXPECT_REF(para2, 1);

  ITextPara_Release(para);
  ITextPara_Release(para2);

  EXPECT_REF(reOle, 3);
  EXPECT_REF(doc, 3);
  EXPECT_REF(selection, 2);

  hr = ITextSelection_GetPara(selection, &para);
  ok(hr == S_OK, "got 0x%08x\n", hr);

  EXPECT_REF(reOle, 3);
  EXPECT_REF(doc, 3);
  EXPECT_REF(selection, 3);
  EXPECT_REF(para, 1);

  hr = ITextSelection_GetPara(selection, &para2);
  ok(hr == S_OK, "got 0x%08x\n", hr);
  ok(para != para2, "got %p, %p\n", para, para2);

  ITextPara_Release(para);
  ITextPara_Release(para2);
  release_interfaces(&hwnd, &reOle, &doc, NULL);

  hr = ITextRange_GetPara(range, NULL);
  ok(hr == CO_E_RELEASED, "got 0x%08x\n", hr);

  hr = ITextRange_GetPara(range, &para);
  ok(hr == CO_E_RELEASED, "got 0x%08x\n", hr);

  hr = ITextSelection_GetPara(selection, NULL);
  ok(hr == CO_E_RELEASED, "got 0x%08x\n", hr);

  hr = ITextSelection_GetPara(selection, &para);
  ok(hr == CO_E_RELEASED, "got 0x%08x\n", hr);

  ITextSelection_Release(selection);
  ITextRange_Release(range);
}