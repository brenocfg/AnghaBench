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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
struct TYPE_3__ {int size; int /*<<< orphan*/ * bytes; } ;
typedef  TYPE_1__ MetadataPayload ;

/* Variables and functions */
 scalar_t__ kChunkHeaderSize ; 

__attribute__((used)) static int UpdateFlagsAndSize(const MetadataPayload* const payload,
                              int keep, int flag,
                              uint32_t* vp8x_flags, uint64_t* metadata_size) {
  if (keep && payload->bytes != NULL && payload->size > 0) {
    *vp8x_flags |= flag;
    *metadata_size += kChunkHeaderSize + payload->size + (payload->size & 1);
    return 1;
  }
  return 0;
}