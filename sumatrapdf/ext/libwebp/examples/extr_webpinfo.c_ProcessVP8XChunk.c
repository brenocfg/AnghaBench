#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  WebPInfoStatus ;
struct TYPE_5__ {int feature_flags_; int canvas_width_; int canvas_height_; int /*<<< orphan*/  quiet_; scalar_t__* chunk_counts_; } ;
typedef  TYPE_1__ WebPInfo ;
struct TYPE_6__ {int* payload_; scalar_t__ size_; } ;
typedef  TYPE_2__ ChunkData ;

/* Variables and functions */
 int ALPHA_FLAG ; 
 int ANIMATION_FLAG ; 
 scalar_t__ CHUNK_HEADER_SIZE ; 
 size_t CHUNK_VP8 ; 
 size_t CHUNK_VP8L ; 
 size_t CHUNK_VP8X ; 
 int EXIF_FLAG ; 
 int ICCP_FLAG ; 
 int /*<<< orphan*/  LOG_ERROR (char*) ; 
 int /*<<< orphan*/  LOG_WARN (char*) ; 
 int MAX_CANVAS_SIZE ; 
 int MAX_IMAGE_AREA ; 
 void* ReadLE24 (int const**) ; 
 scalar_t__ VP8X_CHUNK_SIZE ; 
 int /*<<< orphan*/  WEBP_INFO_OK ; 
 int /*<<< orphan*/  WEBP_INFO_PARSE_ERROR ; 
 int XMP_FLAG ; 
 int /*<<< orphan*/  printf (char*,int,int,...) ; 

__attribute__((used)) static WebPInfoStatus ProcessVP8XChunk(const ChunkData* const chunk_data,
                                       WebPInfo* const webp_info) {
  const uint8_t* data = chunk_data->payload_;
  if (webp_info->chunk_counts_[CHUNK_VP8] ||
      webp_info->chunk_counts_[CHUNK_VP8L] ||
      webp_info->chunk_counts_[CHUNK_VP8X]) {
    LOG_ERROR("Already seen a VP8/VP8L/VP8X chunk when parsing VP8X chunk.");
    return WEBP_INFO_PARSE_ERROR;
  }
  if (chunk_data->size_ != VP8X_CHUNK_SIZE + CHUNK_HEADER_SIZE) {
    LOG_ERROR("Corrupted VP8X chunk.");
    return WEBP_INFO_PARSE_ERROR;
  }
  ++webp_info->chunk_counts_[CHUNK_VP8X];
  webp_info->feature_flags_ = *data;
  data += 4;
  webp_info->canvas_width_ = 1 + ReadLE24(&data);
  webp_info->canvas_height_ = 1 + ReadLE24(&data);
  if (!webp_info->quiet_) {
    printf("  ICCP: %d\n  Alpha: %d\n  EXIF: %d\n  XMP: %d\n  Animation: %d\n",
           (webp_info->feature_flags_ & ICCP_FLAG) != 0,
           (webp_info->feature_flags_ & ALPHA_FLAG) != 0,
           (webp_info->feature_flags_ & EXIF_FLAG) != 0,
           (webp_info->feature_flags_ & XMP_FLAG) != 0,
           (webp_info->feature_flags_ & ANIMATION_FLAG) != 0);
    printf("  Canvas size %d x %d\n",
           webp_info->canvas_width_, webp_info->canvas_height_);
  }
  if (webp_info->canvas_width_ > MAX_CANVAS_SIZE) {
    LOG_WARN("Canvas width is out of range in VP8X chunk.");
  }
  if (webp_info->canvas_height_ > MAX_CANVAS_SIZE) {
    LOG_WARN("Canvas height is out of range in VP8X chunk.");
  }
  if ((uint64_t)webp_info->canvas_width_ * webp_info->canvas_height_ >
      MAX_IMAGE_AREA) {
    LOG_WARN("Canvas area is out of range in VP8X chunk.");
  }
  return WEBP_INFO_OK;
}