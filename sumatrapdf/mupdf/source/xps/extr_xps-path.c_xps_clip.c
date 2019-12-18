#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xps_resource ;
struct TYPE_5__ {int /*<<< orphan*/ * dev; } ;
typedef  TYPE_1__ xps_document ;
typedef  int /*<<< orphan*/  fz_xml ;
typedef  int /*<<< orphan*/  fz_path ;
typedef  int /*<<< orphan*/  fz_matrix ;
typedef  int /*<<< orphan*/  fz_device ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_clip_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_drop_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_infinite_rect ; 
 int /*<<< orphan*/ * fz_new_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xps_parse_abbreviated_geometry (int /*<<< orphan*/ *,TYPE_1__*,char*,int*) ; 
 int /*<<< orphan*/ * xps_parse_path_geometry (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 

void
xps_clip(fz_context *ctx, xps_document *doc, fz_matrix ctm, xps_resource *dict, char *clip_att, fz_xml *clip_tag)
{
	fz_device *dev = doc->dev;
	fz_path *path;
	int fill_rule = 0;

	if (clip_att)
		path = xps_parse_abbreviated_geometry(ctx, doc, clip_att, &fill_rule);
	else if (clip_tag)
		path = xps_parse_path_geometry(ctx, doc, dict, clip_tag, 0, &fill_rule);
	else
		path = fz_new_path(ctx);
	fz_clip_path(ctx, dev, path, fill_rule == 0, ctm, fz_infinite_rect);
	fz_drop_path(ctx, path);
}