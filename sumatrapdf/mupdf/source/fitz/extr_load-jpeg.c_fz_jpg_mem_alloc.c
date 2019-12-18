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
typedef  int /*<<< orphan*/  j_common_ptr ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/ * JZ_CTX_FROM_CINFO (int /*<<< orphan*/ ) ; 
 void* fz_malloc_no_throw (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void *
fz_jpg_mem_alloc(j_common_ptr cinfo, size_t size)
{
	fz_context *ctx = JZ_CTX_FROM_CINFO(cinfo);
	return fz_malloc_no_throw(ctx, size);
}