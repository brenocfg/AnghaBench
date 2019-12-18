#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  scalar_t__ VP8StatusCode ;
struct TYPE_13__ {int width_; int xscale_; int height_; int yscale_; void* clamp_type_; void* colorspace_; } ;
typedef  TYPE_1__ VP8PictureHeader ;
struct TYPE_14__ {int* data; size_t data_size; int width; int height; int crop_right; int crop_bottom; int scaled_width; int scaled_height; int mb_w; int mb_h; scalar_t__ use_scaling; scalar_t__ crop_left; scalar_t__ crop_top; scalar_t__ use_cropping; } ;
typedef  TYPE_2__ VP8Io ;
struct TYPE_15__ {int key_frame_; int profile_; int show_; int partition_length_; } ;
typedef  TYPE_3__ VP8FrameHeader ;
struct TYPE_16__ {int mb_w_; int mb_h_; int ready_; int /*<<< orphan*/  proba_; int /*<<< orphan*/  segment_hdr_; int /*<<< orphan*/  br_; TYPE_1__ pic_hdr_; TYPE_3__ frm_hdr_; } ;
typedef  TYPE_4__ VP8Decoder ;
typedef  int /*<<< orphan*/  VP8BitReader ;

/* Variables and functions */
 int /*<<< orphan*/  ParseFilterHeader (int /*<<< orphan*/ *,TYPE_4__* const) ; 
 scalar_t__ ParsePartitions (TYPE_4__* const,int const*,size_t) ; 
 int /*<<< orphan*/  ParseSegmentHeader (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ResetSegmentHeader (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetOk (TYPE_4__* const) ; 
 int /*<<< orphan*/  VP8CheckSignature (int const*,size_t) ; 
 void* VP8Get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  VP8InitBitReader (int /*<<< orphan*/ *,int const*,size_t) ; 
 int /*<<< orphan*/  VP8ParseProba (int /*<<< orphan*/ *,TYPE_4__* const) ; 
 int /*<<< orphan*/  VP8ParseQuant (TYPE_4__* const) ; 
 int /*<<< orphan*/  VP8ResetProba (int /*<<< orphan*/ *) ; 
 int VP8SetError (TYPE_4__* const,scalar_t__,char*) ; 
 scalar_t__ VP8_STATUS_BITSTREAM_ERROR ; 
 scalar_t__ VP8_STATUS_INVALID_PARAM ; 
 scalar_t__ VP8_STATUS_NOT_ENOUGH_DATA ; 
 scalar_t__ VP8_STATUS_OK ; 
 scalar_t__ VP8_STATUS_UNSUPPORTED_FEATURE ; 

int VP8GetHeaders(VP8Decoder* const dec, VP8Io* const io) {
  const uint8_t* buf;
  size_t buf_size;
  VP8FrameHeader* frm_hdr;
  VP8PictureHeader* pic_hdr;
  VP8BitReader* br;
  VP8StatusCode status;

  if (dec == NULL) {
    return 0;
  }
  SetOk(dec);
  if (io == NULL) {
    return VP8SetError(dec, VP8_STATUS_INVALID_PARAM,
                       "null VP8Io passed to VP8GetHeaders()");
  }
  buf = io->data;
  buf_size = io->data_size;
  if (buf_size < 4) {
    return VP8SetError(dec, VP8_STATUS_NOT_ENOUGH_DATA,
                       "Truncated header.");
  }

  // Paragraph 9.1
  {
    const uint32_t bits = buf[0] | (buf[1] << 8) | (buf[2] << 16);
    frm_hdr = &dec->frm_hdr_;
    frm_hdr->key_frame_ = !(bits & 1);
    frm_hdr->profile_ = (bits >> 1) & 7;
    frm_hdr->show_ = (bits >> 4) & 1;
    frm_hdr->partition_length_ = (bits >> 5);
    if (frm_hdr->profile_ > 3) {
      return VP8SetError(dec, VP8_STATUS_BITSTREAM_ERROR,
                         "Incorrect keyframe parameters.");
    }
    if (!frm_hdr->show_) {
      return VP8SetError(dec, VP8_STATUS_UNSUPPORTED_FEATURE,
                         "Frame not displayable.");
    }
    buf += 3;
    buf_size -= 3;
  }

  pic_hdr = &dec->pic_hdr_;
  if (frm_hdr->key_frame_) {
    // Paragraph 9.2
    if (buf_size < 7) {
      return VP8SetError(dec, VP8_STATUS_NOT_ENOUGH_DATA,
                         "cannot parse picture header");
    }
    if (!VP8CheckSignature(buf, buf_size)) {
      return VP8SetError(dec, VP8_STATUS_BITSTREAM_ERROR,
                         "Bad code word");
    }
    pic_hdr->width_ = ((buf[4] << 8) | buf[3]) & 0x3fff;
    pic_hdr->xscale_ = buf[4] >> 6;   // ratio: 1, 5/4 5/3 or 2
    pic_hdr->height_ = ((buf[6] << 8) | buf[5]) & 0x3fff;
    pic_hdr->yscale_ = buf[6] >> 6;
    buf += 7;
    buf_size -= 7;

    dec->mb_w_ = (pic_hdr->width_ + 15) >> 4;
    dec->mb_h_ = (pic_hdr->height_ + 15) >> 4;

    // Setup default output area (can be later modified during io->setup())
    io->width = pic_hdr->width_;
    io->height = pic_hdr->height_;
    // IMPORTANT! use some sane dimensions in crop_* and scaled_* fields.
    // So they can be used interchangeably without always testing for
    // 'use_cropping'.
    io->use_cropping = 0;
    io->crop_top  = 0;
    io->crop_left = 0;
    io->crop_right  = io->width;
    io->crop_bottom = io->height;
    io->use_scaling  = 0;
    io->scaled_width = io->width;
    io->scaled_height = io->height;

    io->mb_w = io->width;   // sanity check
    io->mb_h = io->height;  // ditto

    VP8ResetProba(&dec->proba_);
    ResetSegmentHeader(&dec->segment_hdr_);
  }

  // Check if we have all the partition #0 available, and initialize dec->br_
  // to read this partition (and this partition only).
  if (frm_hdr->partition_length_ > buf_size) {
    return VP8SetError(dec, VP8_STATUS_NOT_ENOUGH_DATA,
                       "bad partition length");
  }

  br = &dec->br_;
  VP8InitBitReader(br, buf, frm_hdr->partition_length_);
  buf += frm_hdr->partition_length_;
  buf_size -= frm_hdr->partition_length_;

  if (frm_hdr->key_frame_) {
    pic_hdr->colorspace_ = VP8Get(br, "global-header");
    pic_hdr->clamp_type_ = VP8Get(br, "global-header");
  }
  if (!ParseSegmentHeader(br, &dec->segment_hdr_, &dec->proba_)) {
    return VP8SetError(dec, VP8_STATUS_BITSTREAM_ERROR,
                       "cannot parse segment header");
  }
  // Filter specs
  if (!ParseFilterHeader(br, dec)) {
    return VP8SetError(dec, VP8_STATUS_BITSTREAM_ERROR,
                       "cannot parse filter header");
  }
  status = ParsePartitions(dec, buf, buf_size);
  if (status != VP8_STATUS_OK) {
    return VP8SetError(dec, status, "cannot parse partitions");
  }

  // quantizer change
  VP8ParseQuant(dec);

  // Frame buffer marking
  if (!frm_hdr->key_frame_) {
    return VP8SetError(dec, VP8_STATUS_UNSUPPORTED_FEATURE,
                       "Not a key frame.");
  }

  VP8Get(br, "global-header");   // ignore the value of update_proba_

  VP8ParseProba(br, dec);

  // sanitized state
  dec->ready_ = 1;
  return 1;
}