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
 long long NOT_FOUND ; 
 char* cur_token ; 
 size_t cur_token_len ; 
 long long strtoll (char*,char**,int /*<<< orphan*/ ) ; 

long long cur_token_int (void) {
  if (cur_token_len <= 0) {
    return NOT_FOUND;
  } else {
    char c = cur_token[cur_token_len];
    cur_token[cur_token_len] = 0;
    char *end = 0;
    long long x = strtoll (cur_token, &end, 0);
    cur_token[cur_token_len] = c;
    if (end != cur_token + cur_token_len) {
      return NOT_FOUND;
    } else {
      return x;
    }
  }
}