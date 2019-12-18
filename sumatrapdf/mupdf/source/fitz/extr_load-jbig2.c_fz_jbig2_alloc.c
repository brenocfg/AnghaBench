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
struct fz_jbig2_alloc_s {int /*<<< orphan*/ * ctx; } ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  Jbig2Allocator ;

/* Variables and functions */
 void* fz_malloc_no_throw (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void *fz_jbig2_alloc(Jbig2Allocator *allocator, size_t size)
{
	fz_context *ctx = ((struct fz_jbig2_alloc_s *) allocator)->ctx;
	return fz_malloc_no_throw(ctx, size);
}