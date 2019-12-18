#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  img_; int /*<<< orphan*/  alpha_; } ;
typedef  TYPE_1__ WebPMuxImage ;
typedef  scalar_t__ WebPMuxError ;
struct TYPE_12__ {int /*<<< orphan*/ * bytes; } ;
typedef  TYPE_2__ WebPData ;
struct TYPE_13__ {int tag; } ;

/* Variables and functions */
 scalar_t__ AddDataToChunkList (TYPE_2__*,int,int const,int /*<<< orphan*/ *) ; 
 scalar_t__ GetImageData (TYPE_2__ const* const,TYPE_2__*,TYPE_2__*,int*) ; 
 size_t IDX_ALPHA ; 
 size_t IDX_VP8 ; 
 size_t IDX_VP8L ; 
 scalar_t__ MuxImageFinalize (TYPE_1__* const) ; 
 scalar_t__ WEBP_MUX_INVALID_ARGUMENT ; 
 scalar_t__ WEBP_MUX_OK ; 
 TYPE_3__* kChunks ; 

__attribute__((used)) static WebPMuxError SetAlphaAndImageChunks(
    const WebPData* const bitstream, int copy_data, WebPMuxImage* const wpi) {
  int is_lossless = 0;
  WebPData image, alpha;
  WebPMuxError err = GetImageData(bitstream, &image, &alpha, &is_lossless);
  const int image_tag =
      is_lossless ? kChunks[IDX_VP8L].tag : kChunks[IDX_VP8].tag;
  if (err != WEBP_MUX_OK) return err;
  if (alpha.bytes != NULL) {
    err = AddDataToChunkList(&alpha, copy_data, kChunks[IDX_ALPHA].tag,
                             &wpi->alpha_);
    if (err != WEBP_MUX_OK) return err;
  }
  err = AddDataToChunkList(&image, copy_data, image_tag, &wpi->img_);
  if (err != WEBP_MUX_OK) return err;
  return MuxImageFinalize(wpi) ? WEBP_MUX_OK : WEBP_MUX_INVALID_ARGUMENT;
}