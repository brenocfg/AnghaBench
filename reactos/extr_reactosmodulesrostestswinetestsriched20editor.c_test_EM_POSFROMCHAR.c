#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fmt ;
typedef  int WPARAM ;
struct TYPE_6__ {int* lsUsb; } ;
struct TYPE_5__ {int cbSize; int dxStartIndent; int dxOffset; int wAlignment; } ;
struct TYPE_4__ {int x; } ;
typedef  TYPE_1__ POINTL ;
typedef  TYPE_2__ PARAFORMAT2 ;
typedef  int LRESULT ;
typedef  int /*<<< orphan*/  LPSTR ;
typedef  int LPARAM ;
typedef  TYPE_3__ LOCALESIGNATURE ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EM_GETPARAFORMAT ; 
 int /*<<< orphan*/  EM_POSFROMCHAR ; 
 int /*<<< orphan*/  EM_REPLACESEL ; 
 int /*<<< orphan*/  EM_SCROLL ; 
 int /*<<< orphan*/  EM_SETSEL ; 
 scalar_t__ GetLocaleInfoA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int HIWORD (int) ; 
 int /*<<< orphan*/  LOCALE_FONTSIGNATURE ; 
 int /*<<< orphan*/  LOCALE_USER_DEFAULT ; 
 int LOWORD (int) ; 
 int PFA_LEFT ; 
 int SB_LINEDOWN ; 
 int SB_LINELEFT ; 
 int SB_LINERIGHT ; 
 int SB_LINEUP ; 
 int SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  WM_GETTEXTLENGTH ; 
 int /*<<< orphan*/  WM_HSCROLL ; 
 int /*<<< orphan*/  WM_SETTEXT ; 
 int /*<<< orphan*/  new_richedit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 

