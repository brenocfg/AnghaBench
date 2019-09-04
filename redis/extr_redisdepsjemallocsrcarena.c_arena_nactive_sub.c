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
struct TYPE_3__ {int /*<<< orphan*/  nactive; } ;
typedef  TYPE_1__ arena_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC_RELAXED ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  atomic_fetch_sub_zu (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 size_t atomic_load_zu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
arena_nactive_sub(arena_t *arena, size_t sub_pages) {
	assert(atomic_load_zu(&arena->nactive, ATOMIC_RELAXED) >= sub_pages);
	atomic_fetch_sub_zu(&arena->nactive, sub_pages, ATOMIC_RELAXED);
}