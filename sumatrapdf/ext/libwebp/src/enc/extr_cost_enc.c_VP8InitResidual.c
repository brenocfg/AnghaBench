#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int coeff_type; int first; int /*<<< orphan*/  costs; int /*<<< orphan*/  stats; int /*<<< orphan*/  prob; } ;
typedef  TYPE_2__ VP8Residual ;
struct TYPE_6__ {int /*<<< orphan*/ * remapped_costs_; int /*<<< orphan*/ * stats_; int /*<<< orphan*/ * coeffs_; } ;
struct TYPE_8__ {TYPE_1__ proba_; } ;
typedef  TYPE_3__ VP8Encoder ;

/* Variables and functions */

void VP8InitResidual(int first, int coeff_type,
                     VP8Encoder* const enc, VP8Residual* const res) {
  res->coeff_type = coeff_type;
  res->prob  = enc->proba_.coeffs_[coeff_type];
  res->stats = enc->proba_.stats_[coeff_type];
  res->costs = enc->proba_.remapped_costs_[coeff_type];
  res->first = first;
}