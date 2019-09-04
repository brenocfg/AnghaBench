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

void my_ltoa(long __x, char* buf) {
  char rbuf[64];
  char* ptr = rbuf;

  if (__x == 0)
    *ptr++ = '0';
  else {
    for (; __x != 0; __x /= 10)
      *ptr++ = (char)(__x % 10) + '0';
  }
  while(ptr > rbuf) *buf++ = *--ptr;
  /* psw */
  *buf = '\0';
}