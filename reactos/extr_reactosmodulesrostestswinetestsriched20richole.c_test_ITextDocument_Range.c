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
typedef  int LONG ;
typedef  int /*<<< orphan*/  ITextRange ;
typedef  int /*<<< orphan*/  ITextDocument ;
typedef  int /*<<< orphan*/  IRichEditOle ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  char CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  CO_E_RELEASED ; 
 int /*<<< orphan*/  EXPECT_REF (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  E_INVALIDARG ; 
 int /*<<< orphan*/  ITextDocument_Range (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ITextRange_CanEdit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITextRange_GetEnd (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  ITextRange_GetStart (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  ITextRange_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_SETTEXT ; 
 int /*<<< orphan*/  create_interfaces (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  release_interfaces (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_ITextDocument_Range(void)
{
  static const CHAR test_text1[] = "TestSomeText";
  HWND w;
  IRichEditOle *reOle = NULL;
  ITextDocument *txtDoc = NULL;
  ITextRange *txtRge, *range2;
  HRESULT hres;
  LONG value;

  create_interfaces(&w, &reOle, &txtDoc, NULL);
  hres = ITextDocument_Range(txtDoc, 0, 0, &txtRge);
  ok(hres == S_OK, "ITextDocument_Range fails 0x%x.\n", hres);
  EXPECT_REF(txtRge, 1);

  hres = ITextDocument_Range(txtDoc, 0, 0, &range2);
  ok(hres == S_OK, "ITextDocument_Range fails 0x%x.\n", hres);
  ok(range2 != txtRge, "A new pointer should be returned\n");
  ITextRange_Release(range2);

  hres = ITextDocument_Range(txtDoc, 0, 0, NULL);
  ok(hres == E_INVALIDARG, "ITextDocument_Range should fail 0x%x.\n", hres);

  SendMessageA(w, WM_SETTEXT, 0, (LPARAM)test_text1);

  hres = ITextDocument_Range(txtDoc, 8, 30, &range2);
  ok(hres == S_OK, "ITextDocument_Range fails 0x%x.\n", hres);
  hres = ITextRange_GetStart(range2, &value);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  ok(value == 8, "got %d\n", value);

  hres = ITextRange_GetEnd(range2, &value);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  ok(value == 13, "got %d\n", value);
  ITextRange_Release(range2);

  release_interfaces(&w, &reOle, &txtDoc, NULL);
  hres = ITextRange_CanEdit(txtRge, NULL);
  ok(hres == CO_E_RELEASED, "ITextRange after ITextDocument destroyed\n");
  ITextRange_Release(txtRge);
}