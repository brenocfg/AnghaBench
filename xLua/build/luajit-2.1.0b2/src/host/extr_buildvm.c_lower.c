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

__attribute__((used)) static const char *lower(char *buf, const char *s)
{
  char *p = buf;
  while (*s) {
    *p++ = (*s >= 'A' && *s <= 'Z') ? *s+0x20 : *s;
    s++;
  }
  *p = '\0';
  return buf;
}