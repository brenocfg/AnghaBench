#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  WebPInfoStatus ;
typedef  int /*<<< orphan*/  WebPInfo ;
struct TYPE_11__ {size_t offset_; size_t size_; scalar_t__ id_; int /*<<< orphan*/  payload_; } ;
struct TYPE_10__ {size_t start_; } ;
typedef  TYPE_1__ MemBuffer ;
typedef  scalar_t__ ChunkID ;
typedef  TYPE_2__ ChunkData ;

/* Variables and functions */
 int const ANMF_CHUNK_SIZE ; 
 scalar_t__ CHUNK_ANMF ; 
 int const CHUNK_HEADER_SIZE ; 
 int CHUNK_TYPES ; 
 int /*<<< orphan*/  GetBuffer (TYPE_1__* const) ; 
 int /*<<< orphan*/  LOG_ERROR (char*) ; 
 int const MAX_CHUNK_PAYLOAD ; 
 int const MemDataSize (TYPE_1__* const) ; 
 int ReadMemBufLE32 (TYPE_1__* const) ; 
 int /*<<< orphan*/  Skip (TYPE_1__* const,int const) ; 
 int /*<<< orphan*/  TAG_SIZE ; 
 int /*<<< orphan*/  WEBP_INFO_INVALID_PARAM ; 
 int /*<<< orphan*/  WEBP_INFO_OK ; 
 int /*<<< orphan*/  WEBP_INFO_PARSE_ERROR ; 
 int /*<<< orphan*/  WEBP_INFO_TRUNCATED_DATA ; 
 int /*<<< orphan*/ * kWebPChunkTags ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__* const,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static WebPInfoStatus ParseChunk(const WebPInfo* const webp_info,
                                 MemBuffer* const mem,
                                 ChunkData* const chunk_data) {
  memset(chunk_data, 0, sizeof(*chunk_data));
  if (MemDataSize(mem) < CHUNK_HEADER_SIZE) {
    LOG_ERROR("Truncated data detected when parsing chunk header.");
    return WEBP_INFO_TRUNCATED_DATA;
  } else {
    const size_t chunk_start_offset = mem->start_;
    const uint32_t fourcc = ReadMemBufLE32(mem);
    const uint32_t payload_size = ReadMemBufLE32(mem);
    const uint32_t payload_size_padded = payload_size + (payload_size & 1);
    const size_t chunk_size = CHUNK_HEADER_SIZE + payload_size_padded;
    int i;
    if (payload_size > MAX_CHUNK_PAYLOAD) {
      LOG_ERROR("Size of chunk payload is over limit.");
      return WEBP_INFO_INVALID_PARAM;
    }
    if (payload_size_padded > MemDataSize(mem)){
      LOG_ERROR("Truncated data detected when parsing chunk payload.");
      return WEBP_INFO_TRUNCATED_DATA;
    }
    for (i = 0; i < CHUNK_TYPES; ++i) {
      if (!memcmp(kWebPChunkTags[i], &fourcc, TAG_SIZE)) break;
    }
    chunk_data->offset_ = chunk_start_offset;
    chunk_data->size_ = chunk_size;
    chunk_data->id_ = (ChunkID)i;
    chunk_data->payload_ = GetBuffer(mem);
    if (chunk_data->id_ == CHUNK_ANMF) {
      if (payload_size != payload_size_padded) {
        LOG_ERROR("ANMF chunk size should always be even.");
        return WEBP_INFO_PARSE_ERROR;
      }
      // There are sub-chunks to be parsed in an ANMF chunk.
      Skip(mem, ANMF_CHUNK_SIZE);
    } else {
      Skip(mem, payload_size_padded);
    }
    return WEBP_INFO_OK;
  }
}