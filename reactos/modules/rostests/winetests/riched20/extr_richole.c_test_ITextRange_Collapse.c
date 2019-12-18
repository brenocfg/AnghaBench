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
typedef  int HRESULT ;
typedef  char CHAR ;

/* Variables and functions */
 int CO_E_RELEASED ; 
 int ITextDocument_Range (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ **) ; 
 int ITextRange_Collapse (int /*<<< orphan*/ *,int) ; 
 int ITextRange_GetEnd (int /*<<< orphan*/ *,int*) ; 
 int ITextRange_GetStart (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  ITextRange_Release (int /*<<< orphan*/ *) ; 
 int S_FALSE ; 
 int S_OK ; 
 int /*<<< orphan*/  SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_SETTEXT ; 
 int /*<<< orphan*/  create_interfaces (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  release_interfaces (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int tomEnd ; 
 int tomFalse ; 
 int tomStart ; 
 int tomTrue ; 
 int tomUndefined ; 

__attribute__((used)) static void test_ITextRange_Collapse(void)
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
  hres = ITextDocument_Range(txtDoc, first, lim, &txtRge);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  hres = ITextRange_Collapse(txtRge, tomTrue);
  ok(hres == S_OK, "ITextRange_Collapse\n");
  hres = ITextRange_GetStart(txtRge, &start);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  ok(start == 4, "got wrong start value: %d\n", start);
  hres = ITextRange_GetEnd(txtRge, &end);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  ok(end == 4, "got wrong end value: %d\n", end);
  ITextRange_Release(txtRge);

  hres = ITextDocument_Range(txtDoc, first, lim, &txtRge);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  hres = ITextRange_Collapse(txtRge, tomStart);
  ok(hres == S_OK, "ITextRange_Collapse\n");
  hres = ITextRange_GetStart(txtRge, &start);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  ok(start == 4, "got wrong start value: %d\n", start);
  hres = ITextRange_GetEnd(txtRge, &end);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  ok(end == 4, "got wrong end value: %d\n", end);
  ITextRange_Release(txtRge);

  hres = ITextDocument_Range(txtDoc, first, lim, &txtRge);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  hres = ITextRange_Collapse(txtRge, tomFalse);
  ok(hres == S_OK, "ITextRange_Collapse\n");
  hres = ITextRange_GetStart(txtRge, &start);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  ok(start == 8, "got wrong start value: %d\n", start);
  hres = ITextRange_GetEnd(txtRge, &end);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  ok(end == 8, "got wrong end value: %d\n", end);
  ITextRange_Release(txtRge);

  hres = ITextDocument_Range(txtDoc, first, lim, &txtRge);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  hres = ITextRange_Collapse(txtRge, tomEnd);
  ok(hres == S_OK, "ITextRange_Collapse\n");
  hres = ITextRange_GetStart(txtRge, &start);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  ok(start == 8, "got wrong start value: %d\n", start);
  hres = ITextRange_GetEnd(txtRge, &end);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  ok(end == 8, "got wrong end value: %d\n", end);
  ITextRange_Release(txtRge);

  /* tomStart is the default */
  hres = ITextDocument_Range(txtDoc, first, lim, &txtRge);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  hres = ITextRange_Collapse(txtRge, 256);
  ok(hres == S_OK, "ITextRange_Collapse\n");
  hres = ITextRange_GetStart(txtRge, &start);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  ok(start == 4, "got wrong start value: %d\n", start);
  hres = ITextRange_GetEnd(txtRge, &end);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  ok(end == 4, "got wrong end value: %d\n", end);
  ITextRange_Release(txtRge);

  first = 6, lim = 6;
  hres = ITextDocument_Range(txtDoc, first, lim, &txtRge);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  hres = ITextRange_Collapse(txtRge, tomEnd);
  ok(hres == S_FALSE, "ITextRange_Collapse\n");
  hres = ITextRange_GetStart(txtRge, &start);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  ok(start == 6, "got wrong start value: %d\n", start);
  hres = ITextRange_GetEnd(txtRge, &end);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  ok(end == 6, "got wrong end value: %d\n", end);
  ITextRange_Release(txtRge);

  first = 8, lim = 8;
  hres = ITextDocument_Range(txtDoc, first, lim, &txtRge);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  hres = ITextRange_Collapse(txtRge, tomStart);
  ok(hres == S_FALSE, "ITextRange_Collapse\n");
  hres = ITextRange_GetStart(txtRge, &start);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  ok(start == 8, "got wrong start value: %d\n", start);
  hres = ITextRange_GetEnd(txtRge, &end);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  ok(end == 8, "got wrong end value: %d\n", end);

  release_interfaces(&w, &reOle, &txtDoc, NULL);

  hres = ITextRange_Collapse(txtRge, tomStart);
  ok(hres == CO_E_RELEASED, "got 0x%08x\n", hres);

  hres = ITextRange_Collapse(txtRge, tomUndefined);
  ok(hres == CO_E_RELEASED, "got 0x%08x\n", hres);

  ITextRange_Release(txtRge);
}