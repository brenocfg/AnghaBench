#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int entropy; int /*<<< orphan*/  nonzero_code; scalar_t__ max_val; scalar_t__ nonzeros; scalar_t__ sum; } ;
typedef  TYPE_1__ VP8LBitEntropy ;

/* Variables and functions */
 int /*<<< orphan*/  VP8L_NON_TRIVIAL_SYM ; 

void VP8LBitEntropyInit(VP8LBitEntropy* const entropy) {
  entropy->entropy = 0.;
  entropy->sum = 0;
  entropy->nonzeros = 0;
  entropy->max_val = 0;
  entropy->nonzero_code = VP8L_NON_TRIVIAL_SYM;
}