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
struct TYPE_5__ {int xdivs; int ydivs; } ;
struct TYPE_6__ {TYPE_1__ f; } ;
struct TYPE_7__ {scalar_t__ type; int /*<<< orphan*/  buffer; int /*<<< orphan*/  colorspace; TYPE_2__ u; } ;
typedef  TYPE_3__ fz_shade ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 scalar_t__ FZ_FUNCTION_BASED ; 
 int fz_colorspace_n (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t fz_compressed_buffer_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t
fz_shade_size(fz_context *ctx, fz_shade *s)
{
	if (s == NULL)
		return 0;
	if (s->type == FZ_FUNCTION_BASED)
		return sizeof(*s) + sizeof(float) * s->u.f.xdivs * s->u.f.ydivs * fz_colorspace_n(ctx, s->colorspace);
	return sizeof(*s) + fz_compressed_buffer_size(s->buffer);
}