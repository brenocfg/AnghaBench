#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  WebPWorker ;

/* Variables and functions */
 int /*<<< orphan*/  ChangeState (int /*<<< orphan*/ * const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Execute (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  WORK ; 

__attribute__((used)) static void Launch(WebPWorker* const worker) {
#ifdef WEBP_USE_THREAD
  ChangeState(worker, WORK);
#else
  Execute(worker);
#endif
}