#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int* index; int max_len; scalar_t__ new_line; scalar_t__ patch_l; } ;
typedef  TYPE_1__ fz_weights ;
struct TYPE_7__ {float (* fn ) (TYPE_2__*,float) ;} ;
typedef  TYPE_2__ fz_scale_filter ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 float stub1 (TYPE_2__*,float) ; 

__attribute__((used)) static void
add_weight(fz_weights *weights, int j, int i, fz_scale_filter *filter,
	float x, float F, float G, int src_w, float dst_w)
{
	float dist = j - x + 0.5f - ((i + 0.5f)*dst_w/src_w);
	float f;
	int min, len, index, weight;

	dist *= G;
	if (dist < 0)
		dist = -dist;
	f = filter->fn(filter, dist)*F;
	weight = (int)(256*f+0.5f);

	/* Ensure i is in range */
	if (i < 0 || i >= src_w)
		return;
	if (weight == 0)
	{
		/* We add a fudge factor here to allow for extreme downscales
		 * where all the weights round to 0. Ensure that at least one
		 * (arbitrarily the first one) is non zero. */
		if (weights->new_line && f > 0)
			weight = 1;
		else
			return;
	}

	/* Move j from patch_l...patch_l+patch_w range to 0..patch_w range */
	j -= weights->patch_l;
	if (weights->new_line)
	{
		/* New line */
		weights->new_line = 0;
		index = weights->index[j]; /* row pointer */
		weights->index[index] = i; /* min */
		weights->index[index+1] = 0; /* len */
	}
	index = weights->index[j];
	min = weights->index[index++];
	len = weights->index[index++];
	while (i < min)
	{
		/* This only happens in rare cases, but we need to insert
		 * one earlier. In exceedingly rare cases we may need to
		 * insert more than one earlier. */
		int k;

		for (k = len; k > 0; k--)
		{
			weights->index[index+k] = weights->index[index+k-1];
		}
		weights->index[index] = 0;
		min--;
		len++;
		weights->index[index-2] = min;
		weights->index[index-1] = len;
	}
	if (i-min >= len)
	{
		/* The usual case */
		while (i-min >= ++len)
		{
			weights->index[index+len-1] = 0;
		}
		assert(len-1 == i-min);
		weights->index[index+i-min] = weight;
		weights->index[index-1] = len;
		assert(len <= weights->max_len);
	}
	else
	{
		/* Infrequent case */
		weights->index[index+i-min] += weight;
	}
}