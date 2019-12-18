#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int dims; scalar_t__ psobjs; TYPE_4__* psobj; scalar_t__ forms; TYPE_4__* form; scalar_t__ patterns; TYPE_4__* pattern; scalar_t__ shadings; TYPE_4__* shading; scalar_t__ images; TYPE_4__* image; scalar_t__ fonts; TYPE_4__* font; TYPE_4__* dim; } ;
typedef  TYPE_3__ globals ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_6__ {TYPE_4__* bbox; } ;
struct TYPE_7__ {TYPE_1__ dim; } ;
struct TYPE_9__ {TYPE_2__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,TYPE_4__*) ; 

__attribute__((used)) static void clearinfo(fz_context *ctx, globals *glo)
{
	int i;

	if (glo->dim)
	{
		for (i = 0; i < glo->dims; i++)
			fz_free(ctx, glo->dim[i].u.dim.bbox);
		fz_free(ctx, glo->dim);
		glo->dim = NULL;
		glo->dims = 0;
	}

	if (glo->font)
	{
		fz_free(ctx, glo->font);
		glo->font = NULL;
		glo->fonts = 0;
	}

	if (glo->image)
	{
		fz_free(ctx, glo->image);
		glo->image = NULL;
		glo->images = 0;
	}

	if (glo->shading)
	{
		fz_free(ctx, glo->shading);
		glo->shading = NULL;
		glo->shadings = 0;
	}

	if (glo->pattern)
	{
		fz_free(ctx, glo->pattern);
		glo->pattern = NULL;
		glo->patterns = 0;
	}

	if (glo->form)
	{
		fz_free(ctx, glo->form);
		glo->form = NULL;
		glo->forms = 0;
	}

	if (glo->psobj)
	{
		fz_free(ctx, glo->psobj);
		glo->psobj = NULL;
		glo->psobjs = 0;
	}
}