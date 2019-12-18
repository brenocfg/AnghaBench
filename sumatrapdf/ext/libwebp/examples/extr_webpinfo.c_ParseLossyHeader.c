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
typedef  int uint8_t ;
typedef  int uint64_t ;
typedef  int const uint32_t ;
typedef  scalar_t__ WebPInfoStatus ;
typedef  int /*<<< orphan*/  WebPInfo ;
struct TYPE_3__ {int* payload_; scalar_t__ size_; } ;
typedef  TYPE_1__ ChunkData ;

/* Variables and functions */
 scalar_t__ CHUNK_HEADER_SIZE ; 
 int /*<<< orphan*/  GET_BITS (int,int) ; 
 int /*<<< orphan*/  GET_SIGNED_BITS (int,int) ; 
 int /*<<< orphan*/  LOG_ERROR (char*) ; 
 scalar_t__ ParseLossyFilterHeader (int /*<<< orphan*/  const* const,int const*,size_t,int* const) ; 
 scalar_t__ ParseLossySegmentHeader (int /*<<< orphan*/  const* const,int const*,size_t,int* const) ; 
 scalar_t__ WEBP_INFO_BITSTREAM_ERROR ; 
 scalar_t__ WEBP_INFO_OK ; 
 scalar_t__ WEBP_INFO_TRUNCATED_DATA ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static WebPInfoStatus ParseLossyHeader(const ChunkData* const chunk_data,
                                       const WebPInfo* const webp_info) {
  const uint8_t* data = chunk_data->payload_;
  size_t data_size = chunk_data->size_ - CHUNK_HEADER_SIZE;
  const uint32_t bits = (uint32_t)data[0] | (data[1] << 8) | (data[2] << 16);
  const int key_frame = !(bits & 1);
  const int profile = (bits >> 1) & 7;
  const int display = (bits >> 4) & 1;
  const uint32_t partition0_length = (bits >> 5);
  WebPInfoStatus status = WEBP_INFO_OK;
  uint64_t bit_position = 0;
  uint64_t* const bit_pos = &bit_position;
  int colorspace, clamp_type;
  printf("  Parsing lossy bitstream...\n");
  // Calling WebPGetFeatures() in ProcessImageChunk() should ensure this.
  assert(chunk_data->size_ >= CHUNK_HEADER_SIZE + 10);
  if (profile > 3) {
    LOG_ERROR("Unknown profile.");
    return WEBP_INFO_BITSTREAM_ERROR;
  }
  if (!display) {
    LOG_ERROR("Frame is not displayable.");
    return WEBP_INFO_BITSTREAM_ERROR;
  }
  data += 3;
  data_size -= 3;
  printf("  Key frame:        %s\n"
         "  Profile:          %d\n"
         "  Display:          %s\n"
         "  Part. 0 length:   %d\n",
         key_frame ? "Yes" : "No", profile,
         display ? "Yes" : "No", partition0_length);
  if (key_frame) {
    if (!(data[0] == 0x9d && data[1] == 0x01 && data[2] == 0x2a)) {
      LOG_ERROR("Invalid lossy bitstream signature.");
      return WEBP_INFO_BITSTREAM_ERROR;
    }
    printf("  Width:            %d\n"
           "  X scale:          %d\n"
           "  Height:           %d\n"
           "  Y scale:          %d\n",
           ((data[4] << 8) | data[3]) & 0x3fff, data[4] >> 6,
           ((data[6] << 8) | data[5]) & 0x3fff, data[6] >> 6);
    data += 7;
    data_size -= 7;
  } else {
    LOG_ERROR("Non-keyframe detected in lossy bitstream.");
    return WEBP_INFO_BITSTREAM_ERROR;
  }
  if (partition0_length >= data_size) {
    LOG_ERROR("Bad partition length.");
    return WEBP_INFO_BITSTREAM_ERROR;
  }
  GET_BITS(colorspace, 1);
  GET_BITS(clamp_type, 1);
  printf("  Color space:      %d\n", colorspace);
  printf("  Clamp type:       %d\n", clamp_type);
  status = ParseLossySegmentHeader(webp_info, data, data_size, bit_pos);
  if (status != WEBP_INFO_OK) return status;
  status = ParseLossyFilterHeader(webp_info, data, data_size, bit_pos);
  if (status != WEBP_INFO_OK) return status;
  {  // Partition number and size.
    const uint8_t* part_size = data + partition0_length;
    int num_parts, i;
    size_t part_data_size;
    GET_BITS(num_parts, 2);
    num_parts = 1 << num_parts;
    if ((int)(data_size - partition0_length) < (num_parts - 1) * 3) {
      LOG_ERROR("Truncated lossy bitstream.");
      return WEBP_INFO_TRUNCATED_DATA;
    }
    part_data_size = data_size - partition0_length - (num_parts - 1) * 3;
    printf("  Total partitions: %d\n", num_parts);
    for (i = 1; i < num_parts; ++i) {
      const size_t psize =
          part_size[0] | (part_size[1] << 8) | (part_size[2] << 16);
      if (psize > part_data_size) {
        LOG_ERROR("Truncated partition.");
        return WEBP_INFO_TRUNCATED_DATA;
      }
      printf("  Part. %d length:   %d\n", i, (int)psize);
      part_data_size -= psize;
      part_size += 3;
    }
  }
  // Quantizer.
  {
    int base_q, bit;
    int dq_y1_dc = 0, dq_y2_dc = 0, dq_y2_ac = 0, dq_uv_dc = 0, dq_uv_ac = 0;
    GET_BITS(base_q, 7);
    GET_BITS(bit, 1);
    if (bit) GET_SIGNED_BITS(dq_y1_dc, 4);
    GET_BITS(bit, 1);
    if (bit) GET_SIGNED_BITS(dq_y2_dc, 4);
    GET_BITS(bit, 1);
    if (bit) GET_SIGNED_BITS(dq_y2_ac, 4);
    GET_BITS(bit, 1);
    if (bit) GET_SIGNED_BITS(dq_uv_dc, 4);
    GET_BITS(bit, 1);
    if (bit) GET_SIGNED_BITS(dq_uv_ac, 4);
    printf("  Base Q:           %d\n", base_q);
    printf("  DQ Y1 DC:         %d\n", dq_y1_dc);
    printf("  DQ Y2 DC:         %d\n", dq_y2_dc);
    printf("  DQ Y2 AC:         %d\n", dq_y2_ac);
    printf("  DQ UV DC:         %d\n", dq_uv_dc);
    printf("  DQ UV AC:         %d\n", dq_uv_ac);
  }
  if ((*bit_pos >> 3) >= partition0_length) {
    LOG_ERROR("Truncated lossy bitstream.");
    return WEBP_INFO_TRUNCATED_DATA;
  }
  return WEBP_INFO_OK;
}