#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WebPMuxError ;
struct TYPE_7__ {int /*<<< orphan*/  unknown_; } ;
typedef  TYPE_1__ WebPMux ;
typedef  int /*<<< orphan*/  WebPData ;
struct TYPE_8__ {int /*<<< orphan*/  data_; } ;
typedef  TYPE_2__ WebPChunk ;
struct TYPE_9__ {int /*<<< orphan*/  id; } ;
typedef  size_t CHUNK_INDEX ;

/* Variables and functions */
 size_t ChunkGetIndexFromFourCC (char const*) ; 
 int /*<<< orphan*/  ChunkGetTagFromFourCC (char const*) ; 
 TYPE_2__* ChunkSearchList (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 size_t IDX_UNKNOWN ; 
 scalar_t__ IsWPI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MuxGet (TYPE_1__ const*,size_t,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WEBP_MUX_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  WEBP_MUX_NOT_FOUND ; 
 int /*<<< orphan*/  WEBP_MUX_OK ; 
 TYPE_3__* kChunks ; 

WebPMuxError WebPMuxGetChunk(const WebPMux* mux, const char fourcc[4],
                             WebPData* chunk_data) {
  CHUNK_INDEX idx;
  if (mux == NULL || fourcc == NULL || chunk_data == NULL) {
    return WEBP_MUX_INVALID_ARGUMENT;
  }
  idx = ChunkGetIndexFromFourCC(fourcc);
  if (IsWPI(kChunks[idx].id)) {     // An image chunk.
    return WEBP_MUX_INVALID_ARGUMENT;
  } else if (idx != IDX_UNKNOWN) {  // A known chunk type.
    return MuxGet(mux, idx, 1, chunk_data);
  } else {                          // An unknown chunk type.
    const WebPChunk* const chunk =
        ChunkSearchList(mux->unknown_, 1, ChunkGetTagFromFourCC(fourcc));
    if (chunk == NULL) return WEBP_MUX_NOT_FOUND;
    *chunk_data = chunk->data_;
    return WEBP_MUX_OK;
  }
}