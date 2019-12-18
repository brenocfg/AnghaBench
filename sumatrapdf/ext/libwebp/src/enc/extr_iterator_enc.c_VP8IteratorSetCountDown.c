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
struct TYPE_3__ {int count_down_; int count_down0_; } ;
typedef  TYPE_1__ VP8EncIterator ;

/* Variables and functions */

void VP8IteratorSetCountDown(VP8EncIterator* const it, int count_down) {
  it->count_down_ = it->count_down0_ = count_down;
}