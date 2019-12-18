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
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  ITextRange ;
typedef  int /*<<< orphan*/  ITextPara ;
typedef  int /*<<< orphan*/  ITextDocument ;
typedef  int /*<<< orphan*/  IRichEditOle ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ HRESULT ;
typedef  char CHAR ;

/* Variables and functions */
 scalar_t__ CO_E_RELEASED ; 
 int /*<<< orphan*/  ITextDocument_Range (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ **) ; 
 scalar_t__ ITextPara_GetStyle (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITextPara_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ ITextRange_GetPara (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ITextRange_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_SETTEXT ; 
 int /*<<< orphan*/  create_interfaces (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int get_refcount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  release_interfaces (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_ITextRange_GetPara(void)
{
  HWND w;
  IRichEditOle *reOle = NULL;
  ITextDocument *txtDoc = NULL;
  ITextRange *txtRge = NULL;
  ITextPara *txtPara = NULL, *txtPara1 = NULL;
  HRESULT hres;
  int first, lim;
  int refcount;
  static const CHAR test_text1[] = "TestSomeText";
  LONG value;

  create_interfaces(&w, &reOle, &txtDoc, NULL);
  SendMessageA(w, WM_SETTEXT, 0, (LPARAM)test_text1);

  first = 4, lim = 4;
  ITextDocument_Range(txtDoc, first, lim, &txtRge);
  refcount = get_refcount((IUnknown *)txtRge);
  ok(refcount == 1, "got wrong ref count: %d\n", refcount);

  hres = ITextRange_GetPara(txtRge, &txtPara);
  ok(hres == S_OK, "ITextRange_GetPara\n");
  refcount = get_refcount((IUnknown *)txtPara);
  ok(refcount == 1, "got wrong ref count: %d\n", refcount);
  refcount = get_refcount((IUnknown *)txtRge);
  ok(refcount == 2, "got wrong ref count: %d\n", refcount);

  hres = ITextRange_GetPara(txtRge, &txtPara1);
  ok(hres == S_OK, "ITextRange_GetPara\n");
  ok(txtPara1 != txtPara, "A new pointer should be return\n");
  refcount = get_refcount((IUnknown *)txtPara1);
  ok(refcount == 1, "got wrong ref count: %d\n", refcount);
  ITextPara_Release(txtPara1);
  refcount = get_refcount((IUnknown *)txtRge);
  ok(refcount == 2, "got wrong ref count: %d\n", refcount);

  ITextRange_Release(txtRge);
  release_interfaces(&w, &reOle, &txtDoc, NULL);

  hres = ITextPara_GetStyle(txtPara, &value);
  ok(hres == CO_E_RELEASED, "ITextPara after ITextDocument destroyed\n");

  ITextPara_Release(txtPara);
}