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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  fz_stream ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int FZ_LN2 ; 
 float U_NEU ; 
 float V_NEU ; 
 float expf (int) ; 
 int fz_read_byte (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sqrtf (float) ; 
 scalar_t__ uv_decode (float*,float*,int) ; 

__attribute__((used)) static inline int
sgilog24val(fz_context *ctx, fz_stream *chain, uint8_t *rgb)
{
	int b0, b1, b2;
	int luv, p;
	float u, v, s, x, y, X, Y, Z;
	float r, g, b;

	b0 = fz_read_byte(ctx, chain);
	if (b0 < 0)
		return b0;
	b1 = fz_read_byte(ctx, chain);
	if (b1 < 0)
		return b1;
	b2 = fz_read_byte(ctx, chain);
	if (b2 < 0)
		return b2;

	luv = (b0<<16) | (b1<<8) | b2;

	/* decode luminance */
	p = (luv>>14) & 0x3ff;
	Y = (p == 0 ? 0 : expf(FZ_LN2/64*(p+.5f) - FZ_LN2*12));
	if (Y <= 0)
	{
		X = Y = Z = 0;
	}
	else
	{
		/* decode color */
		if (uv_decode(&u, &v, luv & 0x3fff) < 0) {
			u = U_NEU; v = V_NEU;
		}
		s = 6*u - 16*v + 12;
		x = 9*u;
		y = 4*v;
		/* convert to XYZ */
		X = x/y * Y;
		Z = (s-x-y)/y * Y;
	}

	/* assume CCIR-709 primaries */
	r =  2.690f*X + -1.276f*Y + -0.414f*Z;
	g = -1.022f*X +  1.978f*Y +  0.044f*Z;
	b =  0.061f*X + -0.224f*Y +  1.163f*Z;

	/* assume 2.0 gamma for speed */
	/* could use integer sqrt approx., but this is probably faster */
	rgb[0] = (uint8_t)((r<=0) ? 0 : (r >= 1) ? 255 : (int)(256*sqrtf(r)));
	rgb[1] = (uint8_t)((g<=0) ? 0 : (g >= 1) ? 255 : (int)(256*sqrtf(g)));
	rgb[2] = (uint8_t)((b<=0) ? 0 : (b >= 1) ? 255 : (int)(256*sqrtf(b)));

	return 0;
}