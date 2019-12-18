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
 int /*<<< orphan*/  cdio_assert (int /*<<< orphan*/ ) ; 

size_t
_cdio_strlenv(char **str_array)
{
  size_t n = 0;

  cdio_assert (str_array != NULL);

  while(str_array[n])
    n++;

  return n;
}