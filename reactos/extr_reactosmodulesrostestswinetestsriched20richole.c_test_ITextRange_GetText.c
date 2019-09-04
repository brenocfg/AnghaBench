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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  ITextRange ;
typedef  int /*<<< orphan*/  ITextDocument ;
typedef  int /*<<< orphan*/  IRichEditOle ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ HRESULT ;
typedef  char CHAR ;
typedef  int /*<<< orphan*/ * BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  ITextDocument_Range (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ **) ; 
 scalar_t__ ITextRange_GetText (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ITextRange_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WM_SETTEXT ; 
 int /*<<< orphan*/  create_interfaces (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcmpW (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  release_interfaces (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wine_dbgstr_w (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_ITextRange_GetText(void)
{
  HWND w;
  IRichEditOle *reOle = NULL;
  ITextDocument *txtDoc = NULL;
  ITextRange *txtRge = NULL;
  HRESULT hres;
  BSTR bstr = NULL;
  static const CHAR test_text1[] = "TestSomeText";
  static const WCHAR bufW1[] = {'T', 'e', 's', 't', 0};
  static const WCHAR bufW2[] = {'T', 'e', 'x', 't', '\r', 0};
  static const WCHAR bufW3[] = {'T', 'e', 'x', 't', 0};
  static const WCHAR bufW4[] = {'T', 'e', 's', 't', 'S', 'o', 'm',
                                'e', 'T', 'e', 'x', 't', '\r', 0};
  static const WCHAR bufW5[] = {'\r', 0};


#define TEST_TXTRGE_GETTEXT(first, lim, expected_string)                \
  create_interfaces(&w, &reOle, &txtDoc, NULL);                         \
  SendMessageA(w, WM_SETTEXT, 0, (LPARAM)test_text1);                   \
  ITextDocument_Range(txtDoc, first, lim, &txtRge);                     \
  hres = ITextRange_GetText(txtRge, &bstr);                             \
  ok(hres == S_OK, "ITextRange_GetText\n");                             \
  ok(!lstrcmpW(bstr, expected_string), "got wrong text: %s\n", wine_dbgstr_w(bstr)); \
  SysFreeString(bstr);                                                  \
  ITextRange_Release(txtRge);                                           \
  release_interfaces(&w, &reOle, &txtDoc, NULL);

  TEST_TXTRGE_GETTEXT(0, 4, bufW1)
  TEST_TXTRGE_GETTEXT(4, 0, bufW1)
  TEST_TXTRGE_GETTEXT(8, 12, bufW3)
  TEST_TXTRGE_GETTEXT(8, 13, bufW2)
  TEST_TXTRGE_GETTEXT(12, 13, bufW5)
  TEST_TXTRGE_GETTEXT(0, 13, bufW4)
  TEST_TXTRGE_GETTEXT(1, 1, NULL)
}