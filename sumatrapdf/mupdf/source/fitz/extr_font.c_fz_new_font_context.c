#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_4__* font; } ;
typedef  TYPE_2__ fz_context ;
struct TYPE_6__ {int /*<<< orphan*/  realloc; int /*<<< orphan*/  free; int /*<<< orphan*/  alloc; TYPE_2__* user; } ;
struct TYPE_8__ {int ctx_refs; TYPE_1__ ftmemory; int /*<<< orphan*/ * load_font; scalar_t__ ftlib_refs; int /*<<< orphan*/ * ftlib; } ;

/* Variables and functions */
 int /*<<< orphan*/  ft_alloc ; 
 int /*<<< orphan*/  ft_free ; 
 int /*<<< orphan*/  ft_realloc ; 
 int /*<<< orphan*/  fz_font_context ; 
 TYPE_4__* fz_malloc_struct (TYPE_2__*,int /*<<< orphan*/ ) ; 

void fz_new_font_context(fz_context *ctx)
{
	ctx->font = fz_malloc_struct(ctx, fz_font_context);
	ctx->font->ctx_refs = 1;
	ctx->font->ftlib = NULL;
	ctx->font->ftlib_refs = 0;
	ctx->font->load_font = NULL;
	ctx->font->ftmemory.user = ctx;
	ctx->font->ftmemory.alloc = ft_alloc;
	ctx->font->ftmemory.free = ft_free;
	ctx->font->ftmemory.realloc = ft_realloc;
}