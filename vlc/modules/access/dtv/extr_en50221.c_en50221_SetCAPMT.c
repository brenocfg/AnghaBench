#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ i_program_number; } ;
typedef  TYPE_2__ en50221_capmt_info_t ;
struct TYPE_16__ {TYPE_1__* p_sessions; TYPE_2__** pp_selected_programs; } ;
typedef  TYPE_3__ cam_t ;
struct TYPE_14__ {scalar_t__ i_resource_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAPMTAdd (TYPE_3__*,unsigned int,TYPE_2__*) ; 
 int /*<<< orphan*/  CAPMTDelete (TYPE_3__*,unsigned int,TYPE_2__*) ; 
 int CAPMTNeedsDescrambling (TYPE_2__*) ; 
 int /*<<< orphan*/  CAPMTUpdate (TYPE_3__*,unsigned int,TYPE_2__*) ; 
 unsigned int MAX_PROGRAMS ; 
 unsigned int MAX_SESSIONS ; 
 scalar_t__ RI_CONDITIONAL_ACCESS_SUPPORT ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  en50221_capmt_Delete (TYPE_2__*) ; 

int en50221_SetCAPMT( cam_t * p_cam, en50221_capmt_info_t *p_info )
{
    bool b_update = false;
    bool b_needs_descrambling = CAPMTNeedsDescrambling( p_info );

    for ( unsigned i = 0; i < MAX_PROGRAMS; i++ )
    {
        if ( p_cam->pp_selected_programs[i] != NULL
              && p_cam->pp_selected_programs[i]->i_program_number
                  == p_info->i_program_number )
        {
            b_update = true;

            if ( !b_needs_descrambling )
            {
                en50221_capmt_Delete( p_info );
                p_info = p_cam->pp_selected_programs[i];
                p_cam->pp_selected_programs[i] = NULL;
            }
            else if( p_info != p_cam->pp_selected_programs[i] )
            {
                en50221_capmt_Delete( p_cam->pp_selected_programs[i] );
                p_cam->pp_selected_programs[i] = p_info;
            }

            break;
        }
    }

    if ( !b_update && b_needs_descrambling )
    {
        for ( unsigned i = 0; i < MAX_PROGRAMS; i++ )
        {
            if ( p_cam->pp_selected_programs[i] == NULL )
            {
                p_cam->pp_selected_programs[i] = p_info;
                break;
            }
        }
    }

    if ( b_update || b_needs_descrambling )
    {
        for ( unsigned i = 1; i <= MAX_SESSIONS; i++ )
        {
            if ( p_cam->p_sessions[i - 1].i_resource_id
                    == RI_CONDITIONAL_ACCESS_SUPPORT )
            {
                if ( b_update && b_needs_descrambling )
                    CAPMTUpdate( p_cam, i, p_info );
                else if ( b_update )
                    CAPMTDelete( p_cam, i, p_info );
                else
                    CAPMTAdd( p_cam, i, p_info );
            }
        }
    }

    if ( !b_needs_descrambling )
    {
        en50221_capmt_Delete( p_info );
    }

    return VLC_SUCCESS;
}