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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int FZ_LN2 ; 
 float expf (int) ; 
 int sqrtf (float) ; 

__attribute__((used)) static inline int
sgilog16val(fz_context *ctx, uint16_t v)
{
	int Le;
	float Y;

	Le = v & 0x7fff;
	if (!Le)
		Y = 0;
	else
	{
		Y = expf(FZ_LN2/256 * (Le + .5f) - FZ_LN2*64);
		if (v & 0x8000)
			Y = -Y;
	}

	return ((Y <= 0) ? 0 : (Y >= 1) ? 255 : (int)(256*sqrtf(Y)));
}