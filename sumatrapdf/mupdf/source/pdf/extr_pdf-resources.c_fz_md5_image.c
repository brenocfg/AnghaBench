#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned char* samples; int h; int w; int n; int /*<<< orphan*/  stride; } ;
typedef  TYPE_1__ fz_pixmap ;
typedef  int /*<<< orphan*/  fz_md5 ;
typedef  int /*<<< orphan*/  fz_image ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_drop_pixmap (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* fz_get_pixmap_from_image (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_md5_final (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  fz_md5_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_md5_update (int /*<<< orphan*/ *,unsigned char*,int) ; 

__attribute__((used)) static void
fz_md5_image(fz_context *ctx, fz_image *image, unsigned char digest[16])
{
	fz_pixmap *pixmap;
	fz_md5 state;
	int h;
	unsigned char *d;

	pixmap = fz_get_pixmap_from_image(ctx, image, NULL, NULL, 0, 0);
	fz_md5_init(&state);
	d = pixmap->samples;
	h = pixmap->h;
	while (h--)
	{
		fz_md5_update(&state, d, pixmap->w * pixmap->n);
		d += pixmap->stride;
	}
	fz_md5_final(&state, digest);
	fz_drop_pixmap(ctx, pixmap);
}