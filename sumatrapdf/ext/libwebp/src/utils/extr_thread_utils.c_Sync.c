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
struct TYPE_4__ {scalar_t__ status_; int /*<<< orphan*/  had_error; } ;
typedef  TYPE_1__ WebPWorker ;

/* Variables and functions */
 int /*<<< orphan*/  ChangeState (TYPE_1__* const,scalar_t__) ; 
 scalar_t__ OK ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int Sync(WebPWorker* const worker) {
#ifdef WEBP_USE_THREAD
  ChangeState(worker, OK);
#endif
  assert(worker->status_ <= OK);
  return !worker->had_error;
}