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
typedef  int LONG ;
typedef  int /*<<< orphan*/  ITextRange ;
typedef  int /*<<< orphan*/  ITextDocument ;
typedef  int /*<<< orphan*/  IRichEditOle ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ HRESULT ;
typedef  char CHAR ;

/* Variables and functions */
 scalar_t__ E_INVALIDARG ; 
 int /*<<< orphan*/  ITextDocument_Range (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ ITextRange_GetStoryLength (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  ITextRange_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITextRange_SetRange (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_SETTEXT ; 
 int /*<<< orphan*/  create_interfaces (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  release_interfaces (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void test_ITextRange_GetStoryLength(void)
{
  HWND w;
  IRichEditOle *reOle = NULL;
  ITextDocument *txtDoc = NULL;
  ITextRange *txtRge = NULL;
  HRESULT hres;
  LONG count;
  static const CHAR test_text1[] = "TestSomeText";
  int len = strlen(test_text1) + 1;

  create_interfaces(&w, &reOle, &txtDoc, NULL);
  SendMessageA(w, WM_SETTEXT, 0, (LPARAM)test_text1);
  ITextDocument_Range(txtDoc, 0, 0, &txtRge);

  hres = ITextRange_GetStoryLength(txtRge, &count);
  ok(hres == S_OK, "ITextRange_GetStoryLength\n");
  ok(count == len, "got wrong length: %d\n", count);

  ITextRange_SetRange(txtRge, 1, 2);
  hres = ITextRange_GetStoryLength(txtRge, &count);
  ok(hres == S_OK, "ITextRange_GetStoryLength\n");
  ok(count == len, "got wrong length: %d\n", count);

  hres = ITextRange_GetStoryLength(txtRge, NULL);
  ok(hres == E_INVALIDARG, "ITextRange_GetStoryLength\n");

  ITextRange_Release(txtRge);
  release_interfaces(&w, &reOle, &txtDoc, NULL);
}