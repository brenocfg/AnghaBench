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
struct TYPE_5__ {int num_parts_; int preds_w_; int mb_w_; int /*<<< orphan*/  uv_top_; int /*<<< orphan*/  y_top_; scalar_t__ mb_info_; int /*<<< orphan*/  nz_; scalar_t__ preds_; int /*<<< orphan*/ * parts_; } ;
typedef  TYPE_1__ VP8Encoder ;
struct TYPE_6__ {int y_; int /*<<< orphan*/  uv_top_; int /*<<< orphan*/  y_top_; scalar_t__ mb_; int /*<<< orphan*/  nz_; scalar_t__ preds_; int /*<<< orphan*/ * bw_; scalar_t__ x_; TYPE_1__* enc_; } ;
typedef  TYPE_2__ VP8EncIterator ;

/* Variables and functions */
 int /*<<< orphan*/  InitLeft (TYPE_2__* const) ; 

void VP8IteratorSetRow(VP8EncIterator* const it, int y) {
  VP8Encoder* const enc = it->enc_;
  it->x_ = 0;
  it->y_ = y;
  it->bw_ = &enc->parts_[y & (enc->num_parts_ - 1)];
  it->preds_ = enc->preds_ + y * 4 * enc->preds_w_;
  it->nz_ = enc->nz_;
  it->mb_ = enc->mb_info_ + y * enc->mb_w_;
  it->y_top_ = enc->y_top_;
  it->uv_top_ = enc->uv_top_;
  InitLeft(it);
}