__attribute__((used)) static void test_EM_POSFROMCHAR(void)
{
  HWND hwndRichEdit = new_richedit(NULL);
  int i, expected;
  LRESULT result;
  unsigned int height = 0;
  int xpos = 0;
  POINTL pt;
  LOCALESIGNATURE sig;
  BOOL rtl;
  PARAFORMAT2 fmt;
  static const char text[] = "aa\n"
      "this is a long line of text that should be longer than the "
      "control's width\n"
      "cc\n"
      "dd\n"
      "ee\n"
      "ff\n"
      "gg\n"
      "hh\n";

  rtl = (GetLocaleInfoA(LOCALE_USER_DEFAULT, LOCALE_FONTSIGNATURE,
                        (LPSTR) &sig, sizeof(LOCALESIGNATURE)) &&
         (sig.lsUsb[3] & 0x08000000) != 0);

  /* Fill the control to lines to ensure that most of them are offscreen */
  for (i = 0; i < 50; i++)
  {
    /* Do not modify the string; it is exactly 16 characters long. */
    SendMessageA(hwndRichEdit, EM_SETSEL, 0, 0);
    SendMessageA(hwndRichEdit, EM_REPLACESEL, 0, (LPARAM)"0123456789ABCDE\n");
  }

  /*
   Richedit 1.0 receives a POINTL* on wParam and character offset on lParam, returns void.
   Richedit 2.0 receives character offset on wParam, ignores lParam, returns MAKELONG(x,y)
   Richedit 3.0 accepts either of the above API conventions.
   */

  /* Testing Richedit 2.0 API format */

  /* Testing start of lines. X-offset should be constant on all cases (native is 1).
     Since all lines are identical and drawn with the same font,
     they should have the same height... right?
   */
  for (i = 0; i < 50; i++)
  {
    /* All the lines are 16 characters long */
    result = SendMessageA(hwndRichEdit, EM_POSFROMCHAR, i * 16, 0);
    if (i == 0)
    {
      ok(HIWORD(result) == 0, "EM_POSFROMCHAR reports y=%d, expected 0\n", HIWORD(result));
      ok(LOWORD(result) == 1, "EM_POSFROMCHAR reports x=%d, expected 1\n", LOWORD(result));
      xpos = LOWORD(result);
    }
    else if (i == 1)
    {
      ok(HIWORD(result) > 0, "EM_POSFROMCHAR reports y=%d, expected > 0\n", HIWORD(result));
      ok(LOWORD(result) == xpos, "EM_POSFROMCHAR reports x=%d, expected 1\n", LOWORD(result));
      height = HIWORD(result);
    }
    else
    {
      ok(HIWORD(result) == i * height, "EM_POSFROMCHAR reports y=%d, expected %d\n", HIWORD(result), i * height);
      ok(LOWORD(result) == xpos, "EM_POSFROMCHAR reports x=%d, expected 1\n", LOWORD(result));
    }
  }

  /* Testing position at end of text */
  result = SendMessageA(hwndRichEdit, EM_POSFROMCHAR, 50 * 16, 0);
  ok(HIWORD(result) == 50 * height, "EM_POSFROMCHAR reports y=%d, expected %d\n", HIWORD(result), 50 * height);
  ok(LOWORD(result) == xpos, "EM_POSFROMCHAR reports x=%d, expected 1\n", LOWORD(result));

  /* Testing position way past end of text */
  result = SendMessageA(hwndRichEdit, EM_POSFROMCHAR, 55 * 16, 0);
  ok(HIWORD(result) == 50 * height, "EM_POSFROMCHAR reports y=%d, expected %d\n", HIWORD(result), 50 * height);
  expected = (rtl ? 8 : 1);
  ok(LOWORD(result) == expected, "EM_POSFROMCHAR reports x=%d, expected %d\n", LOWORD(result), expected);

  /* Testing that vertical scrolling does, in fact, have an effect on EM_POSFROMCHAR */
  SendMessageA(hwndRichEdit, EM_SCROLL, SB_LINEDOWN, 0); /* line down */
  for (i = 0; i < 50; i++)
  {
    /* All the lines are 16 characters long */
    result = SendMessageA(hwndRichEdit, EM_POSFROMCHAR, i * 16, 0);
    ok((signed short)(HIWORD(result)) == (i - 1) * height,
        "EM_POSFROMCHAR reports y=%hd, expected %d\n",
        (signed short)(HIWORD(result)), (i - 1) * height);
    ok(LOWORD(result) == xpos, "EM_POSFROMCHAR reports x=%d, expected 1\n", LOWORD(result));
  }

  /* Testing position at end of text */
  result = SendMessageA(hwndRichEdit, EM_POSFROMCHAR, 50 * 16, 0);
  ok(HIWORD(result) == (50 - 1) * height, "EM_POSFROMCHAR reports y=%d, expected %d\n", HIWORD(result), (50 - 1) * height);
  ok(LOWORD(result) == xpos, "EM_POSFROMCHAR reports x=%d, expected 1\n", LOWORD(result));

  /* Testing position way past end of text */
  result = SendMessageA(hwndRichEdit, EM_POSFROMCHAR, 55 * 16, 0);
  ok(HIWORD(result) == (50 - 1) * height, "EM_POSFROMCHAR reports y=%d, expected %d\n", HIWORD(result), (50 - 1) * height);
  expected = (rtl ? 8 : 1);
  ok(LOWORD(result) == expected, "EM_POSFROMCHAR reports x=%d, expected %d\n", LOWORD(result), expected);

  /* Testing that horizontal scrolling does, in fact, have an effect on EM_POSFROMCHAR */
  SendMessageA(hwndRichEdit, WM_SETTEXT, 0, (LPARAM)text);
  SendMessageA(hwndRichEdit, EM_SCROLL, SB_LINEUP, 0); /* line up */

  result = SendMessageA(hwndRichEdit, EM_POSFROMCHAR, 0, 0);
  ok(HIWORD(result) == 0, "EM_POSFROMCHAR reports y=%d, expected 0\n", HIWORD(result));
  ok(LOWORD(result) == 1, "EM_POSFROMCHAR reports x=%d, expected 1\n", LOWORD(result));
  xpos = LOWORD(result);

  SendMessageA(hwndRichEdit, WM_HSCROLL, SB_LINERIGHT, 0);
  result = SendMessageA(hwndRichEdit, EM_POSFROMCHAR, 0, 0);
  ok(HIWORD(result) == 0, "EM_POSFROMCHAR reports y=%d, expected 0\n", HIWORD(result));
  ok((signed short)(LOWORD(result)) < xpos,
        "EM_POSFROMCHAR reports x=%hd, expected value less than %d\n",
        (signed short)(LOWORD(result)), xpos);
  SendMessageA(hwndRichEdit, WM_HSCROLL, SB_LINELEFT, 0);

  /* Test around end of text that doesn't end in a newline. */
  SendMessageA(hwndRichEdit, WM_SETTEXT, 0, (LPARAM)"12345678901234");
  SendMessageA(hwndRichEdit, EM_POSFROMCHAR, (WPARAM)&pt,
              SendMessageA(hwndRichEdit, WM_GETTEXTLENGTH, 0, 0)-1);
  ok(pt.x > 1, "pt.x = %d\n", pt.x);
  xpos = pt.x;
  SendMessageA(hwndRichEdit, EM_POSFROMCHAR, (WPARAM)&pt,
              SendMessageA(hwndRichEdit, WM_GETTEXTLENGTH, 0, 0));
  ok(pt.x > xpos, "pt.x = %d\n", pt.x);
  xpos = (rtl ? pt.x + 7 : pt.x);
  SendMessageA(hwndRichEdit, EM_POSFROMCHAR, (WPARAM)&pt,
              SendMessageA(hwndRichEdit, WM_GETTEXTLENGTH, 0, 0)+1);
  ok(pt.x == xpos, "pt.x = %d\n", pt.x);

  /* Try a negative position. */
  SendMessageA(hwndRichEdit, EM_POSFROMCHAR, (WPARAM)&pt, -1);
  ok(pt.x == 1, "pt.x = %d\n", pt.x);

  /* test negative indentation */
  SendMessageA(hwndRichEdit, WM_SETTEXT, 0,
          (LPARAM)"{\\rtf1\\pard\\fi-200\\li-200\\f1 TestSomeText\\par}");
  SendMessageA(hwndRichEdit, EM_POSFROMCHAR, (WPARAM)&pt, 0);
  ok(pt.x == 1, "pt.x = %d\n", pt.x);

  fmt.cbSize = sizeof(fmt);
  SendMessageA(hwndRichEdit, EM_GETPARAFORMAT, 0, (LPARAM)&fmt);
  ok(fmt.dxStartIndent == -400, "got %d\n", fmt.dxStartIndent);
  ok(fmt.dxOffset == 200, "got %d\n", fmt.dxOffset);
  ok(fmt.wAlignment == PFA_LEFT, "got %d\n", fmt.wAlignment);

  DestroyWindow(hwndRichEdit);
}