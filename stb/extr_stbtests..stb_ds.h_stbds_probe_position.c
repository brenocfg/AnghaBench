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

__attribute__((used)) static size_t stbds_probe_position(size_t hash, size_t slot_count, size_t slot_log2)
{
  size_t pos;
  pos = hash & (slot_count-1);
  #ifdef STBDS_INTERNAL_BUCKET_START
  pos &= ~STBDS_BUCKET_MASK;
  #endif
  return pos;
}