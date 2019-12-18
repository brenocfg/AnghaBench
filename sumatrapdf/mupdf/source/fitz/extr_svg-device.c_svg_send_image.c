#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int num_images; int max_images; TYPE_7__* images; int /*<<< orphan*/  id; scalar_t__ reuse_images; int /*<<< orphan*/ * out; } ;
typedef  TYPE_1__ svg_device ;
typedef  int /*<<< orphan*/  fz_output ;
struct TYPE_13__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
typedef  TYPE_2__ fz_image ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_color_params ;
struct TYPE_14__ {int id; TYPE_2__* image; } ;

/* Variables and functions */
 int /*<<< orphan*/ * end_def (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_2__* fz_keep_image (int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_7__* fz_realloc_array (int /*<<< orphan*/ *,TYPE_7__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_write_image_as_data_uri (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  fz_write_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  image ; 
 int /*<<< orphan*/ * start_def (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void
svg_send_image(fz_context *ctx, svg_device *sdev, fz_image *img, fz_color_params color_params)
{
	fz_output *out = sdev->out;
	int i;
	int id;

	if (sdev->reuse_images)
	{
		for (i = sdev->num_images-1; i >= 0; i--)
			if (img == sdev->images[i].image)
				break;
		if (i >= 0)
		{
			fz_write_printf(ctx, out, "<use xlink:href=\"#im%d\" x=\"0\" y=\"0\" width=\"%d\" height=\"%d\"/>\n",
					sdev->images[i].id, img->w, img->h);
			return;
		}

		/* We need to send this image for the first time */
		if (sdev->num_images == sdev->max_images)
		{
			int new_max = sdev->max_images * 2;
			if (new_max == 0)
				new_max = 32;
			sdev->images = fz_realloc_array(ctx, sdev->images, new_max, image);
			sdev->max_images = new_max;
		}

		id = sdev->id++;
		out = start_def(ctx, sdev);
		fz_write_printf(ctx, out, "<symbol id=\"im%d\" viewBox=\"0 0 %d %d\">\n", id, img->w, img->h);

		fz_write_printf(ctx, out, "<image width=\"%d\" height=\"%d\" xlink:href=\"", img->w, img->h);
		fz_write_image_as_data_uri(ctx, out, img);
		fz_write_printf(ctx, out, "\"/>\n");

		fz_write_printf(ctx, out, "</symbol>\n");
		out = end_def(ctx, sdev);

		sdev->images[sdev->num_images].id = id;
		sdev->images[sdev->num_images].image = fz_keep_image(ctx, img);
		sdev->num_images++;

		fz_write_printf(ctx, out, "<use xlink:href=\"#im%d\" x=\"0\" y=\"0\" width=\"%d\" height=\"%d\"/>\n",
				id, img->w, img->h);
	}
	else
	{
		fz_write_printf(ctx, out, "<image width=\"%d\" height=\"%d\" xlink:href=\"", img->w, img->h);
		fz_write_image_as_data_uri(ctx, out, img);
		fz_write_printf(ctx, out, "\"/>\n");
	}
}