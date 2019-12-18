#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ score; int /*<<< orphan*/  nz; scalar_t__ H; scalar_t__ R; scalar_t__ SD; scalar_t__ D; } ;
typedef  TYPE_1__ VP8ModeScore ;

/* Variables and functions */

__attribute__((used)) static void AddScore(VP8ModeScore* const dst, const VP8ModeScore* const src) {
  dst->D  += src->D;
  dst->SD += src->SD;
  dst->R  += src->R;
  dst->H  += src->H;
  dst->nz |= src->nz;     // here, new nz bits are accumulated.
  dst->score += src->score;
}