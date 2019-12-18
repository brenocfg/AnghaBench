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
struct test_es_out_t {TYPE_1__* ids; } ;
typedef  int /*<<< orphan*/  es_out_t ;
struct TYPE_4__ {struct TYPE_4__* next; } ;
typedef  TYPE_1__ es_out_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  IdDelete (TYPE_1__*) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  debug (char*,void*) ; 

__attribute__((used)) static void EsOutDelete(es_out_t *out, es_out_id_t *id)
{
    struct test_es_out_t *ctx = (struct test_es_out_t *) out;
    es_out_id_t **pp = &ctx->ids;

    while (*pp != id)
    {
        if (*pp == NULL)
            abort();
        pp = &((*pp)->next);
    }

    debug("[%p] Deleted ES\n", (void *)id);
    *pp = id->next;
    IdDelete(id);
}