#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int width; int height; } ;
typedef  TYPE_1__ WebPPicture ;
struct TYPE_7__ {int /*<<< orphan*/  error_; } ;
typedef  TYPE_2__ VP8LBitWriter ;

/* Variables and functions */
 int /*<<< orphan*/  VP8LPutBits (TYPE_2__* const,int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VP8L_IMAGE_SIZE_BITS ; 
 int const WEBP_MAX_DIMENSION ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int WriteImageSize(const WebPPicture* const pic,
                          VP8LBitWriter* const bw) {
  const int width = pic->width - 1;
  const int height = pic->height - 1;
  assert(width < WEBP_MAX_DIMENSION && height < WEBP_MAX_DIMENSION);

  VP8LPutBits(bw, width, VP8L_IMAGE_SIZE_BITS);
  VP8LPutBits(bw, height, VP8L_IMAGE_SIZE_BITS);
  return !bw->error_;
}