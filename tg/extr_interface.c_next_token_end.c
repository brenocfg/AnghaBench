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
 int /*<<< orphan*/  assert (int) ; 
 char* cur_token ; 
 int cur_token_end_str ; 
 int cur_token_len ; 
 scalar_t__ cur_token_quoted ; 
 int /*<<< orphan*/  force_end_mode ; 
 char* line_ptr ; 
 int /*<<< orphan*/  next_token () ; 
 int /*<<< orphan*/  skip_wspc () ; 

void next_token_end (void) {
  skip_wspc ();
  
  if (*line_ptr && *line_ptr != '"' && *line_ptr != '\'') {
    cur_token_quoted = 0;
    cur_token = line_ptr;
    while (*line_ptr) { line_ptr ++; }
    cur_token_len = line_ptr - cur_token;
    while (((unsigned char)cur_token[cur_token_len - 1]) <= ' ' && cur_token_len >= 0) { 
      cur_token_len --;
    }
    assert (cur_token_len > 0);
    cur_token_end_str = !force_end_mode;
    return;
  } else {
    if (*line_ptr) {
      next_token ();
      skip_wspc ();
      if (*line_ptr) {
        cur_token_len = -1; 
      }
    } else {
      next_token ();
    }
  }
}