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
struct block {int /*<<< orphan*/ * next; } ;

/* Variables and functions */
 struct block* skynet_malloc (int) ; 

__attribute__((used)) inline static struct block *
blk_alloc(void) {
	struct block *b = skynet_malloc(sizeof(struct block));
	b->next = NULL;
	return b;
}