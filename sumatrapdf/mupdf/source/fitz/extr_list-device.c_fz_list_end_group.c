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
 int /*<<< orphan*/  FZ_CMD_END_GROUP ; 
 int /*<<< orphan*/  fz_append_display_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fz_list_end_group(fz_context *ctx, fz_device *dev)
{
	fz_append_display_node(
		ctx,
		dev,
		FZ_CMD_END_GROUP,
		0, /* flags */
		NULL, /* rect */
		NULL, /* path */
		NULL, /* color */
		NULL, /* colorspace */
		NULL, /* alpha */
		NULL, /* ctm */
		NULL, /* stroke */
		NULL, /* private_data */
		0); /* private_data_len */
}