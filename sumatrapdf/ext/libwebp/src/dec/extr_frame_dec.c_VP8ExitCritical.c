#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  (* teardown ) (TYPE_1__* const) ;} ;
typedef  TYPE_1__ VP8Io ;
struct TYPE_8__ {scalar_t__ mt_method_; int /*<<< orphan*/  worker_; } ;
typedef  TYPE_2__ VP8Decoder ;
struct TYPE_9__ {int (* Sync ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 TYPE_4__* WebPGetWorkerInterface () ; 
 int stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__* const) ; 

int VP8ExitCritical(VP8Decoder* const dec, VP8Io* const io) {
  int ok = 1;
  if (dec->mt_method_ > 0) {
    ok = WebPGetWorkerInterface()->Sync(&dec->worker_);
  }

  if (io->teardown != NULL) {
    io->teardown(io);
  }
  return ok;
}