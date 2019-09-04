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
typedef  int HRESULT ;
typedef  char CHAR ;

/* Variables and functions */
 int CO_E_RELEASED ; 
 int ITextDocument_Range (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ **) ; 
 int ITextRange_GetEnd (int /*<<< orphan*/ *,int*) ; 
 int ITextRange_GetStart (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  ITextRange_Release (int /*<<< orphan*/ *) ; 
 int ITextRange_SetEnd (int /*<<< orphan*/ *,int) ; 
 int ITextRange_SetStart (int /*<<< orphan*/ *,int) ; 
 int S_FALSE ; 
 int S_OK ; 
 int /*<<< orphan*/  SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_SETTEXT ; 
 int /*<<< orphan*/  create_interfaces (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  release_interfaces (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_ITextRange_GetStart_GetEnd(void)
{
  HWND w;
  IRichEditOle *reOle = NULL;
  ITextDocument *txtDoc = NULL;
  ITextRange *txtRge = NULL;
  HRESULT hres;
  int first, lim, start, end;
  static const CHAR test_text1[] = "TestSomeText";

  create_interfaces(&w, &reOle, &txtDoc, NULL);
  SendMessageA(w, WM_SETTEXT, 0, (LPARAM)test_text1);

  first = 1, lim = 6;
  hres = ITextDocument_Range(txtDoc, first, lim, &txtRge);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  start = 0xdeadbeef;
  hres = ITextRange_GetStart(txtRge, &start);
  ok(hres == S_OK, "ITextRange_GetStart\n");
  ok(start == 1, "got wrong start value: %d\n", start);
  end = 0xdeadbeef;
  hres = ITextRange_GetEnd(txtRge, &end);
  ok(hres == S_OK, "ITextRange_GetEnd\n");
  ok(end == 6, "got wrong end value: %d\n", end);
  ITextRange_Release(txtRge);

  first = 6, lim = 1;
  hres = ITextDocument_Range(txtDoc, first, lim, &txtRge);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  start = 0xdeadbeef;
  hres = ITextRange_GetStart(txtRge, &start);
  ok(hres == S_OK, "ITextRange_GetStart\n");
  ok(start == 1, "got wrong start value: %d\n", start);
  end = 0xdeadbeef;
  hres = ITextRange_GetEnd(txtRge, &end);
  ok(hres == S_OK, "ITextRange_GetEnd\n");
  ok(end == 6, "got wrong end value: %d\n", end);
  ITextRange_Release(txtRge);

  first = -1, lim = 13;
  hres = ITextDocument_Range(txtDoc, first, lim, &txtRge);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  start = 0xdeadbeef;
  hres = ITextRange_GetStart(txtRge, &start);
  ok(hres == S_OK, "ITextRange_GetStart\n");
  ok(start == 0, "got wrong start value: %d\n", start);
  end = 0xdeadbeef;
  hres = ITextRange_GetEnd(txtRge, &end);
  ok(hres == S_OK, "ITextRange_GetEnd\n");
  ok(end == 13, "got wrong end value: %d\n", end);
  ITextRange_Release(txtRge);

  first = 13, lim = 13;
  hres = ITextDocument_Range(txtDoc, first, lim, &txtRge);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  start = 0xdeadbeef;
  hres = ITextRange_GetStart(txtRge, &start);
  ok(hres == S_OK, "ITextRange_GetStart\n");
  ok(start == 12, "got wrong start value: %d\n", start);
  end = 0xdeadbeef;
  hres = ITextRange_GetEnd(txtRge, &end);
  ok(hres == S_OK, "ITextRange_GetEnd\n");
  ok(end == 12, "got wrong end value: %d\n", end);

  /* SetStart */
  hres = ITextRange_SetStart(txtRge, 0);
  ok(hres == S_OK, "got 0x%08x\n", hres);

  /* same value */
  hres = ITextRange_SetStart(txtRge, 0);
  ok(hres == S_FALSE, "got 0x%08x\n", hres);

  hres = ITextRange_SetStart(txtRge, 1);
  ok(hres == S_OK, "got 0x%08x\n", hres);

  /* negative resets to 0, return value is S_FALSE when
     position wasn't changed */
  hres = ITextRange_SetStart(txtRge, -1);
  ok(hres == S_OK, "got 0x%08x\n", hres);

  hres = ITextRange_SetStart(txtRge, -1);
  ok(hres == S_FALSE, "got 0x%08x\n", hres);

  hres = ITextRange_SetStart(txtRge, 0);
  ok(hres == S_FALSE, "got 0x%08x\n", hres);

  start = -1;
  hres = ITextRange_GetStart(txtRge, &start);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  ok(start == 0, "got %d\n", start);

  /* greater than initial end, but less than total char count */
  hres = ITextRange_SetStart(txtRge, 1);
  ok(hres == S_OK, "got 0x%08x\n", hres);

  hres = ITextRange_SetEnd(txtRge, 3);
  ok(hres == S_OK, "got 0x%08x\n", hres);

  hres = ITextRange_SetStart(txtRge, 10);
  ok(hres == S_OK, "got 0x%08x\n", hres);

  start = 0;
  hres = ITextRange_GetStart(txtRge, &start);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  ok(start == 10, "got %d\n", start);

  end = 0;
  hres = ITextRange_GetEnd(txtRge, &end);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  ok(end == 10, "got %d\n", end);

  /* more that total text length */
  hres = ITextRange_SetStart(txtRge, 50);
  ok(hres == S_OK, "got 0x%08x\n", hres);

  start = 0;
  hres = ITextRange_GetStart(txtRge, &start);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  ok(start == 12, "got %d\n", start);

  end = 0;
  hres = ITextRange_GetEnd(txtRge, &end);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  ok(end == 12, "got %d\n", end);

  /* SetEnd */
  hres = ITextRange_SetStart(txtRge, 0);
  ok(hres == S_OK, "got 0x%08x\n", hres);

  /* same value */
  hres = ITextRange_SetEnd(txtRge, 5);
  ok(hres == S_OK, "got 0x%08x\n", hres);

  hres = ITextRange_SetEnd(txtRge, 5);
  ok(hres == S_FALSE, "got 0x%08x\n", hres);

  /* negative resets to 0 */
  hres = ITextRange_SetEnd(txtRge, -1);
  ok(hres == S_OK, "got 0x%08x\n", hres);

  end = -1;
  hres = ITextRange_GetEnd(txtRge, &end);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  ok(end == 0, "got %d\n", end);

  start = -1;
  hres = ITextRange_GetStart(txtRge, &start);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  ok(start == 0, "got %d\n", start);

  /* greater than initial end, but less than total char count */
  hres = ITextRange_SetStart(txtRge, 3);
  ok(hres == S_OK, "got 0x%08x\n", hres);

  hres = ITextRange_SetEnd(txtRge, 1);
  ok(hres == S_OK, "got 0x%08x\n", hres);

  start = 0;
  hres = ITextRange_GetStart(txtRge, &start);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  ok(start == 1, "got %d\n", start);

  end = 0;
  hres = ITextRange_GetEnd(txtRge, &end);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  ok(end == 1, "got %d\n", end);

  /* more than total count */
  hres = ITextRange_SetEnd(txtRge, 50);
  ok(hres == S_OK, "got 0x%08x\n", hres);

  start = 0;
  hres = ITextRange_GetStart(txtRge, &start);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  ok(start == 1, "got %d\n", start);

  end = 0;
  hres = ITextRange_GetEnd(txtRge, &end);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  ok(end == 13, "got %d\n", end);

  /* zero */
  hres = ITextRange_SetEnd(txtRge, 0);
  ok(hres == S_OK, "got 0x%08x\n", hres);

  start = 0;
  hres = ITextRange_GetStart(txtRge, &start);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  ok(start == 0, "got %d\n", start);

  end = 0;
  hres = ITextRange_GetEnd(txtRge, &end);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  ok(end == 0, "got %d\n", end);

  release_interfaces(&w, &reOle, &txtDoc, NULL);

  /* detached range */
  hres = ITextRange_SetStart(txtRge, 0);
  ok(hres == CO_E_RELEASED, "got 0x%08x\n", hres);

  hres = ITextRange_SetEnd(txtRge, 3);
  ok(hres == CO_E_RELEASED, "got 0x%08x\n", hres);

  hres = ITextRange_GetStart(txtRge, &start);
  ok(hres == CO_E_RELEASED, "got 0x%08x\n", hres);

  hres = ITextRange_GetStart(txtRge, NULL);
  ok(hres == CO_E_RELEASED, "got 0x%08x\n", hres);

  hres = ITextRange_GetEnd(txtRge, &end);
  ok(hres == CO_E_RELEASED, "got 0x%08x\n", hres);

  hres = ITextRange_GetEnd(txtRge, NULL);
  ok(hres == CO_E_RELEASED, "got 0x%08x\n", hres);

  ITextRange_Release(txtRge);
}