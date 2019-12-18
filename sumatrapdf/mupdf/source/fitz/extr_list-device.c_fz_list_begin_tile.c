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
typedef  int /*<<< orphan*/  tile ;
typedef  int /*<<< orphan*/  fz_rect ;
typedef  int /*<<< orphan*/  fz_matrix ;
struct TYPE_3__ {float xstep; float ystep; int id; int /*<<< orphan*/  view; } ;
typedef  TYPE_1__ fz_list_tile_data ;
typedef  int /*<<< orphan*/  fz_device ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_CMD_BEGIN_TILE ; 
 int /*<<< orphan*/  fz_append_display_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int) ; 

__attribute__((used)) static int
fz_list_begin_tile(fz_context *ctx, fz_device *dev, fz_rect area, fz_rect view, float xstep, float ystep, fz_matrix ctm, int id)
{
	fz_list_tile_data tile;

	tile.xstep = xstep;
	tile.ystep = ystep;
	tile.view = view;
	tile.id = id;
	fz_append_display_node(
		ctx,
		dev,
		FZ_CMD_BEGIN_TILE,
		0, /* flags */
		&area,
		NULL, /* path */
		NULL, /* color */
		NULL, /* colorspace */
		NULL, /* alpha */
		&ctm, /* ctm */
		NULL, /* stroke */
		&tile, /* private_data */
		sizeof(tile)); /* private_data_len */

	return 0;
}