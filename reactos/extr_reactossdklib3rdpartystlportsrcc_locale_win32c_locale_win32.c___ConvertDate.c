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

__attribute__((used)) static int __ConvertDate(const char *NTDate, char *buffer, int buf_size) {
  /* This function will return an incomplete buffer if buffer is not long enough */
  const char *cur_char;
  char *cur_output, *end_output;

  /* Correct time format. */
  cur_char = NTDate;
  cur_output = buffer;
  end_output = cur_output + buf_size;
  buf_size = 0;
  while (*cur_char) {
    if (cur_output && (cur_output == end_output)) break;
    switch (*cur_char) {
    case 'd':
    {
      if (*(cur_char + 1) == 'd') {
        if (cur_output && (cur_output + 2 > end_output)) {
          *cur_output = 0;
          return ++buf_size;
        }
        if (*(cur_char + 2) == 'd') {
          if (*(cur_char + 3) == 'd') {
            if (cur_output) { *(cur_output++) = '%'; *(cur_output++) = 'A'; }
            buf_size += 2;
            cur_char += 3;
          }
          else {
            if (cur_output) { *(cur_output++) = '%'; *(cur_output++) = 'a'; }
            buf_size += 2;
            cur_char += 2;
          }
        }
        else {
          if (cur_output) { *(cur_output++) = '%'; *(cur_output++) = 'd'; }
          buf_size += 2;
          cur_char++;
        }
      }
      else {
        if (cur_output && (cur_output + 3 > end_output)) {
          *cur_output = 0;
          return ++buf_size;
        }
        if (cur_output) { *(cur_output++) = '%'; *(cur_output++) = '#'; *(cur_output++) = 'd'; }
        buf_size += 3;
      }
    }
    break;
    case 'M':
    {
      if (*(cur_char + 1) == 'M') {
        if (cur_output && (cur_output + 2 > end_output)) {
          *cur_output = 0;
          return ++buf_size;
        }
        if (*(cur_char + 2) == 'M') {
          if (*(cur_char + 3) == 'M') {
            if (cur_output) { *(cur_output++) = '%'; *(cur_output++) = 'B'; }
            buf_size += 2;
            cur_char += 3;
          }
          else {
            if (cur_output) { *(cur_output++) = '%'; *(cur_output++) = 'b'; }
            buf_size += 2;
            cur_char += 2;
          }
        }
        else {
          if (cur_output) { *(cur_output++) = '%'; *(cur_output++) = 'm'; }
          buf_size += 2;
          cur_char++;
        }
      }
      else {
        if (cur_output && (cur_output + 3 > end_output)) {
          *cur_output = 0;
          return ++buf_size;
        }
        if (cur_output) { *(cur_output++) = '%'; *(cur_output++) = '#'; *(cur_output++) = 'm'; }
        buf_size += 3;
      }
    }
    break;
    case 'y':
    {
      if (*(cur_char + 1) == 'y') {
        if (cur_output && (cur_output + 2 > end_output)) {
          *cur_output = 0;
          return ++buf_size;
        }
        if (*(cur_char + 2) == 'y' && *(cur_char + 3) == 'y') {
          if (cur_output) { *(cur_output++) = '%'; *(cur_output++) = 'Y'; }
          buf_size += 2;
          cur_char += 3;
        }
        else {
          if (cur_output) { *(cur_output++) = '%'; *(cur_output++) = 'y'; }
          buf_size += 2;
          cur_char++;
        }
      }
      else {
        if (cur_output && (cur_output + 3 > end_output)) {
          *cur_output = 0;
          return ++buf_size;
        }
        if (cur_output) { *(cur_output++) = '%'; *(cur_output++) = '#'; *(cur_output++) = 'y'; }
        buf_size += 3;
      }
    }
    break;
    case '%':
    {
      if (cur_output && (cur_output + 2 > end_output)) {
        *cur_output = 0;
        return ++buf_size;
      }
      if (cur_output) { *(cur_output++) = '%'; *(cur_output++) = '%'; }
      buf_size += 2;
    }
    break;
    case '\'':
    {
      ++cur_char;
      while (*cur_char != '\'' && *cur_char != 0 && (cur_output == NULL || cur_output != end_output)) {
        if (cur_output) { *cur_output++ = *cur_char; }
        ++cur_char;
        buf_size += 1;
      }
    }
    break;
    default:
    {
      if (cur_output) { *(cur_output++) = *cur_char; }
      buf_size += 1;
    }
    break;
    }
    if (*cur_char == 0) break;
    ++cur_char;
  }

  if (!cur_output || cur_output != end_output) {
    if (cur_output) *cur_output = 0;
    buf_size += 1;
  }
  else {
    /* We trunc result */
    *(--cur_output) = 0;
  }

  return buf_size;
}