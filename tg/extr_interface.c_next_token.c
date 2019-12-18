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

/* Variables and functions */
 char* cur_token ; 
 int cur_token_end_str ; 
 int cur_token_len ; 
 int cur_token_quoted ; 
 int /*<<< orphan*/  force_end_mode ; 
 char* line_ptr ; 
 int /*<<< orphan*/  skip_wspc () ; 
 int /*<<< orphan*/  unescape_token (char*,char*) ; 

__attribute__((used)) static void next_token (void) {
  skip_wspc ();
  cur_token_end_str = 0;
  cur_token_quoted = 0;
  if (!*line_ptr) {
    cur_token_len = 0;
    cur_token_end_str = 1;
    return;
  }
  char c = *line_ptr;
  char *start = line_ptr;
  if (c == '"' || c == '\'') {
    cur_token_quoted = 1;
    line_ptr ++;
    int esc = 0;
    while (*line_ptr && (esc || *line_ptr != c)) {
      if (*line_ptr == '\\') {
        esc = 1 - esc;
      } else {
        esc = 0;
      }
      line_ptr ++;
    }
    if (!*line_ptr) {
      cur_token_len = -2;
    } else {
      unescape_token (start + 1, line_ptr);
      line_ptr ++;
    }
  } else {
    while (*line_ptr && ((unsigned char)*line_ptr) > ' ') {
      line_ptr ++;
    }
    cur_token = start;
    cur_token_len = line_ptr - start;
    cur_token_end_str = (!force_end_mode) && (*line_ptr == 0);
  }
}