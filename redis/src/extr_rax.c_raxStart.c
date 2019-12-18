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
struct TYPE_3__ {int /*<<< orphan*/  stack; int /*<<< orphan*/ * node_cb; int /*<<< orphan*/ * data; int /*<<< orphan*/  key_max; int /*<<< orphan*/  key_static_string; int /*<<< orphan*/  key; scalar_t__ key_len; int /*<<< orphan*/ * rt; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ raxIterator ;
typedef  int /*<<< orphan*/  rax ;

/* Variables and functions */
 int /*<<< orphan*/  RAX_ITER_EOF ; 
 int /*<<< orphan*/  RAX_ITER_STATIC_LEN ; 
 int /*<<< orphan*/  raxStackInit (int /*<<< orphan*/ *) ; 

void raxStart(raxIterator *it, rax *rt) {
    it->flags = RAX_ITER_EOF; /* No crash if the iterator is not seeked. */
    it->rt = rt;
    it->key_len = 0;
    it->key = it->key_static_string;
    it->key_max = RAX_ITER_STATIC_LEN;
    it->data = NULL;
    it->node_cb = NULL;
    raxStackInit(&it->stack);
}