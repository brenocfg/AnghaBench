#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  i_sar_den; int /*<<< orphan*/  i_sar_num; int /*<<< orphan*/  orientation; int /*<<< orphan*/  i_y_offset; int /*<<< orphan*/  i_x_offset; int /*<<< orphan*/  i_visible_height; int /*<<< orphan*/  i_visible_width; int /*<<< orphan*/  i_height; int /*<<< orphan*/  i_width; } ;
struct TYPE_9__ {TYPE_1__ video; } ;
typedef  TYPE_2__ es_format_t ;

/* Variables and functions */
 int /*<<< orphan*/  es_format_Copy (TYPE_2__*,TYPE_2__ const*) ; 

__attribute__((used)) static void EsFormatMergeSize( es_format_t *p_dst,
                               const es_format_t *p_base,
                               const es_format_t *p_size )
{
    es_format_Copy( p_dst, p_base );

    p_dst->video.i_width  = p_size->video.i_width;
    p_dst->video.i_height = p_size->video.i_height;

    p_dst->video.i_visible_width  = p_size->video.i_visible_width;
    p_dst->video.i_visible_height = p_size->video.i_visible_height;

    p_dst->video.i_x_offset = p_size->video.i_x_offset;
    p_dst->video.i_y_offset = p_size->video.i_y_offset;

    p_dst->video.orientation = p_size->video.orientation;
    p_dst->video.i_sar_num = p_size->video.i_sar_num;
    p_dst->video.i_sar_den = p_size->video.i_sar_den;
}