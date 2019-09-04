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
typedef  int /*<<< orphan*/  ITextSelection ;
typedef  int /*<<< orphan*/  ITextDocument ;
typedef  int /*<<< orphan*/  IRichEditOle ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int HRESULT ;
typedef  char CHAR ;

/* Variables and functions */
 int CO_E_RELEASED ; 
 int /*<<< orphan*/  EM_SETSEL ; 
 int ITextSelection_GetEnd (int /*<<< orphan*/ *,int*) ; 
 int ITextSelection_GetStart (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  ITextSelection_Release (int /*<<< orphan*/ *) ; 
 int ITextSelection_SetEnd (int /*<<< orphan*/ *,int) ; 
 int ITextSelection_SetStart (int /*<<< orphan*/ *,int) ; 
 int S_FALSE ; 
 int S_OK ; 
 int /*<<< orphan*/  SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  WM_SETTEXT ; 
 int /*<<< orphan*/  create_interfaces (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  release_interfaces (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_ITextSelection_GetStart_GetEnd(void)
{
  HWND w;
  IRichEditOle *reOle = NULL;
  ITextDocument *txtDoc = NULL;
  ITextSelection *txtSel = NULL;
  HRESULT hres;
  int first, lim, start, end;
  static const CHAR test_text1[] = "TestSomeText";

  create_interfaces(&w, &reOle, &txtDoc, &txtSel);
  SendMessageA(w, WM_SETTEXT, 0, (LPARAM)test_text1);

  first = 2, lim = 5;
  SendMessageA(w, EM_SETSEL, first, lim);
  start = 0xdeadbeef;
  hres = ITextSelection_GetStart(txtSel, &start);
  ok(hres == S_OK, "ITextSelection_GetStart\n");
  ok(start == 2, "got wrong start value: %d\n", start);
  end = 0xdeadbeef;
  hres = ITextSelection_GetEnd(txtSel, &end);
  ok(hres == S_OK, "ITextSelection_GetEnd\n");
  ok(end == 5, "got wrong end value: %d\n", end);

  first = 5, lim = 2;
  SendMessageA(w, EM_SETSEL, first, lim);
  start = 0xdeadbeef;
  hres = ITextSelection_GetStart(txtSel, &start);
  ok(hres == S_OK, "ITextSelection_GetStart\n");
  ok(start == 2, "got wrong start value: %d\n", start);
  end = 0xdeadbeef;
  hres = ITextSelection_GetEnd(txtSel, &end);
  ok(hres == S_OK, "ITextSelection_GetEnd\n");
  ok(end == 5, "got wrong end value: %d\n", end);

  first = 0, lim = -1;
  SendMessageA(w, EM_SETSEL, first, lim);
  start = 0xdeadbeef;
  hres = ITextSelection_GetStart(txtSel, &start);
  ok(hres == S_OK, "ITextSelection_GetStart\n");
  ok(start == 0, "got wrong start value: %d\n", start);
  end = 0xdeadbeef;
  hres = ITextSelection_GetEnd(txtSel, &end);
  ok(hres == S_OK, "ITextSelection_GetEnd\n");
  ok(end == 13, "got wrong end value: %d\n", end);

  first = 13, lim = 13;
  SendMessageA(w, EM_SETSEL, first, lim);
  start = 0xdeadbeef;
  hres = ITextSelection_GetStart(txtSel, &start);
  ok(hres == S_OK, "ITextSelection_GetStart\n");
  ok(start == 12, "got wrong start value: %d\n", start);
  end = 0xdeadbeef;
  hres = ITextSelection_GetEnd(txtSel, &end);
  ok(hres == S_OK, "ITextSelection_GetEnd\n");
  ok(end == 12, "got wrong end value: %d\n", end);

  /* SetStart/SetEnd */
  hres = ITextSelection_SetStart(txtSel, 0);
  ok(hres == S_OK, "got 0x%08x\n", hres);

  /* same value */
  hres = ITextSelection_SetStart(txtSel, 0);
  ok(hres == S_FALSE, "got 0x%08x\n", hres);

  hres = ITextSelection_SetStart(txtSel, 1);
  ok(hres == S_OK, "got 0x%08x\n", hres);

  /* negative resets to 0, return value is S_FALSE when
     position wasn't changed */
  hres = ITextSelection_SetStart(txtSel, -1);
  ok(hres == S_OK, "got 0x%08x\n", hres);

  hres = ITextSelection_SetStart(txtSel, -1);
  ok(hres == S_FALSE, "got 0x%08x\n", hres);

  hres = ITextSelection_SetStart(txtSel, 0);
  ok(hres == S_FALSE, "got 0x%08x\n", hres);

  start = -1;
  hres = ITextSelection_GetStart(txtSel, &start);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  ok(start == 0, "got %d\n", start);

  /* greater than initial end, but less than total char count */
  hres = ITextSelection_SetStart(txtSel, 1);
  ok(hres == S_OK, "got 0x%08x\n", hres);

  hres = ITextSelection_SetEnd(txtSel, 3);
  ok(hres == S_OK, "got 0x%08x\n", hres);

  hres = ITextSelection_SetStart(txtSel, 10);
  ok(hres == S_OK, "got 0x%08x\n", hres);

  start = 0;
  hres = ITextSelection_GetStart(txtSel, &start);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  ok(start == 10, "got %d\n", start);

  end = 0;
  hres = ITextSelection_GetEnd(txtSel, &end);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  ok(end == 10, "got %d\n", end);

  /* more that total text length */
  hres = ITextSelection_SetStart(txtSel, 50);
  ok(hres == S_OK, "got 0x%08x\n", hres);

  start = 0;
  hres = ITextSelection_GetStart(txtSel, &start);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  ok(start == 12, "got %d\n", start);

  end = 0;
  hres = ITextSelection_GetEnd(txtSel, &end);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  ok(end == 12, "got %d\n", end);

  /* SetEnd */
  hres = ITextSelection_SetStart(txtSel, 0);
  ok(hres == S_OK, "got 0x%08x\n", hres);

  /* same value */
  hres = ITextSelection_SetEnd(txtSel, 5);
  ok(hres == S_OK, "got 0x%08x\n", hres);

  hres = ITextSelection_SetEnd(txtSel, 5);
  ok(hres == S_FALSE, "got 0x%08x\n", hres);

  /* negative resets to 0 */
  hres = ITextSelection_SetEnd(txtSel, -1);
  ok(hres == S_OK, "got 0x%08x\n", hres);

  end = -1;
  hres = ITextSelection_GetEnd(txtSel, &end);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  ok(end == 0, "got %d\n", end);

  start = -1;
  hres = ITextSelection_GetStart(txtSel, &start);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  ok(start == 0, "got %d\n", start);

  /* greater than initial end, but less than total char count */
  hres = ITextSelection_SetStart(txtSel, 3);
  ok(hres == S_OK, "got 0x%08x\n", hres);

  hres = ITextSelection_SetEnd(txtSel, 1);
  ok(hres == S_OK, "got 0x%08x\n", hres);

  start = 0;
  hres = ITextSelection_GetStart(txtSel, &start);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  ok(start == 1, "got %d\n", start);

  end = 0;
  hres = ITextSelection_GetEnd(txtSel, &end);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  ok(end == 1, "got %d\n", end);

  /* more than total count */
  hres = ITextSelection_SetEnd(txtSel, 50);
  ok(hres == S_OK, "got 0x%08x\n", hres);

  start = 0;
  hres = ITextSelection_GetStart(txtSel, &start);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  ok(start == 1, "got %d\n", start);

  end = 0;
  hres = ITextSelection_GetEnd(txtSel, &end);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  ok(end == 13, "got %d\n", end);

  /* zero */
  hres = ITextSelection_SetEnd(txtSel, 0);
  ok(hres == S_OK, "got 0x%08x\n", hres);

  start = 0;
  hres = ITextSelection_GetStart(txtSel, &start);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  ok(start == 0, "got %d\n", start);

  end = 0;
  hres = ITextSelection_GetEnd(txtSel, &end);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  ok(end == 0, "got %d\n", end);

  release_interfaces(&w, &reOle, &txtDoc, NULL);

  /* detached selection */
  hres = ITextSelection_GetStart(txtSel, NULL);
  ok(hres == CO_E_RELEASED, "got 0x%08x\n", hres);

  hres = ITextSelection_GetStart(txtSel, &start);
  ok(hres == CO_E_RELEASED, "got 0x%08x\n", hres);

  hres = ITextSelection_GetEnd(txtSel, NULL);
  ok(hres == CO_E_RELEASED, "got 0x%08x\n", hres);

  hres = ITextSelection_GetEnd(txtSel, &end);
  ok(hres == CO_E_RELEASED, "got 0x%08x\n", hres);

  ITextSelection_Release(txtSel);
}