#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int width; int height; } ;
typedef  TYPE_1__ WebPPicture ;
struct TYPE_5__ {int /*<<< orphan*/ * refs_; int /*<<< orphan*/  hash_chain_; TYPE_1__* pic_; } ;
typedef  TYPE_2__ VP8LEncoder ;

/* Variables and functions */
 int const MAX_REFS_BLOCK_PER_IMAGE ; 
 int /*<<< orphan*/  VP8LBackwardRefsInit (int /*<<< orphan*/ *,int const) ; 
 int /*<<< orphan*/  VP8LHashChainInit (int /*<<< orphan*/ *,int const) ; 

__attribute__((used)) static int EncoderInit(VP8LEncoder* const enc) {
  const WebPPicture* const pic = enc->pic_;
  const int width = pic->width;
  const int height = pic->height;
  const int pix_cnt = width * height;
  // we round the block size up, so we're guaranteed to have
  // at most MAX_REFS_BLOCK_PER_IMAGE blocks used:
  const int refs_block_size = (pix_cnt - 1) / MAX_REFS_BLOCK_PER_IMAGE + 1;
  int i;
  if (!VP8LHashChainInit(&enc->hash_chain_, pix_cnt)) return 0;

  for (i = 0; i < 3; ++i) VP8LBackwardRefsInit(&enc->refs_[i], refs_block_size);

  return 1;
}