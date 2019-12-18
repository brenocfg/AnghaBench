#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  stream_t ;
struct TYPE_7__ {scalar_t__ i_parent; scalar_t__ i_type; int /*<<< orphan*/  (* MP4_ReadBox_function ) (int /*<<< orphan*/ *,TYPE_1__*) ;} ;
struct TYPE_6__ {scalar_t__ i_type; } ;
typedef  TYPE_1__ MP4_Box_t ;

/* Variables and functions */
 TYPE_5__* MP4_Box_Function ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int MP4_Box_Read_Specific( stream_t *p_stream, MP4_Box_t *p_box, MP4_Box_t *p_father )
{
    int i_index;

    for( i_index = 0; ; i_index++ )
    {
        if ( MP4_Box_Function[i_index].i_parent &&
             p_father && p_father->i_type != MP4_Box_Function[i_index].i_parent )
            continue;

        if( ( MP4_Box_Function[i_index].i_type == p_box->i_type )||
            ( MP4_Box_Function[i_index].i_type == 0 ) )
        {
            break;
        }
    }

    if( !(MP4_Box_Function[i_index].MP4_ReadBox_function)( p_stream, p_box ) )
    {
        return VLC_EGENERIC;
    }

    return VLC_SUCCESS;
}