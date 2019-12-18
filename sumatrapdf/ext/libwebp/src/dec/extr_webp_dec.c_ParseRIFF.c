#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  VP8StatusCode ;

/* Variables and functions */
 size_t CHUNK_HEADER_SIZE ; 
 int GetLE32 (int /*<<< orphan*/  const*) ; 
 int const MAX_CHUNK_PAYLOAD ; 
 size_t RIFF_HEADER_SIZE ; 
 int TAG_SIZE ; 
 int /*<<< orphan*/  VP8_STATUS_BITSTREAM_ERROR ; 
 int /*<<< orphan*/  VP8_STATUS_NOT_ENOUGH_DATA ; 
 int /*<<< orphan*/  VP8_STATUS_OK ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/  const*,char*,int) ; 

__attribute__((used)) static VP8StatusCode ParseRIFF(const uint8_t** const data,
                               size_t* const data_size, int have_all_data,
                               size_t* const riff_size) {
  assert(data != NULL);
  assert(data_size != NULL);
  assert(riff_size != NULL);

  *riff_size = 0;  // Default: no RIFF present.
  if (*data_size >= RIFF_HEADER_SIZE && !memcmp(*data, "RIFF", TAG_SIZE)) {
    if (memcmp(*data + 8, "WEBP", TAG_SIZE)) {
      return VP8_STATUS_BITSTREAM_ERROR;  // Wrong image file signature.
    } else {
      const uint32_t size = GetLE32(*data + TAG_SIZE);
      // Check that we have at least one chunk (i.e "WEBP" + "VP8?nnnn").
      if (size < TAG_SIZE + CHUNK_HEADER_SIZE) {
        return VP8_STATUS_BITSTREAM_ERROR;
      }
      if (size > MAX_CHUNK_PAYLOAD) {
        return VP8_STATUS_BITSTREAM_ERROR;
      }
      if (have_all_data && (size > *data_size - CHUNK_HEADER_SIZE)) {
        return VP8_STATUS_NOT_ENOUGH_DATA;  // Truncated bitstream.
      }
      // We have a RIFF container. Skip it.
      *riff_size = size;
      *data += RIFF_HEADER_SIZE;
      *data_size -= RIFF_HEADER_SIZE;
    }
  }
  return VP8_STATUS_OK;
}