#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VP8RDLevel ;
typedef  int /*<<< orphan*/  VP8ModeScore ;
struct TYPE_21__ {int /*<<< orphan*/  use_skip_proba_; } ;
struct TYPE_22__ {int /*<<< orphan*/  rd_opt_level_; TYPE_1__ proba_; } ;
typedef  TYPE_2__ VP8Encoder ;
struct TYPE_23__ {int /*<<< orphan*/  bw_; } ;
typedef  TYPE_3__ VP8EncIterator ;

/* Variables and functions */
 int /*<<< orphan*/  CodeResiduals (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int PostLoopFinalize (TYPE_3__*,int) ; 
 int PreLoopInitialize (TYPE_2__* const) ; 
 int /*<<< orphan*/  ResetAfterSkip (TYPE_3__*) ; 
 int /*<<< orphan*/  StatLoop (TYPE_2__* const) ; 
 int /*<<< orphan*/  StoreSideInfo (TYPE_3__*) ; 
 int /*<<< orphan*/  VP8Decimate (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  VP8InitFilter (TYPE_3__*) ; 
 int /*<<< orphan*/  VP8IteratorExport (TYPE_3__*) ; 
 int /*<<< orphan*/  VP8IteratorImport (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VP8IteratorInit (TYPE_2__* const,TYPE_3__*) ; 
 scalar_t__ VP8IteratorNext (TYPE_3__*) ; 
 int VP8IteratorProgress (TYPE_3__*,int) ; 
 int /*<<< orphan*/  VP8IteratorSaveBoundary (TYPE_3__*) ; 
 int /*<<< orphan*/  VP8StoreFilterStats (TYPE_3__*) ; 

int VP8EncLoop(VP8Encoder* const enc) {
  VP8EncIterator it;
  int ok = PreLoopInitialize(enc);
  if (!ok) return 0;

  StatLoop(enc);  // stats-collection loop

  VP8IteratorInit(enc, &it);
  VP8InitFilter(&it);
  do {
    VP8ModeScore info;
    const int dont_use_skip = !enc->proba_.use_skip_proba_;
    const VP8RDLevel rd_opt = enc->rd_opt_level_;

    VP8IteratorImport(&it, NULL);
    // Warning! order is important: first call VP8Decimate() and
    // *then* decide how to code the skip decision if there's one.
    if (!VP8Decimate(&it, &info, rd_opt) || dont_use_skip) {
      CodeResiduals(it.bw_, &it, &info);
    } else {   // reset predictors after a skip
      ResetAfterSkip(&it);
    }
    StoreSideInfo(&it);
    VP8StoreFilterStats(&it);
    VP8IteratorExport(&it);
    ok = VP8IteratorProgress(&it, 20);
    VP8IteratorSaveBoundary(&it);
  } while (ok && VP8IteratorNext(&it));

  return PostLoopFinalize(&it, ok);
}