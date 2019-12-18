#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* next_; } ;
typedef  TYPE_1__ WebPMuxImage ;
typedef  int /*<<< orphan*/  const WebPChunkId ;
struct TYPE_7__ {int /*<<< orphan*/  tag_; } ;
typedef  TYPE_2__ WebPChunk ;

/* Variables and functions */
 int /*<<< orphan*/  const ChunkGetIdFromTag (int /*<<< orphan*/ ) ; 
 TYPE_2__** GetChunkListFromId (TYPE_1__ const*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  const WEBP_CHUNK_NIL ; 

int MuxImageCount(const WebPMuxImage* wpi_list, WebPChunkId id) {
  int count = 0;
  const WebPMuxImage* current;
  for (current = wpi_list; current != NULL; current = current->next_) {
    if (id == WEBP_CHUNK_NIL) {
      ++count;  // Special case: count all images.
    } else {
      const WebPChunk* const wpi_chunk = *GetChunkListFromId(current, id);
      if (wpi_chunk != NULL) {
        const WebPChunkId wpi_chunk_id = ChunkGetIdFromTag(wpi_chunk->tag_);
        if (wpi_chunk_id == id) ++count;  // Count images with a matching 'id'.
      }
    }
  }
  return count;
}