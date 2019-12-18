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
struct TYPE_3__ {int* index; int patch_l; } ;
typedef  TYPE_1__ fz_weights ;

/* Variables and functions */

__attribute__((used)) static void
check_weights(fz_weights *weights, int j, int w, float x, float wf)
{
	int idx, len;
	int sum = 0;
	int max = -256;
	int maxidx = 0;
	int i;

	idx = weights->index[j - weights->patch_l];
	idx++; /* min */
	len = weights->index[idx++];

	for(i=0; i < len; i++)
	{
		int v = weights->index[idx++];
		sum += v;
		if (v > max)
		{
			max = v;
			maxidx = idx;
		}
	}
	/* If we aren't the first or last pixel, OR if the sum is too big
	 * then adjust it. */
	if (((j != 0) && (j != w-1)) || (sum > 256))
		weights->index[maxidx-1] += 256-sum;
	/* Otherwise, if we are the first pixel, and it's fully covered, then
	 * adjust it. */
	else if ((j == 0) && (x < 0.0001f) && (sum != 256))
		weights->index[maxidx-1] += 256-sum;
	/* Finally, if we are the last pixel, and it's fully covered, then
	 * adjust it. */
	else if ((j == w-1) && (w - wf < 0.0001f) && (sum != 256))
		weights->index[maxidx-1] += 256-sum;
}