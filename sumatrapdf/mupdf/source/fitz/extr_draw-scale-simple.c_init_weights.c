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
struct TYPE_3__ {int count; int new_line; int* index; scalar_t__ patch_l; } ;
typedef  TYPE_1__ fz_weights ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void
init_weights(fz_weights *weights, int j)
{
	int index;

	j -= weights->patch_l;
	assert(weights->count == j-1);
	weights->count++;
	weights->new_line = 1;
	if (j == 0)
		index = weights->index[0];
	else
	{
		index = weights->index[j-1];
		index += 2 + weights->index[index+1];
	}
	weights->index[j] = index; /* row pointer */
	weights->index[index] = 0; /* min */
	weights->index[index+1] = 0; /* len */
}