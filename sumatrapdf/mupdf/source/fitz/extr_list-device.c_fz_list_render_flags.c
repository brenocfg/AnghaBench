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
 int /*<<< orphan*/  FZ_CMD_RENDER_FLAGS ; 
 int FZ_DEVFLAG_GRIDFIT_AS_TILED ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_append_display_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fz_list_render_flags(fz_context *ctx, fz_device *dev, int set, int clear)
{
	int flags;

	/* Pack the options down */
	if (set == FZ_DEVFLAG_GRIDFIT_AS_TILED && clear == 0)
		flags = 1;
	else if (set == 0 && clear == FZ_DEVFLAG_GRIDFIT_AS_TILED)
		flags = 0;
	else
	{
		assert("Unsupported flags combination" == NULL);
		return;
	}
	fz_append_display_node(
		ctx,
		dev,
		FZ_CMD_RENDER_FLAGS,
		flags, /* flags */
		NULL,
		NULL, /* path */
		NULL, /* color */
		NULL, /* colorspace */
		NULL, /* alpha */
		NULL, /* ctm */
		NULL, /* stroke */
		NULL, /* private_data */
		0); /* private_data_len */
}