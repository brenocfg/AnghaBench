#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  eof_; } ;
struct TYPE_6__ {int mb_w_; TYPE_1__ br_; } ;
typedef  TYPE_2__ VP8Decoder ;
typedef  int /*<<< orphan*/  VP8BitReader ;

/* Variables and functions */
 int /*<<< orphan*/  ParseIntraMode (int /*<<< orphan*/ * const,TYPE_2__* const,int) ; 

int VP8ParseIntraModeRow(VP8BitReader* const br, VP8Decoder* const dec) {
  int mb_x;
  for (mb_x = 0; mb_x < dec->mb_w_; ++mb_x) {
    ParseIntraMode(br, dec, mb_x);
  }
  return !dec->br_.eof_;
}