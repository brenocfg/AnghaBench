#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  WebPChunkId ;
struct TYPE_2__ {scalar_t__ tag; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 scalar_t__ NIL_TAG ; 
 int /*<<< orphan*/  WEBP_CHUNK_UNKNOWN ; 
 TYPE_1__* kChunks ; 

WebPChunkId ChunkGetIdFromTag(uint32_t tag) {
  int i;
  for (i = 0; kChunks[i].tag != NIL_TAG; ++i) {
    if (tag == kChunks[i].tag) return kChunks[i].id;
  }
  return WEBP_CHUNK_UNKNOWN;
}