#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  stime_t ;

/* Variables and functions */
 int /*<<< orphan*/  ExtractPESTimestamp (int const*,int const,int /*<<< orphan*/ *) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) inline
static int ParsePESHeader( vlc_object_t *p_object, const uint8_t *p_header, size_t i_header,
                           unsigned *pi_skip, stime_t *pi_dts, stime_t *pi_pts,
                           uint8_t *pi_stream_id, bool *pb_pes_scambling )
{
    unsigned i_skip;

    if ( i_header < 9 )
        return VLC_EGENERIC;

    *pi_stream_id = p_header[3];

    switch( p_header[3] )
    {
    case 0xBC:  /* Program stream map */
    case 0xBE:  /* Padding */
    case 0xBF:  /* Private stream 2 */
    case 0xF0:  /* ECM */
    case 0xF1:  /* EMM */
    case 0xFF:  /* Program stream directory */
    case 0xF2:  /* DSMCC stream */
    case 0xF8:  /* ITU-T H.222.1 type E stream */
        i_skip = 6;
        if( pb_pes_scambling )
            *pb_pes_scambling = false;
        break;
    default:
        if( ( p_header[6]&0xC0 ) == 0x80 )
        {
            /* mpeg2 PES */
            i_skip = p_header[8] + 9;

            if( pb_pes_scambling )
                *pb_pes_scambling = p_header[6]&0x30;

            if( p_header[7]&0x80 )    /* has pts */
            {
                if( i_header >= 9 + 5 )
                   (void) ExtractPESTimestamp( &p_header[9], p_header[7] >> 6, pi_pts );

                if( ( p_header[7]&0x40 ) &&    /* has dts */
                    i_header >= 14 + 5 )
                   (void) ExtractPESTimestamp( &p_header[14], 0x01, pi_dts );
            }
        }
        else
        {
            /* FIXME?: WTH do we have undocumented MPEG1 packet stuff here ?
               This code path should not be valid, but seems some ppl did
               put MPEG1 packets into PS or TS.
               Non spec reference for packet format on http://andrewduncan.net/mpeg/mpeg-1.html */
            i_skip = 6;

            if( pb_pes_scambling )
                *pb_pes_scambling = false;

            while( i_skip < 23 && p_header[i_skip] == 0xff )
            {
                i_skip++;
                if( i_header < i_skip + 1 )
                    return VLC_EGENERIC;
            }
            if( i_skip == 23 )
            {
                msg_Err( p_object, "too much MPEG-1 stuffing" );
                return VLC_EGENERIC;
            }
            /* Skip STD buffer size */
            if( ( p_header[i_skip] & 0xC0 ) == 0x40 )
            {
                i_skip += 2;
            }

            if( i_header < i_skip + 1 )
                return VLC_EGENERIC;

            if(  p_header[i_skip]&0x20 )
            {
                if( i_header >= i_skip + 5 )
                    (void) ExtractPESTimestamp( &p_header[i_skip], p_header[i_skip] >> 4, pi_pts );

                if( ( p_header[i_skip]&0x10 ) &&     /* has dts */
                    i_header >= i_skip + 10 )
                {
                    (void) ExtractPESTimestamp( &p_header[i_skip+5], 0x01, pi_dts );
                    i_skip += 10;
                }
                else
                {
                    i_skip += 5;
                }
            }
            else
            {
                if( (p_header[i_skip] & 0xFF) != 0x0F ) /* No pts/dts, lowest bits set to 0x0F */
                    return VLC_EGENERIC;
                i_skip += 1;
            }
        }
        break;
    }

    *pi_skip = i_skip;
    return VLC_SUCCESS;
}