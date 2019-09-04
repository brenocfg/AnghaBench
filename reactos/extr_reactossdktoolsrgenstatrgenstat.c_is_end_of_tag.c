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

__attribute__((used)) static int
is_end_of_tag(char ch)
{
  if ((ch >= 'a') && (ch <= 'z'))
    {
      return 0;
    }
  if ((ch >= 'A') && (ch <= 'Z'))
    {
      return 0;
    }
  if ((ch >= '0') && (ch <= '9'))
    {
      return 0;
    }
  if (ch == '_')
    {
      return 0;
    }
  return 1;
}