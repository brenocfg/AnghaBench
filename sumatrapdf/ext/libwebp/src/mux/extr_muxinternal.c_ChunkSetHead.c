#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WebPMuxError ;
struct TYPE_4__ {int /*<<< orphan*/ * next_; scalar_t__ owner_; } ;
typedef  TYPE_1__ WebPChunk ;

/* Variables and functions */
 int /*<<< orphan*/  WEBP_MUX_MEMORY_ERROR ; 
 int /*<<< orphan*/  WEBP_MUX_NOT_FOUND ; 
 int /*<<< orphan*/  WEBP_MUX_OK ; 
 scalar_t__ WebPSafeMalloc (unsigned long long,int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

WebPMuxError ChunkSetHead(WebPChunk* const chunk,
                          WebPChunk** const chunk_list) {
  WebPChunk* new_chunk;

  assert(chunk_list != NULL);
  if (*chunk_list != NULL) {
    return WEBP_MUX_NOT_FOUND;
  }

  new_chunk = (WebPChunk*)WebPSafeMalloc(1ULL, sizeof(*new_chunk));
  if (new_chunk == NULL) return WEBP_MUX_MEMORY_ERROR;
  *new_chunk = *chunk;
  chunk->owner_ = 0;
  new_chunk->next_ = NULL;
  *chunk_list = new_chunk;
  return WEBP_MUX_OK;
}