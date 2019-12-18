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
struct TYPE_4__ {int mb_w_; int /*<<< orphan*/ * top_derr_; int /*<<< orphan*/ * nz_; int /*<<< orphan*/ * y_top_; } ;
typedef  TYPE_1__ VP8Encoder ;
struct TYPE_5__ {TYPE_1__* enc_; } ;
typedef  TYPE_2__ VP8EncIterator ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void InitTop(VP8EncIterator* const it) {
  const VP8Encoder* const enc = it->enc_;
  const size_t top_size = enc->mb_w_ * 16;
  memset(enc->y_top_, 127, 2 * top_size);
  memset(enc->nz_, 0, enc->mb_w_ * sizeof(*enc->nz_));
  if (enc->top_derr_ != NULL) {
    memset(enc->top_derr_, 0, enc->mb_w_ * sizeof(*enc->top_derr_));
  }
}