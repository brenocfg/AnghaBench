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
 size_t SIZE_MAX ; 
 void* do_scavenging_malloc (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,size_t,size_t) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 

void *
fz_calloc(fz_context *ctx, size_t count, size_t size)
{
	void *p;
	if (count == 0 || size == 0)
		return NULL;
	if (count > SIZE_MAX / size)
		fz_throw(ctx, FZ_ERROR_MEMORY, "calloc (%zu x %zu bytes) failed (size_t overflow)", count, size);
	p = do_scavenging_malloc(ctx, count * size);
	if (!p)
		fz_throw(ctx, FZ_ERROR_MEMORY, "calloc (%zu x %zu bytes) failed", count, size);
	memset(p, 0, count*size);
	return p;
}