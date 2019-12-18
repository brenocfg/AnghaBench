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
 void* fz_malloc (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 

__attribute__((used)) static void *
clone_block(fz_context *ctx, void *block, size_t len)
{
	void *target;

	if (len == 0 || block == NULL)
		return NULL;

	target = fz_malloc(ctx, len);
	memcpy(target, block, len);
	return target;
}