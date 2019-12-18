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
struct TYPE_6__ {int count; int max_len; int* index; int n; int patch_l; int flip; } ;
typedef  TYPE_1__ fz_weights ;
struct TYPE_7__ {int width; } ;
typedef  TYPE_2__ fz_scale_filter ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 scalar_t__ ceilf (int) ; 
 TYPE_1__* fz_malloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static fz_weights *
new_weights(fz_context *ctx, fz_scale_filter *filter, int src_w, float dst_w, int patch_w, int n, int flip, int patch_l)
{
	int max_len;
	fz_weights *weights;

	if (src_w > dst_w)
	{
		/* Scaling down, so there will be a maximum of
		 * 2*filterwidth*src_w/dst_w src pixels
		 * contributing to each dst pixel. */
		max_len = (int)ceilf((2 * filter->width * src_w)/dst_w);
		if (max_len > src_w)
			max_len = src_w;
	}
	else
	{
		/* Scaling up, so there will be a maximum of
		 * 2*filterwidth src pixels contributing to each dst pixel.
		 */
		max_len = 2 * filter->width;
	}
	/* We need the size of the struct,
	 * plus patch_w*sizeof(int) for the index
	 * plus (2+max_len)*sizeof(int) for the weights
	 * plus room for an extra set of weights for reordering.
	 */
	weights = fz_malloc(ctx, sizeof(*weights)+(max_len+3)*(patch_w+1)*sizeof(int));
	if (!weights)
		return NULL;
	weights->count = -1;
	weights->max_len = max_len;
	weights->index[0] = patch_w;
	weights->n = n;
	weights->patch_l = patch_l;
	weights->flip = flip;
	return weights;
}