#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ intra_constraint_flag; } ;
struct TYPE_9__ {int profile_idc; TYPE_1__ idc4to7; } ;
struct TYPE_7__ {TYPE_4__ general; } ;
struct TYPE_8__ {TYPE_2__ profile_tier_level; } ;
typedef  TYPE_3__ hevc_sequence_parameter_set_t ;
typedef  enum vlc_hevc_profile_e { ____Placeholder_vlc_hevc_profile_e } vlc_hevc_profile_e ;
typedef  enum hevc_general_profile_idc_e { ____Placeholder_hevc_general_profile_idc_e } hevc_general_profile_idc_e ;

/* Variables and functions */
 unsigned int HEVC_INDICATION_SHIFT ; 
#define  HEVC_PROFILE_IDC_HIGH_THROUGHPUT 130 
#define  HEVC_PROFILE_IDC_REXT 129 
#define  HEVC_PROFILE_IDC_SCREEN_EXTENDED 128 
 int hevc_make_indication (TYPE_4__*) ; 

enum vlc_hevc_profile_e hevc_get_vlc_profile( const hevc_sequence_parameter_set_t *p_sps )
{
    unsigned indication = 0;
    enum hevc_general_profile_idc_e profile = p_sps->profile_tier_level.general.profile_idc;
    switch( profile )
    {
        case HEVC_PROFILE_IDC_REXT:
            indication = hevc_make_indication( &p_sps->profile_tier_level.general ) & 0x1FF;
            break;
        case HEVC_PROFILE_IDC_HIGH_THROUGHPUT:
        case HEVC_PROFILE_IDC_SCREEN_EXTENDED:
            indication = hevc_make_indication( &p_sps->profile_tier_level.general );
            break;
        default:
            break;
    }

    /* all intras have insignifiant lowest bit */
    if( p_sps->profile_tier_level.general.idc4to7.intra_constraint_flag )
        indication &= ~1;

    return (indication << HEVC_INDICATION_SHIFT) | profile;
}