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
struct TYPE_3__ {int bpc; int colors; int columns; int /*<<< orphan*/  stride; } ;
typedef  TYPE_1__ fz_predict ;

/* Variables and functions */
 int FZ_MAX_COLORS ; 
 int getcomponent (unsigned char*,int,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putcomponent (unsigned char*,int,int,int) ; 

__attribute__((used)) static void
fz_predict_tiff(fz_predict *state, unsigned char *out, unsigned char *in)
{
	int left[FZ_MAX_COLORS];
	int i, k;
	const int mask = (1 << state->bpc)-1;

	for (k = 0; k < state->colors; k++)
		left[k] = 0;

	/* special fast case */
	if (state->bpc == 8)
	{
		for (i = 0; i < state->columns; i++)
			for (k = 0; k < state->colors; k++)
				*out++ = left[k] = (*in++ + left[k]) & 0xFF;
		return;
	}

	/* putcomponent assumes zeroed memory for bpc < 8 */
	if (state->bpc < 8)
		memset(out, 0, state->stride);

	for (i = 0; i < state->columns; i++)
	{
		for (k = 0; k < state->colors; k++)
		{
			int a = getcomponent(in, i * state->colors + k, state->bpc);
			int b = a + left[k];
			int c = b & mask;
			putcomponent(out, i * state->colors + k, state->bpc, c);
			left[k] = c;
		}
	}
}