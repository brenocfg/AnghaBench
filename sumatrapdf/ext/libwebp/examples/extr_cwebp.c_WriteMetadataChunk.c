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
typedef  char uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int size; char const* bytes; } ;
typedef  TYPE_1__ MetadataPayload ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ WriteLE32 (int /*<<< orphan*/ * const,int /*<<< orphan*/ ) ; 
 size_t const fwrite (char const*,size_t const,size_t const,int /*<<< orphan*/ * const) ; 
 size_t const kTagSize ; 

__attribute__((used)) static int WriteMetadataChunk(FILE* const out, const char fourcc[4],
                              const MetadataPayload* const payload) {
  const uint8_t zero = 0;
  const size_t need_padding = payload->size & 1;
  int ok = (fwrite(fourcc, kTagSize, 1, out) == 1);
  ok = ok && WriteLE32(out, (uint32_t)payload->size);
  ok = ok && (fwrite(payload->bytes, payload->size, 1, out) == 1);
  return ok && (fwrite(&zero, need_padding, need_padding, out) == need_padding);
}