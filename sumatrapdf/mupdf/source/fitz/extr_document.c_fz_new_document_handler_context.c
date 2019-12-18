#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_3__* handler; } ;
typedef  TYPE_1__ fz_context ;
struct TYPE_6__ {int refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  fz_document_handler_context ; 
 TYPE_3__* fz_malloc_struct (TYPE_1__*,int /*<<< orphan*/ ) ; 

void fz_new_document_handler_context(fz_context *ctx)
{
	ctx->handler = fz_malloc_struct(ctx, fz_document_handler_context);
	ctx->handler->refs = 1;
}