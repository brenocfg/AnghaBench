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
struct info {int width; int height; int bitcount; int /*<<< orphan*/  compression; } ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  BI_RGB ; 
 unsigned char* fz_calloc (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  fz_warn (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static unsigned char *
bmp_decompress_rle24(fz_context *ctx, struct info *info, const unsigned char *p, const unsigned char **end)
{
	const unsigned char *sp;
	unsigned char *dp, *ep, *decompressed;
	int width = info->width;
	int height = info->height;
	int stride;
	int x, i;

	stride = (width*3 + 3) / 4 * 4;

	sp = p;
	dp = decompressed = fz_calloc(ctx, height, stride);
	ep = dp + height * stride;
	x = 0;

	while (sp + 2 <= *end)
	{
		if (sp[0] == 0 && sp[1] == 0)
		{ /* end of line */
			if (x*3 < stride)
				dp += stride - x*3;
			sp += 2;
			x = 0;
		}
		else if (sp[0] == 0 && sp[1] == 1)
		{ /* end of bitmap */
			dp = ep;
			break;
		}
		else if (sp[0] == 0 && sp[1] == 2)
		{ /* delta */
			int deltax, deltay;
			if (sp + 4 > *end)
				break;
			deltax = sp[2];
			deltay = sp[3];
			dp += deltax*3 + deltay * stride;
			sp += 4;
			x += deltax;
		}
		else if (sp[0] == 0 && sp[1] >= 3)
		{ /* absolute */
			int n = sp[1] * 3;
			int nn = (n + 1) / 2 * 2;
			if (sp + 2 + nn > *end)
				break;
			if (dp + n > ep) {
				fz_warn(ctx, "buffer overflow in bitmap data in bmp image");
				break;
			}
			sp += 2;
			for (i = 0; i < n; i++)
				dp[i] = sp[i];
			dp += n;
			sp += (n + 1) / 2 * 2;
			x += n;
		}
		else
		{ /* encoded */
			int n = sp[0] * 3;
			if (sp + 1 + 3 > *end)
				break;
			if (dp + n > ep) {
				fz_warn(ctx, "buffer overflow in bitmap data in bmp image");
				break;
			}
			for (i = 0; i < n / 3; i++) {
				dp[i * 3 + 0] = sp[1];
				dp[i * 3 + 1] = sp[2];
				dp[i * 3 + 2] = sp[3];
			}
			dp += n;
			sp += 1 + 3;
			x += n;
		}
	}

	if (dp < ep)
		fz_warn(ctx, "premature end of bitmap data in bmp image");

	info->compression = BI_RGB;
	info->bitcount = 24;
	*end = ep;
	return decompressed;
}