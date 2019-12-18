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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ WebPInfoStatus ;
typedef  int /*<<< orphan*/  WebPInfo ;
struct TYPE_3__ {scalar_t__* payload_; size_t size_; } ;
typedef  TYPE_1__ ChunkData ;

/* Variables and functions */
 size_t CHUNK_HEADER_SIZE ; 
 int /*<<< orphan*/  LL_GET_BITS (int,int) ; 
 int /*<<< orphan*/  LOG_ERROR (char*) ; 
 scalar_t__ ParseLosslessTransform (int /*<<< orphan*/ * const,scalar_t__ const*,size_t,int /*<<< orphan*/ * const) ; 
 size_t VP8L_FRAME_HEADER_SIZE ; 
 scalar_t__ const VP8L_MAGIC_BYTE ; 
 scalar_t__ WEBP_INFO_BITSTREAM_ERROR ; 
 scalar_t__ WEBP_INFO_OK ; 
 scalar_t__ WEBP_INFO_TRUNCATED_DATA ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static WebPInfoStatus ParseLosslessHeader(const ChunkData* const chunk_data,
                                          WebPInfo* const webp_info) {
  const uint8_t* data = chunk_data->payload_;
  size_t data_size = chunk_data->size_ - CHUNK_HEADER_SIZE;
  uint64_t bit_position = 0;
  uint64_t* const bit_pos = &bit_position;
  WebPInfoStatus status;
  printf("  Parsing lossless bitstream...\n");
  if (data_size < VP8L_FRAME_HEADER_SIZE) {
    LOG_ERROR("Truncated lossless bitstream.");
    return WEBP_INFO_TRUNCATED_DATA;
  }
  if (data[0] != VP8L_MAGIC_BYTE) {
    LOG_ERROR("Invalid lossless bitstream signature.");
    return WEBP_INFO_BITSTREAM_ERROR;
  }
  data += 1;
  data_size -= 1;
  {
    int width, height, has_alpha, version;
    LL_GET_BITS(width, 14);
    LL_GET_BITS(height, 14);
    LL_GET_BITS(has_alpha, 1);
    LL_GET_BITS(version, 3);
    width += 1;
    height += 1;
    printf("  Width:            %d\n", width);
    printf("  Height:           %d\n", height);
    printf("  Alpha:            %d\n", has_alpha);
    printf("  Version:          %d\n", version);
  }
  status = ParseLosslessTransform(webp_info, data, data_size, bit_pos);
  if (status != WEBP_INFO_OK) return status;
  return WEBP_INFO_OK;
}