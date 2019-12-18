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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  iso_path_table_t ;

/* Variables and functions */
 int /*<<< orphan*/  cdio_assert (int /*<<< orphan*/ ) ; 
 scalar_t__ from_711 (int /*<<< orphan*/  const) ; 

void
pathtable_get_size_and_entries (const void *pt,
                                unsigned int *size,
                                unsigned int *entries)
{
  const uint8_t *tmp = pt;
  unsigned int offset = 0;
  unsigned int count = 0;

  cdio_assert (pt != NULL);

  while (from_711 (*tmp))
    {
      offset += sizeof (iso_path_table_t);
      offset += from_711 (*tmp);
      if (offset % 2)
        offset++;
      tmp = (uint8_t *)pt + offset;
      count++;
    }

  if (size)
    *size = offset;

  if (entries)
    *entries = count;
}