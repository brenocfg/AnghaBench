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
typedef  int /*<<< orphan*/  text ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/ * HWND ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateWindowA (int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EM_SCROLLCARET ; 
 int ES_MULTILINE ; 
 scalar_t__ GetLastError () ; 
 int RICHEDIT_CLASS20A ; 
 int /*<<< orphan*/  SendMessageA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_SETTEXT ; 
 int WS_HSCROLL ; 
 int WS_POPUP ; 
 int WS_VISIBLE ; 
 int WS_VSCROLL ; 
 int get_scroll_pos_y (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hmoduleRichEdit ; 
 int /*<<< orphan*/  line_scroll (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  move_cursor (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ok (int,char*,int,int) ; 

__attribute__((used)) static void test_EM_SCROLLCARET(void)
{
  int prevY, curY;
  const char text[] = "aa\n"
      "this is a long line of text that should be longer than the "
      "control's width\n"
      "cc\n"
      "dd\n"
      "ee\n"
      "ff\n"
      "gg\n"
      "hh\n";
  /* The richedit window height needs to be large enough vertically to fit in
   * more than two lines of text, so the new_richedit function can't be used
   * since a height of 60 was not large enough on some systems.
   */
  HWND hwndRichEdit = CreateWindowA(RICHEDIT_CLASS20A, NULL,
                                   ES_MULTILINE|WS_POPUP|WS_HSCROLL|WS_VSCROLL|WS_VISIBLE,
                                   0, 0, 200, 80, NULL, NULL, hmoduleRichEdit, NULL);
  ok(hwndRichEdit != NULL, "class: %s, error: %d\n", RICHEDIT_CLASS20A, (int) GetLastError());

  /* Can't verify this */
  SendMessageA(hwndRichEdit, EM_SCROLLCARET, 0, 0);

  SendMessageA(hwndRichEdit, WM_SETTEXT, 0, (LPARAM)text);

  /* Caret above visible window */
  line_scroll(hwndRichEdit, 3);
  prevY = get_scroll_pos_y(hwndRichEdit);
  SendMessageA(hwndRichEdit, EM_SCROLLCARET, 0, 0);
  curY = get_scroll_pos_y(hwndRichEdit);
  ok(prevY != curY, "%d == %d\n", prevY, curY);

  /* Caret below visible window */
  move_cursor(hwndRichEdit, sizeof(text) - 1);
  line_scroll(hwndRichEdit, -3);
  prevY = get_scroll_pos_y(hwndRichEdit);
  SendMessageA(hwndRichEdit, EM_SCROLLCARET, 0, 0);
  curY = get_scroll_pos_y(hwndRichEdit);
  ok(prevY != curY, "%d == %d\n", prevY, curY);

  /* Caret in visible window */
  move_cursor(hwndRichEdit, sizeof(text) - 2);
  prevY = get_scroll_pos_y(hwndRichEdit);
  SendMessageA(hwndRichEdit, EM_SCROLLCARET, 0, 0);
  curY = get_scroll_pos_y(hwndRichEdit);
  ok(prevY == curY, "%d != %d\n", prevY, curY);

  /* Caret still in visible window */
  line_scroll(hwndRichEdit, -1);
  prevY = get_scroll_pos_y(hwndRichEdit);
  SendMessageA(hwndRichEdit, EM_SCROLLCARET, 0, 0);
  curY = get_scroll_pos_y(hwndRichEdit);
  ok(prevY == curY, "%d != %d\n", prevY, curY);

  DestroyWindow(hwndRichEdit);
}