#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_4__ {scalar_t__ lower_bit_rate_constraint_flag; scalar_t__ one_picture_only_constraint_flag; scalar_t__ intra_constraint_flag; scalar_t__ max_monochrome_constraint_flag; scalar_t__ max_420chroma_constraint_flag; scalar_t__ max_422chroma_constraint_flag; scalar_t__ max_8bit_constraint_flag; scalar_t__ max_10bit_constraint_flag; scalar_t__ max_12bit_constraint_flag; scalar_t__ max_14bit_constraint_flag; } ;
struct TYPE_5__ {TYPE_1__ idc4to7; } ;
typedef  TYPE_2__ hevc_inner_profile_tier_level_t ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 

__attribute__((used)) static unsigned hevc_make_indication( const hevc_inner_profile_tier_level_t *p )
{
    uint8_t flags[] =
    {
        p->idc4to7.max_14bit_constraint_flag,
        p->idc4to7.max_12bit_constraint_flag,
        p->idc4to7.max_10bit_constraint_flag,
        p->idc4to7.max_8bit_constraint_flag,
        p->idc4to7.max_422chroma_constraint_flag,
        p->idc4to7.max_420chroma_constraint_flag,
        p->idc4to7.max_monochrome_constraint_flag,
        p->idc4to7.intra_constraint_flag,
        p->idc4to7.one_picture_only_constraint_flag,
        p->idc4to7.lower_bit_rate_constraint_flag,
    };
    unsigned indication = 0;
    for( size_t i=0; i<ARRAY_SIZE(flags); i++ )
    {
        if( flags[i] )
            indication |= (1 << (ARRAY_SIZE(flags) - 1 - i));
    }
    return indication;
}