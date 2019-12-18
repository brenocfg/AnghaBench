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
struct TYPE_5__ {int /*<<< orphan*/  stats_; } ;
struct TYPE_4__ {TYPE_2__ proba_; } ;
typedef  TYPE_1__ VP8Encoder ;
typedef  TYPE_2__ VP8EncProba ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ResetTokenStats(VP8Encoder* const enc) {
  VP8EncProba* const proba = &enc->proba_;
  memset(proba->stats_, 0, sizeof(proba->stats_));
}