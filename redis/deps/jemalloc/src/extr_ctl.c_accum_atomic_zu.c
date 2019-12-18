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
typedef  int /*<<< orphan*/  atomic_zu_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC_RELAXED ; 
 size_t atomic_load_zu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_store_zu (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
accum_atomic_zu(atomic_zu_t *dst, atomic_zu_t *src) {
	size_t cur_dst = atomic_load_zu(dst, ATOMIC_RELAXED);
	size_t cur_src = atomic_load_zu(src, ATOMIC_RELAXED);
	atomic_store_zu(dst, cur_dst + cur_src, ATOMIC_RELAXED);
}