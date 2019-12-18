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
 void* Memento_label (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_malloc_no_throw (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * get_hb_context () ; 

void *fz_hb_malloc(size_t size)
{
	fz_context *ctx = get_hb_context();

	assert(ctx != NULL);

	return Memento_label(fz_malloc_no_throw(ctx, size), "hb");
}