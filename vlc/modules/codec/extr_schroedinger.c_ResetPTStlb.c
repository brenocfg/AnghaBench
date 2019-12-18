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
struct TYPE_6__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ encoder_t ;
struct TYPE_7__ {TYPE_1__* pts_tlb; } ;
typedef  TYPE_3__ encoder_sys_t ;
struct TYPE_5__ {int b_empty; } ;

/* Variables and functions */
 int SCHRO_PTS_TLB_SIZE ; 

__attribute__((used)) static void ResetPTStlb( encoder_t *p_enc )
{
    encoder_sys_t *p_sys = p_enc->p_sys;
    for( int i = 0; i < SCHRO_PTS_TLB_SIZE; i++ )
    {
        p_sys->pts_tlb[i].b_empty = true;
    }
}