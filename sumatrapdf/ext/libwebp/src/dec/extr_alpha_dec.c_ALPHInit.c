#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ WEBP_FILTER_TYPE ;
struct TYPE_8__ {size_t width; size_t height; int /*<<< orphan*/  crop_bottom; int /*<<< orphan*/  crop_top; int /*<<< orphan*/  crop_right; int /*<<< orphan*/  crop_left; int /*<<< orphan*/  use_cropping; TYPE_2__* opaque; } ;
typedef  TYPE_1__ VP8Io ;
struct TYPE_9__ {int* output_; size_t width_; size_t height_; int method_; scalar_t__ filter_; int pre_processing_; TYPE_1__ io_; } ;
typedef  TYPE_2__ ALPHDecoder ;

/* Variables and functions */
 size_t ALPHA_HEADER_LEN ; 
 int ALPHA_LOSSLESS_COMPRESSION ; 
 int ALPHA_NO_COMPRESSION ; 
 int ALPHA_PREPROCESSED_LEVELS ; 
 int /*<<< orphan*/  VP8FiltersInit () ; 
 int /*<<< orphan*/  VP8InitIo (TYPE_1__* const) ; 
 int VP8LDecodeAlphaHeader (TYPE_2__* const,int const* const,size_t const) ; 
 scalar_t__ WEBP_FILTER_LAST ; 
 int /*<<< orphan*/  WebPInitCustomIo (int /*<<< orphan*/ *,TYPE_1__* const) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int ALPHInit(ALPHDecoder* const dec, const uint8_t* data,
                    size_t data_size, const VP8Io* const src_io,
                    uint8_t* output) {
  int ok = 0;
  const uint8_t* const alpha_data = data + ALPHA_HEADER_LEN;
  const size_t alpha_data_size = data_size - ALPHA_HEADER_LEN;
  int rsrv;
  VP8Io* const io = &dec->io_;

  assert(data != NULL && output != NULL && src_io != NULL);

  VP8FiltersInit();
  dec->output_ = output;
  dec->width_ = src_io->width;
  dec->height_ = src_io->height;
  assert(dec->width_ > 0 && dec->height_ > 0);

  if (data_size <= ALPHA_HEADER_LEN) {
    return 0;
  }

  dec->method_ = (data[0] >> 0) & 0x03;
  dec->filter_ = (WEBP_FILTER_TYPE)((data[0] >> 2) & 0x03);
  dec->pre_processing_ = (data[0] >> 4) & 0x03;
  rsrv = (data[0] >> 6) & 0x03;
  if (dec->method_ < ALPHA_NO_COMPRESSION ||
      dec->method_ > ALPHA_LOSSLESS_COMPRESSION ||
      dec->filter_ >= WEBP_FILTER_LAST ||
      dec->pre_processing_ > ALPHA_PREPROCESSED_LEVELS ||
      rsrv != 0) {
    return 0;
  }

  // Copy the necessary parameters from src_io to io
  VP8InitIo(io);
  WebPInitCustomIo(NULL, io);
  io->opaque = dec;
  io->width = src_io->width;
  io->height = src_io->height;

  io->use_cropping = src_io->use_cropping;
  io->crop_left = src_io->crop_left;
  io->crop_right = src_io->crop_right;
  io->crop_top = src_io->crop_top;
  io->crop_bottom = src_io->crop_bottom;
  // No need to copy the scaling parameters.

  if (dec->method_ == ALPHA_NO_COMPRESSION) {
    const size_t alpha_decoded_size = dec->width_ * dec->height_;
    ok = (alpha_data_size >= alpha_decoded_size);
  } else {
    assert(dec->method_ == ALPHA_LOSSLESS_COMPRESSION);
    ok = VP8LDecodeAlphaHeader(dec, alpha_data, alpha_data_size);
  }

  return ok;
}