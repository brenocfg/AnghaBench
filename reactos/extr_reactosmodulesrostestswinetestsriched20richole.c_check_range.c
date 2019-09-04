#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int cbSize; int fMask; int /*<<< orphan*/  nMax; int /*<<< orphan*/  nMin; int /*<<< orphan*/  nPos; } ;
typedef  TYPE_1__ SCROLLINFO ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  ITextRange ;
typedef  int /*<<< orphan*/  ITextDocument ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  GetScrollInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ ITextDocument_Range (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ **) ; 
 scalar_t__ ITextRange_ScrollIntoView (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SB_VERT ; 
 int SIF_POS ; 
 int SIF_RANGE ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,...) ; 

__attribute__((used)) static void check_range(HWND w, ITextDocument* doc, int first, int lim,
                        LONG bStart, int expected_nonzero)
{
  SCROLLINFO si;
  ITextRange *txtRge = NULL;
  HRESULT hres;

  si.cbSize = sizeof(SCROLLINFO);
  si.fMask = SIF_POS | SIF_RANGE;

  hres = ITextDocument_Range(doc, first, lim, &txtRge);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  hres = ITextRange_ScrollIntoView(txtRge, bStart);
  ok(hres == S_OK, "got 0x%08x\n", hres);
  GetScrollInfo(w, SB_VERT, &si);
  if (expected_nonzero) {
    ok(si.nPos != 0,
       "Scrollbar at 0, should be >0. (TextRange %d-%d, scroll range %d-%d.)\n",
       first, lim, si.nMin, si.nMax);
  } else {
    ok(si.nPos == 0,
       "Scrollbar at %d, should be 0. (TextRange %d-%d, scroll range %d-%d.)\n",
       si.nPos, first, lim, si.nMin, si.nMax);
  }
}