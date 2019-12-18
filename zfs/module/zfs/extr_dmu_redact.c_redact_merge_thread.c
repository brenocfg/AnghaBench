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
struct redact_record {int /*<<< orphan*/  eos_marker; } ;
struct redact_merge_thread_arg {int /*<<< orphan*/  q; int /*<<< orphan*/  cancel; int /*<<< orphan*/  thr_args; int /*<<< orphan*/  numsnaps; int /*<<< orphan*/  error_code; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  bqueue_enqueue_flush (int /*<<< orphan*/ *,struct redact_record*,int) ; 
 struct redact_record* kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perform_thread_merge (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_exit () ; 

__attribute__((used)) static void
redact_merge_thread(void *arg)
{
	struct redact_merge_thread_arg *rmta = arg;
	rmta->error_code = perform_thread_merge(&rmta->q,
	    rmta->numsnaps, rmta->thr_args, &rmta->cancel);
	struct redact_record *rec = kmem_zalloc(sizeof (*rec), KM_SLEEP);
	rec->eos_marker = B_TRUE;
	bqueue_enqueue_flush(&rmta->q, rec, 1);
	thread_exit();
}