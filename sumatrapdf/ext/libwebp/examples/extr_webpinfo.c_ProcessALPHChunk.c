#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ WebPInfoStatus ;
struct TYPE_4__ {int seen_alpha_subchunk_; int has_alpha_; scalar_t__ parse_bitstream_; scalar_t__* chunk_counts_; scalar_t__ seen_image_subchunk_; int /*<<< orphan*/ * anmf_subchunk_counts_; scalar_t__ is_processing_anim_frame_; } ;
typedef  TYPE_1__ WebPInfo ;
typedef  int /*<<< orphan*/  ChunkData ;

/* Variables and functions */
 size_t CHUNK_ALPHA ; 
 size_t CHUNK_ANIM ; 
 size_t CHUNK_ANMF ; 
 size_t CHUNK_VP8 ; 
 size_t CHUNK_VP8X ; 
 int /*<<< orphan*/  LOG_ERROR (char*) ; 
 scalar_t__ ParseAlphaHeader (int /*<<< orphan*/  const* const,TYPE_1__* const) ; 
 scalar_t__ const WEBP_INFO_OK ; 
 scalar_t__ WEBP_INFO_PARSE_ERROR ; 

__attribute__((used)) static WebPInfoStatus ProcessALPHChunk(const ChunkData* const chunk_data,
                                       WebPInfo* const webp_info) {
  if (webp_info->is_processing_anim_frame_) {
    ++webp_info->anmf_subchunk_counts_[2];
    if (webp_info->seen_alpha_subchunk_) {
      LOG_ERROR("Consecutive ALPH sub-chunks in an ANMF chunk.");
      return WEBP_INFO_PARSE_ERROR;
    }
    webp_info->seen_alpha_subchunk_ = 1;

    if (webp_info->seen_image_subchunk_) {
      LOG_ERROR("ALPHA sub-chunk detected after VP8 sub-chunk "
                "in an ANMF chunk.");
      return WEBP_INFO_PARSE_ERROR;
    }
  } else {
    if (webp_info->chunk_counts_[CHUNK_ANIM] ||
        webp_info->chunk_counts_[CHUNK_ANMF]) {
      LOG_ERROR("ALPHA chunk and ANIM/ANMF chunk are both detected.");
      return WEBP_INFO_PARSE_ERROR;
    }
    if (!webp_info->chunk_counts_[CHUNK_VP8X]) {
      LOG_ERROR("ALPHA chunk detected before VP8X chunk.");
      return WEBP_INFO_PARSE_ERROR;
    }
    if (webp_info->chunk_counts_[CHUNK_VP8]) {
      LOG_ERROR("ALPHA chunk detected after VP8 chunk.");
      return WEBP_INFO_PARSE_ERROR;
    }
    if (webp_info->chunk_counts_[CHUNK_ALPHA]) {
      LOG_ERROR("Multiple ALPHA chunks detected.");
      return WEBP_INFO_PARSE_ERROR;
    }
    ++webp_info->chunk_counts_[CHUNK_ALPHA];
  }
  webp_info->has_alpha_ = 1;
  if (webp_info->parse_bitstream_) {
    const WebPInfoStatus status = ParseAlphaHeader(chunk_data, webp_info);
    if (status != WEBP_INFO_OK) return status;
  }
  return WEBP_INFO_OK;
}