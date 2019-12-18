#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int width_; int height_; int /*<<< orphan*/ * header_; } ;
typedef  TYPE_1__ WebPMuxImage ;
typedef  scalar_t__ WebPMuxError ;
typedef  int /*<<< orphan*/  WebPChunk ;

/* Variables and functions */
 scalar_t__ GetFrameInfo (int /*<<< orphan*/  const* const,int* const,int* const,int* const) ; 
 scalar_t__ WEBP_MUX_OK ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static WebPMuxError GetImageInfo(const WebPMuxImage* const wpi,
                                 int* const x_offset, int* const y_offset,
                                 int* const duration,
                                 int* const width, int* const height) {
  const WebPChunk* const frame_chunk = wpi->header_;
  WebPMuxError err;
  assert(wpi != NULL);
  assert(frame_chunk != NULL);

  // Get offsets and duration from ANMF chunk.
  err = GetFrameInfo(frame_chunk, x_offset, y_offset, duration);
  if (err != WEBP_MUX_OK) return err;

  // Get width and height from VP8/VP8L chunk.
  if (width != NULL) *width = wpi->width_;
  if (height != NULL) *height = wpi->height_;
  return WEBP_MUX_OK;
}