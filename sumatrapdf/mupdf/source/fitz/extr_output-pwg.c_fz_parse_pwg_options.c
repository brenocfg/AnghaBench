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
struct TYPE_5__ {void* row_step; void* row_feed; void* row_count; void* compression; void* media_type_num; void* tumble; void* tray_switch; void* separations; void** PageSize; void* output_face_up; void* orientation; void* num_copies; void* negative_print; void* mirror_print; void* media_weight; void* media_position; void* manual_feed; void* leading_edge; void* jog; void* insert_sheet; void* duplex; void* cut_media; void* collate; void* advance_media; void* advance_distance; int /*<<< orphan*/  page_size_name; int /*<<< orphan*/  rendering_intent; int /*<<< orphan*/  output_type; int /*<<< orphan*/  media_type; int /*<<< orphan*/  media_color; int /*<<< orphan*/  media_class; } ;
typedef  TYPE_1__ fz_pwg_options ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 void* fz_atoi (char const*) ; 
 int /*<<< orphan*/  fz_copy_option (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ fz_has_option (int /*<<< orphan*/ *,char const*,char*,char const**) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  warn_if_long (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

fz_pwg_options *
fz_parse_pwg_options(fz_context *ctx, fz_pwg_options *opts, const char *args)
{
	const char *val;

	memset(opts, 0, sizeof *opts);

	if (fz_has_option(ctx, args, "media_class", &val))
		warn_if_long(ctx, "media_class", fz_copy_option(ctx, val, opts->media_class, 64));
	if (fz_has_option(ctx, args, "media_color", &val))
		warn_if_long(ctx, "media_color", fz_copy_option(ctx, val, opts->media_color, 64));
	if (fz_has_option(ctx, args, "media_type", &val))
		warn_if_long(ctx, "media_type", fz_copy_option(ctx, val, opts->media_type, 64));
	if (fz_has_option(ctx, args, "output_type", &val))
		warn_if_long(ctx, "output_type", fz_copy_option(ctx, val, opts->output_type, 64));
	if (fz_has_option(ctx, args, "rendering_intent", &val))
		warn_if_long(ctx, "rendering_intent", fz_copy_option(ctx, val, opts->rendering_intent, 64));
	if (fz_has_option(ctx, args, "page_size_name", &val))
		warn_if_long(ctx, "page_size_name", fz_copy_option(ctx, val, opts->page_size_name, 64));
	if (fz_has_option(ctx, args, "advance_distance", &val))
		opts->advance_distance = fz_atoi(val);
	if (fz_has_option(ctx, args, "advance_media", &val))
		opts->advance_media = fz_atoi(val);
	if (fz_has_option(ctx, args, "collate", &val))
		opts->collate = fz_atoi(val);
	if (fz_has_option(ctx, args, "cut_media", &val))
		opts->cut_media = fz_atoi(val);
	if (fz_has_option(ctx, args, "duplex", &val))
		opts->duplex = fz_atoi(val);
	if (fz_has_option(ctx, args, "insert_sheet", &val))
		opts->insert_sheet = fz_atoi(val);
	if (fz_has_option(ctx, args, "jog", &val))
		opts->jog = fz_atoi(val);
	if (fz_has_option(ctx, args, "leading_edge", &val))
		opts->leading_edge = fz_atoi(val);
	if (fz_has_option(ctx, args, "manual_feed", &val))
		opts->manual_feed = fz_atoi(val);
	if (fz_has_option(ctx, args, "media_position", &val))
		opts->media_position = fz_atoi(val);
	if (fz_has_option(ctx, args, "media_weight", &val))
		opts->media_weight = fz_atoi(val);
	if (fz_has_option(ctx, args, "mirror_print", &val))
		opts->mirror_print = fz_atoi(val);
	if (fz_has_option(ctx, args, "negative_print", &val))
		opts->negative_print = fz_atoi(val);
	if (fz_has_option(ctx, args, "num_copies", &val))
		opts->num_copies = fz_atoi(val);
	if (fz_has_option(ctx, args, "orientation", &val))
		opts->orientation = fz_atoi(val);
	if (fz_has_option(ctx, args, "output_face_up", &val))
		opts->output_face_up = fz_atoi(val);
	if (fz_has_option(ctx, args, "page_size_x", &val))
		opts->PageSize[0] = fz_atoi(val);
	if (fz_has_option(ctx, args, "page_size_y", &val))
		opts->PageSize[1] = fz_atoi(val);
	if (fz_has_option(ctx, args, "separations", &val))
		opts->separations = fz_atoi(val);
	if (fz_has_option(ctx, args, "tray_switch", &val))
		opts->tray_switch = fz_atoi(val);
	if (fz_has_option(ctx, args, "tumble", &val))
		opts->tumble = fz_atoi(val);
	if (fz_has_option(ctx, args, "media_type_num", &val))
		opts->media_type_num = fz_atoi(val);
	if (fz_has_option(ctx, args, "compression", &val))
		opts->compression = fz_atoi(val);
	if (fz_has_option(ctx, args, "row_count", &val))
		opts->row_count = fz_atoi(val);
	if (fz_has_option(ctx, args, "row_feed", &val))
		opts->row_feed = fz_atoi(val);
	if (fz_has_option(ctx, args, "row_step", &val))
		opts->row_step = fz_atoi(val);

	return opts;
}