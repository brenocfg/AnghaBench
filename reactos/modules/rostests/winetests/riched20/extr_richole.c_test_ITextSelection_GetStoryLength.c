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
typedef  int /*<<< orphan*/  ITextDocument ;
typedef  int /*<<< orphan*/  IRichEditOle ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ HRESULT ;
typedef  char CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  EM_SETSEL ; 
 scalar_t__ E_INVALIDARG ; 
 scalar_t__ ITextSelection_GetStoryLength (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  WM_SETTEXT ; 
 int /*<<< orphan*/  create_interfaces (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  release_interfaces (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void test_ITextSelection_GetStoryLength(void)
{
  HWND w;
  IRichEditOle *reOle = NULL;
  ITextDocument *txtDoc = NULL;
  ITextSelection *txtSel = NULL;
  HRESULT hres;
  LONG count;
  static const CHAR test_text1[] = "TestSomeText";
  int len = strlen(test_text1) + 1;

  create_interfaces(&w, &reOle, &txtDoc, &txtSel);
  SendMessageA(w, WM_SETTEXT, 0, (LPARAM)test_text1);

  hres = ITextSelection_GetStoryLength(txtSel, &count);
  ok(hres == S_OK, "ITextSelection_GetStoryLength\n");
  ok(count == len, "got wrong length: %d\n", count);

  SendMessageA(w, EM_SETSEL, 1, 2);
  hres = ITextSelection_GetStoryLength(txtSel, &count);
  ok(hres == S_OK, "ITextSelection_GetStoryLength\n");
  ok(count == len, "got wrong length: %d\n", count);

  hres = ITextSelection_GetStoryLength(txtSel, NULL);
  ok(hres == E_INVALIDARG, "ITextSelection_GetStoryLength\n");

  release_interfaces(&w, &reOle, &txtDoc, &txtSel);
}