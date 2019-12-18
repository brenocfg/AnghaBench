#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int white ;
struct TYPE_3__ {unsigned char* samples; int n; int h; int w; int /*<<< orphan*/  stride; int /*<<< orphan*/  colorspace; } ;
typedef  TYPE_1__ fz_pixmap ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int black ;

/* Variables and functions */
#define  FZ_COLORSPACE_BGR 130 
#define  FZ_COLORSPACE_GRAY 129 
#define  FZ_COLORSPACE_RGB 128 
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int fz_colorspace_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_mul255 (unsigned char,int) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

void
fz_tint_pixmap(fz_context *ctx, fz_pixmap *pix, int black, int white)
{
	unsigned char *s = pix->samples;
	int n = pix->n;
	int x, y, save;
	int rb = (black>>16)&255;
	int gb = (black>>8)&255;
	int bb = (black)&255;
	int rw = (white>>16)&255;
	int gw = (white>>8)&255;
	int bw = (white)&255;
	int rm = (rw - rb);
	int gm = (gw - gb);
	int bm = (bw - bb);

	switch (fz_colorspace_type(ctx, pix->colorspace))
	{
	case FZ_COLORSPACE_GRAY:
		gw = (rw + gw + bw) / 3;
		gb = (rb + gb + bb) / 3;
		gm = gw - gb;
		for (y = 0; y < pix->h; y++)
		{
			for (x = 0; x < pix->w; x++)
			{
				*s = gb + fz_mul255(*s, gm);
				s += n;
			}
			s += pix->stride - pix->w * n;
		}
		break;

	case FZ_COLORSPACE_BGR:
		save = rm; rm = bm; bm = save;
		save = rb; rb = bb; bb = save;
		/* fall through */
	case FZ_COLORSPACE_RGB:
		for (y = 0; y < pix->h; y++)
		{
			for (x = 0; x < pix->w; x++)
			{
				s[0] = rb + fz_mul255(s[0], rm);
				s[1] = gb + fz_mul255(s[1], gm);
				s[2] = bb + fz_mul255(s[2], bm);
				s += n;
			}
			s += pix->stride - pix->w * n;
		}
		break;

	default:
		fz_throw(ctx, FZ_ERROR_GENERIC, "can only tint RGB, BGR and Gray pixmaps");
		break;
	}
}