#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_9__ ;
typedef  struct TYPE_32__   TYPE_8__ ;
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;
typedef  struct TYPE_24__   TYPE_13__ ;
typedef  struct TYPE_23__   TYPE_12__ ;
typedef  struct TYPE_22__   TYPE_11__ ;
typedef  struct TYPE_21__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_21__ {TYPE_9__* header_; TYPE_2__* img_; } ;
typedef  TYPE_10__ WebPMuxImage ;
typedef  scalar_t__ WebPMuxError ;
struct TYPE_22__ {int canvas_width_; int canvas_height_; int /*<<< orphan*/ * unknown_; TYPE_8__* xmp_; TYPE_6__* exif_; TYPE_4__* iccp_; TYPE_10__* images_; } ;
typedef  TYPE_11__ WebPMux ;
struct TYPE_23__ {int member_1; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_12__ WebPData ;
struct TYPE_33__ {scalar_t__ tag_; } ;
struct TYPE_31__ {int /*<<< orphan*/ * bytes; } ;
struct TYPE_32__ {TYPE_7__ data_; } ;
struct TYPE_29__ {int /*<<< orphan*/ * bytes; } ;
struct TYPE_30__ {TYPE_5__ data_; } ;
struct TYPE_27__ {int /*<<< orphan*/ * bytes; } ;
struct TYPE_28__ {TYPE_3__ data_; } ;
struct TYPE_25__ {int /*<<< orphan*/ * bytes; } ;
struct TYPE_26__ {TYPE_1__ data_; } ;
struct TYPE_24__ {scalar_t__ tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALPHA_FLAG ; 
 int /*<<< orphan*/  ANIMATION_FLAG ; 
 int /*<<< orphan*/  EXIF_FLAG ; 
 scalar_t__ GetAdjustedCanvasSize (TYPE_11__* const,int*,int*) ; 
 int /*<<< orphan*/  ICCP_FLAG ; 
 size_t IDX_ANMF ; 
 size_t IDX_VP8X ; 
 int MAX_CANVAS_SIZE ; 
 scalar_t__ MuxDeleteAllNamedData (TYPE_11__* const,scalar_t__) ; 
 scalar_t__ MuxHasAlpha (TYPE_10__ const*) ; 
 scalar_t__ MuxImageCount (TYPE_10__ const*,int /*<<< orphan*/ ) ; 
 scalar_t__ MuxSet (TYPE_11__* const,scalar_t__,TYPE_12__ const*,int) ; 
 int /*<<< orphan*/  PutLE24 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  PutLE32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int VP8X_CHUNK_SIZE ; 
 int /*<<< orphan*/  WEBP_CHUNK_ALPHA ; 
 scalar_t__ WEBP_MUX_INVALID_ARGUMENT ; 
 scalar_t__ WEBP_MUX_NOT_FOUND ; 
 scalar_t__ WEBP_MUX_OK ; 
 int /*<<< orphan*/  XMP_FLAG ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_13__* kChunks ; 

__attribute__((used)) static WebPMuxError CreateVP8XChunk(WebPMux* const mux) {
  WebPMuxError err = WEBP_MUX_OK;
  uint32_t flags = 0;
  int width = 0;
  int height = 0;
  uint8_t data[VP8X_CHUNK_SIZE];
  const WebPData vp8x = { data, VP8X_CHUNK_SIZE };
  const WebPMuxImage* images = NULL;

  assert(mux != NULL);
  images = mux->images_;  // First image.
  if (images == NULL || images->img_ == NULL ||
      images->img_->data_.bytes == NULL) {
    return WEBP_MUX_INVALID_ARGUMENT;
  }

  // If VP8X chunk(s) is(are) already present, remove them (and later add new
  // VP8X chunk with updated flags).
  err = MuxDeleteAllNamedData(mux, kChunks[IDX_VP8X].tag);
  if (err != WEBP_MUX_OK && err != WEBP_MUX_NOT_FOUND) return err;

  // Set flags.
  if (mux->iccp_ != NULL && mux->iccp_->data_.bytes != NULL) {
    flags |= ICCP_FLAG;
  }
  if (mux->exif_ != NULL && mux->exif_->data_.bytes != NULL) {
    flags |= EXIF_FLAG;
  }
  if (mux->xmp_ != NULL && mux->xmp_->data_.bytes != NULL) {
    flags |= XMP_FLAG;
  }
  if (images->header_ != NULL) {
    if (images->header_->tag_ == kChunks[IDX_ANMF].tag) {
      // This is an image with animation.
      flags |= ANIMATION_FLAG;
    }
  }
  if (MuxImageCount(images, WEBP_CHUNK_ALPHA) > 0) {
    flags |= ALPHA_FLAG;  // Some images have an alpha channel.
  }

  err = GetAdjustedCanvasSize(mux, &width, &height);
  if (err != WEBP_MUX_OK) return err;

  if (width <= 0 || height <= 0) {
    return WEBP_MUX_INVALID_ARGUMENT;
  }
  if (width > MAX_CANVAS_SIZE || height > MAX_CANVAS_SIZE) {
    return WEBP_MUX_INVALID_ARGUMENT;
  }

  if (mux->canvas_width_ != 0 || mux->canvas_height_ != 0) {
    if (width > mux->canvas_width_ || height > mux->canvas_height_) {
      return WEBP_MUX_INVALID_ARGUMENT;
    }
    width = mux->canvas_width_;
    height = mux->canvas_height_;
  }

  if (flags == 0 && mux->unknown_ == NULL) {
    // For simple file format, VP8X chunk should not be added.
    return WEBP_MUX_OK;
  }

  if (MuxHasAlpha(images)) {
    // This means some frames explicitly/implicitly contain alpha.
    // Note: This 'flags' update must NOT be done for a lossless image
    // without a VP8X chunk!
    flags |= ALPHA_FLAG;
  }

  PutLE32(data + 0, flags);   // VP8X chunk flags.
  PutLE24(data + 4, width - 1);   // canvas width.
  PutLE24(data + 7, height - 1);  // canvas height.

  return MuxSet(mux, kChunks[IDX_VP8X].tag, &vp8x, 1);
}