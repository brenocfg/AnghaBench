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

__attribute__((used)) static int __ConvertTime(const char *NTTime, char *buffer, int buf_size) {
  const char *cur_char;
  char *cur_output, *end_output;
  cur_char = NTTime;
  cur_output = buffer;
  end_output = cur_output + buf_size;
  buf_size = 0;
  while (*cur_char) {
    switch(*cur_char) {
    case 'h':
      if (*(cur_char + 1) == 'h') {
        if (cur_output && (cur_output + 2 > end_output)) {
          *cur_output = 0;
          return ++buf_size;
        }
        if (cur_output) { *(cur_output++) = '%'; *(cur_output++) = 'I'; }
        buf_size += 2;
        ++cur_char;
      }
      else {
        if (cur_output && (cur_output + 3 > end_output)) {
          *cur_output = 0;
          return ++buf_size;
        }
        if (cur_output) { *(cur_output++) = '%'; *(cur_output++) = '#'; *(cur_output++) = 'I'; }
        buf_size += 3;
      }
      break;
    case 'H':
      if (*(cur_char + 1) == 'H') {
        if (cur_output && (cur_output + 2 > end_output)) {
          *cur_output = 0;
          return ++buf_size;
        }
        if (cur_output) { *(cur_output++) = '%'; *(cur_output++) = 'H'; }
        buf_size += 2;
        ++cur_char;
      }
      else {
        if (cur_output && (cur_output + 3 > end_output)) {
          *cur_output = 0;
          return ++buf_size;
        }
        if (cur_output) { *(cur_output++) = '%'; *(cur_output++) = '#'; *(cur_output++) = 'H'; }
        buf_size += 3;
      }
      break;
    case 'm':
      if (*(cur_char + 1) == 'm') {
        if (cur_output && (cur_output + 2 > end_output)) {
          *cur_output = 0;
          return ++buf_size;
        }
        if (cur_output) { *(cur_output++) = '%'; *(cur_output++) = 'M'; }
        buf_size += 2;
        cur_char++;
      }
      else {
        if (cur_output && (cur_output + 3 > end_output)) {
          *cur_output = 0;
          return ++buf_size;
        }
        if (cur_output) { *(cur_output++) = '%'; *(cur_output++) = '#'; *(cur_output++) = 'M'; }
        buf_size += 3;
      }
      break;
    case 's':
      if (*(cur_char + 1) == 's') {
        if (cur_output && (cur_output + 2 > end_output)) {
          *cur_output = 0;
          return ++buf_size;
        }
        if (cur_output) { *(cur_output++) = '%'; *(cur_output++) = 'S'; }
        buf_size += 2;
        ++cur_char;
      }
      else {
        if (cur_output && (cur_output + 3 > end_output)) {
          *cur_output = 0;
          return ++buf_size;
        }
        if (cur_output) { *(cur_output++) = '%'; *(cur_output++) = '#'; *(cur_output++) = 'S'; }
        buf_size += 3;
      }
      break;
    case 't':
      if (*(cur_char + 1) == 't')
        ++cur_char;
      if (cur_output && (cur_output + 2 > end_output)) {
        *cur_output = 0;
        return ++buf_size;
      }
      if (cur_output) { *(cur_output++) = '%'; *(cur_output++) = 'p'; }
      buf_size += 2;
      break;
    case '%':
      if (cur_output && (cur_output + 2 > end_output)) {
        *cur_output = 0;
        return ++buf_size;
      }
      if (cur_output) { *(cur_output++)='%'; *(cur_output++)='%'; }
      buf_size += 2;
      break;
    case '\'':
      ++cur_char;
      while (*cur_char != '\'' && *cur_char != 0 && (!cur_output || (cur_output != end_output))) {
        if (cur_output) *cur_output++ = *cur_char;
        ++cur_char;
        buf_size += 1;
      }
      break;
    default:
      if (cur_output) { *(cur_output++) = *cur_char; }
      buf_size += 1;
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