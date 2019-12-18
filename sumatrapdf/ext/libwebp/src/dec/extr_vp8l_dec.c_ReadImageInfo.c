#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  eos_; } ;
typedef  TYPE_1__ VP8LBitReader ;

/* Variables and functions */
 int VP8LReadBits (TYPE_1__* const,int) ; 
 int VP8L_IMAGE_SIZE_BITS ; 
 int VP8L_MAGIC_BYTE ; 
 int VP8L_VERSION_BITS ; 

__attribute__((used)) static int ReadImageInfo(VP8LBitReader* const br,
                         int* const width, int* const height,
                         int* const has_alpha) {
  if (VP8LReadBits(br, 8) != VP8L_MAGIC_BYTE) return 0;
  *width = VP8LReadBits(br, VP8L_IMAGE_SIZE_BITS) + 1;
  *height = VP8LReadBits(br, VP8L_IMAGE_SIZE_BITS) + 1;
  *has_alpha = VP8LReadBits(br, 1);
  if (VP8LReadBits(br, VP8L_VERSION_BITS) != 0) return 0;
  return !br->eos_;
}