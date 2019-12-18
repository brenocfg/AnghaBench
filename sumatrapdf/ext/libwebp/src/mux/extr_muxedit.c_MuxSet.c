#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  WebPMuxError ;
struct TYPE_4__ {int /*<<< orphan*/  unknown_; int /*<<< orphan*/  xmp_; int /*<<< orphan*/  exif_; int /*<<< orphan*/  anim_; int /*<<< orphan*/  iccp_; int /*<<< orphan*/  vp8x_; } ;
typedef  TYPE_1__ WebPMux ;
typedef  int /*<<< orphan*/  WebPData ;
typedef  int /*<<< orphan*/  WebPChunk ;
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
typedef  size_t CHUNK_INDEX ;

/* Variables and functions */
 size_t ChunkGetIndexFromTag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ChunkInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDX_ANIM ; 
 int /*<<< orphan*/  IDX_EXIF ; 
 int /*<<< orphan*/  IDX_ICCP ; 
 int /*<<< orphan*/  IDX_UNKNOWN ; 
 int /*<<< orphan*/  IDX_VP8X ; 
 int /*<<< orphan*/  IDX_XMP ; 
 int /*<<< orphan*/  IsWPI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SWITCH_ID_LIST (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WEBP_MUX_NOT_FOUND ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__* kChunks ; 

__attribute__((used)) static WebPMuxError MuxSet(WebPMux* const mux, uint32_t tag,
                           const WebPData* const data, int copy_data) {
  WebPChunk chunk;
  WebPMuxError err = WEBP_MUX_NOT_FOUND;
  const CHUNK_INDEX idx = ChunkGetIndexFromTag(tag);
  assert(mux != NULL);
  assert(!IsWPI(kChunks[idx].id));

  ChunkInit(&chunk);
  SWITCH_ID_LIST(IDX_VP8X,    &mux->vp8x_);
  SWITCH_ID_LIST(IDX_ICCP,    &mux->iccp_);
  SWITCH_ID_LIST(IDX_ANIM,    &mux->anim_);
  SWITCH_ID_LIST(IDX_EXIF,    &mux->exif_);
  SWITCH_ID_LIST(IDX_XMP,     &mux->xmp_);
  SWITCH_ID_LIST(IDX_UNKNOWN, &mux->unknown_);
  return err;
}