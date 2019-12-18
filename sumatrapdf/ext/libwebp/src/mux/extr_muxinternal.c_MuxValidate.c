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
typedef  int uint32_t ;
struct TYPE_8__ {scalar_t__ width_; scalar_t__ height_; int /*<<< orphan*/ * next_; } ;
typedef  TYPE_1__ WebPMuxImage ;
typedef  scalar_t__ WebPMuxError ;
struct TYPE_9__ {scalar_t__ canvas_width_; scalar_t__ canvas_height_; TYPE_1__* images_; } ;
typedef  TYPE_2__ WebPMux ;

/* Variables and functions */
 int ALPHA_FLAG ; 
 int ANIMATION_FLAG ; 
 int /*<<< orphan*/  EXIF_FLAG ; 
 int /*<<< orphan*/  ICCP_FLAG ; 
 int /*<<< orphan*/  IDX_ANIM ; 
 int /*<<< orphan*/  IDX_ANMF ; 
 int /*<<< orphan*/  IDX_EXIF ; 
 int /*<<< orphan*/  IDX_ICCP ; 
 int /*<<< orphan*/  IDX_VP8 ; 
 int /*<<< orphan*/  IDX_VP8X ; 
 int /*<<< orphan*/  IDX_XMP ; 
 scalar_t__ MuxHasAlpha (TYPE_1__*) ; 
 int /*<<< orphan*/  NO_FLAG ; 
 scalar_t__ ValidateChunk (TYPE_2__ const* const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int*) ; 
 int /*<<< orphan*/  WEBP_CHUNK_ALPHA ; 
 scalar_t__ WEBP_MUX_INVALID_ARGUMENT ; 
 scalar_t__ WEBP_MUX_OK ; 
 scalar_t__ WebPMuxGetFeatures (TYPE_2__ const* const,int*) ; 
 scalar_t__ WebPMuxNumChunks (TYPE_2__ const* const,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  XMP_FLAG ; 

WebPMuxError MuxValidate(const WebPMux* const mux) {
  int num_iccp;
  int num_exif;
  int num_xmp;
  int num_anim;
  int num_frames;
  int num_vp8x;
  int num_images;
  int num_alpha;
  uint32_t flags;
  WebPMuxError err;

  // Verify mux is not NULL.
  if (mux == NULL) return WEBP_MUX_INVALID_ARGUMENT;

  // Verify mux has at least one image.
  if (mux->images_ == NULL) return WEBP_MUX_INVALID_ARGUMENT;

  err = WebPMuxGetFeatures(mux, &flags);
  if (err != WEBP_MUX_OK) return err;

  // At most one color profile chunk.
  err = ValidateChunk(mux, IDX_ICCP, ICCP_FLAG, flags, 1, &num_iccp);
  if (err != WEBP_MUX_OK) return err;

  // At most one EXIF metadata.
  err = ValidateChunk(mux, IDX_EXIF, EXIF_FLAG, flags, 1, &num_exif);
  if (err != WEBP_MUX_OK) return err;

  // At most one XMP metadata.
  err = ValidateChunk(mux, IDX_XMP, XMP_FLAG, flags, 1, &num_xmp);
  if (err != WEBP_MUX_OK) return err;

  // Animation: ANIMATION_FLAG, ANIM chunk and ANMF chunk(s) are consistent.
  // At most one ANIM chunk.
  err = ValidateChunk(mux, IDX_ANIM, NO_FLAG, flags, 1, &num_anim);
  if (err != WEBP_MUX_OK) return err;
  err = ValidateChunk(mux, IDX_ANMF, NO_FLAG, flags, -1, &num_frames);
  if (err != WEBP_MUX_OK) return err;

  {
    const int has_animation = !!(flags & ANIMATION_FLAG);
    if (has_animation && (num_anim == 0 || num_frames == 0)) {
      return WEBP_MUX_INVALID_ARGUMENT;
    }
    if (!has_animation && (num_anim == 1 || num_frames > 0)) {
      return WEBP_MUX_INVALID_ARGUMENT;
    }
    if (!has_animation) {
      const WebPMuxImage* images = mux->images_;
      // There can be only one image.
      if (images == NULL || images->next_ != NULL) {
        return WEBP_MUX_INVALID_ARGUMENT;
      }
      // Size must match.
      if (mux->canvas_width_ > 0) {
        if (images->width_ != mux->canvas_width_ ||
            images->height_ != mux->canvas_height_) {
          return WEBP_MUX_INVALID_ARGUMENT;
        }
      }
    }
  }

  // Verify either VP8X chunk is present OR there is only one elem in
  // mux->images_.
  err = ValidateChunk(mux, IDX_VP8X, NO_FLAG, flags, 1, &num_vp8x);
  if (err != WEBP_MUX_OK) return err;
  err = ValidateChunk(mux, IDX_VP8, NO_FLAG, flags, -1, &num_images);
  if (err != WEBP_MUX_OK) return err;
  if (num_vp8x == 0 && num_images != 1) return WEBP_MUX_INVALID_ARGUMENT;

  // ALPHA_FLAG & alpha chunk(s) are consistent.
  // Note: ALPHA_FLAG can be set when there is actually no Alpha data present.
  if (MuxHasAlpha(mux->images_)) {
    if (num_vp8x > 0) {
      // VP8X chunk is present, so it should contain ALPHA_FLAG.
      if (!(flags & ALPHA_FLAG)) return WEBP_MUX_INVALID_ARGUMENT;
    } else {
      // VP8X chunk is not present, so ALPH chunks should NOT be present either.
      err = WebPMuxNumChunks(mux, WEBP_CHUNK_ALPHA, &num_alpha);
      if (err != WEBP_MUX_OK) return err;
      if (num_alpha > 0) return WEBP_MUX_INVALID_ARGUMENT;
    }
  }

  return WEBP_MUX_OK;
}