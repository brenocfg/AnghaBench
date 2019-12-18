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
struct TYPE_3__ {scalar_t__ sse_count_; scalar_t__* sse_; } ;
typedef  TYPE_1__ VP8Encoder ;

/* Variables and functions */

__attribute__((used)) static void ResetSSE(VP8Encoder* const enc) {
  enc->sse_[0] = 0;
  enc->sse_[1] = 0;
  enc->sse_[2] = 0;
  // Note: enc->sse_[3] is managed by alpha.c
  enc->sse_count_ = 0;
}