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
typedef  int /*<<< orphan*/  LCID ;

/* Variables and functions */

__attribute__((used)) static LCID LocaleFromHex(const char* locale) {
  unsigned long result = 0;
  int digit;
  while (*locale) {
    result <<= 4;
    digit = (*locale >= '0' && *locale <= '9') ? *locale - '0':
            (*locale >= 'A' && *locale <= 'F') ? (*locale - 'A') + 10
                                               : (*locale - 'a') + 10;
    result += digit;
    ++locale;
  }
  return (LCID)result;
}