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
typedef  int /*<<< orphan*/  iso9660_dir_t ;

/* Variables and functions */

unsigned int
iso9660_dir_calc_record_size(unsigned int namelen, unsigned int su_len)
{
  unsigned int length;

  length = sizeof(iso9660_dir_t);
  length += namelen;
  if (length % 2) /* pad to word boundary */
    length++;
  length += su_len;
  if (length % 2) /* pad to word boundary again */
    length++;

  return length;
}