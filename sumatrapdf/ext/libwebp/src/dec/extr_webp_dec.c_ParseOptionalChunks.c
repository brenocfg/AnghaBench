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
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  VP8StatusCode ;

/* Variables and functions */
 size_t CHUNK_HEADER_SIZE ; 
 size_t GetLE32 (int /*<<< orphan*/  const*) ; 
 size_t MAX_CHUNK_PAYLOAD ; 
 int TAG_SIZE ; 
 int VP8X_CHUNK_SIZE ; 
 int /*<<< orphan*/  VP8_STATUS_BITSTREAM_ERROR ; 
 int /*<<< orphan*/  VP8_STATUS_NOT_ENOUGH_DATA ; 
 int /*<<< orphan*/  VP8_STATUS_OK ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/  const*,char*,int) ; 

__attribute__((used)) static VP8StatusCode ParseOptionalChunks(const uint8_t** const data,
                                         size_t* const data_size,
                                         size_t const riff_size,
                                         const uint8_t** const alpha_data,
                                         size_t* const alpha_size) {
  const uint8_t* buf;
  size_t buf_size;
  uint32_t total_size = TAG_SIZE +           // "WEBP".
                        CHUNK_HEADER_SIZE +  // "VP8Xnnnn".
                        VP8X_CHUNK_SIZE;     // data.
  assert(data != NULL);
  assert(data_size != NULL);
  buf = *data;
  buf_size = *data_size;

  assert(alpha_data != NULL);
  assert(alpha_size != NULL);
  *alpha_data = NULL;
  *alpha_size = 0;

  while (1) {
    uint32_t chunk_size;
    uint32_t disk_chunk_size;   // chunk_size with padding

    *data = buf;
    *data_size = buf_size;

    if (buf_size < CHUNK_HEADER_SIZE) {  // Insufficient data.
      return VP8_STATUS_NOT_ENOUGH_DATA;
    }

    chunk_size = GetLE32(buf + TAG_SIZE);
    if (chunk_size > MAX_CHUNK_PAYLOAD) {
      return VP8_STATUS_BITSTREAM_ERROR;          // Not a valid chunk size.
    }
    // For odd-sized chunk-payload, there's one byte padding at the end.
    disk_chunk_size = (CHUNK_HEADER_SIZE + chunk_size + 1) & ~1;
    total_size += disk_chunk_size;

    // Check that total bytes skipped so far does not exceed riff_size.
    if (riff_size > 0 && (total_size > riff_size)) {
      return VP8_STATUS_BITSTREAM_ERROR;          // Not a valid chunk size.
    }

    // Start of a (possibly incomplete) VP8/VP8L chunk implies that we have
    // parsed all the optional chunks.
    // Note: This check must occur before the check 'buf_size < disk_chunk_size'
    // below to allow incomplete VP8/VP8L chunks.
    if (!memcmp(buf, "VP8 ", TAG_SIZE) ||
        !memcmp(buf, "VP8L", TAG_SIZE)) {
      return VP8_STATUS_OK;
    }

    if (buf_size < disk_chunk_size) {             // Insufficient data.
      return VP8_STATUS_NOT_ENOUGH_DATA;
    }

    if (!memcmp(buf, "ALPH", TAG_SIZE)) {         // A valid ALPH header.
      *alpha_data = buf + CHUNK_HEADER_SIZE;
      *alpha_size = chunk_size;
    }

    // We have a full and valid chunk; skip it.
    buf += disk_chunk_size;
    buf_size -= disk_chunk_size;
  }
}