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
struct pool {scalar_t__ current_used; int /*<<< orphan*/ * current; int /*<<< orphan*/ * header; } ;

/* Variables and functions */

__attribute__((used)) static void
pool_init(struct pool *p) {
	p->header = NULL;
	p->current = NULL;
	p->current_used = 0;
}