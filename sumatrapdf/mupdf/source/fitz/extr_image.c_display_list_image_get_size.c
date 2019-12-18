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
typedef  int /*<<< orphan*/  fz_image ;
typedef  int /*<<< orphan*/  fz_display_list_image ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */

__attribute__((used)) static size_t
display_list_image_get_size(fz_context *ctx, fz_image *image_)
{
	fz_display_list_image *image = (fz_display_list_image *)image_;

	if (image == NULL)
		return 0;

	return sizeof(fz_display_list_image) + 4096; /* FIXME */
}