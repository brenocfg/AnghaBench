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
typedef  int LONG ;
typedef  int /*<<< orphan*/  ITextSelection ;
typedef  int /*<<< orphan*/  ITextRange ;
typedef  int /*<<< orphan*/  ITextDocument ;
typedef  int /*<<< orphan*/  IRichEditOle ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_RANGE (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  CHECK_SELECTION (int /*<<< orphan*/ *,int,int) ; 
 int CO_E_RELEASED ; 
 int /*<<< orphan*/  EM_SETSEL ; 
 int ITextDocument_Range (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ **) ; 
 int ITextRange_MoveEnd (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  ITextRange_Release (int /*<<< orphan*/ *) ; 
 int ITextSelection_MoveEnd (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  ITextSelection_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RESET_RANGE (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  RESET_SELECTION (int /*<<< orphan*/ *,int,int) ; 
 int S_FALSE ; 
 int S_OK ; 
 int /*<<< orphan*/  SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  WM_SETTEXT ; 
 int /*<<< orphan*/  create_interfaces (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  release_interfaces (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tomStory ; 

__attribute__((used)) static void test_MoveEnd(void)
{
  static const char test_text1[] = "Word1 Word2";
  IRichEditOle *reole = NULL;
  ITextDocument *doc = NULL;
  ITextSelection *selection;
  ITextRange *range;
  LONG delta;
  HRESULT hr;
  HWND hwnd;

  create_interfaces(&hwnd, &reole, &doc, &selection);
  SendMessageA(hwnd, WM_SETTEXT, 0, (LPARAM)test_text1);
  SendMessageA(hwnd, EM_SETSEL, 1, 2);

  hr = ITextDocument_Range(doc, 1, 2, &range);
  ok(hr == S_OK, "got 0x%08x\n", hr);

  hr = ITextRange_MoveEnd(range, tomStory, 0, &delta);
  ok(hr == S_FALSE, "got 0x%08x\n", hr);
  ok(delta == 0, "got %d\n", delta);
  CHECK_RANGE(range, 1, 2);

  hr = ITextRange_MoveEnd(range, tomStory, -1, &delta);
  ok(hr == S_OK, "got 0x%08x\n", hr);
  ok(delta == -1, "got %d\n", delta);
  CHECK_RANGE(range, 0, 0);

  hr = ITextRange_MoveEnd(range, tomStory, 1, &delta);
  ok(hr == S_OK, "got 0x%08x\n", hr);
  ok(delta == 1, "got %d\n", delta);
  CHECK_RANGE(range, 0, 12);

  hr = ITextRange_MoveEnd(range, tomStory, 1, &delta);
  ok(hr == S_FALSE, "got 0x%08x\n", hr);
  ok(delta == 0, "got %d\n", delta);
  CHECK_RANGE(range, 0, 12);

  RESET_RANGE(range, 1, 2);

  hr = ITextRange_MoveEnd(range, tomStory, 3, &delta);
  ok(hr == S_OK, "got 0x%08x\n", hr);
  ok(delta == 1, "got %d\n", delta);
  CHECK_RANGE(range, 1, 12);

  RESET_RANGE(range, 2, 3);

  hr = ITextRange_MoveEnd(range, tomStory, -3, &delta);
  ok(hr == S_OK, "got 0x%08x\n", hr);
  ok(delta == -1, "got %d\n", delta);
  CHECK_RANGE(range, 0, 0);

  hr = ITextRange_MoveEnd(range, tomStory, -1, &delta);
  ok(hr == S_FALSE, "got 0x%08x\n", hr);
  ok(delta == 0, "got %d\n", delta);
  CHECK_RANGE(range, 0, 0);

  hr = ITextSelection_MoveEnd(selection, tomStory, 0, &delta);
  ok(hr == S_FALSE, "got 0x%08x\n", hr);
  ok(delta == 0, "got %d\n", delta);
  CHECK_SELECTION(selection, 1, 2);

  hr = ITextSelection_MoveEnd(selection, tomStory, -1, &delta);
  ok(hr == S_OK, "got 0x%08x\n", hr);
  ok(delta == -1, "got %d\n", delta);
  CHECK_SELECTION(selection, 0, 0);

  hr = ITextSelection_MoveEnd(selection, tomStory, 1, &delta);
  ok(hr == S_OK, "got 0x%08x\n", hr);
  ok(delta == 1, "got %d\n", delta);
  CHECK_SELECTION(selection, 0, 12);

  hr = ITextSelection_MoveEnd(selection, tomStory, 1, &delta);
  ok(hr == S_FALSE, "got 0x%08x\n", hr);
  ok(delta == 0, "got %d\n", delta);
  CHECK_SELECTION(selection, 0, 12);

  RESET_SELECTION(selection, 1, 2);

  hr = ITextSelection_MoveEnd(selection, tomStory, 3, &delta);
  ok(hr == S_OK, "got 0x%08x\n", hr);
  ok(delta == 1, "got %d\n", delta);
  CHECK_SELECTION(selection, 1, 12);

  RESET_SELECTION(selection, 2, 3);

  hr = ITextSelection_MoveEnd(selection, tomStory, -3, &delta);
  ok(hr == S_OK, "got 0x%08x\n", hr);
  ok(delta == -1, "got %d\n", delta);
  CHECK_SELECTION(selection, 0, 0);

  hr = ITextSelection_MoveEnd(selection, tomStory, -1, &delta);
  ok(hr == S_FALSE, "got 0x%08x\n", hr);
  ok(delta == 0, "got %d\n", delta);
  CHECK_SELECTION(selection, 0, 0);

  release_interfaces(&hwnd, &reole, &doc, NULL);

  hr = ITextRange_MoveEnd(range, tomStory, 1, NULL);
  ok(hr == CO_E_RELEASED, "got 0x%08x\n", hr);

  hr = ITextRange_MoveEnd(range, tomStory, 1, &delta);
  ok(hr == CO_E_RELEASED, "got 0x%08x\n", hr);

  hr = ITextSelection_MoveEnd(selection, tomStory, 1, NULL);
  ok(hr == CO_E_RELEASED, "got 0x%08x\n", hr);

  hr = ITextSelection_MoveEnd(selection, tomStory, 1, &delta);
  ok(hr == CO_E_RELEASED, "got 0x%08x\n", hr);

  ITextSelection_Release(selection);
  ITextRange_Release(range);
}