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
 scalar_t__ CO_E_RELEASED ; 
 scalar_t__ E_INVALIDARG ; 
 scalar_t__ ITextDocument_Range (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ **) ; 
 scalar_t__ ITextRange_GetDuplicate (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ ITextRange_GetEnd (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ ITextRange_GetStart (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  ITextRange_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_SETTEXT ; 
 int /*<<< orphan*/  create_interfaces (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  release_interfaces (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_ITextRange_GetDuplicate(void)
{
  HWND w;
  IRichEditOle *reOle = NULL;
  ITextDocument *txtDoc = NULL;
  ITextRange *txtRge = NULL;
  ITextRange *txtRgeDup = NULL;
  HRESULT hres;
  LONG first, lim, start, end;
  static const CHAR test_text1[] = "TestSomeText";

  create_interfaces(&w, &reOle, &txtDoc, NULL);
  SendMessageA(w, WM_SETTEXT, 0, (LPARAM)test_text1);
  first = 0, lim = 4;
  hres = ITextDocument_Range(txtDoc, first, lim, &txtRge);
  ok(hres == S_OK, "ITextDocument_Range fails 0x%x.\n", hres);

  hres = ITextRange_GetDuplicate(txtRge, &txtRgeDup);
  ok(hres == S_OK, "ITextRange_GetDuplicate\n");
  ok(txtRgeDup != txtRge, "A new pointer should be returned\n");
  hres = ITextRange_GetStart(txtRgeDup, &start);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  ok(start == first, "got wrong value: %d\n", start);
  hres = ITextRange_GetEnd(txtRgeDup, &end);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  ok(end == lim, "got wrong value: %d\n", end);

  ITextRange_Release(txtRgeDup);

  hres = ITextRange_GetDuplicate(txtRge, NULL);
  ok(hres == E_INVALIDARG, "ITextRange_GetDuplicate\n");

  release_interfaces(&w, &reOle, &txtDoc, NULL);

  hres = ITextRange_GetDuplicate(txtRge, NULL);
  ok(hres == CO_E_RELEASED, "got 0x%08x\n", hres);

  hres = ITextRange_GetDuplicate(txtRge, &txtRgeDup);
  ok(hres == CO_E_RELEASED, "got 0x%08x\n", hres);

  ITextRange_Release(txtRge);
}