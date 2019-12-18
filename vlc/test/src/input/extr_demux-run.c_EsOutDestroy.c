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
struct test_es_out_t {TYPE_1__* ids; } ;
typedef  int /*<<< orphan*/  es_out_t ;
struct TYPE_3__ {struct TYPE_3__* next; } ;
typedef  TYPE_1__ es_out_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  IdDelete (TYPE_1__*) ; 
 int /*<<< orphan*/  free (struct test_es_out_t*) ; 

__attribute__((used)) static void EsOutDestroy(es_out_t *out)
{
    struct test_es_out_t *ctx = (struct test_es_out_t *)out;
    es_out_id_t *id;

    while ((id = ctx->ids) != NULL)
    {
        ctx->ids = id->next;
        IdDelete(id);
    }
    free(ctx);
}