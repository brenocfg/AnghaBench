#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  urls ;
typedef  int /*<<< orphan*/  templates_xten_delim ;
typedef  int /*<<< orphan*/  templates_non_delim ;
typedef  int /*<<< orphan*/  templates_neutral_delim ;
typedef  int /*<<< orphan*/  templates_delim ;
typedef  int /*<<< orphan*/  buffer ;
typedef  int WPARAM ;
struct TYPE_2__ {void* flags; void* codepage; } ;
typedef  TYPE_1__ SETTEXTEX ;
typedef  int LPARAM ;
typedef  int /*<<< orphan*/ * HWND ;
typedef  int BOOL ;

/* Variables and functions */
 void* CP_ACP ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EM_AUTOURLDETECT ; 
 int /*<<< orphan*/  EM_REPLACESEL ; 
 int /*<<< orphan*/  EM_SETSEL ; 
 int /*<<< orphan*/  EM_SETTEXTEX ; 
 int E_INVALIDARG ; 
 int FALSE ; 
 void* ST_DEFAULT ; 
 void* ST_SELECTION ; 
 int SendMessageA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const,int) ; 
 int TRUE ; 
 int /*<<< orphan*/  WM_CHAR ; 
 int /*<<< orphan*/  WM_GETTEXT ; 
 int /*<<< orphan*/  WM_SETTEXT ; 
 int /*<<< orphan*/  check_CFE_LINK_rcvd (int /*<<< orphan*/ *,int,char const*) ; 
 int check_CFE_LINK_selection (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/ * new_richedit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * new_static_wnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  simulate_typing_characters (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void test_EM_AUTOURLDETECT(void)
{
  /* DO NOT change the properties of the first two elements. To shorten the
     tests, all tests after WM_SETTEXT test just the first two elements -
     one non-URL and one URL */
  struct urls_s {
    const char *text;
    BOOL is_url;
  } urls[12] = {
    {"winehq.org", FALSE},
    {"http://www.winehq.org", TRUE},
    {"http//winehq.org", FALSE},
    {"ww.winehq.org", FALSE},
    {"www.winehq.org", TRUE},
    {"ftp://192.168.1.1", TRUE},
    {"ftp//192.168.1.1", FALSE},
    {"mailto:your@email.com", TRUE},
    {"prospero:prosperoserver", TRUE},
    {"telnet:test", TRUE},
    {"news:newserver", TRUE},
    {"wais:waisserver", TRUE}
  };

  int i, j;
  int urlRet=-1;
  HWND hwndRichEdit, parent;

  /* All of the following should cause the URL to be detected  */
  const char * templates_delim[] = {
    "This is some text with X on it",
    "This is some text with (X) on it",
    "This is some text with X\r on it",
    "This is some text with ---X--- on it",
    "This is some text with \"X\" on it",
    "This is some text with 'X' on it",
    "This is some text with 'X' on it",
    "This is some text with :X: on it",

    "This text ends with X",

    "This is some text with X) on it",
    "This is some text with X--- on it",
    "This is some text with X\" on it",
    "This is some text with X' on it",
    "This is some text with X: on it",

    "This is some text with (X on it",
    "This is some text with \rX on it",
    "This is some text with ---X on it",
    "This is some text with \"X on it",
    "This is some text with 'X on it",
    "This is some text with :X on it",
  };
  /* None of these should cause the URL to be detected */
  const char * templates_non_delim[] = {
    "This is some text with |X| on it",
    "This is some text with *X* on it",
    "This is some text with /X/ on it",
    "This is some text with +X+ on it",
    "This is some text with %X% on it",
    "This is some text with #X# on it",
    "This is some text with @X@ on it",
    "This is some text with \\X\\ on it",
    "This is some text with |X on it",
    "This is some text with *X on it",
    "This is some text with /X on it",
    "This is some text with +X on it",
    "This is some text with %X on it",
    "This is some text with #X on it",
    "This is some text with @X on it",
    "This is some text with \\X on it",
    "This is some text with _X on it",
  };
  /* All of these cause the URL detection to be extended by one more byte,
     thus demonstrating that the tested character is considered as part
     of the URL. */
  const char * templates_xten_delim[] = {
    "This is some text with X| on it",
    "This is some text with X* on it",
    "This is some text with X/ on it",
    "This is some text with X+ on it",
    "This is some text with X% on it",
    "This is some text with X# on it",
    "This is some text with X@ on it",
    "This is some text with X\\ on it",
    "This is some text with X_ on it",
  };
  /* These delims act as neutral breaks.  Whether the url is ended
     or not depends on the next non-neutral character.  We'll test
     with Y unchanged, in which case the url should include the
     deliminator and the Y.  We'll also test with the Y changed
     to a space, in which case the url stops before the
     deliminator. */
  const char * templates_neutral_delim[] = {
    "This is some text with X-Y on it",
    "This is some text with X--Y on it",
    "This is some text with X!Y on it",
    "This is some text with X[Y on it",
    "This is some text with X]Y on it",
    "This is some text with X{Y on it",
    "This is some text with X}Y on it",
    "This is some text with X(Y on it",
    "This is some text with X)Y on it",
    "This is some text with X\"Y on it",
    "This is some text with X;Y on it",
    "This is some text with X:Y on it",
    "This is some text with X'Y on it",
    "This is some text with X?Y on it",
    "This is some text with X<Y on it",
    "This is some text with X>Y on it",
    "This is some text with X.Y on it",
    "This is some text with X,Y on it",
  };
  char buffer[1024];

  parent = new_static_wnd(NULL);
  hwndRichEdit = new_richedit(parent);
  /* Try and pass EM_AUTOURLDETECT some test wParam values */
  urlRet=SendMessageA(hwndRichEdit, EM_AUTOURLDETECT, FALSE, 0);
  ok(urlRet==0, "Good wParam: urlRet is: %d\n", urlRet);
  urlRet=SendMessageA(hwndRichEdit, EM_AUTOURLDETECT, 1, 0);
  ok(urlRet==0, "Good wParam2: urlRet is: %d\n", urlRet);
  /* Windows returns -2147024809 (0x80070057) on bad wParam values */
  urlRet=SendMessageA(hwndRichEdit, EM_AUTOURLDETECT, 8, 0);
  ok(urlRet==E_INVALIDARG, "Bad wParam: urlRet is: %d\n", urlRet);
  urlRet=SendMessageA(hwndRichEdit, EM_AUTOURLDETECT, (WPARAM)"h", (LPARAM)"h");
  ok(urlRet==E_INVALIDARG, "Bad wParam2: urlRet is: %d\n", urlRet);
  /* for each url, check the text to see if CFE_LINK effect is present */
  for (i = 0; i < sizeof(urls)/sizeof(struct urls_s); i++) {

    SendMessageA(hwndRichEdit, EM_AUTOURLDETECT, FALSE, 0);
    SendMessageA(hwndRichEdit, WM_SETTEXT, 0, (LPARAM)urls[i].text);
    check_CFE_LINK_rcvd(hwndRichEdit, FALSE, urls[i].text);

    /* Link detection should happen immediately upon WM_SETTEXT */
    SendMessageA(hwndRichEdit, EM_AUTOURLDETECT, TRUE, 0);
    SendMessageA(hwndRichEdit, WM_SETTEXT, 0, (LPARAM)urls[i].text);
    check_CFE_LINK_rcvd(hwndRichEdit, urls[i].is_url, urls[i].text);
  }
  DestroyWindow(hwndRichEdit);

  /* Test detection of URLs within normal text - WM_SETTEXT case. */
  for (i = 0; i < sizeof(urls)/sizeof(struct urls_s); i++) {
    hwndRichEdit = new_richedit(parent);

    for (j = 0; j < sizeof(templates_delim) / sizeof(const char *); j++) {
      char * at_pos;
      int at_offset;
      int end_offset;

      at_pos = strchr(templates_delim[j], 'X');
      at_offset = at_pos - templates_delim[j];
      memcpy(buffer, templates_delim[j], at_offset);
      buffer[at_offset] = '\0';
      strcat(buffer, urls[i].text);
      strcat(buffer, templates_delim[j] + at_offset + 1);
      end_offset = at_offset + strlen(urls[i].text);

      SendMessageA(hwndRichEdit, EM_AUTOURLDETECT, TRUE, 0);
      SendMessageA(hwndRichEdit, WM_SETTEXT, 0, (LPARAM)buffer);

      /* This assumes no templates start with the URL itself, and that they
         have at least two characters before the URL text */
      ok(!check_CFE_LINK_selection(hwndRichEdit, 0, 1),
        "CFE_LINK incorrectly set in (%d-%d), text: %s\n", 0, 1, buffer);
      ok(!check_CFE_LINK_selection(hwndRichEdit, at_offset -2, at_offset -1),
        "CFE_LINK incorrectly set in (%d-%d), text: %s\n", at_offset -2, at_offset -1, buffer);
      ok(!check_CFE_LINK_selection(hwndRichEdit, at_offset -1, at_offset),
        "CFE_LINK incorrectly set in (%d-%d), text: %s\n", at_offset -1, at_offset, buffer);

      if (urls[i].is_url)
      {
        ok(check_CFE_LINK_selection(hwndRichEdit, at_offset, at_offset +1),
          "CFE_LINK not set in (%d-%d), text: %s\n", at_offset, at_offset +1, buffer);
        ok(check_CFE_LINK_selection(hwndRichEdit, end_offset -1, end_offset),
          "CFE_LINK not set in (%d-%d), text: %s\n", end_offset -1, end_offset, buffer);
      }
      else
      {
        ok(!check_CFE_LINK_selection(hwndRichEdit, at_offset, at_offset +1),
          "CFE_LINK incorrectly set in (%d-%d), text: %s\n", at_offset, at_offset + 1, buffer);
        ok(!check_CFE_LINK_selection(hwndRichEdit, end_offset -1, end_offset),
          "CFE_LINK incorrectly set in (%d-%d), text: %s\n", end_offset -1, end_offset, buffer);
      }
      if (buffer[end_offset] != '\0')
      {
        ok(!check_CFE_LINK_selection(hwndRichEdit, end_offset, end_offset +1),
          "CFE_LINK incorrectly set in (%d-%d), text: %s\n", end_offset, end_offset + 1, buffer);
        if (buffer[end_offset +1] != '\0')
        {
          ok(!check_CFE_LINK_selection(hwndRichEdit, end_offset +1, end_offset +2),
            "CFE_LINK incorrectly set in (%d-%d), text: %s\n", end_offset +1, end_offset +2, buffer);
        }
      }
    }

    for (j = 0; j < sizeof(templates_non_delim) / sizeof(const char *); j++) {
      char * at_pos;
      int at_offset;
      int end_offset;

      at_pos = strchr(templates_non_delim[j], 'X');
      at_offset = at_pos - templates_non_delim[j];
      memcpy(buffer, templates_non_delim[j], at_offset);
      buffer[at_offset] = '\0';
      strcat(buffer, urls[i].text);
      strcat(buffer, templates_non_delim[j] + at_offset + 1);
      end_offset = at_offset + strlen(urls[i].text);

      SendMessageA(hwndRichEdit, EM_AUTOURLDETECT, TRUE, 0);
      SendMessageA(hwndRichEdit, WM_SETTEXT, 0, (LPARAM)buffer);

      /* This assumes no templates start with the URL itself, and that they
         have at least two characters before the URL text */
      ok(!check_CFE_LINK_selection(hwndRichEdit, 0, 1),
        "CFE_LINK incorrectly set in (%d-%d), text: %s\n", 0, 1, buffer);
      ok(!check_CFE_LINK_selection(hwndRichEdit, at_offset -2, at_offset -1),
        "CFE_LINK incorrectly set in (%d-%d), text: %s\n", at_offset -2, at_offset -1, buffer);
      ok(!check_CFE_LINK_selection(hwndRichEdit, at_offset -1, at_offset),
        "CFE_LINK incorrectly set in (%d-%d), text: %s\n", at_offset -1, at_offset, buffer);

      ok(!check_CFE_LINK_selection(hwndRichEdit, at_offset, at_offset +1),
        "CFE_LINK incorrectly set in (%d-%d), text: %s\n", at_offset, at_offset + 1, buffer);
      ok(!check_CFE_LINK_selection(hwndRichEdit, end_offset -1, end_offset),
        "CFE_LINK incorrectly set in (%d-%d), text: %s\n", end_offset -1, end_offset, buffer);
      if (buffer[end_offset] != '\0')
      {
        ok(!check_CFE_LINK_selection(hwndRichEdit, end_offset, end_offset +1),
          "CFE_LINK incorrectly set in (%d-%d), text: %s\n", end_offset, end_offset + 1, buffer);
        if (buffer[end_offset +1] != '\0')
        {
          ok(!check_CFE_LINK_selection(hwndRichEdit, end_offset +1, end_offset +2),
            "CFE_LINK incorrectly set in (%d-%d), text: %s\n", end_offset +1, end_offset +2, buffer);
        }
      }
    }

    for (j = 0; j < sizeof(templates_xten_delim) / sizeof(const char *); j++) {
      char * at_pos;
      int at_offset;
      int end_offset;

      at_pos = strchr(templates_xten_delim[j], 'X');
      at_offset = at_pos - templates_xten_delim[j];
      memcpy(buffer, templates_xten_delim[j], at_offset);
      buffer[at_offset] = '\0';
      strcat(buffer, urls[i].text);
      strcat(buffer, templates_xten_delim[j] + at_offset + 1);
      end_offset = at_offset + strlen(urls[i].text);

      SendMessageA(hwndRichEdit, EM_AUTOURLDETECT, TRUE, 0);
      SendMessageA(hwndRichEdit, WM_SETTEXT, 0, (LPARAM)buffer);

      /* This assumes no templates start with the URL itself, and that they
         have at least two characters before the URL text */
      ok(!check_CFE_LINK_selection(hwndRichEdit, 0, 1),
        "CFE_LINK incorrectly set in (%d-%d), text: %s\n", 0, 1, buffer);
      ok(!check_CFE_LINK_selection(hwndRichEdit, at_offset -2, at_offset -1),
        "CFE_LINK incorrectly set in (%d-%d), text: %s\n", at_offset -2, at_offset -1, buffer);
      ok(!check_CFE_LINK_selection(hwndRichEdit, at_offset -1, at_offset),
        "CFE_LINK incorrectly set in (%d-%d), text: %s\n", at_offset -1, at_offset, buffer);

      if (urls[i].is_url)
      {
        ok(check_CFE_LINK_selection(hwndRichEdit, at_offset, at_offset +1),
          "CFE_LINK not set in (%d-%d), text: %s\n", at_offset, at_offset +1, buffer);
        ok(check_CFE_LINK_selection(hwndRichEdit, end_offset -1, end_offset),
          "CFE_LINK not set in (%d-%d), text: %s\n", end_offset -1, end_offset, buffer);
        ok(check_CFE_LINK_selection(hwndRichEdit, end_offset, end_offset +1),
          "CFE_LINK not set in (%d-%d), text: %s\n", end_offset, end_offset +1, buffer);
      }
      else
      {
        ok(!check_CFE_LINK_selection(hwndRichEdit, at_offset, at_offset +1),
          "CFE_LINK incorrectly set in (%d-%d), text: %s\n", at_offset, at_offset + 1, buffer);
        ok(!check_CFE_LINK_selection(hwndRichEdit, end_offset -1, end_offset),
          "CFE_LINK incorrectly set in (%d-%d), text: %s\n", end_offset -1, end_offset, buffer);
        ok(!check_CFE_LINK_selection(hwndRichEdit, end_offset, end_offset +1),
          "CFE_LINK incorrectly set in (%d-%d), text: %s\n", end_offset, end_offset +1, buffer);
      }
      if (buffer[end_offset +1] != '\0')
      {
        ok(!check_CFE_LINK_selection(hwndRichEdit, end_offset +1, end_offset +2),
          "CFE_LINK incorrectly set in (%d-%d), text: %s\n", end_offset +1, end_offset + 2, buffer);
        if (buffer[end_offset +2] != '\0')
        {
          ok(!check_CFE_LINK_selection(hwndRichEdit, end_offset +2, end_offset +3),
            "CFE_LINK incorrectly set in (%d-%d), text: %s\n", end_offset +2, end_offset +3, buffer);
        }
      }
    }

    for (j = 0; j < sizeof(templates_neutral_delim) / sizeof(const char *); j++) {
      char * at_pos, * end_pos;
      int at_offset;
      int end_offset;

      if (!urls[i].is_url) continue;

      at_pos = strchr(templates_neutral_delim[j], 'X');
      at_offset = at_pos - templates_neutral_delim[j];
      memcpy(buffer, templates_neutral_delim[j], at_offset);
      buffer[at_offset] = '\0';
      strcat(buffer, urls[i].text);
      strcat(buffer, templates_neutral_delim[j] + at_offset + 1);

      end_pos = strchr(buffer, 'Y');
      end_offset = end_pos - buffer;

      SendMessageA(hwndRichEdit, EM_AUTOURLDETECT, TRUE, 0);
      SendMessageA(hwndRichEdit, WM_SETTEXT, 0, (LPARAM)buffer);

      /* This assumes no templates start with the URL itself, and that they
         have at least two characters before the URL text */
      ok(!check_CFE_LINK_selection(hwndRichEdit, 0, 1),
         "CFE_LINK incorrectly set in (%d-%d), text: %s\n", 0, 1, buffer);
      ok(!check_CFE_LINK_selection(hwndRichEdit, at_offset -2, at_offset -1),
         "CFE_LINK incorrectly set in (%d-%d), text: %s\n", at_offset -2, at_offset -1, buffer);
      ok(!check_CFE_LINK_selection(hwndRichEdit, at_offset -1, at_offset),
         "CFE_LINK incorrectly set in (%d-%d), text: %s\n", at_offset -1, at_offset, buffer);

      ok(check_CFE_LINK_selection(hwndRichEdit, at_offset, at_offset +1),
         "CFE_LINK not set in (%d-%d), text: %s\n", at_offset, at_offset +1, buffer);
      ok(check_CFE_LINK_selection(hwndRichEdit, end_offset -1, end_offset),
         "CFE_LINK not set in (%d-%d), text: %s\n", end_offset -1, end_offset, buffer);
      ok(check_CFE_LINK_selection(hwndRichEdit, end_offset, end_offset +1),
         "CFE_LINK not set in (%d-%d), text: %s\n", end_offset, end_offset +1, buffer);

      *end_pos = ' ';

      SendMessageA(hwndRichEdit, EM_AUTOURLDETECT, TRUE, 0);
      SendMessageA(hwndRichEdit, WM_SETTEXT, 0, (LPARAM)buffer);

      ok(check_CFE_LINK_selection(hwndRichEdit, at_offset, at_offset +1),
         "CFE_LINK not set in (%d-%d), text: %s\n", at_offset, at_offset +1, buffer);
      ok(!check_CFE_LINK_selection(hwndRichEdit, end_offset -1, end_offset),
         "CFE_LINK set in (%d-%d), text: %s\n", end_offset -1, end_offset, buffer);
      ok(!check_CFE_LINK_selection(hwndRichEdit, end_offset, end_offset +1),
         "CFE_LINK set in (%d-%d), text: %s\n", end_offset, end_offset +1, buffer);
    }

    DestroyWindow(hwndRichEdit);
    hwndRichEdit = NULL;
  }

  /* Test detection of URLs within normal text - WM_CHAR case. */
  /* Test only the first two URL examples for brevity */
  for (i = 0; i < 2; i++) {
    hwndRichEdit = new_richedit(parent);

    /* Also for brevity, test only the first three delimiters */
    for (j = 0; j < 3; j++) {
      char * at_pos;
      int at_offset;
      int end_offset;
      int u, v;

      at_pos = strchr(templates_delim[j], 'X');
      at_offset = at_pos - templates_delim[j];
      end_offset = at_offset + strlen(urls[i].text);

      SendMessageA(hwndRichEdit, EM_AUTOURLDETECT, TRUE, 0);
      SendMessageA(hwndRichEdit, WM_SETTEXT, 0, 0);
      for (u = 0; templates_delim[j][u]; u++) {
        if (templates_delim[j][u] == '\r') {
          simulate_typing_characters(hwndRichEdit, "\r");
        } else if (templates_delim[j][u] != 'X') {
          SendMessageA(hwndRichEdit, WM_CHAR, templates_delim[j][u], 1);
        } else {
          for (v = 0; urls[i].text[v]; v++) {
            SendMessageA(hwndRichEdit, WM_CHAR, urls[i].text[v], 1);
          }
        }
      }
      SendMessageA(hwndRichEdit, WM_GETTEXT, sizeof(buffer), (LPARAM)buffer);

      /* This assumes no templates start with the URL itself, and that they
         have at least two characters before the URL text */
      ok(!check_CFE_LINK_selection(hwndRichEdit, 0, 1),
        "CFE_LINK incorrectly set in (%d-%d), text: %s\n", 0, 1, buffer);
      ok(!check_CFE_LINK_selection(hwndRichEdit, at_offset -2, at_offset -1),
        "CFE_LINK incorrectly set in (%d-%d), text: %s\n", at_offset -2, at_offset -1, buffer);
      ok(!check_CFE_LINK_selection(hwndRichEdit, at_offset -1, at_offset),
        "CFE_LINK incorrectly set in (%d-%d), text: %s\n", at_offset -1, at_offset, buffer);

      if (urls[i].is_url)
      {
        ok(check_CFE_LINK_selection(hwndRichEdit, at_offset, at_offset +1),
          "CFE_LINK not set in (%d-%d), text: %s\n", at_offset, at_offset +1, buffer);
        ok(check_CFE_LINK_selection(hwndRichEdit, end_offset -1, end_offset),
          "CFE_LINK not set in (%d-%d), text: %s\n", end_offset -1, end_offset, buffer);
      }
      else
      {
        ok(!check_CFE_LINK_selection(hwndRichEdit, at_offset, at_offset +1),
          "CFE_LINK incorrectly set in (%d-%d), text: %s\n", at_offset, at_offset + 1, buffer);
        ok(!check_CFE_LINK_selection(hwndRichEdit, end_offset -1, end_offset),
          "CFE_LINK incorrectly set in (%d-%d), text: %s\n", end_offset -1, end_offset, buffer);
      }
      if (buffer[end_offset] != '\0')
      {
        ok(!check_CFE_LINK_selection(hwndRichEdit, end_offset, end_offset +1),
          "CFE_LINK incorrectly set in (%d-%d), text: %s\n", end_offset, end_offset + 1, buffer);
        if (buffer[end_offset +1] != '\0')
        {
          ok(!check_CFE_LINK_selection(hwndRichEdit, end_offset +1, end_offset +2),
            "CFE_LINK incorrectly set in (%d-%d), text: %s\n", end_offset +1, end_offset +2, buffer);
        }
      }

      /* The following will insert a paragraph break after the first character
         of the URL candidate, thus breaking the URL. It is expected that the
         CFE_LINK attribute should break across both pieces of the URL */
      SendMessageA(hwndRichEdit, EM_SETSEL, at_offset+1, at_offset+1);
      simulate_typing_characters(hwndRichEdit, "\r");
      SendMessageA(hwndRichEdit, WM_GETTEXT, sizeof(buffer), (LPARAM)buffer);

      ok(!check_CFE_LINK_selection(hwndRichEdit, 0, 1),
        "CFE_LINK incorrectly set in (%d-%d), text: %s\n", 0, 1, buffer);
      ok(!check_CFE_LINK_selection(hwndRichEdit, at_offset -2, at_offset -1),
        "CFE_LINK incorrectly set in (%d-%d), text: %s\n", at_offset -2, at_offset -1, buffer);
      ok(!check_CFE_LINK_selection(hwndRichEdit, at_offset -1, at_offset),
        "CFE_LINK incorrectly set in (%d-%d), text: %s\n", at_offset -1, at_offset, buffer);

      ok(!check_CFE_LINK_selection(hwndRichEdit, at_offset, at_offset +1),
        "CFE_LINK incorrectly set in (%d-%d), text: %s\n", at_offset, at_offset + 1, buffer);
      /* end_offset moved because of paragraph break */
      ok(!check_CFE_LINK_selection(hwndRichEdit, end_offset -1, end_offset),
        "CFE_LINK incorrectly set in (%d-%d), text: %s\n", end_offset, end_offset+1, buffer);
      ok(buffer[end_offset], "buffer \"%s\" ended prematurely. Is it missing a newline character?\n", buffer);
      if (buffer[end_offset] != 0  && buffer[end_offset+1] != '\0')
      {
        ok(!check_CFE_LINK_selection(hwndRichEdit, end_offset+1, end_offset +2),
          "CFE_LINK incorrectly set in (%d-%d), text: %s\n", end_offset+1, end_offset +2, buffer);
        if (buffer[end_offset +2] != '\0')
        {
          ok(!check_CFE_LINK_selection(hwndRichEdit, end_offset +2, end_offset +3),
            "CFE_LINK incorrectly set in (%d-%d), text: %s\n", end_offset +2, end_offset +3, buffer);
        }
      }

      /* The following will remove the just-inserted paragraph break, thus
         restoring the URL */
      SendMessageA(hwndRichEdit, EM_SETSEL, at_offset+2, at_offset+2);
      simulate_typing_characters(hwndRichEdit, "\b");
      SendMessageA(hwndRichEdit, WM_GETTEXT, sizeof(buffer), (LPARAM)buffer);

      ok(!check_CFE_LINK_selection(hwndRichEdit, 0, 1),
        "CFE_LINK incorrectly set in (%d-%d), text: %s\n", 0, 1, buffer);
      ok(!check_CFE_LINK_selection(hwndRichEdit, at_offset -2, at_offset -1),
        "CFE_LINK incorrectly set in (%d-%d), text: %s\n", at_offset -2, at_offset -1, buffer);
      ok(!check_CFE_LINK_selection(hwndRichEdit, at_offset -1, at_offset),
        "CFE_LINK incorrectly set in (%d-%d), text: %s\n", at_offset -1, at_offset, buffer);

      if (urls[i].is_url)
      {
        ok(check_CFE_LINK_selection(hwndRichEdit, at_offset, at_offset +1),
          "CFE_LINK not set in (%d-%d), text: %s\n", at_offset, at_offset +1, buffer);
        ok(check_CFE_LINK_selection(hwndRichEdit, end_offset -1, end_offset),
          "CFE_LINK not set in (%d-%d), text: %s\n", end_offset -1, end_offset, buffer);
      }
      else
      {
        ok(!check_CFE_LINK_selection(hwndRichEdit, at_offset, at_offset +1),
          "CFE_LINK incorrectly set in (%d-%d), text: %s\n", at_offset, at_offset + 1, buffer);
        ok(!check_CFE_LINK_selection(hwndRichEdit, end_offset -1, end_offset),
          "CFE_LINK incorrectly set in (%d-%d), text: %s\n", end_offset -1, end_offset, buffer);
      }
      if (buffer[end_offset] != '\0')
      {
        ok(!check_CFE_LINK_selection(hwndRichEdit, end_offset, end_offset +1),
          "CFE_LINK incorrectly set in (%d-%d), text: %s\n", end_offset, end_offset + 1, buffer);
        if (buffer[end_offset +1] != '\0')
        {
          ok(!check_CFE_LINK_selection(hwndRichEdit, end_offset +1, end_offset +2),
            "CFE_LINK incorrectly set in (%d-%d), text: %s\n", end_offset +1, end_offset +2, buffer);
        }
      }
    }
    DestroyWindow(hwndRichEdit);
    hwndRichEdit = NULL;
  }

  /* Test detection of URLs within normal text - EM_SETTEXTEX case. */
  /* Test just the first two URL examples for brevity */
  for (i = 0; i < 2; i++) {
    SETTEXTEX st;

    hwndRichEdit = new_richedit(parent);

    /* There are at least three ways in which EM_SETTEXTEX must cause URLs to
       be detected:
       1) Set entire text, a la WM_SETTEXT
       2) Set a selection of the text to the URL
       3) Set a portion of the text at a time, which eventually results in
          an URL
       All of them should give equivalent results
     */

    /* Set entire text in one go, like WM_SETTEXT */
    for (j = 0; j < sizeof(templates_delim) / sizeof(const char *); j++) {
      char * at_pos;
      int at_offset;
      int end_offset;

      st.codepage = CP_ACP;
      st.flags = ST_DEFAULT;

      at_pos = strchr(templates_delim[j], 'X');
      at_offset = at_pos - templates_delim[j];
      memcpy(buffer, templates_delim[j], at_offset);
      buffer[at_offset] = '\0';
      strcat(buffer, urls[i].text);
      strcat(buffer, templates_delim[j] + at_offset + 1);
      end_offset = at_offset + strlen(urls[i].text);

      SendMessageA(hwndRichEdit, EM_AUTOURLDETECT, TRUE, 0);
      SendMessageA(hwndRichEdit, EM_SETTEXTEX, (WPARAM)&st, (LPARAM)buffer);

      /* This assumes no templates start with the URL itself, and that they
         have at least two characters before the URL text */
      ok(!check_CFE_LINK_selection(hwndRichEdit, 0, 1),
        "CFE_LINK incorrectly set in (%d-%d), text: %s\n", 0, 1, buffer);
      ok(!check_CFE_LINK_selection(hwndRichEdit, at_offset -2, at_offset -1),
        "CFE_LINK incorrectly set in (%d-%d), text: %s\n", at_offset -2, at_offset -1, buffer);
      ok(!check_CFE_LINK_selection(hwndRichEdit, at_offset -1, at_offset),
        "CFE_LINK incorrectly set in (%d-%d), text: %s\n", at_offset -1, at_offset, buffer);

      if (urls[i].is_url)
      {
        ok(check_CFE_LINK_selection(hwndRichEdit, at_offset, at_offset +1),
          "CFE_LINK not set in (%d-%d), text: %s\n", at_offset, at_offset +1, buffer);
        ok(check_CFE_LINK_selection(hwndRichEdit, end_offset -1, end_offset),
          "CFE_LINK not set in (%d-%d), text: %s\n", end_offset -1, end_offset, buffer);
      }
      else
      {
        ok(!check_CFE_LINK_selection(hwndRichEdit, at_offset, at_offset +1),
          "CFE_LINK incorrectly set in (%d-%d), text: %s\n", at_offset, at_offset + 1, buffer);
        ok(!check_CFE_LINK_selection(hwndRichEdit, end_offset -1, end_offset),
          "CFE_LINK incorrectly set in (%d-%d), text: %s\n", end_offset -1, end_offset, buffer);
      }
      if (buffer[end_offset] != '\0')
      {
        ok(!check_CFE_LINK_selection(hwndRichEdit, end_offset, end_offset +1),
          "CFE_LINK incorrectly set in (%d-%d), text: %s\n", end_offset, end_offset + 1, buffer);
        if (buffer[end_offset +1] != '\0')
        {
          ok(!check_CFE_LINK_selection(hwndRichEdit, end_offset +1, end_offset +2),
            "CFE_LINK incorrectly set in (%d-%d), text: %s\n", end_offset +1, end_offset +2, buffer);
        }
      }
    }

    /* Set selection with X to the URL */
    for (j = 0; j < sizeof(templates_delim) / sizeof(const char *); j++) {
      char * at_pos;
      int at_offset;
      int end_offset;

      at_pos = strchr(templates_delim[j], 'X');
      at_offset = at_pos - templates_delim[j];
      end_offset = at_offset + strlen(urls[i].text);

      st.codepage = CP_ACP;
      st.flags = ST_DEFAULT;
      SendMessageA(hwndRichEdit, EM_AUTOURLDETECT, TRUE, 0);
      SendMessageA(hwndRichEdit, EM_SETTEXTEX, (WPARAM)&st, (LPARAM)templates_delim[j]);
      st.flags = ST_SELECTION;
      SendMessageA(hwndRichEdit, EM_SETSEL, at_offset, at_offset+1);
      SendMessageA(hwndRichEdit, EM_SETTEXTEX, (WPARAM)&st, (LPARAM)urls[i].text);
      SendMessageA(hwndRichEdit, WM_GETTEXT, sizeof(buffer), (LPARAM)buffer);

      /* This assumes no templates start with the URL itself, and that they
         have at least two characters before the URL text */
      ok(!check_CFE_LINK_selection(hwndRichEdit, 0, 1),
        "CFE_LINK incorrectly set in (%d-%d), text: %s\n", 0, 1, buffer);
      ok(!check_CFE_LINK_selection(hwndRichEdit, at_offset -2, at_offset -1),
        "CFE_LINK incorrectly set in (%d-%d), text: %s\n", at_offset -2, at_offset -1, buffer);
      ok(!check_CFE_LINK_selection(hwndRichEdit, at_offset -1, at_offset),
        "CFE_LINK incorrectly set in (%d-%d), text: %s\n", at_offset -1, at_offset, buffer);

      if (urls[i].is_url)
      {
        ok(check_CFE_LINK_selection(hwndRichEdit, at_offset, at_offset +1),
          "CFE_LINK not set in (%d-%d), text: %s\n", at_offset, at_offset +1, buffer);
        ok(check_CFE_LINK_selection(hwndRichEdit, end_offset -1, end_offset),
          "CFE_LINK not set in (%d-%d), text: %s\n", end_offset -1, end_offset, buffer);
      }
      else
      {
        ok(!check_CFE_LINK_selection(hwndRichEdit, at_offset, at_offset +1),
          "CFE_LINK incorrectly set in (%d-%d), text: %s\n", at_offset, at_offset + 1, buffer);
        ok(!check_CFE_LINK_selection(hwndRichEdit, end_offset -1, end_offset),
          "CFE_LINK incorrectly set in (%d-%d), text: %s\n", end_offset -1, end_offset, buffer);
      }
      if (buffer[end_offset] != '\0')
      {
        ok(!check_CFE_LINK_selection(hwndRichEdit, end_offset, end_offset +1),
          "CFE_LINK incorrectly set in (%d-%d), text: %s\n", end_offset, end_offset + 1, buffer);
        if (buffer[end_offset +1] != '\0')
        {
          ok(!check_CFE_LINK_selection(hwndRichEdit, end_offset +1, end_offset +2),
            "CFE_LINK incorrectly set in (%d-%d), text: %s\n", end_offset +1, end_offset +2, buffer);
        }
      }
    }

    /* Set selection with X to the first character of the URL, then the rest */
    for (j = 0; j < sizeof(templates_delim) / sizeof(const char *); j++) {
      char * at_pos;
      int at_offset;
      int end_offset;

      at_pos = strchr(templates_delim[j], 'X');
      at_offset = at_pos - templates_delim[j];
      end_offset = at_offset + strlen(urls[i].text);

      strcpy(buffer, "YY");
      buffer[0] = urls[i].text[0];

      st.codepage = CP_ACP;
      st.flags = ST_DEFAULT;
      SendMessageA(hwndRichEdit, EM_AUTOURLDETECT, TRUE, 0);
      SendMessageA(hwndRichEdit, EM_SETTEXTEX, (WPARAM)&st, (LPARAM)templates_delim[j]);
      st.flags = ST_SELECTION;
      SendMessageA(hwndRichEdit, EM_SETSEL, at_offset, at_offset+1);
      SendMessageA(hwndRichEdit, EM_SETTEXTEX, (WPARAM)&st, (LPARAM)buffer);
      SendMessageA(hwndRichEdit, EM_SETSEL, at_offset+1, at_offset+2);
      SendMessageA(hwndRichEdit, EM_SETTEXTEX, (WPARAM)&st, (LPARAM)(urls[i].text + 1));
      SendMessageA(hwndRichEdit, WM_GETTEXT, sizeof(buffer), (LPARAM)buffer);

      /* This assumes no templates start with the URL itself, and that they
         have at least two characters before the URL text */
      ok(!check_CFE_LINK_selection(hwndRichEdit, 0, 1),
        "CFE_LINK incorrectly set in (%d-%d), text: %s\n", 0, 1, buffer);
      ok(!check_CFE_LINK_selection(hwndRichEdit, at_offset -2, at_offset -1),
        "CFE_LINK incorrectly set in (%d-%d), text: %s\n", at_offset -2, at_offset -1, buffer);
      ok(!check_CFE_LINK_selection(hwndRichEdit, at_offset -1, at_offset),
        "CFE_LINK incorrectly set in (%d-%d), text: %s\n", at_offset -1, at_offset, buffer);

      if (urls[i].is_url)
      {
        ok(check_CFE_LINK_selection(hwndRichEdit, at_offset, at_offset +1),
          "CFE_LINK not set in (%d-%d), text: %s\n", at_offset, at_offset +1, buffer);
        ok(check_CFE_LINK_selection(hwndRichEdit, end_offset -1, end_offset),
          "CFE_LINK not set in (%d-%d), text: %s\n", end_offset -1, end_offset, buffer);
      }
      else
      {
        ok(!check_CFE_LINK_selection(hwndRichEdit, at_offset, at_offset +1),
          "CFE_LINK incorrectly set in (%d-%d), text: %s\n", at_offset, at_offset + 1, buffer);
        ok(!check_CFE_LINK_selection(hwndRichEdit, end_offset -1, end_offset),
          "CFE_LINK incorrectly set in (%d-%d), text: %s\n", end_offset -1, end_offset, buffer);
      }
      if (buffer[end_offset] != '\0')
      {
        ok(!check_CFE_LINK_selection(hwndRichEdit, end_offset, end_offset +1),
          "CFE_LINK incorrectly set in (%d-%d), text: %s\n", end_offset, end_offset + 1, buffer);
        if (buffer[end_offset +1] != '\0')
        {
          ok(!check_CFE_LINK_selection(hwndRichEdit, end_offset +1, end_offset +2),
            "CFE_LINK incorrectly set in (%d-%d), text: %s\n", end_offset +1, end_offset +2, buffer);
        }
      }
    }

    DestroyWindow(hwndRichEdit);
    hwndRichEdit = NULL;
  }

  /* Test detection of URLs within normal text - EM_REPLACESEL case. */
  /* Test just the first two URL examples for brevity */
  for (i = 0; i < 2; i++) {
    hwndRichEdit = new_richedit(parent);

    /* Set selection with X to the URL */
    for (j = 0; j < sizeof(templates_delim) / sizeof(const char *); j++) {
      char * at_pos;
      int at_offset;
      int end_offset;

      at_pos = strchr(templates_delim[j], 'X');
      at_offset = at_pos - templates_delim[j];
      end_offset = at_offset + strlen(urls[i].text);

      SendMessageA(hwndRichEdit, EM_AUTOURLDETECT, TRUE, 0);
      SendMessageA(hwndRichEdit, WM_SETTEXT, 0, (LPARAM)templates_delim[j]);
      SendMessageA(hwndRichEdit, EM_SETSEL, at_offset, at_offset+1);
      SendMessageA(hwndRichEdit, EM_REPLACESEL, 0, (LPARAM)urls[i].text);
      SendMessageA(hwndRichEdit, WM_GETTEXT, sizeof(buffer), (LPARAM)buffer);

      /* This assumes no templates start with the URL itself, and that they
         have at least two characters before the URL text */
      ok(!check_CFE_LINK_selection(hwndRichEdit, 0, 1),
        "CFE_LINK incorrectly set in (%d-%d), text: %s\n", 0, 1, buffer);
      ok(!check_CFE_LINK_selection(hwndRichEdit, at_offset -2, at_offset -1),
        "CFE_LINK incorrectly set in (%d-%d), text: %s\n", at_offset -2, at_offset -1, buffer);
      ok(!check_CFE_LINK_selection(hwndRichEdit, at_offset -1, at_offset),
        "CFE_LINK incorrectly set in (%d-%d), text: %s\n", at_offset -1, at_offset, buffer);

      if (urls[i].is_url)
      {
        ok(check_CFE_LINK_selection(hwndRichEdit, at_offset, at_offset +1),
          "CFE_LINK not set in (%d-%d), text: %s\n", at_offset, at_offset +1, buffer);
        ok(check_CFE_LINK_selection(hwndRichEdit, end_offset -1, end_offset),
          "CFE_LINK not set in (%d-%d), text: %s\n", end_offset -1, end_offset, buffer);
      }
      else
      {
        ok(!check_CFE_LINK_selection(hwndRichEdit, at_offset, at_offset +1),
          "CFE_LINK incorrectly set in (%d-%d), text: %s\n", at_offset, at_offset + 1, buffer);
        ok(!check_CFE_LINK_selection(hwndRichEdit, end_offset -1, end_offset),
          "CFE_LINK incorrectly set in (%d-%d), text: %s\n", end_offset -1, end_offset, buffer);
      }
      if (buffer[end_offset] != '\0')
      {
        ok(!check_CFE_LINK_selection(hwndRichEdit, end_offset, end_offset +1),
          "CFE_LINK incorrectly set in (%d-%d), text: %s\n", end_offset, end_offset + 1, buffer);
        if (buffer[end_offset +1] != '\0')
        {
          ok(!check_CFE_LINK_selection(hwndRichEdit, end_offset +1, end_offset +2),
            "CFE_LINK incorrectly set in (%d-%d), text: %s\n", end_offset +1, end_offset +2, buffer);
        }
      }
    }

    /* Set selection with X to the first character of the URL, then the rest */
    for (j = 0; j < sizeof(templates_delim) / sizeof(const char *); j++) {
      char * at_pos;
      int at_offset;
      int end_offset;

      at_pos = strchr(templates_delim[j], 'X');
      at_offset = at_pos - templates_delim[j];
      end_offset = at_offset + strlen(urls[i].text);

      strcpy(buffer, "YY");
      buffer[0] = urls[i].text[0];

      SendMessageA(hwndRichEdit, EM_AUTOURLDETECT, TRUE, 0);
      SendMessageA(hwndRichEdit, WM_SETTEXT, 0, (LPARAM)templates_delim[j]);
      SendMessageA(hwndRichEdit, EM_SETSEL, at_offset, at_offset+1);
      SendMessageA(hwndRichEdit, EM_REPLACESEL, 0, (LPARAM)buffer);
      SendMessageA(hwndRichEdit, EM_SETSEL, at_offset+1, at_offset+2);
      SendMessageA(hwndRichEdit, EM_REPLACESEL, 0, (LPARAM)(urls[i].text + 1));
      SendMessageA(hwndRichEdit, WM_GETTEXT, sizeof(buffer), (LPARAM)buffer);

      /* This assumes no templates start with the URL itself, and that they
         have at least two characters before the URL text */
      ok(!check_CFE_LINK_selection(hwndRichEdit, 0, 1),
        "CFE_LINK incorrectly set in (%d-%d), text: %s\n", 0, 1, buffer);
      ok(!check_CFE_LINK_selection(hwndRichEdit, at_offset -2, at_offset -1),
        "CFE_LINK incorrectly set in (%d-%d), text: %s\n", at_offset -2, at_offset -1, buffer);
      ok(!check_CFE_LINK_selection(hwndRichEdit, at_offset -1, at_offset),
        "CFE_LINK incorrectly set in (%d-%d), text: %s\n", at_offset -1, at_offset, buffer);

      if (urls[i].is_url)
      {
        ok(check_CFE_LINK_selection(hwndRichEdit, at_offset, at_offset +1),
          "CFE_LINK not set in (%d-%d), text: %s\n", at_offset, at_offset +1, buffer);
        ok(check_CFE_LINK_selection(hwndRichEdit, end_offset -1, end_offset),
          "CFE_LINK not set in (%d-%d), text: %s\n", end_offset -1, end_offset, buffer);
      }
      else
      {
        ok(!check_CFE_LINK_selection(hwndRichEdit, at_offset, at_offset +1),
          "CFE_LINK incorrectly set in (%d-%d), text: %s\n", at_offset, at_offset + 1, buffer);
        ok(!check_CFE_LINK_selection(hwndRichEdit, end_offset -1, end_offset),
          "CFE_LINK incorrectly set in (%d-%d), text: %s\n", end_offset -1, end_offset, buffer);
      }
      if (buffer[end_offset] != '\0')
      {
        ok(!check_CFE_LINK_selection(hwndRichEdit, end_offset, end_offset +1),
          "CFE_LINK incorrectly set in (%d-%d), text: %s\n", end_offset, end_offset + 1, buffer);
        if (buffer[end_offset +1] != '\0')
        {
          ok(!check_CFE_LINK_selection(hwndRichEdit, end_offset +1, end_offset +2),
            "CFE_LINK incorrectly set in (%d-%d), text: %s\n", end_offset +1, end_offset +2, buffer);
        }
      }
    }

    DestroyWindow(hwndRichEdit);
    hwndRichEdit = NULL;
  }

  DestroyWindow(parent);
}