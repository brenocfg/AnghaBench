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
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_2__ {int started; int solo; int /*<<< orphan*/  start; int /*<<< orphan*/  active; } ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int RENDER_FATAL ; 
 int RENDER_OK ; 
 TYPE_1__ bgprint ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mu_trigger_semaphore (int /*<<< orphan*/ *) ; 
 int wait_for_bgprint_to_finish () ; 

__attribute__((used)) static void
finish_bgprint(fz_context *ctx)
{
	int status;

	if (!bgprint.active)
		return;

	/* If we are using it, then wait for it to finish. */
	status = wait_for_bgprint_to_finish();
	if (status == RENDER_OK)
	{
		/* The background bgprint completed successfully. */
		return;
	}

	if (status == RENDER_FATAL)
	{
		/* We failed because of not being able to output. No point in retrying. */
		fz_throw(ctx, FZ_ERROR_GENERIC, "Failed to render page");
	}
	bgprint.started = 1;
	bgprint.solo = 1;
	mu_trigger_semaphore(&bgprint.start);
	status = wait_for_bgprint_to_finish();
	if (status != 0)
	{
		/* Hard failure */
		fz_throw(ctx, FZ_ERROR_GENERIC, "Failed to render page");
	}
}