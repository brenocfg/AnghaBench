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
typedef  char WCHAR ;

/* Variables and functions */

__attribute__((used)) static const WCHAR *string_binding_find_delimiterW(
    const WCHAR *string_binding, WCHAR delim)
{
  const WCHAR *next;
  for (next = string_binding; *next; next++) {
    if (*next == '\\') {
      next++;
      continue;
    }
    if (*next == delim)
      return next;
  }
  return NULL;
}