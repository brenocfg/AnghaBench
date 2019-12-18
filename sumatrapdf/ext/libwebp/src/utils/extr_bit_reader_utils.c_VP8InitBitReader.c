#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int range_; int bits_; scalar_t__ eof_; scalar_t__ value_; } ;
typedef  TYPE_1__ VP8BitReader ;

/* Variables and functions */
 int /*<<< orphan*/  VP8BitReaderSetBuffer (TYPE_1__* const,int /*<<< orphan*/  const* const,size_t) ; 
 int /*<<< orphan*/  VP8LoadNewBytes (TYPE_1__* const) ; 
 int /*<<< orphan*/  assert (int) ; 

void VP8InitBitReader(VP8BitReader* const br,
                      const uint8_t* const start, size_t size) {
  assert(br != NULL);
  assert(start != NULL);
  assert(size < (1u << 31));   // limit ensured by format and upstream checks
  br->range_   = 255 - 1;
  br->value_   = 0;
  br->bits_    = -8;   // to load the very first 8bits
  br->eof_     = 0;
  VP8BitReaderSetBuffer(br, start, size);
  VP8LoadNewBytes(br);
}