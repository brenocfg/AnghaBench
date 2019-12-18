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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  CHUNK_INDEX ;

/* Variables and functions */
 int /*<<< orphan*/  ChunkGetIndexFromTag (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ChunkGetTagFromFourCC (char const*) ; 

CHUNK_INDEX ChunkGetIndexFromFourCC(const char fourcc[4]) {
  const uint32_t tag = ChunkGetTagFromFourCC(fourcc);
  return ChunkGetIndexFromTag(tag);
}