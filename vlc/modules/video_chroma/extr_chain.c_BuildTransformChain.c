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
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  orientation; } ;
struct TYPE_15__ {TYPE_1__ video; } ;
struct TYPE_13__ {int /*<<< orphan*/  fmt_in; TYPE_8__ fmt_out; } ;
typedef  TYPE_2__ filter_t ;
struct TYPE_14__ {int /*<<< orphan*/  video; } ;
typedef  TYPE_3__ es_format_t ;

/* Variables and functions */
 int CreateChain (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  EsFormatMergeSize (TYPE_3__*,TYPE_8__*,int /*<<< orphan*/ *) ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  es_format_Clean (TYPE_3__*) ; 
 int /*<<< orphan*/  es_format_Copy (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  video_format_TransformTo (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int BuildTransformChain( filter_t *p_filter )
{

    es_format_t fmt_mid;
    int i_ret;

    /* Lets try transform first, then (potentially) resize+chroma */
    msg_Dbg( p_filter, "Trying to build transform, then chroma+resize" );
    es_format_Copy( &fmt_mid, &p_filter->fmt_in );
    video_format_TransformTo(&fmt_mid.video, p_filter->fmt_out.video.orientation);
    i_ret = CreateChain( p_filter, &fmt_mid );
    es_format_Clean( &fmt_mid );
    if( i_ret == VLC_SUCCESS )
        return VLC_SUCCESS;

    /* Lets try resize+chroma first, then transform */
    msg_Dbg( p_filter, "Trying to build chroma+resize" );
    EsFormatMergeSize( &fmt_mid, &p_filter->fmt_out, &p_filter->fmt_in );
    i_ret = CreateChain( p_filter, &fmt_mid );
    es_format_Clean( &fmt_mid );
    return i_ret;
}