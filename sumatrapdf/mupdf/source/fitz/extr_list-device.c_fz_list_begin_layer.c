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
typedef  int /*<<< orphan*/  fz_device ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_CMD_BEGIN_LAYER ; 
 int /*<<< orphan*/  fz_append_display_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static void
fz_list_begin_layer(fz_context *ctx, fz_device *dev, const char *layer_name)
{
	fz_append_display_node(
		ctx,
		dev,
		FZ_CMD_BEGIN_LAYER,
		0, /* flags */
		NULL,
		NULL, /* path */
		NULL, /* color */
		NULL, /* colorspace */
		NULL, /* alpha */
		NULL,
		NULL, /* stroke */
		layer_name, /* private_data */
		1+strlen(layer_name)); /* private_data_len */
}