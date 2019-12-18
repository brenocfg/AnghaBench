#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {float a; float b; float c; float d; } ;
typedef  TYPE_2__ fz_matrix ;
struct TYPE_18__ {float x0; float y0; float x1; float y1; } ;
typedef  TYPE_3__ fz_irect ;
struct TYPE_19__ {int refs; int l2factor; TYPE_3__ rect; TYPE_5__* image; } ;
typedef  TYPE_4__ fz_image_key ;
struct TYPE_20__ {float w; float h; } ;
typedef  TYPE_5__ fz_image ;
struct TYPE_21__ {TYPE_1__* tuning; } ;
typedef  TYPE_6__ fz_context ;
struct TYPE_16__ {int /*<<< orphan*/  image_decode_arg; int /*<<< orphan*/  (* image_decode ) (int /*<<< orphan*/ ,float,float,int,TYPE_3__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  fz_adjust_image_subarea (TYPE_6__*,TYPE_5__*,TYPE_3__*,int) ; 
 int sqrtf (float) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,float,float,int,TYPE_3__*) ; 

__attribute__((used)) static void fz_compute_image_key(fz_context *ctx, fz_image *image, fz_matrix *ctm,
	fz_image_key *key, const fz_irect *subarea, int l2factor, int *w, int *h, int *dw, int *dh)
{
	key->refs = 1;
	key->image = image;
	key->l2factor = l2factor;

	if (subarea == NULL)
	{
		key->rect.x0 = 0;
		key->rect.y0 = 0;
		key->rect.x1 = image->w;
		key->rect.y1 = image->h;
	}
	else
	{
		key->rect = *subarea;
		ctx->tuning->image_decode(ctx->tuning->image_decode_arg, image->w, image->h, key->l2factor, &key->rect);
		fz_adjust_image_subarea(ctx, image, &key->rect, key->l2factor);
	}

	/* Based on that subarea, recalculate the extents */
	if (ctm)
	{
		float frac_w = (float) (key->rect.x1 - key->rect.x0) / image->w;
		float frac_h = (float) (key->rect.y1 - key->rect.y0) / image->h;
		float a = ctm->a * frac_w;
		float b = ctm->b * frac_h;
		float c = ctm->c * frac_w;
		float d = ctm->d * frac_h;
		*w = sqrtf(a * a + b * b);
		*h = sqrtf(c * c + d * d);
	}
	else
	{
		*w = image->w;
		*h = image->h;
	}

	/* Return the true sizes to the caller */
	if (dw)
		*dw = *w;
	if (dh)
		*dh = *h;
	if (*w > image->w)
		*w = image->w;
	if (*h > image->h)
		*h = image->h;

	if (*w == 0 || *h == 0)
		key->l2factor = 0;
}