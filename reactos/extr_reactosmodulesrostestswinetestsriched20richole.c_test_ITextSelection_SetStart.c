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
typedef  int WPARAM ;
typedef  int LPARAM ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  ITextSelection ;
typedef  int /*<<< orphan*/  ITextDocument ;
typedef  int /*<<< orphan*/  IRichEditOle ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ HRESULT ;
typedef  char CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  EM_GETSEL ; 
 int /*<<< orphan*/  EM_SETSEL ; 
 scalar_t__ ITextSelection_SetStart (int /*<<< orphan*/ *,int) ; 
 scalar_t__ S_FALSE ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  WM_SETTEXT ; 
 int /*<<< orphan*/  create_interfaces (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  release_interfaces (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 

__attribute__((used)) static void test_ITextSelection_SetStart(void)
{
  HWND w;
  IRichEditOle *reOle = NULL;
  ITextDocument *txtDoc = NULL;
  ITextSelection *txtSel = NULL;
  HRESULT hres;
  LONG first, lim, start, end;
  static const CHAR test_text1[] = "TestSomeText";

  create_interfaces(&w, &reOle, &txtDoc, &txtSel);
  SendMessageA(w, WM_SETTEXT, 0, (LPARAM)test_text1);

  first = 4, lim = 8;
  SendMessageA(w, EM_SETSEL, first, lim);
  hres = ITextSelection_SetStart(txtSel, first);
  ok(hres == S_FALSE, "ITextSelection_SetStart\n");

#define TEST_TXTSEL_SETSTART(cp, expected_start, expected_end)        \
  hres = ITextSelection_SetStart(txtSel, cp);                         \
  ok(hres == S_OK, "ITextSelection_SetStart\n");                      \
  SendMessageA(w, EM_GETSEL, (LPARAM)&start, (WPARAM)&end);           \
  ok(start == expected_start, "got wrong start value: %d\n", start);  \
  ok(end == expected_end, "got wrong end value: %d\n", end);

  TEST_TXTSEL_SETSTART(2, 2, 8)
  TEST_TXTSEL_SETSTART(-1, 0, 8)
  TEST_TXTSEL_SETSTART(13, 12, 12)

  release_interfaces(&w, &reOle, &txtDoc, &txtSel);
}