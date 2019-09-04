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
typedef  scalar_t__ HRESULT ;
typedef  char CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  ITextDocument_Range (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ITextRange_GetEnd (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  ITextRange_GetStart (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  ITextRange_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ ITextRange_SetEnd (int /*<<< orphan*/ *,int) ; 
 scalar_t__ S_FALSE ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_SETTEXT ; 
 int /*<<< orphan*/  create_interfaces (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  release_interfaces (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_ITextRange_SetEnd(void)
{
  HWND w;
  IRichEditOle *reOle = NULL;
  ITextDocument *txtDoc = NULL;
  ITextRange *txtRge = NULL;
  HRESULT hres;
  LONG first, lim, start, end;
  static const CHAR test_text1[] = "TestSomeText";

  create_interfaces(&w, &reOle, &txtDoc, NULL);
  SendMessageA(w, WM_SETTEXT, 0, (LPARAM)test_text1);

  first = 4, lim = 8;
  ITextDocument_Range(txtDoc, first, lim, &txtRge);
  hres = ITextRange_SetEnd(txtRge, lim);
  ok(hres == S_FALSE, "ITextRange_SetEnd\n");

#define TEST_TXTRGE_SETEND(cp, expected_start, expected_end)    \
  hres = ITextRange_SetEnd(txtRge, cp);                         \
  ok(hres == S_OK, "ITextRange_SetEnd\n");                      \
  ITextRange_GetStart(txtRge, &start);                          \
  ITextRange_GetEnd(txtRge, &end);                              \
  ok(start == expected_start, "got wrong start value: %d\n", start);  \
  ok(end == expected_end, "got wrong end value: %d\n", end);

  TEST_TXTRGE_SETEND(6, 4, 6)
  TEST_TXTRGE_SETEND(14, 4, 13)
  TEST_TXTRGE_SETEND(-1, 0, 0)

  ITextRange_Release(txtRge);
  release_interfaces(&w, &reOle, &txtDoc, NULL);
}