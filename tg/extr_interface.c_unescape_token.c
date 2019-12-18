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
 int cur_token_len ; 

__attribute__((used)) static void unescape_token (char *start, char *end) {
  static char cur_token_buff[(1 << 20) + 1];
  cur_token_len = 0;
  cur_token = cur_token_buff;
  while (start < end) {
    assert (cur_token_len < (1 << 20));
    switch (*start) {
    case '\\':
      start ++;
      switch (*start) {
      case 'n':
        cur_token[cur_token_len ++] = '\n';
        break;
      case 'r':
        cur_token[cur_token_len ++] = '\r';
        break;
      case 't':
        cur_token[cur_token_len ++] = '\t';
        break;
      case 'b':
        cur_token[cur_token_len ++] = '\b';
        break;
      case 'a':
        cur_token[cur_token_len ++] = '\a';
        break;
      default:
        cur_token[cur_token_len ++] = *start;
        break;
      }
      break;
    default:
      cur_token[cur_token_len ++] = *start;;
      break;
    }
    start ++;
  }
  cur_token[cur_token_len] = 0;
}