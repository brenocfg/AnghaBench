#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ stime_t ;
struct TYPE_3__ {unsigned int i_buffer; void* i_pts; void* i_dts; scalar_t__* p_buffer; int /*<<< orphan*/  i_flags; } ;
typedef  TYPE_1__ block_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_FLAG_SCRAMBLED ; 
 void* FROM_SCALE (scalar_t__) ; 
 scalar_t__ ParsePESHeader (int /*<<< orphan*/ *,scalar_t__*,unsigned int,unsigned int*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,int*) ; 
 int VLC_EGENERIC ; 
 scalar_t__ VLC_SUCCESS ; 
 int ps_pkt_id (scalar_t__*,unsigned int) ; 

__attribute__((used)) static inline int ps_pkt_parse_pes( vlc_object_t *p_object, block_t *p_pes, int i_skip_extra )
{
    unsigned int i_skip  = 0;
    stime_t i_pts = -1;
    stime_t i_dts = -1;
    uint8_t i_stream_id = 0;
    bool b_pes_scrambling = false;

    if( ParsePESHeader( p_object, p_pes->p_buffer, p_pes->i_buffer,
                        &i_skip, &i_dts, &i_pts, &i_stream_id, &b_pes_scrambling ) != VLC_SUCCESS )
        return VLC_EGENERIC;

    if( b_pes_scrambling )
        p_pes->i_flags |= BLOCK_FLAG_SCRAMBLED;

    if( i_skip_extra >= 0 )
        i_skip += i_skip_extra;
    else if( p_pes->i_buffer > i_skip + 3 &&
             ( ps_pkt_id( p_pes->p_buffer, p_pes->i_buffer ) == 0xa001 ||
               ps_pkt_id( p_pes->p_buffer, p_pes->i_buffer ) == 0xbda1 ) )
        i_skip += 4 + p_pes->p_buffer[i_skip+3];

    if( p_pes->i_buffer <= i_skip )
    {
        return VLC_EGENERIC;
    }

    p_pes->p_buffer += i_skip;
    p_pes->i_buffer -= i_skip;

    /* ISO/IEC 13818-1 2.7.5: if no pts and no dts, then dts == pts */
    if( i_pts >= 0 && i_dts < 0 )
        i_dts = i_pts;

    if( i_dts >= 0 )
        p_pes->i_dts = FROM_SCALE( i_dts );
    if( i_pts >= 0 )
        p_pes->i_pts = FROM_SCALE( i_pts );

    return VLC_SUCCESS;
}