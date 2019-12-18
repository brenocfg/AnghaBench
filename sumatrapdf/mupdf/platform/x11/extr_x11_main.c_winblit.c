#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ invert; } ;
typedef  TYPE_1__ pdfapp_t ;
struct TYPE_10__ {int panx; int pany; int winh; int winw; int /*<<< orphan*/  selr; scalar_t__ iscopying; scalar_t__ image; int /*<<< orphan*/  ctx; } ;
struct TYPE_9__ {int /*<<< orphan*/  pixel; } ;

/* Variables and functions */
 int /*<<< orphan*/  BlackPixel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DefaultScreen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSetForeground (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fillrect (int,int,int,int) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 int fz_pixmap_components (int /*<<< orphan*/ ,scalar_t__) ; 
 int fz_pixmap_height (int /*<<< orphan*/ ,scalar_t__) ; 
 unsigned char* fz_pixmap_samples (int /*<<< orphan*/ ,scalar_t__) ; 
 int fz_pixmap_width (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_5__ gapp ; 
 int justcopied ; 
 unsigned char* malloc (int) ; 
 int /*<<< orphan*/  pdfapp_invert (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdfapp_inverthit (TYPE_5__*) ; 
 int /*<<< orphan*/  winblitstatusbar (TYPE_1__*) ; 
 TYPE_2__ xbgcolor ; 
 int /*<<< orphan*/  xdpy ; 
 int /*<<< orphan*/  xgc ; 
 int /*<<< orphan*/  ximage_blit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  xwin ; 

__attribute__((used)) static void winblit(pdfapp_t *app)
{
	if (gapp.image)
	{
		int image_w = fz_pixmap_width(gapp.ctx, gapp.image);
		int image_h = fz_pixmap_height(gapp.ctx, gapp.image);
		int image_n = fz_pixmap_components(gapp.ctx, gapp.image);
		unsigned char *image_samples = fz_pixmap_samples(gapp.ctx, gapp.image);
		int x0 = gapp.panx;
		int y0 = gapp.pany;
		int x1 = gapp.panx + image_w;
		int y1 = gapp.pany + image_h;

		if (app->invert)
			XSetForeground(xdpy, xgc, BlackPixel(xdpy, DefaultScreen(xdpy)));
		else
			XSetForeground(xdpy, xgc, xbgcolor.pixel);
		fillrect(0, 0, x0, gapp.winh);
		fillrect(x1, 0, gapp.winw - x1, gapp.winh);
		fillrect(0, 0, gapp.winw, y0);
		fillrect(0, y1, gapp.winw, gapp.winh - y1);

		if (gapp.iscopying || justcopied)
		{
			pdfapp_invert(&gapp, gapp.selr);
			justcopied = 1;
		}

		pdfapp_inverthit(&gapp);

		if (image_n == 4)
			ximage_blit(xwin, xgc,
				x0, y0,
				image_samples,
				0, 0,
				image_w,
				image_h,
				image_w * image_n);
		else if (image_n == 2)
		{
			int i = image_w*image_h;
			unsigned char *color = malloc(i*4);
			if (color)
			{
				unsigned char *s = image_samples;
				unsigned char *d = color;
				for (; i > 0 ; i--)
				{
					d[2] = d[1] = d[0] = *s++;
					d[3] = *s++;
					d += 4;
				}
				ximage_blit(xwin, xgc,
					x0, y0,
					color,
					0, 0,
					image_w,
					image_h,
					image_w * 4);
				free(color);
			}
		}

		pdfapp_inverthit(&gapp);

		if (gapp.iscopying || justcopied)
		{
			pdfapp_invert(&gapp, gapp.selr);
			justcopied = 1;
		}
	}
	else
	{
		XSetForeground(xdpy, xgc, xbgcolor.pixel);
		fillrect(0, 0, gapp.winw, gapp.winh);
	}

	winblitstatusbar(app);
}