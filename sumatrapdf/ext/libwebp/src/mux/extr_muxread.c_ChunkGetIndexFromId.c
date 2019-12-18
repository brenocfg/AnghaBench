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
typedef  scalar_t__ WebPChunkId ;
struct TYPE_2__ {scalar_t__ id; } ;
typedef  int /*<<< orphan*/  CHUNK_INDEX ;

/* Variables and functions */
 int /*<<< orphan*/  IDX_NIL ; 
 scalar_t__ WEBP_CHUNK_NIL ; 
 TYPE_1__* kChunks ; 

__attribute__((used)) static CHUNK_INDEX ChunkGetIndexFromId(WebPChunkId id) {
  int i;
  for (i = 0; kChunks[i].id != WEBP_CHUNK_NIL; ++i) {
    if (id == kChunks[i].id) return (CHUNK_INDEX)i;
  }
  return IDX_NIL;
}