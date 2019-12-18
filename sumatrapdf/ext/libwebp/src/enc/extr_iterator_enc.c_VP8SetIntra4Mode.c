#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_7__ {TYPE_2__* mb_; TYPE_1__* enc_; int /*<<< orphan*/ * preds_; } ;
typedef  TYPE_3__ VP8EncIterator ;
struct TYPE_6__ {scalar_t__ type_; } ;
struct TYPE_5__ {int /*<<< orphan*/  preds_w_; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

void VP8SetIntra4Mode(const VP8EncIterator* const it, const uint8_t* modes) {
  uint8_t* preds = it->preds_;
  int y;
  for (y = 4; y > 0; --y) {
    memcpy(preds, modes, 4 * sizeof(*modes));
    preds += it->enc_->preds_w_;
    modes += 4;
  }
  it->mb_->type_ = 0;
}