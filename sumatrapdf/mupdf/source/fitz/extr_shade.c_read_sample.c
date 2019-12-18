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
typedef  int /*<<< orphan*/  fz_stream ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 float fz_read_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int powf (int,int) ; 

__attribute__((used)) static inline float read_sample(fz_context *ctx, fz_stream *stream, int bits, float min, float max)
{
	/* we use pow(2,x) because (1<<x) would overflow the math on 32-bit samples */
	float bitscale = 1 / (powf(2, bits) - 1);
	return min + fz_read_bits(ctx, stream, bits) * (max - min) * bitscale;
}