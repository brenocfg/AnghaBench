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
struct TYPE_3__ {struct TYPE_3__* next; } ;
typedef  TYPE_1__ es_out_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 

__attribute__((used)) static void EsOutCheckId(struct test_es_out_t *ctx, es_out_id_t *id)
{
    for (es_out_id_t *ids = ctx->ids; ids != NULL; ids = ids->next)
        if (ids == id)
            return;

    abort();
}