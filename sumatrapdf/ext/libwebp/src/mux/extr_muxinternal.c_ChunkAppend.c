#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WebPMuxError ;
struct TYPE_6__ {struct TYPE_6__* next_; } ;
typedef  TYPE_1__ WebPChunk ;

/* Variables and functions */
 int /*<<< orphan*/  ChunkSetHead (TYPE_1__* const,TYPE_1__**) ; 
 int /*<<< orphan*/  WEBP_MUX_OK ; 
 int /*<<< orphan*/  assert (int) ; 

WebPMuxError ChunkAppend(WebPChunk* const chunk,
                         WebPChunk*** const chunk_list) {
  assert(chunk_list != NULL && *chunk_list != NULL);

  if (**chunk_list == NULL) {
    ChunkSetHead(chunk, *chunk_list);
  } else {
    WebPChunk* last_chunk = **chunk_list;
    while (last_chunk->next_ != NULL) last_chunk = last_chunk->next_;
    ChunkSetHead(chunk, &last_chunk->next_);
    *chunk_list = &last_chunk->next_;
  }
  return WEBP_MUX_OK;
}