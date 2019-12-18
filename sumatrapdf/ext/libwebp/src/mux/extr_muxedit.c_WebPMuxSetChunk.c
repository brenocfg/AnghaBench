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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ WebPMuxError ;
typedef  int /*<<< orphan*/  WebPMux ;
struct TYPE_4__ {scalar_t__ size; int /*<<< orphan*/ * bytes; } ;
typedef  TYPE_1__ WebPData ;

/* Variables and functions */
 int /*<<< orphan*/  ChunkGetTagFromFourCC (char const*) ; 
 scalar_t__ MAX_CHUNK_PAYLOAD ; 
 scalar_t__ MuxDeleteAllNamedData (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ MuxSet (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__ const*,int) ; 
 scalar_t__ WEBP_MUX_INVALID_ARGUMENT ; 
 scalar_t__ WEBP_MUX_NOT_FOUND ; 
 scalar_t__ WEBP_MUX_OK ; 

WebPMuxError WebPMuxSetChunk(WebPMux* mux, const char fourcc[4],
                             const WebPData* chunk_data, int copy_data) {
  uint32_t tag;
  WebPMuxError err;
  if (mux == NULL || fourcc == NULL || chunk_data == NULL ||
      chunk_data->bytes == NULL || chunk_data->size > MAX_CHUNK_PAYLOAD) {
    return WEBP_MUX_INVALID_ARGUMENT;
  }
  tag = ChunkGetTagFromFourCC(fourcc);

  // Delete existing chunk(s) with the same 'fourcc'.
  err = MuxDeleteAllNamedData(mux, tag);
  if (err != WEBP_MUX_OK && err != WEBP_MUX_NOT_FOUND) return err;

  // Add the given chunk.
  return MuxSet(mux, tag, chunk_data, copy_data);
}