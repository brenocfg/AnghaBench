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
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_SETTEXT ; 
 int /*<<< orphan*/  find_tests ; 
 int /*<<< orphan*/  find_tests2 ; 
 int /*<<< orphan*/  find_tests3 ; 
 scalar_t__ haystack ; 
 scalar_t__ haystack2 ; 
 int /*<<< orphan*/  new_richedit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  run_tests_EM_FINDTEXT (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_EM_FINDTEXT(void)
{
  HWND hwndRichEdit = new_richedit(NULL);

  /* Empty rich edit control */
  run_tests_EM_FINDTEXT(hwndRichEdit, "1", find_tests, ARRAY_SIZE(find_tests));

  SendMessageA(hwndRichEdit, WM_SETTEXT, 0, (LPARAM)haystack);

  /* Haystack text */
  run_tests_EM_FINDTEXT(hwndRichEdit, "2", find_tests2, ARRAY_SIZE(find_tests2));

  SendMessageA(hwndRichEdit, WM_SETTEXT, 0, (LPARAM)haystack2);

  /* Haystack text 2 (with EOL characters) */
  run_tests_EM_FINDTEXT(hwndRichEdit, "3", find_tests3, ARRAY_SIZE(find_tests3));

  DestroyWindow(hwndRichEdit);
}