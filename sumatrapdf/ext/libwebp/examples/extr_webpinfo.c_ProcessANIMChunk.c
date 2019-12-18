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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  WebPInfoStatus ;
struct TYPE_5__ {int bgcolor_; int loop_count_; int /*<<< orphan*/  quiet_; int /*<<< orphan*/ * chunk_counts_; } ;
typedef  TYPE_1__ WebPInfo ;
struct TYPE_6__ {scalar_t__ size_; int /*<<< orphan*/ * payload_; } ;
typedef  TYPE_2__ ChunkData ;

/* Variables and functions */
 scalar_t__ ANIM_CHUNK_SIZE ; 
 size_t CHUNK_ANIM ; 
 scalar_t__ CHUNK_HEADER_SIZE ; 
 size_t CHUNK_VP8X ; 
 int /*<<< orphan*/  LOG_ERROR (char*) ; 
 int /*<<< orphan*/  LOG_WARN (char*) ; 
 int MAX_LOOP_COUNT ; 
 int ReadLE16 (int /*<<< orphan*/  const**) ; 
 int ReadLE32 (int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  WEBP_INFO_OK ; 
 int /*<<< orphan*/  WEBP_INFO_PARSE_ERROR ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 

__attribute__((used)) static WebPInfoStatus ProcessANIMChunk(const ChunkData* const chunk_data,
                                       WebPInfo* const webp_info) {
  const uint8_t* data = chunk_data->payload_;
  if (!webp_info->chunk_counts_[CHUNK_VP8X]) {
    LOG_ERROR("ANIM chunk detected before VP8X chunk.");
    return WEBP_INFO_PARSE_ERROR;
  }
  if (chunk_data->size_ != ANIM_CHUNK_SIZE + CHUNK_HEADER_SIZE) {
    LOG_ERROR("Corrupted ANIM chunk.");
    return WEBP_INFO_PARSE_ERROR;
  }
  webp_info->bgcolor_ = ReadLE32(&data);
  webp_info->loop_count_ = ReadLE16(&data);
  ++webp_info->chunk_counts_[CHUNK_ANIM];
  if (!webp_info->quiet_) {
    printf("  Background color:(ARGB) %02x %02x %02x %02x\n",
           (webp_info->bgcolor_ >> 24) & 0xff,
           (webp_info->bgcolor_ >> 16) & 0xff,
           (webp_info->bgcolor_ >> 8) & 0xff,
           webp_info->bgcolor_ & 0xff);
    printf("  Loop count      : %d\n", webp_info->loop_count_);
  }
  if (webp_info->loop_count_ > MAX_LOOP_COUNT) {
    LOG_WARN("Loop count is out of range in ANIM chunk.");
  }
  return WEBP_INFO_OK;
}