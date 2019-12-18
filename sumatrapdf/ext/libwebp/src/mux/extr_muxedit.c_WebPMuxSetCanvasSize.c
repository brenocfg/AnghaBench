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
typedef  int uint64_t ;
typedef  scalar_t__ WebPMuxError ;
struct TYPE_5__ {int canvas_width_; int canvas_height_; } ;
typedef  TYPE_1__ WebPMux ;
struct TYPE_6__ {int /*<<< orphan*/  tag; } ;

/* Variables and functions */
 size_t IDX_VP8X ; 
 int MAX_CANVAS_SIZE ; 
 int MAX_IMAGE_AREA ; 
 scalar_t__ MuxDeleteAllNamedData (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ WEBP_MUX_INVALID_ARGUMENT ; 
 scalar_t__ WEBP_MUX_NOT_FOUND ; 
 scalar_t__ WEBP_MUX_OK ; 
 TYPE_2__* kChunks ; 

WebPMuxError WebPMuxSetCanvasSize(WebPMux* mux,
                                  int width, int height) {
  WebPMuxError err;
  if (mux == NULL) {
    return WEBP_MUX_INVALID_ARGUMENT;
  }
  if (width < 0 || height < 0 ||
      width > MAX_CANVAS_SIZE || height > MAX_CANVAS_SIZE) {
    return WEBP_MUX_INVALID_ARGUMENT;
  }
  if (width * (uint64_t)height >= MAX_IMAGE_AREA) {
    return WEBP_MUX_INVALID_ARGUMENT;
  }
  if ((width * height) == 0 && (width | height) != 0) {
    // one of width / height is zero, but not both -> invalid!
    return WEBP_MUX_INVALID_ARGUMENT;
  }
  // If we already assembled a VP8X chunk, invalidate it.
  err = MuxDeleteAllNamedData(mux, kChunks[IDX_VP8X].tag);
  if (err != WEBP_MUX_OK && err != WEBP_MUX_NOT_FOUND) return err;

  mux->canvas_width_ = width;
  mux->canvas_height_ = height;
  return WEBP_MUX_OK;
}