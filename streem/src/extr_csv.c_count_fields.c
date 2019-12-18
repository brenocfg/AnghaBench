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
typedef  int /*<<< orphan*/  strm_string ;

/* Variables and functions */
 int strm_str_len (int /*<<< orphan*/ ) ; 
 char* strm_str_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
count_fields(strm_string line, char sep)
{
  const char *ptr = strm_str_ptr(line);
  const char *pend = ptr + strm_str_len(line);
  int cnt, quoted = 0;

  for (cnt = 1; ptr<pend; ptr++) {
    if (quoted) {
      if (ptr[0] == '\"') {
        if (ptr[1] == '\"') {
          ptr++;
          continue;
        }
        quoted = 0;
      }
      continue;
    }

    switch(*ptr) {
    case '\"':
      quoted = 1;
      continue;
    case ',':
    case '\t':
      if (*ptr == sep)
        cnt++;
      continue;
    default:
      continue;
    }
  }

  if (quoted)
    return -1;

  return cnt;
}