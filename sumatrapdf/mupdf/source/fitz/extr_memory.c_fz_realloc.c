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
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_MEMORY ; 
 void* do_scavenging_realloc (int /*<<< orphan*/ *,void*,size_t) ; 
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,size_t) ; 

void *
fz_realloc(fz_context *ctx, void *p, size_t size)
{
	if (size == 0)
	{
		fz_free(ctx, p);
		return NULL;
	}
	p = do_scavenging_realloc(ctx, p, size);
	if (!p)
		fz_throw(ctx, FZ_ERROR_MEMORY, "realloc (%zu bytes) failed", size);
	return p;
}