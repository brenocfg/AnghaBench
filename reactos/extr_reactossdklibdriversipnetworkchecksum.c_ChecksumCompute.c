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
typedef  scalar_t__ ULONG_PTR ;
typedef  int /*<<< orphan*/  ULONG ;
typedef  int UINT ;
typedef  scalar_t__ PVOID ;
typedef  scalar_t__* PUSHORT ;
typedef  scalar_t__* PUCHAR ;

/* Variables and functions */

ULONG ChecksumCompute(
  PVOID Data,
  UINT Count,
  ULONG Seed)
/*
 * FUNCTION: Calculate checksum of a buffer
 * ARGUMENTS:
 *     Data  = Pointer to buffer with data
 *     Count = Number of bytes in buffer
 *     Seed  = Previously calculated checksum (if any)
 * RETURNS:
 *     Checksum of buffer
 */
{
  register ULONG Sum = Seed;

  while (Count > 1)
    {
      Sum += *(PUSHORT)Data;
      Count -= 2;
      Data = (PVOID)((ULONG_PTR) Data + 2);
    }

  /* Add left-over byte, if any */
  if (Count > 0)
    {
      Sum += *(PUCHAR)Data;
    }

  return Sum;
}