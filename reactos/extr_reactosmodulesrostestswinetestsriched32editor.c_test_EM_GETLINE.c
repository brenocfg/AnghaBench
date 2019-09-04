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
typedef  int WORD ;
struct TYPE_3__ {int line; int buffer_len; scalar_t__ text; scalar_t__ broken_text; } ;
typedef  int LRESULT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EM_GETLINE ; 
 int /*<<< orphan*/  EM_GETLINECOUNT ; 
 scalar_t__ FALSE ; 
 int SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WM_SETTEXT ; 
 TYPE_1__* gl ; 
 scalar_t__ is_rtl () ; 
 int /*<<< orphan*/  memset (char*,int,int const) ; 
 int min (int,scalar_t__) ; 
 int /*<<< orphan*/  new_richedit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  strcpy (char*,scalar_t__) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int const) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_EM_GETLINE(void)
{
  int i;
  HWND hwndRichEdit = new_richedit(NULL);
  static const int nBuf = 1024;
  char dest[1024], origdest[1024];
  LRESULT linecount;
  const char text[] = "foo bar\r\n"
      "\r"
      "\r\r\n"
      "bar\n";
  BOOL broken_os = FALSE;
  BOOL rtl = is_rtl();

  SendMessageA(hwndRichEdit, WM_SETTEXT, 0, (LPARAM)text);
  linecount = SendMessageA(hwndRichEdit, EM_GETLINECOUNT, 0, 0);
  if (linecount == 4)
  {
    broken_os = TRUE;
    win_skip("Win9x, WinME and NT4 handle '\\r only' differently\n");
  }

  memset(origdest, 0xBB, nBuf);
  for (i = 0; i < ARRAY_SIZE(gl); i++)
  {
    int nCopied, expected_nCopied, expected_bytes_written;
    char gl_text[1024];

    if (gl[i].line >= linecount)
      continue; /* Win9x, WinME and NT4 */

    if (broken_os && gl[i].broken_text)
      /* Win9x, WinME and NT4 */
      strcpy(gl_text, gl[i].broken_text);
    else
      strcpy(gl_text, gl[i].text);

    expected_nCopied = min(gl[i].buffer_len, strlen(gl_text));
    /* Cater for the fact that Win9x, WinME and NT4 don't append the '\0' */
    expected_bytes_written = min(gl[i].buffer_len, strlen(gl_text) + (broken_os ? 0 : 1));

    memset(dest, 0xBB, nBuf);
    *(WORD *) dest = gl[i].buffer_len;

    /* EM_GETLINE appends a "\r\0" to the end of the line
     * nCopied counts up to and including the '\r' */
    nCopied = SendMessageA(hwndRichEdit, EM_GETLINE, gl[i].line, (LPARAM)dest);
    ok(nCopied == expected_nCopied, "%d: %d!=%d\n", i, nCopied,
       expected_nCopied);
    /* two special cases since a parameter is passed via dest */
    if (gl[i].buffer_len == 0)
      ok(!dest[0] && !dest[1] && !strncmp(dest+2, origdest+2, nBuf-2),
         "buffer_len=0\n");
    else if (gl[i].buffer_len == 1)
      ok(dest[0] == gl_text[0] && !dest[1] &&
         !strncmp(dest+2, origdest+2, nBuf-2), "buffer_len=1\n");
    else
    {
      ok(!strncmp(dest, gl_text, expected_bytes_written),
         "%d: expected_bytes_written=%d\n", i, expected_bytes_written);
      if (! rtl || expected_bytes_written == gl[i].buffer_len)
        ok(!strncmp(dest + expected_bytes_written, origdest
                    + expected_bytes_written, nBuf - expected_bytes_written),
           "%d: expected_bytes_written=%d\n", i, expected_bytes_written);
      else
        ok(dest[expected_bytes_written] == 0 &&
           !strncmp(dest + expected_bytes_written + 1, origdest
                    + expected_bytes_written + 1, nBuf - (expected_bytes_written + 1)),
           "%d: expected_bytes_written=%d\n", i, expected_bytes_written);
    }
  }

  DestroyWindow(hwndRichEdit);
}