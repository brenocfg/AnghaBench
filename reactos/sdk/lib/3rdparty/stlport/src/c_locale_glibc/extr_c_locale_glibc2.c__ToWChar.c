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
typedef  char wchar_t ;

/* Variables and functions */

__attribute__((used)) static wchar_t* _ToWChar(const char* buf, wchar_t *wbuf, size_t wbufSize) {
  wchar_t *wcur = wbuf;
  wchar_t *wend = wbuf + wbufSize - 1;
  for (; wcur != wend && *buf != 0; ++buf, ++wcur)
    *wcur = *buf;
  *wcur = 0;
  return wbuf;
}