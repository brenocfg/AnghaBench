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
typedef  char LONG ;
typedef  int /*<<< orphan*/  ITextSelection ;
typedef  int /*<<< orphan*/  ITextDocument ;
typedef  int /*<<< orphan*/  IRichEditOle ;
typedef  int /*<<< orphan*/  HWND ;
typedef  char HRESULT ;
typedef  char CHAR ;

/* Variables and functions */
 char CO_E_RELEASED ; 
 int /*<<< orphan*/  EM_SETSEL ; 
 char E_INVALIDARG ; 
 char ITextSelection_GetChar (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ITextSelection_Release (int /*<<< orphan*/ *) ; 
 char S_OK ; 
 int /*<<< orphan*/  SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  WM_SETTEXT ; 
 int /*<<< orphan*/  create_interfaces (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  release_interfaces (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_ITextSelection_GetChar(void)
{
  HWND w;
  IRichEditOle *reOle = NULL;
  ITextDocument *txtDoc = NULL;
  ITextSelection *txtSel = NULL;
  HRESULT hres;
  LONG pch;
  int first, lim;
  static const CHAR test_text1[] = "TestSomeText";

  create_interfaces(&w, &reOle, &txtDoc, &txtSel);
  SendMessageA(w, WM_SETTEXT, 0, (LPARAM)test_text1);

  first = 0, lim = 4;
  SendMessageA(w, EM_SETSEL, first, lim);
  pch = 0xdeadbeef;
  hres = ITextSelection_GetChar(txtSel, &pch);
  ok(hres == S_OK, "ITextSelection_GetChar\n");
  ok(pch == 'T', "got wrong char: %c\n", pch);

  first = 0, lim = 0;
  SendMessageA(w, EM_SETSEL, first, lim);
  pch = 0xdeadbeef;
  hres = ITextSelection_GetChar(txtSel, &pch);
  ok(hres == S_OK, "ITextSelection_GetChar\n");
  ok(pch == 'T', "got wrong char: %c\n", pch);

  first = 12, lim = 12;
  SendMessageA(w, EM_SETSEL, first, lim);
  pch = 0xdeadbeef;
  hres = ITextSelection_GetChar(txtSel, &pch);
  ok(hres == S_OK, "ITextSelection_GetChar\n");
  ok(pch == '\r', "got wrong char: %c\n", pch);

  first = 13, lim = 13;
  SendMessageA(w, EM_SETSEL, first, lim);
  pch = 0xdeadbeef;
  hres = ITextSelection_GetChar(txtSel, &pch);
  ok(hres == S_OK, "ITextSelection_GetChar\n");
  ok(pch == '\r', "got wrong char: %c\n", pch);

  hres = ITextSelection_GetChar(txtSel, NULL);
  ok(hres == E_INVALIDARG, "ITextSelection_GetChar\n");

  release_interfaces(&w, &reOle, &txtDoc, NULL);

  hres = ITextSelection_GetChar(txtSel, NULL);
  ok(hres == CO_E_RELEASED, "got 0x%08x\n", hres);

  hres = ITextSelection_GetChar(txtSel, &pch);
  ok(hres == CO_E_RELEASED, "got 0x%08x\n", hres);

  ITextSelection_Release(txtSel);
}