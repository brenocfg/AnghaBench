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
struct TYPE_3__ {int /*<<< orphan*/ * offsets; int /*<<< orphan*/ * freqs; int /*<<< orphan*/ * segmentFreqs; } ;
typedef  TYPE_1__ FASTCOVER_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void FASTCOVER_ctx_destroy(FASTCOVER_ctx_t *ctx) {
  if (!ctx) {
    return;
  }
  if (ctx->segmentFreqs) {
    free(ctx->segmentFreqs);
    ctx->segmentFreqs = NULL;
  }
  if (ctx->freqs) {
    free(ctx->freqs);
    ctx->freqs = NULL;
  }
  if (ctx->offsets) {
    free(ctx->offsets);
    ctx->offsets = NULL;
  }
}