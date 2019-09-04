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
typedef  int /*<<< orphan*/  WCHAR ;

/* Variables and functions */

WCHAR * PICE_wcscpy(WCHAR * str1,const WCHAR * str2)
{
  WCHAR *save = str1;

  for (; (*str1 = *str2); ++str2, ++str1);
  return save;
}