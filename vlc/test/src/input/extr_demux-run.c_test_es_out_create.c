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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_3__ {int /*<<< orphan*/ * cbs; } ;
struct test_es_out_t {int /*<<< orphan*/ * parent; TYPE_1__ out; int /*<<< orphan*/ * ids; } ;
typedef  TYPE_1__ es_out_t ;

/* Variables and functions */
 int /*<<< orphan*/  es_out_cbs ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 struct test_es_out_t* malloc (int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static es_out_t *test_es_out_create(vlc_object_t *parent)
{
    struct test_es_out_t *ctx = malloc(sizeof (*ctx));
    if (ctx == NULL)
    {
        fprintf(stderr, "Error: cannot create ES output.\n");
        return NULL;
    }

    ctx->ids = NULL;

    es_out_t *out = &ctx->out;
    out->cbs = &es_out_cbs;
#ifdef HAVE_DECODERS
    ctx->parent = parent;
#else
    (void) parent;
#endif
    return out;
}