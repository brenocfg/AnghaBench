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
struct TYPE_5__ {int* nz_; scalar_t__* left_nz_; TYPE_1__* mb_; } ;
typedef  TYPE_2__ VP8EncIterator ;
struct TYPE_4__ {int type_; } ;

/* Variables and functions */

__attribute__((used)) static void ResetAfterSkip(VP8EncIterator* const it) {
  if (it->mb_->type_ == 1) {
    *it->nz_ = 0;  // reset all predictors
    it->left_nz_[8] = 0;
  } else {
    *it->nz_ &= (1 << 24);  // preserve the dc_nz bit
  }
}