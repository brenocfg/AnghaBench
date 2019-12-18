#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_8__ {int width_; int height_; scalar_t__ has_alpha_; } ;
typedef  TYPE_1__ WebPMuxImage ;
typedef  scalar_t__ WebPMuxError ;
struct TYPE_9__ {int canvas_width_; int canvas_height_; TYPE_1__* images_; } ;
typedef  TYPE_2__ WebPMux ;
struct TYPE_10__ {scalar_t__ size; scalar_t__ bytes; } ;
typedef  TYPE_3__ WebPData ;

/* Variables and functions */
 int /*<<< orphan*/  ALPHA_FLAG ; 
 int GetLE24 (scalar_t__) ; 
 int /*<<< orphan*/  GetLE32 (scalar_t__) ; 
 int /*<<< orphan*/  IDX_VP8X ; 
 int MAX_IMAGE_AREA ; 
 scalar_t__ MuxGet (TYPE_2__ const* const,int /*<<< orphan*/ ,int,TYPE_3__*) ; 
 scalar_t__ VP8X_CHUNK_SIZE ; 
 scalar_t__ ValidateForSingleImage (TYPE_2__ const* const) ; 
 scalar_t__ WEBP_MUX_BAD_DATA ; 
 scalar_t__ WEBP_MUX_OK ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static WebPMuxError MuxGetCanvasInfo(const WebPMux* const mux,
                                     int* width, int* height, uint32_t* flags) {
  int w, h;
  uint32_t f = 0;
  WebPData data;
  assert(mux != NULL);

  // Check if VP8X chunk is present.
  if (MuxGet(mux, IDX_VP8X, 1, &data) == WEBP_MUX_OK) {
    if (data.size < VP8X_CHUNK_SIZE) return WEBP_MUX_BAD_DATA;
    f = GetLE32(data.bytes + 0);
    w = GetLE24(data.bytes + 4) + 1;
    h = GetLE24(data.bytes + 7) + 1;
  } else {
    const WebPMuxImage* const wpi = mux->images_;
    // Grab user-forced canvas size as default.
    w = mux->canvas_width_;
    h = mux->canvas_height_;
    if (w == 0 && h == 0 && ValidateForSingleImage(mux) == WEBP_MUX_OK) {
      // single image and not forced canvas size => use dimension of first frame
      assert(wpi != NULL);
      w = wpi->width_;
      h = wpi->height_;
    }
    if (wpi != NULL) {
      if (wpi->has_alpha_) f |= ALPHA_FLAG;
    }
  }
  if (w * (uint64_t)h >= MAX_IMAGE_AREA) return WEBP_MUX_BAD_DATA;

  if (width != NULL) *width = w;
  if (height != NULL) *height = h;
  if (flags != NULL) *flags = f;
  return WEBP_MUX_OK;
}