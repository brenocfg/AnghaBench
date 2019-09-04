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
struct write_block {scalar_t__ len; scalar_t__ ptr; int /*<<< orphan*/ * current; struct block* head; } ;
struct block {struct block* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  skynet_free (struct block*) ; 

__attribute__((used)) static void
wb_free(struct write_block *wb) {
	struct block *blk = wb->head;
	blk = blk->next;	// the first block is on stack
	while (blk) {
		struct block * next = blk->next;
		skynet_free(blk);
		blk = next;
	}
	wb->head = NULL;
	wb->current = NULL;
	wb->ptr = 0;
	wb->len = 0;
}