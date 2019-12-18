#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  input_thread_t ;
struct TYPE_4__ {TYPE_1__* master; } ;
struct TYPE_3__ {int i_title_end; int i_title_offset; int i_seekpoint_end; int i_seekpoint_offset; } ;

/* Variables and functions */
 int VLC_DEMUXER_EOF ; 
 int VLC_DEMUXER_SUCCESS ; 
 TYPE_2__* input_priv (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int UpdateTitleSeekpoint( input_thread_t *p_input,
                                 int i_title, int i_seekpoint )
{
    int i_title_end = input_priv(p_input)->master->i_title_end -
                        input_priv(p_input)->master->i_title_offset;
    int i_seekpoint_end = input_priv(p_input)->master->i_seekpoint_end -
                            input_priv(p_input)->master->i_seekpoint_offset;

    if( i_title_end >= 0 && i_seekpoint_end >= 0 )
    {
        if( i_title > i_title_end ||
            ( i_title == i_title_end && i_seekpoint > i_seekpoint_end ) )
            return VLC_DEMUXER_EOF;
    }
    else if( i_seekpoint_end >= 0 )
    {
        if( i_seekpoint > i_seekpoint_end )
            return VLC_DEMUXER_EOF;
    }
    else if( i_title_end >= 0 )
    {
        if( i_title > i_title_end )
            return VLC_DEMUXER_EOF;
    }
    return VLC_DEMUXER_SUCCESS;
}