#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  pu_dirac_vidfmt_frate ;
typedef  int /*<<< orphan*/  p_dirac_frate_tbl ;
struct TYPE_9__ {char* packet; int /*<<< orphan*/  bytes; } ;
typedef  TYPE_3__ ogg_packet ;
struct TYPE_7__ {int b_old; int b_interlaced; } ;
struct TYPE_8__ {TYPE_1__ dirac; } ;
struct TYPE_10__ {int b_force_backup; int /*<<< orphan*/  dts; TYPE_2__ special; } ;
typedef  TYPE_4__ logical_stream_t ;
typedef  int /*<<< orphan*/  bs_t ;

/* Variables and functions */
 int __MAX (int,int) ; 
 int /*<<< orphan*/  bs_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bs_skip (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  date_Init (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ dirac_bool (int /*<<< orphan*/ *) ; 
 void* dirac_uint (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool Ogg_ReadDiracHeader( logical_stream_t *p_stream,
                                 ogg_packet *p_oggpacket )
{
    p_stream->special.dirac.b_old = (p_oggpacket->packet[0] == 'K');

    static const struct {
        uint32_t u_n /* numerator */, u_d /* denominator */;
    } p_dirac_frate_tbl[] = { /* table 10.3 */
        {1,1}, /* this first value is never used */
        {24000,1001}, {24,1}, {25,1}, {30000,1001}, {30,1},
        {50,1}, {60000,1001}, {60,1}, {15000,1001}, {25,2},
    };
    static const size_t u_dirac_frate_tbl = sizeof(p_dirac_frate_tbl)/sizeof(*p_dirac_frate_tbl);

    static const uint32_t pu_dirac_vidfmt_frate[] = { /* table C.1 */
        1, 9, 10, 9, 10, 9, 10, 4, 3, 7, 6, 4, 3, 7, 6, 2, 2, 7, 6, 7, 6,
    };
    static const size_t u_dirac_vidfmt_frate = sizeof(pu_dirac_vidfmt_frate)/sizeof(*pu_dirac_vidfmt_frate);

    bs_t bs;

    /* Backing up stream headers is not required -- seqhdrs are repeated
     * thoughout the stream at suitable decoding start points */
    p_stream->b_force_backup = false;

    /* read in useful bits from sequence header */
    bs_init( &bs, p_oggpacket->packet, p_oggpacket->bytes );
    bs_skip( &bs, 13*8); /* parse_info_header */
    dirac_uint( &bs ); /* major_version */
    dirac_uint( &bs ); /* minor_version */
    dirac_uint( &bs ); /* profile */
    dirac_uint( &bs ); /* level */

    uint32_t u_video_format = dirac_uint( &bs ); /* index */
    if( u_video_format >= u_dirac_vidfmt_frate )
    {
        /* don't know how to parse this ogg dirac stream */
        return false;
    }

    if( dirac_bool( &bs ) )
    {
        dirac_uint( &bs ); /* frame_width */
        dirac_uint( &bs ); /* frame_height */
    }

    if( dirac_bool( &bs ) )
    {
        dirac_uint( &bs ); /* chroma_format */
    }

    if( dirac_bool( &bs ) )
    {
        p_stream->special.dirac.b_interlaced = dirac_uint( &bs ); /* scan_format */
    }
    else
        p_stream->special.dirac.b_interlaced = false;

    uint32_t u_n = p_dirac_frate_tbl[pu_dirac_vidfmt_frate[u_video_format]].u_n;
    uint32_t u_d = p_dirac_frate_tbl[pu_dirac_vidfmt_frate[u_video_format]].u_d;
    u_d = __MAX( u_d, 1 );
    if( dirac_bool( &bs ) )
    {
        uint32_t u_frame_rate_index = dirac_uint( &bs );
        if( u_frame_rate_index >= u_dirac_frate_tbl )
        {
            /* something is wrong with this stream */
            return false;
        }
        u_n = p_dirac_frate_tbl[u_frame_rate_index].u_n;
        u_d = p_dirac_frate_tbl[u_frame_rate_index].u_d;
        if( u_frame_rate_index == 0 )
        {
            u_n = dirac_uint( &bs ); /* frame_rate_numerator */
            u_d = dirac_uint( &bs ); /* frame_rate_denominator */
        }
    }

    if( !u_n || !u_d )
        return false;

    /*
     * NB, OggDirac granulepos values are in units of 2*picturerate
     * When picture_coding_mode = 0 (progressive),
     * pt increments by two for each picture in display order.
     * When picture_coding_mode = 1 (interlace),
     * pt increments by one for each field in display order. */
    date_Init( &p_stream->dts, 2 * u_n, u_d );

    return true;
}