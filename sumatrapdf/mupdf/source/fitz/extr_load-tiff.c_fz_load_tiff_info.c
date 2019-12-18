#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_colorspace ;

/* Variables and functions */
 int /*<<< orphan*/  fz_load_tiff_info_subimage (int /*<<< orphan*/ *,unsigned char const*,size_t,int*,int*,int*,int*,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

void
fz_load_tiff_info(fz_context *ctx, const unsigned char *buf, size_t len, int *wp, int *hp, int *xresp, int *yresp, fz_colorspace **cspacep)
{
	fz_load_tiff_info_subimage(ctx, buf, len, wp, hp, xresp, yresp, cspacep, 0);
}