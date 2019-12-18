#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  allocator; } ;
struct TYPE_6__ {struct TYPE_6__* entries; } ;
typedef  TYPE_1__ Jbig2HuffmanTable ;
typedef  TYPE_2__ Jbig2Ctx ;

/* Variables and functions */
 int /*<<< orphan*/  jbig2_free (int /*<<< orphan*/ ,TYPE_1__*) ; 

void
jbig2_release_huffman_table(Jbig2Ctx *ctx, Jbig2HuffmanTable *table)
{
    if (table != NULL) {
        jbig2_free(ctx->allocator, table->entries);
        jbig2_free(ctx->allocator, table);
    }
}