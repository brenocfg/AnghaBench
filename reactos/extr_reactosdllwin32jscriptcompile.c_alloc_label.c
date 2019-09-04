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
struct TYPE_3__ {int labels_size; unsigned int* labels; int labels_cnt; } ;
typedef  TYPE_1__ compiler_ctx_t ;

/* Variables and functions */
 int LABEL_FLAG ; 
 unsigned int* heap_alloc (int) ; 
 unsigned int* heap_realloc (unsigned int*,int) ; 

__attribute__((used)) static unsigned alloc_label(compiler_ctx_t *ctx)
{
    if(!ctx->labels_size) {
        ctx->labels = heap_alloc(8 * sizeof(*ctx->labels));
        if(!ctx->labels)
            return 0;
        ctx->labels_size = 8;
    }else if(ctx->labels_size == ctx->labels_cnt) {
        unsigned *new_labels;

        new_labels = heap_realloc(ctx->labels, 2*ctx->labels_size*sizeof(*ctx->labels));
        if(!new_labels)
            return 0;

        ctx->labels = new_labels;
        ctx->labels_size *= 2;
    }

    return ctx->labels_cnt++ | LABEL_FLAG;
}