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
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  ITextSelection ;
typedef  int /*<<< orphan*/  ITextFont ;
typedef  int /*<<< orphan*/  ITextDocument ;
typedef  int /*<<< orphan*/  IRichEditOle ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ HRESULT ;
typedef  char CHAR ;

/* Variables and functions */
 scalar_t__ CO_E_RELEASED ; 
 int /*<<< orphan*/  EM_SETSEL ; 
 scalar_t__ ITextFont_GetOutline (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITextFont_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ ITextSelection_GetFont (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  WM_SETTEXT ; 
 int /*<<< orphan*/  create_interfaces (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int get_refcount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  release_interfaces (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 

__attribute__((used)) static void test_ITextSelection_GetFont(void)
{
  HWND w;
  IRichEditOle *reOle = NULL;
  ITextDocument *txtDoc = NULL;
  ITextSelection *txtSel = NULL;
  ITextFont *txtFont = NULL, *txtFont1 = NULL;
  HRESULT hres;
  int first, lim;
  int refcount;
  static const CHAR test_text1[] = "TestSomeText";
  LONG value;

  create_interfaces(&w, &reOle, &txtDoc, &txtSel);
  SendMessageA(w, WM_SETTEXT, 0, (LPARAM)test_text1);

  first = 4, lim = 4;
  SendMessageA(w, EM_SETSEL, first, lim);
  refcount = get_refcount((IUnknown *)txtSel);
  ok(refcount == 2, "got wrong ref count: %d\n", refcount);

  hres = ITextSelection_GetFont(txtSel, &txtFont);
  ok(hres == S_OK, "ITextSelection_GetFont\n");
  refcount = get_refcount((IUnknown *)txtFont);
  ok(refcount == 1, "got wrong ref count: %d\n", refcount);
  refcount = get_refcount((IUnknown *)txtSel);
  ok(refcount == 3, "got wrong ref count: %d\n", refcount);

  hres = ITextSelection_GetFont(txtSel, &txtFont1);
  ok(hres == S_OK, "ITextSelection_GetFont\n");
  ok(txtFont1 != txtFont, "A new pointer should be return\n");
  refcount = get_refcount((IUnknown *)txtFont1);
  ok(refcount == 1, "got wrong ref count: %d\n", refcount);
  ITextFont_Release(txtFont1);
  refcount = get_refcount((IUnknown *)txtSel);
  ok(refcount == 3, "got wrong ref count: %d\n", refcount);

  release_interfaces(&w, &reOle, &txtDoc, &txtSel);

  hres = ITextFont_GetOutline(txtFont, &value);
  ok(hres == CO_E_RELEASED, "ITextFont after ITextDocument destroyed\n");

  ITextFont_Release(txtFont);
}