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
struct TYPE_3__ {int bpp; unsigned char* ref; } ;
typedef  TYPE_1__ fz_predict ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  paeth (unsigned char,unsigned char,unsigned char) ; 

__attribute__((used)) static void
fz_predict_png(fz_context *ctx, fz_predict *state, unsigned char *out, unsigned char *in, size_t len, int predictor)
{
	int bpp = state->bpp;
	size_t i;
	unsigned char *ref = state->ref;

	if ((size_t)bpp > len)
		bpp = (int)len;

	switch (predictor)
	{
	default:
		fz_warn(ctx, "unknown png predictor %d, treating as none", predictor);
		/* fallthrough */
	case 0:
		memcpy(out, in, len);
		break;
	case 1:
		for (i = bpp; i > 0; i--)
		{
			*out++ = *in++;
		}
		for (i = len - bpp; i > 0; i--)
		{
			*out = *in++ + out[-bpp];
			out++;
		}
		break;
	case 2:
		for (i = bpp; i > 0; i--)
		{
			*out++ = *in++ + *ref++;
		}
		for (i = len - bpp; i > 0; i--)
		{
			*out++ = *in++ + *ref++;
		}
		break;
	case 3:
		for (i = bpp; i > 0; i--)
		{
			*out++ = *in++ + (*ref++) / 2;
		}
		for (i = len - bpp; i > 0; i--)
		{
			*out = *in++ + (out[-bpp] + *ref++) / 2;
			out++;
		}
		break;
	case 4:
		for (i = bpp; i > 0; i--)
		{
			*out++ = *in++ + paeth(0, *ref++, 0);
		}
		for (i = len - bpp; i > 0; i --)
		{
			*out = *in++ + paeth(out[-bpp], *ref, ref[-bpp]);
			ref++;
			out++;
		}
		break;
	}
}