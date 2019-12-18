#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_6__ {int /*<<< orphan*/ * p_sys; int /*<<< orphan*/  pf_video_filter; int /*<<< orphan*/  fmt_in; } ;
typedef  TYPE_1__ filter_t ;
struct TYPE_7__ {TYPE_1__* sys; int /*<<< orphan*/ * video; } ;
typedef  TYPE_2__ filter_owner_t ;
typedef  int /*<<< orphan*/  filter_chain_t ;

/* Variables and functions */
 int /*<<< orphan*/  Filter ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int filter_chain_AppendFromString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  filter_chain_Delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * filter_chain_NewVideo (TYPE_1__*,int,TYPE_2__*) ; 
 int /*<<< orphan*/  filter_chain_Reset (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  filter_video_edge_cbs ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*) ; 

__attribute__((used)) static int Open( vlc_object_t *p_this )
{
    int i_ret;
    filter_t *p_filter = (filter_t *)p_this;
    filter_owner_t owner = {
        .video = &filter_video_edge_cbs,
        .sys = p_filter,
    };
    /* Store the filter chain in p_sys */
    filter_chain_t *sys = filter_chain_NewVideo( p_filter, true, &owner );
    if ( sys == NULL)
    {
        msg_Err( p_filter, "Could not allocate filter chain" );
        return VLC_EGENERIC;
    }
    /* Clear filter chain */
    filter_chain_Reset( sys, &p_filter->fmt_in, &p_filter->fmt_in);
    /* Add adjust filter to turn frame black-and-white */
    i_ret = filter_chain_AppendFromString( sys, "adjust{saturation=0}" );
    if ( i_ret == -1 )
    {
        msg_Err( p_filter, "Could not append filter to filter chain" );
        filter_chain_Delete( sys );
        return VLC_EGENERIC;
    }
    /* Add gaussian blur to the frame so to remove noise from the frame */
    i_ret = filter_chain_AppendFromString( sys, "gaussianblur{deviation=1}" );
    if ( i_ret == -1 )
    {
        msg_Err( p_filter, "Could not append filter to filter chain" );
        filter_chain_Delete( sys );
        return VLC_EGENERIC;
    }
    /* Set callback function */
    p_filter->pf_video_filter = Filter;
    p_filter->p_sys = sys;
    return VLC_SUCCESS;
}