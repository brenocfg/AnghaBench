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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  WebPMuxError ;
struct TYPE_3__ {scalar_t__ size; int /*<<< orphan*/  const* bytes; } ;
typedef  TYPE_1__ WebPData ;
typedef  int /*<<< orphan*/  WebPChunk ;

/* Variables and functions */
 size_t CHUNK_HEADER_SIZE ; 
 int /*<<< orphan*/  ChunkAssignData (int /*<<< orphan*/ *,TYPE_1__*,int,scalar_t__) ; 
 scalar_t__ GetLE32 (int /*<<< orphan*/  const*) ; 
 scalar_t__ MAX_CHUNK_PAYLOAD ; 
 size_t SizeWithPadding (scalar_t__) ; 
 int TAG_SIZE ; 
 int /*<<< orphan*/  WEBP_MUX_BAD_DATA ; 
 int /*<<< orphan*/  WEBP_MUX_NOT_ENOUGH_DATA ; 

__attribute__((used)) static WebPMuxError ChunkVerifyAndAssign(WebPChunk* chunk,
                                         const uint8_t* data, size_t data_size,
                                         size_t riff_size, int copy_data) {
  uint32_t chunk_size;
  WebPData chunk_data;

  // Sanity checks.
  if (data_size < CHUNK_HEADER_SIZE) return WEBP_MUX_NOT_ENOUGH_DATA;
  chunk_size = GetLE32(data + TAG_SIZE);
  if (chunk_size > MAX_CHUNK_PAYLOAD) return WEBP_MUX_BAD_DATA;

  {
    const size_t chunk_disk_size = SizeWithPadding(chunk_size);
    if (chunk_disk_size > riff_size) return WEBP_MUX_BAD_DATA;
    if (chunk_disk_size > data_size) return WEBP_MUX_NOT_ENOUGH_DATA;
  }

  // Data assignment.
  chunk_data.bytes = data + CHUNK_HEADER_SIZE;
  chunk_data.size = chunk_size;
  return ChunkAssignData(chunk, &chunk_data, copy_data, GetLE32(data + 0));
}