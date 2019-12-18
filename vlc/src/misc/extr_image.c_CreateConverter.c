#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_12__ {int /*<<< orphan*/  i_chroma; } ;
typedef  TYPE_1__ video_format_t ;
struct TYPE_14__ {scalar_t__ i_y_offset; scalar_t__ i_x_offset; } ;
struct TYPE_15__ {int /*<<< orphan*/  i_codec; TYPE_4__ video; } ;
struct TYPE_13__ {int /*<<< orphan*/  p_module; TYPE_8__ fmt_out; TYPE_8__ fmt_in; } ;
typedef  TYPE_2__ filter_t ;
typedef  int /*<<< orphan*/  es_format_t ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteConverter (TYPE_2__*) ; 
 int /*<<< orphan*/  es_format_Copy (TYPE_8__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  module_need (TYPE_2__*,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  video_format_Copy (TYPE_4__*,TYPE_1__ const*) ; 
 TYPE_2__* vlc_custom_create (int /*<<< orphan*/ *,int,char*) ; 

__attribute__((used)) static filter_t *CreateConverter( vlc_object_t *p_this, const es_format_t *p_fmt_in,
                               const video_format_t *p_fmt_out )
{
    filter_t *p_filter;

    p_filter = vlc_custom_create( p_this, sizeof(filter_t), "filter" );

    es_format_Copy( &p_filter->fmt_in, p_fmt_in );
    es_format_Copy( &p_filter->fmt_out, p_fmt_in );
    video_format_Copy( &p_filter->fmt_out.video, p_fmt_out );

    /* whatever the input offset, write at offset 0 in the target image */
    p_filter->fmt_out.video.i_x_offset = 0;
    p_filter->fmt_out.video.i_y_offset = 0;

    p_filter->fmt_out.i_codec = p_fmt_out->i_chroma;
    p_filter->p_module = module_need( p_filter, "video converter", NULL, false );

    if( !p_filter->p_module )
    {
        msg_Dbg( p_filter, "no video converter found" );
        DeleteConverter( p_filter );
        return NULL;
    }

    return p_filter;
}