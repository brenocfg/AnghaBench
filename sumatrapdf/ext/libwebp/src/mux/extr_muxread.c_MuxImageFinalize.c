#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int width_; int height_; int has_alpha_; int /*<<< orphan*/ * alpha_; TYPE_3__* img_; } ;
typedef  TYPE_1__ WebPMuxImage ;
struct TYPE_7__ {int /*<<< orphan*/  size; int /*<<< orphan*/  bytes; } ;
typedef  TYPE_2__ WebPData ;
struct TYPE_8__ {scalar_t__ tag_; TYPE_2__ data_; } ;
typedef  TYPE_3__ WebPChunk ;
struct TYPE_9__ {scalar_t__ tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  ChunkDelete (int /*<<< orphan*/ *) ; 
 size_t IDX_VP8L ; 
 int VP8GetInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int VP8LGetInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*,int*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_4__* kChunks ; 

int MuxImageFinalize(WebPMuxImage* const wpi) {
  const WebPChunk* const img = wpi->img_;
  const WebPData* const image = &img->data_;
  const int is_lossless = (img->tag_ == kChunks[IDX_VP8L].tag);
  int w, h;
  int vp8l_has_alpha = 0;
  const int ok = is_lossless ?
      VP8LGetInfo(image->bytes, image->size, &w, &h, &vp8l_has_alpha) :
      VP8GetInfo(image->bytes, image->size, image->size, &w, &h);
  assert(img != NULL);
  if (ok) {
    // Ignore ALPH chunk accompanying VP8L.
    if (is_lossless && (wpi->alpha_ != NULL)) {
      ChunkDelete(wpi->alpha_);
      wpi->alpha_ = NULL;
    }
    wpi->width_ = w;
    wpi->height_ = h;
    wpi->has_alpha_ = vp8l_has_alpha || (wpi->alpha_ != NULL);
  }
  return ok;
}