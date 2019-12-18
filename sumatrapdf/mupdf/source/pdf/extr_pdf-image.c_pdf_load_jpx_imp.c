#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdf_obj ;
typedef  int /*<<< orphan*/  pdf_document ;
typedef  int /*<<< orphan*/  fz_stream ;
typedef  int /*<<< orphan*/  fz_pixmap_image ;
struct TYPE_9__ {int n; } ;
typedef  TYPE_1__ fz_pixmap ;
typedef  int /*<<< orphan*/  fz_image ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 TYPE_1__* fz_alpha_from_gray (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* fz_convert_pixmap (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_default_color_params ; 
 int /*<<< orphan*/  fz_device_gray (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_drop_pixmap (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* fz_pixmap_image_tile (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_set_pixmap_image_tile (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * pdf_load_jpx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static fz_image *
pdf_load_jpx_imp(fz_context *ctx, pdf_document *doc, pdf_obj *rdb, pdf_obj *dict, fz_stream *cstm, int forcemask)
{
	fz_image *image = pdf_load_jpx(ctx, doc, dict, forcemask);

	if (forcemask)
	{
		fz_pixmap_image *cimg = (fz_pixmap_image *)image;
		fz_pixmap *mask_pixmap;
		fz_pixmap *tile = fz_pixmap_image_tile(ctx, cimg);

		if (tile->n != 1)
		{
			fz_pixmap *gray = fz_convert_pixmap(ctx, tile, fz_device_gray(ctx), NULL, NULL, fz_default_color_params, 0);
			fz_drop_pixmap(ctx, tile);
			tile = gray;
		}

		mask_pixmap = fz_alpha_from_gray(ctx, tile);
		fz_drop_pixmap(ctx, tile);
		fz_set_pixmap_image_tile(ctx, cimg, mask_pixmap);
	}

	return image;
}