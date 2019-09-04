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
typedef  int /*<<< orphan*/  ITextRange ;
typedef  int /*<<< orphan*/  ITextDocument ;
typedef  int /*<<< orphan*/  IRichEditOle ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ HRESULT ;
typedef  char CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  ITextDocument_Range (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ITextRange_GetEnd (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  ITextRange_GetStart (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  ITextRange_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ ITextRange_SetRange (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ S_FALSE ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_SETTEXT ; 
 int /*<<< orphan*/  create_interfaces (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  release_interfaces (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_ITextRange_SetRange(void)
{
  HWND w;
  IRichEditOle *reOle = NULL;
  ITextDocument *txtDoc = NULL;
  ITextRange *txtRge = NULL;
  HRESULT hres;
  int start, end;
  static const CHAR test_text1[] = "TestSomeText";

  create_interfaces(&w, &reOle, &txtDoc, NULL);
  SendMessageA(w, WM_SETTEXT, 0, (LPARAM)test_text1);
  ITextDocument_Range(txtDoc, 0, 0, &txtRge);

#define TEST_TXTRGE_SETRANGE(first, lim, expected_start, expected_end, expected_return) \
  hres = ITextRange_SetRange(txtRge, first, lim);                       \
  ok(hres == expected_return, "ITextRange_SetRange\n");                 \
  ITextRange_GetStart(txtRge, &start);                                  \
  ITextRange_GetEnd(txtRge, &end);                                      \
  ok(start == expected_start, "got wrong start value: %d\n", start);    \
  ok(end == expected_end, "got wrong end value: %d\n", end);

  TEST_TXTRGE_SETRANGE(2, 4, 2, 4, S_OK)
  TEST_TXTRGE_SETRANGE(2, 4, 2, 4, S_FALSE)
  TEST_TXTRGE_SETRANGE(4, 2, 2, 4, S_FALSE)
  TEST_TXTRGE_SETRANGE(14, 14, 12, 12, S_OK)
  TEST_TXTRGE_SETRANGE(15, 15, 12, 12, S_FALSE)
  TEST_TXTRGE_SETRANGE(14, 1, 1, 13, S_OK)
  TEST_TXTRGE_SETRANGE(-1, 4, 0, 4, S_OK)

  ITextRange_Release(txtRge);
  release_interfaces(&w, &reOle, &txtDoc, NULL);
}