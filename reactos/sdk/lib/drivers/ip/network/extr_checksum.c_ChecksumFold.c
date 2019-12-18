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
typedef  int ULONG ;

/* Variables and functions */

ULONG ChecksumFold(
  ULONG Sum)
{
  /* Fold 32-bit sum to 16 bits */
  while (Sum >> 16)
    {
      Sum = (Sum & 0xFFFF) + (Sum >> 16);
    }

  return Sum;
}