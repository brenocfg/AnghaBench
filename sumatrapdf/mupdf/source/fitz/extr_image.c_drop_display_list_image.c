#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_image ;
struct TYPE_2__ {int /*<<< orphan*/  list; } ;
typedef  TYPE_1__ fz_display_list_image ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_drop_display_list (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void drop_display_list_image(fz_context *ctx, fz_image *image_)
{
	fz_display_list_image *image = (fz_display_list_image *)image_;

	if (image == NULL)
		return;
	fz_drop_display_list(ctx, image->list);
}