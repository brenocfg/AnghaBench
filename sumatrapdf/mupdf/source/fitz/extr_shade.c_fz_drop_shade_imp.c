#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_storable ;
struct TYPE_5__ {TYPE_3__* fn_vals; } ;
struct TYPE_6__ {TYPE_1__ f; } ;
struct TYPE_7__ {scalar_t__ type; int /*<<< orphan*/  buffer; TYPE_2__ u; int /*<<< orphan*/  colorspace; } ;
typedef  TYPE_3__ fz_shade ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 scalar_t__ FZ_FUNCTION_BASED ; 
 int /*<<< orphan*/  fz_drop_colorspace (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_drop_compressed_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,TYPE_3__*) ; 

void
fz_drop_shade_imp(fz_context *ctx, fz_storable *shade_)
{
	fz_shade *shade = (fz_shade *)shade_;

	fz_drop_colorspace(ctx, shade->colorspace);
	if (shade->type == FZ_FUNCTION_BASED)
		fz_free(ctx, shade->u.f.fn_vals);
	fz_drop_compressed_buffer(ctx, shade->buffer);
	fz_free(ctx, shade);
}