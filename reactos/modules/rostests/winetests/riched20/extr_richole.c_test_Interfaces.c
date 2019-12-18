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
typedef  int ULONG ;
typedef  int LRESULT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  ITextSelection ;
typedef  int /*<<< orphan*/  ITextDocument ;
typedef  int /*<<< orphan*/  IRichEditOle ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ CO_E_RELEASED ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EM_GETOLEINTERFACE ; 
 int /*<<< orphan*/  EXPECT_REF (int /*<<< orphan*/ *,int) ; 
 scalar_t__ E_INVALIDARG ; 
 scalar_t__ E_NOINTERFACE ; 
 int /*<<< orphan*/  IID_IDispatch ; 
 int /*<<< orphan*/  IID_IOleClientSite ; 
 int /*<<< orphan*/  IID_IOleInPlaceSite ; 
 int /*<<< orphan*/  IID_IOleWindow ; 
 int /*<<< orphan*/  IID_ITextDocument ; 
 int /*<<< orphan*/  IID_ITextRange ; 
 int /*<<< orphan*/  IID_ITextSelection ; 
 scalar_t__ IRichEditOle_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int IRichEditOle_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ ITextDocument_GetSelection (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ITextDocument_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ ITextSelection_CanEdit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ITextSelection_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  ITextSelection_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  new_richedit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void test_Interfaces(void)
{
  IRichEditOle *reOle = NULL, *reOle1 = NULL;
  ITextDocument *txtDoc = NULL;
  ITextSelection *txtSel = NULL, *txtSel2;
  IUnknown *punk;
  HRESULT hres;
  LRESULT res;
  HWND w;
  ULONG refcount;

  w = new_richedit(NULL);
  if (!w) {
    skip("Couldn't create window\n");
    return;
  }

  res = SendMessageA(w, EM_GETOLEINTERFACE, 0, (LPARAM)&reOle);
  ok(res, "SendMessage\n");
  ok(reOle != NULL, "EM_GETOLEINTERFACE\n");
  EXPECT_REF(reOle, 2);

  res = SendMessageA(w, EM_GETOLEINTERFACE, 0, (LPARAM)&reOle1);
  ok(res == 1, "SendMessage\n");
  ok(reOle1 == reOle, "Should not return a new IRichEditOle interface\n");
  EXPECT_REF(reOle, 3);

  hres = IRichEditOle_QueryInterface(reOle, &IID_ITextDocument,
                                 (void **) &txtDoc);
  ok(hres == S_OK, "IRichEditOle_QueryInterface\n");
  ok(txtDoc != NULL, "IRichEditOle_QueryInterface\n");

  hres = ITextDocument_GetSelection(txtDoc, NULL);
  ok(hres == E_INVALIDARG, "ITextDocument_GetSelection: 0x%x\n", hres);

  EXPECT_REF(txtDoc, 4);

  hres = ITextDocument_GetSelection(txtDoc, &txtSel);
  ok(hres == S_OK, "got 0x%08x\n", hres);

  EXPECT_REF(txtDoc, 4);
  EXPECT_REF(txtSel, 2);

  hres = ITextDocument_GetSelection(txtDoc, &txtSel2);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  ok(txtSel2 == txtSel, "got %p, %p\n", txtSel, txtSel2);

  EXPECT_REF(txtDoc, 4);
  EXPECT_REF(txtSel, 3);

  ITextSelection_Release(txtSel2);

  punk = NULL;
  hres = ITextSelection_QueryInterface(txtSel, &IID_ITextSelection, (void **) &punk);
  ok(hres == S_OK, "ITextSelection_QueryInterface\n");
  ok(punk != NULL, "ITextSelection_QueryInterface\n");
  IUnknown_Release(punk);

  punk = NULL;
  hres = ITextSelection_QueryInterface(txtSel, &IID_ITextRange, (void **) &punk);
  ok(hres == S_OK, "ITextSelection_QueryInterface\n");
  ok(punk != NULL, "ITextSelection_QueryInterface\n");
  IUnknown_Release(punk);

  punk = NULL;
  hres = ITextSelection_QueryInterface(txtSel, &IID_IDispatch, (void **) &punk);
  ok(hres == S_OK, "ITextSelection_QueryInterface\n");
  ok(punk != NULL, "ITextSelection_QueryInterface\n");
  IUnknown_Release(punk);

  punk = NULL;
  hres = IRichEditOle_QueryInterface(reOle, &IID_IOleClientSite, (void **) &punk);
  ok(hres == E_NOINTERFACE, "IRichEditOle_QueryInterface\n");

  punk = NULL;
  hres = IRichEditOle_QueryInterface(reOle, &IID_IOleWindow, (void **) &punk);
  ok(hres == E_NOINTERFACE, "IRichEditOle_QueryInterface\n");

  punk = NULL;
  hres = IRichEditOle_QueryInterface(reOle, &IID_IOleInPlaceSite, (void **) &punk);
  ok(hres == E_NOINTERFACE, "IRichEditOle_QueryInterface\n");

  ITextDocument_Release(txtDoc);
  IRichEditOle_Release(reOle);
  refcount = IRichEditOle_Release(reOle);
  ok(refcount == 1, "got wrong ref count: %d\n", refcount);
  DestroyWindow(w);

  /* Methods should return CO_E_RELEASED if the backing document has
     been released.  One test should suffice.  */
  hres = ITextSelection_CanEdit(txtSel, NULL);
  ok(hres == CO_E_RELEASED, "ITextSelection after ITextDocument destroyed\n");

  ITextSelection_Release(txtSel);
}