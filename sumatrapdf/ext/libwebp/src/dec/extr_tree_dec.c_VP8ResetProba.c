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
struct TYPE_3__ {int /*<<< orphan*/  segments_; } ;
typedef  TYPE_1__ VP8Proba ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,unsigned int,int) ; 

void VP8ResetProba(VP8Proba* const proba) {
  memset(proba->segments_, 255u, sizeof(proba->segments_));
  // proba->bands_[][] is initialized later
}