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
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_3__ {int aborted; int /*<<< orphan*/  password_sem; int /*<<< orphan*/ * ctx; } ;
typedef  TYPE_1__ MuOfficeDoc ;

/* Variables and functions */
 int /*<<< orphan*/  mu_trigger_semaphore (int /*<<< orphan*/ *) ; 

void MuOfficeDoc_abortLoad(MuOfficeDoc *doc)
{
	fz_context *ctx;

	if (doc == NULL)
		return;

	ctx = doc->ctx;
	doc->aborted = 1;
	mu_trigger_semaphore(&doc->password_sem);
}