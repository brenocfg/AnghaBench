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
struct info {int /*<<< orphan*/  subimages; void* cs; } ;
typedef  int /*<<< orphan*/  fz_pixmap ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 void* fz_device_gray (int /*<<< orphan*/ *) ; 
 void* fz_device_rgb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * pam_binary_read_image (int /*<<< orphan*/ *,struct info*,unsigned char const*,unsigned char const*,int,unsigned char const**) ; 
 int /*<<< orphan*/ * pnm_ascii_read_image (int /*<<< orphan*/ *,struct info*,unsigned char const*,unsigned char const*,int,int,unsigned char const**) ; 
 int /*<<< orphan*/ * pnm_binary_read_image (int /*<<< orphan*/ *,struct info*,unsigned char const*,unsigned char const*,int,int,unsigned char const**) ; 
 unsigned char* pnm_read_signature (int /*<<< orphan*/ *,unsigned char const*,unsigned char const*,char*) ; 
 unsigned char* pnm_read_white (int /*<<< orphan*/ *,unsigned char const*,unsigned char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static fz_pixmap *
pnm_read_image(fz_context *ctx, struct info *pnm, const unsigned char *p, size_t total, int onlymeta, int subimage)
{
	const unsigned char *e = p + total;
	char signature[3] = { 0 };
	fz_pixmap *pix = NULL;

	while (p < e && ((!onlymeta && subimage >= 0) || onlymeta))
	{
		int subonlymeta = onlymeta || (subimage > 0);

		p = pnm_read_signature(ctx, p, e, signature);
		p = pnm_read_white(ctx, p, e, 0);

		if (!strcmp(signature, "P1"))
		{
			pnm->cs = fz_device_gray(ctx);
			pix = pnm_ascii_read_image(ctx, pnm, p, e, subonlymeta, 1, &p);
		}
		else if (!strcmp(signature, "P2"))
		{
			pnm->cs = fz_device_gray(ctx);
			pix = pnm_ascii_read_image(ctx, pnm, p, e, subonlymeta, 0, &p);
		}
		else if (!strcmp(signature, "P3"))
		{
			pnm->cs = fz_device_rgb(ctx);
			pix = pnm_ascii_read_image(ctx, pnm, p, e, subonlymeta, 0, &p);
		}
		else if (!strcmp(signature, "P4"))
		{
			pnm->cs = fz_device_gray(ctx);
			pix = pnm_binary_read_image(ctx, pnm, p, e, subonlymeta, 1, &p);
		}
		else if (!strcmp(signature, "P5"))
		{
			pnm->cs = fz_device_gray(ctx);
			pix = pnm_binary_read_image(ctx, pnm, p, e, subonlymeta, 0, &p);
		}
		else if (!strcmp(signature, "P6"))
		{
			pnm->cs = fz_device_rgb(ctx);
			pix = pnm_binary_read_image(ctx, pnm, p, e, subonlymeta, 0, &p);
		}
		else if (!strcmp(signature, "P7"))
			pix = pam_binary_read_image(ctx, pnm, p, e, subonlymeta, &p);
		else
			fz_throw(ctx, FZ_ERROR_GENERIC, "unsupported portable anymap signature (0x%02x, 0x%02x)", signature[0], signature[1]);

		if (onlymeta)
			pnm->subimages++;
		if (subimage >= 0)
			subimage--;
	}

	if (p >= e && subimage >= 0)
		fz_throw(ctx, FZ_ERROR_GENERIC, "subimage count out of range");

	return pix;
}