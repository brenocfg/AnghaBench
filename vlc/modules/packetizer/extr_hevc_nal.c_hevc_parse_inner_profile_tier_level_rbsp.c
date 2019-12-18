#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {void* inbld_flag; } ;
struct TYPE_5__ {void* one_picture_only_constraint_flag; void* max_14bit_constraint_flag; void* lower_bit_rate_constraint_flag; void* intra_constraint_flag; void* max_monochrome_constraint_flag; void* max_420chroma_constraint_flag; void* max_422chroma_constraint_flag; void* max_8bit_constraint_flag; void* max_10bit_constraint_flag; void* max_12bit_constraint_flag; } ;
struct TYPE_7__ {int profile_idc; int profile_compatibility_flag; TYPE_2__ idc1to5; TYPE_1__ idc4to7; void* frame_only_constraint_flag; void* non_packed_constraint_flag; void* interlaced_source_flag; void* progressive_source_flag; void* tier_flag; void* profile_space; } ;
typedef  TYPE_3__ hevc_inner_profile_tier_level_t ;
typedef  int /*<<< orphan*/  bs_t ;

/* Variables and functions */
 void* bs_read (int /*<<< orphan*/ *,int) ; 
 void* bs_read1 (int /*<<< orphan*/ *) ; 
 int bs_remain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bs_skip (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool hevc_parse_inner_profile_tier_level_rbsp( bs_t *p_bs,
                                                      hevc_inner_profile_tier_level_t *p_in )
{
    if( bs_remain( p_bs ) < 88 )
        return false;

    p_in->profile_space = bs_read( p_bs, 2 );
    p_in->tier_flag = bs_read1( p_bs );
    p_in->profile_idc = bs_read( p_bs, 5 );
    p_in->profile_compatibility_flag = bs_read( p_bs, 32 );
    p_in->progressive_source_flag = bs_read1( p_bs );
    p_in->interlaced_source_flag = bs_read1( p_bs );
    p_in->non_packed_constraint_flag = bs_read1( p_bs );
    p_in->frame_only_constraint_flag = bs_read1( p_bs );

    if( ( p_in->profile_idc >= 4 && p_in->profile_idc <= 10 ) ||
        ( p_in->profile_compatibility_flag & 0x0F700000 ) )
    {
        p_in->idc4to7.max_12bit_constraint_flag = bs_read1( p_bs );
        p_in->idc4to7.max_10bit_constraint_flag = bs_read1( p_bs );
        p_in->idc4to7.max_8bit_constraint_flag = bs_read1( p_bs );
        p_in->idc4to7.max_422chroma_constraint_flag = bs_read1( p_bs );
        p_in->idc4to7.max_420chroma_constraint_flag = bs_read1( p_bs );
        p_in->idc4to7.max_monochrome_constraint_flag = bs_read1( p_bs );
        p_in->idc4to7.intra_constraint_flag = bs_read1( p_bs );
        p_in->idc4to7.one_picture_only_constraint_flag = bs_read1( p_bs );
        p_in->idc4to7.lower_bit_rate_constraint_flag = bs_read1( p_bs );
        if( p_in->profile_idc == 5 ||
            p_in->profile_idc == 9 ||
            p_in->profile_idc == 10 ||
           (p_in->profile_compatibility_flag & 0x08600000) )
        {
            p_in->idc4to7.max_14bit_constraint_flag = bs_read1( p_bs );
            bs_skip( p_bs, 33 );
        }
        else bs_skip( p_bs, 34 );
    }
    else if( p_in->profile_idc == 2 ||
            (p_in->profile_compatibility_flag & 0x20000000) )
    {
        bs_skip( p_bs, 7 );
        p_in->idc4to7.one_picture_only_constraint_flag = bs_read1( p_bs );
        bs_skip( p_bs, 35 );
    }
    else
    {
        bs_read( p_bs, 43 );
    }

    if( ( p_in->profile_idc >= 1 && p_in->profile_idc <= 5 ) ||
         p_in->profile_idc == 9 ||
        ( p_in->profile_compatibility_flag & 0x7C400000 ) )
        p_in->idc1to5.inbld_flag = bs_read1( p_bs );
    else
        bs_skip( p_bs, 1 );

    return true;
}