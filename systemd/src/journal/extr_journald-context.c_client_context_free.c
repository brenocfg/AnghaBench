#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  lru_index; scalar_t__ in_lru; int /*<<< orphan*/  pid; } ;
struct TYPE_13__ {int /*<<< orphan*/  client_contexts_lru; int /*<<< orphan*/  client_contexts; } ;
typedef  TYPE_1__ Server ;
typedef  TYPE_2__ ClientContext ;

/* Variables and functions */
 int /*<<< orphan*/  PID_TO_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  client_context_reset (TYPE_1__*,TYPE_2__*) ; 
 TYPE_2__* hashmap_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* mfree (TYPE_2__*) ; 
 scalar_t__ prioq_remove (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ClientContext* client_context_free(Server *s, ClientContext *c) {
        assert(s);

        if (!c)
                return NULL;

        assert_se(hashmap_remove(s->client_contexts, PID_TO_PTR(c->pid)) == c);

        if (c->in_lru)
                assert_se(prioq_remove(s->client_contexts_lru, c, &c->lru_index) >= 0);

        client_context_reset(s, c);

        return mfree(c);
}