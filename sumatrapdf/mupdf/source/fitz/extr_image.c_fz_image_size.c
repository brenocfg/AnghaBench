#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t (* get_size ) (int /*<<< orphan*/ *,TYPE_1__*) ;} ;
typedef  TYPE_1__ fz_image ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 size_t stub1 (int /*<<< orphan*/ *,TYPE_1__*) ; 

size_t fz_image_size(fz_context *ctx, fz_image *im)
{
	if (im == NULL)
		return 0;

	return im->get_size(ctx, im);
}