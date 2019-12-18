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
typedef  int /*<<< orphan*/  WebPInfoStatus ;
struct TYPE_3__ {int num_frames_; int feature_flags_; scalar_t__* chunk_counts_; scalar_t__ is_processing_anim_frame_; scalar_t__ has_alpha_; } ;
typedef  TYPE_1__ WebPInfo ;

/* Variables and functions */
 int ALPHA_FLAG ; 
 int ANIMATION_FLAG ; 
 size_t CHUNK_ANIM ; 
 size_t CHUNK_ANMF ; 
 size_t CHUNK_EXIF ; 
 size_t CHUNK_ICCP ; 
 size_t CHUNK_VP8X ; 
 size_t CHUNK_XMP ; 
 int EXIF_FLAG ; 
 int ICCP_FLAG ; 
 int /*<<< orphan*/  LOG_ERROR (char*) ; 
 int /*<<< orphan*/  LOG_WARN (char*) ; 
 int /*<<< orphan*/  WEBP_INFO_MISSING_DATA ; 
 int /*<<< orphan*/  WEBP_INFO_OK ; 
 int /*<<< orphan*/  WEBP_INFO_PARSE_ERROR ; 
 int XMP_FLAG ; 

__attribute__((used)) static WebPInfoStatus Validate(const WebPInfo* const webp_info) {
  if (webp_info->num_frames_ < 1) {
    LOG_ERROR("No image/frame detected.");
    return WEBP_INFO_MISSING_DATA;
  }
  if (webp_info->chunk_counts_[CHUNK_VP8X]) {
    const int iccp = !!(webp_info->feature_flags_ & ICCP_FLAG);
    const int exif = !!(webp_info->feature_flags_ & EXIF_FLAG);
    const int xmp = !!(webp_info->feature_flags_ & XMP_FLAG);
    const int animation = !!(webp_info->feature_flags_ & ANIMATION_FLAG);
    const int alpha = !!(webp_info->feature_flags_ & ALPHA_FLAG);
    if (!alpha && webp_info->has_alpha_) {
      LOG_ERROR("Unexpected alpha data detected.");
      return WEBP_INFO_PARSE_ERROR;
    }
    if (alpha && !webp_info->has_alpha_) {
      LOG_WARN("Alpha flag is set with no alpha data present.");
    }
    if (iccp && !webp_info->chunk_counts_[CHUNK_ICCP]) {
      LOG_ERROR("Missing ICCP chunk.");
      return WEBP_INFO_MISSING_DATA;
    }
    if (exif && !webp_info->chunk_counts_[CHUNK_EXIF]) {
      LOG_ERROR("Missing EXIF chunk.");
      return WEBP_INFO_MISSING_DATA;
    }
    if (xmp && !webp_info->chunk_counts_[CHUNK_XMP]) {
      LOG_ERROR("Missing XMP chunk.");
      return WEBP_INFO_MISSING_DATA;
    }
    if (!iccp && webp_info->chunk_counts_[CHUNK_ICCP]) {
      LOG_ERROR("Unexpected ICCP chunk detected.");
      return WEBP_INFO_PARSE_ERROR;
    }
    if (!exif && webp_info->chunk_counts_[CHUNK_EXIF]) {
      LOG_ERROR("Unexpected EXIF chunk detected.");
      return WEBP_INFO_PARSE_ERROR;
    }
    if (!xmp && webp_info->chunk_counts_[CHUNK_XMP]) {
      LOG_ERROR("Unexpected XMP chunk detected.");
      return WEBP_INFO_PARSE_ERROR;
    }
    // Incomplete animation frame.
    if (webp_info->is_processing_anim_frame_) return WEBP_INFO_MISSING_DATA;
    if (!animation && webp_info->num_frames_ > 1) {
      LOG_ERROR("More than 1 frame detected in non-animation file.");
      return WEBP_INFO_PARSE_ERROR;
    }
    if (animation && (!webp_info->chunk_counts_[CHUNK_ANIM] ||
        !webp_info->chunk_counts_[CHUNK_ANMF])) {
      LOG_ERROR("No ANIM/ANMF chunk detected in animation file.");
      return WEBP_INFO_PARSE_ERROR;
    }
  }
  return WEBP_INFO_OK;
}