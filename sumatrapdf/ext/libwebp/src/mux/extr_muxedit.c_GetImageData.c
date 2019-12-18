#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_2__* alpha_; TYPE_1__* img_; } ;
typedef  TYPE_3__ WebPMuxImage ;
typedef  int /*<<< orphan*/  WebPMuxError ;
struct TYPE_16__ {TYPE_3__* images_; } ;
typedef  TYPE_4__ WebPMux ;
struct TYPE_17__ {scalar_t__ size; int /*<<< orphan*/  bytes; } ;
typedef  TYPE_5__ WebPData ;
struct TYPE_14__ {TYPE_5__ data_; } ;
struct TYPE_13__ {TYPE_5__ data_; } ;

/* Variables and functions */
 scalar_t__ TAG_SIZE ; 
 int VP8LCheckSignature (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  WEBP_MUX_BAD_DATA ; 
 int /*<<< orphan*/  WEBP_MUX_OK ; 
 int /*<<< orphan*/  WebPDataInit (TYPE_5__* const) ; 
 TYPE_4__* WebPMuxCreate (TYPE_5__ const* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WebPMuxDelete (TYPE_4__* const) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static WebPMuxError GetImageData(const WebPData* const bitstream,
                                 WebPData* const image, WebPData* const alpha,
                                 int* const is_lossless) {
  WebPDataInit(alpha);  // Default: no alpha.
  if (bitstream->size < TAG_SIZE ||
      memcmp(bitstream->bytes, "RIFF", TAG_SIZE)) {
    // It is NOT webp file data. Return input data as is.
    *image = *bitstream;
  } else {
    // It is webp file data. Extract image data from it.
    const WebPMuxImage* wpi;
    WebPMux* const mux = WebPMuxCreate(bitstream, 0);
    if (mux == NULL) return WEBP_MUX_BAD_DATA;
    wpi = mux->images_;
    assert(wpi != NULL && wpi->img_ != NULL);
    *image = wpi->img_->data_;
    if (wpi->alpha_ != NULL) {
      *alpha = wpi->alpha_->data_;
    }
    WebPMuxDelete(mux);
  }
  *is_lossless = VP8LCheckSignature(image->bytes, image->size);
  return WEBP_MUX_OK;
}