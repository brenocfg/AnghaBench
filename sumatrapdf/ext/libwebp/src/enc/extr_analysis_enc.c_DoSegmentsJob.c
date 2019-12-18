#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  VP8EncIterator ;
struct TYPE_2__ {int /*<<< orphan*/  delta_progress; int /*<<< orphan*/  uv_alpha; int /*<<< orphan*/  alpha; int /*<<< orphan*/  alphas; } ;
typedef  TYPE_1__ SegmentJob ;

/* Variables and functions */
 int /*<<< orphan*/  MBAnalyze (int /*<<< orphan*/ * const,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VP8IteratorImport (int /*<<< orphan*/ * const,int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  VP8IteratorIsDone (int /*<<< orphan*/ * const) ; 
 scalar_t__ VP8IteratorNext (int /*<<< orphan*/ * const) ; 
 int VP8IteratorProgress (int /*<<< orphan*/ * const,int /*<<< orphan*/ ) ; 
 scalar_t__ WEBP_ALIGN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WEBP_ALIGN_CST ; 

__attribute__((used)) static int DoSegmentsJob(void* arg1, void* arg2) {
  SegmentJob* const job = (SegmentJob*)arg1;
  VP8EncIterator* const it = (VP8EncIterator*)arg2;
  int ok = 1;
  if (!VP8IteratorIsDone(it)) {
    uint8_t tmp[32 + WEBP_ALIGN_CST];
    uint8_t* const scratch = (uint8_t*)WEBP_ALIGN(tmp);
    do {
      // Let's pretend we have perfect lossless reconstruction.
      VP8IteratorImport(it, scratch);
      MBAnalyze(it, job->alphas, &job->alpha, &job->uv_alpha);
      ok = VP8IteratorProgress(it, job->delta_progress);
    } while (ok && VP8IteratorNext(it));
  }
  return ok;
}