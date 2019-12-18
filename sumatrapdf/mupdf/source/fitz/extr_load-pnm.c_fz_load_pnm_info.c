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
struct info {int width; int height; int /*<<< orphan*/  cs; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_colorspace ;

/* Variables and functions */
 int /*<<< orphan*/ * fz_keep_colorspace (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnm_read_image (int /*<<< orphan*/ *,struct info*,unsigned char const*,size_t,int,int /*<<< orphan*/ ) ; 

void
fz_load_pnm_info(fz_context *ctx, const unsigned char *p, size_t total, int *wp, int *hp, int *xresp, int *yresp, fz_colorspace **cspacep)
{
	struct info pnm = { 0 };
	(void) pnm_read_image(ctx, &pnm, p, total, 1, 0);
	*cspacep = fz_keep_colorspace(ctx, pnm.cs); /* pnm.cs is a borrowed device colorspace */
	*wp = pnm.width;
	*hp = pnm.height;
	*xresp = 72;
	*yresp = 72;
}