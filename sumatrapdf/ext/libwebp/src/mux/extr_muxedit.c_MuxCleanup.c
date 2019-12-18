#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_9__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ width_; scalar_t__ height_; TYPE_9__* header_; } ;
typedef  TYPE_1__ WebPMuxImage ;
typedef  scalar_t__ WebPMuxError ;
struct TYPE_11__ {scalar_t__ canvas_width_; scalar_t__ canvas_height_; int /*<<< orphan*/  images_; } ;
typedef  TYPE_2__ WebPMux ;
struct TYPE_13__ {scalar_t__ tag_; } ;
struct TYPE_12__ {scalar_t__ tag; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ChunkDelete (TYPE_9__*) ; 
 size_t IDX_ANIM ; 
 size_t IDX_ANMF ; 
 scalar_t__ MuxDeleteAllNamedData (TYPE_2__* const,scalar_t__) ; 
 scalar_t__ MuxImageGetNth (TYPE_1__ const**,int,TYPE_1__**) ; 
 scalar_t__ WEBP_MUX_OK ; 
 scalar_t__ WebPMuxNumChunks (TYPE_2__* const,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_3__* kChunks ; 

__attribute__((used)) static WebPMuxError MuxCleanup(WebPMux* const mux) {
  int num_frames;
  int num_anim_chunks;

  // If we have an image with a single frame, and its rectangle
  // covers the whole canvas, convert it to a non-animated image
  // (to avoid writing ANMF chunk unnecessarily).
  WebPMuxError err = WebPMuxNumChunks(mux, kChunks[IDX_ANMF].id, &num_frames);
  if (err != WEBP_MUX_OK) return err;
  if (num_frames == 1) {
    WebPMuxImage* frame = NULL;
    err = MuxImageGetNth((const WebPMuxImage**)&mux->images_, 1, &frame);
    assert(err == WEBP_MUX_OK);  // We know that one frame does exist.
    assert(frame != NULL);
    if (frame->header_ != NULL &&
        ((mux->canvas_width_ == 0 && mux->canvas_height_ == 0) ||
         (frame->width_ == mux->canvas_width_ &&
          frame->height_ == mux->canvas_height_))) {
      assert(frame->header_->tag_ == kChunks[IDX_ANMF].tag);
      ChunkDelete(frame->header_);  // Removes ANMF chunk.
      frame->header_ = NULL;
      num_frames = 0;
    }
  }
  // Remove ANIM chunk if this is a non-animated image.
  err = WebPMuxNumChunks(mux, kChunks[IDX_ANIM].id, &num_anim_chunks);
  if (err != WEBP_MUX_OK) return err;
  if (num_anim_chunks >= 1 && num_frames == 0) {
    err = MuxDeleteAllNamedData(mux, kChunks[IDX_ANIM].tag);
    if (err != WEBP_MUX_OK) return err;
  }
  return WEBP_MUX_OK;
}