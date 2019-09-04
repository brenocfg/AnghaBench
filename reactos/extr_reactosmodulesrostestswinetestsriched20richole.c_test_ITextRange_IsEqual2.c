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
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  ITextRange ;
typedef  int /*<<< orphan*/  ITextDocument ;
typedef  int /*<<< orphan*/  IRichEditOle ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ HRESULT ;
typedef  char CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  ITextDocument_Range (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ **) ; 
 scalar_t__ ITextRange_IsEqual (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  ITextRange_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITextRange_SetRange (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ S_FALSE ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_SETTEXT ; 
 int /*<<< orphan*/  create_interfaces (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  release_interfaces (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ tomFalse ; 
 scalar_t__ tomTrue ; 

__attribute__((used)) static void test_ITextRange_IsEqual2(void)
{
  HWND w;
  IRichEditOle *reOle = NULL;
  ITextDocument *txtDoc = NULL;
  ITextRange *txtRge1 = NULL, *txtRge2 = NULL;
  HRESULT hres;
  static const CHAR test_text1[] = "TestSomeText";
  LONG res;

  create_interfaces(&w, &reOle, &txtDoc, NULL);
  SendMessageA(w, WM_SETTEXT, 0, (LPARAM)test_text1);
  ITextDocument_Range(txtDoc, 2, 4, &txtRge1);
  ITextDocument_Range(txtDoc, 2, 4, &txtRge2);

#define TEST_TXTRGE_ISEQUAL(expected_hres, expected_res)                \
  hres = ITextRange_IsEqual(txtRge1, txtRge2, &res);                    \
  ok(hres == expected_hres, "ITextRange_IsEqual\n");                    \
  ok(res == expected_res, "got wrong return value: %d\n", res);

  TEST_TXTRGE_ISEQUAL(S_OK, tomTrue)
  ITextRange_SetRange(txtRge2, 1, 2);
  TEST_TXTRGE_ISEQUAL(S_FALSE, tomFalse)

  ITextRange_SetRange(txtRge1, 1, 1);
  ITextRange_SetRange(txtRge2, 2, 2);
  TEST_TXTRGE_ISEQUAL(S_FALSE, tomFalse)

  ITextRange_SetRange(txtRge2, 1, 1);
  TEST_TXTRGE_ISEQUAL(S_OK, tomTrue)

  hres = ITextRange_IsEqual(txtRge1, txtRge1, &res);
  ok(hres == S_OK, "ITextRange_IsEqual\n");
  ok(res == tomTrue, "got wrong return value: %d\n", res);

  hres = ITextRange_IsEqual(txtRge1, txtRge2, NULL);
  ok(hres == S_OK, "ITextRange_IsEqual\n");

  hres = ITextRange_IsEqual(txtRge1, NULL, NULL);
  ok(hres == S_FALSE, "ITextRange_IsEqual\n");

  ITextRange_Release(txtRge1);
  ITextRange_Release(txtRge2);
  release_interfaces(&w, &reOle, &txtDoc, NULL);
}