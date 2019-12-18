#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WebPInfoStatus ;
struct TYPE_8__ {int /*<<< orphan*/  quiet_; } ;
typedef  TYPE_1__ WebPInfo ;
struct TYPE_9__ {size_t end_; } ;
typedef  TYPE_2__ MemBuffer ;

/* Variables and functions */
 size_t CHUNK_HEADER_SIZE ; 
 int /*<<< orphan*/  CHUNK_SIZE_BYTES ; 
 scalar_t__ GetBuffer (TYPE_2__* const) ; 
 size_t GetLE32 (scalar_t__) ; 
 int /*<<< orphan*/  LOG_ERROR (char*) ; 
 int /*<<< orphan*/  LOG_WARN (char*) ; 
 size_t MAX_CHUNK_PAYLOAD ; 
 size_t const MemDataSize (TYPE_2__* const) ; 
 size_t RIFF_HEADER_SIZE ; 
 int /*<<< orphan*/  Skip (TYPE_2__* const,size_t) ; 
 scalar_t__ TAG_SIZE ; 
 int /*<<< orphan*/  WEBP_INFO_OK ; 
 int /*<<< orphan*/  WEBP_INFO_PARSE_ERROR ; 
 int /*<<< orphan*/  WEBP_INFO_TRUNCATED_DATA ; 
 scalar_t__ memcmp (scalar_t__,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static WebPInfoStatus ParseRIFFHeader(const WebPInfo* const webp_info,
                                      MemBuffer* const mem) {
  const size_t min_size = RIFF_HEADER_SIZE + CHUNK_HEADER_SIZE;
  size_t riff_size;

  if (MemDataSize(mem) < min_size) {
    LOG_ERROR("Truncated data detected when parsing RIFF header.");
    return WEBP_INFO_TRUNCATED_DATA;
  }
  if (memcmp(GetBuffer(mem), "RIFF", CHUNK_SIZE_BYTES) ||
      memcmp(GetBuffer(mem) + CHUNK_HEADER_SIZE, "WEBP", CHUNK_SIZE_BYTES)) {
    LOG_ERROR("Corrupted RIFF header.");
    return WEBP_INFO_PARSE_ERROR;
  }
  riff_size = GetLE32(GetBuffer(mem) + TAG_SIZE);
  if (riff_size < CHUNK_HEADER_SIZE) {
    LOG_ERROR("RIFF size is too small.");
    return WEBP_INFO_PARSE_ERROR;
  }
  if (riff_size > MAX_CHUNK_PAYLOAD) {
    LOG_ERROR("RIFF size is over limit.");
    return WEBP_INFO_PARSE_ERROR;
  }
  riff_size += CHUNK_HEADER_SIZE;
  if (!webp_info->quiet_) {
    printf("RIFF HEADER:\n");
    printf("  File size: %6d\n", (int)riff_size);
  }
  if (riff_size < mem->end_) {
    LOG_WARN("RIFF size is smaller than the file size.");
    mem->end_ = riff_size;
  } else if (riff_size > mem->end_) {
    LOG_ERROR("Truncated data detected when parsing RIFF payload.");
    return WEBP_INFO_TRUNCATED_DATA;
  }
  Skip(mem, RIFF_HEADER_SIZE);
  return WEBP_INFO_OK;
}