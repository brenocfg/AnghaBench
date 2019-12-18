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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;
typedef  scalar_t__ WebPInfoStatus ;
struct TYPE_11__ {scalar_t__ frame_width_; scalar_t__ frame_height_; int seen_image_subchunk_; scalar_t__ canvas_width_; scalar_t__ canvas_height_; int has_alpha_; scalar_t__ parse_bitstream_; int /*<<< orphan*/  num_frames_; scalar_t__* chunk_counts_; scalar_t__ seen_alpha_subchunk_; int /*<<< orphan*/ * anmf_subchunk_counts_; scalar_t__ is_processing_anim_frame_; int /*<<< orphan*/  quiet_; } ;
typedef  TYPE_1__ WebPInfo ;
struct TYPE_12__ {int format; int width; int height; int has_alpha; int has_animation; } ;
typedef  TYPE_2__ WebPBitstreamFeatures ;
typedef  scalar_t__ VP8StatusCode ;
struct TYPE_13__ {size_t id_; int /*<<< orphan*/  size_; int /*<<< orphan*/  payload_; } ;
typedef  TYPE_3__ ChunkData ;

/* Variables and functions */
 size_t CHUNK_ALPHA ; 
 size_t CHUNK_ANIM ; 
 size_t CHUNK_ANMF ; 
 int /*<<< orphan*/  CHUNK_HEADER_SIZE ; 
 size_t CHUNK_VP8 ; 
 size_t CHUNK_VP8L ; 
 size_t CHUNK_VP8X ; 
 int /*<<< orphan*/  LOG_ERROR (char*) ; 
 int /*<<< orphan*/  LOG_WARN (char*) ; 
 int MAX_CANVAS_SIZE ; 
 int MAX_IMAGE_AREA ; 
 scalar_t__ ParseLosslessHeader (TYPE_3__ const* const,TYPE_1__* const) ; 
 scalar_t__ ParseLossyHeader (TYPE_3__ const* const,TYPE_1__* const) ; 
 scalar_t__ const VP8_STATUS_OK ; 
 scalar_t__ WEBP_INFO_BITSTREAM_ERROR ; 
 scalar_t__ const WEBP_INFO_OK ; 
 scalar_t__ WEBP_INFO_PARSE_ERROR ; 
 scalar_t__ WebPGetFeatures (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 char** kFormats ; 
 int /*<<< orphan*/  printf (char*,int,int,int,int,char*,size_t) ; 

__attribute__((used)) static WebPInfoStatus ProcessImageChunk(const ChunkData* const chunk_data,
                                        WebPInfo* const webp_info) {
  const uint8_t* data = chunk_data->payload_ - CHUNK_HEADER_SIZE;
  WebPBitstreamFeatures features;
  const VP8StatusCode vp8_status =
      WebPGetFeatures(data, chunk_data->size_, &features);
  if (vp8_status != VP8_STATUS_OK) {
    LOG_ERROR("VP8/VP8L bitstream error.");
    return WEBP_INFO_BITSTREAM_ERROR;
  }
  if (!webp_info->quiet_) {
    assert(features.format >= 0 && features.format <= 2);
    printf("  Width: %d\n  Height: %d\n  Alpha: %d\n  Animation: %d\n"
           "  Format: %s (%d)\n",
           features.width, features.height, features.has_alpha,
           features.has_animation, kFormats[features.format], features.format);
  }
  if (webp_info->is_processing_anim_frame_) {
    ++webp_info->anmf_subchunk_counts_[chunk_data->id_ == CHUNK_VP8 ? 0 : 1];
    if (chunk_data->id_ == CHUNK_VP8L && webp_info->seen_alpha_subchunk_) {
      LOG_ERROR("Both VP8L and ALPH sub-chunks are present in an ANMF chunk.");
      return WEBP_INFO_PARSE_ERROR;
    }
    if (webp_info->frame_width_ != features.width ||
        webp_info->frame_height_ != features.height) {
      LOG_ERROR("Frame size in VP8/VP8L sub-chunk differs from ANMF header.");
      return WEBP_INFO_PARSE_ERROR;
    }
    if (webp_info->seen_image_subchunk_) {
      LOG_ERROR("Consecutive VP8/VP8L sub-chunks in an ANMF chunk.");
      return WEBP_INFO_PARSE_ERROR;
    }
    webp_info->seen_image_subchunk_ = 1;
  } else {
    if (webp_info->chunk_counts_[CHUNK_VP8] ||
        webp_info->chunk_counts_[CHUNK_VP8L]) {
      LOG_ERROR("Multiple VP8/VP8L chunks detected.");
      return WEBP_INFO_PARSE_ERROR;
    }
    if (chunk_data->id_ == CHUNK_VP8L &&
        webp_info->chunk_counts_[CHUNK_ALPHA]) {
      LOG_WARN("Both VP8L and ALPH chunks are detected.");
    }
    if (webp_info->chunk_counts_[CHUNK_ANIM] ||
        webp_info->chunk_counts_[CHUNK_ANMF]) {
      LOG_ERROR("VP8/VP8L chunk and ANIM/ANMF chunk are both detected.");
      return WEBP_INFO_PARSE_ERROR;
    }
    if (webp_info->chunk_counts_[CHUNK_VP8X]) {
      if (webp_info->canvas_width_ != features.width ||
          webp_info->canvas_height_ != features.height) {
        LOG_ERROR("Image size in VP8/VP8L chunk differs from VP8X chunk.");
        return WEBP_INFO_PARSE_ERROR;
      }
    } else {
      webp_info->canvas_width_ = features.width;
      webp_info->canvas_height_ = features.height;
      if (webp_info->canvas_width_ < 1 || webp_info->canvas_height_ < 1 ||
          webp_info->canvas_width_ > MAX_CANVAS_SIZE ||
          webp_info->canvas_height_ > MAX_CANVAS_SIZE ||
          (uint64_t)webp_info->canvas_width_ * webp_info->canvas_height_ >
              MAX_IMAGE_AREA) {
        LOG_WARN("Invalid parameters in VP8/VP8L chunk.");
      }
    }
    ++webp_info->chunk_counts_[chunk_data->id_];
  }
  ++webp_info->num_frames_;
  webp_info->has_alpha_ |= features.has_alpha;
  if (webp_info->parse_bitstream_) {
    const int is_lossy = (chunk_data->id_ == CHUNK_VP8);
    const WebPInfoStatus status =
        is_lossy ? ParseLossyHeader(chunk_data, webp_info)
                 : ParseLosslessHeader(chunk_data, webp_info);
    if (status != WEBP_INFO_OK) return status;
  }
  return WEBP_INFO_OK;
}