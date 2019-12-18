#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WebPInfoStatus ;
struct TYPE_17__ {scalar_t__ anim_frame_data_size_; scalar_t__ is_processing_anim_frame_; int /*<<< orphan*/  seen_image_subchunk_; int /*<<< orphan*/ * chunk_counts_; int /*<<< orphan*/  quiet_; } ;
typedef  TYPE_1__ WebPInfo ;
struct TYPE_18__ {int id_; scalar_t__ size_; scalar_t__ offset_; } ;
typedef  int ChunkID ;
typedef  TYPE_2__ ChunkData ;

/* Variables and functions */
#define  CHUNK_ALPHA 137 
#define  CHUNK_ANIM 136 
#define  CHUNK_ANMF 135 
#define  CHUNK_EXIF 134 
#define  CHUNK_ICCP 133 
#define  CHUNK_UNKNOWN 132 
#define  CHUNK_VP8 131 
#define  CHUNK_VP8L 130 
#define  CHUNK_VP8X 129 
#define  CHUNK_XMP 128 
 int /*<<< orphan*/  LOG_ERROR (char*) ; 
 int /*<<< orphan*/  LOG_WARN (char*) ; 
 int /*<<< orphan*/  ProcessALPHChunk (TYPE_2__ const* const,TYPE_1__* const) ; 
 int /*<<< orphan*/  ProcessANIMChunk (TYPE_2__ const* const,TYPE_1__* const) ; 
 int /*<<< orphan*/  ProcessANMFChunk (TYPE_2__ const* const,TYPE_1__* const) ; 
 int /*<<< orphan*/  ProcessICCPChunk (TYPE_2__ const* const,TYPE_1__* const) ; 
 int /*<<< orphan*/  ProcessImageChunk (TYPE_2__ const* const,TYPE_1__* const) ; 
 int /*<<< orphan*/  ProcessVP8XChunk (TYPE_2__ const* const,TYPE_1__* const) ; 
 int /*<<< orphan*/  WEBP_INFO_OK ; 
 int /*<<< orphan*/  WEBP_INFO_PARSE_ERROR ; 
 int /*<<< orphan*/  WEBP_INFO_TRUNCATED_DATA ; 
 char** kWebPChunkTags ; 
 int /*<<< orphan*/  printf (char*,char const,char const,char const,char const,int,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int) ; 

__attribute__((used)) static WebPInfoStatus ProcessChunk(const ChunkData* const chunk_data,
                                   WebPInfo* const webp_info) {
  WebPInfoStatus status = WEBP_INFO_OK;
  ChunkID id = chunk_data->id_;
  if (chunk_data->id_ == CHUNK_UNKNOWN) {
    char error_message[50];
    snprintf(error_message, 50, "Unknown chunk at offset %6d, length %6d",
            (int)chunk_data->offset_, (int)chunk_data->size_);
    LOG_WARN(error_message);
  } else {
    if (!webp_info->quiet_) {
      const char* tag = kWebPChunkTags[chunk_data->id_];
      printf("Chunk %c%c%c%c at offset %6d, length %6d\n",
             tag[0], tag[1], tag[2], tag[3], (int)chunk_data->offset_,
             (int)chunk_data->size_);
    }
  }
  switch (id) {
    case CHUNK_VP8:
    case CHUNK_VP8L:
      status = ProcessImageChunk(chunk_data, webp_info);
      break;
    case CHUNK_VP8X:
      status = ProcessVP8XChunk(chunk_data, webp_info);
      break;
    case CHUNK_ALPHA:
      status = ProcessALPHChunk(chunk_data, webp_info);
      break;
    case CHUNK_ANIM:
      status = ProcessANIMChunk(chunk_data, webp_info);
      break;
    case CHUNK_ANMF:
      status = ProcessANMFChunk(chunk_data, webp_info);
      break;
    case CHUNK_ICCP:
      status = ProcessICCPChunk(chunk_data, webp_info);
      break;
    case CHUNK_EXIF:
    case CHUNK_XMP:
      ++webp_info->chunk_counts_[id];
      break;
    case CHUNK_UNKNOWN:
    default:
      break;
  }
  if (webp_info->is_processing_anim_frame_ && id != CHUNK_ANMF) {
    if (webp_info->anim_frame_data_size_ == chunk_data->size_) {
      if (!webp_info->seen_image_subchunk_) {
        LOG_ERROR("No VP8/VP8L chunk detected in an ANMF chunk.");
        return WEBP_INFO_PARSE_ERROR;
      }
      webp_info->is_processing_anim_frame_ = 0;
    } else if (webp_info->anim_frame_data_size_ > chunk_data->size_) {
      webp_info->anim_frame_data_size_ -= chunk_data->size_;
    } else {
      LOG_ERROR("Truncated data detected when parsing ANMF chunk.");
      return WEBP_INFO_TRUNCATED_DATA;
    }
  }
  return status;
}