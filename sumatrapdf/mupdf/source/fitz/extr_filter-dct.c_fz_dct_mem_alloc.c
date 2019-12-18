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
typedef  int /*<<< orphan*/  j_common_ptr ;
struct TYPE_3__ {int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ fz_dctd ;

/* Variables and functions */
 TYPE_1__* JZ_DCT_STATE_FROM_CINFO (int /*<<< orphan*/ ) ; 
 void* fz_malloc_no_throw (int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void *
fz_dct_mem_alloc(j_common_ptr cinfo, size_t size)
{
	fz_dctd *state = JZ_DCT_STATE_FROM_CINFO(cinfo);
	return fz_malloc_no_throw(state->ctx, size);
}