#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  w128_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_4__ {int initialized; scalar_t__ idx; } ;
typedef  TYPE_1__ sfmt_t ;

/* Variables and functions */
 scalar_t__ N32 ; 
 int N64 ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  gen_rand_array (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  swap (int /*<<< orphan*/ *,int) ; 

void fill_array64(sfmt_t *ctx, uint64_t *array, int size) {
    assert(ctx->initialized);
    assert(ctx->idx == N32);
    assert(size % 2 == 0);
    assert(size >= N64);

    gen_rand_array(ctx, (w128_t *)array, size / 2);
    ctx->idx = N32;

#if defined(BIG_ENDIAN64) && !defined(ONLY64)
    swap((w128_t *)array, size /2);
#endif
}