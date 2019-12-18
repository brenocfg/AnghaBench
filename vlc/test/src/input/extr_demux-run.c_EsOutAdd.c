#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct test_es_out_t {int /*<<< orphan*/  parent; TYPE_1__* ids; } ;
typedef  int /*<<< orphan*/  es_out_t ;
struct TYPE_7__ {int /*<<< orphan*/  fmt; int /*<<< orphan*/ * decoder; struct TYPE_7__* next; } ;
typedef  TYPE_1__ es_out_id_t ;
struct TYPE_8__ {scalar_t__ i_group; } ;
typedef  TYPE_2__ es_format_t ;

/* Variables and functions */
 int /*<<< orphan*/  debug (char*,void*) ; 
 int /*<<< orphan*/  es_format_Clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  es_format_Copy (int /*<<< orphan*/ *,TYPE_2__ const*) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/ * test_decoder_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static es_out_id_t *EsOutAdd(es_out_t *out, const es_format_t *fmt)
{
    struct test_es_out_t *ctx = (struct test_es_out_t *) out;

    if (fmt->i_group < 0)
        return NULL;

    es_out_id_t *id = malloc(sizeof (*id));
    if (unlikely(id == NULL))
        return NULL;

    id->next = ctx->ids;
    ctx->ids = id;
#ifdef HAVE_DECODERS
    es_format_Copy(&id->fmt, fmt);
    id->decoder = test_decoder_create(ctx->parent, &id->fmt);
    if (id->decoder == NULL)
        es_format_Clean(&id->fmt);
#endif

    debug("[%p] Added   ES\n", (void *)id);
    return id;
}