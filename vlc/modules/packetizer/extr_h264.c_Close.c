#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_7__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ decoder_t ;
struct TYPE_8__ {int /*<<< orphan*/  p_ccs; int /*<<< orphan*/  packetizer; } ;
typedef  TYPE_2__ decoder_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  DropStoredNAL (TYPE_2__*) ; 
 int H264_PPS_ID_MAX ; 
 int H264_SPS_ID_MAX ; 
 int /*<<< orphan*/  StorePPS (TYPE_2__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StoreSPS (TYPE_2__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cc_storage_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  packetizer_Clean (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Close( vlc_object_t *p_this )
{
    decoder_t *p_dec = (decoder_t*)p_this;
    decoder_sys_t *p_sys = p_dec->p_sys;
    int i;

    DropStoredNAL( p_sys );
    for( i = 0; i <= H264_SPS_ID_MAX; i++ )
        StoreSPS( p_sys, i, NULL, NULL );
    for( i = 0; i <= H264_PPS_ID_MAX; i++ )
        StorePPS( p_sys, i, NULL, NULL );

    packetizer_Clean( &p_sys->packetizer );

    cc_storage_delete( p_sys->p_ccs );

    free( p_sys );
}