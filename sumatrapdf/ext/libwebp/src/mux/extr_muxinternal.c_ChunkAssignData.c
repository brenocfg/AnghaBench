#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  WebPMuxError ;
typedef  int /*<<< orphan*/  WebPData ;
struct TYPE_5__ {int owner_; scalar_t__ tag_; int /*<<< orphan*/  data_; } ;
typedef  TYPE_1__ WebPChunk ;
struct TYPE_6__ {scalar_t__ tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  ChunkRelease (TYPE_1__*) ; 
 size_t IDX_ANIM ; 
 size_t IDX_VP8X ; 
 int /*<<< orphan*/  WEBP_MUX_MEMORY_ERROR ; 
 int /*<<< orphan*/  WEBP_MUX_OK ; 
 int /*<<< orphan*/  WebPDataCopy (int /*<<< orphan*/  const* const,int /*<<< orphan*/ *) ; 
 TYPE_2__* kChunks ; 

WebPMuxError ChunkAssignData(WebPChunk* chunk, const WebPData* const data,
                             int copy_data, uint32_t tag) {
  // For internally allocated chunks, always copy data & make it owner of data.
  if (tag == kChunks[IDX_VP8X].tag || tag == kChunks[IDX_ANIM].tag) {
    copy_data = 1;
  }

  ChunkRelease(chunk);

  if (data != NULL) {
    if (copy_data) {        // Copy data.
      if (!WebPDataCopy(data, &chunk->data_)) return WEBP_MUX_MEMORY_ERROR;
      chunk->owner_ = 1;    // Chunk is owner of data.
    } else {                // Don't copy data.
      chunk->data_ = *data;
    }
  }
  chunk->tag_ = tag;
  return WEBP_MUX_OK;
}