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
struct TYPE_3__ {int* index; int patch_l; int max_len; } ;
typedef  TYPE_1__ fz_weights ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
reorder_weights(fz_weights *weights, int j, int src_w)
{
	int idx = weights->index[j - weights->patch_l];
	int min = weights->index[idx++];
	int len = weights->index[idx++];
	int max = weights->max_len;
	int tmp = idx+max;
	int i, off;

	/* Copy into the temporary area */
	memcpy(&weights->index[tmp], &weights->index[idx], sizeof(int)*len);

	/* Pad out if required */
	assert(len <= max);
	assert(min+len <= src_w);
	off = 0;
	if (len < max)
	{
		memset(&weights->index[tmp+len], 0, sizeof(int)*(max-len));
		len = max;
		if (min + len > src_w)
		{
			off = min + len - src_w;
			min = src_w - len;
			weights->index[idx-2] = min;
		}
		weights->index[idx-1] = len;
	}

	/* Copy back into the proper places */
	for (i = 0; i < len; i++)
	{
		weights->index[idx+((min+i+off) % max)] = weights->index[tmp+i];
	}
}