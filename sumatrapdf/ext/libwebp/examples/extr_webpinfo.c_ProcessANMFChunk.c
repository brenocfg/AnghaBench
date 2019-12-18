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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  WebPInfoStatus ;
struct TYPE_5__ {int is_processing_anim_frame_; int frame_width_; int frame_height_; scalar_t__ anim_frame_data_size_; scalar_t__ seen_image_subchunk_; scalar_t__ seen_alpha_subchunk_; scalar_t__ canvas_height_; scalar_t__ canvas_width_; int /*<<< orphan*/  quiet_; int /*<<< orphan*/ * chunk_counts_; } ;
typedef  TYPE_1__ WebPInfo ;
struct TYPE_6__ {int* payload_; scalar_t__ size_; } ;
typedef  TYPE_2__ ChunkData ;

/* Variables and functions */
 scalar_t__ ANMF_CHUNK_SIZE ; 
 size_t CHUNK_ANIM ; 
 size_t CHUNK_ANMF ; 
 scalar_t__ CHUNK_HEADER_SIZE ; 
 int /*<<< orphan*/  LOG_ERROR (char*) ; 
 int MAX_DURATION ; 
 int MAX_POSITION_OFFSET ; 
 int ReadLE24 (int const**) ; 
 int /*<<< orphan*/  WEBP_INFO_INVALID_PARAM ; 
 int /*<<< orphan*/  WEBP_INFO_OK ; 
 int /*<<< orphan*/  WEBP_INFO_PARSE_ERROR ; 
 int /*<<< orphan*/  WEBP_INFO_TRUNCATED_DATA ; 
 int /*<<< orphan*/  printf (char*,int,int,int,int,int,int,int) ; 

__attribute__((used)) static WebPInfoStatus ProcessANMFChunk(const ChunkData* const chunk_data,
                                       WebPInfo* const webp_info) {
  const uint8_t* data = chunk_data->payload_;
  int offset_x, offset_y, width, height, duration, blend, dispose, temp;
  if (webp_info->is_processing_anim_frame_) {
    LOG_ERROR("ANMF chunk detected within another ANMF chunk.");
    return WEBP_INFO_PARSE_ERROR;
  }
  if (!webp_info->chunk_counts_[CHUNK_ANIM]) {
    LOG_ERROR("ANMF chunk detected before ANIM chunk.");
    return WEBP_INFO_PARSE_ERROR;
  }
  if (chunk_data->size_ <= CHUNK_HEADER_SIZE + ANMF_CHUNK_SIZE) {
    LOG_ERROR("Truncated data detected when parsing ANMF chunk.");
    return WEBP_INFO_TRUNCATED_DATA;
  }
  offset_x = 2 * ReadLE24(&data);
  offset_y = 2 * ReadLE24(&data);
  width = 1 + ReadLE24(&data);
  height = 1 + ReadLE24(&data);
  duration = ReadLE24(&data);
  temp = *data;
  dispose = temp & 1;
  blend = (temp >> 1) & 1;
  ++webp_info->chunk_counts_[CHUNK_ANMF];
  if (!webp_info->quiet_) {
    printf("  Offset_X: %d\n  Offset_Y: %d\n  Width: %d\n  Height: %d\n"
           "  Duration: %d\n  Dispose: %d\n  Blend: %d\n",
           offset_x, offset_y, width, height, duration, dispose, blend);
  }
  if (duration > MAX_DURATION) {
    LOG_ERROR("Invalid duration parameter in ANMF chunk.");
    return WEBP_INFO_INVALID_PARAM;
  }
  if (offset_x > MAX_POSITION_OFFSET || offset_y > MAX_POSITION_OFFSET) {
    LOG_ERROR("Invalid offset parameters in ANMF chunk.");
    return WEBP_INFO_INVALID_PARAM;
  }
  if ((uint64_t)offset_x + width > (uint64_t)webp_info->canvas_width_ ||
      (uint64_t)offset_y + height > (uint64_t)webp_info->canvas_height_) {
    LOG_ERROR("Frame exceeds canvas in ANMF chunk.");
    return WEBP_INFO_INVALID_PARAM;
  }
  webp_info->is_processing_anim_frame_ = 1;
  webp_info->seen_alpha_subchunk_ = 0;
  webp_info->seen_image_subchunk_ = 0;
  webp_info->frame_width_ = width;
  webp_info->frame_height_ = height;
  webp_info->anim_frame_data_size_ =
      chunk_data->size_ - CHUNK_HEADER_SIZE - ANMF_CHUNK_SIZE;
  return WEBP_INFO_OK;
}